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

size_t ft_lstsize(t_list *lst)
{
	size_t size = 0;
	while (lst) {
		size++;
		lst = lst->next;
	}
	return size;
}

t_list *check_stock(t_list *stock, int ret_read)
{
	t_list *current = stock;
	while (current) {
		if (current->c == '\n' || ret_read < BUFFER_SIZE) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

int append_to_stock(int fd, t_list **stock)
{
	char buffer[BUFFER_SIZE + 1];
	int ret_read;

	ret_read = read(fd, buffer, BUFFER_SIZE);
	if (ret_read <= 0) {
		return ret_read;
	}

	buffer[ret_read] = '\0';
	for (int i = 0; i < ret_read; i++) {
		t_list *new_node = malloc(sizeof(t_list));
		if (!new_node) {
			return -1;
		}
		new_node->c = buffer[i];
		new_node->next = NULL;
		if (!*stock) {
			*stock = new_node;
		} else {
			t_list *last = *stock;
			while (last->next) {
				last = last->next;
			}
			last->next = new_node;
		}
	}
	return ret_read;
}

size_t find_line_length(t_list *stock)
{
	size_t length = 0;
	t_list *current = stock;

	while (current && current->c != '\n') {
		length++;
		current = current->next;
	}
	if (current && current->c == '\n') {
		length++;
	}
	return length;
}

char *cpy_n_free(t_list **stock, size_t nb_chars)
{
	t_list *temp;
	char *line;
	size_t i;

	if (!(line = malloc(nb_chars + 1))) {
		return NULL;
	}
	i = 0;
	while (i < nb_chars && *stock) {
		line[i++] = (*stock)->c;
		temp = *stock;
		*stock = (*stock)->next;
		free(temp);
	}
	line[i] = '\0';
	return line;
}

char *get_next_line(int fd)
{
	static t_list *stock = NULL;
	int ret_read;
	size_t line_length;

	if (fd < 0 || BUFFER_SIZE <= 0) {
		return NULL;
	}
	ret_read = 1;
	while (ret_read > 0)
	{
		ret_read = append_to_stock(fd, &stock);
		if (check_stock(stock, ret_read)) {
			break;
		}
	}

	if (ret_read < 0) {
		return NULL;
	}

	if (!stock) {
		return NULL;
	}

	line_length = find_line_length(stock);
	return cpy_n_free(&stock, line_length);
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
