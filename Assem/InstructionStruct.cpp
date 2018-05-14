#include "InstructionStruct.h"
#include <iostream>
#include <cctype>
#include <algorithm>
int InstructionStruct::currentAddress = 0;
int InstructionStruct::startAddress = 0;
std::string InstructionStruct::sourceName = "0";
std::list<std::string> InstructionStruct::sizeInst = {};
std::list<InstructionStruct::SIC_OPTAB> InstructionStruct::sic_optable = {};
std::map<std::string, int> InstructionStruct::symbolTable = {};
InstructionStruct::InstructionStruct(std::string* words)//생성자
{	this->label = words[0];	this->opcode = words[1];this->operand = words[2];}

void InstructionStruct::calAddress()
{
	// 10주차 :주석일떄 주소 처리를 하지않음  
	if (this->label[0] == '.') return;
	if (this->opcode == "start")
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
		if (this->opcode == "resb")
		{
			this->address = this->currentAddress;
			this->currentAddress += 0x1 * stoi(this->operand);//1byte * 뒤에있는 숫자만큼
		}
		else if (this->opcode == "resw")
		{
			this->address = this->currentAddress;
			this->currentAddress += 0x3 * stoi(this->operand);//3byte * 
		}
		else if (this->opcode == "word")
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
	InstructionStruct::sizeInst.push_back("resb");
	InstructionStruct::sizeInst.push_back("resw");
	InstructionStruct::sizeInst.push_back("word");
	InstructionStruct::sizeInst.push_back("byte");
}

// 10주차 : Optab 초기화 해주는 함수
void InstructionStruct::initOptable()
{
	InstructionStruct::sic_optable.push_back({ "add"	,3		,0X18 });
	InstructionStruct::sic_optable.push_back({ "and"	,3		,0X40 });
	InstructionStruct::sic_optable.push_back({ "comp"	,3		,0X28 });
	InstructionStruct::sic_optable.push_back({ "div"   ,3		,0X24 });
	InstructionStruct::sic_optable.push_back({ "j"      ,3		,0X3C });
	InstructionStruct::sic_optable.push_back({ "jeq"    ,3		,0X30 });
	InstructionStruct::sic_optable.push_back({ "jgt"    ,3		,0X34 });
	InstructionStruct::sic_optable.push_back({ "jlt"    ,3		,0X38 });
	InstructionStruct::sic_optable.push_back({ "jsub"   ,3		,0X48 });
	InstructionStruct::sic_optable.push_back({ "lda"    ,3		,0X00 });
	InstructionStruct::sic_optable.push_back({ "ldch"   ,3		,0X50 });
	InstructionStruct::sic_optable.push_back({ "ldl"    ,3		,0X08 });
	InstructionStruct::sic_optable.push_back({ "ldx"    ,3		,0X04 });
	InstructionStruct::sic_optable.push_back({ "mul"   ,3		,0X20 });
	InstructionStruct::sic_optable.push_back({ "op"		,3		,0X44 });
	InstructionStruct::sic_optable.push_back({ "rd"	    ,3		,0XD8 });
	InstructionStruct::sic_optable.push_back({ "rsub"   ,3		,0X4C });
	InstructionStruct::sic_optable.push_back({ "sta"    ,3		,0X0C });
	InstructionStruct::sic_optable.push_back({ "stch"   ,3		,0X54 });
	InstructionStruct::sic_optable.push_back({ "stl"    ,3		,0X14 });
	InstructionStruct::sic_optable.push_back({ "stsw"   ,3		,0XE8 });
	InstructionStruct::sic_optable.push_back({ "stx"    ,3		,0X10 });
	InstructionStruct::sic_optable.push_back({ "sub"    ,3		,0X1C });
	InstructionStruct::sic_optable.push_back({ "td"     ,3		,0XE0 });
	InstructionStruct::sic_optable.push_back({ "tix"    ,3		,0X2C });
	InstructionStruct::sic_optable.push_back({ "wd"     ,3		,0XDC });	
}
void InstructionStruct::convertOpcode()
{
	for (auto itr : sic_optable) {
		if (itr.Mnemonic.compare(this->opcode)==0)
		{
			this->hex_opcode = itr.MachineCode;
			this->instruction_format = itr.Format;
			break;
		}
		else
			hex_opcode = -1;
	}
}


std::ostream& operator<<(std::ostream &strm, const InstructionStruct &a) {
	// 10주차 : 
	using namespace std;
	if (a.label[0] == '.')
		return strm << "주석:" << a.label.substr(1, a.label.size()) << endl;
	else if(a.hex_opcode==-1)
		return strm << "label=" << a.label << endl << "opcode=" << a.opcode << endl << "operand=" 
		<< a.operand << endl << "address=" << hex << a.address << endl ;
	else
		return strm << "label=" << a.label << endl << "opcode=" << a.opcode << endl << "operand=" 
		<< a.operand << endl << "address=" << hex << a.address << endl << "HexOpcode="  << a.hex_opcode << endl;
}

//11주 실습
void InstructionStruct::makeSymbolTable()
{
	using namespace std;
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
	using namespace std;
	if (convertHexOperand() != -1)
		cout << hex << "hex_opcode:" << this->hex_opcode<<"     hex_operand:" << hex << convertHexOperand() << endl;
	else
		cout << "label address : " <<hex<<this->address<< endl;
}
InstructionStruct::~InstructionStruct()
{
}

