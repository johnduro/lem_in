/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemmin.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/03 17:18:46 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/06 19:38:05 by mle-roy          ###   ########.fr       */
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
	char				move;
	char				finish;
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

typedef struct		s_room
{
	char				*name;
	char				start;
	char				end;
	struct s_room		*next;
	struct s_room		*prev;
}					t_room;

typedef struct		s_res
{
	t_room				*path;
	t_connex			*current;
	t_connex			*next;
}					t_res;

t_lx		*get_lex(void);
void		add_to_list(t_lx *list, char *buf);
t_lx		*init_lex(void);
t_lex		*init_node(char *buf);
void		add_connex_to_room(t_mz *room, char *str, t_env *maze, int flag);
int			error_lemmin(void);
t_env		*get_maze(t_lx *lex);
void		add_start_end(t_env *maze, t_lex *node);
void		add_to_mz(t_env *maze, t_mz *room);
void		add_room(t_env *maze, t_lex *lex);
t_mz		*init_room(char *str);
void		add_connex(t_env *maze, t_lex *lex);
t_connex	*init_connex(char *str);
void		make_ants(t_env *maze);
int			is_valid_char_lem(char c);
t_res		*treat_maze(t_env *maze);
t_connex	*copy_connex(t_connex *list);
int			find_solution(t_env *maze, t_res *res, int i);
void		save_solution(t_res *res, t_env *maze);
void		print_result(t_res *res, t_env *maze, t_lx *lex);
void		move_ants(t_res *res, t_env *maze);

void		print_room(t_mz *room); //nononoonnononon
void		print_maze(t_env *maze); //nonononoononon
void		print_lex(t_lx *lex); //nononoonononon
void		debug_solution(t_res *res, t_env *maze); //nonononoon
void		debug_treat_maze(t_env *maze, int i); //nononoononon

#endif /* !LEMMIN_H */
