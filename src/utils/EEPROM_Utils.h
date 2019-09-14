#pragma once

#include "Arduboy2Ext.h"
#include "Constants.h"



class EEPROM_Utils {

  public: 

    EEPROM_Utils() {};
        
    static void initEEPROM(bool forceClear);

};


/* ----------------------------------------------------------------------------
 *   Is the EEPROM initialised?
 *
 *   Looks for the characters 'P' and 'C' in the first two bytes of the EEPROM
 *   memory range starting from byte EEPROM_STORAGE_SPACE_START.  If not found,
 *   it resets the settings ..
 */
void EEPROM_Utils::initEEPROM(bool forceClear) {

  byte c1 = eeprom_read_byte(Constants::PuzzleStartChar1);
  byte c2 = eeprom_read_byte(Constants::PuzzleStartChar2);

  if (forceClear || c1 != 'P' || c2 != 'C') { 

    const uint16_t index = 0;
    eeprom_update_byte(Constants::PuzzleStartChar1, 'P');
    eeprom_update_byte(Constants::PuzzleStartChar2, 'C');
    eeprom_update_word(Constants::PuzzleIndex, index);

    for (uint8_t x = 0; x < 255; x++) {
      eeprom_update_byte(Constants::PuzzlesSolved + x, 0);
    }

  }

}

