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
		{//��Ʈ���� ���� �����Ҷ� ���� �ٸ��� �޾ƿ�
			string line;
			getline(is, line);
			string* temp = parseCode(line);//parseCode �� ������ �κкκ� ����
			//3���� ���� �迭�� ���ò���
			makeCodeList(temp);
			//�ڵ帮��Ʈ�� ����
			cout << line << endl;
			//10���� : ���� end�� ���� ����
			if (codes.rbegin()->opcode == "end")break;
		}
		//Init
		InstructionStruct::initSizeInst();
		//10���� : InitOptable �� ȣ���Ͽ� opTable�� �ʱ�ȭ�Ѵ�.
		InstructionStruct::initOptable();
		for (auto itr : codes)
		{//10���� : convertOpcode�� ���ؼ� hex_opcode�� ���� �־��ش�.
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
		words[0] = line;////10���� : ���� �ּ��̸� line�ٳ���
	else if (line.find(" ") == 0)
	{////  Label�� ����  ��
		words[0] = "";
		//�׷��� ù���� �迭�� �������� ��
		line = line.substr(9, line.size() - 9);
		//10��° ���� �߶� (Operator �� 10��° �ٺ��� �����ϴϱ�
		//�ǿ�����(operand)�� �������
		if (line.find(" ") != string::npos)
		{
			words[1] = line.substr(0, line.find(" "));
			//0~ ���� ���������� ��
			line = line.substr(8, line.size());
			// 10���� : �ڿ� ���� �ڸ��� ����
			line = line.substr(0, line.find(" "));
			words[2] = line;
		}		
		else
		{//operand�� ���� ��� ex) rsub
			words[1] = line;
			words[2] = "";
		}
		return words;
	}
	//Label ���� ��
	else
	{	//Label ����
		words[0] = line.substr(0, line.find(" "));
		line = line.substr(9, line.size() - 9);
		if (line.find(" ") != string::npos)
		{//�ǿ����� �������
			words[1] = line.substr(0, line.find(" "));
			line = line.substr(8, line.size());
			// 10���� : �ǿ������� ù��° ���ڰ� c�� x �϶� , ���� ó�����ش�.
			if (line[0] == 'c' || line[0] == 'x')
			{//' �� ���������� �ִ� �� ���� ¥��. (find_last_of)
				line = line.substr(0, line.find_last_of("'") + 1);
			}
			else//Ư���� ���� ������ ���� �ִ°����� �ڸ�
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
