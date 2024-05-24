/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:47:53 by alarose           #+#    #+#             */
/*   Updated: 2024/05/24 15:51:47 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//******************TEST FUNCTION******************
/*void	print_lst(t_list **stock)
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
}*/
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
	size_t	i;

	ret_read = read(fd, buff, BUFFER_SIZE);
	if (ret_read < 1)
		return (ret_read);
	i = 0;
	while (i < ret_read)
	{
		add_to_stock(buff[i], stock);
		i++;
	}
	return (ret_read);
}

int	find_nl_or_eof(t_list **stock, int ret_read)
{
	t_list	*tmp;

	tmp = *stock;
	while (tmp)
	{
		if (ret_read < BUFFER_SIZE || tmp->c == '\n')
			return (1);
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
	while (tmp && tmp->c != '\n')
	{
		nb_chars++;
		tmp = tmp->next;
	}
	if (tmp && tmp->c == '\n')
		nb_chars++;
	return (nb_chars);
}

char	*cpy_n_free(t_list **stock, size_t nb_chars)
{
	char	*line;
	t_list	*tmp;
	size_t	i;

	line = malloc(sizeof(char) * (nb_chars + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < nb_chars)
	{
		line[i] = (*stock)->c;
		tmp = *stock;
		*stock = (*stock)->next;
		free (tmp);
		i++;
	}
	line[i] = '\0';
	return (line);
}
