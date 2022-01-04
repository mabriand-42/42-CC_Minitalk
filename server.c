/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 11:34:21 by mabriand          #+#    #+#             */
/*   Updated: 2022/01/04 16:26:39 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	get_byte(int signum)
{
	static int	bits = 0;
	static char	byte = 0;
	char		c = -1;

	if (signum == SIGUSR2)
		byte += 1 << bits;
	++bits;
	if (bits == 8)
	{
		c = byte;
		byte = 0;
		bits = 0;
	}
	return (c);
}

void	printMsgHandler(int signum, siginfo_t *info, void *unused)
{
	int			byte;
	static char	buffer[BUFFER_SIZE];
	static int	i = 0;
	
	if ((byte = get_byte(signum)) != -1)
	{
		buffer[i++] = byte;
		if (!byte || i == BUFFER_SIZE - 1)
		{
			if (i == BUFFER_SIZE - 1)
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
	
	s.sa_sigaction = printMsgHandler;
	s.sa_flags = SA_SIGINFO;
	
	if ((sigaction(SIGUSR1, &s, NULL) < 0) || (sigaction(SIGUSR2, &s, NULL) < 0))
		return (1);
	while (1)
		pause();
	return (0);
}
