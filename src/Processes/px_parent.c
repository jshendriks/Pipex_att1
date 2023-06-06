/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_parent.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 15:12:05 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/06 10:32:54 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./processes.h"

/* static void	st_putsplit_fd(char **split, int fd)
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
} */

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

void	px_first_parent(t_px_vars *buc, int *p_fd)
{
	int	r_id2;

	r_id2 = fork();
	if (r_id2 == -1)
		exit(st_error(buc, 1, "Second fork() failed"));
	if (r_id2 == 0)
		px_sec_child(buc);
	else
		px_sec_parent(buc, p_fd, r_id2);
}

void	px_sec_parent(t_px_vars *buc, int *p_fd, int r_id2)
{
	int	status;
	int	tmp;

	status = 0;
	tmp = 0;
	close((buc->p_fds)[0]);
	close((buc->p_fds)[1]);
	close(p_fd[1]);
	close(p_fd[0]);
	waitpid(r_id2, &status, 0);
	waitpid(0, NULL, 0);
	if ((buc->paths) != NULL)
		px_free_split(buc->paths);
	free(buc);
	if (WIFEXITED(status))
	{
		exit(WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
	else
		exit(EXIT_SUCCESS);
}
