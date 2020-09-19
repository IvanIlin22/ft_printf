//
// Created by ivan on 15.09.2020.
//
#include "ft_printf.h"

bool     ft_isdigit(int c)
{
    if (c >= '0' && c <= '9')
        return (true);
    return (false);
}

int						ft_atoi(const char *str)
{
    int					i;
    int					znak;
    unsigned long long	res;

    i = 0;
    res = 0;
    znak = 1;
    while (str[i] == '\t' || str[i] == '\n' || str[i] == ' ' ||
           str[i] == '\f' || str[i] == '\v' || str[i] == '\r')
        i++;
    if (str[i] == '+')
        i++;
    else if (str[i] == '-')
    {
        znak = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
        res = res * 10 + (str[i++] - '0');
    if (res > 9223372036854775807 && znak == 1)
        return (-1);
    if (res > 9223372036854775807 && znak == -1)
        return (0);
    return (res * znak);
}

static void ft_parse_width(t_printf *p, const char *format, va_list argc)
{
    if (format[p->i] == '*')
    {
        p->width = va_arg(argc, int);
        if (p->width < 0)
        {
            p->minus = 1;
            p->width = -p->width;
        }
        //перемещать укзатаель в цикле пока*
        p->i++;
    }
    if (ft_isdigit(format[p->i]))
    {
        p->width = ft_atoi(&format[p->i]);
        while (ft_isdigit(format[p->i]))
        {
            p->i++;
            //
            /*if(format[p->i] == '*')
            {
                p->width = va_arg(argc, int);
                if (p->width < 0)
                {
                    p->minus = 1;
                    p->width = -p->width;
                }
                p->i++;
            }*/
            //
        }
    }
}

static void ft_parse_flags(t_printf *p, const char *format)
{

    while (ft_strchr("-+ #0", format[p->i]))
    {
        if (format[p->i] == '-')
            p->minus = 1;
        else if (format[p->i] == '+')
            p->plus = 1;
        else if (format[p->i] == '#')
            p->hash = 1;
        else if (format[p->i] == '0')
            p->zero = 1;
        else if (format[p->i] == ' ')
            p->space = 1;
        p->i++;
    }
    if (p->plus)
        p->space = 0;
}

static void    ft_parse_precision(t_printf *p, const char *format, va_list argc)
{
    if(format[p->i] == '.')
    {
        p->i++;
        p->fl_precision = 1;
        if (format[p->i] == '*')
        {
            p->precision = va_arg(argc, int);
            if (p->precision < 0)
            {
                p->fl_precision = 0;
                p->precision = 0;
            }
            p->i++;
        }
        else if (ft_isdigit(format[p->i]))
        {
            p->precision = ft_atoi(&format[p->i]);
            while(ft_isdigit(format[p->i]))
                p->i++;
        }
    }
    /*if(p->fl_precision && !p->minus)
        p->space = 0;*/
}

static void    ft_parse_length(t_printf *p, const char *format)
{
    if (ft_strchr("hljz", format[p->i]))
    {
        if (format[p->i] == 'h')
        {
            if (format[p->i + 1] == 'h')
                p->length = HH;
            else
                p->length = H;
        }
        else if (format[p->i] == 'l')
        {
            if (format[p->i + 1] == 'l')
                p->length = LL;
            else
                p->length = L;
        }
        else if (format[p->i] == 'j')
            p->length = J;
        else if (format[p->i] == 'z')
            p->length = Z;
        while (ft_strchr("hljz", format[p->i]))
            p->i++;
    }

}

void    ft_parse_modificator(t_printf *p, va_list argc, const char *format)
{
    ft_parse_flags(p, format);
    ft_parse_width(p, format, argc);
    ft_parse_precision(p, format, argc);
    ft_parse_length(p, format);

}

