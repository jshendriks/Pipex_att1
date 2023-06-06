/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_checks.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 17:18:36 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/06 09:38:05 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./checks.h"

int	px_check_args(int argc, char *argv[], char *envp[])
{
	if (argc != 5)
		return (1);
	if (argv == NULL || envp == NULL)
		return (1);
	return (0);
}

void	px_check_outfile(t_px_vars *buc)
{
	int		fd_out;
	char	*filename;

	if (buc != NULL)
	{
		filename = (buc->args)[(buc->argcnt) - 1];
		if (access(filename, F_OK) != 0)
			fd_out = open(filename, O_CREAT, 0666);
		else
			fd_out = -1;
		if (fd_out != -1)
			close(fd_out);
	}
}

static void	st_helpfree(char *str1, char *str2)
{
	if (str1 != NULL)
		free(str1);
	if (str2 != NULL)
		free(str2);
}

int	px_check_files(t_px_vars *buc)
{
	char	*fileout;
	char	*filein;

	if (buc != NULL)
	{
		fileout = px_find_valid_cmnpath(buc, (buc->argcnt) - 1);
		filein = px_find_valid_cmnpath(buc, 1);
		if (fileout != NULL || filein != NULL)
			return (st_helpfree(filein, fileout), 1);
		return (st_helpfree(filein, fileout), 0);
	}
	return (1);
}
