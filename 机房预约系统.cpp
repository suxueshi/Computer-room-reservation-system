#include<iostream>
#include<string>
#include"globalFile.h"
#include"Identity.h"
#include<fstream>
#include"student.h"
#include"teacher.h"
#include"manager.h"

using namespace std;

//�����ʦ�Ӳ˵�
void teacherMenu(Identity*& teacher) {
	while (true)
	{
		teacher->operMenu();	//��̬�������ָ�봴�������������õĽӿ�
		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1) {	//�鿴����ԤԼ
			tea->showAllOrder();
		}
		else if (select == 2) {	//���ԤԼ
			tea->validOrder();
		}
		else {
			delete teacher;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//����ѧ���Ӳ˵�����
void studentMenu(Identity*& student) {
	while (true)
	{
		//����ѧ���Ӳ˵�
		student->operMenu();
		
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1) {	//����ԤԼ
			stu->applyOrder();
		}
		else if (select == 2) {	//�鿴����ԤԼ
			stu->showMyOrder();
		}
		else if (select == 3) {	//�鿴������ԤԼ
			stu->shouAllOrder();
		}
		else if (select == 4) {	//ȡ��ԤԼ
			stu->cancelOrder();
		}
		else {	//ע����½
			delete student;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//�������Ա�Ӳ˵�����
void managerMenu(Identity*& manager) {
	while (true)
	{
		//���ù���Ա�Ӳ˵�
		manager->operMenu();	//��̬�������ָ�봴�������������õĽӿ�

		//������ָ��תΪ����ָ�� ��������������Ľӿ�
		Manager* man = (Manager*)manager;
		
		int select = 0;
		cin >> select;
		if (select == 1)  //����˺�
		{
			//cout << "����˺�" << endl;
			man->addPerson();
		}
		else if (select == 2) //�鿴�˺�
		{
			//cout << "�鿴�˺�" << endl;
			man->showPerson();
		}
		else if (select == 3) //�鿴����
		{
			//cout << "�鿴����" << endl;
			man->showComputer();
		}
		else if (select == 4) //���ԤԼ
		{
			//cout << "���ԤԼ" << endl;
			man->cleanFile();
		}
		else
		{	//ע��ģ��
			delete manager;	//���ٶ�������
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

void LoginIn(string filename, int type) {
	Identity* person = nullptr;

	ifstream ifs;
	ifs.open(filename, ios::in);	//���ļ�

	//�ļ����������
	if (!ifs.is_open()) {
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}

	int id = 0;
	string name;
	string pwd;
	if (type == 1)	//ѧ����¼
	{
		cout << "���������ѧ��" << endl;
		cin >> id;
	}
	else if (type == 2) //��ʦ��¼
	{
		cout << "���������ְ����" << endl;
		cin >> id;
	}

	cout << "�������û�����" << endl;
	cin >> name;

	cout << "���������룺 " << endl;
	cin >> pwd;

	if (type == 1)
	{
		//ѧ����¼��֤
		int fId;	//���ļ���ȡ��id��
		string fName;	//���ļ���ȡ������
		string fPwd;	//���ļ���ȡ������
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {	//�Կո�ָ����Ϣ��һ��һ������ȥ
			//���û���Ϣ���Ա�
			if (fId == id && fName == name && fPwd == pwd) {	//����ԭ��������txt�ļ���Ҫ���±����ANSI��ʽ
				cout << "ѧ����½��֤�ɹ�" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);	//��̬������ָ������������
				//ѧ����֤ͨ���ͽ���ѧ����ݵ��Ӳ˵�
				studentMenu(person);
				return;
			}
		}

	}
	else if (type == 2)
	{
		//��ʦ��¼��֤
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
		
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "��ʦ��֤��¼�ɹ�!" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//��ʦ��֤ͨ���ͽ�����ʦ���Ӳ˵�
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա��¼��֤
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)	{
		
			if (name == fName && pwd == fPwd)
			{
				cout << "��֤��¼�ɹ�!" << endl;
				//��¼�ɹ��󣬰�������������Ա����
				system("pause");
				system("cls");
				//��������Ա����
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}

	cout << "��֤��¼ʧ��!" << endl;

	system("pause");
	system("cls");
	return;
}	

int main() {

	int select = 0;	//���ڽ����û���ѡ��
	while (true)
	{
		cout << "======================  ��ӭ�������ǲ��ͻ���ԤԼϵͳ  ====================="
			<< endl;
		cout << endl << "�������������" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.ѧ������           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.��    ʦ           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.�� �� Ա           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.��    ��           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "��������ѡ��: ";

		cin >> select;
		switch (select)
		{
		case 1:	//ѧ�����
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:	//��ʦ���
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:	//����Ա���
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "�����������������룡" << endl;
			system("pause");
			system("cls");
			break;
		}
		
	}
	system("pause");
	return 0;
}