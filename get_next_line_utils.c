/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:47:53 by alarose           #+#    #+#             */
/*   Updated: 2024/05/30 17:44:59 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_n_stock(int fd, char *buff, t_list **stock)
{
	int		ret_read;
	int		i;
	t_list	*new;
	t_list	*tmp;

	ret_read = read(fd, buff, BUFFER_SIZE);
	i = 0;
	while (i < ret_read)
	{
		new = malloc(sizeof(t_list));
		if (!new)
			return (-1);
		new->c = buff[i++];
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
	}
	return (ret_read);
}

int	find_nl_or_eof(t_list **stock, int ret_read)
{
	t_list	*tmp;

	tmp = *stock;
	while (tmp)
	{
		if (ret_read < (int)BUFFER_SIZE || tmp->c == '\n')
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

void	free_all(t_list **stock)
{
	t_list	*tmp;

	while (*stock != NULL)
	{
		tmp = *stock;
		*stock = (*stock)->next;
		free(tmp);
	}
}
