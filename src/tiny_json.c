#include "tiny_json.h"
#include <assert.h>
#include <stdlib.h>

/*
    check first character of json string and move pointer to next character
*/
#define EXPECT(c, ch)              \
    do                             \
    {                              \
        assert(*c->json == (*ch)); \
        c->json++;                 \
        ch++;                      \
    } while (0)

typedef struct
{
    const char *json;
} json_context;

/*
    remove whitespace, tab, newline and return characters before json string
*/
static void json_parse_whitespace(json_context *c)
{
    const char *p = c->json;
    while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
    {
        p++;
    }
    c->json = p;
}

/*
    parse type literal (null, true, false) from json string
*/
static int json_parse_literal(json_context *c, json_value *v, const char *literal, json_type type)
{
    EXPECT(c, literal);
    size_t len = 0;
    const char *j = c->json;
    while (*literal != '\0')
    {
        len++;
        if (*j++ != *literal++)
        {
            return PARSE_INVALID_VALUE;
        }
    }
    v->type = type;
    c->json += len;
    return PARSE_OK;
}

/*
    parse json string accoring to its first character
*/
static int json_parse_value(json_context *c, json_value *v)
{
    switch (*c->json)
    {
    case 'n':
        return json_parse_literal(c, v, "null", JSON_NULL);
    case 't':
        return json_parse_literal(c, v, "true", JSON_TRUE);
    case 'f':
        return json_parse_literal(c, v, "false", JSON_FALSE);
    case '\0':
        return PARSE_EXPECT_VALUE;
    default:
        return PARSE_INVALID_VALUE;
    }
}

/*
    parse json type and return parse status
*/
int json_parse(json_value *v, const char *json)
{
    json_context c;
    assert(json != NULL);
    c.json = json;
    v->type = JSON_NULL;
    json_parse_whitespace(&c);
    int parse_ret = json_parse_value(&c, v);
    if (parse_ret == PARSE_OK)
    {
        json_parse_whitespace(&c);
        if (*c.json != '\0')
        {
            return PARSE_ROOT_NOT_SINGULAR;
        }
    }
    return parse_ret;
}

/*
    get json type
*/
json_type get_type(const json_value *v)
{
    assert(v != NULL);
    return v->type;
}

/*
    get json value if json is a number
*/
double get_value(const json_value *v)
{
    assert(v != NULL && v->type == JSON_NUMBER);
    return v->n;
}