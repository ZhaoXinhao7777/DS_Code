#include<iostream>
#include <iomanip>
#include<vector>
using namespace std;

class resource {//��Դ��
public:
	resource() {//����Ĭ��ֵ
		Max = 0;
		Allocation = 0;
		Need = 0;
	}
	int Max;
	int Allocation;
	int Need;
};

class process {//������
public:
	process() {//����Ĭ��ֵ
		isyfp = false;
	}
	vector<resource> res_vec;//��Դ����
	bool isyfp;//�Ƿ���Ԥ����
};

class System {//ϵͳ��
public:
	System();//Ĭ�Ϲ��캯��
	bool issafe();//��ȫ���㷨
	void print_System();//���ϵͳ��ǰ״̬
	void banker();//���м��㷨
	bool is_finish();
	bool is_workDneed(vector<int>work, int i);
	bool is_continue(vector<int>);
private:
	vector<process> pro_vec;//��������
	vector<int> res_sum;//ϵͳ���е���Դ����Ŀ
	vector<int> Available;
};

System::System()
{
	int pro_num, res_num;
	cout << "������ϵͳ�еĽ��̸���: ";
	cin >> pro_num;
	cout << endl;
	while (pro_num < 0) {
		cout << "������������ ����������: ";
		cin >> pro_num;
		cout << endl;
	}
	cout << "������ϵͳ�е���Դ������: ";
	cin >> res_num;
	cout << endl;
	while (res_num < 0) {
		cout << "������������ ����������: ";
		cin >> res_num;
		cout << endl;
	}
	for (int i = 0; i < res_num; i++) {
		cout << "������ϵͳ��" << char('A' + i) << "��Դ����: ";
		int m; cin >> m;
		cout << endl;
		while (m < 0) {
			cout << "������������ ����������: ";
			cin >> m;
			cout << endl;
		}
		res_sum.push_back(m);
		Available.push_back(m);
	}
	system("cls");
	for (int i = 0; i < pro_num; i++) {
		process pro;
		for (int j = 0; j < res_num; j++) {
			cout << "�������" << i << "������" << char('A' + j) << "��Դ��������(Max)�ͷ�����Ŀ(Allocation): ";
			resource res;
			cin >> res.Max >> res.Allocation;
			cout << endl;
			while (res.Max < 0 || res.Allocation < 0) {
				cout << "������������ ����������: ";
				cin >> res.Max >> res.Allocation;
				cout << endl;
			}
			while (res.Allocation > Available[j]) {
				cout << "ϵͳ��Դ������䣡 ���������������Ŀ: ";
				cin >> res.Allocation;
				cout << endl;
			}
			res.Need = res.Max - res.Allocation;
			pro.res_vec.push_back(res);
			Available[j] = Available[j] - res.Allocation;
		}
		pro_vec.push_back(pro);
	}
}

bool System::issafe()
{
	cout << "ϵͳ��ǰ״̬:\n";
	print_System();
	cout << "--------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < pro_vec.size(); i++)
		pro_vec[i].isyfp = false;
	vector<int>work;
	for (int i = 0; i < Available.size(); i++)
		work.push_back(Available[i]);
	//��ʼ��
	int t = res_sum.size();
	cout << '\t';
	cout << setw(t * 6) << "����" << setw(t * 6) << "Work" << setw(t * 6) << "Need" << setw(t * 6) << "Allocation" << setw(t * 6) << "work+Allocation";
	cout << endl;
	cout << "--------------------------------------------------------------------------------------------\n";
	//5 3 10 5 7 7 0 5 1 3 0 3 2 2 0 2 0 9 3 0 0 2 2 2 2 2 1 2 1 4 0 3 0 3 2

	//0 2 2 2
	//1 3 3 3
	//1 1 1 1
	vector<int>vec;
	while (is_continue(work) == true) {
		for (int i = 0; i < pro_vec.size(); i++) {
			if (pro_vec[i].isyfp == false && is_workDneed(work, i) == true) {
				vec.push_back(i);
				pro_vec[i].isyfp = true;
				cout << "\tprocess" << i << '\t';
				for (int k = 0; k < work.size(); k++)
					cout << setw(t * 2) << work[k];
				cout << "|";
				for (int k = 0; k < work.size(); k++)
					cout << setw(t * 2) << pro_vec[i].res_vec[k].Need;
				cout << "|";
				for (int k = 0; k < work.size(); k++)
					cout << setw(t * 2) << pro_vec[i].res_vec[k].Allocation;
				cout << "|";
				for (int k = 0; k < work.size(); k++)
					work[k] += pro_vec[i].res_vec[k].Allocation;
				for (int k = 0; k < work.size(); k++)
					cout << setw(t * 2) << work[k];
				cout << endl;
				break;
			}//if
		}//for
	}//while
	cout << "--------------------------------------------------------------------------------------------\n";
	if (is_finish())
	{
		cout << "ϵͳ��ȫ!\n" << endl;
		cout << "��ȫ����Ϊ��";
		int j = 0;
		for (; j < vec.size() - 1; j++)
			cout << "process" << vec[j] << "---->";
		cout << "process" << vec[j] << endl;
		return true;
	}
	else {
		cout << "ϵͳ����ȫ!,���������,���н���������Դ�޷�����\n" << endl;
		for (int j = 0; j < pro_vec.size(); j++) {
			if (pro_vec[j].isyfp == false) {
				cout << "process" << j << "  ";
			}
		}return false;
	}
}

void System::print_System()
{
	cout << "   Available:\t";
	for (int i = 0; i < Available.size(); i++)
		cout << char('A' + i) << " :" << Available[i] << '\t';
	cout << endl;
	cout << left;
	int t = res_sum.size();
	cout << '\t';
	cout << setw(t * 6) << "����" << setw(t * 6) << "Max" << setw(t * 6) << "Allocation" << setw(t * 6) << "Need";
	cout << endl;
	cout << "--------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < pro_vec.size(); i++) {
		cout << "\tprocess" << i << '\t';
		for (int j = 0; j < pro_vec[i].res_vec.size(); j++)
			cout << setw(t * 2) << pro_vec[i].res_vec[j].Max;
		cout << "|";
		for (int j = 0; j < pro_vec[i].res_vec.size(); j++)
			cout << setw(t * 2) << pro_vec[i].res_vec[j].Allocation;
		cout << "|";
		for (int j = 0; j < pro_vec[i].res_vec.size(); j++)
			cout << setw(t * 2) << pro_vec[i].res_vec[j].Need;
		cout << endl;
	}
	cout << "--------------------------------------------------------------------------------------------\n";
}

void System::banker()
{
	vector<int> request;
	if (!issafe())return;
	cout << "������Ҫ���������Ľ�����ţ�\n";
	int n; cin >> n;
	for (int i = 0; i < res_sum.size(); i++) {
		cout << "���������Դ" << char('A' + i) << "������������ ";
		int m; cin >> m;
		cout << endl;
		while (m < 0) {
			cout << "������������ ����������: ";
			cin >> m;
			cout << endl;
		}
		if (m > pro_vec[n].res_vec[i].Need) {
			cout << "Request����Ƿ���----�������Դ����������������(Need)\n";
			return;
		}
		request.push_back(m);
	}
	for (int i = 0; i < res_sum.size(); i++) {
		if (request[i] > Available[i]) {
			cout << "Request>Available----û���㹻��Դ���䣬���̱���ȴ���\n";
			return;
		}
	}
	for (int i = 0; i < res_sum.size(); i++) {
		Available[i] -= request[i];
		pro_vec[n].res_vec[i].Allocation += request[i];
		pro_vec[n].res_vec[i].Need -= request[i];
	}
	if (issafe()) {
		cout << "����ɹ���\n";
	}
	else {
		cout << "����ʧ�ܣ�\n";
		for (int i = 0; i < res_sum.size(); i++) {
			Available[i] += request[i];
			pro_vec[n].res_vec[i].Allocation -= request[i];
			pro_vec[n].res_vec[i].Need += request[i];
		}
	}
	//����
	vector<vector<process>::iterator>v;
	for (vector<process>::iterator it = pro_vec.begin(); it != pro_vec.end(); it++) {
		bool judge = false;
		for (int j = 0; j < res_sum.size(); j++) {
			if (it->res_vec[j].Need != 0)
				judge = true;
		}//needȫΪ0��judgeΪfalse
		if (judge == false) {
			for (int k = 0; k < res_sum.size(); k++) {
				Available[k] += it->res_vec[k].Allocation;
			}
			v.push_back(it);
		}
	}
	for (int j = 0; j < v.size(); j++) {
		pro_vec.erase(v[j]);
	}
	return;
}

bool System::is_finish()
{
	for (int i = 0; i < pro_vec.size(); i++)
		if (pro_vec[i].isyfp == false)
			return false;
	return true;
}

bool System::is_workDneed(vector<int> work, int i)
{
	for (int j = 0; j < pro_vec[i].res_vec.size(); j++) {
		if (work[j] < pro_vec[i].res_vec[j].Need)
			return false;
	}
	return true;
}

bool System::is_continue(vector<int>work)
{
	for (int i = 0; i < pro_vec.size(); i++)
		if (pro_vec[i].isyfp == false && is_workDneed(work, i))
			return true;
	return false;
}

void menu() {
	cout << "\t\t|----------------------------------------|\n";
	cout << "\t\t|------------1.ִ�а�ȫ���㷨------------|\n";
	cout << "\t\t|------------2.���ϵͳ��ǰ״̬----------|\n";
	cout << "\t\t|------------3.��������µ�����----------|\n";
	cout << "\t\t|------------4.�˳�ϵͳ------------------|\n";
	cout << "\t\t|----------------------------------------|\n";
	cout << " \t\t������ִ�еĹ���: ";
}

int main() {
	System sys;
	int func = -1;
	while (func != 4) {
		system("cls");
		menu();
		cin >> func;
		cout << endl;
		switch (func)
		{
		case 1:
			sys.issafe();//ִ�а�ȫ���㷨
			break;
		case 2:
			sys.print_System();//���ϵͳ��ǰ״̬
			break;
		case 3:
			sys.banker();//��������µ�����
			break;
		default:
			break;
		}
		system("pause");
	}
	return 0;
}
