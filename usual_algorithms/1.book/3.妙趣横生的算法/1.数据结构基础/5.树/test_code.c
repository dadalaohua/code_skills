#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode{
    char data;                                      /*结点的数据域*/
    struct BiTNode *lchild , *rchild;               /*指向左孩子和右孩子*/
} BiTNode, *BiTree;

/*创建一棵二叉树*/
void CreatBiTree(BiTree *T){
    char c;
    
    scanf("%c",&c);
    if(c == ' ')
        *T = NULL;
    else{
       *T = (BiTNode * )malloc(sizeof(BiTNode));    /*创建根结点*/
        (*T)->data = c;                             /*向根结点中输入数据*/
        CreatBiTree(&((*T)->lchild));               /*递归地创建左子树*/
        CreatBiTree(&((*T)->rchild));               /*递归地创建右子树*/
    }
}

/*访问二叉树结点，输出包含D字符结点位于二叉树中的层数*/
void visit(char c,int level){
     if(c == 'D')
        printf("%c is at %dth level of BiTree\n",c,level);
}

/*遍历二叉树*/
void PreOrderTraverse(BiTree T,int level){
    if(T){                                          /*递归结束条件，T为空*/
            visit(T->data,level);                   /*访问根结点*/
            PreOrderTraverse(T->lchild,level+1);    /*先序遍历T的左子树*/
            PreOrderTraverse(T->rchild,level+1);    /*先序遍历T的右子数*/
    }
}

/****************************/

int main(int argc, char* argv[])
{
   int level = 1;
   BiTree T = NULL;             /*最开始T指向空*/
   
   CreatBiTree(&T);             /*创建二叉树*/
   PreOrderTraverse(T, level);   /*遍历二叉树，找到包含D字符结点位于二叉树中的层数*/
    
    return 0;
}