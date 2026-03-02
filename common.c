#include "common.h"

void putchar(char c);

void printf(const char *fmt, ...){
    va_list vargs;
    va_start(vargs, fmt);

    while (*fmt){
        if (*fmt == '%'){
            fmt++;
            switch(*fmt){
                case '/0':
                    putchar('%');
                    goto end;
                case 'd':{
                    int value = va_arg(vargs, int);
                    if (value < 0){
                        putchar('-');
                        value = -value;
                    }

                    unsigned divisor = 1;
                    while (value / divisor > 9){
                        divisor *= 10;
                    }

                    while (divisor > 0){
                        putchar('0' + value / divisor);
                        value = value % divisor;
                        divisor /=10;
                    }

                    break;
                }
                case 's':{
                    char *str = va_arg(vargs, char *);
                    while (*str){
                        putchar(*str);
                        str++;
                    }
                    break;
                }
                case 'x': {
                    unsigned value = va_arg(vargs, unsigned);
                    for (int i = 7; i >= 0; i--){
                        unsigned digit = (value >> (i * 4)) & 0xF;
                        if (digit < 10){
                            putchar('0' + digit);
                        } else {
                            putchar('a' + digit - 10);
                        }
                    }
                }
            }
        }
        else {
            putchar(*fmt);
        }

        fmt++;
    }

    end:
    va_end(vargs);
}