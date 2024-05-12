/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:47:49 by alarose           #+#    #+#             */
/*   Updated: 2024/05/08 16:35:39 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
1. check if BUFFER_SIZE is def and not 0
2. malloc my buff with BUFFER_SIZE
3. read and store BUFFER_SIZE nb of bytes in buff.
4. check buff for \n
	- IF no \n => go to 3
	- ELSE \n => store what comes after the \n in a static variable (e.g. rest)
5. When read is launched again: check if rest is empty
	- IF empty => go to 3
	- ELSE copy chars from rest (unitl end or until \n) + clean rest


Hints:
- On appelle “ligne” une suite de caractères terminée par un ’\n’ (code ascii 0x0a) ou bien par End Of File (EOF).
- use static variables. -> the number of times we went through the function? for the input in **line ?
- must read from files but also any standard input.
- file offset is incremented by the number of bytes read.
- If the file offset is at or past the end of file, no bytes are read, and read() returns zero.
- According to POSIX.1, if count is greater than SSIZE_MAX, the result is implementation-defined;
	see NOTES for the upper limit on Linux.
- READ: On error, -1 is returned, and errno is set to indicate the error.
*/

int	get_next_line(int fd, char **line)
{

}
