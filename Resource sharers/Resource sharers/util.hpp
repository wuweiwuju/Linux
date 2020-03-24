#pragma once
#ifdef _WIN32
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<ws2tcpip.h>
//��ȡ������Ϣ��ͷ�ļ�
#include<Iphlpapi.h>
//��ȡ������Ϣ�ӿڵĿ��ļ�����
#pragma comment(lib, "Iphlpapi.lib")
//windows�µ�socket��
#pragma comment(lib, "ws2_32.lib")
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
		//����һ��������Ϣ�ṹ�Ŀռ�
		PIP_ADAPTER_INFO p_adapters = new IP_ADAPTER_INFO();
		//GetAdapterInfo windows�»�ȡ������Ϣ�Ľӿ�--������Ϣ�п����ж������˴���һ��ָ��
		//��ȡ������Ϣ�п��ܻ�ʧ�ܣ���Ϊ�ռ䲻�㣬�����һ������Ͳ������������û���������������Ϣռ�ô�С
		uint64_t all_adpter_size = sizeof(IP_ADAPTER_INFO);
		//all_adpter_size���ڻ�ȡʵ������������Ϣ��ռ�ռ��С
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
			Adapter adapter;
			inet_pton(AF_INET,p_adapters->IpAddressList.IpAddress.String,&adapter._ip_addr);
			inet_pton(AF_INET,p_adapters->IpAddressList.IpMask.String,&adapter._mask_addr);
			//��Ϊ��Щ������û�����ã�����IP��ַΪ0
			if (adapter._ip_addr != 0) {
				//���������Ϣ��ӵ�vector�з��ظ��û�
				list->push_back(adapter);
				std::cout << "�������ƣ�" << p_adapters->AdapterName << std::endl;
				std::cout << "����������" << p_adapters->Description << std::endl;
				std::cout << "ip��ַ��" << p_adapters->IpAddressList.IpAddress.String << std::endl;
				std::cout << "�������룺" << p_adapters->IpAddressList.IpMask.String << std::endl;
				std::cout << std::endl;
			}
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