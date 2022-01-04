/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:34:21 by mabriand          #+#    #+#             */
/*   Updated: 2022/01/04 23:18:32 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	get_byte(int signum)
{
	static int	bits = 0;
	static char	byte = 0;
	char		c;

	if (signum == SIGUSR2)
		byte += 1 << bits;
	++bits;
	if (bits == 8)
	{
		c = byte;
		byte = 0;
		bits = 0;
		return (c);
	}
	return (-1);
}

void	print_msg(int signum, siginfo_t *info, void *unused)
{
	int			byte;
	static char	buffer[30000];
	static int	i = 0;

	byte = get_byte(signum);
	if (byte != -1)
	{
		buffer[i++] = byte;
		if (!byte)
		{
			ft_putstr_fd(buffer, 1);
			i = 0;
		}
		else if (i == 29999)
		{
			buffer[i] = 0;
			ft_putstr_fd(buffer, 1);
			i = 0;
		}
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_error("No such process.");
	(void)unused;
	return ;
}

int	main(void)
{
	pid_t				pid_server;
	struct sigaction	s;

	pid_server = getpid();
	printf("Hi I'm server!\nThis is my PID: %d\n\n", pid_server);
	s.sa_sigaction = print_msg;
	s.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &s, NULL) < 0)
		return (1);
	if (sigaction(SIGUSR2, &s, NULL) < 0)
		return (1);
	while (1)
		pause();
	return (0);
}
