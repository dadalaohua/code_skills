# 1 "test_code.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 31 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 32 "<command-line>" 2
# 1 "test_code.c"
# 15 "test_code.c"
enum Flag {
    Start, Play, Stop, Next, Prev, Pause,
};


unsigned char MusicFlag = 0x00;

_Bool getFlag(unsigned char flag) {
    return (MusicFlag & flag) ? 1 : 0;
}

void setFlag(unsigned char flag) {
    MusicFlag |= flag;
}

void resetFlag(unsigned char flag) {
    MusicFlag &= ~flag;
}
# 44 "test_code.c"
_Bool getStart() { return getFlag(1 << Start);}void setStart() { setFlag(1 << Start);}void resetStart() { resetFlag(1 << Start);} _Bool getPlay() { return getFlag(1 << Play);}void setPlay() { setFlag(1 << Play);}void resetPlay() { resetFlag(1 << Play);} _Bool getStop() { return getFlag(1 << Stop);}void setStop() { setFlag(1 << Stop);}void resetStop() { resetFlag(1 << Stop);} _Bool getNext() { return getFlag(1 << Next);}void setNext() { setFlag(1 << Next);}void resetNext() { resetFlag(1 << Next);} _Bool getPrev() { return getFlag(1 << Prev);}void setPrev() { setFlag(1 << Prev);}void resetPrev() { resetFlag(1 << Prev);} _Bool getPause() { return getFlag(1 << Pause);}void setPause() { setFlag(1 << Pause);}void resetPause() { resetFlag(1 << Pause);}





int main(int argc, char* argv[])
{

    return 0;
}
