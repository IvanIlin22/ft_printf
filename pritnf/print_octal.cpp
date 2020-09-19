//
// Created by ivan on 18.09.2020.
//
#include "ft_printf.h"

void    ft_print_octal_left(t_printf *p, intmax_t num)
{
    int numlen;

    numlen = ft_len(num, 8);
    if (num == 0 && p->fl_precision && !p->precision)
    {
        if (p->hash)
            p->len += write(p->fd, "0", 1);
        while (p->width-- > numlen)
            p->len += write(p->fd, " ", 1);
        return;
    }
    if (p->hash && num != 0)
    {
        p->len += write(p->fd, "0", 1);
        numlen++;
    }
    while (p->precision > numlen++)
        p->len = write(p->fd, "0", 1);
    p->len += ft_itoa_base_pr(p->fd, num, 8);
    while (p->width-- >= numlen)
        p->len += write(p->fd, " ", 1);
}

static void	ft_print_octal_left1(t_printf *f, intmax_t nbr)
{
    int nbrlen;

    nbrlen = ft_len(nbr, 8);
    if (nbr == 0 && f->fl_precision && !f->precision)
    {
        while (f->width)
        {
            f->len += write(f->fd, " ", 1);
            f->width--;
        }
        if (!f->hash)
            return ;
    }
    if (f->hash && nbr != 0)
    {
        f->len += write(f->fd, "0", 1);
        nbrlen++;
    }
    while (nbrlen++ < f->precision)
        f->len += write(f->fd, "0", 1);
    f->len += ft_itoa_base_pr(f->fd, nbr, 8);
    while (f->width-- >= nbrlen)
        f->len += write(f->fd, " ", 1);
}

void    ft_print_octal_right(t_printf *p, intmax_t num)
{
    int numlen;
    int i;

    i = 0;
    numlen = ft_len(num, 8);
    if (num == 0 && p->fl_precision && !p->precision)
    {
        while (p->width-- > numlen)
            p->len += write(p->fd, " ", 1);
        if (p->hash)
            p->len += write(p->fd, "0", 1);
        return;
    }

     if (p->hash && num !=0)
     {
         //p->width--;
         numlen++;
     }
    if (!p->fl_precision)
    {
        while (p->width > numlen) {
            if (p->zero)
                p->len += write(p->fd, "0", 1);
            else
                p->len += write(p->fd, " ", 1);
            numlen++;
        }
    }
    else
    {
        if (p->precision > 0)
            i = p->precision;
        else
            i = numlen;
        while (p->width > i)
        {
            p->len += write(p->fd, " ", 1);
            p->width--;
        }
    }
    while (p->precision > numlen++)
        p->len += write(p->fd, "0", 1);
    if (p->hash && num !=0)
    {
        p->len += write(p->fd, "0", 1);
    }
    p->len += ft_itoa_base_pr(p->fd, num, 8);
}

void    ft_print_octal(t_printf *p, va_list argc, char c)
{
    intmax_t num;

    if (c == 'O')
        num = va_arg(argc, unsigned long);
    else if (!p->length)
        num = va_arg(argc, unsigned int);
    else if (p->length == L)
        num = va_arg(argc, unsigned long int);
    else if (p->length == LL)
        num = va_arg(argc, unsigned long long int);
    else if (p->length == H)
        num = (unsigned short)va_arg(argc, unsigned int);
    else if (p->length == HH)
        num = (unsigned char)va_arg(argc, unsigned int);
    else if (p->length == J)
        num = va_arg(argc, intmax_t);
    else if (p->length == Z)
        num = va_arg(argc, size_t);
    if (p->minus)
        ft_print_octal_left(p, num);
    else
        ft_print_octal_right(p, num);
}