# CCAN json

http://ccodearchive.net/list.html

http://ccodearchive.net/info/json.html

### Module:

json

### Summary:

Parse and generate JSON (JavaScript Object Notation)

### Author:

Joey Adams

### Description:

This is a library for encoding and decoding JSON that strives to be easy to learn, use, and incorporate into an application.

JSON (JavaScript Object Notation) facilitates passing data among different programming languages, particularly JavaScript. It looks like this:

```
    [
        {
            "id":           1,
            "firstname":    "John",
            "lastname":     "Smith",
            "email":        "john@example.com",
            "likes_pizza":  false
        },
        {
            "id":           2,
            "firstname":    "Linda",
            "lastname":     "Jones",
            "email":        null,
            "likes_pizza":  true
        }
    ]
```



### Example:

```c
#include <ccan/json/json.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int find_number(JsonNode *object, const char *name, double *out)
{
        JsonNode *node = json_find_member(object, name);
        if (node && node->tag == JSON_NUMBER) {
                *out = node->number_;
                return 1;
        }
        return 0;
}

static void solve_pythagorean(JsonNode *triple)
{
        double a = 0, b = 0, c = 0;
        int a_given, b_given, c_given;
        
        if (triple->tag != JSON_OBJECT) {
                fprintf(stderr, "Error: Expected a JSON object.\n");
                exit(EXIT_FAILURE);
        }
        
        a_given = find_number(triple, "a", &a);
        b_given = find_number(triple, "b", &b);
        c_given = find_number(triple, "c", &c);
        
        if (a_given + b_given + c_given != 2) {
                fprintf(stderr, "Error: I need two sides to compute the length of the third.\n");
                exit(EXIT_FAILURE);
        }
        
        if (a_given && b_given) {
                c = sqrt(a*a + b*b);
                json_append_member(triple, "c", json_mknumber(c));
        } else if (a_given && c_given) {
                b = sqrt(c*c - a*a);
                json_append_member(triple, "b", json_mknumber(b));
        } else if (b_given && c_given) {
                a = sqrt(c*c - b*b);
                json_append_member(triple, "a", json_mknumber(a));
        }
}

int main(void)
{
        JsonNode *triples = json_mkarray();
        
        json_append_element(triples, json_decode("{\"a\": 3, \"b\": 4}"));
        json_append_element(triples, json_decode("{\"a\": 5, \"c\": 13}"));
        json_append_element(triples, json_decode("{\"b\": 24, \"c\": 25}"));
        
        JsonNode *triple;
        json_foreach(triple, triples)
                solve_pythagorean(triple);
        
        char *tmp = json_stringify(triples, "\t");
        puts(tmp);
        free(tmp);
        
        json_delete(triples);
        return 0;
}
```

### License:

MIT
