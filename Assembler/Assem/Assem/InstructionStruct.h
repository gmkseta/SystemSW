#pragma once
#include <string>
#include <list>
using namespace std;
class InstructionStruct
{
public:
	InstructionStruct(string* words);
	void calAddress();
	static void initSizeInst();


	string label;
	string opcode;
	string operand;
	

	int instruction_format;
	int address;
	static int startAddress;
	static int currentAddress;
	//주소값 이동하는거?

	static string sourceName;
	static list<string> sizeInst;
	//사이즈 명령어들을 저장하고있는 리스트?

	~InstructionStruct();
};

std::ostream& operator<<(std::ostream &strm, const InstructionStruct &a);
