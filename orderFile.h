#pragma once
#include<iostream>
using namespace std;
#include"globalFile.h"
#include<fstream>
#include<string>
#include<map>

class OrderFile {
public:
	//���캯��
	OrderFile();

	//����ԤԼ����
	void updateOrder();

	//��¼ԤԼ����
	int m_Size;

	//��¼������Ϣ������ key�Ǽ�¼������ value�Ǿ����¼��ֵ����Ϣ
	map<int, map<string, string>> m_orderData;
};
