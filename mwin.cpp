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
  //cu->add_opcode(std::vector<size_t>(0x1, {0x4,0x7}));
  cu->add_opcode(std::vector<size_t>{0x701,0x175});
  //cu->opcodes.insert(make_pair(2, vector<size_t>{0x147}));
  //cu->opcodes.insert(make_pair(3, vector<size_t>{0x400}));
  cu->make_alu(12);
  cu->get_alu(0)->A->set(std::bitset<max_bits>(0xfff));
  mem->body.at(0x002) = 15;
  //cu->get_register(cu->make_regist(12));
  cu->make_regist(12);
  cu->make_regist(12);

  for(auto item:cu->regists_in_out){cout << item.first << endl;}
  cu->get_register(4)->set(0x002);
  cu->get_register(5)->set(0x003);
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
  mar->link_out(bu);

  cu->cu_reg->set(0x000);
 
  
  //ov.cycle();
  //on_criar_regist_clicked(); 
   cout << "mar " << mar->id << " :" << mar->info << endl
        << "mdr " << mdr->id << " :" << mdr->info << endl
        << "local na memoria: " << mem->body.at(mar->info.to_ulong()) << endl
        << "mdr info: " << mdr->info.to_ulong() << endl;
 fill_opcodes_tree();
 fill_memory_list();
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

void mwin::on_microcode_repl_input_returnPressed()
{
  //NEED TO FIX THIS
  if(auto control_unit = this->ov.control_units.at(ui->repl_cu_select->value())){
    if(ui->microcode_repl_input->text().length() ==
       (control_unit->operand_size * control_unit->operand_amnt + control_unit->operator_size)/4){
      ui->microcode_repl_display->appendPlainText(ui->repl_input->text());
      control_unit->cu_reg->set(std::stoul(ui->microcode_repl_input->text().toStdString(),nullptr,16));
      auto cu = this->ov.control_units.at(ui->repl_cu_select->value());
      //cu->interpret_minst(cu->cu_reg->info,ov.memories);
      //cu->sync_bus();

    }
    else{
      ui->microcode_repl_display->appendPlainText("tamanho do codigo invalido");
    }
  }
  ui->microcode_repl_input->setText("");
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

void mwin::fill_opcodes_tree(){
    auto selected_cu = ov.control_units.at(ui->repl_cu_select->value());
    auto opcodes = selected_cu->opcodes;
    auto tree_widget = ui->opcode_display;
    tree_widget->setColumnCount(3);
    QList<QTreeWidgetItem*>items;
    for (auto it = opcodes.begin(); it!= opcodes.end(); it++){
        auto tree_w = new QTreeWidgetItem(
                    static_cast<QTreeWidget*>(nullptr),
                    QStringList(QString("%0").arg(it->first)));


        items.append(tree_w);




        std::vector<size_t> mc;
        std::vector<microcode> micro = (it->second).get_microcodes();
        for (auto mic :micro){
            QStringList q_lst = QStringList{};
            mc.push_back(mic.get_operator());
            q_lst.append(QString("%0").arg(mic.get_operator()));
            for (auto operand: mic.get_operands()){
                q_lst.append(QString("%0").arg(operand));
            }
            tree_w->addChild(new QTreeWidgetItem(
                                 static_cast<QTreeWidget*>(nullptr),
                                 q_lst));
        };

    }
    tree_widget->insertTopLevelItems(0,items);

}
void mwin::fill_memory_list(){
    std::vector<size_t> membody = ov.memories[0]->body;
    int iter = 0;
    for (auto memval: membody){
        auto q = std::to_string(iter);
        //auto qs = QString(q.c_str()).toUtf8().toHex();
        auto g = std::to_string(memval);
        //auto gh = QString(g.c_str()).toUtf8().toHex();
        std::string gg = (q + " : "+ g);
        //new QListWidgetItem(tr("%1").arg(gg), ui->memory_list);
        new QListWidgetItem(tr(gg.c_str()), ui->memory_list);
        iter++;
    }
    return;
}
