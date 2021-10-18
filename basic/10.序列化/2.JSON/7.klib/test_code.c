#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "kson.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
//Example 1: parse and query with kson_by_path() 使用kson_by_path（）解析和查询
void example_1(void)
{
  kson_t *kson;
  const kson_node_t *p;
  kson = kson_parse("{'a' : 1,'b':[0,'isn\\'t',true],'d':[{\n}]}");
  p = kson_by_path(kson->root, 2, "b", 2);
  if (p) printf("Value: %s\n", p->v.str); // this prints "true"
  kson_destroy(kson);
}

//Example 2: parse and query with kson_by_key() and kson_by_index() 使用kson_by_key（）和kson_by_index（）进行解析和查询
void example_2(void)
{
  kson_t *kson;
  const kson_node_t *p;
  kson = kson_parse("{'a' : 1,'b':[0,'isn\\'t',true],'d':[{\n}]}");
  p = kson_by_key(kson->root, "b");
  if (p) p = kson_by_index(p, 2);
  if (p) printf("Value: %s\n", p->v.str); // this also prints "true"
  kson_destroy(kson);
}

//Example 3: recursive tree traversal 递归树遍历
void format_recur(const kson_node_t *p)
{
  long i;
  if (p->key) printf("\"%s\":", p->key);
  if (p->type == KSON_TYPE_BRACKET || p->type == KSON_TYPE_BRACE) {
    putchar(p->type == KSON_TYPE_BRACKET? '[' : '{');
    for (i = 0; i < (long)p->n; ++i) {
      if (i) putchar(',');
      format_recur(p->v.child[i]);
    }
    putchar(p->type == KSON_TYPE_BRACKET? ']' : '}');
  } else {
    if (p->type != KSON_TYPE_NO_QUOTE)
      putchar(p->type == KSON_TYPE_SGL_QUOTE? '\'' : '"');
    fputs(p->v.str, stdout);
    if (p->type != KSON_TYPE_NO_QUOTE)
      putchar(p->type == KSON_TYPE_SGL_QUOTE? '\'' : '"');
  }
}

void example_3(void)
{
  kson_t *kson;
  kson = kson_parse("{'a' : 1,'b':[0,'isn\\'t',true],'d':[{\n}]}");
  format_recur(kson->root);
  putchar('\n');
  kson_destroy(kson);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    example_1();
    example_2();
    example_3();
    return 0;
}