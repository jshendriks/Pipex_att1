/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 16:13:33 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/06 10:29:19 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_px_vars
{
	char	**args;
	int		argcnt;
	char	**paths;
	int		*p_fds;
	char	**env;
}	t_px_vars;

typedef struct s_pxsplitbuc
{
	char const	*str;
	char		**subs;
	int			amount_subs;
}	t_pxsplitbuc;

#endif
