#include "mwin.h"
#include <ui_mwin.h>
#include <memory>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGraphicsView>
#include <QtGui/QPen>

using namespace std;

mwin::mwin(QWidget *parent) :
  QMainWindow(parent),
  ov(this),
  ui(new Ui::mwin)
{
  ui->setupUi(this);
  ov.make_cu(12,4,4,2,ui->frame)->display->setText("control unit 0");
  ov.memories.push_back(make_shared<memory>(5000, 12, 12, 12));
  auto cu = ov.control_units[0];
  auto mem = ov.memories[0];
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
  
  auto scene = new Scene(centralWidget());
  scene->setSceneRect(0,0,500,500);
  auto view = new QGraphicsView(scene, centralWidget());
  view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  CustomRectItem* rectItem1 = new CustomRectItem(QRect(3,4,80,80));
  rectItem1->setPos(0,0);
  rectItem1->setBrush(Qt::gray);
  scene->addItem(rectItem1);
  
  CustomRectItem* rectItem2 = new CustomRectItem(QRect(3,4,60,60));
  rectItem2->setPos(1,19);
  rectItem2->setBrush(Qt::magenta);
  scene->addItem(rectItem2);

  CustomRectItem* rectItem3 = new CustomRectItem(QRect(3,4,60,60));
  rectItem3->setPos(20,10);
  rectItem3->setBrush(Qt::white);
  rectItem3->info.setText("diferentessdsfsdfsdfdfsdf");
  scene->addItem(rectItem3);
}

mwin::~mwin()
{
  delete ui;
}

void mwin::on_criar_cu_clicked()
{
  auto cu = ov.make_cu(12, 4, 4, 4, ui->frame);
  auto lastindx = ov.control_units.size() - 1;
  cu->display->setText(QString("control unit" + QString::number(lastindx)));
  cu->display->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  cu->display->setAlignment(Qt::AlignBottom | Qt::AlignRight);
  cu->display->show();
}
