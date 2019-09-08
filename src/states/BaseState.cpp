#include "BaseState.h"

#include "../images/Images.h"
#include "../utils/Utils.h"
#include "../utils/Enums.h"
#include "../fonts/Font3x5.h"

void BaseState::drawMessageBox(StateMachine &machine, String message, uint8_t lines, uint8_t left, uint8_t width) {

	auto & arduboy = machine.getContext().arduboy;

	int8_t y = -1;
	uint8_t yBottom = y + (lines * 9) + 5;

	arduboy.fillRect(left, y + 4, width, yBottom - y, BLACK);	
	arduboy.fillRect(left + 4, y, width - 8, yBottom - y + 8, BLACK);	
	arduboy.fillRect(left + 1, y + 4, width - 2, yBottom - y + 1, WHITE);	
	arduboy.fillRect(left + 4, y + 1, width - 8, yBottom - y + 6, WHITE);	
	arduboy.drawRect(left + 2, y + 2, width - 4, yBottom - y + 4, BLACK);	

	Sprites::drawExternalMask(left, y, Images::Talk_Top_Left, Images::Talk_Top_Left_Mask, 0, 0);
	Sprites::drawExternalMask(left + width - 8, y, Images::Talk_Top_Right, Images::Talk_Top_Right_Mask, 0, 0);

  Sprites::drawExternalMask(left, yBottom, Images::Talk_Bottom_Left, Images::Talk_Bottom_Left_Mask, 0, 0);
  Sprites::drawExternalMask(left + width - 26, yBottom - 1, Images::Talk_Bubble_Right, Images::Talk_Bubble_Right_Mask, 0, 0);

  font3x5.setTextColor(BLACK);
  font3x5.setCursor(left + 6, y + 6);
  font3x5.print(message);

}

