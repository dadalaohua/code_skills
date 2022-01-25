#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
//结点定义
struct SegmentTree{
    unsigned int left, right, total, childrenExtra;
    struct SegmentTree *lson, *rson;
};

// 获取区间个数
unsigned int regionLength(struct SegmentTree *tree) {
    return tree->right - tree->left + 1;
}

// 将父结点未完成的操作更新到子结点
void updateChildren(struct SegmentTree *root) {
    if (root->lson != NULL && root->rson != NULL && root->childrenExtra != 0) {
        root->lson->total += root->childrenExtra * regionLength(root->lson);
        root->lson->childrenExtra += root->childrenExtra;
        root->rson->total += root->childrenExtra * regionLength(root->rson);
        root->rson->childrenExtra += root->childrenExtra;
        root->childrenExtra = 0;
    }
}

//线段树构建
struct SegmentTree *buildTree(int *num, unsigned int l, unsigned int r) {
    if (l > r) {
        return NULL;
    }
    if (l == r) {
        struct SegmentTree *root = malloc(sizeof(struct SegmentTree));
        root->left = l;
        root->right = r;
        root->total = num[l];
        root->childrenExtra = 0;
        root->lson = NULL;
        root->rson = NULL;
        return root;
    }
    struct SegmentTree *root = malloc(sizeof(struct SegmentTree));
    root->left = l;
    root->right = r;
    root->childrenExtra = 0;
    unsigned int mid = l + ((r - l) >> 1);
    root->lson = buildTree(num, l, mid);
    root->rson = buildTree(num, mid + 1, r);
    root->total = root->lson->total + root->rson->total;
    return root;
}

//区间更新
void addRegion(struct SegmentTree *root, unsigned int regionLeft, unsigned int regionRight, int addNum) {
    if (root == NULL || root->right < regionLeft || root->left > regionRight) {
        return;
    }
    if (root->left >= regionLeft && root->right <= regionRight) {
        root->total += addNum * regionLength(root);
        if (root->left < root->right)root->childrenExtra += addNum;
        return;
    }
    updateChildren(root);
    addRegion(root->lson, regionLeft, regionRight, addNum);
    addRegion(root->rson, regionLeft, regionRight, addNum);
    root->total = root->lson->total + root->rson->total;
}

//区间查询
void queryRegion(struct SegmentTree *root, unsigned int regionLeft, unsigned int regionRight, int* sum) {
    if (root == NULL || root->right < regionLeft || root->left > regionRight) {
        return;
    }
    if (root->left >= regionLeft && root->right <= regionRight) {
        *sum += root->total;
        return;
    }
    updateChildren(root);
    queryRegion(root->lson, regionLeft, regionRight, sum);
    queryRegion(root->rson, regionLeft, regionRight, sum);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    struct SegmentTree *root;
    int num[10];
    int i, sum = 0;
    for(i = 0; i < 10; i++)
        num[i] = i;
    
    root = buildTree(num, 0, 9);
    
    queryRegion(root, 0, 9, &sum);
    printf("sum %d\n", sum);
    
    sum = 0;
    queryRegion(root, 5, 9, &sum);
    printf("sum %d\n", sum);
    
    addRegion(root, 7, 9, 10);
    
    sum = 0;
    queryRegion(root, 5, 9, &sum);
    printf("sum %d\n", sum);

    return 0;
}