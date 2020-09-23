#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef _WIN32
#include <Windows.h>
#define delay_ms(DELAY) Sleep(DELAY)
#define clear_screen()  system("cls")
#else
#include <unistd.h>
#define delay_ms(DELAY) sleep(DELAY/1000.0)
#define clear_screen()  system("clear")
#endif

/* User includes */
#include "LCDMenu.h"
#include "example/DFR_LCD_Keypad_Menu/DFR_LCD_Keypad_Menu.ino"


void Debug(void);

int main(void) {
    setup();
    while (true) {
        loop();
    }
    return 0;
}

void Debug(void) {
    SETCURSOR(0, LCD_HEIGHT + 5);
    printf("encoderTopLine = %d\n", encoderTopLine);
    printf("encoderLine = %d\n", encoderLine);
    printf("screen_items = %d\n", screen_items);
    printf("_thisItemNr = %d\n", _thisItemNr);
}
