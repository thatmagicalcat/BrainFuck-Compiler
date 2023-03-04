#include "Tokenizer.hpp"

std::vector<TOKENS> Tokenize(const std::string &code) {
  std::vector<TOKENS> vec;

  for (const char &c : code) {
    switch (c) {
      case '>': {
        vec.push_back(RIGHT);
        break;
      }

      case '<': {
        vec.push_back(LEFT);
        break;
      }

      case '+': {
        vec.push_back(INCREMENT); 
        break;
      }

      case '-': {
        vec.push_back(DECREMENT);
        break;
      }

      case '.': {
        vec.push_back(OUTPUT);
        break;
      }

      case ',': {
        vec.push_back(INPUT);
        break;
      }

      case '[': {
        vec.push_back(LOOP_START);
        break;
      }

      case ']': {
        vec.push_back(LOOP_END);
        break;
      }

      case '\n':
      case '\t':
      case '\r':
        break;
      
      default: {
        std::cerr << "[Error] Unexpected character: '" << c << "'\n";
        std::exit(1);

        break;
      }
    }
  }

  return vec;
}
