

#include "libft.h"
#include "get_next_line.h"

t_lx		*init_lex(void)
{
	t_lx	*new;

	if ((new = (t_lx *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->start = NULL;
	new->end = NULL;
	return (new);
}

int			check_buf(char *buf)
{
	int		i;

	i = 0;
	while (ft_isspace(buf[i]))
		i++;
	if (buf[i] == '\0')
		return (-1);
	if (buf[0] == '#' && buf[1] == '#' && (buf[2] != 's' || buf[2] != 'e'))
		return (0);
	return (1);
}

t_lex		*init_node(char *buf)
{
	t_lex	*new;

	if ((new = (t_lex *)malloc(sizeof(*new))) == NULL)
		return (NULL);
	new->str = ft_strdup(buf);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		add_to_list(t_lx *list, char *buf)
{
	t_lex	*node;

	node = init_node(buf);
	if (node == NULL)
		return ;
	if (list->first == NULL)
	{
		list->first = node;
		list->end = node;
	}
	else
	{
		list->end->next = node;
		node->prev = list->end;
		list->end = node;
	}
}

t_lx		*get_lex(void)
{
	char	*buf;
	t_lx	*list;
	int		ret;

	ret = 0;
	if ((list = init_lex()) == NULL)
		return (NULL);
	while ((ret = get_next_line(0, &buf)))
	{
		if (ret == -1)
			return (NULL);
		if (ret = check_buff(buf))
		{
			if (ret == -1)
				return (list);
			add_to_list(list, buf);
		}
		free(buf);
	}
	return (list);
}

int			main(void)
{
	t_lx	*lex;
	t_env	*maze;

	lex = get_lex();
	if (lex == NULL)
	{
		write(2, "ERROR\n", 6);
		return (0);
	}
	maze = get_maze(lex);
	treat_maze(maze);
	return (0);
}
