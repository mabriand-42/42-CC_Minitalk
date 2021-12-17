/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:40:44 by adbenoit          #+#    #+#             */
/*   Updated: 2021/12/17 22:09:04 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_trans	g_client;

static void	ft_error(char *str)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

/* if it's the last bit of the string, returns -1.
Otherwise returns the bit to send */

static int	get_bit(char *str)
{
	bool		bit;
	static int	i_bit = 0;
	static int	i = 0;
	printf("i_bit : %d\n", i_bit);
	if (i_bit > 7)
	{
		if (!str[i])
			return (-1);
		i_bit = 0;
		++i;
	}
	bit = (str[i] >> i_bit) & 1;
	++i_bit;
	printf("str[%d] : %c\n", i, str[i]);
	printf("bit : %d\n\n", bit);
	return (bit);
}

static void	send_bit(pid_t pid, bool bit)
{
	printf("bit para (in send_bit) = %d\n", bit);
	if (bit == 0)
	{
		printf("bit = 0 so sending SIGNAL 1\n\n");
		if (kill(pid, SIGUSR1) == -1)
			ft_error("No such process");
	}
	else if (bit == 1)
	{
		printf("bit = 1 so sending SIGNAL 2\n\n");
		if (kill(pid, SIGUSR2) == -1)
			ft_error("No such process");
		else
			printf("it woooooooooooooooooooooooooooooorked\n");
	}
}

/* wait for the server confirmation to continue the transmission */

static void	send_next_bit(int signum)
{
	int	bit;
	printf("SIGNUM IS : %d\n\n", signum);

	if (signum == SIGUSR2)
		ft_error("Wrong signal.\nPlease relaunch the server");
	bit = get_bit(g_client.mess);
	usleep(100);
	if (bit == -1)
	{
		ft_putstr_fd("End of the transmission.\n", 1);
		exit(EXIT_SUCCESS);
	}
	send_bit(g_client.pid, bit);
}

int	main(int ac, char **av)
{
	pid_t	pid;
	pid_t	pid2 = getpid();
	printf("pid of client: %d\n", pid2);
	if (ac != 3)
		ft_error("Usage: ./client [PID] [string to send]");
	pid = ft_atoi(av[1]);
	if (pid < 1)
		ft_error("Wrong PID");
	g_client.mess = av[2];
	g_client.pid = pid;
	// defini ce quel signql apelle quelle fonction

	printf("SIGUSR1 = %d\n", SIGUSR1);
	printf("SIGUSR2 = %d\n", SIGUSR2);

	signal(SIGUSR1, send_next_bit);
	signal(SIGUSR2, send_next_bit);

	send_bit(g_client.pid, get_bit(g_client.mess));
	printf("yolo\n");
	while (1)
	{
		if (sleep(1) == 0)
			ft_error("Transmission failed.\nPlease relaunch the server");
	}
	return (0);
}
