#include"speechManager.h"

SpeechManager::SpeechManager(){
	this->initSpeech();
	this->m_Session = 1;
}
void SpeechManager::showMenu() {
	cout << "**************************************" << endl
		<<"************��ӭ�μ��ݽ�����**********" << endl
		<<"************1.��ʼ�ݽ�����************" << endl
		<<"************2.�鿴�����¼************" << endl
		<<"************3.��ձ�����¼************" << endl
		<<"************0.�˳���������************" << endl;
	cout << endl;
}
void SpeechManager::exitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
void SpeechManager::initSpeech() {
	//�������ÿ�
	this->v1.clear();
	this->v2.clear();
	this->Victory.clear();
	this->m_Speaker.clear();
	//��ʼ����������
	this->m_Index = 1;
	
}
void SpeechManager::createSpeaker() {
	string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		string name = "ѡ��";
		name += nameSeed[i];
		Speaker sp;
		sp.m_Name = name;
		for (int j = 0; j < 2; j++) {
			sp.m_Score[j] = 0;
		}
		//����ѡ�ֱ�ţ����ҷ��뵽v1������
		this->v1.push_back(i + 10001);
		//ѡ�ֱ���Լ���Ӧѡ�ַ��뵽map������
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}
void SpeechManager::speechDraw() {
	cout << "��" << this->m_Index << "�ֱ���ѡ�����ڳ�ǩ" << endl;
	cout << "------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_Index == 1) {
		//��һ�ֱ���
		random_shuffle(this->v1.begin(), this->v1.end());
		for (auto c : this->v1) {
			cout << c << " ";
		}
		cout << endl;
	}
	else {
		//�ڶ��ֱ���
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
	cout << "--------------��" << this->m_Index << "�ֱ�����ʽ��ʼ---------------" << endl;
	//׼����ʱ���������С��ɼ�
	multimap<double, int, greater<double>>groupScore;
	vector<int>v_Src;//���
	int num = 0;//6��һ��
	if (this->m_Index == 1) {
		v_Src = this->v1;
	}
	else {
		v_Src = this->v2;
	}
	//��������ѡ�ֽ��б���
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		++num;
		deque<double>d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;
			cout <<left<<setw(4)<< score << "  ";
			d.push_back(score);
		}
		sort(d.begin(), d.end(), greater<double>());
		d.pop_front();//ȥ����߷���ͷ�
		d.pop_back();
		double sum = accumulate(d.begin(), d.end(), 0.0f);
		double avg = sum / (double)d.size();
		//��ӡƽ����
		cout << "��ţ�" << *it << " ������" << m_Speaker[*it].m_Name
			<< " ��ȡ��ƽ����Ϊ��" << avg <<endl;
		//��ƽ���ַŵ�map������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;
		//��������ݷ��뵽��ʱС��������
		groupScore.insert(make_pair(avg, *it));//key�ǵ÷֣�value�Ǿ���ѡ�ֱ��	
		// 6��һ��
		if (num % 6 == 0) {
			cout << endl<<"��" << num/6 << "С�����������" << endl;
			for (auto c : groupScore) {
				cout << "��ţ�" << c.second << " ������" << this->m_Speaker[c.second].m_Name
					<< " �ɼ���" << this->m_Speaker[c.second].m_Score[this->m_Index - 1] << endl;
			}
			//ȡ��ǰ����
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
	cout << "--------------��" << this->m_Index << "�ֱ������---------------" << endl;
}
void SpeechManager::showScore() {
	cout << "-------------��" << this->m_Index << "�ֽ���ѡ����Ϣ����---------" << endl;
	if (this->m_Index == 1) {
		for (auto c : this->v2) {
			cout << "��ţ�" << c << " ����" << this->m_Speaker[c].m_Name << " �÷�" <<
			this->m_Speaker[c].m_Score[this->m_Index - 1] << endl;
		}
	}
	else {
		cout << "�ھ���ţ�" << Victory.at(0) << " ����;" << this->m_Speaker[Victory.at(0)].m_Name
		<< " �÷֣�" << this->m_Speaker[Victory.at(0)].m_Score[this->m_Index - 1] << endl
		<< "�Ǿ���ţ�" << Victory.at(1) << " ����;" << this->m_Speaker[Victory.at(1)].m_Name
		<< " �÷֣�" << this->m_Speaker[Victory.at(1)].m_Score[this->m_Index - 1] << endl
		<< "������ţ�" << Victory.at(2) << " ����;" << this->m_Speaker[Victory.at(2)].m_Name
		<< " �÷֣�" << this->m_Speaker[Victory.at(2)].m_Score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");
}
void SpeechManager::saveScore() {
	ofstream ofs;
	ofs.open("speech.txt", ios::out | ios::app);//��׷�ӵķ�ʽд�ļ�
	//��ÿ��ѡ�ֵ�����д�뵽�ļ���
	ofs << "��" <<this->m_Session << "���ݽ������������" << endl
		<<"�ھ���ţ�" << Victory.at(0) << " ����;" << this->m_Speaker[Victory.at(0)].m_Name
		<< " �÷֣�" << this->m_Speaker[Victory.at(0)].m_Score[this->m_Index - 1] << endl
		<< "�Ǿ���ţ�" << Victory.at(1) << " ����;" << this->m_Speaker[Victory.at(1)].m_Name
		<< " �÷֣�" << this->m_Speaker[Victory.at(1)].m_Score[this->m_Index - 1] << endl
		<< "������ţ�" << Victory.at(2) << " ����;" << this->m_Speaker[Victory.at(2)].m_Name
		<< " �÷֣�" << this->m_Speaker[Victory.at(2)].m_Score[this->m_Index - 1] << endl;
	cout << endl;
	//�ر��ļ�
	ofs.close();
	cout << "��¼����ɹ���" << endl;
	this->fileIsEmpty = false;
//	this->preRecord.insert(make_pair(m_Session, Victory));
	this->m_Session++;
	this->Victory.clear();
}
void SpeechManager::startSpeech() {//�����������̿��ƺ���
	//��һ�ֱ���
	this->m_Index=1;
	this->initSpeech();
	this->createSpeaker();
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ�������
	this->showScore();
	//�ڶ��ֱ���
	++this->m_Index;
	//1.��ǩ
	this->speechDraw();
	//2.����
	this->speechContest();
	//3.��ʾ���ս��
	this->showScore();
	//4.����������ļ���
	this->saveScore();
	cout << "���������ϣ�" << endl;
	system("pause");
	system("cls");
}
void SpeechManager::loadScore() {
	ifstream ifs("speech.txt",ios::in);
	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}
	//�ļ�Ϊ�����
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		system("pause");
		system("cls");
		return;
	}
	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);//�������ȡ�ĵ����ַ��Ż��� 
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
//		cout << "��" << it->first << "���ݽ������������" << endl <<
//			"�ھ���ţ�" << it->second.at((it->first) * 3 - 3) <<
//			" ������" << this->m_Speaker[it->second.at((it->first) * 3 - 3)].m_Name <<
//			" �÷֣�" << this->m_Speaker[it->second.at((it->first) * 3 - 3)].m_Score[1] << endl <<
//			"�Ǿ���ţ�" << it->second.at((it->first) * 3 - 2) <<
//			" ������" << this->m_Speaker[it->second.at((it->first) * 3 - 2)].m_Name <<
//			" �÷֣�" << this->m_Speaker[it->second.at((it->first) * 3 - 2)].m_Score[1] << endl <<
//			"������ţ�" << it->second.at((it->first) * 3 - 1) <<
//			" ������" << this->m_Speaker[it->second.at((it->first) * 3 - 1)].m_Name <<
//			" �÷֣�" << this->m_Speaker[it->second.at((it->first) * 3 - 1)].m_Score[1] << endl;
//
//	}
//	system("pause");
//	system("cls");
//}
void SpeechManager::clearRecord() {
	cout << "ȷ����գ�" << endl
		<< "1.��" << endl
		<< "2.��" << endl;
	while (true) {
		int select = _getch();
		if (select == '1') {
			ofstream ofs("speech.txt", ios::trunc);
			ofs.close();
			cout << "��ճɹ���" << endl;
			break;
		}
		else if (select == '2') {
			cout << "���ʧ�ܣ�" << endl;
			break;
		}
		else {
			cout << "�������룬���������룺";
		}
	}
	system("pause");
	system("cls");
}
SpeechManager::~SpeechManager() {

}