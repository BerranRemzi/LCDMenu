#pragma once
#include <stdio.h>
#include <stdint.h>

class LiquidCrystal {
public:
    LiquidCrystal(int,int,int,int,int,int) {}
    void begin(int x, int y) {

    }
    void createChar(int, const uint8_t[]) {

    }
};

class SoftwareSerial {
public:
    void begin(uint32_t _baud) {
    }
    void print(char const* const _input) {
        printf("%s", _input);
    }
    void println(char const* const _input) {
        print(_input);
        print("\n");
    }
    void print(int _input) {
        printf("%d", _input);
    }
    void println(int _input) {
        print(_input);
        print("\n");
    }
};

static SoftwareSerial Serial;


uint32_t millis(void) {
    return 0;
}

void delay(uint32_t) {

}

uint32_t analogRead(int input) {
    return 0;
}