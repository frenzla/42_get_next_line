/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:14 by alarose           #+#    #+#             */
/*   Updated: 2024/05/18 11:19:04 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

//******************TEST FUNCTION******************
void	print_lst(t_list **stock)
{
	t_list	*tmp;

	tmp = *stock;
	if (!tmp)
		printf("STOCK IS EMPTY\n");
	else
	{
		printf("IN STOCK: ");
		while (tmp)
		{
			printf("%c|", tmp->c);
			tmp = tmp->next;
		}
		printf("\n");
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
	if (!*stock)
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

size_t	read_n_stock(int fd, char *buff)
{
	size_t	ret_read;
	t_list	*stock;
	int		i;

	ret_read = read(fd, buff, BUFFER_SIZE);
	if (ret_read < 1)
		return (ret_read);
	buff[ret_read] = '\0';
	//WORKING: printf("ret_read: %zu, buff: %s\n", ret_read, buff);
	i = 0;
	while (i < ret_read)
	{
		add_to_stock(buff[i], &stock);
		i++;
	}
	//WORKING: print_lst(&stock);
	return(ret_read);
}

char	*get_next_line(int fd)
{
	//create buffer
	char 	buff[BUFFER_SIZE +1];
	size_t	ret_read;

	ret_read = -1;
	//read & stock
	while(ret_read != 0)
	{
		ret_read = read_n_stock(fd, buff);
		if (ret_read < 1)
			return (NULL);
		//WORKING: printf("\nRET_READ = %zu\n\n", ret_read);
		//check stock for newline OR EOF

	}
	//count nb_chars to write in line

	//copy in line and free stock
	return (NULL);
}

int	main(void)
{
	int	fd;
	//Open file
	fd = open("./myExample.txt", O_RDONLY);
	if (fd < 1)
	{
		printf("Error while opening file\n");
		return (-1);
	}
	else
		printf("File open\n" );

	//call get_next_line in a loop
	get_next_line(fd);

	//free and close file
	close (fd);

	//return
	return (0);
}