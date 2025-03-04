#pragma once

namespace UtilityFunctions
{
	bool containsNewline(char* buffer)
	{
		while (*buffer)
		{
			if (*buffer++ == '\n')
				return true;
		}

		return false;
	}
	void decodeEntity(char* str)
	{
		char* ptr = str;
		while (*ptr != '\0')
		{
			if (*ptr == '&' && *(ptr + 1) == '#' && *(ptr + 2) >= '0' && *(ptr + 2) <= '9')
			{
				int code = 0;
				ptr += 2; // Move past "&#" characters
				while (*ptr >= '0' && *ptr <= '9')
				{
					code = code * 10 + (*ptr - '0');
					ptr++;
				}

				*str++ = (char)code;
			}
			else
			{
				*str++ = *ptr++;
			}
		}

		*str = '\0'; // Null-terminate the modified string
	}
	bool areOnlySpaces(char* str)
	{
		if (strlen(str) == 0)
			return true;
		while (*str)
		{
			if (*str != ' ' && *str != '\n')
				return false;
			*str++;
		}

		return true;
	}
	void removeWhitespaces(char* str)
	{
		char* ptr = str;
		char* startPtr = nullptr;
		bool isTagOpen = true;
		while (*str)
		{
			if (*str != ' ' || startPtr)
			{
				if (!startPtr)
				{
					startPtr = ptr;
				}
				*ptr++ = *str;
			}
			str++;
		}
		if (startPtr)
		{
			*ptr = '\0'; // Null-terminate the string if there were leading spaces
		}
	}
}