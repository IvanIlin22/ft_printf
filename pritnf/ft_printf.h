//
// Created by ivan on 15.09.2020.
//

#ifndef PRITNF_FT_PRINTF_H
#define PRITNF_FT_PRINTF_H

#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <limits.h>

#define H   1
#define HH  2
#define L   3
#define LL  4
#define J   5
#define Z   6

typedef struct  s_printf
{
    int         i;
    int         fd;
    int         len;

    int         minus;
    int         plus;
    int         zero;
    int         space;
    int         hash;

    int         width;
    int         precision;
    int         fl_precision;
    int         length;
}               t_printf;

void    ft_parse_modificator(t_printf *p, va_list args, const char *format);
char    *ft_strchr(const char *str, char c);
int     ft_itoa_base_pr(int fd, intmax_t num, int base);
int     ft_len(intmax_t num, int base);


void    ft_print_decimal(t_printf *p, va_list argc, char c);
void    ft_print_octal(t_printf *p, va_list argc, char c);

#endif //PRITNF_FT_PRINTF_H
