/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabriand <mabriand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 12:04:51 by mabriand          #+#    #+#             */
/*   Updated: 2022/05/20 11:09:20 by mabriand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minitalk.h"

/*
**	Having a global variable is necessary as parameters cannot be passed to a
**	function called when receiving a specific signal. There is only 1 inherent
**	argument: the value of the received signal (= int).
*/
t_trans	g_client;

/*
**	Parameters:
**		@ char	*str :
**
**	Description:
**	->	If we consecutively returned 8 bits, it means a full char (=byte) of the
**		string 'str' has been sent to the server process.
**			
**		If it is '\0', returns -1 meaning transmission is done. Else, reboots
**		the static variable 'i_bit' and increments 'i', going to the next char.
**
**	->	Makes a right bit-shifting operation to isolate the bit at index 'i_bit'.
**
**	->	Increments 'i_bit' for next function call and returns the isolated bit.
**	
**	Return values:
**		1 or 0 given the result of the right bit-shifting operation.		
*/
static int	ft_get_bit(char *str)
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
**		@ pid_t	pid	:	the server process id
**		@ bool	bit	:	bit to be transmitted
**
**	Description:
**	->	1.	If 'bit' is 0, sends the signal SIGUSR1 to the server process.
**		2.	Else, if 'bit' is 1, sends the other signal: SIGUSR2.
**	
**	Return values:
**		None.	
*/
static void	ft_send_bit(pid_t pid, bool bit)
{
	if (bit == 0)
	{
		if (kill(pid, SIGUSR1) == -1)
			ft_print_error("No such process");
	}
	else if (bit == 1)
	{
		if (kill(pid, SIGUSR2) == -1)
			ft_print_error("No such process");
	}
	return ;
}

/*
**	Parameters:
**		@ int	signum	:	integer corresponding to the signal received by the
**							client process.
**
**	Description:
**		When SIGUSR1 is sent from the server, this function sends the next bit
**		of the string or stops the process if it is done transmitting.
**	
**	->	Checks if the signal received is SIGUSR1. If not, the process exits 1
**		through ft_error(1);
**
**	->	1.	If the bit returned by get_bit(1) is -1, the job is done.
**		2.	Else, sends this bit to the server via send_bit().
**	
**	Return values:
**		None.	
*/
static void	ft_send_next_bit(int signum)
{
	int	bit;

	if (signum == SIGUSR2)
		ft_print_error("Wrong signal. Please relaunch...");
	bit = ft_get_bit(g_client.msg);
	usleep(100);
	if (bit == -1)
		exit(EXIT_SUCCESS);
	ft_send_bit(g_client.pid, bit);
}

/*
**  int main(int ac, char **av)
**
**	Parameters:
**		@ int	ac      :	number of arguments passed to the program
**		@ char	**av	:	array of arguments (av[0] being its name)
**
**	Description:
**	->	Store the server's pid (av[1]) as you need it to talk to the process.
**	
**	->	Thanks to sigaction(3), defines which action occurs when SIGUSR1 or
**		SIGUSR2 is received.
**
**	->	Gives the first drive by sending the first bit of the string to transfer 
**		thanks to send_bit(2).
**	
**	->	Waits for the response signal from the server during 2 second.
**		(For both signals, send_next_bit(1) will be called. However, the set of
**		actions will defer inside the function according to the signal recevied).
**	
**	Return values:
**		If an error occurs, the process exits 1 by calling ft_error(1), else 0.
**    	(A return from the main always performs an exit through its return!)
*/
int	main(int ac, char **av)
{
	pid_t	pid_server;

	if (ac != 3)
		ft_print_error("Usage is as follows:\n'./client [PID] [string]'\n");
	pid_server = ft_atoi(av[1]);
	if (pid_server < 1)
		ft_print_error("Wrong PID");
	g_client.msg = av[2];
	g_client.pid = pid_server;
	signal(SIGUSR1, ft_send_next_bit);
	signal(SIGUSR2, ft_send_next_bit);
	ft_send_bit(g_client.pid, ft_get_bit(g_client.msg));
	while (1)
	{
		if (sleep(2) == 0)
			ft_print_error("Transmission failed.\nPlease relaunch the server");
	}
	return (0);
}
