/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_free_split.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:25:14 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/25 16:28:28 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./utils.h"

/*This file contains the function px_free_split(char **ptr_subs)
 * px_free_split(char **ptr_subs):
		This function frees the entries in the double pointer
		by iterating through the double pointer.
		Then it frees the double pointer.
		This function will loop infinitely if ptr_subs[k]
		is not NULL for some k.
 */

void	px_free_split(char **ptr_subs)
{
	int	k;

	if (ptr_subs != NULL)
	{
		k = 0;
		while (ptr_subs[k] != NULL)
		{
			free(ptr_subs[k]);
			k++;
		}
		free(ptr_subs);
	}
}
