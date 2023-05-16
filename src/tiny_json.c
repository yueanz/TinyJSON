#include "tiny_json.h"
#include <assert.h>
#include <stdlib.h>

/*
    check first character of json string and move pointer to next character
*/
#define EXPECT(c, ch)             \
    do                            \
    {                             \
        assert(*c->json == (ch)); \
        c->json++;                \
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
    parse type null from json string
*/
static int json_parse_null(json_context *c, json_value *v)
{
    EXPECT(c, 'n');
    const char *j = c->json;
    if (j[0] == 'u' && j[1] == 'l' && j[2] == 'l')
    {
        v->type = JSON_NULL;
        c->json += 3;
        return PARSE_OK;
    }
    return PARSE_INVALID_VALUE;
}

/*
    parse json string accoring to its first character
*/
static int json_parse_value(json_context *c, json_value *v)
{
    switch (*c->json)
    {
    case 'n':
        return json_parse_null(c, v);
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
    v->type = NULL;
    json_parse_whitespace(&c);
    return json_parse_value(&c, v);
}

/*
    get json type
*/
json_type get_type(const json_value *v)
{
    assert(v != NULL);
    return v->type;
}