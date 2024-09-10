#include"speechManager.h"

SpeechManager::SpeechManager(){
	this->initSpeech();
	this->m_Session = 1;
}
void SpeechManager::showMenu() {
	cout << "**************************************" << endl
		<<"************欢迎参加演讲比赛**********" << endl
		<<"************1.开始演讲比赛************" << endl
		<<"************2.查看往届记录************" << endl
		<<"************3.清空比赛记录************" << endl
		<<"************0.退出比赛程序************" << endl;
	cout << endl;
}
void SpeechManager::exitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
void SpeechManager::initSpeech() {
	//容器都置空
	this->v1.clear();
	this->v2.clear();
	this->Victory.clear();
	this->m_Speaker.clear();
	//初始化比赛轮数
	this->m_Index = 1;
	
}
void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "选手";
		name += nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}
		//创建选手编号，并且放入到v1容器中
		this->v1.push_back(i + 10001);
		//选手编号以及对应选手放入到map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}
void SpeechManager::speechDraw() {
	cout << "第" << this->m_Index << "轮比赛选手正在抽签" << endl;
	cout << "------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1) {
		//第一轮比赛
		random_shuffle(this->v1.begin(), this->v1.end());
		for (auto c : this->v1) {
			cout << c << " ";
		}
		cout << endl;
	}
	else {
		//第二轮比赛
		random_shuffle(this->v2.begin(), this->v2.end());
		for (auto c : this->v2) {
			cout << c << " ";
		}
		cout << endl;
	}
	cout << "-------------------------" << endl;
	system("pause");
	cout << endl;
}
void SpeechManager::speechContest() {
	cout << "--------------第" << this->m_Index << "轮比赛正式开始---------------" << endl;
	//准备临时容器，存放小组成绩
	multimap<double, int, greater<double>>groupScore;
	vector<int>v_Src;//编号
	int num = 0;//6人一组
	if (this->m_Index == 1) {
		v_Src = this->v1;
	}
	else {
		v_Src = this->v2;
	}
	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		++num;
		deque<double>d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			cout <<left<<setw(4)<< score << "  ";
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();//去除最高分最低分
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		//打印平均分
		cout << "编号：" << *it << " 姓名：" << m_Speaker[*it].m_Name
			<< " 获取的平均分为：" << avg <<endl;
		//将平均分放到map容器里
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		//将打分数据放入到临时小组容器中
		groupScore.insert(make_pair(avg, *it));//key是得分，value是具体选手编号	
		// 6人一组
		if (num % 6 == 0) {
			cout << endl<<"第" << num/6 << "小组比赛排名：" << endl;
			for (auto c : groupScore) {
				cout << "编号：" << c.second << " 姓名：" << this->m_Speaker[c.second].m_Name
					<< " 成绩：" << this->m_Speaker[c.second].m_Score[this->m_Index - 1] << endl;
			}
			//取走前三名
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; count++, it++) {
				if (this->m_Index == 1) {
					v2.push_back((*it).second);
				}
				else {
					Victory.push_back((*it).second);
				}
			}
			groupScore.clear();
			cout << endl;
		}
	}
	cout << "--------------第" << this->m_Index << "轮比赛完毕---------------" << endl;
}
void SpeechManager::showScore() {
	cout << "-------------第" << this->m_Index << "轮晋级选手信息如下---------" << endl;
	if (this->m_Index == 1) {
		for (auto c : this->v2) {
			cout << "编号：" << c << " 姓名" << this->m_Speaker[c].m_Name << " 得分" <<
			this->m_Speaker[c].m_Score[this->m_Index - 1] << endl;
		}
	}
	else {
		cout << "冠军编号：" << Victory.at(0) << " 姓名;" << this->m_Speaker[Victory.at(0)].m_Name
		<< " 得分：" << this->m_Speaker[Victory.at(0)].m_Score[this->m_Index - 1] << endl
		<< "亚军编号：" << Victory.at(1) << " 姓名;" << this->m_Speaker[Victory.at(1)].m_Name
		<< " 得分：" << this->m_Speaker[Victory.at(1)].m_Score[this->m_Index - 1] << endl
		<< "季军编号：" << Victory.at(2) << " 姓名;" << this->m_Speaker[Victory.at(2)].m_Name
		<< " 得分：" << this->m_Speaker[Victory.at(2)].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
}
void SpeechManager::saveScore() {
	ofstream ofs;
	ofs.open("speech.txt", ios::out | ios::app);//用追加的方式写文件
	//将每个选手的数据写入到文件中
	ofs << "第" <<this->m_Session << "届演讲比赛结果如下" << endl
		<<"冠军编号：" << Victory.at(0) << " 姓名;" << this->m_Speaker[Victory.at(0)].m_Name
		<< " 得分：" << this->m_Speaker[Victory.at(0)].m_Score[this->m_Index - 1] << endl
		<< "亚军编号：" << Victory.at(1) << " 姓名;" << this->m_Speaker[Victory.at(1)].m_Name
		<< " 得分：" << this->m_Speaker[Victory.at(1)].m_Score[this->m_Index - 1] << endl
		<< "季军编号：" << Victory.at(2) << " 姓名;" << this->m_Speaker[Victory.at(2)].m_Name
		<< " 得分：" << this->m_Speaker[Victory.at(2)].m_Score[this->m_Index - 1] << endl;
	cout << endl;
	//关闭文件
	ofs.close();
	cout << "记录保存成功！" << endl;
	this->fileIsEmpty = false;
//	this->preRecord.insert(make_pair(m_Session, Victory));
	this->m_Session++;
	this->Victory.clear();
}
void SpeechManager::startSpeech() {//比赛整个流程控制函数
	//第一轮比赛
	this->m_Index=1;
	this->initSpeech();
	this->createSpeaker();
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示晋级结果
	this->showScore();
	//第二轮比赛
	++this->m_Index;
	//1.抽签
	this->speechDraw();
	//2.比赛
	this->speechContest();
	//3.显示最终结果
	this->showScore();
	//4.保存分数到文件中
	this->saveScore();
	cout << "本届比赛完毕！" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::loadScore() {
	ifstream ifs("speech.txt",ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "文件不存在！" << endl;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}
	//文件为空情况
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}
	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);//将上面读取的单个字符放回来 
	string data;
	while (getline(ifs,data)) {
		cout << data << endl;
	}
	ifs.close();
	system("pause");
	system("cls");
}
//void SpeechManager::showRecord() {
//	for (map<int, vector<int>>::iterator it = preRecord.begin(); it != preRecord.end(); it++) {
//		cout << "第" << it->first << "届演讲比赛结果如下" << endl <<
//			"冠军编号：" << it->second.at((it->first) * 3 - 3) <<
//			" 姓名：" << this->m_Speaker[it->second.at((it->first) * 3 - 3)].m_Name <<
//			" 得分：" << this->m_Speaker[it->second.at((it->first) * 3 - 3)].m_Score[1] << endl <<
//			"亚军编号：" << it->second.at((it->first) * 3 - 2) <<
//			" 姓名：" << this->m_Speaker[it->second.at((it->first) * 3 - 2)].m_Name <<
//			" 得分：" << this->m_Speaker[it->second.at((it->first) * 3 - 2)].m_Score[1] << endl <<
//			"季军编号：" << it->second.at((it->first) * 3 - 1) <<
//			" 姓名：" << this->m_Speaker[it->second.at((it->first) * 3 - 1)].m_Name <<
//			" 得分：" << this->m_Speaker[it->second.at((it->first) * 3 - 1)].m_Score[1] << endl;
//
//	}
//	system("pause");
//	system("cls");
//}
void SpeechManager::clearRecord() {
	cout << "确定清空？" << endl
		<< "1.是" << endl
		<< "2.否" << endl;
	while (true) {
		int select = _getch();
		if (select == '1') {
			ofstream ofs("speech.txt", ios::trunc);
			ofs.close();
			cout << "清空成功！" << endl;
			break;
		}
		else if (select == '2') {
			cout << "清空失败！" << endl;
			break;
		}
		else {
			cout << "错误输入，请重新输入：";
		}
	}
	system("pause");
	system("cls");
}
SpeechManager::~SpeechManager() {

}