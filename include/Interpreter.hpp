#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <vector>
#include <iostream>
#include <string>

#include "Tokens.hpp"
#include "Config.hpp"

void exec(const std::vector<TOKENS> &vec) {
  unsigned char cells[CELL_COUNT] = {0};
  std::size_t ptr = 0, loop_idx = -1, loop_ptr = -1;
  bool loop = 0;

  for (std::size_t i = 0; i < vec.size(); i++) {
    if (loop && cells[loop_ptr] == 0) loop = 0;
    else if (loop && vec[i] == LOOP_END) i = loop_idx;

    switch (vec[i]) {
      [[likely]] case INCREMENT:
        if (cells[ptr] == 255) { std::cout << "Error '+': Cannot increment more than 255\n"; exit(EXIT_SUCCESS); }
        ++ cells[ptr];
        break;
      [[likely]] case DECREMENT:
        if (cells[ptr] == 0) { std::cout << "Error '-': Cannot decrement zero\n"; exit(EXIT_SUCCESS); }
        -- cells[ptr];
        break;
      case OUTPUT:
        std::cout << (char)cells[ptr];
        break;
      case LEFT:
        if (!ptr) { std::cout << "Error: out of range! can't go before the first cell.\n"; exit(EXIT_SUCCESS); }
        ptr--;
        break;
      case RIGHT:
        if (ptr == CELL_COUNT) { std::cout << "Error: out of memory!\n"; exit(EXIT_SUCCESS); }
        ptr++;
        break;
      case LOOP_START:
        loop = 1;
        loop_ptr = ptr;
        loop_idx = i;
        break;    
      case LOOP_END:
        loop = 0;
        break;
      [[unlikely]] case INPUT:
        unsigned char inp; std::cin >> inp;
        cells[ptr] = inp;
        break;
    }
  }
}

#endif // !INTERPRETER_HPP
