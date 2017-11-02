#include "InstructionStruct.h"
#include <iostream>
int InstructionStruct::currentAddress = 0;
int InstructionStruct::startAddress = 0;
string InstructionStruct::sourceName = "0";
list<string> InstructionStruct::sizeInst = {};

InstructionStruct::InstructionStruct(string* words)
{
	this->label = words[0];
	this->opcode = words[1];
	this->operand = words[2];
}


void InstructionStruct::calAddress()
{
	//lda index ~ �̷��� �� ��ɾ 3byte �� ������

	if (this->opcode == "start")
	{
		InstructionStruct::sourceName = this->label;
		//start�� label�� �ҽ��ڵ��� �̸���
	    InstructionStruct::startAddress = stoi(this->operand, 0, 16);
		//�̰� ���ڿ��� �������ϱ� 16������ ��ȯ
		InstructionStruct::currentAddress = InstructionStruct::startAddress;
	}
	else if (find(begin(sizeInst), end(sizeInst), this->opcode) == end(sizeInst))
	{//find �� ���� sizeInst ��� ����Ʈ���� �� ������� this->opcode�� ���� Ȯ���ϴ°��� 
	//�״ϱ� resw resb �̷��� �ƴҶ� ���� ���°���
		//lda ldx ���� �Ϲ����� ��ɾ ���⼭ ó��
		this->address = this->currentAddress;
		this->currentAddress += 0x3;
		//3byte�� ����~
	}
	else
	{
		if (this->opcode == "resb")
		{
			this->address = this->currentAddress;
			this->currentAddress += 0x1 * stoi(this->operand);
			//1byte * �ڿ��ִ� ���ڸ�ŭ
			
		}
		else if (this->opcode == "resw")
		{
			this->address = this->currentAddress;
			this->currentAddress += 0x3 * stoi(this->operand);
		}
		else if (this->opcode == "word")
		{
			this->address = this->currentAddress;
			this->currentAddress += 0x3;
			//����� ���� �׳� 3��
		}
		else//this->opcode =="byte"��
		{//�ٵ� ��� �̰� str1 byte c'sdafas' �̷������� �� �� �����ڳ�..

			this->address = this->currentAddress;
			this->currentAddress += this->operand.substr(
				this->operand.find("'"),//ù���� ' ����
				this->operand.size() - this->operand.find("'")).size() - 2;
			//�� ' �����ε� �ֳװ� '' �̰� �ΰ� �����ϴϱ� -2 �ؼ� �־��ִ°�
		}
	}
}
void InstructionStruct::initSizeInst()
{
	InstructionStruct::sizeInst.push_back("resb");
	InstructionStruct::sizeInst.push_back("resw");
	InstructionStruct::sizeInst.push_back("word");
	InstructionStruct::sizeInst.push_back("byte");
}
/*
InstructionStruct::InstructionStruct(string* words)
{
	if (words[1] != "start")
	{
		this->label = words[0];
		this->opcode = words[1];
		this->operand = words[2];
		this->address = this->currentAddress;
		this->currentAddress += 0x3;
	}
	else
	{
		this->startAddress = stoi(words[2], 0, 16);
		this->currentAddress = this->startAddress;
	}
}
*/

std::ostream& operator<<(std::ostream &strm, const InstructionStruct &a) {
	return strm << "label=" << a.label << endl << "opcode="<<a.opcode<< endl<<"operand="<<a.operand<<endl<<"address="<<hex<<a.address<<endl;
}

InstructionStruct::~InstructionStruct()
{
}
