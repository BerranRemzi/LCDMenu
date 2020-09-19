#define _CRT_SECURE_NO_WARNINGS

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "LCDMenu.h"

void UpdateScreen(const void* pFunction());

void menu_mmu2(void);
void SubMenu1(void);
void SubMenu1_1(void);
void SubMenu1_2(void);
void SubMenu2(void);
void SubMenu2_1(void);
void SubMenu2_2(void);
void SubMenu3(void);
void ActionItem1(void);
void ActionItem2(void);
void Exit(void);

void (*pPrintScreen[8])();

int menuDepth = 0;
int selection = -1;
bool menuChange = false;
bool run = true;

int main() {
    pPrintScreen[menuDepth] = &menu_mmu2;
    UpdateScreen(pPrintScreen[menuDepth]);
    do{ 
        UpdateScreen(pPrintScreen[menuDepth]);
        selection = -1;
        UpdateScreen(pPrintScreen[menuDepth]);
        printf("Select : ");

        int value = scanf("%d", &selection);
        printf("%d\n", value);
        Sleep(500);
    } while (run == true);
    return 0;
}

void UpdateScreen(const void* pFunction()) {
    system("cls");
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
    Sleep(1000);
}
void ActionItem2(void) {
    printf("ActionItem2");
    Sleep(1000);
}

void Exit(void) {
    run = false;
}