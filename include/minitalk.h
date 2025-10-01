/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lanton-m <lanton-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:56:45 by lanton-m          #+#    #+#             */
/*   Updated: 2025/10/01 18:40:36 by lanton-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h> // write, usleep, pause, getpid
# include <stdlib.h> // malloc(), free() and size_t
# include <signal.h> // sigaction, sigemptyset, sigaddset, kill, siginfo_t
# include <sys/types.h> // pid_t
# include "../libs/libft/includes/libft.h" // libft functions

# define ERROR 1
# define SUCCESS 0
# define ASCII_BITS 8
# define USLEEP_TIME 300

typedef struct s_data
{
	pid_t			server_pid;
	unsigned char	c;
	int				bit_index;
}	t_data;

void	ft_error(const char *msg);
void	ft_send_char(pid_t server_pid, unsigned char c);
void	ft_send_str(pid_t server_pid, const char *str);
void	ft_sigaction_server(struct sigaction *sa);
void	ft_sigaction_client(struct sigaction *sa);
void	ft_handler_server(int signum, siginfo_t *info, void *context);
void	ft_handler_client(int signum);
void	ft_print_pid(void);
int		ft_atoi(const char *str);
int		ft_is_valid_pid(const char *str);
size_t	ft_strlen(const char *s);
#endif
