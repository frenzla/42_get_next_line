/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:14 by alarose           #+#    #+#             */
/*   Updated: 2024/05/20 12:18:10 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

typedef struct s_list
{
	char			c;
	struct s_list	*next;
} t_list;

#endif

//******************TEST FUNCTION******************
void	print_lst(t_list **stock)
{
	t_list	*tmp;

	tmp = *stock;
	if (!tmp)
		printf("STOCK IS EMPTY\n");
	else
	{
		//printf("IN STOCK: ");
		while (tmp)
		{
			//printf("%c|", tmp->c);
			tmp = tmp->next;
		}
		//printf("\n");
	}
}
//******************TEST FUNCTION******************

int	add_to_stock(char c, t_list **stock)
{
	t_list	*new;
	t_list	*tmp;

	new = malloc(sizeof(t_list));
	if (!new)
		return (-1);
	new->c = c;
	new->next = NULL;
	if (!(*stock))
		*stock = new;
	else
	{
		tmp = *stock;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

size_t	read_n_stock(int fd, char *buff, t_list **stock)
{
	size_t	ret_read;
	int		i;

	ret_read = read(fd, buff, BUFFER_SIZE);
	if (ret_read < 1)
		return (ret_read);
	buff[ret_read] = '\0';
	//WORKING: printf("ret_read: %zu, buff: %s\n", ret_read, buff);
	i = 0;
	while (i < ret_read)
	{
		add_to_stock(buff[i], stock);
		i++;
	}
	/*WORKING: */print_lst(stock);
	return(ret_read);
}

int	find_NL_or_EOF(t_list **stock, int	ret_read)
{
	t_list	*tmp;

	tmp = *stock;
	while (tmp)
	{
		if (ret_read < BUFFER_SIZE || tmp->c == '\n')
		{
			printf("NL or EOF found\n");
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
size_t	get_len(t_list **stock)
{
	t_list	*tmp;
	size_t	nb_chars;

	tmp = *stock;
	nb_chars = 0;
	//printf("Counting: ");
	while (tmp && tmp->c != '\n')
	{
		nb_chars++;
		//printf("%c|", tmp->c);
		tmp = tmp->next;
	}
	if (tmp && tmp->c == '\n')
		nb_chars++;
	printf("\nnb_chars (with NL): %zu\n", nb_chars);
	return (nb_chars);
}

char	*cpy_n_free(t_list **stock, size_t nb_chars)
{
	char	*line;
	t_list	*tmp;
	size_t		i;

	line = malloc(sizeof(char) * (nb_chars + 1));
	if (!line)
		return (NULL);
	i = 0;
	//printf("Copied: ");
	while (i < nb_chars) // && *stock ?
	{
		line[i] = (*stock)->c;
		//printf("%c|", line[i]);
		tmp = *stock;
		*stock = (*stock)->next;
		free(tmp);
		i++;
	}
	line[i]= '\0';
	//printf("\nAfter deletion - ");
	//print_lst(stock);
	return (line);
}

char	*get_next_line(int fd)
{
	//create buffer
	char 			buff[BUFFER_SIZE + 1];
	size_t			ret_read;
	size_t			nb_chars;
	static t_list	*stock = NULL;
	char			*line;

	line = NULL;
	ret_read = BUFFER_SIZE;
	//printf("CURRENT STOCK: ");
	print_lst(&stock);
	//read & stock
	if (find_NL_or_EOF(&stock, ret_read))
	{
		nb_chars = get_len(&stock);
		//printf("Chars to copy: %zu\n", nb_chars);
		//copy in line and free stock
		line = cpy_n_free(&stock, nb_chars);
		return (line);
	}
	while(ret_read != 0)
	{
		ret_read = read_n_stock(fd, buff, &stock);
		//WORKING: printf("\nRET_READ = %zu\n\n", ret_read);
		//check stock for newline OR EOF => break while if NL OR EOF
		if (find_NL_or_EOF(&stock, ret_read))
			break;
	}
	if (ret_read == 0 || !stock)
		return (NULL);
	//count nb_chars to write in line
	nb_chars = get_len(&stock);
	//printf("Chars to copy: %zu\n", nb_chars);
	//copy in line and free stock
	line = cpy_n_free(&stock, nb_chars);
	return(line);
}

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
	printf("LINE: %s\n", line);
	printf("********************************\n");
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			printf("LINE: %s\n", line);
			printf("********************************\n");
		}
	}

	//free and close file
	close (fd);

	//return
	return (0);
}