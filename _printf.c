#include "main.h"

void printToBuffer(char buffer[], int *buffIndex);

/**
 * myPrintf - Custom printf function
 * @format: The format string.
 * Return: The number of characters printed.
 */
int myPrintf(const char *format, ...)
{
	int i, totalPrintedChars = 0, printedChars = 0;
	int flags, width, precision, size, buffIndex = 0;
	va_list argList;
	char buffer[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(argList, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buffIndex++] = format[i];
			if (buffIndex == BUFFER_SIZE)
				printToBuffer(buffer, &buffIndex);
			printedChars++;
		}
		else
		{
			printToBuffer(buffer, &buffIndex);
			flags = getFlags(format, &i);
			width = getWidth(format, &i, argList);
			precision = getPrecision(format, &i, argList);
			size = getSize(format, &i);
			++i;
			printedChars = handlePrint(format, &i, argList, buffer, flags, width, precision, size);
			if (printedChars == -1)
				return (-1);
			totalPrintedChars += printedChars;
		}
	}

	printToBuffer(buffer, &buffIndex);

	va_end(argList);

	return (totalPrintedChars);
}

/**
 * printToBuffer - Prints the contents of the buffer if it exists
 * @buffer: Array of characters
 * @buffIndex: Index at which to add the next character, represents the length.
 */
void printToBuffer(char buffer[], int *buffIndex)
{
	if (*buffIndex > 0)
		write(1, &buffer[0], *buffIndex);

	*buffIndex = 0;
}

