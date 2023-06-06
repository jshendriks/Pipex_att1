/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_mama_children.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 12:58:49 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/06 10:36:08 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "creating.h"

static int	st_error(t_px_vars *buc, int errno, char *errmess)
{
	if (buc != NULL && errmess != NULL)
	{
		perror(errmess);
		close((buc->p_fds)[0]);
		close((buc->p_fds)[1]);
		if ((buc->paths) != NULL)
			px_free_split(buc->paths);
		free(buc);
		return (errno);
	}
	return (-1);
}

void	px_mama_children(t_px_vars *var_buc, int *p_fd)
{
	int	r_id1;

	r_id1 = fork();
	if (r_id1 == -1)
		exit(st_error(var_buc, 1, "First fork() failed"));
	if (r_id1 == 0)
		px_first_child(var_buc);
	else
		px_first_parent(var_buc, p_fd);
}
