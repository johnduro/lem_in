/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 18:16:58 by mle-roy           #+#    #+#             */
/*   Updated: 2014/03/06 19:26:22 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include "lemmin.h"

static int			is_start_end(char *str)
{
	char			*buf;
	static int		start = 0;
	static int		end = 0;

	buf = ft_strtrim(str);
	if (!ft_strcmp(buf, "##start"))
	{
		free(buf);
		if (start == 1)
			return (0);
		start = 1;
		return (1);
	}
	else if (!ft_strcmp(buf, "##end"))
	{
		free(buf);
		if (end == 1)
			return (0);
		end = 1;
		return (1);
	}
	free(buf);
	return (0);
}

static int			is_valid_lem(char *buf)
{
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	while (buf[i])
	{
		if (is_valid_char_lem(buf[i]) && (i == 0 || ft_isspace(buf[i - 1])))
			flag++;
		i++;
	}
	if (flag > 3)
		return (0);
	else
		return (1);
}

static int			check_buf(char *buf)
{
	int		i;

	i = 0;
	while (ft_isspace(buf[i]))
		i++;
	if (buf[i] == '\0')
		return (-1);
	if (buf[i] == '#')
	{
		if (is_start_end(buf))
			return (1);
		return (0);
	}
	if (!is_valid_lem(buf))
		return (-1);
	return (1);
}

void				add_to_save(t_lx *lex, char *buf)
{
	t_lex		*node;

	node = init_node(buf);
	if (lex->save == NULL)
	{
		lex->save = node;
		lex->save_end = node;
	}
	else
	{
		lex->save_end->next = node;
		node->prev = lex->save_end;
		lex->save_end = node;
	}
}

t_lx				*get_lex(void)
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
		add_to_save(list, buf);
		if ((ret = check_buf(buf)))
		{
			if (ret == -1)
				return (list);
			add_to_list(list, buf);
		}
		free(buf);
	}
	return (list);
}
