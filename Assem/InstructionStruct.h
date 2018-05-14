#pragma once
#include <list>
#include <map>
#include <string>

class InstructionStruct
{
public:
	typedef struct OperationCodeTable
	{//Optable�� ����ü
		std::string Mnemonic;
		int Format;
		unsigned short int MachineCode;
	}SIC_OPTAB;
	InstructionStruct(std::string* words);
	//�������ε� word�� �Ű������� ������ 0,1,2 �ε����� ������
	//���� label opcode oprand�� ��
	std::string label;//���̺�
	std::string opcode;
	std::string operand;
	int instruction_format;
	int address;//�ּҰ� ����
	static int startAddress;//���� address
	static int currentAddress;
	static std::string sourceName;//�����̸�
	void calAddress();//opcode�� ���� ���� �ּ� ��������
	unsigned short int hex_opcode;//16������ opcode�� �����Ұ�
	//OPTAB ���� static �Լ� , ����Ʈ
	static std::list<std::string> sizeInst;
	static std::list<SIC_OPTAB> sic_optable;
	static void initSizeInst();//resw resb���� size init��
	static void initOptable();//optable�� init��
	int convertHexOperand(); //hex_opcode �־��ֱ�����
	//Symbol Table ���� �Լ�
	void makeSymbolTable();//label�� �ּҸ� Table�� ����
	void convertOpcode();//���ڿ��� ���� 16���� ��ɾ� �ڵ�� ��ȯ�Ͽ� ����
	void convertHexToStr();//16������ Str����
	void convertCharToHex();//Str�� 16������
	static std::map<std::string, int> symbolTable;

	void printHexOperand();

	~InstructionStruct();
};

std::ostream& operator<<(std::ostream &strm, const InstructionStruct &a);
