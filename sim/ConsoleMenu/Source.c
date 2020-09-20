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
#define delay_ms(DELAY) sleep(DELAY)
#define clear_screen()  system("clear")
#endif

/* User includes */
#include "LCDMenu.h"

typedef enum Button_t {
    BUTTON_RIGHT,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_LEFT,
    BUTTON_SELECT,
    BUTTON_NONE
}Button_t;

Button_t Key_Read(void);

void UpdateScreen(void* pFunction());

void menu_static(void);
void menu_mmu2(void);
void SubMenu1(void);
void SubMenu1_1(void);
void SubMenu1_2(void);
void SubMenu2(void);
void SubMenu3(void);
void ActionItem1(void);
void ActionItem2(void);
void Exit(void);

void (*pPrintScreen[8])();

bool run = true;

int main() {
    pPrintScreen[menuDepth] = &menu_static;
    do{ 
        UpdateScreen(pPrintScreen[menuDepth]);
        UpdateScreen(pPrintScreen[menuDepth]);

        SETCURSOR(0, LCD_HEIGHT + 5);
        printf("encoderTopLine = %d\n", encoderTopLine);
        printf("encoderLine = %d\n", encoderLine);
        printf("screen_items = %d\n", screen_items);
        printf("_thisItemNr = %d\n", _thisItemNr);

        switch (Key_Read()) {
        case BUTTON_UP:
            LCDMenu_Up();
            break;
        case BUTTON_DOWN:
            LCDMenu_Down();
            break;
        case BUTTON_SELECT:
            LCDMenu_Select();
            break;
        default: break;
        }


    } while (run == true);
    return 0;
}

void UpdateScreen(void* pFunction()) {
    clear_screen();
    if (pFunction != NULL) {
        pFunction();
    }
}

void menu_mmu2(void) {
    START_MENU();
    ACTION_ITEM("Exit...", Exit);
    SUBMENU("SubMenu1", SubMenu1);
    SUBMENU("SubMenu2", SubMenu2);
    SUBMENU("SubMenu3", SubMenu3);
    ACTION_ITEM("ActionItem1", ActionItem1);
    ACTION_ITEM("ActionItem2", ActionItem2);
    END_MENU();
}
void menu_static(void) {
    START_MENU();
    ACTION_ITEM("Exit...", Exit);
    STATIC_ITEM("Static1");
    SUBMENU("SubMenu1", SubMenu1);
    STATIC_ITEM("Static2");
    STATIC_ITEM("Static3");
    STATIC_ITEM("Static4");
    STATIC_ITEM("Static5");
    END_MENU();
}

void SubMenu1(void) {
    START_MENU();
    BACK_ITEM("<<BACK");
    SUBMENU("SubMenu1-1", SubMenu1_1);
    SUBMENU("SubMenu1-2", SubMenu1_2);
    END_MENU();
}
void SubMenu1_1(void) {
    START_MENU();
    BACK_ITEM("<<BACK");
    SUBMENU("SubMenu1-1-1", SubMenu1_1);
    SUBMENU("SubMenu1-1-2", SubMenu1_1);
    END_MENU();
}
void SubMenu1_2(void) {
    START_MENU();
    BACK_ITEM("<<BACK");
    SUBMENU("SubMenu1-2-1", SubMenu1_2);
    SUBMENU("SubMenu1-2-2", SubMenu1_2);
    END_MENU();
}

void SubMenu2(void) {
    START_MENU();
    BACK_ITEM("<<BACK");
    STATIC_ITEM("SubMenu2-1");
    STATIC_ITEM("SubMenu2-2");
    END_MENU();
}
void SubMenu3(void) {
    START_MENU();
    BACK_ITEM("<<BACK");
    STATIC_ITEM("SubMenu3-1");
    STATIC_ITEM("SubMenu3-2");
    END_MENU();
}
void ActionItem1(void) {
    printf("ActionItem1");
    delay_ms(1000);
}
void ActionItem2(void) {
    printf("ActionItem2");
    delay_ms(1000);
}

void Exit(void) {
    run = false;
}

Button_t Key_Read(void) {
    Button_t returnValue = BUTTON_NONE;
    int temp = getch();
    if (temp == 224) { // if the first value is esc
#ifndef _WIN32
        getch(); // skip the [
#endif
        switch (getch()) { // the real value
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
    }else if (temp == 13) {
        // code for select
        returnValue = BUTTON_SELECT;
    }
    return returnValue;
}