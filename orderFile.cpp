#include"orderFile.h"

//构造函数
OrderFile::OrderFile() {
	//拿到所有文件信息
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);
	string date;      //日期
	string interval;  //时间段
	string stuId;     //学生编号
	string stuName;   //学生姓名
	string roomId;    //机房编号
	string status;    //预约状态

	this->m_Size = 0;	//预约记录的条数

	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs 
		>> stuName && ifs >> roomId && ifs >> status)	//以空格为界读入信息
	{
		//cout << date << endl;
		//cout << interval << endl;
		//cout << stuId << endl;
		//cout << stuName << endl;
		//cout << roomId << endl;
		//cout << status << endl;
		//cout << endl;

		//date:1111
		string key;
		string value;
		map<string, string> m;
		//截取字符
		int pos = date.find(":");	//4
		if (pos != -1) {
			key = date.substr(0, pos);	//substr指从0位置开始 截取pos个字符 
			value = date.substr(pos + 1, date.size() - pos - 1);	//size = 9 pos = 4 
			m.insert(make_pair(key, value));
		}
		pos = interval.find(":");
		if (pos != -1) {
			key = interval.substr(0, pos);	//substr指从0位置开始 截取pos个字符 
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = roomId.find(":");
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			m.insert(make_pair(key, value));
		}

		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(make_pair(key, value));
		}
		//将小map容器放入大的容器中
		this->m_orderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
	}
	ifs.close();

	//for (auto e : m_orderData) {
	//	cout << "条数为" << e.first << "value = " << endl;
	//	for (auto me : e.second) {
	//		cout << "key: " << me.first << " value: " << me.second << endl;
	//	}
	//}
	//cout << endl;
}

//更新预约纪律
void OrderFile::updateOrder() {
	if (this->m_Size == 0) {
		return;
	}
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::out | ios::trunc);
	//将信息重新写入
	for (int i = 0; i < this->m_Size; ++i) {
		ofs << "date:" << this->m_orderData[i]["date"] << " ";
		ofs << "interval:" << this->m_orderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_orderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_orderData[i]["stuName"] << " ";
		ofs << "roomId:" << this->m_orderData[i]["roomId"] << " ";
		ofs << "status:" << this->m_orderData[i]["status"] << endl;
	}
	ofs.close();
}