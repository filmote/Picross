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

  return this->grid[this->x][this->y];

}

GridValue Player::getGrid(uint8_t x, uint8_t y) {

  return this->grid[x][y];

}

uint8_t Player::getCol(uint8_t col, uint8_t index) {

  return this->cols[col][index];

}

uint8_t Player::getRow(uint8_t row, uint8_t index) {

  return this->rows[row][index];

}

void Player::setX(uint8_t value) {
  
  this->x = value;
  
}

void Player::setY(uint8_t value) {
  
  this->y = value;
  
}

void Player::setGrid(GridValue value) {

  this->grid[this->x][this->y] = value;

}

void Player::setGrid(uint8_t x, uint8_t y, GridValue value) {

  this->grid[x][y] = value;

}

void Player::setCol(uint8_t col, uint8_t index, uint8_t value) {

  this->cols[col][index] = value;

}

void Player::setRow(uint8_t row, uint8_t index, uint8_t value) {

  this->rows[row][index] = value;

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

bool Player::isColMatch(uint8_t col, uint8_t match01, uint8_t match02, uint8_t match03, uint8_t match04, uint8_t match05) {

  return this->cols[col][0] == match01 && 
         this->cols[col][1] == match02 &&
         this->cols[col][2] == match03 &&
         this->cols[col][3] == match04 &&
         this->cols[col][4] == match05;

}

bool Player::isRowMatch(uint8_t row, uint8_t match01, uint8_t match02, uint8_t match03, uint8_t match04, uint8_t match05) {

  return this->rows[row][0] == match01 && 
         this->rows[row][1] == match02 &&
         this->rows[row][2] == match03 &&
         this->rows[row][3] == match04 &&
         this->rows[row][4] == match05;

}
         