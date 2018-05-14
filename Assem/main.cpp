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
		{//��Ʈ���� ���� �����Ҷ� ���� �ٸ��� �޾ƿ�
			string line;
			getline(is, line);
			string* temp = parseCode(line);//parseCode �� ������ �κкκ� ����
			makeCodeList(temp);//�ڵ帮��Ʈ�� ����
			cout << line << endl;
			//10���� : ���� end�� ���� ����
		if (codes.rbegin()->opcode == "end")break;
		}
		//Init
		InstructionStruct::initSizeInst();
		InstructionStruct::initOptable();

		list<InstructionStruct>::iterator iter;
		for (iter=codes.begin();iter!=codes.end();iter++)//auto *itr : codes)
		{//10���� : convertOpcode�� ���ؼ� hex_opcode�� ���� �־��ش�.
			iter->calAddress();
			iter->convertOpcode();
			iter->makeSymbolTable();
			cout << *iter << ' ' << endl;
		}
		//12���� SymbolTable ����ϱ�
		cout << "��������Symbol��Table����������" << endl;
		cout << "��    Label   ��  Address    ��" << endl;
		cout << "�������������� ����������������" << endl;
		for (auto itr : InstructionStruct::symbolTable)
		{
			cout << "��  " << setw(8)<<itr.first;//label
			cout<< setw(17)<<itr.second <<"��"<< endl;//
		}
		cout << "�������������� ����������������" << endl;
		
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
//12����  - hexOpcode: 00
//          hex_operand: 101e
//�̷������� ����ٲ���


static std::string* parseCode(std::string line)
{
	
	using namespace std;
	
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
		if (line.find(" ") !=string::npos )
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
		if (line.find(" ") != std::string::npos)
		{//�ǿ����� �������
			words[1] = line.substr(0, line.find(" "));
			line = line.substr(8, line.size());
			// 10���� : �ǿ������� ù��° ���ڰ� c�� x �϶� , ���� ó�����ش�.
			if (line[0] == 'c' || line[0] == 'x' || line[0] == 'C' || line[0] == 'X')
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
void makeCodeList(std::string* words)
{
	InstructionStruct newLine(words);
	codes.push_back(newLine);// push_back(newLine);
}
