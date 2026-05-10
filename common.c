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

void *memcpy(void *dst, const void *src, size_t n){
    uint8_t *d = (uint8_t *)dst;
    const uint8_t *s = (const uint8_t *)src;

    while (n--){
        *d++ = *s++;
    }

    return dst;
}

void *memset(void *buf, char c, size_t n){
    uint8_t *ptr = (uint8_t *)buf;
    while (n--){
        *ptr++ = c;
    }

    return buf;
}

char *strcpy(char *dst, const char *src){
    char *d = dst;
    while (*src){
        *d++ = *src++;
    }
    *d = '\0';
    return dst;
} // implement strcpy_s later

int strcmp(const char *s1, const char *s2){
    while (*s1 && *s2){
        if (*s1 != *s2){
            return *s1 - *s2;
        }
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

