#include "AnalogButton.h"
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <conio.h> 
#include <stdint.h>
#include <stdbool.h>

#ifdef _WIN32
//#include <Windows.h>
#define delay_ms(DELAY) Sleep(DELAY)
#define clear_screen()  system("cls")
#else
#include <unistd.h>
#define delay_ms(DELAY) sleep(DELAY)
#define clear_screen()  system("clear")
#endif

enum Button_t {
    BUTTON_RIGHT,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_SELECT,
    BUTTON_NONE
};

void AnalogButton_Init(AnalogButtonConfig_t* _config)
{
}

uint8_t AnalogButton_IsSinglePressed(void)
{
    return 1;
}

void AnalogButton_LoadSample(uint16_t _new_sample)
{
}

uint8_t AnalogButton_ReadCommand(void)
{
    static int key[2];
    Button_t returnValue = BUTTON_NONE;
    key[0] = key[1];
    key[1] = _getch();
    if (key[0] == 224) { // if the first value is esc
#ifndef _WIN32
        _getch(); // skip the [
#endif
        switch (key[1]) { // the real value
        case 72:
            // code for arrow up
            returnValue = BUTTON_UP;
            break;
        case 80:
            // code for arrow down
            returnValue = BUTTON_DOWN;
            break;
        case 77:
            // code for arrow right
            returnValue = BUTTON_RIGHT;
            break;
        case 75:
            // code for arrow left
            returnValue = BUTTON_LEFT;
            break;
        default: break;
        }
    }
    else if (key[1] == 13) {
        // code for select
        returnValue = BUTTON_SELECT;
    }
    return returnValue;
}
