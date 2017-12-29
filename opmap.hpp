#include <vector>
#include <map>
#ifndef OPMAP_HPP
#define OPMAP_HPP

const std::map<size_t, std::vector<size_t>> opmap
  {{0, {0x147, 0x147, 0x400, 0x300}},
   {1, {0x147, 0x147, 0x400, 0x300}},
   {2, std::vector<size_t>{0x147}},
   {3, std::vector<size_t>{0x400}}}
;

#endif //OPMAP_HPP
