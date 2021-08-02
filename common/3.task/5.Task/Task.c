//Task.c

#include "Task.h"

/************************************************************************/
/*                                                                      */
/************************************************************************/

sTask_t SCH_tasks_g[SCH_MAX_TASKS];
uint32_t Current_Task_id = 0;
uint32_t Tick_count_g = 0;
/************************************************************************/
/*                                                                      */
/************************************************************************/
//关中断
void SCH_Disable_Irq(void)
{
    //__disable_irq();
}

//开中断
void SCH_Enable_Irq(void)
{
    //__enable_irq();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

//添加（创建）任务

// Add_Task
void SCH_Add_Task(uint32_t (*pTask)(),
                  const uint32_t DELAY,
                  const uint32_t PERIOD)
{
   uint32_t Task_id = 0;

   // Check pre-conditions (START)
   // First find a gap in the array (if there is one)
   while ((SCH_tasks_g[Task_id].pTask != SCH_NULL_PTR) && (Task_id < SCH_MAX_TASKS))
   {
      Task_id++;
   }

   // Have we reached the end of the list?
   if ((Task_id < SCH_MAX_TASKS) || (PERIOD > 0))
   {
      // If we're here, there is a space in the task array
      // and the task to be added is periodic
      SCH_tasks_g[Task_id].pTask = pTask;
      SCH_tasks_g[Task_id].Delay = DELAY + 1;
      SCH_tasks_g[Task_id].Period = PERIOD;
   }
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

//删除任务

void SCH_Delete_Task(uint32_t (*pTask)())
{

   uint32_t id_counter;
   for (id_counter = 0; id_counter < SCH_MAX_TASKS;)
   {
      if (SCH_tasks_g[id_counter].pTask != pTask)
         id_counter++;

      else
      {
         SCH_Disable_Irq();

         SCH_tasks_g[id_counter].pTask = SCH_NULL_PTR;

         SCH_Enable_Irq();
         id_counter = SCH_MAX_TASKS + 1;
      }
   }
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

//更改任务

//任务运行过程中切换为其他任务运行。
//则当前任务返回后不再运行。
//为了安全应该关中断操作。
// 可以在task中增加一个参数，task运行到一定次数切换到其他的task;
//或者 事件触发 退出当前task,执行新的task
void SCH_Change_Task(uint32_t (*pTask)(),
                     const uint32_t DELAY,
                     const uint32_t PERIOD)
{

   SCH_Disable_Irq();

   if ((Current_Task_id < SCH_MAX_TASKS) || (PERIOD > 0))
   {
      SCH_tasks_g[Current_Task_id].pTask = pTask;
      SCH_tasks_g[Current_Task_id].Delay = DELAY + 1;
      SCH_tasks_g[Current_Task_id].Period = PERIOD;
   }
   SCH_Enable_Irq();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

//执行调度器

/*----------------------------------------------------------------------------*-

  SCH_Dispatch_Tasks()
-*----------------------------------------------------------------------------*/
void SCH_Dispatch_Tasks(void)
{
   //uint32_t Status;
   uint32_t Task_id;

   // Go through the task array
   for (Task_id = 0; Task_id < SCH_MAX_TASKS; Task_id++)
   {

      // Check if there is a task at this location
      if (SCH_tasks_g[Task_id].pTask != SCH_NULL_PTR)
      {
         if (SCH_tasks_g[Task_id].Delay == 0)
         {
            //   printf("\n task=%d \n",Task_id);
            Current_Task_id = Task_id;
            (*SCH_tasks_g[Task_id].pTask)();//Status = (*SCH_tasks_g[Task_id].pTask)(); // Run the task
            // All tasks are periodic: schedule task to run again
            SCH_tasks_g[Task_id].Delay = SCH_tasks_g[Task_id].Period;
         }
      }
   }

   // Update inverted copy of Tick_count_g
   //   Tick_count_ig = ~Tick_count_g;

   // The scheduler enters idle mode at this point
   // __WFI();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/

//定时器查询时间片

void SCH_Timer_User(void)
{
   uint32_t Task_id;
   ++Tick_count_g;
   for (Task_id = 0; Task_id < SCH_MAX_TASKS; Task_id++)
   {
      if (SCH_tasks_g[Task_id].Delay > 0)
         SCH_tasks_g[Task_id].Delay--;
   }
}
