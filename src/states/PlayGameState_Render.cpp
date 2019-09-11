#include "PlayGameState.h"
#include "../images/Images.h"


// ---------------------------------------------------------------------------------------------------------------------------
//  Render the state .. 
// ---------------------------------------------------------------------------------------------------------------------------
// 
void PlayGameState::render(StateMachine & machine) {

  uint8_t const solidLines[] =
   {
     0, 0, 0, 0, 0,    // 0
     0, 0, 0, 0, 0,    // 1
     0, 2, 0, 0, 0,    // 2
     0, 3, 0, 0, 0,    // 3
     0, 4, 0, 0, 0,    // 4
     0, 5, 0, 0, 0,    // 5
     0, 3, 6, 0, 0,    // 6
     0, 7, 0, 0, 0,    // 7
     0, 4, 8, 0, 0,    // 8
     0, 3, 6, 9, 0,    // 9
     0, 5, 10, 0, 0,   // 10
     0, 11, 0, 0, 0,   // 11
     0, 4, 8, 12, 0,   // 12
     0, 13, 0, 0, 0,   // 13
     0, 7, 14, 0, 0,   // 14
     0, 5, 10, 15, 0,  // 15
     0, 4, 8, 12, 16,  // 16
   };

	auto & arduboy = machine.getContext().arduboy;
  auto & gameStats = machine.getContext().gameStats;

  bool flash = arduboy.getFrameCountHalf(48);  
  uint8_t size = this->puzzle.getSize();
  uint8_t completedRows = 0;

  for (uint8_t x = 0; x <= size; x++) {


    // Horizontal and Vertical lines ..

    for (uint8_t z = size * 5; z < (size * 5) + 5; z++) {

      if (x == solidLines[z]) {
        arduboy.drawFastVLine(this->marginLeft + (x * Constants::GridWidthX), this->marginTop - gameStats.yOffset, size * Constants::GridWidthY, WHITE); 
        arduboy.drawFastHLine(this->marginLeft, this->marginTop + (x * Constants::GridWidthY) - gameStats.yOffset, size * Constants::GridWidthX, WHITE);  
      }

    }

    arduboy.drawVerticalDottedLine(0, this->marginTop + (size * Constants::GridWidthY) - gameStats.yOffset, this->marginLeft + (x * Constants::GridWidthX));  
    arduboy.drawHorizontalDottedLine(0, this->marginLeft + (size * Constants::GridWidthX), this->marginTop + (x * Constants::GridWidthY) - gameStats.yOffset);  

  }

  for (uint8_t x = 0; x < size; x++) {

    for (uint8_t y = 0; y < size; y++) {

      GridValue gridValue = this->puzzle.getGrid(x, y);

      switch (gridValue) {

        case GridValue::Blank:
          break;

        case GridValue::Selected:
          arduboy.fillRect(this->marginLeft + (x * Constants::GridWidthX) + 2, this->marginTop + (y * Constants::GridWidthY) + 2 - gameStats.yOffset, 5, 5, WHITE);
          break;

        case GridValue::Marked:
          Sprites::drawSelfMasked(this->marginLeft + (x * Constants::GridWidthX) + 2, this->marginTop + (y * Constants::GridWidthY) + 2 - gameStats.yOffset, Images::Marked, 0);
          break;
          
      }
    
    }

  }


  // Render column headers ..

  for (uint8_t x = 0; x < size; x++) {

    if (this->puzzle.isColMatch(x)) {

      arduboy.fillRect(this->marginLeft + (x * Constants::GridWidthX) + 1, -gameStats.yOffset, 7, this->marginTop - 1, WHITE);
      font3x5.setTextColor(BLACK);

      completedRows++;

    }
    else {

      font3x5.setTextColor(WHITE);

    }

    for (uint8_t y = 0; y < 5; y++) {

      uint8_t val = this->puzzle.getCol(x, y);

      if (val != 0) {
      
        font3x5.setCursor(this->marginLeft + (x * Constants::GridWidthX) + 3 - (val >= 10 ? 3 : (val == 1 ? 1 : 0)), -gameStats.yOffset + y * 7);

        font3x5.print(val);
        font3x5.print("\n");
      }
  
    }

  }


  // Render row headers ..

  for (uint8_t y = 0; y < size; y++) {

    if (this->puzzle.isRowMatch(y)) {

      arduboy.fillRect(0, this->marginTop + (y * Constants::GridWidthY) + 1 - gameStats.yOffset, this->marginLeft - 1, 7, WHITE);
      font3x5.setTextColor(BLACK);

      completedRows++;

    }
    else {

      font3x5.setTextColor(WHITE);

    }
    
    uint8_t largerThan10 = 0;

    for (uint8_t x = 0; x < 5; x++) {
      
      uint8_t val = this->puzzle.getRow(y, x);

      if (val != 0) {

        if (val >= 10) largerThan10++;

        font3x5.setCursor(1 + (x * 5) - (largerThan10 * 2), this->marginTop + (y * Constants::GridWidthY) + 1 - gameStats.yOffset);
        font3x5.print(val);
      }
  
    }

  }


  // Game over?

  if (completedRows == 2 * size) {

    this->gameOver = true;
    EEPROM.update(Constants::PuzzlesSolved + this->puzzle.getPuzzleIndex(), 1);

  }


  if (this->gameOver) {

    if (this->counter == 64) {

      Sprites::drawOverwrite(24, 24, Images::Congratulations, 0);

    }

  }
  else {

    if (flash) {
      arduboy.drawRect(this->marginLeft + (this->puzzle.getX() * Constants::GridWidthX), this->marginTop + (this->puzzle.getY() * Constants::GridWidthY) - gameStats.yOffset, 9, 9);
    }

  }

}

