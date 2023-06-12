#include "opcode_parser.h"
#include <iostream>

std::string trim_string(std::string input, std::string to_trim){
  auto pos = input.find(to_trim);
  if (pos != std::string::npos){
    return input.substr(0,pos);
  }
  return input;

}
void generate_microcode(size_t opertr,std::string UAtom1,std::string LAtom2, std::string opcodeLine, opcode* opcod){
    size_t UAtom1_size_t,LAtom2_size_t;
    try{
         UAtom1_size_t = stoi(UAtom1,nullptr,16);}
    catch(const std::exception& e){
        std::cout<<"stoi failed on: " << UAtom1 <<std::endl;
        return;}
    try{
         LAtom2_size_t = stoi(LAtom2,nullptr,16);}
    catch(const std::exception& e){
        std::cout<<"stoi failed on: " << UAtom1 <<std::endl;
        return;}

        opcod->microcodes.push_back(microcode(opertr, {LAtom2_size_t,UAtom1_size_t}));
        opcod->microcodes.back().literal = opcodeLine;
    }



std::map<size_t, opcode> parseAllOpcodes(std::string opcodef[MAXOPCODE][MAXMICROC], std::string Dopcode[100][MAXMICROC])//, opcode opcode_return[100]){
{
  //std::string opcode[MAXOPCODE][MAXMICROC];
  std::map<size_t, opcode> opmap;
  auto opcode = opcodef;
  for(int i= 0; i<MAXOPCODE; i++){
    for(int j= 0; j< MAXMICROC; j++){
      opcode[i][j] = trim_string(opcode[i][j], "\r");
      opcode[i][j] = trim_string(opcode[i][j], "\n");
      opcode[i][j] = trim_string(opcode[i][j], "\n\r");
      opcode[i][j] = trim_string(opcode[i][j], "\r\n");
    }
  }
  int i= 0;
  for(i; i<MAXOPCODE; i++){
    if (opcode[i][0] == ""){break;}

    opmap[i] = parseOpcode(opcode[i], Dopcode[i]);//std::cout<< "AllOpcodes  "<< std::endl;
  }
  return opmap;
}
opcode parseOpcode(std::string opcodef[MAXMICROC], std::string Dopcode[MAXMICROC])//, opcode opcode_return[MAXMICROC]){
{
  //auto  opcode = opcodef;
  opcode* opcod = new opcode;
  opcod->literal = opcodef[0];
  int i = 1, lastIndx = 1;
  Dopcode[0]=opcodef[0].substr(1,opcodef[0].length());
  //std::cout << opcodef << std::endl;
  while (opcodef[i] != ")"){
      parseOpcodeLine(opcodef[i], Dopcode, lastIndx, opcod);i++;}//std::cout<<i<<std::endl;}
  //std::cout<< "tst" << std::endl;
  return *opcod;
}
std::string parseOpcodeLine(std::string opcodeLine, std::string Dopcode[MAXMICROC], int &lastIndx, opcode* opcod){
  std::string UAtom1, LAtom2;
  int i=0, oper = 0;
  while (i < opcodeLine.length()){
    if (opcodeLine == ""){break;}

    else{
      //ASSIGNMENT LITERAL (assigns the operando of opcode)
        if(i < opcodeLine.length() -2 &&
                opcodeLine.at(i) == '<' && opcodeLine.at(i+1) == '-' && opcodeLine.at(i+2) == '\'' ){
      oper = 0xc;
      UAtom1 = opcodeLine.substr(0,i);
//      LAtom2 = parseOpcodeLine(opcodeLine.substr(i+2,opcodeLine.length()-1),Dopcode, lastIndx, opcod);
//      if(LAtom2 == "end"){
        LAtom2 = opcodeLine.substr(i+3,opcodeLine.length()-1);
      //}
      Dopcode[lastIndx] ="0C";
      Dopcode[lastIndx] =Dopcode[lastIndx] + '(' + UAtom1 + ',' + LAtom2 + ')';
      size_t opertr = 0xC;

      generate_microcode(opertr,UAtom1,LAtom2, opcodeLine,opcod);
      lastIndx++;
      return UAtom1;
        }
      //ASSIGNMENT
      if(i < opcodeLine.length() -1 &&
              opcodeLine.at(i) == '<' && opcodeLine.at(i+1) == '-' ){
	oper = 1;
	UAtom1 = opcodeLine.substr(0,i);
    LAtom2 = parseOpcodeLine(opcodeLine.substr(i+2,opcodeLine.length()-1),Dopcode, lastIndx, opcod);
	if(LAtom2 == "end"){
	  LAtom2 = opcodeLine.substr(i+2,opcodeLine.length()-1);
	}
	Dopcode[lastIndx] ="00";
	Dopcode[lastIndx] =Dopcode[lastIndx] + '(' + UAtom1 + ',' + LAtom2 + ')';
    size_t opertr = 0x1;
    generate_microcode(opertr,UAtom1,LAtom2, opcodeLine,opcod);
	lastIndx++;
	return UAtom1;
      }
      //SHL
      if(i < opcodeLine.length() -2 &&
              opcodeLine.at(i) == 'S' && opcodeLine.at(i+1) == 'H' && opcodeLine.at(i+2) == 'L'){
    oper = 2;
    UAtom1 = "0"; //need to specify the target later once im doing the full generics
    LAtom2 = "0"; //opcodeLine.substr(i+1,opcodeLine.length()-1);        need to specify the target later once im doing the full generics
  Dopcode[lastIndx] ="03";
  Dopcode[lastIndx] =Dopcode[lastIndx] + '(' + UAtom1 + ',' + LAtom2 + ')';
  size_t opertr = 0x6;
  generate_microcode(opertr,UAtom1,LAtom2, opcodeLine,opcod);
  lastIndx++;
  return UAtom1;
	lastIndx++;
	return UAtom1;
      }
      //SHR
      if(i < opcodeLine.length() -2 &&
              opcodeLine.at(i) == 'S' && opcodeLine.at(i+1) == 'H' && opcodeLine.at(i+2) == 'R'){
        oper = 3;
        UAtom1 = opcodeLine.substr(0,i);
    LAtom2 = parseOpcodeLine(opcodeLine.substr(i+2,opcodeLine.length()-1), Dopcode, lastIndx,opcod);
	if(LAtom2 == "end"){
	  LAtom2 = opcodeLine.substr(i+2,opcodeLine.length()-1);
	}
	Dopcode[lastIndx] ="02";
	Dopcode[lastIndx] =Dopcode[lastIndx] + '(' + UAtom1 + ',' + LAtom2 + ')';
	lastIndx++;
	return UAtom1;
      }
      //ADD
      if(i < opcodeLine.length() -2 &&
              opcodeLine.at(i) == 'A' && opcodeLine.at(i+1) == 'D'&& opcodeLine.at(i+2) == 'D'){
        oper = 4;
      UAtom1 = "0"; //need to specify the target later once im doing the full generics
      LAtom2 = "0"; //opcodeLine.substr(i+1,opcodeLine.length()-1);        need to specify the target later once im doing the full generics
    Dopcode[lastIndx] ="03";
    Dopcode[lastIndx] =Dopcode[lastIndx] + '(' + UAtom1 + ',' + LAtom2 + ')';
    size_t opertr = 0x2;
    generate_microcode(opertr,UAtom1,LAtom2, opcodeLine,opcod);
    lastIndx++;
    return UAtom1;
      }
      //SUB
      if(i < opcodeLine.length() -2 &&
              opcodeLine.at(i) == 'S' && opcodeLine.at(i+1) == 'U'&& opcodeLine.at(i+2) == 'U'){
        oper = 5;
        //UAtom1 = opcodeLine.substr(0,i);
//    LAtom2 = parseOpcodeLine(opcodeLine.substr(i+1,opcodeLine.length()-1), Dopcode, lastIndx,opcod);
//	if(LAtom2 == "end"){
      //LAtom2 = opcodeLine.substr(i+1,opcodeLine.length()-1);
      UAtom1 = "0"; //need to specify the target later once im doing the full generics
      LAtom2 = "0"; //opcodeLine.substr(i+1,opcodeLine.length()-1);        need to specify the target later once im doing the full generics
    //}
	Dopcode[lastIndx] ="04";
	Dopcode[lastIndx] =Dopcode[lastIndx] + '(' + UAtom1 + ',' + LAtom2 + ')';
    size_t opertr = 0x5;
    generate_microcode(opertr,UAtom1,LAtom2, opcodeLine,opcod);
    lastIndx++;
	return UAtom1;
      }
      //IFS (still need doing)
      if(i < opcodeLine.length() -9 &&
              opcodeLine.at(i) == 'i' && opcodeLine.at(i+1) == 'f'){
          auto type = opcodeLine.at(i+6);
          std::cout << type << std::endl;
          //UAtom1 = "0";
          UAtom1 = opcodeLine.substr(i+9,opcodeLine.length()-1);
          LAtom2 = "0";
           size_t opertr;
          if (type == 'e'){
              opertr = 0x8;
          }
          if (type == 'z'){
              opertr = 0x9;
          }
          if (type == 'c'){
              opertr = 0xa;
          }
          if (type == 'n'){
              opertr = 0xb;
          }
          generate_microcode(opertr,UAtom1,LAtom2, opcodeLine,opcod);
        oper = 7;
	lastIndx++;
	return UAtom1;
      }
      //WRITE
      if(i < opcodeLine.length() -3 &&
              opcodeLine.at(i) == 'W' && opcodeLine.at(i+1) == 'R' && opcodeLine.at(i+2) == 'I' && opcodeLine.at(i+3) == 'T'){
          oper = -1;
          size_t opertr = 0x4;
          UAtom1= "0"; //will need to be generalized on a later date
          LAtom2 = "0"; //will need to be generalized on a later date
          generate_microcode(opertr,UAtom1,LAtom2, opcodeLine,opcod);
          lastIndx++;
          return UAtom1;
      }
      //READ
      if(i < opcodeLine.length() -3 &&
              opcodeLine.at(i) == 'R' && opcodeLine.at(i+1) == 'E' && opcodeLine.at(i+2) == 'A' && opcodeLine.at(i+3) == 'D'){
          oper = -1;
          size_t opertr = 0x3;
          UAtom1= "0"; //will need to be generalized on a later date
          LAtom2 = "0"; //will need to be generalized on a later date
          generate_microcode(opertr,UAtom1,LAtom2, opcodeLine,opcod);
          lastIndx++;
          return UAtom1;
      }
      //HALT
      if(i < opcodeLine.length() -3 &&
              opcodeLine.at(i) == 'H' && opcodeLine.at(i+1) == 'A' && opcodeLine.at(i+2) == 'L' && opcodeLine.at(i+3) == 'T'){
          oper = -1;
	Dopcode[lastIndx] ="07";
    size_t opertr = 0x0;
    UAtom1= "0";
    LAtom2 = "0";
    generate_microcode(opertr,UAtom1,LAtom2, opcodeLine,opcod);
	lastIndx++;
    return UAtom1;
      }
      //INC
      if(i < opcodeLine.length() -2 &&
              opcodeLine.at(i) == 'I' && opcodeLine.at(i+1) == 'N' && opcodeLine.at(i+2) == 'C'){
          oper = 0xd;
          size_t opertr = 0xd;
          UAtom1= "0";
          LAtom2 = "0";
          generate_microcode(opertr,UAtom1,LAtom2, opcodeLine,opcod);
          lastIndx++;
          return UAtom1;
      }
      i++;
    }
  }
  if (oper == 0){return "end";}
}
