#ifndef ASSEMBLYGENERATOR_HPP
#define ASSEMBLYGENERATOR_HPP

#include <fstream>
#include "Config.hpp"

class AssemblyGenerator {
  using u32 = uint32_t;

public:
  AssemblyGenerator(std::string_view fileName);
  virtual ~AssemblyGenerator();

public:
  void Init();
  void Increment(u32 i = 1);
  void Decrement(u32 i = 1);
  void ShiftRight(u32 i = 1);
  void ShiftLeft(u32 i = 1);
  void Output();
  void Input();
  void LoopStart();
  void LoopEnd();

private:
  void add_label(std::string_view label);
  void create_message(std::string_view message, std::string_view var_name);
  void create_error(std::string_view var_name);
  void add_footer();

private:
  uint32_t m_loop_idx;
  std::ofstream m_out;
};

#endif // !ASSEMBLYGENERATOR_HPP
