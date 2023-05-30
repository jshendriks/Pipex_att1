/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   processes.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhendrik <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 16:08:23 by jhendrik      #+#    #+#                 */
/*   Updated: 2023/05/30 15:07:33 by jhendrik      ########   odam.nl         */
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

int	px_first_child(t_px_vars *buc);
int	px_sec_child(t_px_vars *buc);

#endif
