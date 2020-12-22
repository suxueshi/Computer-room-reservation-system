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
	//Ĭ�Ϲ���
	Student();
	//�вι���
	Student(int id, string name, string pwd);

	//��д����Ĵ��麯��
    void operMenu();

	//����ԤԼ
	void applyOrder();

	//�鿴����ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void shouAllOrder();

	//ȡ��ԤԼ
	void cancelOrder();

	//ѧ��
	int m_Id;

	//������Ϣ
	vector<ComputerRoom> vCom;
};