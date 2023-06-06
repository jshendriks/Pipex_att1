/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_splitpaths.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:07:30 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/06 10:20:44 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./utils.h"

static int	st_strchr_int(const char *str, int c)
{
	char	asc_c;
	int		cnt;

	if (str == NULL)
		return (-2);
	asc_c = c % 256;
	cnt = 0;
	while (*(str + cnt) && (*(str + cnt) != asc_c))
		cnt++;
	if (*(str + cnt) == asc_c)
		return (cnt);
	return (-1);
}

char	**px_splitpaths(char *env_path)
{
	int		start;
	char	*paths;
	char	**paths_sep;

	if (env_path == NULL)
		return (NULL);
	start = st_strchr_int((const char *)env_path, '=');
	if (*(env_path + start + 1) == '\0')
		return (NULL);
	if (start >= 0)
	{
		paths = ft_substr((char const *)env_path, start, ft_strlen(env_path));
		if (paths != NULL)
		{
			paths_sep = ft_split((char const *)paths, ':');
			free(paths);
		}
		else
			paths_sep = NULL;
		return (paths_sep);
	}
	return (NULL);
}
