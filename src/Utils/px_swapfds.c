/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_swapfds.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:33:30 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/26 13:55:06 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./utils.h"

static int	st_fdswap_begin(t_px_vars *buc, int filefd)
{
	int	rtnd1;
	int	rtnd2;

	rtnd1 = dup2(filefd, 0);
	rtnd2 = dup2((buc->p_fds)[1], 1);
	if (rtnd1 == -1)
	{
		close(filefd);
		close(0);
		return (2);
	}
	if (rtnd2 == -1)
	{
		close(filefd);
		close((buc->p_fds)[1]);
		exit(EXIT_FAILURE);
	}
	return (0);
}

static int	st_fdswap_end(t_px_vars *buc, int filefd)
{
	int	rtnd1;
	int	rtnd2;

	rtnd1 = dup2(filefd, 1);
	rtnd2 = dup2((buc->p_fds)[0], 0);
	if (rtnd2 == -1)
	{
		close(0);
		close((buc->p_fds)[0]);
		return (2);
	}
	if (rtnd1 == -1)
	{
		close(filefd);
		close((buc->p_fds)[0]);
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	px_swapfds_be(t_px_vars *buc, int *p_filefd, int i)
{
	int	filefd;

	if (i != 1 && i != (buc->argcnt) - 1)
		return (-1);
	if (i == 1)
	{
		filefd = open((buc->args)[i], O_RDONLY);
		close((buc->p_fds)[0]);
	}
	else
	{
		filefd = open((buc->args)[i], O_WRONLY | O_CREAT, 0666);
		close((buc->p_fds)[1]);
	}
	*p_filefd = filefd;
	if (filefd == -1)
	{
		if (i == 1)
			close(0);
		else
			close(1);
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
