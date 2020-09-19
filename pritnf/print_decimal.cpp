//
// Created by ivan on 16.09.2020.
//
#include "ft_printf.h"

int    ft_len(intmax_t num, int base)
{
    int i;

    i = 0;
    if (num == 0)
        return (1);
    if (num < -9223372036854775807)
        return (20);
    if (num < 0)
    {
        i++;
        num *= -1;
    }
    while (num > 0)
    {
        num /= base;
        i++;
    }
    return (i);
}

int     ft_print_decimal_right2(t_printf *p, intmax_t num, int znak)
{
    if (num == 0 && p->fl_precision && !p->precision)
    {
        if (p->plus && p->width)
            p->width--;
        while (p->width)
        {
            p->len += write(p->fd, " ", 1);
            p->width--;
        }
        if (p->plus)
            p->len +=  write(p->fd, "+", 1);
        return (1);
    }
    if (p->space && znak == 1 && !p->width)
        p->len += write(p->fd, " ", 1);
    if (p->plus && p->zero && znak == 1)
        p->len += write(p->fd, "+", 1);
    if (p->zero && znak == -1)
        p->len += write(p->fd, "-", 1);
    return (0);
}

void    ft_print_decimal3(t_printf *p, intmax_t num, int numlen)
{
    if (!p->fl_precision)
    {
        while (p->width > numlen)
        {
            if (p->zero)
                p->len += write(p->fd, "0", 1);
            else
                p->len += write(p->fd, " ", 1);
            p->width--;
        }
    }
    else
    {
        if (p->plus)
            p->width--;
        while (p->width > p->precision)
        {
            p->len += write(p->fd, " ", 1);
            p->width--;
        }
    }
}

void    ft_print_decimal_right(t_printf *p, intmax_t num)
{
    int numlen;
    int znak;

    znak = 1;
    numlen = ft_len(num, 10);
    if (num < 0)
    {
        znak = -1;
        num *= -1;
    }
    if (ft_print_decimal_right2(p, num, znak))
        return;
    if (p->plus && znak == 1 && p->width && !p->fl_precision)
        numlen++;
    ft_print_decimal3(p, num, numlen);
    if (znak == 1 && p->plus && !p->zero)
        p->len += write(p->fd, "+", 1);
    else if (znak == -1 && !p->zero)
    {
        p->len += write(p->fd, "-", 1);
        numlen--;
    }
    while (p->precision > numlen)
    {
        p->len += write(p->fd, "0", 1);
        numlen++;
    }
    p->len += ft_itoa_base_pr(p->fd, num, 10);

}

void    ft_print_decimal_left2(t_printf *p, intmax_t num)
{
    if (num == 0 && p->fl_precision && !p->precision)
    {
        if (p->plus)
            p->len += write(p->fd, "+", 1);
    }
}

void    ft_print_decimal_left(t_printf *p, intmax_t num)
{
    int znak;
    int numlen;

    znak = 1;
    numlen = ft_len(num, 10);
    if (num < 0)
    {
        znak = -1;
        num *= -1;
    }
    if (num == 0 && p->fl_precision && !p->precision)
    {
        if (p->plus && p->width)
            p->width--;
        if (p->plus)
            p->len += write(p->fd, "+", 1);
        while (p->width--)
            p->len += write(p->fd, " ", 1);
        return;
    }
    if (p->space && znak == 1)
    {
        p->width--;
        p->len += write(p->fd, " ", 1);
    }
    if (p->plus && znak == 1)
    {
        numlen++;
        p->len += write(p->fd, "+", 1);
    }
    else if (znak == -1)
        p->len += write(p->fd, "-", 1);
    while (p->precision >= numlen)
    {
        p->len += write(p->fd, "0", 1);
        numlen++;
    }
    p->len += ft_itoa_base_pr(p->fd, num, 10);
    while (p->width > numlen)
    {
        p->len += write(p->fd, " ", 1);
        numlen++;
    }
}

void    ft_print_decimal(t_printf *p, va_list argc, char c)
{
    intmax_t num;

    if (c == 'i' || c == 'd' || c == 'D')
    {
        if (c == 'D')
            num = va_arg(argc, long);
        else if (!p->length)
            num = va_arg(argc, int);
        else if (p->length = HH)
            num = (signed char)va_arg(argc, int);
        else if (p->length = H)
            num = (short int)va_arg(argc, int);
        else if (p->length = L)
            num = va_arg(argc, long int);
        else if (p->length = LL)
            num = va_arg(argc, long long);
        else if (p->length = J)
            num = va_arg(argc, intmax_t);
        else if (p->length = Z)
            num = va_arg(argc, size_t);
        if (p->minus)
            ft_print_decimal_left(p, num);
        else
            ft_print_decimal_right(p, num);
    }
}
