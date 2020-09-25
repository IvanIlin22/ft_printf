#include "ft_printf.h"

void    *ft_memalloc(size_t size)
{
    void    *p;
    size_t  i;

    p = (void*)malloc(size);
    if (p == NULL)
        return (NULL);
    i = 0;
    while(i < size)
    {
        ((char*)p)[i] = 0;
        i++;
    }
    return (p);
}

int     ft_strlen(const char *str)
{
    if (!str)
        return 0;
    int len;

    len = 0;
    while(str[len])
        len++;
    return len;
}

char    *ft_strchr(const char *str, char c)
{
    int     i;

    i = 0;
    while (str[i])
    {
        if (str[i] == c)
            return ((char*)&str[i]);
        i++;
    }
    return NULL;
}

static t_printf *ft_init_struct(t_printf *p)
{
    if ((p = (t_printf*)ft_memalloc(sizeof(t_printf))) == NULL)
        return(NULL);
    p->len = 0;
    p->i = 0;
    p->fd = 1;
    return(p);
}

void    ft_reset_struct(t_printf *p)
{
    p->minus = 0;
    p->plus = 0;
    p->hash = 0;
    p->space = 0;
    p->zero = 0;
    p->length = 0;
    p->precision = 0;
    p->fl_precision = 0;
    p->width = 0;
}

void    ft_print(t_printf *p, va_list argc, const char *format)
{
    if (format[p->i] == 'd' || format[p->i] == 'D' || format[p->i] == 'i')
        ft_print_decimal(p, argc, format[p->i]);
    else if (format[p->i] == 'o' || format[p->i] == 'O')
        ft_print_octal(p, argc, format[p->i]);
    else if (format[p->i] == 's' || format[p->i] == 'S')
        ft_print_string(p, argc, format[p->i]);
    else if (format[p->i] == 'c' || format[p->i] == 'C')
        ft_print_char(p, argc, format[p->i]);
    /*else if (format[p->i] == 'p')
        ft_print_pointer(p, argc, format[p->i]);
    else if (format[p->i] == 'u' || format[p->i] == 'U')
        ft_print_(p, argc, format[p->i]);
    else if (format[p->i] == 'x' || format[p->i] == 'X')
        ft_print_hexadecimal(p, argc, format[p->i]);
    else if (format[p->i] == 'b')
        ft_print_binary(p, argc, format[p->i]);
    else if (format[p->i] == 'r')
        ft_print_control_char(p, argc, format[p->i]);
    else if (format[p->i] == '%')
        ft_print_percent(p, argc, format[p->i]);*/

}

void    ft_process_string(t_printf *p, va_list args, const char *format)
{
    while (format[p->i])
    {
        if (format[p->i] == '%')
        {
            p->i++;
            if (ft_strchr("#-+ .*0123456789hljz", format[p->i]))
                ft_parse_modificator(p, args, format);
            if (ft_strchr("sSpdDioOuUxXcCbr%", format[p->i]))
            {
                ft_print(p, args, format);
                if (p->len == -1)
                    return;
                ft_reset_struct(p);
            }
        }
        else
            p->len += write(p->fd, &format[p->i], 1);
        p->i++;
    }
}

int     ft_printf(const char *format, ...)
{
    int         len;
    t_printf    *p;
    va_list     argc;

    //p = NULL;
    p = ft_init_struct(p);

    va_start(argc, format);
    if (format[0] == '%' && format[1] == '\0')
        ;
    else if (!ft_strchr(format, '%'))
        p->len += write(p->fd, format, ft_strlen(format));
    else
        ft_process_string(p, argc, format);
    len = p->len;
    free(p);
    va_end(argc);
    return (len);
}

bool     ft_is_digit(int c)
{
    if (c >= '0' && c <= '9')
        return (true);
    return (false);
}

int     ft_itoa_base_pr(int fd, intmax_t num, int base)
{
    int     len;
    intmax_t    val;
    char    *res;
    char    *str = "0123456789ABCDEF";

    len = 1;
    val = num;
    while (val /= base)
        len++;
    res = (char*)malloc(sizeof(char) * (len + 1));
    res[len] = '\0';

    while(--len >= 0)
    {
        res[len] = str[num % base];
        num /= base;
    }
    len = ft_strlen(res);
    write(fd, res, len);
    free(res);
    return (len);

}


int main() {

    setlocale(LC_ALL, "");
    //printf("%i\n", ft_itoa_base_pr(1, 150, 10));
    //printf("%08.4f\n", 2.5);
    int len = 0;
    int lenmy = 0;

    wchar_t *str = NULL;
    ft_printf("%15.13ls", L"Hello!€¢");
    printf("124\n");
    printf("%15.13ls", L"Hello!€¢");
    printf("123\n");
    ft_printf("%-10.6ls", str);
    printf("4\n");
    printf("%-10.6ls", str);
    printf("4\n");

    //printf("%-+5.i\n", 1);
    //printf("len = %i\n", len);
    //printf("lenmy = %i\n", len);
}
/*
//тест Восьмеричных
ft_printf("%-0#8.4o", 11);
printf("Hello1\n");
printf("%-0#8.4o", 10);
printf("Hello1\n");
ft_printf("%-#04.o", 11);
printf("Hello2\n");
printf("%-#04.o", 10);
printf("Hello2\n");
printf("%-0#4.8o", 11);
printf("Hello3\n");
ft_printf("%-0#4.8o", 10);
printf("Hello3\n");
    /символ
    ft_printf("%-5lc", L'¢');
    printf("Hello\n");
    printf("%-5lc", L'¢');
    printf("Hello\n");
    ft_printf("%011lc\n", L'€');
    printf("%011lc\n", L'€');
 */
