#include "mwin.h"
#include <ui_mwin.h>
#include <memory>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGraphicsView>
#include <QtGui/QPen>
#include <string>
#ifdef slots
#undef slots
#endif
#include <ecl/ecl.h>
//#include "ecl_injection.h"
using namespace std;
 
mwin::mwin(QWidget *parent) :
  QMainWindow(parent),
  ov(this),
  ui(new Ui::mwin)
{
  ui->setupUi(this);
  auto scene = new Scene(centralWidget());
  scene->setSceneRect(0,0,800,800);
  scene_info::scene = scene;
  new QGraphicsView(scene, centralWidget());
  //view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  ov.make_cu(12,4,4,2)->display->info.setText("control unit 0");
  ov.memories.push_back(make_shared<memory>(5000, 12, 12, 12));
  auto cu = ov.control_units[0];
  auto mem = ov.memories[0];
  cu->opcodes = opmap;
  cu->make_alu(12);
  mem->body.at(0x0ffe) = 15;
  cu->get_register(cu->make_regist(12));
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

  cu->cu_reg->set(0x000);
 
  
  ov.cycle();
  //on_criar_regist_clicked(); 
//   cout << "mar " << mar->id << " :" << mar->info << endl
//        << "mdr " << mdr->id << " :" << mdr->info << endl 
//        << "local na memoria: " << mem->body.at(mar->info.to_ulong()) << endl
//        << "mdr info: " << mdr->info.to_ulong() << endl;
 
  
}
mwin::~mwin()
{
  delete ui;
}

void mwin::on_criar_cu_clicked()
{
  auto new_cu = ov.make_cu(12, 4, 4, 4);
  auto lastindx = ov.control_units.size() - 1;
  new_cu->display->setText(QString("control unit" + QString::number(lastindx)));
}

void mwin::on_repl_input_returnPressed()
{
  
  if(auto control_unit = this->ov.control_units.at(ui->repl_cu_select->value())){
    if(ui->repl_input->text().length() ==
       (control_unit->operand_size * control_unit->operand_amnt + control_unit->operator_size)/4){
      ui->repl_display->appendPlainText(ui->repl_input->text());
      control_unit->cu_reg->set(std::stoul(ui->repl_input->text().toStdString(),nullptr,16));
      this->ov.cycle();
    }
    else{
      ui->repl_display->appendPlainText("tamanho do codigo invalido");
    }
  } 
  ui->repl_input->setText("");
}






void mwin::on_criar_regist_clicked()
{
  auto selected_cu = ov.control_units.at(ui->repl_cu_select->value());
  auto selected_bus = selected_cu->get_bus(ui->repl_bus_select->value());
  auto new_register = selected_cu->get_register(selected_cu->make_regist(12));
  new_register->link_in(selected_bus);
  new_register->link_out(selected_bus);
  
  
}
void mwin::on_criar_bus_clicked()
{
  ov.control_units.at(ui->repl_cu_select->value())->make_bus();
}
void mwin::on_criar_alu_clicked()
{
  ov.control_units.at(ui->repl_cu_select->value())->make_alu();
}

void mwin::on_ecl_repl_input_returnPressed()
{

    auto val = ui->ecl_repl_input->text().toStdString();
    auto val_form = c_string_to_object(val.data());
    cl_eval(val_form);
    //si_safe_eval(0,, ECL_NIL);
    ui->ecl_repl_input->setText("");
}

