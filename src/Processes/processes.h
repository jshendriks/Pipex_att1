/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 16:08:23 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/06/06 10:37:26 by jhendrik      ########   odam.nl         */
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

void	px_first_child(t_px_vars *buc);
void	px_sec_child(t_px_vars *buc);
void	px_first_parent(t_px_vars *buc, int *p_fd);
void	px_sec_parent(t_px_vars *buc, int *p_fd, int r_id2);

#endif
