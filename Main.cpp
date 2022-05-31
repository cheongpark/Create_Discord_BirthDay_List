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

struct Birthday b[1000]; //구조체 배열 생성

int main()
{
	int i = 0, findDataB = 0, namelen = 0;;
	string fileName, s, name;

	while (1) {
		textcolor(15);
		cout << "만든 이 : "; 
		textcolor(10);
		cout << "청박";
		textcolor(15);
		cout << endl
			 << "무조건 파일은 실행 파일과 같은 폴더에서 실행해주세요." << endl
			 << "생일을 작성하실 땐 이름/01월 30일 로 적어서 비어있는 줄 없이 ANSI로 저장해주셔야 정상적으로 작동합니다." << endl
			 << "이름은 2 ~ 3 글자로 작성해주세요." << endl
			 << "꼭 실행 후 콘솔 창의 생일 목록을 사용하지 마시고 실행 폴더에 있는 파일이름(Edit).txt 에 있는 것을 모두 복사하여 사용해주세요." << endl << endl;

		cout << "파일 이름을 입력해주세요 : ";
		cin >> fileName;

		ifstream IFile(fileName + ".txt");

		if (IFile.is_open()) {
			ofstream OFile(fileName + "(Edit).txt");

			cout << fileName << " 파일을 찾았습니다.\n\n";
			while (!IFile.eof()) {
				s.clear(); //한줄의 변수 초기화

				getline(IFile, s); //한줄 받아오기

				findDataB = s.find("/"); //문자열에서 / 찾기 (생일과 이름을 구분)

				name = s.substr(0, findDataB);

				namelen = name.length(); //이름의 길이를 알아내기
				if (namelen == 4)
					name += "님";

				b[i].nameDate = "<" + name + "> " + s.substr(findDataB + 1, findDataB + 5);
				b[i].sortDate = Datetoint(s.substr(findDataB + 1, findDataB + 5));

				i++;
			}

			sort(b, b + i, cmp); //생일별로 정렬

			OFile << "```diff" << endl; //출력
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
			cout << "\a해당 이름의 txt 파일을 찾을 수 없습니다. \n\n";
		}
	}

	system("pause");
}