/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 14:12:49 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/07/03 13:53:34 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./src.h"

static t_px_vars	*st_mvars(int argc, char *argv[], char *envp[], int *pfd)
{
	char		*env_path;
	char		**envpaths;
	t_px_vars	*var_buc;

	env_path = px_find_envvar(envp, "PATH");
	envpaths = px_splitpaths(env_path);
	var_buc = malloc(sizeof(t_px_vars));
	if (var_buc == NULL)
	{
		if (envpaths != NULL)
			px_free_split(envpaths);
		return (NULL);
	}
	var_buc->args = argv;
	var_buc->argcnt = argc;
	var_buc->paths = envpaths;
	var_buc->p_fds = pfd;
	var_buc->env = envp;
	return (var_buc);
}

int	main(int argc, char *argv[], char *envp[])
{
	int			p_fd[2];
	t_px_vars	*var_buc;

	if (px_check_args(argc, argv, envp) == 1)
	{
		ft_putstr_fd("Wrong input, try again...\n", 2);
		return (1);
	}
	if (pipe(p_fd) == -1)
	{
		ft_putstr_fd("Pipe() failed\n", 2);
		return (1);
	}
	var_buc = st_mvars(argc, argv, envp, p_fd);
	if (var_buc == NULL)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		ft_putstr_fd("Variable not created, can't work...\n", 2);
		return (1);
	}
	px_check_outfile(var_buc);
	px_mama_children(var_buc);
}
