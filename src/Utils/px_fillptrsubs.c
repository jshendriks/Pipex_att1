/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_fillptrsubs.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:11:50 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/25 16:29:04 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./utils.h"

static int	st_free_extra(char **ptr_subs, int cnt_subs, int am_subs)
{
	int	k;

	k = 0;
	while (k < cnt_subs)
	{
		free(ptr_subs[k]);
		k++;
	}
	free(ptr_subs[am_subs]);
	free(ptr_subs);
	return (0);
}

static int	st_fillsub(int j, int i, int cnt_subs, t_pxsplitbuc *bucket)
{
	(bucket->subs)[cnt_subs] = (char *)malloc(j);
	if ((bucket->subs)[cnt_subs] == NULL)
		return (st_free_extra(bucket->subs, cnt_subs, bucket->amount_subs));
	ft_strlcpy((bucket->subs)[cnt_subs], ((bucket->str) + i), j);
	return (1);
}

static int	st_len_sub(char const *s, char del, int i, int j)
{
	while (*(s + i + j) != del && *(s + i + j))
		j++;
	return (j);
}

static int	st_fillsubs(int *i, int cnt_subs, t_pxsplitbuc *bucket, char c)
{
	int	j;

	if (*((bucket->str) + (*i)) != 39)
	{
		j = st_len_sub(bucket->str, c, *i, 0);
		if (st_fillsub(j + 1, *i, cnt_subs, bucket) == 0)
			return (0);
		(*i) += j;
	}
	else
	{
		j = st_len_sub(bucket->str, 39, *i, 1);
		if (st_fillsub(j, *i + 1, cnt_subs, bucket) == 0)
			return (0);
		(*i) += j;
	}
	return (1);
}

int	px_fill_ptr_subs(char const *s, char c, char **ptr_subs, int am_subs)
{
	int				i;
	int				cnt_subs;
	t_pxsplitbuc	*bucket;

	bucket = malloc(sizeof(t_pxsplitbuc));
	if (bucket == NULL)
		return (0);
	bucket->str = s;
	bucket->subs = ptr_subs;
	bucket->amount_subs = am_subs;
	i = 0;
	cnt_subs = 0;
	(bucket->subs)[(bucket->amount_subs)] = NULL;
	while (*(s + i) && cnt_subs < am_subs)
	{
		if (*(s + i) != c)
		{
			if (st_fillsubs(&i, cnt_subs, bucket, c) == 0)
				return (free(bucket), 0);
			cnt_subs++;
		}
		else
			i++;
	}
	return (free(bucket), 1);
}
