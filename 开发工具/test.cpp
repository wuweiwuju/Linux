 |  管道符：连接两个命令，将前边命令的输出结果当做后面命令的输入进行处理
	  yum list | grep lrzsz

常用工具：
	软件包管理工具
	写代码相关工具：编辑器/编译器/调试器
	项目管理工具：项目构建工具/项目的版本管理工具

软件包管理工具：yum
	查看软件包：yum list	yum list installed
	安装软件包: yum list
		yum install lrzsz
		yum install gcc
		yum install gcc - c++
		yum install gdb
		yum install git
	移除安装包
		yum remove  package_name

编辑器：vim
	 1.模式：12种，常用有三种：插入模式  普通模式  底行模式
			所有模式都是围绕普通模式切换的
			vim打开一个文件默认就处于普通模式
			模式切换：
				由普通模式切换到插入模式：i/a/I/A  
				由插入模式切换到普通模式：esc
				由普通模式切换到底行模式：:
				由底行模式切换到普通模式：esc
	2.普通模式下常见指令：
		光标移动：hjkl 左下上右 ctrl+f/b 向上或者向下翻页  gg/G 跳转文档第一行/最后一行  w/b  按单词向右向左走
		增删改查：yy/nyy,p 复制一行/复制n行 粘贴  dd/ndd  删除一行/删除n行  x/dw 删除一个字符/删除光标所在单词
		其它操作：u 撤销    ctrl+r 返回来    gg = G 全文对齐

编译器： gcc/g++
	将用户所写的高级语言代码解释成为机器可识别指令
	gcc main.c
	编译过程：
		预处理：展开所有代码	gcc -E
		编译：  语义语法纠错，若没有错误，则将高级语言解释成为汇编语言	gcc -S
		汇编：  将汇编语言解释成为机器指令   gcc -c
		链接：  将所有文件代码以及库文件中的代码集合打包成为可执行程序
		//执行程序的时候，程序需要被加载到内存中，若多个程序使用了相同的库，则内存中就出现了大量的库函数冗余，这是没必要的
		//完全可以相同的库函数代码在内存中只加载一次就够了，不需要多份，大家共享使用
		//因此链接方式有两种：动态链接   静态链接
				静态链接：链接生成可执行程序时，直接将库中的代码拷贝一份到可执行程序中
					1.优点：可以不依赖库文件的存在，库文件被删除依然可以运行
					2.缺点：若库文件被大量的程序使用，则运行时会造成大量的内存中代码冗余
				动态链接：链接生成可执行程序时，并不拷贝代码，只是在可执行程序中记录函数符号信息。等到运行的时候将库加载到内存中，
						  并且多个程序可以共享使用。
					1.优点：节省资源，内存中共用一份
					2.缺点：运行的时候库文件必须存在
				静态链接链接的是静态库，动态链接链接的是动态库。
			gcc链接方式默认是动态链接

调试器： gdb
	gdb调试程序的前提：使用gcc生成debug版的程序（gcc默认生成release版本）
		gcc -g main.c -o main   加-g生成debug版本 
		gdb ./main 加载程序调试
	gdb调试通过命令完成整个程序的调试过程
		逐步调试：
				 start（开始逐步调试） list(查看调试行附近代码) next（下一步：不进入函数）
				 step(下一步：跟踪进入函数)   continue（从当前位置开始直接运行程序）
				 until（直接运行到指定行停下）  until filename:14     list filename:line
				 run（直接运行程序）
		断点调试：
					break main.c:10 指定行数打断点
					break funcname 给函数打断点
					info break  查看断点信息
					delete      删除断点
					print       打印变量内容
					watch： watch variable_name 变量监控
		其它调试：
					backtrace  查看函数调用栈（也就是崩溃位置）

项目构建工具： make/Makefile
				Makefile:是一个普通的文本文件，又有一点不普通，这个文件中记录的是一个项目的所有构建规则  
				make:是一个解释程序，在执行make命令的时候，会到当前目录下寻找Makefile文件，然后，对Makefile中记录的
					 构建规则进行逐行解释执行，最终完成整个项目的构建
				Makefile编写规则：
					目标对象：依赖对象
					[tab]为了生成对象所执行的命令
					预定义变量：
						$^: 所有的依赖对象   $@: 目标对象的内容  $<: 依赖对象中的第一个
				make的解释执行规则：
					从上往下找到第一个目标对象，生成后，则退出
					main.o:main.c
					gcc -c $^ -o $@
					child.o:child.c
					gcc -c $^ -o $@
					main:main.o child.o
					gcc $^ -o $@
					这个代码只能生成一个main.o就退出了

					main : main.o child.o
					gcc $ ^ -o $@
					main.o:main.c             以第一个为标准  格式（间距啥的）
					gcc - c $ ^ -o $@
					child.o:child.c
					gcc - c $ ^ -o $@
					依赖两个.0生成main
					两个.o都不存在
					在下方继续找依赖对象(.0的生成规则)
					先生成依赖对象，然后最终生成目标对象

				伪对象：不管目标对象是否最新，每次都需要重新生成
				声明伪对象：.PHONY:target_name
项目版本管理工具：Git
	从服务器克隆一个项目：git clone https...
	本地的版本提交：git add ./ *            git commit -m"本次提交的备注信息"   / 和 *没有空格
	远程服务器的提交：git push origin master
	

1.修改一个sudoers配置---临时为当前用户赋予一下管理员权限
				/etc/sudoers
					1.su root
					2.chmod u+w /etc/sodoers
					3.vim /etc/sudoers
					4.:90   //跳转到90行附近后，添加当前用户信息
					5.:wq 保存退出
					
2.编写一个最简单的进度条程序：换行的作用
#include<stdio.h>
#include<unistd.h>
int main()
				{
					char buf[11] = { 0 };
					int i = 0;
					for (; i < 10; i++) {
						buf[i] = '-';
						//\n换行符: 数据换行，针对标准输出的时候，还有刷新缓冲区
								//      printf("%s\n",buf);
						//\r让光标回到起始位置
						printf("%s\r", buf);
						//      printf("-",buf);
						fflush(stdout);
						sleep(1);
					}
					return 0;
				}



	




