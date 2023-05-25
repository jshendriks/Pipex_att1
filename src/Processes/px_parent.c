/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_parent.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 15:12:05 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/25 18:36:08 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./processes.h"

static void	st_putsplit_fd(char **split, int fd)
{
	int	i;

	if (split != NULL)
	{
		i = 0;
		while(split[i])
		{
			ft_putstr_fd(split[i], fd);
			write(fd, "\n", 1);
			i++;
		}
	}
}

static int	st_execute(t_px_vars *buc, int fdout, int rtnd, int exst)
{
	char	*val_cmnd;
	char	**cmnd_split;

	val_cmnd = px_find_valid_cmnpath(buc, 3);
	ft_putstr_fd(val_cmnd, 2);
	write(2, "\n", 1);
	cmnd_split = px_split_xtr((buc->args)[3], ' ');
	st_putsplit_fd(cmnd_split, 2);
	execve(val_cmnd, cmnd_split, (buc->env));
	px_free_split(cmnd_split);
	if (rtnd == 0 && fdout >= 0)
	{
		close(fdout);
		close((buc->p_fds)[0]);
	}
	// THIS probably doesn't return correct exitcode, try to find the right one
	perror("Execve() failed");
	exit(exst);
}

int	px_parent(t_px_vars *buc)
{
	int	fdout;
	int	*p_fdout;
	int	rtnd;
	int	status;

	// HOW can you use status to return correct exitcode??
	status = 0;
	waitpid(-1, &status, 0);
	fdout = -2;
	p_fdout = &fdout;
	rtnd = px_swapfds_be(buc, p_fdout, 4);
	if (rtnd < 0)
	{
		perror("Swapping fds failed");
		return (1);
	}
	else
	{
		if (WIFEXITED(status))
			return (st_execute(buc, fdout, rtnd, WEXITSTATUS(status)));
		else
			return (st_execute(buc, fdout, rtnd, 1));
	}
}
