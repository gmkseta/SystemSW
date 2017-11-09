#pragma once
#include <string>
#include <list>
#include <map>

using namespace std;





class InstructionStruct
{
public:

	typedef struct OperationCodeTable
	{
		string Mnemonic;
		int Format;
		unsigned short int MachineCode;
	}SIC_OPTAB;

	InstructionStruct(string* words);
	void calAddress();
	static void initSizeInst();
	static void initOptable();

	void makeSymbolTable();

	void convertOpcode();
	void convertHexToStr();
	void convertCharToHex();




	string label;
	string opcode;
	string operand;
	int hex_opcode;


	int instruction_format;
	int address;
	static int startAddress;
	static int currentAddress;
	//�ּҰ� �̵��ϴ°�?

	static string sourceName;
	static list<string> sizeInst;
	//������ ��ɾ���� �����ϰ��ִ� ����Ʈ?
	static list<SIC_OPTAB> sic_optable;
	static map<string, int> symbolTable;

	

	~InstructionStruct();
};

std::ostream& operator<<(std::ostream &strm, const InstructionStruct &a);
