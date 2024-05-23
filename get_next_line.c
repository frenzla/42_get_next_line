/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:47:49 by alarose           #+#    #+#             */
/*   Updated: 2024/05/17 18:57:36 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void	print_error()
{
	if (errno != 0 )
		printf("ERROR: %s", strerror(errno));
}

int	add_char(t_list **stock, char c)
{
	t_list *new;
	t_list *last;

	new = malloc(sizeof(t_list));
	if (!new)
		return (-1);
	new->c = c;
	new->next = NULL;
	if(!(*stock))
		*stock = new;
	else
	{
		last = *stock; // SEE IF "last" OR "*last"
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (0);
}

int	add_to_stock(int fd, t_list **stock)
{
	char	buff[BUFFER_SIZE + 1];
	t_list	*new;
	int		ret_read;
	int		i;
	t_list	*last;

	ret_read = read(fd, buff, BUFFER_SIZE);
	if (ret_read <= 0)
		return (ret_read);
	buff[ret_read] = '\0';
	i = 0;
	while (i < ret_read)
	{
		add_char(stock, buff[i]);
		i++;
	}
	return (ret_read);
}

int	check_nl(t_list *stock, int ret_read)
{
	t_list	*current;
	int		count;

	current = stock;
	while (current)
	{
		count++;
		if (current->c == '\n' || ret_read < BUFFER_SIZE)
			return(1);
		current = current->next;
	}
	return(0);
}

int	find_len(t_list *stock)
{
	int		nb_chars;
	t_list	*current;

	nb_chars = 0;
	current = stock;
	while (current && current->c != '\n')
	{
		nb_chars++;
		current = current->next;
	}
	nb_chars++;
	return (nb_chars);
}

char *cpy_n_free(t_list **stock, int line_len)
{
	t_list	*temp;
	char	*line;
	int		i;

	line = malloc(sizeof(char) * line_len);
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_len && *stock)
	{
		line[i] = (*stock)->c;
		temp = *stock;
		*stock = (*stock)->next;
		free(temp);
		i++;
	}
	line[i] = '\0';
	return(line);
}

char *get_next_line(int fd)
{
	int		ret_read;
	static t_list	*stock;
	int		line_len;

	ret_read = 1;
	while (ret_read != 0)
	{
		ret_read = add_to_stock(fd, &stock);
		if (check_nl(stock, ret_read))
			break;
	}
	if (ret_read == 0 || !stock)
		return (NULL);
	line_len = find_len(stock);
	return (cpy_n_free(&stock, line_len));
}

int	main(void)
{
	int		fd;
	char	*line;

	errno = 0;
//Open file
	fd = open("myExample.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("File couldn't OPEN: ");
		print_error();
		return (1);
	}

	line = get_next_line(fd);
	printf("LINE: %s", line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		printf("LINE: %s", line);
	}
	free(line);

	close(fd);
	return (0);
}