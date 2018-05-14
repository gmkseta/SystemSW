#pragma once
#include <list>
#include <map>
#include <string>

class InstructionStruct
{
public:
	typedef struct OperationCodeTable
	{//Optable의 구조체
		std::string Mnemonic;
		int Format;
		unsigned short int MachineCode;
	}SIC_OPTAB;
	InstructionStruct(std::string* words);
	//생성자인데 word를 매개변수로 넣으면 0,1,2 인덱스의 것을이
	//각각 label opcode oprand로 들어감
	std::string label;//레이블
	std::string opcode;
	std::string operand;
	int instruction_format;
	int address;//주소값 저장
	static int startAddress;//시작 address
	static int currentAddress;
	static std::string sourceName;//파일이름
	void calAddress();//opcode에 따라 각각 주소 배정해줌
	unsigned short int hex_opcode;//16진수의 opcode를 저장할곳
	//OPTAB 관련 static 함수 , 리스트
	static std::list<std::string> sizeInst;
	static std::list<SIC_OPTAB> sic_optable;
	static void initSizeInst();//resw resb등의 size init함
	static void initOptable();//optable을 init함
	int convertHexOperand(); //hex_opcode 넣어주기위함
	//Symbol Table 관련 함수
	void makeSymbolTable();//label의 주소를 Table에 저장
	void convertOpcode();//문자열에 따라 16진수 명령어 코드로 변환하여 저장
	void convertHexToStr();//16진수를 Str으로
	void convertCharToHex();//Str을 16진수로
	static std::map<std::string, int> symbolTable;

	void printHexOperand();

	~InstructionStruct();
};

std::ostream& operator<<(std::ostream &strm, const InstructionStruct &a);
