#include "mwin.h"
//#include "../builds/build-jarasper-Desktop_Qt_5_5_1_GCC_32bit-Debug/ui_mwin.h"
#include "ui_mwin.h"
#include <memory>
#include <qt5/QtWidgets/QLabel>

using namespace std;

mwin::mwin(QWidget *parent) :
  QMainWindow(parent),
  ov(this),
  ui(new Ui::mwin)
{
  ui->setupUi(this);
  ov.make_cu(12,4,4,2,ui->frame)->display->setText("oi");
  ov.memories.push_back(make_shared<memory>(5000, 12, 12, 12));
  auto cu = ov.control_units[0];
  auto mem = ov.memories[0];
  //  set_styling<decltype(cu)>(cu);
  // cu->display->setFixedSize(300, 300);
  // cu->display->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  // cu->display->setAlignment(Qt::AlignBottom | Qt::AlignRight);
  cu->opcodes = opmap;
  cu->make_alu(cu->get_register(cu->make_regist(12)),
  	       cu->get_register(cu->make_regist(12)),
  	       cu->get_register(cu->make_regist(12)));
  mem->body.at(0x0ffe) = 15;
  cu->get_register(cu->make_regist(12))->display->show();
  cu->make_regist(12);
  for(auto item:cu->regists_in_out){cout << item.first << endl;}
  cu->get_register(4)->set(0xffe);
  cu->get_register(5)->set(0x0fe);
  auto bu = cu->get_bus(cu->make_bus(12));
  for(auto& item:cu->regists_in_out){
    (get<0>(item.second))->link_in(bu);
    (get<0>(item.second))->link_out(bu);
  }
  
  auto mdr_id = cu->make_mdr(12, mem);
  auto mar_id = cu->make_mar(12, mem);
  cout <<   cu->get_register(4)->info << endl;  
  cout <<   cu->get_register(5)->info << endl;  
  auto mdr = cu->get_mdr(mdr_id);
  mdr->link_in(bu);  
  mdr->link_out(bu);
  auto mar = cu->get_mar(mar_id);
  mar->link_in(bu);
  cu->opcodes.insert(make_pair(0, vector<size_t>{0x174, 0x164, 0x400, 0x300}));
  cu->cu_reg->set(0x043);
  ov.cycle();

  cout << "mar " << mar->id << " :" << mar->info << endl
       << "mdr " << mdr->id << " :" << mdr->info << endl 
       << "local na memoria: " << mem->body.at(mar->info.to_ulong()) << endl
       << "mdr info: " << mdr->info.to_ulong() << endl;
  //cu->display->show_context_menu(cu->display->pos());
}

mwin::~mwin()
{
  delete ui;
}

void mwin::on_criar_cu_clicked()
{
  auto cu = ov.make_cu(12, 4, 4, 4, ui->frame);
 
  cu->display->setText("oi");
  cu->display->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  cu->display->setAlignment(Qt::AlignBottom | Qt::AlignRight);
  //cu->display->setParent(ui->frame);
  cu->display->show();
  // mov_cnt<QLabel> * but = new mov_cnt<QLabel>(ui->frame);
  // but->setText("ola");
  // but->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  // but->setAlignment(Qt::AlignBottom | Qt::AlignRight);
  // but->show();
}
