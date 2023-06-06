/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_child.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 14:10:55 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/06 15:05:20 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./processes.h"

static void	st_putsplit_fd(char **split, int fd)
{
	int	i;

	if (split != NULL)
	{
		i = 0;
		while (split[i])
		{
			ft_putstr_fd(split[i], fd);
			write(fd, "\n", 1);
			i++;
		}
	}
	else
		ft_putstr_fd("NULL", fd);
}

static int	st_first_execute(t_px_vars *buc, int fdin, int rtnd)
{
	char	*val_cmnd;
	char	**cmnd_split;

	val_cmnd = px_find_valid_cmnpath(buc, 2);
	cmnd_split = px_split_xtr((buc->args)[2], ' ');
	execve(val_cmnd, cmnd_split, (buc->env));
	px_free_split(cmnd_split);
	if (rtnd == 0 && fdin >= 0)
	{
		close(fdin);
		close((buc->p_fds)[1]);
	}
	return (px_error(buc, 127, "Command not found"));
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
		exit(st_first_execute(buc, fdin, rtnd));
}

static int	st_second_execute(t_px_vars *buc, int fdout, int rtnd)
{
	char	*val_cmnd;
	char	**cmnd_split;

	val_cmnd = px_find_valid_cmnpath(buc, 3);
	cmnd_split = px_split_xtr((buc->args)[3], ' ');
	execve(val_cmnd, cmnd_split, (buc->env));
	px_free_split(cmnd_split);
	if (rtnd == 0 && fdout >= 0)
	{
		close(fdout);
		close((buc->p_fds)[0]);
	}
	return (px_error(buc, 127, "Command not found"));
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
		exit(st_second_execute(buc, fdout, rtnd));
}
