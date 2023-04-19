#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/inotify.h>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define EVENT_BUF_LEN (1024 * (EVENT_SIZE + 16))

/*
   - INACCESS：文件被访问
- INATTRIB：文件属性被修改
- INCLOSEWRITE：文件被关闭，且写入操作完成
- INCLOSENOWRITE：文件被关闭，但没有写入操作
- INCREATE：文件或目录被创建
- INDELETE：文件或目录被删除
- INDELETESELF：监控的文件或目录本身被删除
- INMODIFY：文件被修改
- INMOVESELF：监控的文件或目录本身被移动或重命名
- INMOVEDFROM：文件或目录被移动或重命名，且事件是移动前的事件
- INMOVEDTO：文件或目录被移动或重命名，且事件是移动后的事件
- INOPEN：文件被打开
   */
int main() {
    int fd = inotify_init();
    if (fd == -1) {
        std::cerr << "inotify_init failed" << std::endl;
        return 1;
    }

    const char* path_to_watch = "/home/zeekr/pro/";
    int wd = inotify_add_watch(fd, path_to_watch, IN_ALL_EVENTS);
    if (wd == -1) {
        std::cerr << "inotify_add_watch failed" << std::endl;
        return 1;
    }

    std::cout << "watching path: " << path_to_watch << std::endl;

    char event_buffer[EVENT_BUF_LEN];
    while (true) {
        int length = read(fd, event_buffer, EVENT_BUF_LEN);
        if (length < 0) {
            std::cerr << "read failed" << std::endl;
            break;
        }

        int i = 0;
        while (i < length) {
            struct inotify_event* event = (struct inotify_event*) &event_buffer[i];
            i += EVENT_SIZE + event->len;
            // if (!event->len) {
            //     std::cout << "invalid event->len: " << event->len << std::endl;
            //     continue;
            // }

            if (event->mask & IN_CREATE) {
                printf("File %s was created.\n", event->name);
            } else if (event->mask & IN_DELETE) {
                printf("File %s was deleted.\n", event->name);
            } else if (event->mask & IN_MODIFY) {
                printf("File %s was modified.\n", event->name);
            }
        }
    }

    inotify_rm_watch(fd, wd);
    close(fd);
    return 0;
}
