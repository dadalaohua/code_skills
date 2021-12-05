
#include "progress.h"
#include <assert.h>

void
on_progress_start (progress_data_t *data);

void
on_progress (progress_data_t *data);

void
on_progress_end (progress_data_t *data);

int
main (void) {
  // init with 
  //初始化 总数100，进度条长度60
  progress_t *progress = progress_new(100, 60);
  //进度条格式
  //:bar - 表示进度条
  //:percent - 表示当前进度百分比
  //:elapsed - 表示当前运行的时间(以秒为单位)为浮点
  progress->fmt = "    progress (:percent) => {:bar} [:elapsed]";
  //表示用于绘制进度条未完成部分的字符
  progress->bg_bar_char = " ";
  //表示用于绘制进度条完成部分的字符
  progress->bar_char = ".";

  // set events
  //PROGRESS_EVENT_START - 表示进程开始时的事件类型
  //PROGRESS_EVENT_PROGRESS - 表示进度滴答时的事件类型
  //PROGRESS_EVENT_END - 表示进度完成时的事件类型
  progress_on(progress, PROGRESS_EVENT_START, on_progress_start);
  progress_on(progress, PROGRESS_EVENT_PROGRESS, on_progress);
  progress_on(progress, PROGRESS_EVENT_END, on_progress_end);

  // tick progress
  //传递滴答值，当滴答值累计到总数时，绑定到PROGRESS_EVENT_END的函数指针会被调用
  progress_tick(progress, 10);
  
  sleep(1);
  progress_tick(progress, 30);
  progress_tick(progress, 5);
  progress_tick(progress, 10);
  progress_tick(progress, 20);
  sleep(1);
  progress_tick(progress, 10);
  progress_tick(progress, 5);
  progress_tick(progress, 10);

  // inspect
  //检查进度
  progress_inspect(progress);

  //释放
  progress_free(progress);


  progress = progress_new(100, 60);
  progress->fmt = "    progress (:percent) => {:bar} [:elapsed]";
  progress->bg_bar_char = " ";
  progress->bar_char = ".";

  // set events
  progress_on(progress, PROGRESS_EVENT_START, on_progress_start);
  progress_on(progress, PROGRESS_EVENT_PROGRESS, on_progress);
  progress_on(progress, PROGRESS_EVENT_END, on_progress_end);

  // tick progress
  //将进度条设置为可以调用的特定值，当到达总数时，绑定到PROGRESS_EVENT_END的函数指针会被调用
  progress_value(progress, 2);
  sleep(1);
  progress_value(progress, 5);
  progress_value(progress, 10);
  sleep(1);
  progress_value(progress, 15);
  progress_value(progress, 20);
  sleep(1);
  progress_value(progress, 30);
  sleep(1);
  progress_value(progress, 40);
  sleep(1);
  progress_value(progress, 100);

  // inspect
  progress_inspect(progress);

  progress_free(progress);


  progress = progress_new(100, 60);
  progress->fmt = "    progress (:percent) => {:bar} [:elapsed]";
  progress->bg_bar_char = " ";
  progress->bar_char = ".";

  // set events
  progress_on(progress, PROGRESS_EVENT_START, on_progress_start);
  progress_on(progress, PROGRESS_EVENT_PROGRESS, on_progress);
  progress_on(progress, PROGRESS_EVENT_END, on_progress_end);

  for (long i = 0; i < 10000; ++i) {
     progress_value(progress, i / 100); 
  }

  progress_free(progress);
}

void
on_progress_start (progress_data_t *data) {
  assert(data);
  puts("\nprogress start");
  progress_write(data->holder);
}

void
on_progress (progress_data_t *data) {
  progress_write(data->holder);
}

void
on_progress_end (progress_data_t *data) {
  puts("\nprogress end");
}

