#pragma once

namespace Puzzles {

  const unsigned char PROGMEM pica[] = {
  3, 3,
  0x00, 0x02, 0x00, 
  };

  const unsigned char PROGMEM Puzzle_00[] = {
  9, 9,
  0x38, 0x7c, 0xfe, 0xff, 0xff, 0xff, 0xfe, 0x7c, 0x38, 
  0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 
  };

  const unsigned char PROGMEM Puzzle_01[] = {
  12, 12,
  0x3c, 0xfe, 0xff, 0xc7, 0xff, 0xfe, 0xfe, 0xff, 0xc7, 0xff, 0xfe, 0x3c, 
  0x00, 0x00, 0x03, 0x07, 0x0d, 0x0e, 0x0e, 0x0d, 0x07, 0x03, 0x00, 0x00, 
  };

  const unsigned char PROGMEM Puzzle_02[] = {
  12, 12,
  0xfe, 0xfd, 0xfe, 0xfd, 0xfe, 0xfd, 0xfe, 0xfd, 0xfe, 0xfd, 0xfe, 0xfd, 
  0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 
  };

  const uint8_t * const puzzles[] PROGMEM = { pica, Puzzle_00, Puzzle_01, Puzzle_02, Puzzle_02 };

}