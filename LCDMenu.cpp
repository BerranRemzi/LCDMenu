#include "LCDMenu.h"
#include "Arduino.h"
////////////////////////////////////////////
///////////// Global Variables /////////////
////////////////////////////////////////////

// Menu Navigation
int8_t encoderTopLine, encoderLine, screen_items;

menuPosition screen_history[6];
int8_t screen_history_depth = 0;

// Menu Navigation
int8_t _thisItemNr;

bool selectPressed = false;

int32_t valueChange = 0;

const uint8_t arrowChar[8] = {0x00, 0x04, 0x06, 0x1f, 0x06, 0x04, 0x00}; //Send 0,4,6,1F,6,4,0 for the arrow
const uint8_t returnChar[8] = {0x01, 0x01, 0x01, 0x05, 0x09, 0x1F, 0x08, 0x04};

char charBuffer[LCD_WIDTH + 2];

void LCDMenu_Down(void)
{
    if (encoderLine < LCD_HEIGHT - 1)
    {
        encoderLine++;
    }
    else if (encoderTopLine < screen_items - LCD_HEIGHT)
    {
        encoderTopLine++;
    }
    if (_thisItemNr < screen_items - 1)
    {
        _thisItemNr++;
    }
}

void LCDMenu_Up(void)
{
    if (encoderLine > 0)
    {
        encoderLine--;
    }
    else if (encoderTopLine > 0)
    {
        encoderTopLine--;
    }
    if (_thisItemNr > 0)
    {
        _thisItemNr--;
    }
}
void LCDMenu_Increment(uint8_t _step)
{
    valueChange = _step;
}

void LCDMenu_Decrement(uint8_t _step)
{
    valueChange = -_step;
}
void LCDMenu_Select(void)
{
    selectPressed = true;
}
int32_t LCDMenu_ValueChange(void)
{
    return valueChange;
}
void LCDMenu_ValueReset(void)
{
    valueChange = 0;
}

void LCDMenu_Task(void)
{
    if (screen_history[screen_history_depth].menu_function != NULL)
    {
        screen_history[screen_history_depth].menu_function();
    }
}