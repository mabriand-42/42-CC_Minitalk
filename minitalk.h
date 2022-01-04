/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:10:29 by mabriand          #+#    #+#             */
/*   Updated: 2022/01/04 23:03:53 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdbool.h>

# include <stdio.h>

// #define BUFFER_SIZE 3000

typedef struct	s_trans
{
	pid_t	pid;
	char*	msg;
}				t_trans;

int		ft_atoi(const char *str);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_error(char *strerror);

#endif