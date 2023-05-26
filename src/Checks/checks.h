/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checks.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/26 17:46:43 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/26 18:00:28 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKS_H
# define CHECKS_H

# include "./../types.h"
# include "./../Utils/utils.h"
# include "./../libft/src/libft.h"

int		px_check_args(int argc, char *argv[], char *envp[]);
void	px_check_outfile(t_px_vars *buc);
int		px_check_files(t_px_vars *buc);

#endif
