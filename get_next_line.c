/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:14 by alarose           #+#    #+#             */
/*   Updated: 2024/05/18 10:34:34 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*int	add_to_stock(char *buff, t_list **stock)
{

}*/

size_t	read_n_stock(int fd, char *buff)
{
	size_t	ret_read;
	t_list	*stock;

	ret_read = -1;
	ret_read = read(fd, buff, BUFFER_SIZE);
	if (ret_read < 1)
		return (ret_read);
	buff[ret_read] = '\0';
	//WORKING: printf("ret_read: %zu, buff: %s\n", ret_read, buff);

	//add_to_stock(buff, &stock);

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