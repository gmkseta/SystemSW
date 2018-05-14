#pragma once
#include <string>
#include <list>
#include <map>

class InstructionStruct
{
public:
	std::string label, opcode, operand;
	int instruction_format, address;
	static int startAddress, currentAddress;
	static std::string sourceName;//�����̸�
	unsigned short int hex_opcode;//16������ op�ڵ� ������ ��


	typedef struct OperationCodeTable
	{
		std::string Mnemonic;
		int Format;
		unsigned short int MachineCode;
	}SIC_OPTAB;

	InstructionStruct(std::string* word) 
		:label(word[0]),opcode(word[1]),operand(word[2]){};
	// 0 ��°�ε����� label 1��°�� opcode 2������ oprand�� ��

	void calAddress();//opcode�� ���� ���� �ּҸ� ����

	//OPTAB ���� static �Լ� , ����Ʈ
	static std::list<std::string> sizeInst;
	static void initSizeInst();

	static std::list<SIC_OPTAB> sic_optable;
	static void initOptable();

	int convertHexOperand(); // hex_opcode �־��ֱ�����

	//Symbol Table ���� �Լ�
	void makeSymbolTable();//label �� �ּҸ� table�� ����
	void convertOpcode();//���ڿ��� ���� 16���� ��ɾ� �ڵ�� ��ȯ�Ͽ� ����
	void convertHexToStr();//16������ Str����
	void convertCharToHex();//Str�� 16������
	static std::map<std::string, int> symbolTable;

	void printHexOperand();
	~InstructionStruct();

};

std::ostream& operator<<(std::ostream &strm, const InstructionStruct &a);