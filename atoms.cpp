#include "atoms.h"
#include "file_loader.h"
Scene *scene_info::scene;


using namespace std;
//auto trim_input = [](const int bits, bitset<max_bits> input){
//		    for (int i = max_bits-1; i > bits-1; i--){input.reset(i);}
//		    return input;};
bus::bus (int bits, int info, custom_bus_item* disp):
  bits(bits), info(info), display(disp) {
  display = new custom_bus_item();
  display->setBrush(Qt::darkGreen);
  scene_info::scene->addItem(display);
}


void bus::set(int arg){
  auto tmp = bitset<max_bits>(arg);
  info = trim_input(bits, tmp);
  display = nullptr;
}

  
//zerar após cada ciclo?

memory::memory(size_t mem_size,
           size_t mem_block_len,
           size_t abus_len,
           size_t dbus_len,
           std::string file_path): len(mem_block_len),
                 body(vector<size_t>(mem_size,0)),
                 addr_bus(make_shared<bus>(abus_len)),
                 data_bus(make_shared<bus>(dbus_len)){
  loadMem(file_path, this);
  display = new CustomRectItem();
  scene_info::scene->addItem(display);
  set_styling(this);
  addr_bus->display->link(this->display);
  data_bus->display->link(this->display);
}


regist::regist(size_t bits,size_t id) :bits(bits), id(id),
				       info(0), in(),
				       out() {
  display = new CustomRectItem();
  scene_info::scene->addItem(display);
  set_styling(this);
}

regist::~regist() {
  delete display;
}
void regist::link_in(shared_ptr<bus> arg) {
  in.push_back(arg);
  if (arg->display != nullptr)
    arg->display->link(this->display);
}
void regist::link_out(shared_ptr<bus> arg) {
  out.push_back(arg);
  if (arg->display != nullptr)
    arg->display->link(this->display);
}
void regist::remove_link_in(shared_ptr<bus> arg){
  in.erase(find (in.begin(),
		 in.end(),
		 arg));
  if (arg->display != nullptr)
    arg->display->remove_link(this->display);
}
void regist::remove_link_out(shared_ptr<bus> arg){
  out.erase(find (out.begin(),
		  out.end(),
		  arg));
  if (arg->display != nullptr)
    arg->display->remove_link(this->display);
}  
void regist::set(int arg) {
  info = trim_input(bits, arg);
  auto value = QString::number(info.to_ulong(),16);
  auto label = QString::number(id,16);
  auto disp= label +": " + value;
  cout << "id:  " << id << endl;
  //display->setText(QString::number(info.to_ulong(),16));
  display->setText(disp);
}
void regist::set(bitset<max_bits> arg) {
  info = arg;
  auto value = QString::number(info.to_ulong(),16);
  auto label = QString::number(id,16);
  auto disp= label +": " + value;
  cout << "id:  " << id << endl;
  //display->setText(QString::number(info.to_ulong(),16));}
  display->setText(disp);
}

//void inc::set(int arg) {

//  info = trim_input(bits, arg+1);
//  auto value = QString::number(info.to_ulong(),16);
//  auto label = QString::number(id,16);
//  auto disp= label +": " + value;
//  cout << "id:  " << id << endl;
//  //display->setText(QString::number(info.to_ulong(),16));
//  display->setText(disp);
//}
//void inc::set(bitset<max_bits> arg) {

//  info = trim_input(bits,arg.to_ulong()+1);
//  auto value = QString::number(info.to_ulong(),16);
//  auto label = QString::number(id,16);
//  auto disp= label +": " + value;
//  cout << "id:  " << id << endl;
//  //display->setText(QString::number(info.to_ulong(),16));}
//  display->setText(disp);
//}





alu::alu() : A(), B(), Z(),
	     f_overflow(0),
	     f_negative(0),
	     f_carry(0),
	     f_zero(0){}

alu::alu(regist *A,
	 regist *B,
     regist *Z)
  : A(A), B(B), Z(Z),
    f_overflow(0),
    f_negative(0),
    f_carry(0),
    f_zero(0),
    f_equal(0){
  display = new CustomRectItem();
  scene_info::scene->addItem(display);
  set_styling(this);
  Z->display->setParentItem(this->display);
  B->display->setParentItem(this->display);
  A->display->setParentItem(this->display);
}
alu::~alu(){
  delete display;
}
bool alu::get_overflow(){return f_overflow;}
bool alu::get_negative(){return f_negative;}
bool alu::get_carry(){return f_carry;}
bool alu::get_zero(){return f_zero;}
bool alu::get_equal(){return f_equal;}
void alu::add() {
    Z->set(trim_input(Z->bits, A->info.to_ulong() + B->info.to_ulong()));
    this->set_flags(1);


                }
void alu::sub() {
    Z->set(trim_input(Z->bits, A->info.to_ulong() - B->info.to_ulong()));
    //Z->info = trim_input(Z->bits, A->info.to_ulong() - B->info.to_ulong());
                this->set_flags(1);}
void alu::SHR(size_t id, size_t amnt) {
    //maybe need to set the flags here?
  if (A->id == id){
    Z->set(trim_input(Z->bits, A->info >>  amnt));
  }
  else if (B->id == id){
    Z->set(trim_input(Z->bits, B->info >>  amnt));
  }
  else {(cout << "id invávlido em SHR" <<endl);}
}
void alu::SHL(size_t id, size_t amnt) {
    //maybe need to set the flags here?
  if (A->id == id){
    Z->set(trim_input(Z->bits, A->info <<  amnt));}
  else if (B->id == id){
    Z->set(trim_input(Z->bits, B->info <<  amnt));}
  else {cout << "id invávlido em SHL" << endl;}
}

void alu::set_flags(size_t op){
    //0 means add, 1 means sub
    //carry is when the result doesnt make sense when interpreted as unsigned
    //overflow is when the result doesn't make sense when interpreted as signed
    f_overflow = 0;
    f_negative = 0;
    f_carry = 0;
    f_zero = 0;
    f_equal = 0;
    auto al = A->info.to_ulong();
    auto bl = B->info.to_ulong();
    auto zl = Z->info.to_ulong();
    if(al ==bl){ f_equal =1;};
    if(zl ==0){f_zero = 1;}
    //need to double check these
    if (al - bl > 0){f_negative =1;}




    //check for overflow
    //figure out their actual size due to bitset fixed size at compile time:
    auto end_offset = A->info.size() - (A->info.size() - A->bits) - 1;
    //cout << "AB: " << ab <<  " AB.flip(start_offset) " << ab.flip(end_offset-1) << endl;
    // case 1: sum of two positives, sign bit true = overflow:
    if (A->info.test(end_offset) && B->info.test(end_offset)){
        if (Z->info.test(end_offset)){f_overflow =1;}
    }
    // case 2: sum of two negatives, sign bit true = overflow:
    if (!(A->info.test(end_offset)) && !(B->info.test(end_offset))){
        if (!Z->info.test(end_offset)){f_overflow =0;}
    }
    // case 3: all if not a sum of both positives or negatives stays off by default, no need to change



    //check for carry
    //checks if there has been an overflow in the unsigned operation
    // if the unadjusted sum is higher than the adjusted sum
    if (op == 0){
        if (zl < al+bl){
            f_carry = 1;
        }
    }
    // if the unadjusted subtraction is lowewr than the adjusted subtraction
    if (op == 1){
        if (zl > al+bl){
            f_carry = 1;
        }
    }
    this->display->setText(QString("E:%1 Z:%2 N:%3 O:%4 C:%5").arg(this->f_equal).arg(this->f_zero).arg(this->f_negative).arg(this->f_overflow).arg(this->f_carry));
    //todo carry


}


size_t get_operator(bitset<max_bits> microcode,
		    size_t operator_size,
		    size_t operand_size,
		    size_t operand_amnt){
  return (trim_input(operator_size,
		     microcode >>(operand_size*operand_amnt))).to_ulong();
}

size_t get_operand(bitset<max_bits> microcode,
		   size_t operand_size,
		   size_t operand_index){
  //cout <<"get_openrand() index: "<< operand_index << "   " <<  trim_input(operand_size,microcode >>(operand_size*operand_index)) << endl;
  //cout <<"get_openrand() index: "<< operand_index << "   " <<  trim_input(operand_size,microcode >>(operand_size*operand_index)).to_ulong() << endl;
  return (trim_input(operand_size,
		     microcode >>(operand_size*operand_index)).to_ulong()
          );
}

control_unit::control_unit(size_t cu_reg_s,
			   size_t operator_s,
			   size_t operand_s,
			   size_t operand_amnt)
  : instruction_register(), instruction_counter(),
    buses(),
    regists_in_out(), map_reg_counter(0),
    map_bus_counter(0), map_alu_counter(0),
    map_mar_counter(0), map_mdr_counter(0),
    operator_size(operator_s), operand_size(operand_s),
    operand_amnt(operand_amnt){
  //im setting the instruction counter size the same as the IR necessarily for now
  display = new CustomRectItem();
  scene_info::scene->addItem(display);
  set_styling(this);
  this->instruction_register = this->get_register(this->make_internal_regist(cu_reg_s));
  this->instruction_counter = this->get_register(this->make_internal_regist(cu_reg_s));
}

microcode control_unit::parse_microcode(size_t microcod){
  vector <size_t> mic_operands{};
  //temporary set to operand_size/2
  auto operand_siz = operand_size/2;
  size_t mic_operator = get_operator(microcod ,
				     operator_size,
                     operand_siz,
                                     2);
                     //operand_amnt);
  //for (int iter = 0; iter < operand_amnt; iter++){
  for (int iter = 0; iter < 2; iter++){
      //temporary set to operand_size/2
      //auto op =   get_operand(microcod, operand_size, iter);
    auto op =   get_operand(microcod, operand_siz, iter);
    cout << "construct_opcode iter inner: " << iter << "   " << op<< endl;

    mic_operands.push_back(op);

  }
  std::reverse(mic_operands.begin(), mic_operands.end());
  //microcode t_microcode{mic_operator,mic_operands};
  microcode t_microcode = microcode(mic_operator,mic_operands);
  return t_microcode;
}

void control_unit::add_opcode(std::vector<size_t> microcodes){
   
  auto construct_opcode = [&](){
			    vector<microcode> mic{};
			    for (auto microcod:microcodes){
			      vector <size_t> mic_operands{};
			      size_t mic_operator = get_operator(microcod ,
								 operator_size,
								 operand_size,
								 operand_amnt);
			      for (int iter = 0; iter < operand_amnt; iter++){
				auto op =   get_operand(microcod, operand_size, iter);
				cout << "construct_opcode iter : " << iter << "   " << op<< endl;

				mic_operands.push_back(op);
			      }
			      std::reverse(mic_operands.begin(), mic_operands.end());
			      microcode t_microcode{mic_operator,mic_operands};
			      cout << mic_operands[0] << " " << mic_operands[1] << endl;
			      mic.push_back(t_microcode);
			    }
			    cout << mic[0].get_operands()[0] << " " <<mic[0].get_operands()[1] << endl;
                return opcode(mic);};
  opcodes.insert({opcodes.size(), construct_opcode()});
}



size_t control_unit::make_bus(int bits){
  buses.insert(make_pair(map_bus_counter, make_shared<bus> (bits)));
  map_bus_counter++;
  return map_bus_counter - 1;
}

size_t control_unit::make_regist(int bits){
  regists_in_out.insert(make_pair(map_reg_counter,
				  make_tuple(make_shared<regist>(bits,map_reg_counter)
					     ,
					     false,false)));
  auto nreg = this->get_register(map_reg_counter);


  //info = trim_input(bits, arg);
  auto value = QString::number(nreg->info.to_ulong(),16);
  auto label = QString::number(map_reg_counter,16);
  auto disp= label +": " + value;
  //cout << "id:  " << id << endl;
  //display->setText(QString::number(info.to_ulong(),16));
  nreg->display->setText(disp);
  //nreg->display->setText(QString::number(nreg->info.to_ulong()));

  map_reg_counter++;
  
  return map_reg_counter - 1;
}

size_t control_unit::make_internal_regist(int bits){
  regists_in_out.insert(make_pair(map_reg_counter,
				  make_tuple(make_shared<regist>(bits,map_reg_counter
								 ),
					     false,false)));
  auto nreg = this->get_register(map_reg_counter);
  nreg->display->setParentItem(this->display);
  nreg->display->setText(QString::number(nreg->info.to_ulong()));
  nreg->set(0);
  map_reg_counter++;
  //cout<< map_reg_counter<< endl;
  return map_reg_counter - 1;
}
//reolver as linkagens para permitir o o input de dados na memoria
//psure its already solved
size_t control_unit::make_mdr(int bits, const shared_ptr<memory> &mem){
  auto id = make_regist(bits);
  mdrs_id.insert(make_pair(map_mdr_counter, id));
  get_register(id)->link_in(mem->data_bus);
  get_register(id)->link_out(mem->data_bus);
  map_mdr_counter++;
  return map_mdr_counter - 1;
}
  
size_t control_unit::make_mar(const int bits, const shared_ptr<memory> &mem){
  auto id = make_regist(bits);
  mars_id.insert(make_pair(map_mar_counter, id));
  get_register(id)->link_out(mem->addr_bus);
  map_mar_counter++;
  return map_mar_counter - 1;
}
  
size_t control_unit::make_alu(regist *A,
			      regist *B,
			      regist *Z){

  
  alus.insert(make_pair(map_alu_counter, make_shared<alu>(A,B,Z)));
  map_alu_counter++;
  return map_alu_counter -1;
}
size_t control_unit::make_alu(size_t num_bits){
  //auto Z = this->get_register(this->make_regist(num_bits));
  auto A = this->get_register(this->make_regist(num_bits));
  auto B = this->get_register(this->make_regist(num_bits));
  auto Z = this->get_register(this->make_regist(num_bits));
  //auto Z = this->get_register(this->make_regist(num_bits));
  //auto Z = this->get_register(this->make_regist(num_bits));
  alus.insert(make_pair(map_alu_counter, make_shared<alu>(A,B,Z)));
  map_alu_counter++;
  return map_alu_counter -1;
}

regist *control_unit::get_register(size_t id){
  return get<0>(regists_in_out.at(id)).get();}

regist *control_unit::get_mar(size_t id){return get_register(mars_id.at(id));}

void control_unit::remove_regist(size_t id) {
  get<0>(regists_in_out.at(id)).reset();
}
void control_unit::remove_alu(size_t id) {
  alus.at(id).reset();
}
regist *control_unit::get_mdr(size_t id){return get_register(mdrs_id.at(id));}


bool control_unit::get_register_in(size_t id){return get<1>(regists_in_out.at(id));}
bool control_unit::get_register_out(size_t id){return get<2>(regists_in_out.at(id));}
shared_ptr<bus> control_unit::get_bus(size_t id){return buses.at(id);}
shared_ptr<alu> control_unit::get_alu(size_t id){return alus.at(id);}
void control_unit::set_in(size_t id){get<1>(regists_in_out.at(id)) = true;}
void control_unit::set_out(size_t id){get<2>(regists_in_out.at(id)) = true;}

void control_unit::assignment(size_t id_reg1, size_t id_reg2){
  set_out(id_reg1);
  set_in(id_reg2);
  cout <<get_register_out(id_reg1) << "  "<< get_register_in(id_reg1) << endl
       <<get_register_in(id_reg2) <<"  " <<get_register_out(id_reg1) << endl;
}
void control_unit::assignment_literal(size_t literal, size_t id_reg){
  //set_out(id_reg1);
  set_in(id_reg);
  //what i'm doing here is setting the bus value directly, so I don't need to make a different register for the IR operand in case of literals
  auto buses = this->get_register(id_reg)->in;
  for (auto &bu:buses){
      //should probably change it later so that only the buses that have connection with the IR get filled
      bu->set(literal);
  }
}
void control_unit::add(size_t id){
  get_alu(id)->add();
    
  cout << "A " << get_alu(id)->A->id << ": " << get_alu(id)->A->info << endl;
  cout << "B " << get_alu(id)->B->id << ": " << get_alu(id)->B->info  << endl;
  cout << "Z " << get_alu(id)->Z->id << ": " << get_alu(id)->Z->info << endl;

}

void control_unit::sub(size_t id){
  get_alu(id)->sub();
    
  cout << "A " << get_alu(id)->A->id << ": " << get_alu(id)->A->info << endl;
  cout << "B " << get_alu(id)->B->id << ": " << get_alu(id)->B->info  << endl;
  cout << "Z " << get_alu(id)->Z->id << ": " << get_alu(id)->Z->info << endl;
}
//no momento só é possível usar SHR  e SHL no primeiro registrador da ALU (A)
void control_unit::SHR(size_t id_alu, size_t amnt){
  auto A_id = get_alu(id_alu)-> A->id;
  get_alu(id_alu)->SHR(A_id, amnt);
    
  cout << "A " << get_alu(id_alu)->A->id << ": " << get_alu(id_alu)->A->info << endl;
  cout << "Z " << get_alu(id_alu)->Z->id << ": " << get_alu(id_alu)->Z->info << endl;
}

void control_unit::SHL(size_t id_alu, size_t amnt){
  auto A_id = (get_alu(id_alu)-> A->id);
  (get_alu(id_alu)->SHL(A_id, amnt));
      
  cout << "A " << get_alu(id_alu)->A->id << ": " << get_alu(id_alu)->A->info << endl;
  cout << "Z " << get_alu(id_alu)->Z->id << ": " << get_alu(id_alu)->Z->info << endl;
}

void control_unit::read( regist *mar,
			 regist *mdr,
			 const vector<shared_ptr<memory>> &memories){
  for(auto& mem:memories){
    if(find(mar->out.begin(), mar->out.end(), mem->addr_bus) != mar->out.end() &&
       find(mdr->in.begin(), mdr->in.end(), mem->data_bus) != mdr->in.end()){
      mdr->set(mem->body.at(mar->info.to_ulong()));
    }
  }
}

void control_unit::write( regist *mar,
			  regist *mdr,
			  const vector<shared_ptr<memory>> &memories){
  for(auto& mem:memories){
    if(find(mar->out.begin(), mar->out.end(), mem->addr_bus) != mar->out.end() &&
       find(mdr->out.begin(), mdr->out.end(), mem->data_bus) != mdr->out.end()){
      mem->body.at(mar->info.to_ulong()) = mdr->info.to_ulong();
    }
  }
}

void control_unit::reg_out(){
  vector<shared_ptr<regist>> outs;
  auto fill_vec_of_out = [&](){
			   for(auto& pair:regists_in_out){
			     if(get<2>(pair.second) == true){
			       outs.push_back(get<0>(pair.second));
			       get<2>(pair.second) = false;}
			   }};
  fill_vec_of_out();

  //não verifica se tem out repetidos, colocar depois (?)
  //register -> bus
  auto transfer_out_data_to_bus = [&](){
				    for(auto& registrador:outs){
				      for(auto& bus:registrador->out){
					cout << "******* REGISTER "
					     << registrador->id <<  "  ->  BUS ********" << endl
					     << "bus antes: " <<bus->info << endl
					     << "reg val : " <<registrador->info.to_ulong()
					     << endl;
					bus->set(registrador->info.to_ulong());
					cout << "bus depois: "
					     << bus->info << endl;}}};
  transfer_out_data_to_bus();
}
void control_unit::reg_in(){
  vector<shared_ptr<regist>> ins;
  // //bus -> register
  auto fill_vec_of_in = [&](){
			  for(auto& pair:regists_in_out){
			    if(get<1>(pair.second) == true)
			      ins.push_back(get<0>(pair.second));
			    get<1>(pair.second) = false;}};
  fill_vec_of_in();



  auto transfer_bus_data_to_in = [&](){
				   for(auto& registrador:ins){
				     for(auto& bus:registrador->in){
				       cout << "******* BUS -> REGISTER "
					    << registrador->id <<" ********" << endl
					    << "register  antes: " <<registrador->info
					    << endl;
				       registrador->set(bus->info.to_ulong());
				       cout << "register depois: "
					    << registrador->info << endl;}}};
  transfer_bus_data_to_in();
}
overseer::overseer() :  QObject(), control_units(), memories(){}
overseer::overseer(QObject *mwid) : QObject(mwid), control_units(), memories(), mwidget(mwid){}
overseer::~overseer(){}
control_unit *overseer::make_cu(size_t cu_reg_s,
				size_t operator_s,
				size_t operand_s,
				size_t operand_amnt)
{
  control_units.push_back(make_shared<control_unit>(cu_reg_s,
						    operator_s,
						    operand_s,
						    operand_amnt
						    ));
  return control_units.back().get();
}

void overseer::cycle(){
    //not actually one cycle, the cycle is decided inside by the sync_bus()
  for(auto& cu:control_units){
    int ret = cu->opcode_execute(memories);
    if (ret == -1){break;}

  }
}


// implementar controle sobre ins e outs individuais dos registradores.(?)




