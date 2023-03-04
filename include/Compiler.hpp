#ifndef COMPILER_HPP
#define COMPILER_HPP

#include <cstdint>
#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <string>
#include <string_view>

#include "AssemblyGenerator.hpp"
#include "Config.hpp"
#include "Tokens.hpp"

struct TokenItem {
  TOKENS token;
  long freq;
};

std::vector<TokenItem> fold(const std::vector<TOKENS> &vec) {
  std::vector<TokenItem> tokens;

  for (auto it = vec.cbegin(); it != vec.cend(); ++ it) {
    auto end = it + 1;
    for (; end != vec.cend() && *end == *it; ++ end);
    tokens.push_back({ .token = *it, .freq = std::distance(it, end) });
    it = end - 1;
  }

  return tokens;
}


// This does what you think it does
void compile(const std::vector<TOKENS> &tokens, std::string_view outputFile) {
  AssemblyGenerator asmGen(outputFile);
  std::unordered_map<std::string, std::string> map;

  auto vec = fold(tokens);

  for (const auto &[token, frequency] : vec) {
    switch (token) {
      case LEFT:
        asmGen.ShiftLeft(frequency);
        break;

      case RIGHT:
        asmGen.ShiftRight(frequency);
        break;

      case INCREMENT:
        asmGen.Increment(frequency);
        break;

      case DECREMENT:
        asmGen.Decrement(frequency);
        break;

      case LOOP_START:
        asmGen.LoopStart();
        break;

      case LOOP_END:
        asmGen.LoopEnd();
        break;

      case INPUT:
        asmGen.Input();
        break;

      case OUTPUT:
        asmGen.Output();
        break;
    }
  }
}

#endif // !COMPILER_HPP
