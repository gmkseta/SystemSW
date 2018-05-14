#include "InstructionStruct.h"
#include <iostream>
#include <fstream>
#include <algorithm>


using namespace std;
static string* parseCode(string line);
static void makeCodeList(string* word);
list<InstructionStruct> codes;

int main()
{
	string fileName;
	cin >> fileName;
	ifstream is(fileName);
	if (is.is_open())
	{
		while (!is.eof())
		{
			string line;
			getline(is, line);
			transform(line.begin(), line.end(), line.begin(), ::toupper);//대문자로 만들기
			
			string* temp = parseCode(line);//ParseCode로 라인을 부분부분 나눔
			makeCodeList(temp);//코드 리스트에 넣음
			cout << line << endl;
			if (codes.rbegin()->opcode == "END") break;
		}


	}
	else cout << "file does not exist" << endl;

	return 0;

}

string* parseCode(string line)
{
	string* words = new string[3];
	if (line.find(".") == 0)
		words[0] = line;//주석이면 그냥 다때려박아넣어
	else if (line.find(" ") == 0)
	{//Label이 없을때
		words[0] = "";
		//첫 배열은 공백
		line = line.substr(9, line.size() - 9);
		//10번째부터 ~ 잘라냄 ( Operator 가 10번쨰 부터임
		//피 연산자가 있을 경우 (Operand)
		if (line.find(" ") != string::npos)
		{
			words[1] = line.substr(0, line.find(" "));//0번부터 공백 이전까지~
			line = line.substr(8, line.size());//다시 자르고
			line = line.substr(0, line.find(" "));
			words[2] = line;
		}
		else
		{//operand 가 없을 경우 ex)rsub 같은거 이므로
			words[1] = line;
			words[2] = "";
		}
	}
	else //label이 있음
	{
		words[0] = line.substr(0, line.find(" "));
		line = line.substr(9, line.size() - 9);
		if (line.find(" ") != string::npos)
		{//피연산자 있을 경우
			words[1] = line.substr(0, line.find(" "));
			line = line.substr(8, line.size());
			//피연산자의 첫 문자가 c나 x일때 따로 처리한다.
			if (line[0] == 'C' || line[0] == 'X')
				line = line.substr(0, line.find_last_of("'") + 1);
			else
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