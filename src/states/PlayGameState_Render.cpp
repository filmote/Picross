#include "PlayGameState.h"
#include "../images/Images.h"


// ---------------------------------------------------------------------------------------------------------------------------
//  Render the state .. 
// ---------------------------------------------------------------------------------------------------------------------------
// 
void PlayGameState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
  auto & gameStats = machine.getContext().gameStats;

  bool flash = arduboy.getFrameCountHalf(48);  

  for (uint8_t x = 0; x <= gameStats.gridSize; x++) {


    // Vertical lines ..

    if (x==0 || x==4 || x == 8 || x ==12) {

      arduboy.drawFastVLine(this->marginLeft + (x * Constants::GridWidthX), -gameStats.yOffset, this->marginTop - 2, WHITE );  

      for (uint8_t y = 3; y< this->marginTop + (gameStats.gridSize * Constants::GridWidthY) - gameStats.yOffset; y = y + 8) {
        arduboy.drawPixel(this->marginLeft + (x * Constants::GridWidthX), y, WHITE);
        arduboy.drawPixel(this->marginLeft + (x * Constants::GridWidthX), y + 2, WHITE);
      }

    }


    // Horizntal lines ..

    if (x==0 || x==4 || x == 8 || x ==12) {

      arduboy.drawFastHLine(0, this->marginTop + (x * Constants::GridWidthY) - gameStats.yOffset, this->marginLeft - 2, WHITE );  

      for (uint8_t y = 5; y < this->marginLeft + (gameStats.gridSize * Constants::GridWidthX); y = y + 8) {
        arduboy.drawPixel(y, this->marginTop + (x * Constants::GridWidthY) - gameStats.yOffset, WHITE);
        arduboy.drawPixel(y + 2, this->marginTop + (x * Constants::GridWidthY) - gameStats.yOffset, WHITE);
      }

    }

    arduboy.drawVerticalDottedLine(0, this->marginTop + (gameStats.gridSize * Constants::GridWidthY) - gameStats.yOffset, this->marginLeft + (x * Constants::GridWidthX));  
    arduboy.drawHorizontalDottedLine(0, this->marginLeft + (gameStats.gridSize * Constants::GridWidthX), this->marginTop + (x * Constants::GridWidthY) - gameStats.yOffset);  

  }


  for (uint8_t x = 0; x < gameStats.gridSize; x++) {

    for (uint8_t y = 0; y < gameStats.gridSize; y++) {

      GridValue gridValue = this->player.getGrid(x, y);

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

  for (uint8_t x = 0; x < gameStats.gridSize; x++) {

    if (this->player.isColMatch(x)) {

      arduboy.fillRect(this->marginLeft + (x * Constants::GridWidthX) + 1, -gameStats.yOffset, 7, this->marginTop - 1, WHITE);
      font3x5.setTextColor(BLACK);

    }
    else {

      font3x5.setTextColor(WHITE);

    }

    for (uint8_t y = 0; y < 5; y++) {

      uint8_t val = this->player.getCol(x, y);

      if (val != 0) {
      
        font3x5.setCursor(this->marginLeft + (x * Constants::GridWidthX) + 3 - (val >= 10 ? 3 : 0), -gameStats.yOffset + y * 7);

        font3x5.print(val);
        font3x5.print("\n");
      }
  
    }

  }


  // Render row headers ..

  for (uint8_t y = 0; y < gameStats.gridSize; y++) {

    if (this->player.isRowMatch(y)) {

      arduboy.fillRect(0, this->marginTop + (y * Constants::GridWidthY) + 1 - gameStats.yOffset, this->marginLeft - 1, 7, WHITE);
      font3x5.setTextColor(BLACK);

    }
    else {

      font3x5.setTextColor(WHITE);

    }
    
    uint8_t largerThan10 = 0;

    for (uint8_t x = 0; x < 5; x++) {
      
      uint8_t val = this->player.getRow(y, x);

      if (val != 0) {

        if (val >= 10) largerThan10++;

        font3x5.setCursor(1 + (x * 5) - (largerThan10 * 2), this->marginTop + (y * Constants::GridWidthY) + 1 - gameStats.yOffset);
        font3x5.print(val);
      }
  
    }

  }

  if (flash) {
    arduboy.drawRect(this->marginLeft + (this->player.getX() * Constants::GridWidthX), this->marginTop + (this->player.getY() * Constants::GridWidthY) - gameStats.yOffset, 9, 9);
  }

}

