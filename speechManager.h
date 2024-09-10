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
//设计演讲管理类
class SpeechManager {
public:
	SpeechManager();
	void showMenu();
	void exitSystem();
	~SpeechManager();
	//初始化容器和属性
	void initSpeech();
	//创建12名选手
	void createSpeaker();
	//开始比赛
	void startSpeech();//比赛整个流程控制函数
	//抽签
	void speechDraw();
	//比赛
	void speechContest();
	//显示得分
	void showScore();
	//保存分数
	void saveScore();
	//读取往届记录
	void loadScore();
	//判断文件是否为空
	bool fileIsEmpty;
	//存放往届记录的容器
	map<int, vector<int>>preRecord;
	//查看往届记录
	//void showRecord();
	//清空记录
	void clearRecord();

	//成员属性
	//保存第一轮比赛选手容器
	vector<int>v1;
	//第一轮晋级选手 第二轮比赛容器
	vector<int>v2;
	//胜出的前三名选手容器
	vector<int>Victory;
	//存放编号以及对应具体选手容器
	map<int, Speaker>m_Speaker;
	//存放比赛轮数
	int m_Index;
	int m_Session ;
};