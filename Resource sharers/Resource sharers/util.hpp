#pragma once
#ifdef _WIN32
#include<iostream>
#include<vector>
#include<ws2tcpip.h>
#include<Iphlpapi.h>
#pragma comment(lib, "Iphlpapi.lib")
#else
//Linux头文件
#endif
class Adapter
{
public:
	uint32_t _ip_addr;//网卡上的ip地址
	uint32_t _mask_addr;//网卡上的子网掩码
};

class AdapterUtil
{
#ifdef _WIN32
public:
	//Windows下的获取网卡信息实现
	static bool GetAllAdapter(std::vector<Adapter> *list) 
	{
		PIP_ADAPTER_INFO p_adapters = new IP_ADAPTER_INFO();
		//GetAdapterInfo windows下获取网卡信息的接口--网卡信息有可能有多个，因此传入一个指针
		//获取网卡信息有可能会失败，因为空间不足，因此有一个输出型参数，用于向用户返回所有网卡信息占用大小
		uint64_t all_adpter_size = sizeof(IP_ADAPTER_INFO);
		int ret = GetAdaptersInfo(p_adapters, (PULONG)&all_adpter_size);
		if (ret == ERROR_BUFFER_OVERFLOW)//这个错误表示缓冲区空间不足
		{
			delete p_adapters;
			p_adapters = (PIP_ADAPTER_INFO)new BYTE[all_adpter_size];
			//重新获取网卡信息
			GetAdaptersInfo(p_adapters, (PULONG)&all_adpter_size);
		}
		while (p_adapters)
		{
			std::cout << "网卡名称：" << p_adapters->AdapterName << std::endl;
			std::cout << "网卡描述：" << p_adapters->Description << std::endl;
			std::cout << "ip地址：" << p_adapters->IpAddressList.IpAddress.String << std::endl;
			std::cout << "子网掩码：" << p_adapters->IpAddressList.IpMask.String << std::endl;
			p_adapters = p_adapters->Next;
		}
		delete p_adapters;
		return true;
	}
#else
	//Linux下的获取网卡信息实现
	bool GetAllAdapter(std::vector<Adapter> *list);
#endif
};