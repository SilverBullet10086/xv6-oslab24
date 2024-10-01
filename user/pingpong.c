#include "kernel/types.h"
#include "user/user.h"

int main(void) {
    int p1[2], p2[2]; // 两个管道
    pipe(p1); // 父进程到子进程
    pipe(p2); // 子进程到父进程

    int pid = getpid(); // 获取父进程的 PID
    int child_pid = fork();

    if (child_pid > 0) {  // 父进程
        close(p1[0]); // 关闭读端
        close(p2[1]); // 关闭写端

        // 向子进程发送父进程的 PID
        write(p1[1], (char*)&pid, sizeof(pid)); 
        // 向子进程发送 "ping"
        write(p1[1], "ping", 4);
        close(p1[1]); // 关闭写端

        char buf[5];
        read(p2[0], buf, 4); // 从子进程读取 "pong"
        buf[4] = '\0';

        printf("%d: received pong from pid %d\n", getpid(), child_pid); // 输出父进程和子进程的 PID
        close(p2[0]); // 关闭读端
        wait(0);
    } else if (child_pid == 0) {  // 子进程
        close(p1[1]); // 关闭写端
        close(p2[0]); // 关闭读端

        char buf[5];
        int parent_pid;

        // 从父进程读取 PID
        read(p1[0], (char*)&parent_pid, sizeof(parent_pid));
        read(p1[0], buf, 4); // 从父进程读取 "ping"
        buf[4] = '\0';

        // 打印子进程收到 ping 的信息
        printf("%d: received ping from pid %d\n", getpid(), parent_pid); 
        
        // 向父进程发送 "pong"
        write(p2[1], "pong", 4);
        close(p2[1]); // 关闭写端
        close(p1[0]); // 关闭读端
    } else {
        printf("fork error\n");
    }
    exit(0);
}

