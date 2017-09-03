#include "mwin.h"
#include <qt5/QtWidgets/QApplication>
#include "atoms.h"
//#include  "ecl/ecl.h"
#include <stdio.h>
//#include "opmap.hpp"

using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mwin w;
    w.show();
    
  // overseer ov(w.centralWidget());
  // //ov.mwindow.show();
  // ov.control_units.push_back(make_shared<control_unit>(12,4,4,2,ov.mwidget));
  // ov.memories.push_back(make_shared<memory>(5000, 12, 12, 12));
  // auto cu = ov.control_units[0];
  // auto mem = ov.memories[0];
  // cu->opcodes = opmap;
  // cu->make_alu(cu->get_register(cu->make_regist(12)),
  // 	       cu->get_register(cu->make_regist(12)),
  // 	       cu->get_register(cu->make_regist(12)));
  
  // mem->body.at(0x0ffe) = 15;
  // cu->get_register(cu->make_regist(12))->display->show();
  // cu->make_regist(12);
  // for(auto item:cu->regists_in_out){cout << item.first << endl;}
  // cu->get_register(4)->set(0xffe);
  // cu->get_register(5)->set(0x0fe);
  // auto bu = cu->get_bus(cu->make_bus(12));
  // for(auto& item:cu->regists_in_out){
  //   (get<0>(item.second))->link_in(bu);
  //   (get<0>(item.second))->link_out(bu);
  // }
  
  // auto mdr_id = cu->make_mdr(12, mem);
  // auto mar_id = cu->make_mar(12, mem);
  // cout <<   cu->get_register(4)->info << endl;  
  // cout <<   cu->get_register(5)->info << endl;  
  // auto mdr = cu->get_mdr(mdr_id);
  // mdr->link_in(bu);  
  // mdr->link_out(bu);
  // auto mar = cu->get_mar(mar_id);
  // mar->link_in(bu);
  // cu->opcodes.insert(make_pair(0, vector<size_t>{0x174, 0x164, 0x400, 0x300}));
  // cu->cu_reg->set(0x043);
  // ov.cycle();

  // cout << "mar " << mar->id << " :" << mar->info << endl
  //      << "mdr " << mdr->id << " :" << mdr->info << endl 
  //      << "local na memoria: " << mem->body.at(mar->info.to_ulong()) << endl
  //      << "mdr info: " << mdr->info.to_ulong() << endl;
  return a.exec();
}
