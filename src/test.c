#include <stdio.h>
#include <stdlib.h>
#include "tiny_json.h"

static int main_ret = 0;
static int test_pass = 0;
static int test_count = 0;

#define EXPECT_EQUAL_BASE(equality, expect, actual, format)                                                        \
    do                                                                                                             \
    {                                                                                                              \
        test_count++;                                                                                              \
        if (equality)                                                                                              \
            test_pass++;                                                                                           \
        else                                                                                                       \
        {                                                                                                          \
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual); \
            main_ret = 1;                                                                                          \
        }                                                                                                          \
    } while (0)

#define EXPECT_EQUAL_INT(expect, actual) EXPECT_EQUAL_BASE((expect) == (actual), expect, actual, "%d")

static void test_parse_null()
{
    json_value *v = (json_value *)malloc(sizeof(json_value));
    v->type = JSON_FALSE;
    EXPECT_EQUAL_INT(json_parse(v, "null"), PARSE_OK);
    EXPECT_EQUAL_INT(get_type(v), JSON_NULL);
    free(v);
}

static void test_parse()
{
    test_parse_null();
}

int main()
{
    test_parse();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}