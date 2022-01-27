#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define FLAG_LIST(_) \
_(Start) \
_(Play) \
_(Stop) \
_(Next) \
_(Prev) \
_(Pause)


#define DEFINE_FLAG(flag) flag,
enum Flag {
    None = 0,
    FLAG_LIST(DEFINE_FLAG)
    Total
};
#undef DEFINE_FLAG
/*
预处理后的效果
enum Flag {
    None = 0,
    Start, Play, Stop, Next, Prev, Pause,
    Total
};
*/

#define MUSIC_FLAG(flag) Music##flag,
enum MusicFlag {
    MusicNone = 0,
    FLAG_LIST(MUSIC_FLAG)
    MusicTotal
};
#undef MUSIC_FLAG
/*
预处理后的效果
enum MusicFlag {
    MusicNone = 0,
    MusicStart, MusicPlay, MusicStop, MusicNext, MusicPrev, MusicPause,
    MusicTotal
};
*/
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    printf("%d\n", Start);
    printf("%d\n", Play);
    printf("%d\n", Stop);
    printf("%d\n", Next);
    printf("%d\n", Prev);
    printf("%d\n", Pause);
    
    printf("\n");
    
    printf("%d\n", MusicStart);
    printf("%d\n", MusicPlay);
    printf("%d\n", MusicStop);
    printf("%d\n", MusicNext);
    printf("%d\n", MusicPrev);
    printf("%d\n", MusicPause);
    
    return 0;
}