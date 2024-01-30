#include "main.h"
/**
 * _printf - a function that produces output according to a format
 * @format: string that contains characters
 * Return: Returns the number of characters printed
 */
int _printf(const char *format, ...)
{
	int j, i, len = 0;
	char *str;
	char c;
	va_list arg_list;

	va_start(arg_list, format);
	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 'c')
			{
				c = va_arg(arg_list, int);
				putchar(c);
			}
			if (format[i] == 's')
			{
				str = va_arg(arg_list, char *);
				for (j = 0; str[j] != '\0'; j++)
				{
					putchar(str[j]);
					len++;
				}
			}
			if (format[i] == '%')
				putchar('%');

		}

		else
		{
			putchar (format[i]);
			len++;
		}
	}
	va_end(arg_list);
	return (len);
}
