#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
/*
https://leetcode.cn/problems/largest-merge-of-two-strings/solutions/2030226/gou-zao-zi-dian-xu-zui-da-de-he-bing-zi-g6az1/
https://oi-wiki.org/string/sa/
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

void sortCharacters(const char *text, int *order) {
    int n = strlen(text);
    int count[128];
    memset(count, 0, sizeof(count));
    for (int i = 0; text[i] != '\0'; i++) {
        count[(unsigned char)text[i]]++;
    }
    for (int i = 1; i < 128; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        count[(unsigned char)text[i]]--;
        order[count[(unsigned char)text[i]]] = i;
    }
}

void computeCharClasses(const char *text, const int* order, int *classfiy) {
    int n = strlen(text);
    classfiy[order[0]] = 0;
    for (int i = 1; i < n; i++) {
        if (text[order[i]] != text[order[i - 1]]) {
            classfiy[order[i]] = classfiy[order[i - 1]] + 1;
        } else {
            classfiy[order[i]] = classfiy[order[i - 1]];
        }
    }
}

void sortDoubled(const char *text, int len, const int *order, const int *classfiy, int *newOrder) {
    int n = strlen(text);
    int count[n];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < n; i++) {
        count[classfiy[i]]++;
    }
    for (int i = 1; i < n; i++) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
        int start = (order[i] - len + n) % n;
        int cl = classfiy[start];
        count[cl]--;
        newOrder[count[cl]] = start;
    }
}

void updateClasses(const int *newOrder, int n, int *classfiy, int len, int *newClassfiy) {
    newClassfiy[newOrder[0]] = 0;
    for (int i = 1; i < n; i++) {
        int curr = newOrder[i];
        int prev = newOrder[i - 1];
        int mid = curr + len;
        int midPrev = (prev + len) % n;
        if (classfiy[curr] != classfiy[prev] || classfiy[mid] != classfiy[midPrev]) {
             newClassfiy[curr] = newClassfiy[prev] + 1;
        } else {
             newClassfiy[curr] = newClassfiy[prev];
        }
    }
}

int  *buildSuffixArray(const char *text) {
    int n = strlen(text);
    int *order = (int *)malloc(sizeof(int) * n);
    int classfiy[n], newOrder[n], newClassfiy[n];
    sortCharacters(text, order);
    computeCharClasses(text, order, classfiy);
    for (int i = 1; i < n; i <<= 1) {
        sortDoubled(text, i, order, classfiy, newOrder);
        updateClasses(newOrder, n, classfiy, i, newClassfiy);
        memcpy(order, newOrder, sizeof(int) * n);
        memcpy(classfiy, newClassfiy, sizeof(int) * n);
    }
    return order;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    char str[100];
    sprintf(str, "aabaaaab*");
    int *suffixArray = buildSuffixArray(str);
    int rank[100];
    for (int i = 0; i < strlen(str); i++) {
        rank[suffixArray[i]] = i;
    }
    
    for (int i = 1; i < strlen(str); i++) {
        printf("suffixArray[%d] %d %s\n", i, suffixArray[i], str + suffixArray[i]);
    }
    for (int i = 0; i < strlen(str) - 1; i++) {
        printf("rank[%d] %d\n", i, rank[i]);
    }
    
    free(suffixArray);
    return 0;
}