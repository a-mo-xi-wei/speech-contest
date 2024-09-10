#pragma once
#include<iostream>
#include"Speaker.h"
#include<map>
#include<vector>
#include<deque>
#include<algorithm>
#include<functional>
#include<numeric>
#include<iomanip>
#include<string>
#include<fstream>
#include<ctime>
#include<conio.h>
using namespace std;
//����ݽ�������
class SpeechManager {
public:
	SpeechManager();
	void showMenu();
	void exitSystem();
	~SpeechManager();
	//��ʼ������������
	void initSpeech();
	//����12��ѡ��
	void createSpeaker();
	//��ʼ����
	void startSpeech();//�����������̿��ƺ���
	//��ǩ
	void speechDraw();
	//����
	void speechContest();
	//��ʾ�÷�
	void showScore();
	//�������
	void saveScore();
	//��ȡ�����¼
	void loadScore();
	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;
	//��������¼������
	map<int, vector<int>>preRecord;
	//�鿴�����¼
	//void showRecord();
	//��ռ�¼
	void clearRecord();

	//��Ա����
	//�����һ�ֱ���ѡ������
	vector<int>v1;
	//��һ�ֽ���ѡ�� �ڶ��ֱ�������
	vector<int>v2;
	//ʤ����ǰ����ѡ������
	vector<int>Victory;
	//��ű���Լ���Ӧ����ѡ������
	map<int, Speaker>m_Speaker;
	//��ű�������
	int m_Index;
	int m_Session ;
};