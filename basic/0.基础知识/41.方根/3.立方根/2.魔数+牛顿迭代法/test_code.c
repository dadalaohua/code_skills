#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/************************************************************************/
float MagicCubeRoot(float x)
{
    if (x < 0)
    {
        x = -x;
        
        float xthird = 0.333f * x;
        int i = *(int*)&x;
        i = (0x2a517d47 + (0.333f * i));//i = (int) (0x2a517d3c + (0.333f * i));
        x = *(float*)&i;
        x = 0.667f * x + xthird / (x * x);
        //x = 0.667f * x + xthird / (x * x);
        
        x = -x;
    }
    else
    {
        float xthird = 0.333f * x;
        int i = *(int*)&x;
        i = (0x2a517d47 + (0.333f * i));//i = (int) (0x2a517d3c + (0.333f * i));
        x = *(float*)&i;
        x = 0.667f * x + xthird / (x * x);
        //x = 0.667f * x + xthird / (x * x);
    }
    
    return x;
}

int main(int argc, char* argv[])
{
    float i;
    
    for(i = -20; i < 20; i++)
    {
        printf("%f: %f\n", i, MagicCubeRoot(i));
        printf("%f: %f\n", i, pow(i, 1/3.0));
    }
    
    return 0;
}