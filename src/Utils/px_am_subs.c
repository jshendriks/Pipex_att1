/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_am_subs.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:11:25 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/25 16:29:21 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./utils.h"

static int	st_cnt_cinsub(char const *s, char c, int *i)
{
	int	j;
	int	cnt;

	j = *i + 1;
	cnt = 0;
	while (*(s + j) || j >= 0)
	{
		if (*(s + j) == c)
			cnt++;
		else if (*(s + j) == 39)
		{
			*i = j;
			j = -2;
		}
		j++;
	}
	return (cnt);
}

static int	st_del_subs(char const *s, char c)
{
	int	i;
	int	cnt;

	if (s != NULL)
	{
		i = 0;
		cnt = 0;
		while (*(s + i))
		{
			if (*(s + i) == 39)
				cnt += st_cnt_cinsub(s, c, &i);
			i++;
		}
		return (cnt);
	}
	return (0);
}

int	px_am_subs(char const *s, char c)
{
	int	i;
	int	j;
	int	cnt;
	int	del;

	i = 0;
	cnt = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			j = 0;
			while (*(s + i + j) != c && *(s + i + j))
				j++;
			cnt++;
			i = i + j;
		}
		else
			i++;
	}
	del = st_del_subs(s, c);
	return (cnt - del);
}
