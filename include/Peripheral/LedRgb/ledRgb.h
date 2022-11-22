#ifndef LED_RGB_H_
#define LED_RGB_H_

#define LED_RGB_ON  1
#define LED_RGB_OFF 0

#define TIME_INTERVAL_BLK_LED_STATUS 250

#define BLK_LED_STATUS_ON 1
#define BLK_LED_STATUS_OFF 0

typedef enum{
	RGB_COLOR_OFF=0,
	RGB_COLOR_BLUE,
	RGB_COLOR_GREEN,
	RGB_COLOR_CYAN,
	RGB_COLOR_RED,
	RGB_COLOR_PURPLE,
	RGB_COLOR_YELLOW,
	RGB_COLOR_WHITE,	
}LED_RGB_BASIC_COLOR;

void ledRgb_initialize(void);
void ledRgb_checkLeds(void);
uint8_t ledRgb_basicCollors(uint8_t setColor, uint8_t blinkError);
void ledRgbStatus(uint8_t setColoer, uint16_t timeDelay);

/*
	WHEN: (RED, BLUE, GREEN)

	Preto - RGB (0,0,0).		(0, 0, 0)
	Azul - RGB (0,0,255);		(0, 0, 1)
	Verde - RGB (0,255,0);		(0, 1, 0)
	Ciano - RGB (0,255,255);	(0, 1, 1)
	Vermelho - RGB (255,0,0);	(1, 0, 0)
	Magenta - RGB (255,0,255);	(1, 0, 1)
	Amarelo - RGB (255,255,0);	(1, 1, 0)
	Branco - RGB (255,255,255);	(1, 1, 1)
*/

#endif /* LED_RGB_H_ */