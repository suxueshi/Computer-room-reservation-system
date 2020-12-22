#include "manager.h"

//默认构造
Manager::Manager()
{
}

//有参构造
Manager::Manager(string name, string pwd)
{	
	//初始化管理员信息
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化容器
	this->initVector();

	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum) {
		vCom.emplace_back(com);
	}
	ifs.close();
	cout << "机房的数量为： " << vCom.size() << endl;
}

//选择菜单
void Manager::operMenu()
{
	cout << "欢迎管理员：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ---------------------------------\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          1.添加账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          2.查看账号            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          3.查看机房            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          4.清空预约            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t|          0.注销登录            |\n";
	cout << "\t\t|                                |\n";
	cout << "\t\t ---------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//添加账号  
void Manager::addPerson()
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;

	string fileNmae;	//操作文件名
	string tip;	//提示id号
	string errorTip;	//重复错误提示

	ofstream ofs;
	int select = 0;
	cin >> select;
	if (select == 1) {
		//添加的是学生
		fileNmae = STUDENT_FILE;
		tip = "请输入学号： ";
		errorTip = "学号重复， 请重新输入";
	}
	else {
		fileNmae = TEACHER_FILE;
		tip = "请输入职工编号： ";
		errorTip = "职工号重复， 请重新输入";
	}

	//利用追加的方式写文件
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

	cout << "请输入姓名： " << endl;
	cin >> name;

	cout << "请输入密码： " << endl;
	cin >> pwd;

	//向文件中添加数据
	ofs << id << " " << name << " " << pwd << " " << endl;
	cout << "添加成功" << endl;

	system("pause");
	system("cls");

	ofs.close();
	this->initVector();	//实时更新容器  重新获取文件信息 防止刚添加的重复BUG
}

void printStudent(Student& s) {	//遍历方式
	cout << "学号： " << s.m_Id << " 姓名： " << s.m_Name << " 密码： " << s.m_Pwd << endl;
}
void printTeacher(Teacher& t) {
	cout << "职工号： " << t.m_EmpId << " 姓名： " << t.m_Name << " 密码： " << t.m_Pwd << endl;
}
//查看账号
void Manager::showPerson()
{
	cout << "请选择查看的内容： " << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;

	int select = 0;
	cin >> select;
	if (select == 1) {
		cout << "所有的学生信息如下" << endl;
		for_each(vSu.begin(), vSu.end(), printStudent);	//遍历方式
	}
	else {
		cout << "所有的老师信息如下" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);
	}
	system("pause");
	system("cls");
}

//查看机房信息
void Manager::showComputer()
{
	cout << "机房的信息如下" << endl;
	for (auto e : vCom) {
		cout << "机房编号为： " << e.m_ComId << " 机房最大容量为： " << e.m_MaxNum << endl;
	}
	system("pause");
	system("cls");
}

//清空预约记录
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);	//清空方式打开
	ofs.close();
	cout << "清空成功" << endl;
	system("pause");
	system("cls");
}

//初始化容器
void Manager::initVector() {
	//确保容器清空状态
	vSu.clear();
	vTea.clear();

	//读取信息 学生、老师
	ifstream ifs;

	//读取学生信息
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "文件读取失败" << endl;
		return;
	}
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd) {
		vSu.emplace_back(s);
	}
	cout << "当前学生数量为： " << vSu.size() << endl;
	ifs.close();

	//读取老师信息
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open()) {
		cout << "文件读取失败" << endl;
		return;
	}
	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd) {
		vTea.emplace_back(t);
	}
	cout << "当前教师数量为： " << vTea.size() << endl;
	ifs.close();
}

//检测重复 参数：(传入id, 传入类型) 返回值：(true代表有重复， false代表无重复)
bool Manager::checkRepeat(int id, int type) {
	if (type == 1) {
		//检测学生
		for (auto e : vSu) {	//遍历容器
			if (id == e.m_Id) {
				return true;
			}
		}
	}
	else {
		//检测老师
		for (auto e : vTea) {
			if (id == e.m_EmpId) {
				return true;
			}
		}
	}
	return false;
}