#include "main.h"

/* print a single character */
int print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

/* print a string */
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

/* print a percent sign */
int print_percent(void)
{
	write(1, "%", 1);
	return (1);
}

/* print unknown specifier as %<char> */
int print_unknown(char c)
{
	write(1, "%", 1);
	write(1, &c, 1);
	return (2);
}

/* main _printf function */
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

