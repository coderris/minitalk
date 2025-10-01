/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:59:37 by lanton-m          #+#    #+#             */
/*   Updated: 2025/10/01 20:18:26 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_ack_received = 0;

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	struct sigaction	sa;

	if (argc != 3)
		ft_error("Usage: ./client <server_pid> <string_to_send>");
	if (!ft_is_valid_pid(argv[1]))
		ft_error("Error: Invalid PID");
	server_pid = (pid_t)ft_atoi(argv[1]);
	ft_sigaction_client(&sa);
	ft_send_str(server_pid, argv[2]);
	return (0);
}

void	ft_sigaction_client(struct sigaction *sa)
{
	sa->sa_handler = ft_handler_client;
	sa->sa_flags = 0;
	sigemptyset(&sa->sa_mask);
	if (sigaction(SIGUSR1, sa, NULL) == -1)
		ft_error("Error: sigaction failed");
	if (sigaction(SIGUSR2, sa, NULL) == -1)
		ft_error("Error: sigaction failed");
}

void	ft_handler_client(int signum)
{
	(void)signum;
	g_ack_received = 1;
}

void	ft_send_str(pid_t server_pid, const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		ft_send_char(server_pid, (unsigned char)str[i]);
		i++;
	}
	ft_send_char(server_pid, '\0');
}

void	ft_send_char(pid_t server_pid, unsigned char c)
{
	int	bit_index;

	bit_index = 0;
	while (bit_index < ASCII_BITS)
	{
		g_ack_received = 0;
		if ((c >> (7 - bit_index)) & 1)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				ft_error("Error: Failed to send SIGUSR1");
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				ft_error("Error: Failed to send SIGUSR2");
		}
		while (!g_ack_received)
			usleep(50);
		bit_index++;
	}
}
