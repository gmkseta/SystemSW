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
	static std::string sourceName;//파일이름
	unsigned short int hex_opcode;//16진수의 op코드 저장할 곳


	typedef struct OperationCodeTable
	{
		std::string Mnemonic;
		int Format;
		unsigned short int MachineCode;
	}SIC_OPTAB;

	InstructionStruct(std::string* word) 
		:label(word[0]),opcode(word[1]),operand(word[2]){};
	// 0 번째인덱스는 label 1번째는 opcode 2번쨰는 oprand가 들어감

	void calAddress();//opcode에 따라 각각 주소를 배정

	//OPTAB 관련 static 함수 , 리스트
	static std::list<std::string> sizeInst;
	static void initSizeInst();

	static std::list<SIC_OPTAB> sic_optable;
	static void initOptable();

	int convertHexOperand(); // hex_opcode 넣어주기위함

	//Symbol Table 관련 함수
	void makeSymbolTable();//label 의 주소를 table에 저장
	void convertOpcode();//문자열에 따라 16진수 명령어 코드로 변환하여 저장
	void convertHexToStr();//16진수를 Str으로
	void convertCharToHex();//Str을 16진수로
	static std::map<std::string, int> symbolTable;

	void printHexOperand();
	~InstructionStruct();

};

std::ostream& operator<<(std::ostream &strm, const InstructionStruct &a);