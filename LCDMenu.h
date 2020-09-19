#ifndef MENU_H
#define MENU_H

#define START_MENU()  {uint8_t menuPos = 0;
#define BACK_ITEM(LABEL)   if(menuPos==selection && menuDepth>0){menuDepth--;} printf("%d. "LABEL"\n",menuPos++);
#define STATIC_ITEM(LABEL)   printf("%d. "LABEL"\n",menuPos++);
#define SUBMENU(LABEL,FUNCTION)    if(menuPos==selection){pPrintScreen[++menuDepth] = FUNCTION;} printf("%d. "LABEL"\n",menuPos++);
#define ACTION_ITEM(LABEL,FUNCTION)   if(menuPos==selection){FUNCTION();} printf("%d. "LABEL"\n",menuPos++); 
#define END_MENU()     }

#endif