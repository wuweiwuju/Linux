#pragma once
#include"util.hpp"
#include<thread>
class Host
{
public:
	uint32_t _ip_addr;//要配对的主机ip地址
	bool _pair_ret;//用于存放配对结果
};
class Client 
{
public:
	//主机配对的线程入口函数
	void HostPair(Host* host)
	{

	}
	//获取在线主机
	bool GetOnlineHost()
	{
		//1.获取网卡信息，进而得到局域网中所有的IP地址列表
		std::vector<Adapter> list;
		AdapterUtil::GetAllAdapter(&list);
		std::vector<Host> host_list;
		//得到所有主机的IP地址列表
		for (int i = 0; i < list.size(); ++i)
		{
			uint32_t ip = list[i]._ip_addr;
			uint32_t mask = list[i]._mask_addr;
			//计算网络号
			uint32_t net = ntohs(ip & mask);
			//计算最大主机号
			uint32_t max_host = (~ntohs(mask));
			for (int j = 1; j < max_host; ++j)
			{
				//这个主机IP的计算应该使用主机字节序的网络号和主机号
				uint32_t host_ip = net + j;
				Host host;
				host._ip_addr = host_ip;
				host._pair_ret = false;
				host_list.push_back(host);
			}
		}
		//2.对host_list中的主机创建线程进行配对
		std::vector<std::thread*> thr_list(host_list.size());
		for (int i = 0; i < host_list.size(); ++i)
		{
			thr_list[i] = new std::thread(&Client::HostPair, this, &host_list[i]);
		}
		//3.等待所有线程主机配对完毕，判断配对结果，将在线主机添加到online_host中
		for (int i = 0; i < host_list.size(); ++i)
		{
			thr_list[i]->join();
			if (host_list[i]._pair_ret == true)
			{
				_online_host.push_back(host_list[i]);
			}
			delete thr_list[i];
		}
		std::cout << "请选择配对主机，读取共享文件列表：";
		fflush(stdout);
	}
	//获取文件列表
	bool GetShareList()
	{

	}
	//下载文件
	bool DownloadFile()
	{

	}
private:
	std::vector<Host> _online_host;
};
