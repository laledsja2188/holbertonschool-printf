#include "main.h"

/**
 * print_char - prints a single character
 * @c: character to print
 *
 * Return: number of characters printed
 */
int print_char(char c)
{
    write(1, &c, 1);
    return (1);
}

/**
 * print_string - prints a string
 * @s: string to print
 *
 * Return: number of characters printed
 */
int print_string(char *s)
{
    int count = 0;

    if (!s)
        s = "(null)";

    while (*s)
    {
        write(1, s, 1);
        s++;
        count++;
    }
    return (count);
}

/**
 * print_percent - prints a percent sign
 *
 * Return: number of characters printed
 */
int print_percent(void)
{
    write(1, "%", 1);
    return (1);
}

/**
 * print_unknown - prints unknown specifier as %<char>
 * @c: unknown specifier character
 *
 * Return: number of characters printed
 */
int print_unknown(char c)
{
    write(1, "%", 1);
    write(1, &c, 1);
    return (2);
}

/**
 * print_number - prints an integer number
 * @n: integer to print
 *
 * Return: number of characters printed
 */
int print_number(int n)
{
    int count = 0;
    unsigned int num;

    if (n < 0)
    {
        write(1, "-", 1);
        count++;
        num = -n;
    }
    else
        num = n;

    if (num / 10)
        count += print_number(num / 10);

    write(1, &"0123456789"[num % 10], 1);
    count++;

    return (count);
}

/**
 * _printf - produces output according to a format
 * @format: format string
 *
 * Return: number of characters printed (excluding null byte),
 *         or -1 if format is NULL
 */
int _printf(const char *format, ...)
{
    va_list args;
    int i = 0, count = 0;

    if (!format)
        return (-1);

    va_start(args, format);

    while (format[i])
    {
        if (format[i] == '%')
        {
            i++;
            if (!format[i])
            {
                va_end(args);
                return (-1);
            }

            if (format[i] == 'c')
                count += print_char((char)va_arg(args, int));
            else if (format[i] == 's')
                count += print_string(va_arg(args, char *));
            else if (format[i] == '%')
                count += print_percent();
            else if (format[i] == 'd' || format[i] == 'i')
                count += print_number(va_arg(args, int));
            else
                count += print_unknown(format[i]);
        }
        else
            count += print_char(format[i]);
        i++;
    }

    va_end(args);
    return (count);
}

