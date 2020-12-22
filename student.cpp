#include"student.h"

//默认构造
Student::Student() {

}
//有参构造
Student::Student(int id, string name, string pwd) {
	//初始化属性
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxNum) {
		vCom.emplace_back(com);
	}
ifs.close();


}

//重写父类的纯虚函数
void Student::operMenu() {
	cout << "欢迎学生代表：" << this->m_Name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          1.申请预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          2.查看我的预约          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          3.查看所有预约          |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          4.取消预约              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                 |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//申请预约
void Student::applyOrder() {
	cout << "机房开放时间为周一至周五，请输入申请预约的时间" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	int date = 0;	//日期
	int interval = 0;	//时间段
	int room = 0;	//机房编号
	while (true)
	{
		cin >> date;
		if (date >= 1 && date <= 5) {
			break;
		}
		cout << "输入有误，重新输入" << endl;
	}
	cout << "请输入申请的时间段： " << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2) {
			break;
		}
		cout << "输入有误，重新输入" << endl;
	}
	cout << "请选择机房" << endl;
	for (auto e : vCom) {
		cout << e.m_ComId << "号机房的容量为： " << e.m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3) {
			break;
		}
		cout << "输入有误，重新输入" << endl;
	}
	cout << "预约成功，审核中" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);	//以追加的形式写文件

	ofs << "date:" << date << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomId:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();
	system("pause");
	system("cls");
}

//查看自身预约
void Student::showMyOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; ++i) {
		//需要stoi转成整型
		if (this->m_Id == stoi(of.m_orderData[i]["stuId"])) {	//找到自身的预约[stuId]是里面的那个map的key值
			cout << "预约日期： 周" << of.m_orderData[i]["date"];
			cout << " 时间段： " << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房号：" << of.m_orderData[i]["roomId"];
			string status = "状态： ";
			//1 审核中  2 已预约 -1 预约失败 0 取消预约
			if (of.m_orderData[i]["status"] == "1") {
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "审核未通过，预约失败";
			}
			else
			{
				status += "预约已取消";
			}
			cout << status << endl;
		}
	}
	system("pause");
	system("cls");
}

//查看所有预约
void Student::shouAllOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < of.m_Size; ++i) {
		cout << i + 1 << "、 ";

		cout << "预约日期： 周" << of.m_orderData[i]["date"];
		cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 学号：" << of.m_orderData[i]["stuId"];
		cout << " 姓名：" << of.m_orderData[i]["stuName"];
		cout << " 机房：" << of.m_orderData[i]["roomId"];
		string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约 -1 预约失败
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "审核未通过，预约失败";
		}
		else
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

	

//取消预约
void Student::cancelOrder() {
	OrderFile of;
	if (of.m_Size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "审核中或者预约成功的记录可以取消， 请输入取消的记录：" << endl;
	int index = 1;
	vector<int> v;	//存放再最大容器的下标编号
	for (int i = 0; i < of.m_Size; ++i) {
		//先判断是自身的学号
		if (this->m_Id == stoi(of.m_orderData[i]["stuId"])) {
			//再筛选状态 审核中或者预约成功
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2") {
				v.emplace_back(i);
				cout << index++ << "、 ";
				cout << "预约日期： 周" << of.m_orderData[i]["date"];
				cout << " 时段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
				cout << " 机房：" << of.m_orderData[i]["roomId"];
				string status = " 状态： ";  // 0 取消的预约   1 审核中   2 已预约  -1 预约失败
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				cout << status << endl;
			}
		}
	}
	cout << "请输入取消的记录， 0代表返回" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size()) {
			if (select == 0) {
				break;
			}
			else {
				of.m_orderData[v[select - 1]]["status"] = "0";	//select要减去1 才是真正再大容器中的下标位置
				of.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误， 请重新输入";
	}
	system("pause");
	system("cls");
}