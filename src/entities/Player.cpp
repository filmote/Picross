#include "Player.h"

#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"
#include "../images/Images.h"

Player::Player() { }


uint8_t Player::getX() {

  return this->x;

}

uint8_t Player::getY() {

  return this->y;

}

GridValue Player::getGrid() {

  uint8_t width = EEPROM.read(Constants::PuzzleWidth);
  uint8_t val = EEPROM.read(Constants::PuzzleStart + (this->y * width) + (this->x)) & 0x0f;

  return static_cast<GridValue>(val);

}

GridValue Player::getGrid(uint8_t x, uint8_t y) {

  uint8_t width = EEPROM.read(Constants::PuzzleWidth);
  uint8_t val = EEPROM.read(Constants::PuzzleStart + (y * width) + x) & 0x0f;

  return static_cast<GridValue>(val);

}

uint8_t Player::getCol(uint8_t col, uint8_t index) {

  return EEPROM.read(Constants::PuzzleCols + (col * Constants::NumberOfNumbers) + index);

}

uint8_t Player::getRow(uint8_t row, uint8_t index) {

  return EEPROM.read(Constants::PuzzleRows + (row * Constants::NumberOfNumbers) + index);

}

void Player::setX(uint8_t value) {

  this->x = value;
  
}

void Player::setY(uint8_t value) {
  
  this->y = value;
  
}

void Player::setGrid(GridValue value) {

  uint8_t width = EEPROM.read(Constants::PuzzleWidth);
  uint16_t memLoc = Constants::PuzzleStart + (this->y * width) + x;
  uint8_t update = (EEPROM.read(memLoc) & static_cast<uint8_t>(GridValue::SelectedInImage)) | static_cast<uint8_t>(value);

  EEPROM.update(memLoc, static_cast<uint8_t>(update));

  this->updateRowCols();

}

void Player::setGrid(uint8_t x, uint8_t y, GridValue value) {

  uint8_t width = EEPROM.read(Constants::PuzzleWidth);

  EEPROM.update(Constants::PuzzleStart + (y * width) + x, static_cast<uint8_t>(value));

  this->updateRowCols();

}

void Player::setCol(uint8_t col, uint8_t index, uint8_t value) {
  
  EEPROM.update(Constants::PuzzleCols + (col * Constants::NumberOfNumbers) + index, value);

}

void Player::setRow(uint8_t row, uint8_t index, uint8_t value) {
  
  EEPROM.update(Constants::PuzzleRows + (row * Constants::NumberOfNumbers) + index, value);

}

void Player::incX() {
  
  this->x++;
  
}

void Player::decX() {
  
  this->x--;
  
}

void Player::incY() {
  
  this->y++;
  
}

void Player::decY() {
  
  this->y--;
  
}

bool Player::isColMatch(uint8_t col) {

  for (uint8_t z = 0; z < Constants::NumberOfNumbers; z++) {

    if (EEPROM.read(Constants::PuzzleCols + (col * Constants::NumberOfNumbers) + z) != this->cols[(col * Constants::NumberOfNumbers) + z]) {
      return false;
    }

  }

  return true;

}

bool Player::isRowMatch(uint8_t row) {

  for (uint8_t z = 0; z < Constants::NumberOfNumbers; z++) {

    if (EEPROM.read(Constants::PuzzleRows + (row * Constants::NumberOfNumbers) + z) != this->rows[(row * Constants::NumberOfNumbers) + z]) {
      return false;
    }

  }

  return true;

}
         

 
void Player::updateRowCols() {

  uint8_t width = EEPROM.read(Constants::PuzzleWidth);
  uint8_t height = EEPROM.read(Constants::PuzzleHeight);

  // Rows ..

  for (uint8_t y = 0; y < height; y++){

    uint8_t series[Constants::NumberOfNumbers];
    memset(series, 0, Constants::NumberOfNumbers);
    int8_t seriesIdx = -1;

    uint8_t lastData = 0;

    for (uint8_t x = 0; x < width; x++){

      uint8_t data = EEPROM.read(Constants::PuzzleStart + (y * width) + x) & 0x0F;

      if (lastData != data) {

        if (data == static_cast<uint8_t>(GridValue::Selected)) {
          seriesIdx++;
          if (seriesIdx == Constants::NumberOfNumbers) break;
        }
        lastData = data;

      }

      if (data == static_cast<uint8_t>(GridValue::Selected)) {
        series[seriesIdx]++;
      }

    }

    for (uint8_t z = 0; z < Constants::NumberOfNumbers; z++){

      this->rows[(y * Constants::NumberOfNumbers) + z] = series[z];

    }

  }


  // Column Headers ..
  
  for (uint8_t x = 0; x < width; x++){

    uint8_t series[Constants::NumberOfNumbers];
    memset(series, 0, Constants::NumberOfNumbers);
    int8_t seriesIdx = -1;

    uint8_t lastData = 0;

    for (uint8_t y = 0; y < height; y++){

      uint8_t data = EEPROM.read(Constants::PuzzleStart + (y * width) + x) & 0x0F;

      if (lastData != data) {

        if (data == static_cast<uint8_t>(GridValue::Selected)) {
          seriesIdx++;
          if (seriesIdx == Constants::NumberOfNumbers) break;
        }
        lastData = data;

      }
      if (data == static_cast<uint8_t>(GridValue::Selected)) {
        series[seriesIdx]++;
      }

    }

    for (uint8_t z = 0; z < Constants::NumberOfNumbers; z++){

      this->cols[(x * Constants::NumberOfNumbers) + z] = series[z];

    }

  }        

}