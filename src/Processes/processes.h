/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 16:08:23 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/25 17:39:57 by jhendrik      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESSES_H
# define PROCESSES_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "./../libft/src/libft.h"
# include "./../types.h"
# include "./../Utils/utils.h"

int	px_child(t_px_vars *buc);
int	px_parent(t_px_vars *buc);

#endif
