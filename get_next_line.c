/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:14 by alarose           #+#    #+#             */
/*   Updated: 2024/05/30 17:47:43 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*buff;
	int				ret_read;
	static t_list	*stock = NULL;

	buff = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE > INT_MAX)
		return (free_all(&stock), NULL);
	ret_read = BUFFER_SIZE;
	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buff)
		return (free_all(&stock), NULL);
	while (ret_read != 0 && !(find_nl_or_eof(&stock, ret_read)))
	{
		ret_read = read_n_stock(fd, buff, &stock);
		if (ret_read < 0)
			return (free_all(&stock), free (buff), NULL);
	}
	free (buff);
	if (find_nl_or_eof(&stock, ret_read))
		return (cpy_n_free(&stock, get_len(&stock)));
	return (free_all(&stock), NULL);
}

/*#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	fd;
	char *line;
	//Open file
	fd = open("./myExample.txt", O_RDONLY);
	if (fd < 1)
	{
		printf("Error while opening file\n");
		return (-1);
	}
	else
		printf("File open\n\n" );

	//call get_next_line in a loop
	line = get_next_line(fd);
	while (line)
	{
		printf("LINE: %s", line);
		printf("********************************\n");
		free(line);
		line = get_next_line(fd);
	}

	//free and close file
	free(line);
	close (fd);

	//return
	return (0);
}*/
