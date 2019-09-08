#pragma once

#include "../utils/Arduboy2Ext.h"
#include "../utils/Constants.h"
#include "../utils/Enums.h"

class Player { 

  public:

    Player();

    uint8_t getX();
    uint8_t getY();
    GridValue getGrid();
    GridValue getGrid(uint8_t x, uint8_t y);
    uint8_t getCol(uint8_t col, uint8_t index);
    uint8_t getRow(uint8_t col, uint8_t index);

    void setX(uint8_t value);
    void setY(uint8_t value);
    void setGrid(GridValue value);
    void setGrid(uint8_t x, uint8_t y, GridValue value);
    void setCol(uint8_t col, uint8_t index, uint8_t value);
    void setRow(uint8_t col, uint8_t index, uint8_t value);

    void incX();
    void decX();
    void incY();
    void decY();

    bool isColMatch(uint8_t col, uint8_t match01, uint8_t match02, uint8_t match03, uint8_t match04, uint8_t match05);
    bool isRowMatch(uint8_t row, uint8_t match01, uint8_t match02, uint8_t match03, uint8_t match04, uint8_t match05);

  private:


  private:

    uint8_t x = 0;
    uint8_t y = 0;
    GridValue grid[12][12];
    uint8_t cols[12][5];
    uint8_t rows[12][5];

};
