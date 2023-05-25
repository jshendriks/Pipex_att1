/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_child.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 14:10:55 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/25 17:38:40 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./processes.h"

static int	st_execute(t_px_vars *buc, int fdin, int rtnd)
{
	char	*val_cmnd;
	char	**cmnd_split;

	val_cmnd = px_find_valid_cmnpath(buc, 2);
	cmnd_split = px_split_xtr(val_cmnd, ' ');
	execve(val_cmnd, cmnd_split, (buc->env));
	px_free_split(cmnd_split);
	if (rtnd == 0 && fdin >= 0)
	{
		close(fdin);
		close((buc->p_fds)[1]);
	}
	// THIS probably doesn't return correct exitcode, try to find the right one
	perror("Execve() failed");
	exit(EXIT_FAILURE);
}

int	px_child(t_px_vars *buc)
{
	int	fdin;
	int	*p_fdin;
	int	rtnd;

	fdin = -2;
	p_fdin = &fdin;
	rtnd = px_swapfds_be(buc, p_fdin, 1);
	if (rtnd < 0)
	{
		perror("Swap function failed");
		return (1);
	}
	else
	{
		// either rtnd == 0 and swap went perfectly, 
		// or == 1 and one of the fd's is closed
		return (st_execute(buc, fdin, rtnd));	
	}
}
