/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alarose <alarose@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 09:29:14 by alarose           #+#    #+#             */
/*   Updated: 2024/05/30 10:56:38 by alarose          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char			*buff;
	int				ret_read;
	static t_list	*stock[1025];

	buff = NULL;
	if (fd < 0)
		return (free_all(&stock[fd]), NULL);
	ret_read = BUFFER_SIZE;
	buff = malloc(sizeof(char) * BUFFER_SIZE);
	if (!buff)
		return (free_all(&stock[fd]), NULL);
	while (ret_read != 0 && !(find_nl_or_eof(&stock[fd], ret_read)))
	{
		ret_read = read_n_stock(fd, buff, &stock[fd]);
		if (ret_read < 0)
			return (free_all(&stock[fd]), free (buff), NULL);
	}
	free (buff);
	if (find_nl_or_eof(&stock[fd], ret_read))
		return (cpy_n_free(&stock[fd], get_len(&stock[fd])));
	return (free_all(&stock[fd]), NULL);
}
