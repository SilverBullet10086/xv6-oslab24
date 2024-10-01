#include "kernel/types.h"
#include "user/user.h"

int main(void) {
    int p1[2], p2[2]; // �����ܵ�
    pipe(p1); // �����̵��ӽ���
    pipe(p2); // �ӽ��̵�������

    int pid = getpid(); // ��ȡ�����̵� PID
    int child_pid = fork();

    if (child_pid > 0) {  // ������
        close(p1[0]); // �رն���
        close(p2[1]); // �ر�д��

        // ���ӽ��̷��͸����̵� PID
        write(p1[1], (char*)&pid, sizeof(pid)); 
        // ���ӽ��̷��� "ping"
        write(p1[1], "ping", 4);
        close(p1[1]); // �ر�д��

        char buf[5];
        read(p2[0], buf, 4); // ���ӽ��̶�ȡ "pong"
        buf[4] = '\0';

        printf("%d: received pong from pid %d\n", getpid(), child_pid); // ��������̺��ӽ��̵� PID
        close(p2[0]); // �رն���
        wait(0);
    } else if (child_pid == 0) {  // �ӽ���
        close(p1[1]); // �ر�д��
        close(p2[0]); // �رն���

        char buf[5];
        int parent_pid;

        // �Ӹ����̶�ȡ PID
        read(p1[0], (char*)&parent_pid, sizeof(parent_pid));
        read(p1[0], buf, 4); // �Ӹ����̶�ȡ "ping"
        buf[4] = '\0';

        // ��ӡ�ӽ����յ� ping ����Ϣ
        printf("%d: received ping from pid %d\n", getpid(), parent_pid); 
        
        // �򸸽��̷��� "pong"
        write(p2[1], "pong", 4);
        close(p2[1]); // �ر�д��
        close(p1[0]); // �رն���
    } else {
        printf("fork error\n");
    }
    exit(0);
}

