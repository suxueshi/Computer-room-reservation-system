#pragma once
#include<iostream>
using namespace std;
#include"globalFile.h"
#include<fstream>
#include<string>
#include<map>

class OrderFile {
public:
	//构造函数
	OrderFile();

	//更新预约纪律
	void updateOrder();

	//记录预约条数
	int m_Size;

	//记录所有信息的容器 key是记录条数， value是具体记录键值的信息
	map<int, map<string, string>> m_orderData;
};
