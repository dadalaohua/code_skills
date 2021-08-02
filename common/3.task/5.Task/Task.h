//Task.h

#ifndef __TASK__
#define __TASK__

#include <stdio.h>

/************************************************************************/
/*                                                                      */
/************************************************************************/

typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned int        u32;
typedef unsigned long long  u64;
typedef signed char         s8;
typedef short               s16;
typedef int                 s32;

typedef u8  uint8_t;
typedef u16 uint16_t;
typedef u32 uint32_t;
typedef u64 uint64_t;
typedef s8  int8_t;
typedef s16 int16_t;
typedef s32 int32_t;

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define SCH_NULL_PTR    NULL
#define SCH_MAX_TASKS   15

/************************************************************************/
/*                                                                      */
/************************************************************************/

// ------ Public data type declarations ----------------------------

// User-defined type to store required data for each task
typedef struct
{
   // Pointer to the task
   // (must be a 'uint32_t (void)' function)
   uint32_t (*pTask)(void);
   //  void (*pTask) (void);

   // Delay (ticks) until the task will (next) be run
   uint32_t Delay;

   // Interval (ticks) between subsequent runs.
   uint32_t Period;
} sTask_t;

/************************************************************************/
/*                                                                      */
/************************************************************************/
extern void SCH_Add_Task(uint32_t (*pTask)(), const uint32_t DELAY, const uint32_t PERIOD);
extern void SCH_Delete_Task(uint32_t (*pTask)());
extern void SCH_Change_Task(uint32_t (*pTask)(), const uint32_t DELAY, const uint32_t PERIOD);
extern void SCH_Dispatch_Tasks(void);
extern void SCH_Timer_User(void);

#endif
