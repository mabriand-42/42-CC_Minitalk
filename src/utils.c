/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 13:46:54 by mabriand          #+#    #+#             */
/*   Updated: 2022/05/19 11:52:27 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

void	ft_putstr_fd(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}

void	ft_putendl_fd(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	write(fd, " \n", 2);
	return ;
}

/*
**  void ft_error(char *strerror)
**
**	Parameters:
**		@ char  *strerror : the error message to print in order
**
**	Description:
**	->	
**	
**	Return values:
**		If an error occurs, the process returns 1 by calling ft_error(1), else 0.
*/
void	ft_error(char *strerror)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(strerror, 2);
	exit(1);
}
