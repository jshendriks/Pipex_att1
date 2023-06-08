/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_valid_cmnpath.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:15:19 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/08 12:19:41 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./utils.h"

static char	*st_check_for_validpath(char *part_comm, char **paths_sep)
{
	char	*tmph1;
	char	*tmph2;
	int		i;

	if (part_comm == NULL || paths_sep == NULL)
		return (NULL);
	i = 0;
	while (paths_sep[i])
	{
		tmph1 = ft_strjoin((char const *)paths_sep[i], "/");
		if (tmph1 != NULL)
		{
			tmph2 = ft_strjoin((char const *)tmph1, (char const *)part_comm);
			if (tmph2 != NULL)
			{
				if (access(tmph2, X_OK) == 0)
					return (free(tmph1), tmph2);
				free(tmph2);
			}
			free(tmph1);
		}
		i++;
	}
	return (NULL);
}

char	*px_find_valid_cmnpath(t_px_vars *varbuc, int i)
{
	char	**comm_sep;
	char	*part_comm;

	if ((varbuc->args)[i] == NULL)
		return (NULL);
	if (*((varbuc->args)[i]) == '\0')
		return (NULL);
	comm_sep = px_split_xtr((varbuc->args)[i], ' ');
	if (comm_sep != NULL)
	{
		part_comm = ft_strdup((char const *)comm_sep[0]);
		px_free_split(comm_sep);
	}
	else
		part_comm = ft_strdup((char const *)((varbuc->args)[i]));
	if (access((const char *)part_comm, X_OK) == 0)
		return (part_comm);
	if ((varbuc->paths) == NULL || ((varbuc->paths)[0]) == NULL)
		return (NULL);
	return (st_check_for_validpath(part_comm, (varbuc->paths)));
}
