/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemmin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 17:18:46 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/04 18:37:21 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMMIN_H
# define LEMMIN_H

typedef struct		s_lex
{
	char				*str;
	struct s_lex		*next;
	struct s_lex		*prev;
}					t_lex;

typedef struct		s_lx
{
	t_lex				*start;
	t_lex				*end;
	t_lex				*save;
	t_lex				*save_end;
}					t_lx;

typedef struct		s_connex
{
	char				*name;
	struct s_connex		*next;
	struct s_connex		*prev;
}					t_connex;

typedef struct		s_mz
{
	char				*name;
	char				flag;
	char				start;
	char				end;
	int					path;
	t_connex			*list;
	struct s_mz			*next;
	struct s_mz			*prev;
}					t_mz;

typedef struct		s_ant
{
	int					nb;
	char				*room;
	struct s_ant		*next;
	struct s_ant		*prev;
}					t_ant;

typedef struct		s_env
{
	int					fourmiz;
	char				*start;
	t_mz				*start_ptr;
	char				*end;
	t_mz				*end_ptr;
	t_mz				*rooms;
	t_ant				*ants;
}					t_env;

t_lx		*get_lex(void);
void		add_to_list(t_lx *list, char *buf);
t_lx		*init_lex(void);
t_lex		*init_node(char *buf);
void		add_connex_to_room(t_mz *room, char *str, t_env *maze, int flag);

#endif /* !LEMMIN_H */
