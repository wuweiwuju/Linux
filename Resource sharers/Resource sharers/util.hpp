#pragma once
#ifdef _WIN32
#include<iostream>
#include<vector>
#include<ws2tcpip.h>
#include<Iphlpapi.h>
#pragma comment(lib, "Iphlpapi.lib")
#else
//Linuxͷ�ļ�
#endif
class Adapter
{
public:
	uint32_t _ip_addr;//�����ϵ�ip��ַ
	uint32_t _mask_addr;//�����ϵ���������
};

class AdapterUtil
{
#ifdef _WIN32
public:
	//Windows�µĻ�ȡ������Ϣʵ��
	static bool GetAllAdapter(std::vector<Adapter> *list) 
	{
		PIP_ADAPTER_INFO p_adapters = new IP_ADAPTER_INFO();
		//GetAdapterInfo windows�»�ȡ������Ϣ�Ľӿ�--������Ϣ�п����ж������˴���һ��ָ��
		//��ȡ������Ϣ�п��ܻ�ʧ�ܣ���Ϊ�ռ䲻�㣬�����һ������Ͳ������������û���������������Ϣռ�ô�С
		uint64_t all_adpter_size = sizeof(IP_ADAPTER_INFO);
		int ret = GetAdaptersInfo(p_adapters, (PULONG)&all_adpter_size);
		if (ret == ERROR_BUFFER_OVERFLOW)//��������ʾ�������ռ䲻��
		{
			delete p_adapters;
			p_adapters = (PIP_ADAPTER_INFO)new BYTE[all_adpter_size];
			//���»�ȡ������Ϣ
			GetAdaptersInfo(p_adapters, (PULONG)&all_adpter_size);
		}
		while (p_adapters)
		{
			std::cout << "�������ƣ�" << p_adapters->AdapterName << std::endl;
			std::cout << "����������" << p_adapters->Description << std::endl;
			std::cout << "ip��ַ��" << p_adapters->IpAddressList.IpAddress.String << std::endl;
			std::cout << "�������룺" << p_adapters->IpAddressList.IpMask.String << std::endl;
			p_adapters = p_adapters->Next;
		}
		delete p_adapters;
		return true;
	}
#else
	//Linux�µĻ�ȡ������Ϣʵ��
	bool GetAllAdapter(std::vector<Adapter> *list);
#endif
};