/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:14 by alarose           #+#    #+#             */
/*   Updated: 2024/05/21 11:08:13 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*buff;
	size_t			ret_read;
	static t_list	*stock[1024];

	buff = NULL;
	if (fd < 0 || read(fd, buff, 0) < 0)
		return (NULL);
	ret_read = BUFFER_SIZE;
	if (find_nl_or_eof(&stock[fd], ret_read) && ret_read != 0)
		return (cpy_n_free(&stock[fd], get_len(&stock[fd])));
	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buff)
		return (NULL);
	while (ret_read != 0)
	{
		ret_read = read_n_stock(fd, buff, &stock[fd]);
		if (find_nl_or_eof(&stock[fd], ret_read))
			break ;
	}
	free (buff);
	if (!stock[fd])
		return (NULL);
	return (cpy_n_free(&stock[fd], get_len(&stock[fd])));
}

/*#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	fd1;
	int	fd2;
	int	fd3;
	char *line;
	//Open file
	fd1 = open("./myExample.txt", O_RDONLY);
	fd2 = open("./myExample2.txt", O_RDONLY);
	fd3 = open("./myExample3.txt", O_RDONLY);
	if (fd1 < 1)
	{
		printf("Error while opening FD1\n");
		return (-1);
	}
	else
		printf("FD1 open\n\n" );

	if (fd2 < 1)
	{
		printf("Error while opening FD2\n");
		return (-1);
	}
	else
		printf("FD2 open\n\n" );

	if (fd1 < 1)
	{
		printf("Error while opening FD3\n");
		return (-1);
	}
	else
		printf("FD3 open\n\n" );

	//call get_next_line in a loop
	line = get_next_line(fd1);
	printf("LINE: %s", line);
	printf("********************************\n");
	free(line);

	line = get_next_line(fd2);
	printf("LINE: %s", line);
	printf("********************************\n");
	free(line);

	line = get_next_line(fd2);
	printf("LINE: %s", line);
	printf("********************************\n");
	free(line);

	line = get_next_line(fd1);
	printf("LINE: %s", line);
	printf("********************************\n");
	free(line);

	line = get_next_line(fd3);
	printf("LINE: %s", line);
	printf("********************************\n");
	free(line);

	line = get_next_line(fd3);
	printf("LINE: %s", line);
	printf("********************************\n");
	free(line);

	line = get_next_line(fd3);
	printf("LINE: %s", line);
	printf("********************************\n");
	free(line);

	line = get_next_line(fd2);
	printf("LINE: %s", line);
	printf("********************************\n");
	free(line);

	line = get_next_line(fd1);
	printf("LINE: %s", line);
	printf("********************************\n");
	free(line);

	//free and close file
	close (fd1);
	close (fd2);
	close (fd3);

	//return
	return (0);
}*/
