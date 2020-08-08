#include <stdio.h>
#include <stdlib.h>

typedef struct ArcNode{
    /*单链表中的结点的类型*/
    int adjvex;                /*该边指向的顶点在顺序表中的位置*/
    struct ArcNode *next;      /*下一条边*/
}ArcNode;

typedef struct VNode{
    /*顶点类型*/
    int data;                  /*顶点中的数据信息*/
    ArcNode *firstarc;         /*指向单链表，即指向第一条边*/
}VNode;

int visited[5] = {0,0,0,0,0};

void CreatGraph(int n , VNode G[] ){
    int i, e;
    ArcNode *p , *q;
    
    printf("Input the information of the vertex\n");
    for(i = 0; i < n; i++){
        scanf("%d", &G[i].data);
        G[i].firstarc = NULL;                        /*初始化第一条边为空*/
    }
    
    for(i = 0; i < n; i++){
        printf("Creat the edges for the %dth vertex\n",i) ;
        scanf("%d", &e);
        while(e != -1){
            p = (ArcNode *)malloc(sizeof(ArcNode));       /*创建一条边*/
            p->next = NULL;
            p->adjvex = e;
            if(G[i].firstarc == NULL) G[i].firstarc = p;  /*i结点的第一条边*/
            else q->next = p;                             /*下一条边*/
            q = p;
            scanf("%d",&e);
        }
    }
}

int FirstAdj(VNode G[],int v){
    if(G[v].firstarc != NULL)
        return (G[v].firstarc)->adjvex;
        
    return -1;
}

int NextAdj(VNode G[],int v){
     ArcNode *p;
     
     p = G[v].firstarc;
     while( p!= NULL){
        if(visited[p->adjvex])
            p = p->next;
        else
            return p->adjvex;
     }
     return -1;
}

void DFS(VNode G[],int v){
    int w;
    
    printf("%d ",G[v].data);    /*访问当前顶点,打印出该顶点中的数据信息*/
    visited[v] = 1;             /*将顶点v对应的访问标记置1*/
    w = FirstAdj(G,v);          /*找到顶点v的第一个邻接点，如果无邻接点，返回-1*/
    while(w != -1){
        if(visited[w] == 0)     /*该顶点未被访问*/
            DFS(G,w);           /*递归地进行深度优先搜索*/
        w = NextAdj(G,v);       /*找到顶点v的下一个邻接点，如果无邻接点，返回-1*/
    }
}

/****************************/

int main(int argc, char* argv[])
{
    VNode G[5];
    
    CreatGraph(5, G);
    
    printf("DFS Travel this undirected graph\n");
    DFS(G, 0);
    
    printf("\n");
    
    return 0;
}