#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  // 检查参数个数，确保用户提供了需要等待的时间
  if (argc != 2) {
    // 如果参数不对，输出提示信息并退出
    fprintf(2, "Usage: sleep <ticks>\n");
    exit(1);
  }

  // 将用户输入的字符串转换为整数
  int ticks = atoi(argv[1]);

  // 调用sleep系统调用等待指定的ticks
  sleep(ticks);

  // 输出完成信息
  printf("(nothing happens for a little while)\n");

  // 正常退出
  exit(0);
}

