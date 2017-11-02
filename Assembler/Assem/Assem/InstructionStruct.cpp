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
	//그니까 resw resb 이런게 아닐때 열로 들어가는거임
		//lda ldx 같은 일반적인 명령어를 여기서 처리
		this->address = this->currentAddress;
		this->currentAddress += 0x3;
		//3byte씩 증가~
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
