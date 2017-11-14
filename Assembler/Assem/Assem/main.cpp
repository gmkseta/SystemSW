#include <iostream>
#include <fstream>
#include <algorithm>
#include "InstructionStruct.h"
using namespace std;
static string* parseCode(string line);
static void makeCodeList(string* words);
//map<int, InstructionStruct> codes;
list<InstructionStruct> codes;
int main()
{
	string fileName;
	cin >> fileName;
	ifstream is(fileName);
	if (is.is_open())
	{//file exist
		while (!is.eof())
		{//스트림의 끝에 도달할때 까지 줄마다 받아옴
			string line;
			getline(is, line);
			string* temp = parseCode(line);//parseCode 로 라인을 부분부분 나눔
			//3개의 문장 배열로 나올꺼임
			makeCodeList(temp);
			//코드리스트에 넣음
			cout << line << endl;
			//10주차 : 만약 end면 루프 나감
			if (codes.rbegin()->opcode == "end")break;
		}
		//Init
		InstructionStruct::initSizeInst();
		//10주차 : InitOptable 을 호출하여 opTable을 초기화한다.
		InstructionStruct::initOptable();
		for (auto itr : codes)
		{//10주차 : convertOpcode를 통해서 hex_opcode에 값을 넣어준다.
			itr.calAddress();
			itr.convertOpcode();
			cout << itr << ' ' << endl;
		}
	}
	else
		cout << "file does not exist"<<endl;
}
static string* parseCode(string line)
{
	string* words = new string[3];
	if (line.find(".") == 0)
		words[0] = line;////10주차 : 만약 주석이면 line다넣음
	else if (line.find(" ") == 0)
	{////  Label이 없을  때
		words[0] = "";
		//그래서 첫번쨰 배열을 공백으로 줌
		line = line.substr(9, line.size() - 9);
		//10번째 부터 잘라냄 (Operator 가 10번째 줄부터 시작하니까
		//피연산자(operand)가 있을경우
		if (line.find(" ") != string::npos)
		{
			words[1] = line.substr(0, line.find(" "));
			//0~ 공백 이전까지가 들어감
			line = line.substr(8, line.size());
			// 10주차 : 뒤에 공백 자르고 넣음
			line = line.substr(0, line.find(" "));
			words[2] = line;
		}		
		else
		{//operand가 없을 경우 ex) rsub
			words[1] = line;
			words[2] = "";
		}
		return words;
	}
	//Label 있을 떄
	else
	{	//Label 넣음
		words[0] = line.substr(0, line.find(" "));
		line = line.substr(9, line.size() - 9);
		if (line.find(" ") != string::npos)
		{//피연산자 있을경우
			words[1] = line.substr(0, line.find(" "));
			line = line.substr(8, line.size());
			// 10주차 : 피연산자의 첫번째 문자가 c나 x 일때 , 따로 처리해준다.
			if (line[0] == 'c' || line[0] == 'x')
			{//' 가 마지막으로 있는 곳 까지 짜룸. (find_last_of)
				line = line.substr(0, line.find_last_of("'") + 1);
			}
			else//특별한 점이 없으면 공백 있는곳까지 자름
				line = line.substr(0, line.find(" "));
			words[2] = line;
		}
		else
		{//피연산자가 없을 경우
			words[1] = line;
			words[2] = "";
		}
	}
	return words;
}
void makeCodeList(string* words)
{
	InstructionStruct newLine(words);
	codes.push_back(newLine);
}
