#pragma once
#include<iostream>
using namespace std;
#include "identity.h"
#include<string>
#include<fstream>
#include"globalFile.h"
#include<vector>
#include"student.h"
#include"teacher.h"
#include<algorithm>
#include"computerRoom.h"

class Manager :public Identity
{
public:

	//Ĭ�Ϲ���
	Manager();

	//�вι���  ����Ա����������
	Manager(string name, string pwd);

	//ѡ��˵�
	virtual void operMenu();

	//����˺�  
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ��¼
	void cleanFile();

	//��ʼ������
	void initVector();

	//ѧ������
	vector<Student> vSu;

	//��ʦ����
	vector<Teacher> vTea;
	
	//����ظ� ������(����id, ��������) ����ֵ��(true�������ظ��� false�������ظ�)
	bool checkRepeat(int id, int type);

	//������Ϣ
	vector<ComputerRoom> vCom;
};