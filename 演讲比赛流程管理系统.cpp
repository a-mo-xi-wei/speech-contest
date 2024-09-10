#include<iostream>
using namespace std;
#include"speechManager.h"
#include<string>
//12名参赛选手，10名评委打分
int main() {
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	//测试12名选手创建
	/*for (auto &c : sm.m_Speaker) {
		cout << "编号：" << c.first<<" 姓名："<<c.second.m_Name<<" 得分："<<c.second.m_Score[0] << endl;
	}*/
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		cout << "选手编号;" << it->first << " 姓名：" << it->second.m_Name << " 分数：" << it->second.m_Score[0] << endl;
	}*/
	
	int choice = 0;//用于存储用户输入
	while (true) {
		sm.showMenu();
		cout << "请输入选择：";
		cin >> choice;
		switch (choice) {
		case 1://开始演讲比赛
			sm.startSpeech(); 
			break;
		case 2://查看往届记录
			sm.loadScore();
			break;
		case 3://清空比赛记录
			sm.clearRecord();
			break;
		case 0://退出比赛程序
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}
//唯一的问题就是再次编译的话，结果还是从第一届开始
//想要实现届数的延续
