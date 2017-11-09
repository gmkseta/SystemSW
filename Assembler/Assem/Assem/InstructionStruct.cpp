#include "InstructionStruct.h"
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
int InstructionStruct::currentAddress = 0;
int InstructionStruct::startAddress = 0;
string InstructionStruct::sourceName = "0";
list<string> InstructionStruct::sizeInst = {};
list<InstructionStruct::SIC_OPTAB> InstructionStruct::sic_optable = {};

InstructionStruct::InstructionStruct(string* words)
{
	this->label = words[0];
	this->opcode = words[1];
	this->operand = words[2];
}


void InstructionStruct::calAddress()
{

	if (this->label[0] == '.')//pr
		return;

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
		//lda ldx ���� �Ϲ����� ��ɾ ���⼭ ó��
		this->address = this->currentAddress;
		this->currentAddress += 0x3;
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


void InstructionStruct::initOptable()
{
	InstructionStruct::sic_optable.push_back({ "ADD"	,3		,0X18 });
	InstructionStruct::sic_optable.push_back({ "AND"	,3		,0X40 });
	InstructionStruct::sic_optable.push_back({ "COMP"	,3		,0X28 });
	InstructionStruct::sic_optable.push_back({ "DIV "   ,3		,0X24 });
	InstructionStruct::sic_optable.push_back({ "J"      ,3		,0X3C });
	InstructionStruct::sic_optable.push_back({ "JEQ"    ,3		,0X30 });
	InstructionStruct::sic_optable.push_back({ "JGT"    ,3		,0X34 });
	InstructionStruct::sic_optable.push_back({ "JLT"    ,3		,0X38 });
	InstructionStruct::sic_optable.push_back({ "JSUB"   ,3		,0X48 });
	InstructionStruct::sic_optable.push_back({ "LDA"    ,3		,0X00 });
	InstructionStruct::sic_optable.push_back({ "LDCH"   ,3		,0X50 });
	InstructionStruct::sic_optable.push_back({ "LDL"    ,3		,0X08 });
	InstructionStruct::sic_optable.push_back({ "LDX"    ,3		,0X04 });
	InstructionStruct::sic_optable.push_back({ "MUL "   ,3		,0X20 });
	InstructionStruct::sic_optable.push_back({ "OR"		,3		,0X44 });
	InstructionStruct::sic_optable.push_back({ "RD"	    ,3		,0XD8 });
	InstructionStruct::sic_optable.push_back({ "RSUB"   ,3		,0X4C });
	InstructionStruct::sic_optable.push_back({ "STA"    ,3		,0X0C });
	InstructionStruct::sic_optable.push_back({ "STCH"   ,3		,0X54 });
	InstructionStruct::sic_optable.push_back({ "STL"    ,3		,0X14 });
	InstructionStruct::sic_optable.push_back({ "STSW"   ,3		,0XE8 });
	InstructionStruct::sic_optable.push_back({ "STX"    ,3		,0X10 });
	InstructionStruct::sic_optable.push_back({ "SUB"    ,3		,0X1C });
	InstructionStruct::sic_optable.push_back({ "TD"     ,3		,0XE0 });
	InstructionStruct::sic_optable.push_back({ "TIX"    ,3		,0X2C });
	InstructionStruct::sic_optable.push_back({ "WD"     ,3		,0XDC });	
}
void InstructionStruct::convertOpcode()
{
	transform(this->opcode.begin(), this->opcode.end(), this->opcode.begin(), toupper);    // s�� �빮�ڷ� ����
	for (auto itr : sic_optable) {
		if (this->opcode == itr.Mnemonic)
		{
			hex_opcode = itr.MachineCode;
			break;
		}
		else
			hex_opcode = -1;
	}
}

void InstructionStruct::convertHexToStr()
{
}
std::ostream& operator<<(std::ostream &strm, const InstructionStruct &a) {
	if (a.label[0] == '.')
		return strm << "�ּ�:" << a.label << endl;//pr
	else if(a.hex_opcode==-1)
		return strm << "label=" << a.label << "��" << endl << "opcode=" << a.opcode << "��" << endl << "operand=" << a.operand << "��" << endl << "address=" << hex << a.address << "��" << endl;
		//return strm << "label=" << a.label << endl << "opcode=" << a.opcode << endl << "operand=" << a.operand << endl << "address=" << hex << a.address << endl ;
	else
		return strm << "label=" << a.label << "��" << endl << "opcode=" << a.opcode << "��" << endl << "operand=" << a.operand << "��" << endl << "address=" << hex << a.address << "��" << endl;
		//return strm << "label=" << a.label << endl << "opcode=" << a.opcode << endl << "operand=" << a.operand << endl << "address=" << hex << a.address << endl << "HexOpcode="  << a.hex_opcode << endl;
}





InstructionStruct::~InstructionStruct()
{
}
