#include "PlayGameState.h"
#include "../images/Images.h"


// ---------------------------------------------------------------------------------------------------------------------------
//  Render the state .. 
// ---------------------------------------------------------------------------------------------------------------------------
// 
void PlayGameState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
  auto & gameStats = machine.getContext().gameStats;
  

  for (uint8_t x = 0; x <= gameStats.gridSize; x++) {

    arduboy.drawVerticalDottedLine(0, Constants::MarginTop + (gameStats.gridSize * Constants::GridWidthY) - gameStats.yOffset, Constants::MarginLeft + (x * Constants::GridWidthX));  
    arduboy.drawHorizontalDottedLine(0, Constants::MarginLeft + (gameStats.gridSize * Constants::GridWidthX), Constants::MarginTop + (x * Constants::GridWidthY) - gameStats.yOffset);  

  }


  for (uint8_t x = 0; x < gameStats.gridSize; x++) {

    for (uint8_t y = 0; y < gameStats.gridSize; y++) {

      GridValue gridValue = this->player.getGrid(x, y);

      switch (gridValue) {

        case GridValue::Blank:
          break;

        case GridValue::Selected:
          arduboy.fillRect(Constants::MarginLeft + (x * Constants::GridWidthX) + 2, Constants::MarginTop + (y * Constants::GridWidthY) + 2 - gameStats.yOffset, 5, 5, WHITE);
          break;

        case GridValue::Marked:
          Sprites::drawSelfMasked(Constants::MarginLeft + (x * Constants::GridWidthX) + 2, Constants::MarginTop + (y * Constants::GridWidthY) + 2 - gameStats.yOffset, Images::Marked, 0);
          break;
          
      }
    
    }

  }


  // Render column headers ..

  for (uint8_t x = 0; x < gameStats.gridSize; x++) {
    
    uint8_t col[5] = { 2, 2, 2, 2, 0 };

    font3x5.setCursor(Constants::MarginLeft + (x * Constants::GridWidthX) + 3, -gameStats.yOffset);

    if (this->player.isColMatch(x, col[0], col[1], col[2], col[3], col[4])) {

      arduboy.fillRect(Constants::MarginLeft + (x * Constants::GridWidthX) + 1, -gameStats.yOffset, 7, Constants::MarginTop, WHITE);
      font3x5.setTextColor(BLACK);

    }
    else {

      font3x5.setTextColor(WHITE);

    }

    for (uint8_t y = 0; y < 5; y++) {
      
      uint8_t val = this->player.getCol(x, y);

      if (val != 0) {
        font3x5.print(val);
        font3x5.print("\n");
      }
  
    }

  }


  // Render row headers ..

  for (uint8_t x = 0; x < gameStats.gridSize; x++) {
    
    uint8_t row[5] = { 2, 2, 2, 3, 0 };

    font3x5.setCursor(1, Constants::MarginTop + (x * Constants::GridWidthY) + 1 - gameStats.yOffset);

    if (this->player.isRowMatch(x, row[0], row[1], row[2], row[3], row[4])) {

      arduboy.fillRect(0, Constants::MarginTop + (x * Constants::GridWidthY) + 1 - gameStats.yOffset, Constants::MarginLeft, 7, WHITE);
      font3x5.setTextColor(BLACK);

    }
    else {

      font3x5.setTextColor(WHITE);

    }

    for (uint8_t y = 0; y < 5; y++) {
      
      uint8_t val = this->player.getRow(x, y);

      if (val != 0) {
        font3x5.print(val);
        font3x5.print("~");
      }
  
    }

  }

  // font3x5.setCursor(0, Constants::MarginTop + 1);
  // font3x5.print("2~3~4~5");

  arduboy.drawRect(Constants::MarginLeft + (this->player.getX() * Constants::GridWidthX), Constants::MarginTop + (this->player.getY() * Constants::GridWidthY) - gameStats.yOffset, 9, 9);

}

