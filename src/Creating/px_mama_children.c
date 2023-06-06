/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_mama_children.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 12:58:49 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/06 14:33:02 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "creating.h"

void	px_mama_children(t_px_vars *var_buc)
{
	int	r_id1;

	r_id1 = fork();
	if (r_id1 == -1)
		exit(px_mainerror(var_buc, 1, "First fork() failed"));
	if (r_id1 == 0)
		px_first_child(var_buc);
	else
		px_first_parent(var_buc);
}
