/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 21:35:08 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/08 22:33:52 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../libft/libft.h"
# include "./ast.h"
# include "./env.h"
# include "./minishell.h"
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <unistd.h>

/* execute functions */
int		execute_ast(t_ast_node *node, t_shell *shell);
int		execute_command(t_ast_node *node, t_shell *shell);
int		execute_pipe(t_ast_node *node, t_shell *shell);
int		execute_logical(t_ast_node *node, t_shell *shell);
int		execute_subshell(t_ast_node *node, t_shell *shell);

/* path utils */
char	*find_command_path(char *cmd, char **envp);

/*command execute utils*/
int		handle_command_not_found(t_ast_node *node, t_shell *shell);
void	handle_cmd_child(t_ast_node *node, char *cmd_path, t_shell *shell);
int		handle_cmd_parent(pid_t pid, char *command_path, t_shell *shell);
int		handle_command_exec_fork_error(char *command_path, t_shell *shell);

/* redirect utils */
int		handle_redirects(t_list *redirect_list);
int		handle_heredoc(t_list *redirect);
int		handle_redirect_in(t_redirect *current, int *fd);
int		handle_redirect_out(t_redirect *current, int *fd);
int		handle_append(t_redirect *current, int *fd);

/* pipe utils */
void	close_fds(int *pipefds);
int		close_fds_return_error(int *pipefds);
void	handle_left_pid(int *pipefds);
void	handle_right_pid(int *pipefds);
int		wait_for_children(pid_t left_pid, pid_t right_pid, t_shell *shell);
pid_t	fork_left_child(t_ast_node *node, int *pipefds, t_shell *shell);
pid_t	fork_right_pid(t_ast_node *node, int *pipefds, t_shell *shell);

/* logical operator utils */
int		execute_and(t_ast_node *node, t_shell *shell);
int		execute_or(t_ast_node *node, t_shell *shell);

/* subshell utils */
void	execute_subshell_in_child(t_ast_node *node, t_shell *shell);
int		wait_for_child(pid_t pid, t_shell *shell);
int		handle_subshell_fork_error(t_shell *shell);

#endif