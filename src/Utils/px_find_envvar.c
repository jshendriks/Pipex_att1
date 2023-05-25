/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   px_find_envvar.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:23:48 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/25 16:28:12 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "./utils.h"

char	*px_find_envvar(char *envp[], char *var)
{
	int		i;
	size_t	len_env;
	char	*rtn_var;
	char	*tmp;

	if (var == NULL || envp == NULL)
		return (NULL);
	if (*var == '\0' || envp[0] == NULL)
		return (NULL);
	i = 0;
	rtn_var = envp[i];
	while (rtn_var)
	{
		len_env = ft_strlen((const char *)rtn_var);
		tmp = ft_strnstr((const char *)rtn_var, (const char *)var, len_env);
		if (tmp == rtn_var)
			return (rtn_var);
		i++;
		rtn_var = envp[i];
	}
	return (NULL);
}
