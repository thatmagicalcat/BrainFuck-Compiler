#include "AssemblyGenerator.hpp"

AssemblyGenerator::AssemblyGenerator(std::string_view fileName): m_loop_idx(0) {
  m_out.open(fileName.data());
  Init();
}

AssemblyGenerator::~AssemblyGenerator() {
  add_footer();
  m_out.close();
}

void AssemblyGenerator::Init() {
  m_out << "section .data\n";
  m_out << "\tarray times " << CELL_COUNT << " db 0\n";
  m_out << "\tnewline db 0xA\n";
  m_out << "\tbuffer times 2 db 0\n"; // the buffer which will be used to print and take input

  // Error Messages
  create_message("Error '-': Cannot decrement zero", "err_msg_zero");
  create_message("Error '+': Cannot increment more than 255", "err_msg_max");
  create_message("Error '>': already at the last cell", "err_msg_last");
  create_message("Error '<': already at the first cell", "err_msg_first");
  //

  m_out << "section .text\n";
  m_out << "global _start\n";

  // putChar function
  m_out << "putChar:\n"
        << "\tmov eax, 1\n"
        << "\tmov edi, 1\n"
        << "\tmov esi, buffer\n"
        << "\tmov edx, 1\n"
        << "\tsyscall\n"

        // i don't wanna print newline
        // << "\tmov esi, newline\n"
        // << "\tsyscall\n"
        
        << "\tret\n";

  // getChar function
  m_out << "getChar:\n"
        << "\tmov eax, 0\n"
        << "\tmov edi, 0\n"
        << "\tmov esi, buffer\n"
        << "\tmov edx, 2\n"       // we will be reading two characters instead of one, because of the newline character
        << "\tsyscall \n"
        << "\tret\n";
  
  // main function
  m_out << "_start:\n";

  // Pointer to the first element of the array (will change when shift functions are called)
  m_out << "\tmov ebx, array\n";

  // keep track of the array index
  // this is very important, its here just to check some conditions
  m_out << "\tmov edx, 0\n"; 
}

void AssemblyGenerator::Increment(u32 i) {
  add_label("Increment");

  // Check if the current cell's value is 255
  m_out << "\tmov al, byte [ebx]\n";
  m_out << "\tcmp al, 255\n";
  m_out << "\tjz label_err_msg_max\n";

  // load the current cell's value in al register
  m_out << "\tadd al, " << i << '\n';
  m_out << "\tmov byte [ebx], al\n";
}

void AssemblyGenerator::Decrement(u32 i) {
  add_label("Decrement");

  // Check if the current cell's value is 0
  m_out << "\tmov al, byte [ebx]\n";
  m_out << "\tcmp al, 0\n";
  m_out << "\tjz label_err_msg_zero\n";

  // load the current cell's value in eax register
  m_out << "\tsub al, " << i << '\n';
  m_out << "\tmov byte [ebx], al\n";
}

void AssemblyGenerator::ShiftRight(u32 i) {
  add_label("Shift Right");

  m_out << "\tcmp edx, " << CELL_COUNT << "\n";
  m_out << "\tjz label_err_msg_last\n";

  m_out << "\tadd ebx, " << i << "\n";
  m_out << "\tadd edx, " << i << "\n";
}

void AssemblyGenerator::ShiftLeft(u32 i) {
  add_label("Shift Left");

  m_out << "\tcmp edx, 0\n";
  m_out << "\tjz label_err_msg_first\n";

  m_out << "\tsub ebx, " << i << "\n";
  m_out << "\tsub edx, " << i << "\n";
}

void AssemblyGenerator::Output() {
  add_label("Print Char");

  m_out << "\tmov al, byte [ebx]\n"
        << "\tmov byte [buffer], al\n"
        << "\tcall putChar\n";
}

void AssemblyGenerator::Input() {
  add_label("Get Char");

  m_out << "\tcall getChar\n"
        << "\tmov al, byte [buffer]\n"
        << "\tmov byte [ebx], al\n";
}

void AssemblyGenerator::LoopStart() {
  add_label("Loop Start");

  m_out << "\tmovzx ecx, byte [ebx]\n"
        << "init_loop_" << m_loop_idx << ":\n"
        << "\tpush rcx\n";
}

void AssemblyGenerator::LoopEnd() {
  add_label("Loop End");

  m_out << "\tpop rcx\n"
        << "\tdec rcx\n"
        << "\tcmp rcx, 0\n"
        << "\tjnz init_loop_" << m_loop_idx << '\n';

  ++ m_loop_idx;
}

void AssemblyGenerator::add_label(std::string_view label) {
  m_out << "\t;; ---- " << label << " ----\n";
}

void AssemblyGenerator::create_message(std::string_view message, std::string_view var_name) {
  m_out << "\t" << var_name << " db \"" << message << "\", 10\n";
  m_out << "\t" << var_name << "_len equ $-" << var_name << "\n";
}

void AssemblyGenerator::create_error(std::string_view var_name) {
  m_out << "label_" << var_name << ":\n";
  m_out << "\tmov eax, 1\n";                        // system call number for write
  m_out << "\tmov edi, 1\n";                        // file descriptor for stdout
  m_out << "\tmov esi, " << var_name << "\n";     // message string
  m_out << "\tmov edx, " << var_name << "_len\n"; // message length
  m_out << "\tsyscall\n";                           // call exit function
  m_out << "\tjmp exit_program\n";                  // jump to exit label to exit program
}

void AssemblyGenerator::add_footer() {
  m_out << "exit_program:\n";
  m_out << "\tmov rax, 60" << '\n';
  m_out << "\tmov rdi, 0" << '\n';
  m_out << "\tsyscall" << '\n';

  create_error("err_msg_zero");
  create_error("err_msg_max");
  create_error("err_msg_last");
  create_error("err_msg_first");
}
