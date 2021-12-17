/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 14:09:58 by adbenoit          #+#    #+#             */
/*   Updated: 2021/12/17 22:07:49 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_error(char *strerror)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(strerror, 2);
	exit(1);
}

/* returns the byte if it has been fully received.
Otherwise returns -1. */

static int	get_byte(int signum)
{
	// printf("signum : %d\n", signum);
	static int	i_bit = 0;
	static char	byte = 0;
	char		c;

	printf("heyheyhey\n\n");
	if (signum == SIGUSR2)
		byte += 1 << i_bit;
	++i_bit;
	if (i_bit == 8)
	{
		c = byte;
		byte = 0;
		i_bit = 0;
		return (c);
	}
	return (-1);
	// return (0);
}

/* decode the message, send confirmation of the reception to the client
 and display the string */

static void	receive_str(int signum, siginfo_t *info, void *unused)
{
	int			byte;
	static char	buffer[30000];
	static int	i = 0;

	//printf("passing here\n");
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
	printf("si_pid = %d", info->si_pid);
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_error("No such process.");
	(void)unused;
}

int	main(void)
{
	struct sigaction	s;

	s.sa_flags = SA_SIGINFO;
	s.sa_sigaction = receive_str;
	ft_putstr_fd("PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	if (sigaction(SIGUSR1, &s, NULL) < 0)
		return (1);
	if (sigaction(SIGUSR2, &s, NULL) < 0)
		return (1);
	while (1)
		pause();
	return (0);
}
