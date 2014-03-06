/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/06 15:37:24 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/06 19:40:16 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lemmin.h"
#include "libft.h"

int			error_lemmin(void)
{
	write(2, "ERROR\n", 6);
	exit(0);
}

t_connex		*init_connex(char *str)
{
	t_connex	*new;

	if ((new = (t_connex *)malloc(sizeof(*new))) == NULL)
		ft_exit("malloc", 1);
	new->name = ft_strdup(str);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

int			main(void)
{
	t_lx	*lex;
	t_env	*maze;
	t_res	*res;

	lex = get_lex();
	if (lex == NULL || lex->start == NULL)
		error_lemmin();
//	print_lex(lex); //nononononon
	maze = get_maze(lex);
	if (maze == NULL)
		error_lemmin();
//	print_maze(maze); //nonononono
	res = treat_maze(maze);
//	debug_solution(res, maze);
	print_result(res, maze, lex);
	return (0);
}
