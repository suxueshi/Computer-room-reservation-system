#include<iostream>
#include<string>
#include"globalFile.h"
#include"Identity.h"
#include<fstream>
#include"student.h"
#include"teacher.h"
#include"manager.h"

using namespace std;

//进入教师子菜单
void teacherMenu(Identity*& teacher) {
	while (true)
	{
		teacher->operMenu();	//多态：父类的指针创建的子类对象调用的接口
		Teacher* tea = (Teacher*)teacher;
		int select = 0;
		cin >> select;
		if (select == 1) {	//查看所有预约
			tea->showAllOrder();
		}
		else if (select == 2) {	//审核预约
			tea->validOrder();
		}
		else {
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//进入学生子菜单界面
void studentMenu(Identity*& student) {
	while (true)
	{
		//调用学生子菜单
		student->operMenu();
		
		Student* stu = (Student*)student;
		int select = 0;
		cin >> select;
		if (select == 1) {	//申请预约
			stu->applyOrder();
		}
		else if (select == 2) {	//查看自身预约
			stu->showMyOrder();
		}
		else if (select == 3) {	//查看所有人预约
			stu->shouAllOrder();
		}
		else if (select == 4) {	//取消预约
			stu->cancelOrder();
		}
		else {	//注销登陆
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//进入管理员子菜单界面
void managerMenu(Identity*& manager) {
	while (true)
	{
		//调用管理员子菜单
		manager->operMenu();	//多态：父类的指针创建的子类对象调用的接口

		//将父类指针转为子类指针 ，调用子类自身的接口
		Manager* man = (Manager*)manager;
		
		int select = 0;
		cin >> select;
		if (select == 1)  //添加账号
		{
			//cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2) //查看账号
		{
			//cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3) //查看机房
		{
			//cout << "查看机房" << endl;
			man->showComputer();
		}
		else if (select == 4) //清空预约
		{
			//cout << "清空预约" << endl;
			man->cleanFile();
		}
		else
		{	//注销模块
			delete manager;	//销毁堆区对象
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}

	}
}

void LoginIn(string filename, int type) {
	Identity* person = nullptr;

	ifstream ifs;
	ifs.open(filename, ios::in);	//读文件

	//文件不存在情况
	if (!ifs.is_open()) {
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}

	int id = 0;
	string name;
	string pwd;
	if (type == 1)	//学生登录
	{
		cout << "请输入你的学号" << endl;
		cin >> id;
	}
	else if (type == 2) //教师登录
	{
		cout << "请输入你的职工号" << endl;
		cin >> id;
	}

	cout << "请输入用户名：" << endl;
	cin >> name;

	cout << "请输入密码： " << endl;
	cin >> pwd;

	if (type == 1)
	{
		//学生登录验证
		int fId;	//从文件读取的id号
		string fName;	//从文件读取的姓名
		string fPwd;	//从文件获取的密码
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {	//以空格分割的信息会一个一个都进去
			//与用户信息做对比
			if (fId == id && fName == name && fPwd == pwd) {	//这里原来创建的txt文件需要重新保存成ANSI格式
				cout << "学生登陆验证成功" << endl;
				system("pause");
				system("cls");
				person = new Student(id, name, pwd);	//多态：父类指针调用子类对象
				//学生验证通过就进入学生身份的子菜单
				studentMenu(person);
				return;
			}
		}

	}
	else if (type == 2)
	{
		//教师登录验证
		int fId;
		string fName;
		string fPwd;
		while (ifs >> fId && ifs >> fName && ifs >> fPwd) {
		
			if (id == fId && name == fName && pwd == fPwd)
			{
				cout << "教师验证登录成功!" << endl;
				system("pause");
				system("cls");
				person = new Teacher(id, name, pwd);
				//老师验证通过就进入老师的子菜单
				teacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员登录验证
		string fName;
		string fPwd;
		while (ifs >> fName && ifs >> fPwd)	{
		
			if (name == fName && pwd == fPwd)
			{
				cout << "验证登录成功!" << endl;
				//登录成功后，按任意键进入管理员界面
				system("pause");
				system("cls");
				//创建管理员对象
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}

	cout << "验证登录失败!" << endl;

	system("pause");
	system("cls");
	return;
}	

int main() {

	int select = 0;	//用于接收用户的选择
	while (true)
	{
		cout << "======================  欢迎来到传智播客机房预约系统  ====================="
			<< endl;
		cout << endl << "请输入您的身份" << endl;
		cout << "\t\t -------------------------------\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          1.学生代表           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          2.老    师           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          3.管 理 员           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t|          0.退    出           |\n";
		cout << "\t\t|                               |\n";
		cout << "\t\t -------------------------------\n";
		cout << "输入您的选择: ";

		cin >> select;
		switch (select)
		{
		case 1:	//学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:	//老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:	//管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0:
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入有误，请重新输入！" << endl;
			system("pause");
			system("cls");
			break;
		}
		
	}
	system("pause");
	return 0;
}