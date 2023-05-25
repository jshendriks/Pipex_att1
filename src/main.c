/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 14:12:49 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/25 17:41:01 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./src.h"

static t_px_vars	*st_make_tpxvars(int argc, char *argv[], char *envp[], int *pfd)
{
	char	*env_path;
	char	**envpaths;
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
	int	r_id;
	int	p_fd[2];
	int	rtnd;
	t_px_vars	*var_buc;

	if (argc != 5)
		return (1);
	if (argv == NULL || envp == NULL)
		return (1);
	rtnd = pipe(p_fd);
	if (rtnd == -1)
	{
		perror("Pipe() failed");
		return (1);
	}
	var_buc = st_make_tpxvars(argc, argv, envp, p_fd);
	if (var_buc == NULL)
	{
		close(p_fd[0]);
		close(p_fd[1]);
		return (1);
	}
	r_id = fork();
	if (r_id == -1)
	{
		perror("Fork failed");
		close(p_fd[0]);
		close(p_fd[1]);
		return (1);
	}
	if (r_id == 0)
	{
		// or should you use exit? if so, what argument do you give?
		return (px_child(var_buc));
	}
	else
	{
		return (px_parent(var_buc));
	}
}
