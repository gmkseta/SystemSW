#include "InstructionStruct.h"
#include <iostream>
#include <cctype>
#include <algorithm>
using namespace std;

int InstructionStruct::currentAddress = 0;
int InstructionStruct::startAddress = 0;
string InstructionStruct::sourceName = "0";
list<string> InstructionStruct::sizeInst = {};
list<InstructionStruct::SIC_OPTAB> InstructionStruct::sic_optable = {};
map<string, int> InstructionStruct::symbolTable = {};

void InstructionStruct::calAddress()
{
	//주석일떄 주소 처리를 하지않음  
	if (this->label[0] == '.') return;
	if (this->opcode == "START")
	{
		InstructionStruct::sourceName = this->label;//start의 label이 소스코드의 이름
		InstructionStruct::startAddress = stoi(this->operand, 0, 16);//문자열을 16진수로 변환
		InstructionStruct::currentAddress = InstructionStruct::startAddress;
		this->address = this->currentAddress;
	}
	else if (find(begin(sizeInst), end(sizeInst), this->opcode) == end(sizeInst))
	{	//lda ldx 같은 일반적인 명령어 처리
		this->address = this->currentAddress;
		this->currentAddress += 0x3;
	}
	else
	{	//res
		if (this->opcode == "RESB")
		{
			this->address = this->currentAddress;
			this->currentAddress += 0x1 * stoi(this->operand);//1byte * 뒤에있는 숫자만큼
		}
		else if (this->opcode == "RESW")
		{
			this->address = this->currentAddress;
			this->currentAddress += 0x3 * stoi(this->operand);//3byte * 
		}
		else if (this->opcode == "WORD")
		{
			this->address = this->currentAddress;
			this->currentAddress += 0x3;//워드는 3
		}
		else//this->opcode =="byte"
		{
			this->address = this->currentAddress;
			this->currentAddress += this->operand.substr(
				this->operand.find("'"),//첫번쨰 ' 부터
				this->operand.size() - this->operand.find("'")).size() - 2;
			//끝 ' 까지인데 애네가 '' 이거 두개 포함하니까 -2 해서 넣어주는거
		}
	}
}
void InstructionStruct::initSizeInst()
{
	InstructionStruct::sizeInst.push_back("RESB");
	InstructionStruct::sizeInst.push_back("RESW");
	InstructionStruct::sizeInst.push_back("WORD");
	InstructionStruct::sizeInst.push_back("BYTE");
}


void InstructionStruct::initOptable()
{
	InstructionStruct::sic_optable.push_back({ "ADD"	,3		,0X18 });
	InstructionStruct::sic_optable.push_back({ "AND"	,3		,0X40 });
	InstructionStruct::sic_optable.push_back({ "COMP"	,3		,0X28 });
	InstructionStruct::sic_optable.push_back({ "DIV"    ,3		,0X24 });
	InstructionStruct::sic_optable.push_back({ "J"      ,3		,0X3C });
	InstructionStruct::sic_optable.push_back({ "JEQ"    ,3		,0X30 });
	InstructionStruct::sic_optable.push_back({ "JGT"    ,3		,0X34 });
	InstructionStruct::sic_optable.push_back({ "JLT"    ,3		,0X38 });
	InstructionStruct::sic_optable.push_back({ "JSUB"   ,3		,0X48 });
	InstructionStruct::sic_optable.push_back({ "LDA"    ,3		,0X00 });
	InstructionStruct::sic_optable.push_back({ "LDCH"   ,3		,0X50 });
	InstructionStruct::sic_optable.push_back({ "LDL"    ,3		,0X08 });
	InstructionStruct::sic_optable.push_back({ "LDX"    ,3		,0X04 });
	InstructionStruct::sic_optable.push_back({ "MUL"    ,3		,0X20 });
	InstructionStruct::sic_optable.push_back({ "OP"		,3		,0X44 });
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
	for (auto itr : sic_optable) {
		if (itr.Mnemonic.compare(this->opcode) == 0)
		{
			this->hex_opcode = itr.MachineCode;
			this->instruction_format = itr.Format;
			break;
		}
		else
			hex_opcode = -1;
	}
}


ostream& operator<<(ostream &strm, const InstructionStruct &a) {
	// 10주차 : 
	if (a.label[0] == '.')
		return strm << "주석:" << a.label.substr(1, a.label.size()) << endl;
	else if (a.hex_opcode == -1)
		return strm << "label=" << a.label << endl << "opcode=" << a.opcode << endl << "operand="
		<< a.operand << endl << "address=" << hex << a.address << endl;
	else
		return strm << "label=" << a.label << endl << "opcode=" << a.opcode << endl << "operand="
		<< a.operand << endl << "address=" << hex << a.address << endl << "HexOpcode=" << a.hex_opcode << endl;
}


void InstructionStruct::makeSymbolTable()
{
	if (this->label.compare("") != 0)
	{
		if (!InstructionStruct::symbolTable.count(this->label))
		{
			InstructionStruct::symbolTable.insert(pair<string, int>(this->label, this->address));
		}
	}
}
int InstructionStruct::convertHexOperand()
{
	if (symbolTable.find(this->operand) == symbolTable.end())
		return -1;
	else
		return symbolTable[this->operand];
}
void InstructionStruct::printHexOperand()
{
	if (convertHexOperand() != -1)
		cout << "hex_opcode:" <<hex<< this->hex_opcode << "     hex_operand:" << hex << convertHexOperand() << endl;
	else
		cout << "label address : " << hex << this->address << endl;
}
InstructionStruct::~InstructionStruct()
{
}

