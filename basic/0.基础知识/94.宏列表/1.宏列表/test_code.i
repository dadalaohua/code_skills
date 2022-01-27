# 1 "test_code.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "test_code.c"
# 14 "test_code.c"
enum Flag {
    None = 0,
    Start, Play, Stop, Next, Prev, Pause,
    Total
};
# 30 "test_code.c"
enum MusicFlag {
    MusicNone = 0,
    MusicStart, MusicPlay, MusicStop, MusicNext, MusicPrev, MusicPause,
    MusicTotal
};
# 48 "test_code.c"
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
