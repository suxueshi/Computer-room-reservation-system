#include "manager.h"

//Ĭ�Ϲ���
Manager::Manager()
{
}

//�вι���
Manager::Manager(string name, string pwd)
{	
	//��ʼ������Ա��Ϣ
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ʼ������
	this->initVector();

	//��ʼ��������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum) {
		vCom.emplace_back(com);
	}
	ifs.close();
	cout << "����������Ϊ�� " << vCom.size() << endl;
}

//ѡ��˵�
void Manager::operMenu()
{
	cout << "��ӭ����Ա��" << this->m_Name << "��¼��" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.����˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.�鿴�˺�            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.�鿴����            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.���ԤԼ            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.ע����¼            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "��ѡ�����Ĳ����� " << endl;
}

//����˺�  
void Manager::addPerson()
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;

	string fileNmae;	//�����ļ���
	string tip;	//��ʾid��
	string errorTip;	//�ظ�������ʾ

	ofstream ofs;
	int select = 0;
	cin >> select;
	if (select == 1) {
		//��ӵ���ѧ��
		fileNmae = STUDENT_FILE;
		tip = "������ѧ�ţ� ";
		errorTip = "ѧ���ظ��� ����������";
	}
	else {
		fileNmae = TEACHER_FILE;
		tip = "������ְ����ţ� ";
		errorTip = "ְ�����ظ��� ����������";
	}

	//����׷�ӵķ�ʽд�ļ�
	ofs.open(fileNmae, ios::out | ios::app);
	int id;
	string name;
	string pwd;
	cout << tip << endl;

	while (true)
	{
		cin >> id;
		bool ret = this->checkRepeat(id, select);
		if (ret) {
			cout << errorTip << endl;
		}
		else
			break;
	}

	cout << "������������ " << endl;
	cin >> name;

	cout << "���������룺 " << endl;
	cin >> pwd;

	//���ļ����������
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "��ӳɹ�" << endl;

	system("pause");
	system("cls");

	ofs.close();
	this->initVector();	//ʵʱ��������  ���»�ȡ�ļ���Ϣ ��ֹ����ӵ��ظ�BUG
}

void printStudent(Student& s) {	//������ʽ
	cout << "ѧ�ţ� " << s.m_Id << " ������ " << s.m_Name << " ���룺 " << s.m_Pwd << endl;
}
void printTeacher(Teacher& t) {
	cout << "ְ���ţ� " << t.m_EmpId << " ������ " << t.m_Name << " ���룺 " << t.m_Pwd << endl;
}
//�鿴�˺�
void Manager::showPerson()
{
	cout << "��ѡ��鿴�����ݣ� " << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴������ʦ" << endl;

	int select = 0;
	cin >> select;
	if (select == 1) {
		cout << "���е�ѧ����Ϣ����" << endl;
		for_each(vSu.begin(), vSu.end(), printStudent);	//������ʽ
	}
	else {
		cout << "���е���ʦ��Ϣ����" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

//�鿴������Ϣ
void Manager::showComputer()
{
	cout << "��������Ϣ����" << endl;
	for (auto e : vCom) {
		cout << "�������Ϊ�� " << e.m_ComId << " �����������Ϊ�� " << e.m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

//���ԤԼ��¼
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);	//��շ�ʽ��
	ofs.close();
	cout << "��ճɹ�" << endl;
	system("pause");
	system("cls");
}

//��ʼ������
void Manager::initVector() {
	//ȷ���������״̬
	vSu.clear();
	vTea.clear();

	//��ȡ��Ϣ ѧ������ʦ
	ifstream ifs;

	//��ȡѧ����Ϣ
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
		vSu.emplace_back(s);
	}
	cout << "��ǰѧ������Ϊ�� " << vSu.size() << endl;
	ifs.close();

	//��ȡ��ʦ��Ϣ
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
		vTea.emplace_back(t);
	}
	cout << "��ǰ��ʦ����Ϊ�� " << vTea.size() << endl;
	ifs.close();
}

//����ظ� ������(����id, ��������) ����ֵ��(true�������ظ��� false�������ظ�)
bool Manager::checkRepeat(int id, int type) {
	if (type == 1) {
		//���ѧ��
		for (auto e : vSu) {	//��������
			if (id == e.m_Id) {
				return true;
			}
		}
	}
	else {
		//�����ʦ
		for (auto e : vTea) {
			if (id == e.m_EmpId) {
				return true;
			}
		}
	}
	return false;
}