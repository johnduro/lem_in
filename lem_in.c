/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 17:29:18 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/04 18:50:45 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemmin.h"
#include "libft.h"
#include "get_next_line.h"

#include <stdio.h> //nononon

int			error_lemmin(void)
{
	write(2, "ERROR\n", 6);
	exit(0);
}

void		print_lex(t_lx *lex)
{
	t_lex	*browse;

	browse = lex->start;
	while (browse)
	{
		printf("LEX=%s\n", browse->str);
		browse = browse->next;
	}
}

int			how_many_word(const char *str)
{
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]) && (i == 0 || ft_isspace(str[i - 1])))
			ret++;
		i++;
	}
	return (ret);
}


int			how_many_dash(const char *str)
{
	int		ret;

	ret = 0;
	while(*str)
	{
		if (*str == '-')
			ret++;
		str++;
	}
	return (ret);
}


t_env		*init_maze(t_lex *first)
{
	t_env	*new;
	int		i;

	i = 0;
	if ((new = (t_env *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	if (how_many_word(first->str) > 1)
		error_lemmin();
	while ((first->str)[i])
	{
		if (!ft_isdigit((first->str)[i]))
			error_lemmin();
		i++;
	}
	new->fourmiz = ft_atoi(first->str);
	new->start = NULL;
	new->end = NULL;
	new->rooms = NULL;
	new->ants = NULL;
	return (new);
}

t_mz		*init_room(char *str)
{
	t_mz	*new;

	if (str[0] == 'L' || str[0] == '#')
		error_lemmin();
	if ((new = (t_mz *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->name = ft_strdup(str);
	new->flag = 0;
	new->start = 0;
	new->end = 0;
	new->path = 0;
	new->list = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		add_to_mz(t_env *maze, t_mz *room)
{
	t_mz	*browse;

	if (maze->rooms == NULL)
		maze->rooms = room;
	else
	{
		browse = maze->rooms;
		while (browse->next)
			browse = browse->next;
		browse->next = room;
		room->prev = browse;
	}
}

void		add_start_end(t_env *maze, t_lex *node)
{
	char	**tab;
	t_mz	*room;

	if (node == NULL || node->str == NULL || (node->str)[0] == '\0')
		error_lemmin();
	tab = ft_strsplitspace(node->str);
	room = init_room(tab[0]);
	if (node->prev && !ft_strcmp(node->prev->str, "##start"))
	{
		room->start = 1;
		maze->start_ptr = room;
		maze->start = ft_strdup(tab[0]);
	}
	else if (node->prev && !ft_strcmp(node->prev->str, "##end"))
	{
		room->end = 1;
		maze->end_ptr = room;
		maze->end = ft_strdup(tab[0]);
	}
	add_to_mz(maze, room);
	ft_tabfree(&tab);
}

void		add_room(t_env *maze, t_lex *lex)
{
	char	**tab;
	t_mz	*room;

	tab = ft_strsplitspace(lex->str);
	room = init_room(tab[0]);
	add_to_mz(maze, room);
	ft_tabfree(&tab);
}

t_connex	*init_connex(char *str)
{
	t_connex	*new;

	if ((new = (t_connex *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->name = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void		add_back_connex(char *name, char *str, t_env *maze)
{
	t_mz	*room;

	room = maze->rooms;
	while (room)
	{
		if (!ft_strcmp(str, room->name))
		{
			add_connex_to_room(room, name, maze, 0);
			return ;
		}
		room = room->next;
	}
	error_lemmin();
}

void		add_connex_to_room(t_mz *room, char *str, t_env *maze, int flag)
{
	t_connex	*connex;
	t_connex	*tmp;

	connex = init_connex(str);
	if (room->list == NULL)
		room->list = connex;
	else
	{
		tmp = room->list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = connex;
		connex->prev = tmp;
	}
	if (flag == 1)
		add_back_connex(room->name, str,  maze);
}

void		add_connex(t_env *maze, t_lex *lex)
{
	t_mz	*room;
	char	**tab;

	if (maze->rooms == NULL)
		error_lemmin();
	if ((how_many_dash(lex->str) != 1))
		error_lemmin();
	tab = ft_strsplit(lex->str, '-');
	room = maze->rooms;
	while (room)
	{
		if (!ft_strcmp(room->name, tab[0]))
		{
			add_connex_to_room(room, tab[1], maze, 1);
			ft_tabfree(&tab);
			return ;
		}
		room = room->next;
	}
	error_lemmin();
}

void		add_ant(t_env *maze, int ant)
{
	t_ant	*new;
	t_ant	*tmp;

	if ((new = (t_ant *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->nb = ant;
	new->room = NULL;
	new->next = NULL;
	new->prev = NULL;
	if (maze->ants == NULL)
		maze->ants = new;
	else
	{
		tmp = maze->ants;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
}

void		make_ants(t_env *maze)
{
	int		i;

	i = 1;
	while (i <= maze->fourmiz)
	{
		add_ant(maze, i);
		i++;
	}
}

t_env		*get_maze(t_lx *lex)
{
	t_env	*maze;
	t_lex	*browse;

	maze = init_maze(lex->start);
	browse = lex->start->next;
	while (browse)
	{
		if ((browse->str)[0] == '#')
		{
			browse = browse->next;
			add_start_end(maze, browse);
		}
		else if ((how_many_word(browse->str)) == 3)
			add_room(maze, browse);
		else if ((how_many_word(browse->str)) == 1)
			add_connex(maze, browse);
		browse = browse->next;
	}
	make_ants(maze);
	return (maze);
}

void		print_room(t_mz *room)
{
	t_connex	*tmp;

	printf("name=%s\n", room->name);
	printf("flag=%d\n", room->flag);
	printf("start=%d\n", room->start);
	printf("end=%d\n", room->end);
	printf("path=%d\n", room->path);
	tmp = room->list;
	printf("CONNEX:\n");
	while (tmp)
	{
		printf("connex to %s\n", tmp->name);
		tmp = tmp->next;
	}
}

void		print_maze(t_env *maze)
{
	t_mz	*rooms;
	t_ant	*ants;

	printf("fourmiz=%d\n", maze->fourmiz);
	printf("***\nstart=%s\n", maze->start);
	if (maze->start_ptr)
	{
		printf("\nSTART-ROOM\n");
		print_room(maze->start_ptr);
	}
	printf("***\nend=%s\n", maze->end);
	if (maze->end_ptr)
	{
		printf("\nEND-ROOM\n");
		print_room(maze->end_ptr);
	}
	rooms = maze->rooms;
	printf("***\nROOMS=\n");
	while (rooms)
	{
		printf("\n");
		print_room(rooms);
		rooms = rooms->next;
	}
	ants = maze->ants;
	printf("***\nANTS=\n");
	while (ants)
	{
		printf("NB=%d\nROOM=%s\n", ants->nb, ants->room);
		ants = ants->next;
	}
}

t_res		*init_res(void)
{
	t_res	*new;

	if ((new = (t_res *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->path = NULL;
	new->current = NULL;
	new->next = NULL;
	return (new);
}

t_connex		*copy_connex(t_connex *list)
{
	t_connex	*first;
	t_connex	*ptr;
	t_connex	*browse;

	first = init_connex(list->name);
	browse = list->next;
	ptr = first;
	while (browse)
	{
		ptr->next = init_connex(browse->name);
		ptr = ptr->next;
		browse = browse->next;
	}
	return (first);
}

t_connex		*make_start(t_mz *start)
{
	t_connex	*copy;

	start->flag = 1;
	start->path = 1;
	copy = copy_connex(start->list);
	return (copy);
}

void		cat_connex(t_res *res, t_mz *room)
{
	t_connex	*connex;

	if (res->next == NULL)
		res->next = copy_connex(room->list);
	else
	{
		connex = res->next;
		while (connex->next)
			connex = connex->next;
		connex->next = copy_connex(room->list);
	}
}

int			find_solution(t_mz *maze, t_res *res)
{
	t_connex		*connex;
	t_mz			*ptr;
	int				ret;
	static int		i = 2;

	ret = 0;
	connex = res->current;
	while (connex)
	{
		ptr = maze->rooms;
		while (ptr)
		{
			if (!ft_strcmp(ptr->name, connex->name) && ptr->flag == 0)
			{
				if (ptr->end == 1)
					ret = 1;
				cat_connex(res, ptr);
				ptr->flag = 1;
				ptr->path = i;
			}
			ptr = ptr->next;
		}
		connex = connex->next;
	}
	manage_res(res); //free et switch des lists a faire
	i++;
	return (ret);
}

int			is_solution(t_mz *rooms)
{
	t_mz		*tmp;
	static int	last = 0;
	int			i;

	i = 0;
	tmp = rooms;
	while (tmp)
	{
		if (tmp->flag == 0)
			i++;
		tmp = tmp->next;
	}
	if (i == last)
		return (1);
	last = i;
	return (0);
}

t_res		*treat_maze(t_env *maze)
{
	t_res	*res;
//	t_mz	*room;
	int		find;

	find = 0;
	res = init_res();
	res->current = make_start(maze->start_ptr);
//	room = maze->start_ptr;
	while (!find)
	{
		if (is_solution(maze->rooms))
			error_lemmin();
		find = find_solution(maze, res);
	}
	save_solution(res); // a faire
	return (res);
}

int			main(void)
{
	t_lx	*lex;
	t_env	*maze;
	t_res	*res;

	lex = get_lex();
	if (lex == NULL)
		error_lemmin();
	print_lex(lex); //nononononon
	maze = get_maze(lex);
	print_maze(maze); //nonononono
	res = treat_maze(maze);
//	print_result(res, maze, lex);
	return (0);
}
