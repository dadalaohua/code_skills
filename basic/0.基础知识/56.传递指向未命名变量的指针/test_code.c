#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
// A func that expects a pointer to three int values.
void func(const int *arg)
{
    printf("%d %d %d\n", *arg, *(arg + 1), *(arg + 2));
}

typedef struct{
    int a;
    char b;
    long c;
} struct_type;

void func2(struct_type *arg)
{
    printf("%d %d %ld\n", arg->a, arg->b, arg->c);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    // Instead of using a local variable.
    //代替使用局部变量。
    int tmp[] = {10, 20, 30};
    func(tmp);

    // We can write.
    //我们可以这么写，传递指向未命名变量的指针
    func( (const int[]){10, 20, 30} );

    // Can be useful with a helper macro.
    //可以使用辅助宏。
    #define VEC(...) ((const int[]){__VA_ARGS__})
    func(VEC(10, 20, 30));

    // (Also works with struct or any other type).
    //也可用于结构体或任何其他类型
    
    struct_type struct_data = {50, 20, 10};
    func2(&struct_data);
    
    func2( (struct_type *)(int[]){50, 20, 10} );
    
    func2( (struct_type *)VEC(50, 20, 10) );
    
    return 0;
}