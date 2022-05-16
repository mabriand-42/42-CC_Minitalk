/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:04:51 by mabriand          #+#    #+#             */
/*   Updated: 2022/05/16 12:11:53 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

/*
**	Having a global variable is necessary as we cannot pass parameters
**	to a function called when receiving a specific signal. There is in
**	only 1 inherent argument: the value of the received signal (= int).
*/
t_trans	g_client;

/*
**	Parameters:
**		@ char	*str :
**
**	Description:
**	->	1)	If we consecutively just returned 8 bits, it means a full
**			char (= byte) of the string 'str' has been sent to the
**			server process.
**			If it happens to be '\0', we return -1, meaning we're done
**			transmitting. Else, we reboot the static variable 'i_bit'
**			and increment the 'i' one, meaning we go to the next char.
**		
**		2)	Do nothing if not.
**
**	->	We make a right bit-shifting operation to isolate the bit at 
**		index 'i_bit'.
**
**	->	We increment 'i_bit' for the next function call and return the
**		bit we isolated.
**	
**	Return values:
**		1 or 0 given the result of the right bit-shifting operation.		
*/
static int	get_bit(char *str)
{
	bool		bit;
	static int	i_bit = 0;
	static int	i = 0;

	if (i_bit > 7)
	{
		if (!str[i])
			return (-1);
		i_bit = 0;
		++i;
	}
	bit = (str[i] >> i_bit) & 1;
	++i_bit;
	return (bit);
}

/*
**	Parameters:
**		@ pid_t	pid	:
**		@ bool	bit	:
**
**	Description:
**	->	1)	If 'bit' is 0, we send the signal SIGUSR1 to the server
**			process thanks to its 'pid'.
**		
**		2)	Else, if 'bit' is 1, we send the other signal: SIGUSR2.
**	
**	Return values:
**		None.	
*/
static void	send_bit(pid_t pid, bool bit)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
			ft_error("No such process");
	}
	else if (bit == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
			ft_error("No such process");
	}
	return ;
}

/*
**	Parameters:
**		@ int	signum	:
**
**	Description:
**		When the SIGUSR1 signal is sent from the server, this function
**		sends the next bit of the string or stops the process if we
**		are done transmitting.
**	
**	->	We check if the signal received is SIGUSR1. If not, we stop
**		the program as it is an error.
**
**	->	1)	If the bit returned by get_bit() is -1 we are successfuly
**			done transmitting the string to the server.
**
**		2)	Else, we send this bit to the server via send_bit().
**	
**	Return values:
**		None.	
*/
static void	send_next_bit(int signum)
{
	int	bit;

	if (signum == SIGUSR2)
		ft_error("Wrong signal. Please relaunch...");
	bit = get_bit(g_client.msg);
	usleep(100);
	if (bit == -1)
	{
		ft_putstr_fd("\nMessage has been successfuly transmitted!!! =) \n", 1);
		exit(EXIT_SUCCESS);
	}
	send_bit(g_client.pid, bit);
}

/*
**	Parameters:
**		@ char	*av1	:
**		@ char	*av2	:
**
**	Description:
**		A simple function that prints in stdout some information about
**		the client and the information received in arguments.
**	
**	Return values:
**		None.	
*/
void	client_speaking(char *av1, char *av2)
{
	// ft_putstr_fd("Client speaking. I receptionned the following:\n\n", 1);
	// ft_putstr_fd("PID of server process: ", 1);
	ft_putendl_fd(av1, 1);
	// ft_putstr_fd("MSG to transfer to it: ", 1);
	// ft_putendl_fd(av2, 1);
	return ;
}

/*
**  int main(int ac, char **av)
**
**	Parameters:
**		@ int	ac      :
**		@ char	**av	:
**
**	Description:
**	->	We store the 2nd argument (= server pid) as we need it to
**		communicate with the process.
**	
**	->	Thanks to sigaction(3), we define which action will occur when
**		SIGUSR1 or SIGUSR2 is received.
**
**	->	We give the first drive by sending the first bit of the string
**		to transfer thanks to send_bit().
**	
**	->	We wait for the response signal from the server during 1 second.
**		(For both signals, send_next_bit() will be called. However,
**		the succession of actions will defer inside the function
**		according to the signal recevied).
**	
**	Return values:
**		If an error occurs, the process exits 1 by calling ft_error(1), else 0.
**    (A return from the main, always performs an exit through its return!)
*/
int	main(int ac, char **av)
{
	pid_t	pid_server;

	if (ac != 3)
		ft_error("Usage is as follows:\n'./client [PID] [string]'\n");
	pid_server = ft_atoi(av[1]);
	if (pid_server < 1)
		ft_error("Wrong PID");
	client_speaking(av[1], av[2]);
	g_client.msg = av[2];
	g_client.pid = pid_server;
	signal(SIGUSR1, send_next_bit);
	signal(SIGUSR2, send_next_bit);
	send_bit(g_client.pid, get_bit(g_client.msg));
	while (1)
	{
		if (sleep(1) == 0)
			ft_error("Transmission failed.\nPlease relaunch the server");
	}
	return (0);
}
