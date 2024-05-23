#include "get_next_line.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int	ft_strchr(const char *s, char c)
{
	char	*tmp_s;
	int		count;

	count = 0;
	tmp_s = (char *)s;
	while (*tmp_s)
	{
		count++;
		if (*tmp_s == c)
			return (count - 1);
		tmp_s++;
	}
	return (count);
}

void	print_error()
{
	if (errno != 0 )
		printf("ERROR: %s", strerror(errno));
}

void	add_to_stock(t_list **lst, char c)
{
	t_list	*new;
	t_list	*temp;

	if (!(*lst))
		printf("STOCK EMPTY\n");
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

int	free_stock(t_list **lst, int nb_chars)
{
	int	i;
	t_list	*tmp;
	t_list	*next;

	i = 0;
		printf("Deleting from list: ");
		while (i < nb_chars && *lst != NULL)
		{
			printf("%c", (*lst)->c);
			printf("|");
			next = (*lst)->next;
			free(*lst);
			*lst = next;
			i++;
		}
		printf("\n");

	i = 0;
	tmp = *lst;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int	get_next_line(int fd, char **line)
{
		int				ret_read;
		char			*buff;
		int				i;
		int				k;
		static t_list	*stock;
		static int		nb_chars = 0;
		t_list			*current;

	printf("nb_chars = %d\n", nb_chars);
//1. check if BUFFER_SIZE is def and not 0
	if (BUFFER_SIZE < 1)
	{
		printf("BUFFER_SIZE error");
		return (1);
	}
//2. malloc my buff with BUFFER_SIZE
	buff = malloc(BUFFER_SIZE);
	if (!buff)
		return (1);
//3. read and store BUFFER_SIZE nb of bytes in buff.
	ret_read = -1;
	i = BUFFER_SIZE;
	while (i == BUFFER_SIZE && ret_read != 0)
	{
		ret_read = read(fd, buff, BUFFER_SIZE);
		printf("ret de READ = %d\n", ret_read);
		if (ret_read == -1)
		{
				printf("File couldn't READ: ");
				print_error();
				return (1);
		}
	//4. check buff for \n
		i = ft_strchr(buff, '\n');
		nb_chars += i;
/*		printf("**********************\n");
		printf("buff size : %d\nchars to newline (10 = no NL): %d\ntotal nb_chars: %d\n", BUFFER_SIZE, i, nb_chars);
		printf("**********************\n");*/
		k = 0;
	//5. write buff in stock
		while (k < ret_read)
		{
			add_to_stock(&stock, buff[k]);
			k++;
		}
		// ****************CHECK****************
		current = stock;
		if (current == NULL)
			printf("STOCK F****G EMPTY");
		printf("IN STOCK: ");
		while (current != NULL)
		{
			printf("%c", current->c);
			current = current->next;
		}
		printf("\n");
		// ****************CHECK****************
	//	- IF \n => write stock in line + del what has been written from stock + return
		if (i < BUFFER_SIZE)
		{
			printf("I got a newline\n");
			//	write stock in line until /n
			*line = malloc(sizeof(char) * (nb_chars + 1));
			k = 0;
/*			**line = 'A';
			(*line)++;
			**line = 'B';
			(*line)--;*/
			current = stock;
			while (k < nb_chars)
			{
				(*line)[k] = current->c;
				current = current->next;
				k++;
			}
			(*line)[k] = 0;
			printf("nb_chars = %d\n", nb_chars);
			printf("Line written: %s\n", *line);
		//	del what has been written from stock
			// ****************CHECK****************
			current = stock;
			if (current == NULL)
				printf("STOCK F****G EMPTY");
			printf("IN STOCK: ");
			while (current != NULL)
			{
				printf("%c", current->c);
				current = current->next;
			}
			printf("\n");
			// ****************CHECK****************
			nb_chars = free_stock(&stock, nb_chars + 1);
			// ****************CHECK****************
			current = stock;
			if (current == NULL)
				printf("STOCK F****G EMPTY");
			printf("Still remaining: ");
			while (current != NULL)
			{
				printf("%c", current->c);
				printf("|");
				current = current->next;
			}
			// ****************CHECK****************
		// free buff malloc
			free(buff);
		//	return
			if (i == 0)
				return (0);
			else
				return (1);
		}
	}
}

int	main(void)
{
	int		fd;
	int		ret;
	char	**line;


	ret = 0;
	errno = 0;
	line = malloc(sizeof(char *));
//Open file
	fd = open("myExample.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("File couldn't OPEN: ");
		print_error();
		return (1);
	}
	ret = get_next_line(fd, line);
	printf("\nRet de get_next_line: %d\n", ret);
	printf("\n**********************************************\n\n");
	ret = get_next_line(fd, line);
	printf("\nRet de get_next_line: %d\n", ret);
	printf("\n**********************************************\n\n");
	ret = get_next_line(fd, line);
	printf("\nRet de get_next_line: %d\n", ret);

	close(fd);

	return (0);
}
