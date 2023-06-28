/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_child.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 14:10:55 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/28 14:08:57 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./processes.h"

static int	st_first_execute(t_px_vars *buc)
{
	char	*val_cmnd;
	char	**cmnd_split;
	int		found;

	found = 0;
	val_cmnd = px_find_valid_cmnpath(buc, 2, &found);
	cmnd_split = px_split_xtr((buc->args)[2], ' ');
	execve(val_cmnd, cmnd_split, (buc->env));
	px_free_split(cmnd_split);
	if (found == 1)
		return (px_error(buc, 126, "Permission denied (1)\n"));
	else
		return (px_error(buc, 127, "Command not found (1)\n"));
}

void	px_first_child(t_px_vars *buc)
{
	int	fdin;
	int	*p_fdin;
	int	rtnd;

	fdin = -2;
	p_fdin = &fdin;
	rtnd = px_swapfds_be(buc, p_fdin, 1);
	if (rtnd != 0)
		px_swaperror(buc, rtnd);
	else
		exit(st_first_execute(buc));
}

static int	st_second_execute(t_px_vars *buc)
{
	char	*val_cmnd;
	char	**cmnd_split;
	int		found;

	found = 0;
	val_cmnd = px_find_valid_cmnpath(buc, 3, &found);
	cmnd_split = px_split_xtr((buc->args)[3], ' ');
	execve(val_cmnd, cmnd_split, (buc->env));
	px_free_split(cmnd_split);
	if (found == 1)
		return (px_error(buc, 126, "Permission denied (2)\n"));
	return (px_error(buc, 127, "Command not found (2)\n"));
}

void	px_sec_child(t_px_vars *buc)
{
	int	fdout;
	int	*p_fdout;
	int	rtnd;

	fdout = -2;
	p_fdout = &fdout;
	rtnd = px_swapfds_be(buc, p_fdout, 4);
	if (rtnd != 0)
		px_swaperror(buc, rtnd);
	else
		exit(st_second_execute(buc));
}
