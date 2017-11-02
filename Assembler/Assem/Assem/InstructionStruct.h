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
	//�ּҰ� �̵��ϴ°�?

	static string sourceName;
	static list<string> sizeInst;
	//������ ��ɾ���� �����ϰ��ִ� ����Ʈ?

	~InstructionStruct();
};

std::ostream& operator<<(std::ostream &strm, const InstructionStruct &a);
