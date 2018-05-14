#include <iostream>
#include <fstream>
#include <algorithm>
#include "InstructionStruct.h"
#include <iomanip>

static std::string* parseCode(std::string line);
static void makeCodeList(std::string* words);
std::list<InstructionStruct> codes;
int main()
{
	using namespace std;
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
			makeCodeList(temp);//코드리스트에 넣음
			cout << line << endl;
			//10주차 : 만약 end면 루프 나감
		if (codes.rbegin()->opcode == "end")break;
		}
		//Init
		InstructionStruct::initSizeInst();
		InstructionStruct::initOptable();

		list<InstructionStruct>::iterator iter;
		for (iter=codes.begin();iter!=codes.end();iter++)//auto *itr : codes)
		{//10주차 : convertOpcode를 통해서 hex_opcode에 값을 넣어준다.
			iter->calAddress();
			iter->convertOpcode();
			iter->makeSymbolTable();
			cout << *iter << ' ' << endl;
		}
		//12주차 SymbolTable 출력하기
		cout << "┏━━━Symbol┳Table━━━━┓" << endl;
		cout << "┃    Label   ┃  Address    ┃" << endl;
		cout << "┣━━━━━━ ━━━━━━━┫" << endl;
		for (auto itr : InstructionStruct::symbolTable)
		{
			cout << "┃  " << setw(8)<<itr.first;//label
			cout<< setw(17)<<itr.second <<"┃"<< endl;//
		}
		cout << "┗━━━━━━ ━━━━━━━┛" << endl;
		
		for (auto itr : codes)
		{
			cout.flags(ios::left);
			cout<<setw(10) << itr.label <<setw(10) << itr.opcode << setw(20) << itr.operand <<"   ";
			itr.printHexOperand();
			cout << endl;

		}
	}
	else { cout << "file does not exist" << endl; }
}
//12주차  - hexOpcode: 00
//          hex_operand: 101e
//이런식으로 찍어줄꺼임


static std::string* parseCode(std::string line)
{
	
	using namespace std;
	
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
		if (line.find(" ") !=string::npos )
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
		if (line.find(" ") != std::string::npos)
		{//피연산자 있을경우
			words[1] = line.substr(0, line.find(" "));
			line = line.substr(8, line.size());
			// 10주차 : 피연산자의 첫번째 문자가 c나 x 일때 , 따로 처리해준다.
			if (line[0] == 'c' || line[0] == 'x' || line[0] == 'C' || line[0] == 'X')
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
void makeCodeList(std::string* words)
{
	InstructionStruct newLine(words);
	codes.push_back(newLine);// push_back(newLine);
}
