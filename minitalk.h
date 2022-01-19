/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:10:29 by mabriand          #+#    #+#             */
/*   Updated: 2022/01/19 13:02:12 by mabriand         ###   ########.fr       */
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

typedef struct s_trans
{
	pid_t	pid;
	char	*msg;
}	t_trans;

int		ft_isdigit(int c);
int		ft_isspace(int c);
size_t	ft_strlen(const char *s);
size_t	ft_intlen(int n);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_error(char *strerror);

#endif