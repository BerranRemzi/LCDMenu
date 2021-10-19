#ifndef LCDMENU_CFG_H
#define LCDMENU_CFG_H

/* User defined macros */
#define LCD_HEIGHT 2
#define LCD_WIDTH 16

#ifdef ARDUINO
#define SETCURSOR(X, Y)     lcd.setCursor(X, Y)
#define PRINT(PLABEL)       lcd.print(PLABEL)
 
#define WRITE_ARROW()       lcd.write(arrowChar[0])
#define WRITE_RETURN()      lcd.write(returnChar[0])
#else
#define SETCURSOR(X, Y)     printf("\033[%d;%dH", Y+1, X+1)
#define PRINT(PLABEL)       printf(PLABEL)
#define WRITE_ARROW()       PRINT(">") 
#define WRITE_RETURN()      PRINT("<") 
#endif

#define TEXTIFY(TEXT)       #TEXT
#define VALUE_FORMAT(WIDTH) TEXTIFY(%10d)
#define PRINT_RIGHT(VALUE)  sprintf( charBuffer, VALUE_FORMAT(LCD_WIDTH), VALUE); PRINT(charBuffer)   
#define DRAW(LINE, PLABEL)  SETCURSOR(1,LINE); PRINT(PLABEL)



#endif