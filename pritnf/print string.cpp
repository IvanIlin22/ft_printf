//
// Created by ivan on 18.09.2020.
//

#include "ft_printf.h"

int    ft_wstrlen(wchar_t *wstr)
{
    int len;
    int i;

    if (!wstr)
        return 0;
    len = 0;
    i = 0;
    while (wstr[i])
    {
        if (wstr[i] <= 127)
            len++;
        else if (wstr[i]  >= 128 && wstr[i]  <= 2047)
        {
            len += 2;
        }
        else if (wstr[i]  >= 2048 && wstr[i]  <= 65535)
        {
            len += 3;
        }
        else if (wstr[i]  >= 65536 && wstr[i]  <= 1114111)
        {
            len += 4;
        }
        i++;
    }
    return (len);
}

void    ft_print_wleft(t_printf *p, wchar_t *wstr)
{
    int i;
    int len;

    len = ft_wstrlen(wstr);
    if (p->fl_precision && len > p->precision)
        len = p->precision;
    else if (!wstr)
    {
        if (p->precision >= 6 || !p->fl_precision)
        {
            p->len += write(p->fd, "(null)", 6);
            len = 6;
        }
        while (p->width-- > len)
            p->len += write(p->fd, " ", 1);
        return;
    }
    i = 0;
    while (i < len)
    {
        ft_putchar_wc(p, wstr[i]);
        i++;
    }
    while (p->width > len)
    {
        p->len += write(p->fd, " ", 1);
        p->width--;
    }
}

void    ft_print_wright(t_printf *p, wchar_t *wstr)
{
    int i;
    int len;

    len = ft_wstrlen(wstr);
    if (p->fl_precision && len > p->precision)
        len = p->precision;
    else if (!wstr && (p->precision >= 6 || !p->fl_precision))
        len = 6;
    while (p->width > len)
    {
        p->len += write(p->fd, " ", 1);
        p->width--;
    }
    if (!wstr && (p->precision >= 6 || !p->fl_precision))
    {
        p->len += write(p->fd, "(null)", 6);
        return;
    }
    i = 0;
    while (i < len)
    {
        ft_putchar_wc(p, wstr[i]);
        i++;
    }
}

void    ft_print_left(t_printf *p, char *str)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(str);
    if (p->fl_precision && len > p->precision)
        len = p->precision;
    else if (!str)
    {
        if (p->precision >= 6 || !p->fl_precision)
        {
            p->len += write(p->fd, "(null)", 6);
            len = 6;
        }
        while (p->width-- > len)
            p->len += write(p->fd, " ", 1);
        return;
    }
    while (i < len)
    {
        p->len += write(p->fd, &str[i], 1);
        i++;
    }
    while (p->width > len)
    {
        p->len += write(p->fd, " ", 1);
        p->width--;
    }
}

void    ft_print_right(t_printf *p, char *str)
{
    int i;
    int len;

    len = ft_strlen(str);
    if (p->fl_precision && len > p->precision)
        len = p->precision;
    else if (!str && (p->precision >= 6 || !p->fl_precision))
        len = 6;
    while (p->width > len)
    {
        p->len += write(p->fd, " ", 1);
        p->width--;
    }
    if (!str && (p->precision >= 6 || !p->fl_precision))
    {
        p->len += write(p->fd, "(null)", 6);
        return;
    }
    i = 0;
    while (i < len)
    {
        p->len += write(p->fd, &str[i], 1);
        i++;
    }
    p->len += write(p->fd, "\0", 1);
}

void ft_print_string(t_printf *p, va_list argc, char c)
{
    char    *str;
    wchar_t *wstr;

    if ((c == 's' && p->length == L) || c == 'S')
    {
        wstr = va_arg(argc, wchar_t*);
        if (p->minus)
            ft_print_wleft(p, wstr);
        else
            ft_print_wright(p, wstr);
    }
    else if (c == 's')
    {
        str = va_arg(argc, char*);
        if (p->minus)
            ft_print_left(p, str);
        else
            ft_print_right(p, str);
    }
}
