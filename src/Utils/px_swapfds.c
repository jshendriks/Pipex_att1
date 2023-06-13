/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_swapfds.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:33:30 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/13 09:50:04 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./utils.h"

static int	st_fdswap_begin(t_px_vars *buc, int filefd)
{
	int	rtnd1;
	int	rtnd2;

	rtnd1 = dup2(filefd, 0);
	rtnd2 = dup2((buc->p_fds)[1], 1);
	close(filefd);
	if (rtnd1 == -1 || rtnd2 == -1)
	{
		close((buc->p_fds)[1]);
		return (2);
	}
	return (0);
}

static int	st_fdswap_end(t_px_vars *buc, int filefd)
{
	int	rtnd1;
	int	rtnd2;

	rtnd1 = dup2(filefd, 1);
	rtnd2 = dup2((buc->p_fds)[0], 0);
	close(filefd);
	if (rtnd2 == -1 || rtnd1 == -1)
	{
		close((buc->p_fds)[0]);
		return (2);
	}
	return (0);
}

static int	st_give_fd(t_px_vars *buc, int i)
{
	int	filefd;

	if (i == 1)
	{
		filefd = open((buc->args)[i], O_RDONLY);
		close((buc->p_fds)[0]);
	}
	else
	{
		filefd = open((buc->args)[i], O_WRONLY | O_TRUNC);
		close((buc->p_fds)[1]);
	}
	return (filefd);
}

int	px_swapfds_be(t_px_vars *buc, int *p_filefd, int i)
{
	int	filefd;

	if (i != 1 && i != (buc->argcnt) - 1)
		return (-2);
	if (access((buc->args)[i], F_OK) == -1)
		return (-1);
	filefd = st_give_fd(buc, i);
	*p_filefd = filefd;
	if (filefd == -1)
	{
		if (i == 1)
			close((buc->p_fds)[1]);
		else
			close((buc->p_fds)[0]);
		return (1);
	}
	else
	{
		if (i == 1)
			return (st_fdswap_begin(buc, filefd));
		else
			return (st_fdswap_end(buc, filefd));
	}
}
