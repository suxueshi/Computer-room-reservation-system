#pragma once
#include<iostream>
using namespace std;
#include "identity.h"
#include<string>
#include"orderFile.h"
#include"student.h"
#include<vector>

class Teacher :public Identity
{
public:

	//Ĭ�Ϲ���
	Teacher();

	//�вι��� (ְ����ţ�����������)
	Teacher(int empId, string name, string pwd);

	//�˵�����
    void operMenu();

	//�鿴����ԤԼ
	void showAllOrder();

	//���ԤԼ
	void validOrder();

	int m_EmpId; //��ʦ���

};