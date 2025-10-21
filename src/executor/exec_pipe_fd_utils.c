/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_fd_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsahakya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:00:47 by nsahakya          #+#    #+#             */
/*   Updated: 2025/10/21 13:00:51 by nsahakya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/executor.h"

void	close_fds(int *pipefds)
{
	close(pipefds[0]);
	close(pipefds[1]);
}

int	close_fds_return_error(int *pipefds)
{
	close_fds(pipefds);
	shell_perror("fork failed");
	return (1);
}

void	handle_left_pid(int *pipefds)
{
	dup2(pipefds[1], 1);
	close_fds(pipefds);
}

void	handle_right_pid(int *pipefds)
{
	dup2(pipefds[0], 0);
	close_fds(pipefds);
}
