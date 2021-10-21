#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "kexpr.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/
// to run:     ./test_code "5.6+exp(x)" x=1.1
int main(int argc, char* argv[])
{
    int i, ret_type, err;
    kexpr_t *ke;
    int64_t vi;
    double vr;
    const char *vs;

    if (argc == 1) {
        fprintf(stderr, "Usage: %s <expr> [var=value [...]]\n", argv[0]);
        return 1;
    }
    ke = ke_parse(argv[1], &err); // parse the expression
    ke_set_default_func(ke);      // enable exp(), log(), etc; no built-in func by default
    if (err) { // parse error
        fprintf(stderr, "Parse error: 0x%x\n", err);
        return 1;
    }
    if (argc > 2) {
        for (i = 2; i < argc; ++i) { // set variables
            char *p, *s = argv[i];
            for (p = s; *p && *p != '='; ++p);
            if (*p == 0) continue; // not an assignment
            *p = 0;
            ke_set_real(ke, s, strtod(p+1, &p));
        }
    }
    err |= ke_eval(ke, &vi, &vr, &vs, &ret_type);
    if (err & KEE_UNFUNC)
        fprintf(stderr, "Evaluation warning: an undefined function returns the first function argument.\n");
    if (err & KEE_UNVAR) fprintf(stderr, "Evaluation warning: unassigned variables are set to 0.\n");
    if (ret_type == KEV_INT) printf("%lld\n", (long long)vi); // the final value is an integer
    else if (ret_type == KEV_REAL) printf("%g\n", vr);        // the final value is a real number
    else printf("%s\n", vs);                                  // the final value is a string
    ke_destroy(ke);
    
    return 0;
}