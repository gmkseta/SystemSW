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
	//직접 입력 받아서 함
	string fileName;
	cin >> fileName;
	ifstream is(fileName);

	if (is.is_open())
	{//파일 존재하는지 확인
		while (!is.eof())
		{//스트림의 끝에 도달할때 까지 줄마다 받아옴
			string line;
			getline(is, line);
			string* temp = parseCode(line);//parseCode 는 아래함수
			//3개의 문장 ㅇㅅㅇ 배열로 나올꺼임

			makeCodeList(temp);
			//코드리스트에 넣음

			cout << line << endl;
		}
		InstructionStruct::initSizeInst();
		list<InstructionStruct>::iterator iter;
		for (iter = codes.begin(); iter != codes.end(); iter++)
		{
			iter->calAddress();
			cout << *iter << ' ' << endl;
		}
	    
		/*
		for (auto const& x : codes)
		{
			std::cout <<hex<< x.first  // string (key)
				<< ':'
				<< x.second // string's value 
				<< std::endl;
		}
		*/
	}
	else
	{//없으면 메세지
		cout << "file does not exist"<<endl;
	}
}

static string* parseCode(string line)
{
	string* words = new string[3];
	if (line.find(" ") == 0)
	{//맨처음이 공백이면 Label이 없는거임 
		words[0] = "";
		//그래서 첫번쨰 배열을 공백으로 줌

		line = line.substr(9, line.size() - 9);
		//10번째 부터 잘라냄 (Operator 가 10번째 줄부터 시작하니까
		if (line.find(" ") != string::npos)
		{//그리고 만약 명령어가 있을 피연산자가 있을경우
			words[1] = line.substr(0, line.find(" "));
			//공백 찾을때 까지 ㅇㅇ, 글고 저기 미만이라고 생각하면됨 
			//0~ 공백 이전까지가 들어감
			//그래서 뒤에 index 생각해서 line.find(" ")+1 하면 안댐
			line = line.substr(8, line.size());
			//똑같이 자름
			words[2] = line;
			//넣음

		}
		else
		{//없을 경우 ex) rsub
			words[1] = line;
			words[2] = "";
		}

		return words;
	}
	else
	{
		words[0] = line.substr(0, line.find(" "));
		//다음 공백까지 잘라주고
		//first     ldx      index
		//word[0]에 first가 들어가는거임

		line = line.substr(9, line.size() - 9);
		//ldx      index
		//아 뒤에 저게 사이즈네
		if (line.find(" ") != string::npos)
		{//위랑 같음
			words[1] = line.substr(0, line.find(" "));
			line = line.substr(8, line.size());
			words[2] = line;
		}
		else
		{
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

/*
void insertCode(string* words)
{
	InstructionStruct newLine(words);
	if (words[1] != "start")
	{
		codes.insert(pair<int, InstructionStruct>(newLine.address, newLine));
	}
}
*/