#include "src/Game.h"

#include "src/utils/Arduboy2Ext.h"

Game game;

void setup() {
	game.setup();


}

void loop() {



	Serial.println("------------------------");

	uint8_t idx = 0;
	uint8_t width = pgm_read_byte(&Images::Pic1[idx++]);
	uint8_t height = pgm_read_byte(&Images::Pic1[idx++]);
	uint8_t height8 = (height % 8 == 0 ? height / 8 : (height / 8) + 1);

	for (uint8_t y = 0; y < height8; y++){

		for (uint8_t x = 0; x < width; x++){

			uint8_t data = pgm_read_byte(&Images::Pic1[idx++]);

			for (uint8_t z = 0; z < 8; z++) {
				Serial.print((data & (1 << z)) > 0 ? "1" : "0");
			}

			Serial.println("");

		}

	}

	game.loop();
}
