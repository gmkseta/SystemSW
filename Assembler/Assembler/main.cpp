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
			transform(line.begin(), line.end(), line.begin(), ::toupper);//�빮�ڷ� �����
			
			string* temp = parseCode(line);//ParseCode�� ������ �κкκ� ����
			makeCodeList(temp);//�ڵ� ����Ʈ�� ����
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
		words[0] = line;//�ּ��̸� �׳� �ٶ����ھƳ־�
	else if (line.find(" ") == 0)
	{//Label�� ������
		words[0] = "";
		//ù �迭�� ����
		line = line.substr(9, line.size() - 9);
		//10��°���� ~ �߶� ( Operator �� 10���� ������
		//�� �����ڰ� ���� ��� (Operand)
		if (line.find(" ") != string::npos)
		{
			words[1] = line.substr(0, line.find(" "));//0������ ���� ��������~
			line = line.substr(8, line.size());//�ٽ� �ڸ���
			line = line.substr(0, line.find(" "));
			words[2] = line;
		}
		else
		{//operand �� ���� ��� ex)rsub ������ �̹Ƿ�
			words[1] = line;
			words[2] = "";
		}
	}
	else //label�� ����
	{
		words[0] = line.substr(0, line.find(" "));
		line = line.substr(9, line.size() - 9);
		if (line.find(" ") != string::npos)
		{//�ǿ����� ���� ���
			words[1] = line.substr(0, line.find(" "));
			line = line.substr(8, line.size());
			//�ǿ������� ù ���ڰ� c�� x�϶� ���� ó���Ѵ�.
			if (line[0] == 'C' || line[0] == 'X')
				line = line.substr(0, line.find_last_of("'") + 1);
			else
				line = line.substr(0, line.find(" "));
			words[2] = line;
		}
		else
		{//�ǿ����ڰ� ���� ���
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