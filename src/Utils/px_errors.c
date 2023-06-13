/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_errors.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 11:46:09 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/13 09:53:24 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./utils.h"

int	px_error(t_px_vars *buc, int errno, char *errmess)
{
	if (buc != NULL)
	{
		if (!(errmess))
			perror(errmess);
		else
			ft_putstr_fd(errmess, 2);
		if ((buc->paths) != NULL)
			px_free_split(buc->paths);
		free(buc);
		return (errno);
	}
	return (-1);
}

int	px_mainerror(t_px_vars *buc, int errno, char *errmess)
{
	if (buc != NULL)
	{
		if (!(errmess))
			perror(errmess);
		else
			ft_putstr_fd(errmess, 2);
		close((buc->p_fds)[0]);
		close((buc->p_fds)[1]);
		if ((buc->paths) != NULL)
			px_free_split(buc->paths);
		free(buc);
		return (errno);
	}
	return (-1);
}

void	px_swaperror(t_px_vars *buc, int rtnd)
{
	if (buc != NULL)
	{
		if (rtnd == -1)
			ft_putstr_fd("No such file\n", 2);
		else if (rtnd == 1)
			ft_putstr_fd("Permission denied\n", 2);
		else
			ft_putstr_fd("Swap function failed\n", 2);
		if ((buc->paths) != NULL)
			px_free_split(buc->paths);
		free(buc);
		exit(EXIT_FAILURE);
	}
}
