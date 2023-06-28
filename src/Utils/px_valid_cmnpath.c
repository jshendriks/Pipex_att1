/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_valid_cmnpath.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:15:19 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/28 13:50:55 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./utils.h"

static char	*st_checkexu(char *tmph1, char *part_comm, int *found)
{
	char	*tmph2;

	if (tmph1 != NULL)
	{
		tmph2 = ft_strjoin((char const *)tmph1, (char const *)part_comm);
		free(tmph1);
		if (tmph2 != NULL)
		{
			if (access(tmph2, X_OK) == 0)
				return (tmph2);
			else if (access(tmph2, F_OK) == 0)
			{
				*found = 1;
				return (NULL);
			}
			free(tmph2);
		}
	}
	return (NULL);
}

static char	*st_checkforpath(char *part_comm, char **paths_sep, int *found)
{
	char	*tmph1;
	char	*tmph2;
	int		i;

	i = 0;
	if (part_comm == NULL || paths_sep == NULL)
		return (NULL);
	while (paths_sep[i])
	{
		tmph1 = ft_strjoin((char const *)paths_sep[i], "/");
		tmph2 = st_checkexu(tmph1, part_comm, found);
		if (tmph2 == NULL && *found == 1)
			return (NULL);
		else if (tmph2 != NULL && *found == 0)
			return (tmph2);
		i++;
	}
	return (NULL);
}

static char	*st_give_partcmn(t_px_vars *varbuc, int i)
{
	char	**comm_sep;
	char	*part_comm;

	comm_sep = px_split_xtr((varbuc->args)[i], ' ');
	if (comm_sep != NULL)
	{
		part_comm = ft_strdup((char const *)comm_sep[0]);
		px_free_split(comm_sep);
	}
	else
		part_comm = ft_strdup((char const *)((varbuc->args)[i]));
	return (part_comm);
}

char	*px_find_valid_cmnpath(t_px_vars *varbuc, int i, int *found)
{
	char	*part_comm;

	if ((varbuc->args)[i] == NULL || found == NULL)
		return (NULL);
	if (*((varbuc->args)[i]) == '\0')
		return (NULL);
	part_comm = st_give_partcmn(varbuc, i);
	if (access((const char *)part_comm, X_OK) == 0)
		return (part_comm);
	else if (part_comm != NULL)
	{
		if (part_comm[0] == '.' && access(part_comm, F_OK) == 0)
		{
			*found = 1;
			return (NULL);
		}
		else if (access(part_comm, F_OK) == 0)
		{
			*found = 1;
			return (NULL);
		}
	}
	if ((varbuc->paths) == NULL || ((varbuc->paths)[0]) == NULL)
		return (NULL);
	return (st_checkforpath(part_comm, (varbuc->paths), found));
}
