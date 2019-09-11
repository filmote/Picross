#pragma once

namespace Constants {

  constexpr uint8_t GridWidthX = 8;
  constexpr uint8_t GridWidthY = 8;
  constexpr uint8_t NumberOfNumbers = 8;

  constexpr uint16_t PuzzleIndex = 450;
  constexpr uint16_t PuzzleWidth = PuzzleIndex + 1;
  constexpr uint16_t PuzzleHeight = PuzzleWidth + 1;
  constexpr uint16_t PuzzleMaxRows = PuzzleHeight + 1;
  constexpr uint16_t PuzzleMaxCols = PuzzleMaxRows + 1;
  constexpr uint16_t PuzzleStart = PuzzleMaxCols + 1;
  constexpr uint16_t PuzzleCols = PuzzleStart + 225;
  constexpr uint16_t PuzzleRows = PuzzleCols + (15 * NumberOfNumbers);

  constexpr uint16_t PuzzlesSolved = PuzzleRows + (15 * NumberOfNumbers);

}