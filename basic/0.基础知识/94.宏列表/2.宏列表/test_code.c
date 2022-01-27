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
    FLAG_LIST(DEFINE_FLAG)
};
#undef DEFINE_FLAG
/*
预处理后的效果
enum Flag {
    Start, Play, Stop, Next, Prev, Pause,
};
*/

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

#define FLAG_ACCESSOR(flag) \
_Bool get##flag() {\
    return getFlag(1 << flag);\
}\
void set##flag() {\
    setFlag(1 << flag);\
}\
void reset##flag() {\
    resetFlag(1 << flag);\
}
FLAG_LIST(FLAG_ACCESSOR)
#undef FLAG_ACCESSOR

/*
预处理后的效果
_Bool getStart() { return getFlag(1 << Start);}
void setStart() { setFlag(1 << Start);}
void resetStart() { resetFlag(1 << Start);} 
_Bool getPlay() { return getFlag(1 << Play);}
void setPlay() { setFlag(1 << Play);}
void resetPlay() { resetFlag(1 << Play);} 
_Bool getStop() { return getFlag(1 << Stop);}
void setStop() { setFlag(1 << Stop);}
void resetStop() { resetFlag(1 << Stop);} 
_Bool getNext() { return getFlag(1 << Next);}
void setNext() { setFlag(1 << Next);}
void resetNext() { resetFlag(1 << Next);} 
_Bool getPrev() { return getFlag(1 << Prev);}
void setPrev() { setFlag(1 << Prev);}
void resetPrev() { resetFlag(1 << Prev);} 
_Bool getPause() { return getFlag(1 << Pause);}
void setPause() { setFlag(1 << Pause);}
void resetPause() { resetFlag(1 << Pause);}
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
    
    printf("getStart %d\n", getStart());
    setStart();
    printf("getStart %d\n", getStart());
    resetStart();
    printf("getStart %d\n", getStart());
    
    printf("\n");
    
    printf("getPlay %d\n", getPlay());
    setPlay();
    printf("getPlay %d\n", getPlay());
    resetPlay();
    printf("getPlay %d\n", getPlay());
    
    printf("\n");
    
    printf("getStop %d\n", getStop());
    setStop();
    printf("getStop %d\n", getStop());
    resetStop();
    printf("getStop %d\n", getStop());
    
    printf("\n");
    
    printf("getNext %d\n", getNext());
    setNext();
    printf("getNext %d\n", getNext());
    resetNext();
    printf("getNext %d\n", getNext());
    
    printf("\n");
    
    printf("getPrev %d\n", getPrev());
    setPrev();
    printf("getPrev %d\n", getPrev());
    resetPrev();
    printf("getPrev %d\n", getPrev());
    
    printf("\n");
    
    printf("getPause %d\n", getPause());
    setPause();
    printf("getPause %d\n", getPause());
    resetPause();
    printf("getPause %d\n", getPause());
    
    return 0;
}