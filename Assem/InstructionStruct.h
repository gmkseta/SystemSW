#pragma once
#include <string>
#include <list>
#include <map>
using namespace std;
class InstructionStruct
{
public:
	typedef struct OperationCodeTable
	{//Optable�� ����ü
		string Mnemonic;
		int Format;
		unsigned short int MachineCode;
	}SIC_OPTAB;
	InstructionStruct(string* words);
	//�������ε� word�� �Ű������� ������ 0,1,2 �ε����� ������
	//���� label opcode oprand�� ��
	string label;//���̺�
	string opcode;
	string operand;
	int instruction_format;
	int address;//�ּҰ� ����
	static int startAddress;//���� address
	static int currentAddress;
	static string sourceName;//�����̸�
	void calAddress();//opcode�� ���� ���� �ּ� ��������
	unsigned short int hex_opcode;//16������ opcode�� �����Ұ�
	//OPTAB ���� static �Լ� , ����Ʈ
	static list<string> sizeInst;
	static list<SIC_OPTAB> sic_optable;
	static void initSizeInst();//resw resb���� size init��
	static void initOptable();//optable�� init��
	int convertHexOperand(); //hex_opcode �־��ֱ�����
	//Symbol Table ���� �Լ�
	void makeSymbolTable();//label�� �ּҸ� Table�� ����
	void convertOpcode();//���ڿ��� ���� 16���� ��ɾ� �ڵ�� ��ȯ�Ͽ� ����
	void convertHexToStr();//16������ Str����
	void convertCharToHex();//Str�� 16������
	static map<string, int> symbolTable;	

	void printHexOperand();

	~InstructionStruct();
};

std::ostream& operator<<(std::ostream &strm, const InstructionStruct &a);
