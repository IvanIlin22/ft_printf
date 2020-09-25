//
// Created by ivan on 18.09.2020.
//
#include "ft_printf.h"

void            ft_putchar(t_printf *p, char c)
{
    p->len += write(p->fd, &c, 1);
}

void            ft_putchar_wc(t_printf *p, wchar_t length_num)
{
    if (length_num <= 127)
        p->len += write(p->fd, &length_num, 1);
    else if (length_num >= 128 && length_num <= 2047)
    {
        ft_putchar(p, 192 | (length_num >> 6));
        ft_putchar(p, 128 | (length_num & 63));
    }
    else if (length_num >= 2048 && length_num <= 65535)
    {
        ft_putchar(p, 224 | (length_num >> 12));
        ft_putchar(p, 128 | ((length_num >> 6) & 63));
        ft_putchar(p, 128 | length_num & 63);

    }
    else if (length_num >= 65536 && length_num <= 1114111)
    {
        ft_putchar(p,240 | (length_num >> 18) );
        ft_putchar(p, 128 | ((length_num >> 12) & 63));
        ft_putchar(p, 128 | ((length_num >> 6) & 63));
        ft_putchar(p, 128 | (length_num & 63));
    }
    /*else
        p->len = -1;*/
}

static void    ft_print_right_length(t_printf *p, wchar_t length_num)
{
    if (length_num >= 128 && length_num <= 2047)
        p->width--;
    else if (length_num >= 2048 && length_num <= 65535)
        p->width -= 2;
    else if (length_num >= 65536 && length_num <= 1114111)
        p->width -= 3;
    while (p->width > 1)
    {
        p->len += write(p->fd, " ", 1);
        p->width--;
    }
    ft_putchar_wc(p, length_num);
}

static void    ft_print_left_length(t_printf *p, wchar_t length_num)
{
    ft_putchar_wc(p, length_num);
    if (length_num >= 128 && length_num <= 2047)
        p->width--;
    else if (length_num >= 2048 && length_num <= 65535)
        p->width -= 2;
    else if (length_num >= 65536 && length_num <= 1114111)
        p->width -= 3;
    while (p->width > 1)
    {
        p->len += write(p->fd, " ", 1);
        p->width--;
    }
}

static void    ft_print_left(t_printf *p, unsigned char num)
{
    p->len += write(p->fd, &num, 1);
    while (p->width > 1)
    {
        p->len += write(p->fd, " ", 1);
        p->width--;
    }
}

static void    ft_print_right(t_printf *p, unsigned char num)
{
    while (p->width > 1)
    {
        p->len += write(p->fd, " ", 1);
        p->width--;
    }
    p->len += write(p->fd, &num, 1);
}

void ft_print_char(t_printf *p, va_list argc, char c)
{
    unsigned char   num;
    wchar_t         length_num;

    if ((c == 'c' && p->length == L) || c == 'C')
    {
        length_num = (wchar_t)va_arg(argc, wint_t);
        if (p->minus)
            ft_print_left_length(p, length_num);
        else
            ft_print_right_length(p, length_num);
    }
    else if (c == 'c')
    {
        num = (unsigned char)va_arg(argc, int);
        if (p->minus)
            ft_print_left(p, num);
        else
            ft_print_right(p, num);
    }
}
