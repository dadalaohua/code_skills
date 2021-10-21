#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct {
    int max_iter, w, h;
    double xmin, xmax, ymin, ymax;
    int *k;
} global_t;
 
static void mbrot(void *_g, long i, int tid)
{
    global_t *g = (global_t*)_g;
    double x, x0 = g->xmin + (g->xmax - g->xmin) * (i%g->w) / g->w;
    double y, y0 = g->ymin + (g->ymax - g->ymin) * (i/g->w) / g->h;
    int k;
    x = x0, y = y0;
    for (k = 0; k < g->max_iter; ++k) {
        double z = x * y;
        x *= x; y *= y;
        if (x + y >= 4) break;
        x = x - y + x0;
        y = z + z + y0; 
    }
    g->k[i] = k;
}
 
void kt_for(int n_threads, void (*func)(void*,long,int), void *data, long n);

/************************************************************************/
/*                                                                      */
/************************************************************************/
//Example 1: compute the Mandelbrot set with kt_for()
int main(int argc, char* argv[])
{
    long tot, n_threads = 2;
    global_t global = { 10240*100, 800, 600, -2., -1.2, -1.2, 1.2, 0 };
    tot = global.w * global.h;
    global.k = calloc(tot, sizeof(int));
    // for (i = 0; i < tot; ++i) compute(&global, i, 0);
    kt_for(n_threads, mbrot, &global, tot);
    free(global.k);
    return 0;
}