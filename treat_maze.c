/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_maze.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/06 15:38:28 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/06 15:51:08 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemmin.h"
#include "libft.h"

static t_res		*init_res(void)
{
	t_res	*new;

	if ((new = (t_res *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->path = NULL;
	new->current = NULL;
	new->next = NULL;
	return (new);
}

static int			is_solution(t_mz *rooms)
{
	t_mz			*tmp;
	static int		last = 0;
	int				i;

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

t_connex			*copy_connex(t_connex *list)
{
	t_connex	*first;
	t_connex	*ptr;
	t_connex	*browse;

	if (list == NULL)
		return (NULL);
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

static t_connex		*make_start(t_mz *start)
{
	t_connex	*copy;

	start->flag = 1;
	start->path = 1;
	copy = copy_connex(start->list);
	return (copy);
}

t_res				*treat_maze(t_env *maze)
{
	t_res	*res;
	int		find;
	int		i;

	i = 2;
	find = 0;
	res = init_res();
	res->current = make_start(maze->start_ptr);
	while (!find)
	{
		if (is_solution(maze->rooms))
			error_lemmin();
		find = find_solution(maze, res, i);
		i++;
	}
	save_solution(res, maze);
	return (res);
}

