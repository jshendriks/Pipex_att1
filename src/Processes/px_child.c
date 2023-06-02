/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_child.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 14:10:55 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/02 15:04:17 by jhendrik      ########   odam.nl         */
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
	else
		ft_putstr_fd("NULL", fd);
} 

static int	st_error(t_px_vars *buc, int errno, char *errmess)
{
	if (buc != NULL && errmess != NULL)
	{
		perror(errmess);
		if ((buc->paths) != NULL)
			px_free_split(buc->paths);
		free(buc);
		return (errno);
	}
	return (-1);
}

static int	st_first_execute(t_px_vars *buc, int fdin, int rtnd)
{
	char	*val_cmnd;
	char	**cmnd_split;

	val_cmnd = px_find_valid_cmnpath(buc, 2);
	cmnd_split = px_split_xtr((buc->args)[2], ' ');
	ft_putstr_fd(val_cmnd, 2);
	write(2, "\n", 1);
	st_putsplit_fd(cmnd_split, 2);
	execve(val_cmnd, cmnd_split, (buc->env));
	px_free_split(cmnd_split);
	if (rtnd == 0 && fdin >= 0)
	{
		close(fdin);
		close((buc->p_fds)[1]);
	}
	return (st_error(buc, 127, "Command not found"));
}

int	px_first_child(t_px_vars *buc)
{
	int	fdin;
	int	*p_fdin;
	int	rtnd;

	fdin = -2;
	p_fdin = &fdin;
	rtnd = px_swapfds_be(buc, p_fdin, 1);
	ft_putstr_fd("First child \n", 2);
	if (rtnd != 0)
	{
		perror("Swap function failed");
		exit(EXIT_FAILURE);
	}
	else
		exit(st_first_execute(buc, fdin, rtnd));	
}

static int	st_second_execute(t_px_vars *buc, int fdout, int rtnd)
{
	char	*val_cmnd;
	char	**cmnd_split;

	val_cmnd = px_find_valid_cmnpath(buc, 3);
	cmnd_split = px_split_xtr((buc->args)[3], ' ');
	ft_putstr_fd(val_cmnd, 2);
	write(2, "\n", 1);
	st_putsplit_fd(cmnd_split, 2);
	execve(val_cmnd, cmnd_split, (buc->env));
	px_free_split(cmnd_split);
	if (rtnd == 0 && fdout >= 0)
	{
		close(fdout);
		close((buc->p_fds)[0]);
	}
	return (st_error(buc, 127, "Command not found"));
}

int	px_sec_child(t_px_vars *buc)
{
	int	fdout;
	int	*p_fdout;
	int	rtnd;

	fdout = -2;
	p_fdout = &fdout;
	rtnd = px_swapfds_be(buc, p_fdout, 4);
	ft_putstr_fd("Second child \n", 2);
	if (rtnd != 0)
	{
		perror("Swap function failed");
		exit(EXIT_FAILURE);
	}
	else
		exit(st_second_execute(buc, fdout, rtnd));
}
