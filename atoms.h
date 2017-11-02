
#ifndef ATOMS_H
#define ATOMS_H
#include <memory>
#include <functional>
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <map>
#include <set>
#include <QtCore/QObject>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include "container.hpp"
#include "styles.hpp"
#include "customrectitem.h"
#include "custom_bus_item.h"

#ifndef CONFIG
#define CONFIG
const size_t max_bits = 16;
#endif





class bus : public QObject{
Q_OBJECT
public:
  int bits;
  std::bitset <max_bits> info;
  custom_bus_item *display;
  void set (int arg);
  bus (int bits);
  bus (int bits, Scene*);
  bus (int inf, int bits);

};
class memory : public QObject{
Q_OBJECT
public:
  size_t const len;
  std::vector<size_t> body;
  std::shared_ptr<bus> addr_bus;
  std::shared_ptr<bus> data_bus;
  memory (size_t mem_size, size_t len);
  memory (size_t mem_size, size_t mem_block_len, size_t abus_len, size_t dbus_len);
};

class regist : public QObject {
Q_OBJECT
public:
  size_t bits;
  size_t id;
  std::bitset<max_bits> info;
  std::vector<std::shared_ptr<bus>> in;
  std::vector<std::shared_ptr<bus>> out;
  mov_cnt<CustomRectItem> * display;
  regist();
  regist(size_t bits,size_t id);
  //regist(size_t bits,size_t id, QWidget *parent);
  regist(size_t bits,size_t id, Scene *scene);
  ~regist();
  void link_in(std::shared_ptr<bus> arg);
  void link_out(std::shared_ptr<bus> arg);
  void remove_link_in(std::shared_ptr<bus> arg);
  void remove_link_out(std::shared_ptr<bus> arg);
  void set(int arg);
  void set(std::bitset<max_bits> arg);
  
};


class alu : public QObject{
Q_OBJECT
public:
  regist *A;
  regist *B;
  regist *Z;
  bool f_overflow;
  bool f_negative;
  bool f_carry;
  bool f_zero;
  mov_cnt<CustomRectItem> *display;
  Scene *scene;
  alu();
  alu(regist *,
      regist *,
      regist *,
      Scene *scene);
  ~alu();
  bool get_overflow();
  bool get_negative();
  bool get_carry();
  bool get_zero();
  void add();
  void sub();
  void SHR(size_t id, size_t amnt);
  void SHL(size_t id, size_t amnt);
};

size_t get_operator(std::bitset<max_bits> microcode,
            size_t operator_size,
            size_t operand_size,
            size_t operand_amnt);


size_t get_operand(std::bitset<max_bits> microcode,
           size_t operand_size,
           size_t operand_index);





class control_unit : public QObject{
Q_OBJECT
public:
  regist *cu_reg;
  std::map <size_t,
        std::shared_ptr<bus>> buses;
  std::map <size_t,
        std::tuple<std::shared_ptr<regist>,
                  bool,
                  bool>> regists_in_out;
  std::map <size_t,
        std::shared_ptr<alu>> alus;
  std::map <size_t,
        std::vector<size_t>> opcodes;
  size_t map_reg_counter;
  size_t map_bus_counter;
  size_t map_alu_counter;
  size_t map_mar_counter;
  size_t map_mdr_counter;
  size_t map_func_counter;
  size_t operator_size;
  size_t operand_size;
  size_t operand_amnt;
  std::map<size_t, size_t> mdrs_id;
  std::map<size_t, size_t> mars_id;
  mov_cnt<CustomRectItem> *display;
  Scene *scene;
  // control_unit(size_t cu_reg_s,
  // 	       size_t operator_s,
  // 	       size_t operand_s,
  // 	       size_t operand_amnt);

  control_unit(size_t cu_reg_s,
	       size_t operator_s,
	       size_t operand_s,
	       size_t operand_amnt,
	       Scene *scen); 
  control_unit(size_t arg);

  size_t make_bus(int bits);
  size_t make_regist(int bits);
  size_t make_internal_regist(int bits, QObject *parent);
    //reolver as linkagens para permitir o o input de dados na memoria
  size_t make_mdr(int bits, const std::shared_ptr<memory> &mem);
  size_t make_mar(const int bits, const std::shared_ptr<memory> &mem);
  size_t make_alu(regist *A, regist *B, regist *Z);
  size_t make_alu(size_t);

  void remove_regist(size_t);
  void remove_alu(size_t);
  
  
  regist *get_register(size_t id);
  regist *get_mar(size_t id);
  regist *get_mdr(size_t id);
  bool get_register_in(size_t id);
  bool get_register_out(size_t id);
  std::shared_ptr<bus> get_bus(size_t id);
  std::shared_ptr<alu> get_alu(size_t id);
  void set_in(size_t id);
  void set_out(size_t id);

  void assignment(size_t id_reg1, size_t id_reg2);
  void add(size_t id);
  void sub(size_t id);
  //no momento só é possível usar SHR  e SHL no primeiro registrador da ALU (A)
  void SHR(size_t id_alu, size_t amnt);
  void SHL(size_t id_alu, size_t amnt);

  void read( regist *mar,
         regist *mdr,
        const std::vector<std::shared_ptr<memory>> &memories);
  void write( regist *mar,
          regist *mdr,
         const std::vector<std::shared_ptr<memory>> &memories);
  void execute(const std::vector<std::shared_ptr<memory>> &memories);
  void opcode_execute(const std::vector<std::shared_ptr<memory>> &);
  void interpret_minst(size_t,const std::vector<std::shared_ptr<memory>> &);
  void reg_out();
  void reg_in();
  void sync_bus();
		 
};
class overseer : public QObject{
  Q_OBJECT
public:
    overseer();
  overseer(QObject *parent);
~overseer();
  control_unit *make_cu(size_t cu_reg_s,
			   size_t operator_s,
			   size_t operand_s,
			size_t operand_amnt,
			Scene *scen);
  std::vector <std::shared_ptr<control_unit>> control_units;
  std::vector <std::shared_ptr<memory>> memories;
  Scene *scene;
  QObject *mwidget;

public slots:
    void cycle();
};

#endif
