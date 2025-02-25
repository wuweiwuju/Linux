程序是先加载到内存上，因为是冯诺依曼体系是这样规定的，
要在CPU上运行只能是内存上拿东西，因此程序就是先加载在内存上

进程控制：进程创建/进程终止/进程等待/程序替换
	进程创建：
		pid_fork(void)--通过复制父进程，创建子进程
	返回值：<0  >0  -1
	创建子进程的流程：写时拷贝
		pid_vfork(void);
		创建一个子进程，但是vfork创建子进程之后父进程会阻塞，直到子进程退出或者程序替换
		创建的子进程与父进程共用同一个虚拟地址空间-为了防止调用栈混乱，因此阻塞父进程
		fork和vfork两个接口创建子进程，都是在内核中通过调用clone函数实现的
		在clone函数重实现task_stack的创建，以及根据参数不同，创建拷贝不同的数据（例如vfork就不需要为子进程创建虚拟地址空间/页表）
	进程终止：
			进程的终止场景：
				异常退出
				正常退出，结果符合预期
				正常退出，结果不符合预期
			获取一个系统调用的错误信息：void perror(char *msg) char *strerror(int errno)
			如何终止一个进程：
				1.在main函数中return
				2.在任意地方调用exit（int statu）接口--库函数接口---退出前都会刷新缓冲区
				3.在任意地方调用_exit(int statu)接口--系统调用接口---退出时直接释放所有资源
	进程等待：等待子进程的退出，获取这个子进程的返回值，并且回收子进程的所有资源，避免产生僵尸进程
			如何等待：
				int wait(int *statu)---阻塞接口-等待一个子进程退出，若没有子进程退出，则一直等待
										子进程的返回值会放到传入的参数status中
				阻塞：为了完成一个功能，发起调用，若当前不具备完成条件，则一直等待！！直到完成后返回
				非阻塞：为了完成一个功能，发起调用，若当前不具备完成条件，则立即报错返回
				pid_t waitpid(pid_t pid,int *status,int options)
					1.可以等待指定的子进程退出
					2.options若被指定为WNOHANG,则将waitpid设置为非阻塞
					3.pid: -1 表示等待任意一个子进程； >0: 表示等待指定pid的子进程
					返回值：>0: 返回的是退出子进程的pid； =0：没有子进程退出；<0:等待出错
	程序替换：替换一个进程正在运行的程序
			进程替换运行的程序后，会初始化虚拟地址空间中的代码段和数据段，并且更新页表信息

			如何进行程序替换：exec函数族




//只有main函数退出才代表进程退出   echo $? 查看最近退出的退货码


minishell:
		非常简单的shell：能够接受用户的数据，并且针对这些输入完成相应的功能

			shell
				1.一直等待标准输入
				2.对输入进行解析 得到程序名称及运行参数
				3.创建子进程
				4.将子进程替换程序指定命令对应的程序
				5.父进程等待子进程退出

