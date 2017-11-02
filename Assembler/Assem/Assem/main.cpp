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
	//���� �Է� �޾Ƽ� ��
	string fileName;
	cin >> fileName;
	ifstream is(fileName);

	if (is.is_open())
	{//���� �����ϴ��� Ȯ��
		while (!is.eof())
		{//��Ʈ���� ���� �����Ҷ� ���� �ٸ��� �޾ƿ�
			string line;
			getline(is, line);
			string* temp = parseCode(line);//parseCode �� �Ʒ��Լ�
			//3���� ���� ������ �迭�� ���ò���

			makeCodeList(temp);
			//�ڵ帮��Ʈ�� ����

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
	{//������ �޼���
		cout << "file does not exist"<<endl;
	}
}

static string* parseCode(string line)
{
	string* words = new string[3];
	if (line.find(" ") == 0)
	{//��ó���� �����̸� Label�� ���°��� 
		words[0] = "";
		//�׷��� ù���� �迭�� �������� ��

		line = line.substr(9, line.size() - 9);
		//10��° ���� �߶� (Operator �� 10��° �ٺ��� �����ϴϱ�
		if (line.find(" ") != string::npos)
		{//�׸��� ���� ��ɾ ���� �ǿ����ڰ� �������
			words[1] = line.substr(0, line.find(" "));
			//���� ã���� ���� ����, �۰� ���� �̸��̶�� �����ϸ�� 
			//0~ ���� ���������� ��
			//�׷��� �ڿ� index �����ؼ� line.find(" ")+1 �ϸ� �ȴ�
			line = line.substr(8, line.size());
			//�Ȱ��� �ڸ�
			words[2] = line;
			//����

		}
		else
		{//���� ��� ex) rsub
			words[1] = line;
			words[2] = "";
		}

		return words;
	}
	else
	{
		words[0] = line.substr(0, line.find(" "));
		//���� ������� �߶��ְ�
		//first     ldx      index
		//word[0]�� first�� ���°���

		line = line.substr(9, line.size() - 9);
		//ldx      index
		//�� �ڿ� ���� �������
		if (line.find(" ") != string::npos)
		{//���� ����
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