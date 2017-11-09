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

	//lda index ~ 이런거 한 명령어가 3byte 라서 ㅇㅅㅇ

	if (this->opcode == "start")
	{
		InstructionStruct::sourceName = this->label;
		//start의 label이 소스코드의 이름임
	    InstructionStruct::startAddress = stoi(this->operand, 0, 16);
		//이게 문자열로 들어왔으니까 16진수로 변환
		InstructionStruct::currentAddress = InstructionStruct::startAddress;
	}
	else if (find(begin(sizeInst), end(sizeInst), this->opcode) == end(sizeInst))
	{//find 는 ㅇㅇ sizeInst 라는 리스트에서 이 멤버들이 this->opcode와 같나 확인하는거임 
		//lda ldx 같은 일반적인 명령어를 여기서 처리
		this->address = this->currentAddress;
		this->currentAddress += 0x3;
	}
	else
	{
		if (this->opcode == "resb")
		{
			this->address = this->currentAddress;
			this->currentAddress += 0x1 * stoi(this->operand);
			//1byte * 뒤에있는 숫자만큼
			
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
			//워드는 ㅇㅇ 그냥 3만
		}
		else//this->opcode =="byte"임
		{//근데 사실 이건 str1 byte c'sdafas' 이런식으로 들어갈 수 도있자나..

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
	transform(this->opcode.begin(), this->opcode.end(), this->opcode.begin(), toupper);    // s를 대문자로 변경
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
		return strm << "주석:" << a.label << endl;//pr
	else if(a.hex_opcode==-1)
		return strm << "label=" << a.label << "끝" << endl << "opcode=" << a.opcode << "끝" << endl << "operand=" << a.operand << "끝" << endl << "address=" << hex << a.address << "끝" << endl;
		//return strm << "label=" << a.label << endl << "opcode=" << a.opcode << endl << "operand=" << a.operand << endl << "address=" << hex << a.address << endl ;
	else
		return strm << "label=" << a.label << "끝" << endl << "opcode=" << a.opcode << "끝" << endl << "operand=" << a.operand << "끝" << endl << "address=" << hex << a.address << "끝" << endl;
		//return strm << "label=" << a.label << endl << "opcode=" << a.opcode << endl << "operand=" << a.operand << endl << "address=" << hex << a.address << endl << "HexOpcode="  << a.hex_opcode << endl;
}





InstructionStruct::~InstructionStruct()
{
}
