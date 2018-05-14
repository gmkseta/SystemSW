#include "InstructionStruct.h"
#include <iostream>


using namespace std;
int InstructionStruct::currentAddress = 0;
int InstructionStruct::startAddress = 0;
string InstructionStruct::sourceName = "0";
list<string>InstructionStruct::sizeInst = {};
list<InstructionStruct::SIC_OPTAB>InstructionStruct::sic_optable = {};
map<string, int>InstructionStruct::symbolTable = {};


void InstructionStruct::calAddress()
{
	if (this->label[0] == '.')return;//林籍老嫐 贸府 x


}