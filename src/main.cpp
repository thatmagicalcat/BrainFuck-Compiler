#include <iostream>
#include <string_view> 
#include <fstream>

#include "Tokenizer.hpp"
#include "Compiler.hpp"
#include "Interpreter.hpp"

int main(const int argc, const char **argv) {
  if (argc < 3) {
    std::cerr << "Not sufficient arguments\n";
    return EXIT_FAILURE;
  }
  
  const char *file_name = argv[2];

  std::ifstream in(file_name);
  std::string data { std::istreambuf_iterator<char>(in), {} };

  std::string_view command = argv[1];
  auto tokens = Tokenize(data);

  if (command == "sim") {
    exec(tokens);
  } else if (command == "com") {
    compile(tokens, "output.asm");

    std::system("nasm -felf64 output.asm -Ox && ld -o output output.o && rm -rf output.o output.asm");
  } else {
    std::cout << "No subcommand named: '" << command << "'\n";
    return 1;
  }
}
