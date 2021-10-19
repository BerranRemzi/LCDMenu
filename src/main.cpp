#include <Arduino.h>

#include <Wire.h>
#include <LiquidCrystal.h>
#include "AnalogButton.h"
#include "LCDMenu.h"
/*******************************************************

  This program will test the LCD panel and the buttons
  Berran Remzi, Septeber 2020

********************************************************/
void ReadInputs(void);
void DrawMenu(void);
void UpdateScreen(void);
void SubMenu_1(void);
void Menu_TestScreen(void);
void RunFunction(void);

enum Button_t {
  BUTTON_RIGHT,
  BUTTON_UP,
  BUTTON_DOWN,
  BUTTON_LEFT,
  BUTTON_SELECT,
  BUTTON_NONE
};
int8_t menuDepth = 0;
uint16_t buttonADC[] = { 0, 99, 255, 408, 639, 1023 };
AnalogButtonConfig_t buttons = {buttonADC, 5};
void (*pPrintScreen[8])(void);

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup()
{
  Serial.begin(115200);
  AnalogButton_Init(&buttons);

  lcd.begin(LCD_WIDTH, LCD_HEIGHT);              // start the library

  lcd.createChar(0, arrowChar); //We create the data to be sent later using lcd.write
  lcd.createChar(1, returnChar); //We create the data to be sent later using lcd.write
  
  pPrintScreen[menuDepth] = &Menu_TestScreen;
  UpdateScreen();
}

void loop()
{
  
  //DrawMenu2();
  if (AnalogButton_IsSinglePressed()){
    UpdateScreen();
  }
ReadInputs();
#if 0
  if (AnalogButton_IsSinglePressed() && Button_StateGet(BUTTON_SELECT) == BUTTON_STATE_PRESSED) {
    RunFunction(menuPos);
  }
#endif
  delay(20);
}

void UpdateScreen(void) {
    clear_screen();
    if (*pPrintScreen[menuDepth] != NULL) {
        pPrintScreen[menuDepth]();
    }
}
int value = 0;
void Menu_TestScreen(void) {
  START_MENU();
  SUBMENU("SubMenu_1", SubMenu_1);
  EDIT_ITEM_FAST("value", value);
  ACTION_ITEM("RunFunction", RunFunction);
  STATIC_ITEM("Bernar 1");
  STATIC_ITEM("Berran 2");
  STATIC_ITEM("Gulcan 3");
  STATIC_ITEM("Static text 4");
  STATIC_ITEM("Static text 5");
  STATIC_ITEM("Static text 6");
  STATIC_ITEM("Static text 7");
  STATIC_ITEM("Static text 8");
  END_MENU();
}
void SubMenu_1(void) {
    START_MENU();
    BACK_ITEM("<<BACK");
    STATIC_ITEM("Static text 1");
    END_MENU();
}

void RunFunction(void) {
  Serial.println(millis());
   Serial.println(VALUE_FORMAT(LCD_WIDTH));
}

void ReadInputs(void) {
  AnalogButton_LoadSample(analogRead(0));
  if (AnalogButton_IsSinglePressed()) {
    switch (AnalogButton_ReadCommand()) {
      case BUTTON_UP:
        LCDMenu_Up();
        break;
      case BUTTON_DOWN:
        LCDMenu_Down();
        break;
        case BUTTON_RIGHT:
        LCDMenu_Increment(1);
        break;
      case BUTTON_LEFT:
        LCDMenu_Decrement(1);
        break;
      case BUTTON_SELECT:
        LCDMenu_Select();
        break;
      default: break;
    }
  }
}
