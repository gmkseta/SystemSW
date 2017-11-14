#pragma once
#include <string>
#include <list>
#include <map>
using namespace std;
class InstructionStruct
{
public:
	typedef struct OperationCodeTable
	{//Optable의 구조체
		string Mnemonic;
		int Format;
		unsigned short int MachineCode;
	}SIC_OPTAB;

	InstructionStruct(string* words);
	//생성자인데 word를 매개변수로 넣으면 0,1,2 인덱스의 것을이
	//각각 label opcode oprand로 들어감
	void calAddress();//opcode에 따라 각각 주소 배정해줌
	static void initSizeInst();//resw resb등의 size init함
	static void initOptable();//optable을 init함
	void convertOpcode();//문자열에 따라 16진수 명령어 코드로 변환하여 저장
	void convertHexToStr();
	void convertCharToHex();
	void makeSymbolTable();

	string label;//레이블
	string opcode;
	string operand;

	int hex_opcode;//16진수의 opcode를 저장할곳
	int instruction_format;
	int address;//주소값 저장
	static int startAddress;//시작 address
	static int currentAddress;

	static string sourceName;//파일이름
	static list<string> sizeInst;

	static list<SIC_OPTAB> sic_optable;
	static map<string, int> symbolTable;	

	~InstructionStruct();
};

std::ostream& operator<<(std::ostream &strm, const InstructionStruct &a);
