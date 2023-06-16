#include "mwin.h"
#include <ui_mwin.h>
#include <memory>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGraphicsView>
#include <QtGui/QPen>
#include <string>
#include <iostream>
#include <sstream>
#include <QThread>
#ifdef slots
#undef slots
#endif

using namespace std;
 
mwin::mwin(QWidget *parent) :
  QMainWindow(parent),
  ov(this),
  ui(new Ui::mwin)
{
  ui->setupUi(this);
  auto scene = new Scene(centralWidget());
  scene->setSceneRect(0,0,800,750);
  scene_info::scene = scene;
  new QGraphicsView(scene, centralWidget());
  //view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
  //ov.make_cu(12,4,4,2)->display->info.setText("control unit 0");
  ov.make_cu(REGISTER_SIZE,8,8,1)->display->info.setText("control unit 0");


  ov.memories.push_back(make_shared<memory>(MEMSIZE, REGISTER_SIZE, REGISTER_SIZE, REGISTER_SIZE));
  ui->memory_fpath_input->setText(MEMTEMPHARDCODEDPATH);
  ui->opcodes_fpath_input->setText(OPCODETEMPHARDCODEDPATH);
  auto cu = ov.control_units[0];
  auto mem = ov.memories[0];
  cu->opcodes = opmap;
  cu->add_opcode(std::vector<size_t>{0x701,0x175});
  cu->make_alu(REGISTER_SIZE);
  cu->get_alu(0)->A->set(std::bitset<max_bits>(0xfff));
  mem->body.at(0x002) = 15;
  //cu->get_register(cu->make_regist(12));
  cu->make_regist(REGISTER_SIZE);
  cu->make_regist(REGISTER_SIZE);

  for(auto item:cu->regists_in_out){cout << item.first << endl;}
  cu->get_register(4)->set(0x002);
  cu->get_register(5)->set(0x003);
  auto bu = cu->get_bus(cu->make_bus(REGISTER_SIZE));
  for(auto& item:cu->regists_in_out){
    (get<0>(item.second))->link_in(bu);
    (get<0>(item.second))->link_out(bu);
  }
  auto mar_id = cu->make_mar(REGISTER_SIZE, mem);
  auto mdr_id = cu->make_mdr(REGISTER_SIZE, mem);
  //auto mar_id = cu->make_mar(12, mem);
  cout <<   cu->get_register(4)->info << endl;  
  cout <<   cu->get_register(5)->info << endl;  
  auto mdr = cu->get_mdr(mdr_id);
  mdr->link_in(bu);  
  mdr->link_out(bu);
  auto mar = cu->get_mar(mar_id);
  mar->link_in(bu);
  mar->link_out(bu);
  mar->set(0x002);
  mdr->set(0x002);
  cu->instruction_register->set(0xF53);
 
  
  //ov.cycle();
  //on_criar_regist_clicked(); 
//   cout << "mar " << mar->id << " :" << mar->info << endl
//        << "mdr " << mdr->id << " :" << mdr->info << endl
//        << "local na memoria: " << mem->body.at(mar->info.to_ulong()) << endl
//        << "mdr info: " << mdr->info.to_ulong() << endl;

 this->fill_opcodes_tree();
 this->fill_memory_list();
  // qApp->processEvents();
// std::string opcodes[MAXOPCODE][MAXMICROC];
// std::string path{OPCODETEMPHARDCODEDPATH};
// loadOpcode(opcodes, path);
// std::string Dopcode[100][MAXMICROC];
 //opcode ocs[100][MAXMICROC]{};
 //parseAllOpcodes(opcodes,  Dopcode);
 //cu->opcodes = parseAllOpcodes(opcodes,  Dopcode);
 //cout << "oi" << endl;





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
      //control_unit->instruction_register->set(std::stoul(ui->repl_input->text().toStdString(),nullptr,16));
      control_unit->instruction_register->set(std::stoi(ui->repl_input->text().toStdString(),nullptr,16));
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
  //NEED TO FIX THIS?? seems to work fine
  if(auto control_unit = this->ov.control_units.at(ui->repl_cu_select->value())){
    if(ui->microcode_repl_input->text().length() ==
       (control_unit->operand_size * control_unit->operand_amnt + control_unit->operator_size)/4){
      ui->microcode_repl_display->appendPlainText(ui->repl_input->text());
      //control_unit->cu_reg->set(std::stoul(ui->microcode_repl_input->text().toStdString(),nullptr,16));
      size_t r = std::stoul(ui->microcode_repl_input->text().toStdString(),nullptr,16);
      microcode microcod = control_unit->parse_microcode(r);
      cout << microcod.get_operator() << microcod.get_operand(0) << microcod.get_operand(1)<<endl;
      control_unit->interpret_minst(microcod,ov.memories);
      control_unit->sync_bus();
      //this->ov.cycle();
      //auto cu = this->ov.control_units.at(ui->repl_cu_select->value());
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
    tree_widget->setColumnCount(4);
    QList<QTreeWidgetItem*>items;
    for (auto it = opcodes.begin(); it!= opcodes.end(); it++){
        std::stringstream stream;
        stream<<std::hex << it->first;
        std::string opcode_num = stream.str();
        auto tree_w = new QTreeWidgetItem(
                    static_cast<QTreeWidget*>(nullptr),
                    QStringList(QStringList{QString("%0").arg(opcode_num.c_str()),
                                            QString(""),
                                            QString(""),
                                            QString(it->second.literal.c_str())}));


        items.append(tree_w);
        std::vector<size_t> mc;
        std::vector<microcode> micro = (it->second).get_microcodes();
        for (auto mic :micro){
            QStringList q_lst = QStringList{};
            mc.push_back(mic.get_operator());
            q_lst.append(QString("%0").arg(QString::number(mic.get_operator(),16)));
            for (auto operand: mic.get_operands()){
                q_lst.append(QString("%0").arg(QString::number(operand,16)));
            }
            q_lst.append(QString(mic.literal.c_str()));
            tree_w->addChild(new QTreeWidgetItem(
                                 static_cast<QTreeWidget*>(nullptr),
                                 q_lst));
        };

    }
    tree_widget->insertTopLevelItems(0,items);

}

void mwin::fill_memory_list(){
    //std::stringstream stream;
    std::vector<size_t> membody = ov.memories[0]->body;
    int iter = 0;
    for (auto memval: membody){
        std::stringstream stream;
        auto q = std::to_string(iter);
        //auto qs = QString(q.c_str()).toUtf8().toHex();
        auto g = std::to_string(memval);
        //auto gh = QString(g.c_str()).toUtf8().toHex();
        //std::string gg = (q + " : "+ g);
        stream<<std::hex << iter << std::hex << " : " << std::hex << memval;
        std::string gg = stream.str();
        //new QListWidgetItem(tr("%1").arg(gg), ui->memory_list);
        auto n = new QListWidgetItem(tr(gg.c_str()), ui->memory_list);//, Qt::ItemIsEditable);
        n->setFlags(n->flags() | Qt::ItemIsEditable);
        iter++;
    }
    return;
}

void mwin::on_pushButton_clicked()
{
    ui->memory_list->clear();
    fill_memory_list();
}

void mwin::on_memory_list_itemChanged(QListWidgetItem *item)
{
    auto po = ui->memory_list->row(item);
    int val,radix;

    //if(ui->toggle_hex_memory_list->checkState()){
        char scanf_str_1[] = "%*x : %x";
        char scanf_str_2[] = "%x";
        radix = 16;
        auto ret = sscanf(item->text().toStdString().c_str(), scanf_str_1 , &val);
        if (ret == -1){
            cout << item->text().toStdString().c_str() << endl;
            auto ret = sscanf(item->text().toStdString().c_str(), scanf_str_2 , &val);
            if (ret == -1){
                return;
            }
        }

    //}
//    else{
//        char scanf_str_1[] = "%*d : %d";
//        char scanf_str_2[] = "%d";
//        radix = 10;
//        auto ret = sscanf(item->text().toStdString().c_str(), scanf_str_1 , &val);
//        if (ret == -1){
//            auto ret = sscanf(item->text().toStdString().c_str(), scanf_str_2 , &val);
//            if (ret == -1){
//                return;
//            }
//        }
//    }

    if (po < 5){
    cout << "po" << ": " << po<< endl;
    cout << "val: " << val << endl;
    cout << "radix: " << radix << endl;
    }
    item->setText(QString("%1 : %2").arg(po,0,radix).arg(val,0,radix));
    ov.memories[0]->body[po] = val;
    return;
}

void mwin::on_toggle_hex_memory_list_stateChanged(int arg1)
{
    if (arg1){
        ui->memory_list->clear();
        this->fill_memory_list();
    }
    else{
        ui->memory_list->clear();
        this->fill_memory_list();
    }
}

void mwin::on_pushButton_2_clicked()
{
    QSettings settings("MyCompany", "MyApp");
    //settings.setValue("geometry", QMainWindow::saveGeometry(1));
    settings.setValue("windowState",QMainWindow::saveState(1));
}

void mwin::on_pushButton_3_clicked()
{
    QSettings settings("MyCompany", "MyApp");
    //QMainWindow::restoreGeometry(settings.value("myWidget/geometry",1).toByteArray());
    QMainWindow::restoreState(settings.value("myWidget/windowState",1).toByteArray());


}

void mwin::on_memory_fpath_input_returnPressed()
{
  //need to add a place to decide which memory im loading, when multiple memories get proper support
  memory* mem = ov.memories[0].get(); //get because its a shared pointer
  string path = ui->memory_fpath_input->text().toStdString();
  //cout << path << endl;
  loadMem(path, mem);
  ui->memory_list->clear();
  this->fill_memory_list();
}

void mwin::on_opcodes_fpath_input_returnPressed()
{
    control_unit* cu = ov.control_units[ui->repl_cu_select->value()].get(); //get because its a shared pointer
    string path = ui->opcodes_fpath_input->text().toStdString();
    std::string opcodes[MAXOPCODE][MAXMICROC];
    loadOpcode(opcodes, path);
    std::string Dopcode[100][MAXMICROC];
    cu->opcodes = parseAllOpcodes(opcodes,  Dopcode);
    ui->opcode_display->clear();
    this->fill_opcodes_tree();
}

void mwin::on_fetch_button_clicked()
{
    control_unit* cu = ov.control_units[ui->repl_cu_select->value()].get(); //get because its a shared pointer
    cu ->opcode_execute(ov.memories,true);
    //QtConcurrent::run(cu,&control_unit::opcode_execute,ov.memories,true,10000);
}

void mwin::on_execute_button_clicked()
{
    control_unit* cu = ov.control_units[ui->repl_cu_select->value()].get(); //get because its a shared pointer
    cu->opcode_execute(ov.memories);
}


void mwin::on_fetch_execute_button_clicked()
{
    control_unit* cu = ov.control_units[ui->repl_cu_select->value()].get(); //get because its a shared pointer
    cu->opcode_execute(ov.memories,true);
    cu->opcode_execute(ov.memories);
}
