#pragma once
#include"util.hpp"
#include<thread>
class Host
{
public:
	uint32_t _ip_addr;//Ҫ��Ե�����ip��ַ
	bool _pair_ret;//���ڴ����Խ��
};
class Client 
{
public:
	//������Ե��߳���ں���
	void HostPair(Host* host)
	{

	}
	//��ȡ��������
	bool GetOnlineHost()
	{
		//1.��ȡ������Ϣ�������õ������������е�IP��ַ�б�
		std::vector<Adapter> list;
		AdapterUtil::GetAllAdapter(&list);
		std::vector<Host> host_list;
		//�õ�����������IP��ַ�б�
		for (int i = 0; i < list.size(); ++i)
		{
			uint32_t ip = list[i]._ip_addr;
			uint32_t mask = list[i]._mask_addr;
			//���������
			uint32_t net = ntohs(ip & mask);
			//�������������
			uint32_t max_host = (~ntohs(mask));
			for (int j = 1; j < max_host; ++j)
			{
				//�������IP�ļ���Ӧ��ʹ�������ֽ��������ź�������
				uint32_t host_ip = net + j;
				Host host;
				host._ip_addr = host_ip;
				host._pair_ret = false;
				host_list.push_back(host);
			}
		}
		//2.��host_list�е����������߳̽������
		std::vector<std::thread*> thr_list(host_list.size());
		for (int i = 0; i < host_list.size(); ++i)
		{
			thr_list[i] = new std::thread(&Client::HostPair, this, &host_list[i]);
		}
		//3.�ȴ������߳����������ϣ��ж���Խ����������������ӵ�online_host��
		for (int i = 0; i < host_list.size(); ++i)
		{
			thr_list[i]->join();
			if (host_list[i]._pair_ret == true)
			{
				_online_host.push_back(host_list[i]);
			}
			delete thr_list[i];
		}
		std::cout << "��ѡ�������������ȡ�����ļ��б�";
		fflush(stdout);
	}
	//��ȡ�ļ��б�
	bool GetShareList()
	{

	}
	//�����ļ�
	bool DownloadFile()
	{

	}
private:
	std::vector<Host> _online_host;
};
