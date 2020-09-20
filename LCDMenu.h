#ifndef MENU_H
#define MENU_H
#include <stdint.h>
#include <stdbool.h>

#include "LCDMenu_cfg.h"

#define IS_CURSOR_ACTIVE()          ((encoderTopLine + encoderLine) == _thisItemNr)

#define BACK_ITEM(LABEL)            if (_menuLineNr == _thisItemNr) { if(menuDepth>0){ DRAW(_lcdLineNr,LABEL);if(IS_CURSOR_ACTIVE() && selectPressed) menuDepth--; }} NEXT_ITEM();  
#define STATIC_ITEM(LABEL)          if (_menuLineNr == _thisItemNr) { DRAW(_lcdLineNr,LABEL); } NEXT_ITEM();  
#define SUBMENU(LABEL,FUNCTION)     if (_menuLineNr == _thisItemNr) { DRAW(_lcdLineNr,LABEL); if(IS_CURSOR_ACTIVE() && selectPressed){ pPrintScreen[++menuDepth] = FUNCTION; }} NEXT_ITEM();  
#define ACTION_ITEM(LABEL,FUNCTION) if (_menuLineNr == _thisItemNr) { DRAW(_lcdLineNr,LABEL); if(IS_CURSOR_ACTIVE() && selectPressed){ FUNCTION(); }} NEXT_ITEM();  

#define UNUSED(x) ((void)(x))
#define SET_CURSOR(LINE)   DRAW(LINE,">"); 

#define SCREEN_OR_MENU_LOOP(IS_MENU)                      \
        int8_t _menuLineNr = encoderTopLine, _thisItemNr; \
        bool _skipStatic = IS_MENU;                       \
        for (int8_t _lcdLineNr = 0; _lcdLineNr < LCD_HEIGHT; _lcdLineNr++, _menuLineNr++) { \
        _thisItemNr = 0

#define START_MENU()    SCREEN_OR_MENU_LOOP(true)
#define NEXT_ITEM()     (++_thisItemNr)
#define SKIP_ITEM()     NEXT_ITEM()
#define END_SCREEN()    } screen_items = _thisItemNr
#define END_MENU()      END_SCREEN(); UNUSED(_skipStatic); SETCURSOR(0,encoderLine); WRITE_ARROW(); selectPressed = false;

#ifdef ARDUINO
#define clear_screen()  lcd.clear()
#endif
// Menu Navigation
extern int8_t encoderTopLine, encoderLine, screen_items, _thisItemNr;
extern bool selectPressed;
extern int8_t menuDepth;

extern const uint8_t arrowChar[];
extern const uint8_t returnChar[];

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

void LCDMenu_Down(void);
void LCDMenu_Up(void);
void LCDMenu_Select(void);

#ifdef __cplusplus  // Provide C++ Compatibility
}
#endif

#endif
