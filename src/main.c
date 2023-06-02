/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 14:12:49 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/02 14:57:59 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./src.h"

/* PROBLEM REPORT
   ----------------------
	*	./pipex emptyfile "ls -la" "wc -l" outfile 
   				-	with emptyfile and outfile existing with the right permissions
				-	output file contians the output of command wc 
					but seemingly of a wrong directory
		.......................................................................
				-	fixed this:
						+	it didn't work properly because the wrong variable
							was being split for the command

	*	./pipex emptyfile "ls -la" "wc -l" filename
				-	with emptyfile existing and proper permissions
					and filename not existing 
				-	it creates the file but with nothing in it 
			.............................................................
				-	fixed one part of this problem:
						+	the file filename was empty because it didn't have
							the right permissions
							you have to add which permissions a file has to get
							when creating it with open!!! 
							For more explanation view the link in your google docs
							useful links file 

	*	./pipex emptyfile "ls" "grep le" outfile 
				-	with emptyfile and outfile existing with the right permissions
				-	it returns how one should use grep and doesn't fill outfile
			....................................................................
				-	fixed this, because I was splitting the wrong variable 
					to give to execve

	*	./pipex file "ls -la" "wc -l" outfile
				-	with file not existing, and 
					outfile existing with the right permissions 
				-	it executes "ls -la" as if it were "ls" in the terminal, and 
					runs "wc -l" as if it were "wc" and 
					stores the result in outfile (0 0 0)
			................................................................
				-	fixed one part of this problem:
						+	it was executing "ls -la" as if it were "ls",
							because you were using split on the wrong variable
							now it is splitting the proper variable and thus 
							executing the correct command
					-	It is still executing it in the "wrong" folder
					
	*	./pipex emptyfile "ls" "grep le" newfile3
				-	emptyfile exists with right permissions, and newfile3 not existing
				-	the output is different from "< emptyfile ls | grep le > newfile3"
					the original also includes the newly created file newfile3, 
					while mine does not include this newly created file,
					since the file isn't created until after the command "ls" has run 
	*	./pipex nofile cat wc noperm
				-	nofile does not exist, and noperm exists but has no permissions
				-	First it closed all the fd's and still tried to execute with execve
					+	now I changed it so it doesn't execute when either file is not 
						reachable or one of the duplicates failes
	*	./pipex emptyfile "cat /dev/urandom" "head -n 50" outfile
				-	emptyfile and outfile exist and have the proper permissions
				-	this will break my code,
					since my parent will be waiting for the child to stop
					but that is an never ending process unless the parent would close 
					the read end of the pipe (not the neatest way to stop it)
			+	I'll propably need two child processes anyway, and use waitpid in the parent process
*/

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

int	main(int argc, char *argv[], char *envp[])
{
	pid_t		r_id1;
	pid_t		r_id2;
	int			p_fd[2];
	int			status;
	int			tmp;
	t_px_vars	*var_buc;

	if (px_check_args(argc, argv, envp) == 1)
		return (1);
	if (pipe(p_fd) == -1)
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
	if (px_check_files(var_buc) == 1)
		return (st_error(var_buc, 1, "Input does not contain two files"));
	px_check_outfile(var_buc);
	r_id1 = fork();
	if (r_id1 == -1)
		return (st_error(var_buc, 1, "First fork() failed"));
	if (r_id1 == 0)
		px_first_child(var_buc);
	else
	{
	//	ft_putstr_fd("Parent process after one fork\n", 2);
		r_id2 = fork();
		if (r_id2 == -1)
			return (st_error(var_buc, 1, "Second fork() failed"));
		if (r_id2 == 0)
			px_sec_child(var_buc);
		else
		{
			status = 0;
			tmp = 0;
			close((var_buc->p_fds)[0]);
			close((var_buc->p_fds)[1]);
			close(p_fd[1]);
			close(p_fd[0]);
		//	ft_putstr_fd("Parent process after two forks\n", 2);
			waitpid(r_id2, &status, 0);
	//		wait(&tmp);
			waitpid(0, NULL, 0);

			if ((var_buc->paths) != NULL)
				px_free_split(var_buc->paths);
			free(var_buc);
			if (WIFEXITED(status))
			{
//				ft_putstr_fd("Help!!\n", 2);
				exit(WEXITSTATUS(status));
			}
			else if (WIFSIGNALED(status))
				exit(128 + WTERMSIG(status));
			else
				exit(EXIT_SUCCESS);
		}
	}

}
