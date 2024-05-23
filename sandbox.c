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

void	add_to_stock(t_list **lst, char c)
{
	t_list	*new;
	t_list	*temp;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->c = c;
	new->next = NULL;
	if (!(*lst))
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

int	ft_lstsize(t_list *lst)
{
	int		count;

	count = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char *	cpy_n_free(t_list **lst, char *line, int nb_chars)
{
	int	i;
	t_list	*tmp;
	t_list	*next;
	t_list *current;

	i = 0;
	line = malloc(sizeof(char) * (nb_chars));
	if (!line)
		return (0);
	while (i < nb_chars && *lst != NULL)
	{
		line[i] = (*lst)-> c;
		next = (*lst)->next;
		free(*lst);
		*lst = next;
		i++;
	}
	line[i] = 0;
	i = 0;
	tmp = *lst;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (line);
}

char *get_next_line(int fd)
{
		int				ret_read;
		char			*buff;
		char			*line;
		int				i;
		int				k;
		static t_list	*stock;
		int				nb_chars = 0;
		t_list			*current;

	if (BUFFER_SIZE < 1)
	{
		printf("BUFFER_SIZE error");
		return (NULL);
	}
	buff = malloc(BUFFER_SIZE);
	if (!buff)
		return (NULL);

	ret_read = BUFFER_SIZE;
		while(ret_read != 0)
		{
			current = stock;
			while (current != NULL)
			{
				nb_chars++;
				if (current->c == '\n' || ret_read < BUFFER_SIZE)
				{
					if (ret_read < BUFFER_SIZE)
						nb_chars = ft_lstsize(stock);
					return(cpy_n_free(&stock, line, nb_chars));
				}
				current = current->next;
			}
			nb_chars= 0;
			ret_read = read(fd, buff, BUFFER_SIZE);
			if (ret_read == -1)
			{
				printf("File couldn't READ: ");
				print_error();
				return (NULL);
			}
			k = 0;
			while (k < ret_read)
			{
				add_to_stock(&stock, buff[k]);
				k++;
			}
		}
		free(buff);
		cpy_n_free(&stock, line, nb_chars);
		return (line);
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
	printf("\nLINE: %s\n", line);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		printf("\nLINE: %s\n", line);
	}
	free(line);

	close(fd);
	return (0);
}

		//****************CHECK****************
/*		current = stock;
		if (current == NULL)
			printf("STOCK F****G EMPTY\n");
		printf("IN STOCK: ");
		while (current != NULL)
		{
			printf("%c", current->c);
			current = current->next;
		}
		printf("\n");*/
		//****************CHECK****************