#include "SelectPuzzleState.h"

#include "../utils/Constants.h"
#include "../utils/Arduboy2Ext.h"
#include "../images/Images.h"


// ----------------------------------------------------------------------------
//  Initialise state ..
//
void SelectPuzzleState::activate(StateMachine & machine) {

  (void)machine;
  uint8_t numberOfImages = ArrayLength(Puzzles::puzzles);
  this->puzzleIndex = EEPROM.read(Constants::PuzzleIndex);


  // If the current puzzle has been completed, then look for the first unfinished puzzle ..

  if (EEPROM.read(Constants::PuzzlesSolved + this->puzzleIndex) == 1) {

    for (uint8_t x = 0; x < numberOfImages; x++) {

      if (EEPROM.read(Constants::PuzzlesSolved + x) == 0) {

        this->puzzleIndex = x;
        break;

      }

    }

  }

}


// ----------------------------------------------------------------------------
//  Handle state updates .. 
//
void SelectPuzzleState::update(StateMachine & machine) { 

	auto & arduboy = machine.getContext().arduboy;
	auto justPressed = arduboy.justPressedButtons();

  uint8_t numberOfImages = ArrayLength(Puzzles::puzzles);


  // Navigation .. 

  if ((justPressed & LEFT_BUTTON) && this->puzzleIndex > 0) {

    this->puzzleIndex--;

  }

  if ((justPressed & RIGHT_BUTTON) && this->puzzleIndex < numberOfImages - 1) {

    this->puzzleIndex++;

  }



  // Populate puzzle ..

  if (justPressed & A_BUTTON) {

    this->populatePuzzle(this->puzzleIndex);
 		machine.changeState(GameStateType::PlayGame); 

  }

}

void SelectPuzzleState::populatePuzzle(uint8_t puzzleIndex) {

  uint16_t idx = 0;
  uint8_t maxSeriesRow = 0;
  uint8_t maxSeriesCol = 0;

  const uint8_t *puzzle = pgm_read_word_near(&Puzzles::puzzles[puzzleIndex]);

  uint8_t width = pgm_read_byte(&puzzle[idx++]);
  uint8_t height = pgm_read_byte(&puzzle[idx++]);
  uint8_t height8 = (height % 8 == 0 ? height / 8 : (height / 8) + 1);

  EEPROM.update(Constants::PuzzleIndex, puzzleIndex);
  EEPROM.update(Constants::PuzzleWidth, width);
  EEPROM.update(Constants::PuzzleHeight, height);

  for (uint16_t y = 0; y < height8; y++){

    for (uint16_t x = 0; x < width; x++){

      uint8_t data = pgm_read_byte(&puzzle[idx++]);

      for (uint8_t z = 0; z < 8; z++) {

        uint8_t val = (data & (1 << z)) > 0 ? static_cast<uint8_t>(GridValue::SelectedInImage) : 0;
        uint16_t memLoc = Constants::PuzzleStart + (y * 8 * width) + (z * width) + x;

        EEPROM.update(memLoc, val);

      }

    }

  }


  // Rows ..

  for (uint8_t y = 0; y < height; y++){

    uint8_t series[Constants::NumberOfNumbers];
    memset(series, 0, Constants::NumberOfNumbers);
    int8_t seriesIdx = -1;

    uint8_t lastData = 0;

    for (uint8_t x = 0; x < width; x++){

      uint8_t data = EEPROM.read(Constants::PuzzleStart + (y * width) + x);

      if (lastData != data) {

        if (data == static_cast<uint8_t>(GridValue::SelectedInImage)) {
          seriesIdx++;
          if (seriesIdx == Constants::NumberOfNumbers) break;
        }
        lastData = data;

      }

      if (data == static_cast<uint8_t>(GridValue::SelectedInImage)) {
        series[seriesIdx]++;
      }

    }


    for (uint8_t z = 0; z < Constants::NumberOfNumbers; z++) {

      if (series[z] > 0 && maxSeriesRow < z + 1) maxSeriesRow = z + 1;
      EEPROM.update(Constants::PuzzleRows + (y * Constants::NumberOfNumbers) + z, series[z]);

    }

  }


  // Column Headers ..
  
  for (uint8_t x = 0; x < width; x++){

    uint8_t series[Constants::NumberOfNumbers];
    memset(series, 0, Constants::NumberOfNumbers);
    int8_t seriesIdx = -1;

    uint8_t lastData = 0;

    for (uint8_t y = 0; y < height; y++){

      uint8_t data = EEPROM.read(Constants::PuzzleStart + (y * width) + x);

      if (lastData != data) {

        if (data == static_cast<uint8_t>(GridValue::SelectedInImage)) {
          seriesIdx++;
          if (seriesIdx == Constants::NumberOfNumbers) break;
        }
        lastData = data;

      }

      if (data == static_cast<uint8_t>(GridValue::SelectedInImage)) {
        series[seriesIdx]++;
      }

    }

    for (uint8_t z = 0; z < Constants::NumberOfNumbers; z++){

      if (series[z] > 0 && maxSeriesCol < z + 1) maxSeriesCol = z + 1;
      EEPROM.update(Constants::PuzzleCols + (x * Constants::NumberOfNumbers) + z, series[z]);

    }

  }

  EEPROM.update(Constants::PuzzleMaxRows, maxSeriesRow);
  EEPROM.update(Constants::PuzzleMaxCols, maxSeriesCol);
  
}


// ----------------------------------------------------------------------------
//  Render the state .. 
//
void SelectPuzzleState::render(StateMachine & machine) {

	auto & arduboy = machine.getContext().arduboy;
  
  uint8_t numberOfImages = ArrayLength(Puzzles::puzzles);

  bool flash = arduboy.getFrameCountHalf(48);  

  for (int8_t x = this->puzzleIndex - 4; x < this->puzzleIndex + 4; x++) {

    if (x >= 0 && x < numberOfImages) {

      const uint8_t *puzzle = pgm_read_word_near(&Puzzles::puzzles[x]);

      uint8_t width = pgm_read_byte(&puzzle[0]);
      uint8_t height = pgm_read_byte(&puzzle[1]);

      if ((flash && x == this->puzzleIndex) || (x != this->puzzleIndex)) {
        Sprites::drawOverwrite(Constants::Select_Centre - ((this->puzzleIndex - x) * Constants::Select_Spacing), Constants::Select_Top, Images::Box, 0);
      }

      if (EEPROM.read(Constants::PuzzlesSolved + x) == 1) {  
        Sprites::drawSelfMasked(Constants::Select_Centre - ((this->puzzleIndex - x) * Constants::Select_Spacing) + 10 - (width / 2), Constants::Select_Top + 10 - (height / 2), pgm_read_word(&Puzzles::puzzles[x]), 0);
      }
      else {
        Sprites::drawSelfMasked(Constants::Select_Centre - ((this->puzzleIndex - x) * Constants::Select_Spacing), Constants::Select_Top, Images::QuestionMark, 0);
      }

      font3x5.setCursor(Constants::Select_Centre - ((this->puzzleIndex - x) * Constants::Select_Spacing) + (width < 10 ? 5 : 0) - 2, Constants::Select_Label);
      font3x5.print(width);
      font3x5.print("~x~");
      font3x5.print(height);

    }

  }
Serial.println(" ");  

  arduboy.drawHorizontalDottedLine(0, 128, 8);
  arduboy.drawHorizontalDottedLine(0, 128, 48);

}
