#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
typedef struct UnionFind {
    int *parent;
    int *rank;
} UnionFind;

UnionFind* unionFindCreate(int n) {
    UnionFind *obj = (UnionFind *)malloc(sizeof(UnionFind));
    obj->parent = (int *)malloc(sizeof(int) * n);
    obj->rank = (int *)malloc(sizeof(int) * n);
    memset(obj->rank, 0, sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        obj->parent[i] = i;
    }
    return obj;
}

int find(const UnionFind *obj, int x) {
    if (obj->parent[x] != x) {
        obj->parent[x] = find(obj, obj->parent[x]);
    }
    return obj->parent[x];
}

void uni(UnionFind *obj, int x, int y) {
    int rootx = find(obj, x);
    int rooty = find(obj, y);
    if (rootx != rooty) {
        if (obj->rank[rootx] > obj->rank[rooty]) {
            obj->parent[rooty] = rootx;
        } else if (obj->rank[rootx] < obj->rank[rooty]) {
            obj->parent[rootx] = rooty;
        } else {
            obj->parent[rooty] = rootx;
            obj->rank[rootx]++;
        }
    }
}

void unionFindFree(UnionFind *obj) {
    free(obj->parent);
    free(obj->rank);
    free(obj);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int largestComponentSize(int* nums, int numsSize) {
    int m = nums[0];
    for (int i = 0; i < numsSize; i++) {
        m = MAX(m, nums[i]);
    }
    UnionFind *uf = unionFindCreate(m + 1);
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                uni(uf, num, i);
                uni(uf, num, num / i);
            }
        }
    }
    int *counts = (int *)malloc(sizeof(int) * (m + 1));
    memset(counts, 0, sizeof(int) * (m + 1));
    int ans = 0;
    for (int i = 0; i < numsSize; i++) {
        int root = find(uf, nums[i]);
        counts[root]++;
        ans = MAX(ans, counts[root]);
    }
    free(counts);
    unionFindFree(uf);
    return ans;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int main(int argc, char* argv[])
{
    int buf1[] = {4,6,15,35};
    int buf2[] = {20,50,9,63};
    int buf3[] = {2,3,6,7,4,12,21,39};
    
    printf("%d\n", largestComponentSize(buf1, sizeof(buf1)/sizeof(int)));
    printf("%d\n", largestComponentSize(buf2, sizeof(buf2)/sizeof(int)));
    printf("%d\n", largestComponentSize(buf3, sizeof(buf3)/sizeof(int)));
    
    return 0;
}