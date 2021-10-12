#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#include <math.h>
#include <errno.h>
#include "json.h"

static char *chomp(char *s)
{
	char *e;
	
	if (s == NULL || *s == 0)
		return s;
	
	e = strchr(s, 0);
	if (e[-1] == '\n')
		*--e = 0;
	return s;
}

static bool expect_literal(const char **sp, const char *str)
{
	const char *s = *sp;
	
	while (*str != '\0')
		if (*s++ != *str++)
			return false;
	
	*sp = s;
	return true;
}

int test(void)
{
	const char *strings_file = "test-strings";
	const char *strings_reencoded_file = "test-strings-reencoded";
	FILE *f, *f2;
	char buffer[1024], buffer2[1024];
	
	f = fopen(strings_file, "rb");
	if (f == NULL) {
		printf("Could not open %s: %s\n", strings_file, strerror(errno));
		return 1;
	}
	f2 = fopen(strings_reencoded_file, "rb");
	if (f2 == NULL) {
		printf("Could not open %s: %s\n", strings_reencoded_file, strerror(errno));
		return 1;
	}
	
	while (fgets(buffer, sizeof(buffer), f)) {
		const char *s = chomp(buffer);
		bool valid;
		JsonNode *node;
		
		if (expect_literal(&s, "valid ")) {
			valid = true;
		} else if (expect_literal(&s, "invalid ")) {
			valid = false;
		} else {
			printf("Invalid line in test-strings: %s\n", buffer);
			continue;
		}
		
		node = json_decode(s);
		
		if (valid) {
			char *reencoded;
			char errmsg[256];
			
			if (node == NULL) {
				printf("%s is valid, but json_decode returned NULL\n", s);
				continue;
			}
			
			if (!json_check(node, errmsg)) {
				printf("Corrupt tree produced by json_decode: %s\n", errmsg);
				continue;
			}
			
			reencoded = json_encode(node);
			
			if (!fgets(buffer2, sizeof(buffer2), f2)) {
				printf("test-strings-reencoded is missing this line: %s\n", reencoded);
				continue;
			}
			chomp(buffer2);
			
			if(strcmp(reencoded, buffer2) == 0)
				printf("0 re-encode %s -> %s\n", s, reencoded);
			else
				printf("1 re-encode %s -> %s\n", s, reencoded);
			
			free(reencoded);
			json_delete(node);
		} else if (node != NULL) {
			printf("%s is invalid, but json_decode returned non-NULL\n", s);
			continue;
		}
	}
	
	if (ferror(f) || fclose(f) != 0 || ferror(f2) || fclose(f2) != 0) {
		printf("I/O error reading test data.\n");
		return 1;
	}
	
	return 0;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    test();
    
    return 0;
}