#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

// 检查字符串是否匹配
int match(const char *name, const char *file) {
    return strcmp(name, file) == 0; // 完全匹配
}

// find 函数
void find(char *dir, char *file) {
    char buf[512], *p;
    int fd;
    struct dirent de;
    struct stat st;

    if ((fd = open(dir, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", dir);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", dir);
        close(fd);
        return;
    }

    if (st.type != T_DIR) {
        fprintf(2, "find: %s is not a directory\n", dir);
        close(fd);
        return;
    }

    if (strlen(dir) + 1 + DIRSIZ + 1 > sizeof buf) {
        fprintf(2, "find: directory too long\n");
        close(fd);
        return;
    }

    strcpy(buf, dir);
    p = buf + strlen(buf);
    *p++ = '/';

    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0 || !strcmp(de.name, ".") || !strcmp(de.name, ".."))
            continue;

        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;

        if (stat(buf, &st) < 0) {
            fprintf(2, "find: cannot stat %s\n", buf);
            continue;
        }

        // 输出匹配的文件或目录
        if (match(de.name, file)) {
            printf("%s\n", buf); // 输出相对路径
        }

        if (st.type == T_DIR) {
            find(buf, file); // 递归查找
        }
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(2, "usage: find dirName fileName\n");
        exit(1);
    }

    find(argv[1], argv[2]);
    exit(0);
}

