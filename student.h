#pragma once
#include<iostream>
using namespace std;
#include"Identity.h"
#include<string>
#include<vector>
#include"computerRoom.h"
#include<fstream>
#include"globalFile.h"
#include"orderFile.h"

class Student : public Identity {
public:
	//默认构造
	Student();
	//有参构造
	Student(int id, string name, string pwd);

	//重写父类的纯虚函数
    void operMenu();

	//申请预约
	void applyOrder();

	//查看自身预约
	void showMyOrder();

	//查看所有预约
	void shouAllOrder();

	//取消预约
	void cancelOrder();

	//学号
	int m_Id;

	//机房信息
	vector<ComputerRoom> vCom;
};