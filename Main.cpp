#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <algorithm>

using namespace std;

struct Birthday {
	string nameDate;
	int sortDate;
};

bool cmp(Birthday a, Birthday b) {
	return a.sortDate < b.sortDate;
}

int Datetoint(string Date) {
	string date1 = Date.substr(0, 2), date2 = Date.substr(5, 2);
	return (stoi(date1) * 100) + stoi(date2);
}

void textcolor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

struct Birthday b[1000]; //����ü �迭 ����

int main()
{
	int i = 0, findDataB = 0, namelen = 0;;
	string fileName, s, name;

	while (1) {
		textcolor(15);
		cout << "���� �� : "; 
		textcolor(10);
		cout << "û��";
		textcolor(15);
		cout << endl
			 << "������ ������ ���� ���ϰ� ���� �������� �������ּ���." << endl
			 << "������ �ۼ��Ͻ� �� �̸�/01�� 30�� �� ��� ����ִ� �� ���� ANSI�� �������ּž� ���������� �۵��մϴ�." << endl
			 << "�̸��� 2 ~ 3 ���ڷ� �ۼ����ּ���." << endl
			 << "�� ���� �� �ܼ� â�� ���� ����� ������� ���ð� ���� ������ �ִ� �����̸�(Edit).txt �� �ִ� ���� ��� �����Ͽ� ������ּ���." << endl << endl;

		cout << "���� �̸��� �Է����ּ��� : ";
		cin >> fileName;

		ifstream IFile(fileName + ".txt");

		if (IFile.is_open()) {
			ofstream OFile(fileName + "(Edit).txt");

			cout << fileName << " ������ ã�ҽ��ϴ�.\n\n";
			while (!IFile.eof()) {
				s.clear(); //������ ���� �ʱ�ȭ

				getline(IFile, s); //���� �޾ƿ���

				findDataB = s.find("/"); //���ڿ����� / ã�� (���ϰ� �̸��� ����)

				name = s.substr(0, findDataB);

				namelen = name.length(); //�̸��� ���̸� �˾Ƴ���
				if (namelen == 4)
					name += "��";

				b[i].nameDate = "<" + name + "> " + s.substr(findDataB + 1, findDataB + 5);
				b[i].sortDate = Datetoint(s.substr(findDataB + 1, findDataB + 5));

				i++;
			}

			sort(b, b + i, cmp); //���Ϻ��� ����

			OFile << "```diff" << endl; //���
			for (int j = 0; j < i; j++) { 
				(j % 2 == 0 ? textcolor(10) : textcolor(12));
				cout << b[j].nameDate << endl;
				OFile << (j % 2 == 0 ? "+" : "-") << b[j].nameDate << endl;
			}
			OFile << "```" << endl;

			textcolor(15);
			cout << endl;

			break;
		}
		else {
			system("cls");
			textcolor(4);
			cout << "\a�ش� �̸��� txt ������ ã�� �� �����ϴ�. \n\n";
		}
	}

	system("pause");
}