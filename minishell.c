#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

//建立一个子进程（fork）
//在子进程中获取命令行
//在子进程中解析命令行，并判断是那种重定向替换相应的文件描述符
//替换子进程（execvp）
//父进程等待子进程退出（wait）


int main()
{
  char buf[1024] = {0};
  while(1){
    //打印提示符
    printf("[lpf@MyShell]$");
    fflush(stdout);
    //获取命令行
    fgets(buf,sizeof(buf) - 1,stdin);
    buf[strlen(buf) - 1] = '\0';
    //解析命令
    char *argv[8] = {NULL};
    argv[0] = strtok(buf," ");
    int argc = 0;
    while(argv[argc]){
      argv[++argc] = strtok(NULL," ");
    }
    //创建子进程
    pid_t id = fork();
    if(id < 0){
      perror("fork");
    }else if(id == 0){
      //子进程
      int i = 0;
      for(i = 0;i < argc;++i){
        if(strcmp(argv[i],">") == 0){
          int fd = open(argv[i+1],O_WRONLY|O_CREAT);
          dup2(fd,1);
          argv[i] = NULL;
        }else if(strcmp(argv[i],">>") == 0){
            int fd = open(argv[i+1],O_WRONLY|O_CREAT|O_APPEND);
            dup2(fd,1);
            argv[i] = NULL;
        }else if(strcmp(argv[i],"<") == 0){
          int fd = open(argv[i+1],O_RDONLY,0644);
          dup2(fd,1);
          argv[i] = NULL;
        }
      }
      //子进程程序替换
      execvp(argv[0],argv);
      perror("execvp");
    }else{
      //父进程等待子进程
      wait(NULL);
    }
  }
  return 0;
}
