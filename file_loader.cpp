#include "file_loader.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <math.h>
#include <atoms.h>



int loadMem(std::string path, memory* mem_target) {
    //remove the std:string mem if there is enough time, and just have it write directly to mem_target
  std::string mem[MEMSIZE];
  int i = 0, temp = 0;
  std::ifstream memload;

  for (int init = 0; init < MEMSIZE; init++){mem[init] = "0000";}
  if (path == ""){
      //there is nothing on the path variable so there's nothing to load
      return -1;}
   else{memload.open(path);}
  if (!memload.is_open()) { std::cout << "erro abrindo o arquivo de memoria" <<path<< std::endl; return 0; }
  while (i < MEMSIZE && getline(memload, mem[i])) {
    if (mem[i].at(0) != ';') { i++; }
  }
  int orgJmp = 0;
  for(int j = 0;j<=i;j++){
    if(mem[j].substr(0,3) == "org"){
      //std::cout<<"CHEGUEI 1:"<<mem[j].substr(4)<<"        "<< stoi(mem[j].substr(4), nullptr, 16)<<"   "<<j<<std::endl;
      int k = i-j;
      orgJmp = stoi(mem[j].substr(4), nullptr, 16);
      mem[j] = "0000";
      while(k > 0){
    mem[orgJmp+k-1] = mem[j+k]; mem[j+k] = "0000";
    k--;
      }
    }
  }

  //i = orgJmp+i;
  //  i=0;
  //  while (i < MEMSIZE){
  //      if(mem[i] == ""){mem[i]= "0000";}
  //      i++;}

  //now we turn it into a vector of size_t to match the new memory store:
  for (int iter = 0;iter < MEMSIZE;iter++){
     mem_target->body[iter] =  stoi(mem[iter],nullptr,16);
//     if (iter < 10){
//         std::cout << mem[iter] << ": " << stoi(mem[iter],nullptr,16) << std::endl;
//     }
  }
  return 0;
}




int loadOpcode(std::string opcode[MAXOPCODE][MAXMICROC], std::string path){
  int i = 0, j=0, open=0, close=0;
  std::ifstream opload;
  if (path == ""){
      //there is nothing on the path variable so there's nothing to load
      return -1;
      //opload.open(OPCODE_LOAD_STD);
  }
  else{opload.open(path);}
  if(!opload.is_open()){std::cout<< "erro abrindo arquivo de Opcode"<< std::endl;}
  while(getline ( opload, opcode[i][j]) && opcode[i][j] != "" && i < MAXOPCODE && j < MAXMICROC){
    if (opcode[i][j].at(0) != ';'){
      if(opcode[i][j].at(0)=='('){open = 1;}
      if(opcode[i][j].at(0)==')'){close = 1;}
      if (open==1){
    j++;
    if(close == 1){
      i++;
      j=0;
      open = 0;
      close = 0;
    }
      }
    }
  }
  return 0;
}
