/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_split_xtr.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:14:18 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/25 16:28:46 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./utils.h"

char	**px_split_xtr(char const *s, char c)
{
	int		am_subs;
	char	**ptr_subs;

	if (s == NULL || (int)c == 39)
		return (NULL);
	if (ft_strlen(s) == 0)
	{
		ptr_subs = (char **)malloc(1 * sizeof(char *));
		if (ptr_subs != NULL)
		{
			ptr_subs[0] = NULL;
			return (ptr_subs);
		}
		return (NULL);
	}
	am_subs = px_am_subs(s, c);
	ptr_subs = (char **)malloc((am_subs + 1) * sizeof(char *));
	if (ptr_subs == NULL)
		return (NULL);
	if (px_fill_ptr_subs(s, c, ptr_subs, am_subs) == 0)
		return (NULL);
	return (ptr_subs);
}
