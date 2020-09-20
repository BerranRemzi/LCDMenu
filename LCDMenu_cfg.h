#ifndef LCDMENU_CFG_H
#define LCDMENU_CFG_H

#ifdef ARDUINO
#define SETCURSOR(X, Y)     lcd.setCursor(X, Y)
#define PRINT(PLABEL)       lcd.print(PLABEL)
#define WRITE_ARROW()       lcd.write(arrowChar[0])
#else
#define SETCURSOR(X, Y)     printf("\033[%d;%dH", Y+1, X+1)
#define PRINT(PLABEL)       printf(PLABEL)
#define WRITE_ARROW()       PRINT(">") 
#endif

#define DRAW(LINE, PLABEL)  SETCURSOR(1,LINE); PRINT(PLABEL)

/* User defined macros */
#define LCD_HEIGHT 2
#define LCD_WIDTH 16

#endif