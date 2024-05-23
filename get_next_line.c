/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:14 by alarose           #+#    #+#             */
/*   Updated: 2024/05/20 16:47:20 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			buff[BUFFER_SIZE];
	size_t			ret_read;
	size_t			nb_chars;
	static t_list	*stock = NULL;

	ret_read = BUFFER_SIZE;
	if (find_nl_or_eof(&stock, ret_read) && ret_read != 0)
	{
		nb_chars = get_len(&stock);
		return (cpy_n_free(&stock, nb_chars));
	}
	while (ret_read != 0)
	{
		ret_read = read_n_stock(fd, buff, &stock);
		if (find_nl_or_eof(&stock, ret_read))
			break ;
	}
	if (!stock)
		return (NULL);
	nb_chars = get_len(&stock);
	return (cpy_n_free(&stock, nb_chars));
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
