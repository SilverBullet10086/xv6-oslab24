#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  // ������������ȷ���û��ṩ����Ҫ�ȴ���ʱ��
  if (argc != 2) {
    // ����������ԣ������ʾ��Ϣ���˳�
    fprintf(2, "Usage: sleep <ticks>\n");
    exit(1);
  }

  // ���û�������ַ���ת��Ϊ����
  int ticks = atoi(argv[1]);

  // ����sleepϵͳ���õȴ�ָ����ticks
  sleep(ticks);

  // ��������Ϣ
  printf("(nothing happens for a little while)\n");

  // �����˳�
  exit(0);
}

