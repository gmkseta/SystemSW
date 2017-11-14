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
	void calAddress();//opcode�� ���� ���� �ּ� ��������
	static void initSizeInst();//resw resb���� size init��
	static void initOptable();//optable�� init��
	void convertOpcode();//���ڿ��� ���� 16���� ��ɾ� �ڵ�� ��ȯ�Ͽ� ����
	void convertHexToStr();
	void convertCharToHex();
	void makeSymbolTable();

	string label;//���̺�
	string opcode;
	string operand;

	int hex_opcode;//16������ opcode�� �����Ұ�
	int instruction_format;
	int address;//�ּҰ� ����
	static int startAddress;//���� address
	static int currentAddress;

	static string sourceName;//�����̸�
	static list<string> sizeInst;

	static list<SIC_OPTAB> sic_optable;
	static map<string, int> symbolTable;	

	~InstructionStruct();
};

std::ostream& operator<<(std::ostream &strm, const InstructionStruct &a);
