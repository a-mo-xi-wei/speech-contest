#include<iostream>
using namespace std;
#include"speechManager.h"
#include<string>
//12������ѡ�֣�10����ί���
int main() {
	srand((unsigned int)time(NULL));
	SpeechManager sm;
	//����12��ѡ�ִ���
	/*for (auto &c : sm.m_Speaker) {
		cout << "��ţ�" << c.first<<" ������"<<c.second.m_Name<<" �÷֣�"<<c.second.m_Score[0] << endl;
	}*/
	/*for (map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it != sm.m_Speaker.end(); it++) {
		cout << "ѡ�ֱ��;" << it->first << " ������" << it->second.m_Name << " ������" << it->second.m_Score[0] << endl;
	}*/
	
	int choice = 0;//���ڴ洢�û�����
	while (true) {
		sm.showMenu();
		cout << "������ѡ��";
		cin >> choice;
		switch (choice) {
		case 1://��ʼ�ݽ�����
			sm.startSpeech(); 
			break;
		case 2://�鿴�����¼
			sm.loadScore();
			break;
		case 3://��ձ�����¼
			sm.clearRecord();
			break;
		case 0://�˳���������
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
//Ψһ����������ٴα���Ļ���������Ǵӵ�һ�쿪ʼ
//��Ҫʵ�ֽ���������
