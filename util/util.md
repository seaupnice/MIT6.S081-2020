# Lab1  util

### sleep

sleep实验使用系统调用sleep（sys_sleep实现）。

user space 的 sleep 进程通过 system call，使用内核服务。system call 进入内核，内核执行服务然后返回。

内核提供的一系列 system call 就是 user space 可见的操作系统接口。



### pingpong

通过管道实现进程之间的双向通信。

管道和临时文件的区别：

- 管道会进行自我清扫，shell重定向，最终必须删除临时文件。
- 管道可以传输任意长度的数据
- 管道允许同步。读操作会阻塞调用进程，直到有数据或者绑定在这个管道的写端口已经关闭。



### primes

[Bell Labs and CSP Threads](https://swtch.com/~rsc/thread/)

管道在顺序通信进程之间的单向流水线通信。



### find

文件系统调用`open`，`fstat`。

`fstat` 可以获取一个文件描述符指向的文件的信息，填充一个`stat`的结构体。

```c
#define T_DIR  1
#define T_FILE 2
#define T_DEV  3
// Directory
// File
// Device
struct stat {
	short type;  // Type of file
    int dev;     // File system’s disk device
    uint ino;    // Inode number
    short nlink; // Number of links to file
    uint size;   // Size of file in bytes
};
```

同一个文件通过inode确定，文件名代表的是**连接**。



### xargs

系统调用`exec`的使用。

父进程从 standard input 读取参数，子进程解析参数并执行。

将创建进程和加载程序分为两个过程。`fork` 在子进程需要装入父进程的内存拷贝时分配空间。`exec` 在需压迫额外内存时可以通过 `sbrk` 增加内存。