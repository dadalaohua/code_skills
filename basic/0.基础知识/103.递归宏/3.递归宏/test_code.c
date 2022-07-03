// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <unistd.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define DEC_1 0
#define DEC_2 1
#define DEC_3 2

#define DEC( n ) DEC_##n

#define CHR( x, y ) CHR1( x, y )
#define CHR1( x, y ) x##y

#define FAC_1( n ) 1
#define FAC_2( n ) n * CHR( FAC_, DEC( n ) )( DEC( n ) )
#define FAC_3( n ) n * CHR( FAC_, DEC( n ) )( DEC( n ) )

/************************************************************************/

#define PARAM( n ) typename P##n
#define PARAM_END typename P

#define ARG( n ) P##n
#define ARG_END P

#define PARAM_1( n ) CHR( typename P, n )
#define PARAM_2( n ) CHR( CHR( PARAM_, DEC( n ) )( DEC( n ) ), TYPE( n ) )
#define PARAM_3( n ) CHR( CHR( PARAM_, DEC( n ) )( DEC( n ) ), TYPE( n ) )

#define REPEAT_1( n, f, e ) CHR( e, n )
#define REPEAT_2( n, f, e ) CHR( REPEAT_, DEC( n ) )( DEC( n ), f, e ), f( n )
#define REPEAT_3( n, f, e ) CHR( REPEAT_, DEC( n ) )( DEC( n ), f, e ), f( n )

#define DEF_PARAM( n ) REPEAT_##n( n, PARAM, PARAM_END )
#define DEF_ARG( n ) REPEAT_##n( n, ARG, ARG_END )

/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    template <typename R, DEF_PARAM( 2 )>
    class functor<R( DEF_ARG( 2 ) )>;
    
    //宏替换成如下
    // template <typename R, typename P1, typename P2>
    // class functor<R(P1,P2)>;
    
    DEF_PARAM( 3 )
    DEF_ARG( 3 )
    
    //宏替换成如下
    // typename P1, typename P2, typename P3
    // P1, P2, P3
    
    FAC_3(3)
    
    //宏替换成如下
    // 3 * 2 * 1
    
    return 0;
}