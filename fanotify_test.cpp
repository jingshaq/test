#include <iostream>
#include <sys/fanotify.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include <libgen.h>
#include <cassert>
#include <climits>
#include <string>
#include <sys/stat.h>
#include <thread>

#define BUF_SIZE 1024
#define EVENT_BUF_SIZE (1024 * (sizeof(struct fanotify_event_metadata) + 256))

// 單獨的事件標誌
const int singleEvents[] = {
    FAN_CREATE,
    FAN_DELETE,
    FAN_MOVE_SELF,
    FAN_MOVED_FROM,
    FAN_MOVED_TO,
    FAN_ATTRIB
};
const int SINGLE_EVENT_COUNT = sizeof(singleEvents) / sizeof(singleEvents[0]);

std::string getPathFromFd(int fd) 
{ 
    char path[PATH_MAX]; 
    char procfd_path[PATH_MAX]; 
    snprintf(procfd_path, sizeof(procfd_path), "/proc/self/fd/%d", fd); 
    ssize_t len = readlink(procfd_path, path, sizeof(path) - 1); 
    if (len >= 0) { 
        path[len] = '\0'; // 确保字符串以空字符结尾 
        return std::string(path); 
    } 
    return "Unknown"; // 读取失败时的处理 
} 

void getNameByPid(pid_t pid, char *task_name) {
    char proc_pid_path[BUF_SIZE];
    char buf[BUF_SIZE];

    sprintf(proc_pid_path, "/proc/%d/status", pid);
    FILE *fp = fopen(proc_pid_path, "r");

    if (fp == NULL) {
        perror("fopen");
        *task_name = '\0';
        return;
    }

    if (fgets(buf, BUF_SIZE - 1, fp) == NULL) {
        perror("fgets");
        fclose(fp);
        *task_name = '\0';
        return;
    }

    fclose(fp);
    if (sscanf(buf, "%*s %s", task_name) != 1) {
        perror("sscanf");
        *task_name = '\0';
    }
}


std::string maskToString(unsigned long long mask) 
{ 
    if ((mask & FAN_ACCESS) != 0U) { 
        return "FAN_ACCESS: "; 
    } 
    if ((mask & FAN_MODIFY) != 0U) { 
        return "FAN_MODIFY: "; 
    } 
    if ((mask & FAN_ATTRIB) != 0U) { 
        return "FAN_ATTRIB: "; 
    } 
    if ((mask & FAN_CLOSE_WRITE) != 0U) { 
        return "FAN_CLOSE_WRITE: "; 
    } 
    if ((mask & FAN_CLOSE_NOWRITE) != 0U) { 
        return "FAN_CLOSE_NOWRITE: "; 
    } 
    if ((mask & FAN_OPEN) != 0U) { 
        return "FAN_OPEN: "; 
    } 
    if ((mask & FAN_MOVED_FROM) != 0U) { 
        return "FAN_MOVED_FROM: "; 
    } 
    if ((mask & FAN_MOVED_TO) != 0U) { 
        return "FAN_MOVED_TO: "; 
    } 
    if ((mask & FAN_CREATE) != 0U) { 
        return "FAN_CREATE: "; 
    } 
    if ((mask & FAN_DELETE) != 0U) { 
        return "FAN_DELETE: "; 
    } 
    if ((mask & FAN_DELETE_SELF) != 0U) { 
        return "FAN_DELETE_SELF: "; 
    } 
    if ((mask & FAN_MOVE_SELF) != 0U) { 
        return "FAN_MOVE_SELF: "; 
    } 
    if ((mask & FAN_OPEN_EXEC) != 0U) { 
        return "FAN_OPEN_EXEC: "; 
    } 
    if ((mask & FAN_Q_OVERFLOW) != 0U) { 
        return "FAN_Q_OVERFLOW: "; 
    } 
    // if ((mask & FAN_FS_ERROR) != 0U) { 
    //     return "FAN_FS_ERROR: "; 
    // } 
    if ((mask & FAN_OPEN_PERM) != 0U) { 
        return "FAN_OPEN_PERM: "; 
    } 
    if ((mask & FAN_ACCESS_PERM) != 0U) { 
        return "FAN_ACCESS_PERM: "; 
    } 
    if ((mask & FAN_OPEN_EXEC_PERM) != 0U) { 
        return "FAN_OPEN_EXEC_PERM: "; 
    } 
    if ((mask & FAN_EVENT_ON_CHILD) != 0U) { 
        return "FAN_EVENT_ON_CHILD: "; 
    } 
    // if ((mask & FAN_RENAME) != 0U) { 
    //     return "FAN_RENAME: "; 
    // } 
    if ((mask & FAN_ONDIR) != 0U) { 
        return "FAN_ONDIR: "; 
    } 
    if ((mask & FAN_CLOSE) != 0U) { 
        return "FAN_CLOSE: "; 
    } 
    if ((mask & FAN_MOVE) != 0U) { 
        return "FAN_MOVE: "; 
    } 
    return "Unknown mask " + std::to_string(mask) + ": "; 
}

int main() {
    // 创建fanotify实例，尝试使用 FAN_CLASS_CONTENT
    // int fan_fd = fanotify_init(FAN_CLASS_NOTIF|FAN_REPORT_FID, O_RDONLY | O_LARGEFILE);
    // int fan_fd = fanotify_init(FAN_CLASS_CONTENT , O_RDONLY | O_LARGEFILE /*| O_NONBLOCK)*/    );

    unsigned int flags = FAN_CLASS_NOTIF | FAN_CLOEXEC | FAN_UNLIMITED_QUEUE
    | FAN_UNLIMITED_MARKS | FAN_ENABLE_AUDIT | FAN_REPORT_FID //;
    | FAN_REPORT_DFID_NAME;
    unsigned int event_f_flags = O_RDONLY | O_LARGEFILE | O_CLOEXEC;
    int fan_fd = fanotify_init(flags, event_f_flags);
    if (fan_fd == -1) {
        perror("fanotify_init");
        return 1;
    }

    // 获取当前工作目录的绝对路径
    // char* cwd = getcwd(NULL, 0);
    // if (cwd == NULL) {
    //     perror("getcwd");
    //     close(fan_fd);
    //     return 1;
    // }
    const char * cwd="/home/";
    //const char * cwd="/";
    char commname[BUF_SIZE];
    unsigned int add_flags = FAN_MARK_ADD | FAN_MARK_FILESYSTEM;
    unsigned int add_mask = FAN_ACCESS | FAN_MODIFY | FAN_ATTRIB | FAN_CLOSE_WRITE | FAN_MOVED_FROM
                        | FAN_MOVED_TO | FAN_CREATE | FAN_DELETE | FAN_DELETE_SELF
                        | FAN_MOVE_SELF | FAN_OPEN_EXEC | FAN_EVENT_ON_CHILD | DN_RENAME//FAN_RENAME
                        | FAN_ONDIR | FAN_MOVE;
    if (fanotify_mark(fan_fd, add_flags, add_mask, AT_FDCWD, cwd) == -1) {
        perror("fanotify_mark");
        return -1;
    }


    // free(cwd);
    

    std::cout << "开始监听当前目录的文件系统事件..." << std::endl;

    char buf[EVENT_BUF_SIZE];
    while (true) {
         ssize_t len = read(fan_fd, buf, EVENT_BUF_SIZE);
         if (len == -1 && errno != EAGAIN) {
             perror("read");
             break;
         }
 
         if (len <= 0) continue;
 
         struct fanotify_event_metadata *metadata = (struct fanotify_event_metadata *)buf;
         while (FAN_EVENT_OK(metadata, len)) {
             if (metadata->pid == getpid()) {
                 metadata = FAN_EVENT_NEXT(metadata, len);
                 continue;
             }
             if (metadata->mask & FAN_Q_OVERFLOW) {
                 std::cout << "事件队列溢出！" << std::endl;
             } else {
                    
                //  if (metadata->vers >= 4 && metadata->fd >= 0) {
                    bzero(commname, BUF_SIZE);
                    getNameByPid(metadata->pid, commname);
                    printf("%s(%d)\t", commname, metadata->pid);
                     const struct fanotify_event_info_fid *fid = (const struct fanotify_event_info_fid *)(metadata + 1);
                     // 这里可以添加使用 fid 读取事件的逻辑
                     std::cout << "检测到文件系统事件（使用 fid 读取）: " << maskToString(metadata->mask) << std::endl;

                     auto *file_handle = (struct file_handle *) fid->handle;
                     int mount_fd = AT_FDCWD; // 假设使用当前工作目录的挂载点
                     int event_fd = open_by_handle_at(mount_fd, file_handle, O_RDONLY);
                     if (event_fd >= 0) {
                         std::string path = getPathFromFd(event_fd);
                         std::cout << "文件路径: " << path << std::endl;
                         close(event_fd);
                     } else {
                         perror("open_by_handle_at");
                     }
                     std::string filename;
                     if (fid->hdr.info_type == FAN_EVENT_INFO_TYPE_DFID_NAME) {
                         auto *file_name = file_handle->f_handle + file_handle->handle_bytes;
                         filename = std::string(file_name,
                                                file_name
                                                    + strlen(reinterpret_cast<const char *>(file_name)));
                     } else {
                         std::cerr << "Received unexpected event info type: "
                                   << std::to_string(fid->hdr.info_type) << std::endl;
                     }
                     printf("filename: %s\n", filename.c_str());
                     

                //  } else {
                //      std::cout << "检测到文件系统事件: " << maskToString(metadata->mask) << std::endl;
                //  }
             }
             metadata = FAN_EVENT_NEXT(metadata, len);
         }
    }

    close(fan_fd);
    return 0;
}

/*
void monitor() 
{ 
    constexpr int BUF_SIZE = 1024 * (sizeof(struct fanotify_event_metadata) + 256);
    char buf[BUF_SIZE]; 
    auto len = read(fanotifyFd, buf, sizeof(buf)); 
    if (!isRunning.load()) { 
        return; 
    } 
    if (len <= 0) { 
        std::cerr << "read failed" << std::endl; 
        return; 
    } 

    fanotify_event_metadata *event = nullptr; 
    for (event = reinterpret_cast<struct fanotify_event_metadata *>(buf); 
         FAN_EVENT_OK(event, len); 
         event = FAN_EVENT_NEXT(event, len)) { 
        if (!isRunning.load()) { 
            return; // 全局监控，会产生大量事件，需要及时处理退出事件 
        } 

        if (event->mask & FAN_Q_OVERFLOW) { 
            std::cerr << "事件队列溢出！" << std::endl; 
            continue; 
        } 

        const auto *fid = reinterpret_cast<const struct fanotify_event_info_fid *>(event + 1); 
        auto *file_handle = (struct file_handle *) fid->handle; 

        std::string path; 
        int event_fd = open_by_handle_at(mountFd, file_handle, O_RDONLY); 
        if (event_fd >= 0) { 
            path = getPathFromFd(event_fd); 
            close(event_fd); 
            if (path.find(dir.string()) == std::string::npos) { 
                continue; // 全局监控，不在目标目录下的文件不处理 
            } 
        } else { 
            if (errno == ESTALE) { 
                std::cerr << "File handle is no longer valid. File has been deleted" << std::endl; 
                continue; 
            } 
            perror("open_by_handle_at"); 
        } 

        std::string filename; 
        if (fid->hdr.info_type == FAN_EVENT_INFO_TYPE_DFID_NAME) { 
            auto *file_name = file_handle->f_handle + file_handle->handle_bytes; 
            filename = std::string(file_name, 
                                   file_name + strlen(reinterpret_cast<const char *>(file_name))); 
        } else { 
            std::cerr << "Received unexpected event info type: " 
                      << std::to_string(fid->hdr.info_type) << std::endl; 
        } 

        auto fileEvent = maskToString(event->mask) + path; 
        if (!filename.empty()) { 
            fileEvent += "/" + filename; 
        } 
        std::cout << fileEvent << std::endl; 
    } 
}
*/

/*
CC = g++
CFLAGS = -Wall -static
TARGET = fanotify_test
SRCS = fanotify_test.cpp
OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
*/
