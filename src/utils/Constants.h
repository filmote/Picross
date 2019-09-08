#pragma once

#define _DEBUG

#define DEBUG_PRINT
#ifdef DEBUG_PRINT
  #define DEBUG_PRINT_CARDS
  #define DEBUG_PRINT_HANDS
  #define _DEBUG_PRINT_DISCARDS
  #define _DEBUG_PRINT_COMPUTER_DISCARDS
#endif

namespace Constants {

  constexpr uint8_t MarginTop = 28;
  constexpr uint8_t MarginLeft = 22;
  constexpr uint8_t GridWidthX = 8;
  constexpr uint8_t GridWidthY = 8;

  
}