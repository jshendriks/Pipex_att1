/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@42.fr>                      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:29:35 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/25 17:10:38 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include "./../libft/src/libft.h"
# include "./../types.h"

// SPLIT EXTRA FUNCTIONS ------------------------------------------------------
int		px_am_subs(char const *s, char c);
int		px_fill_ptr_subs(char const *s, char c, char **ptr_subs, int am_subs);
char	**px_split_xtr(char const *s, char c);

// FUNCTIONS TO FREE ---------------------------------------------------------
void	px_free_split(char **ptr_subs);

// FUNCTIONS CONCERNING PATHS ------------------------------------------------
char	*px_find_envvar(char *envp[], char *var);
char	**px_splitpaths(char *env_path);
char	*px_find_valid_cmnpath(t_px_vars *varbuc, int i);

// FUNCTIONS TO SWAP FD'S ----------------------------------------------------
int	px_swapfds_be(t_px_vars *buc, int *p_filefd, int i);

#endif
