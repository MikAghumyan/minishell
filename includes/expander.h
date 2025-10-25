/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maghumya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 19:26:37 by maghumya          #+#    #+#             */
/*   Updated: 2025/10/23 19:36:24 by maghumya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "./ast.h"
# include "./env.h"
# include "./minishell.h"
# include "./tokenizer.h"
# include <dirent.h>
# include <stdbool.h>
# include <sys/wait.h>

# define WILDCARD_SYMBOL -1

typedef struct s_expand_data
{
	char	*result;
	bool	in_dquote;
	bool	in_squote;
	char	wcstr[2];
}			t_expand_data;

typedef struct s_expander
{
	t_shell	*shell;
	bool	syserror;
	bool	interrupted;
}			t_expander;

/* expand variable functions*/
char		*expand_token_value(t_shell *shell, char *value, bool heredoc);
char		*expand_quotes(char *value);
size_t		get_varlen(const char *var);
char		*expand_strjoin_free(char *s1, char *s2);
char		*initialize_expand(t_expand_data *data);
bool		expand_wildcard(t_strvector *args, char *pattern);
void		recover_pattern(char *pattern);

/* main expander functions*/

int			start_expander(t_shell *shell);
int			process_expander(t_ast_node *node, t_expander *expander);
int			expand_command(t_ast_node *node, t_expander *expander);
int			expand_arguments(t_strvector *args, t_expander *expander);
int			expand_redirections(t_list *redirects, t_expander *expander);
int			expand_subshell(t_ast_node *node, t_expander *expander);

/* heredoc functions */
int			expand_heredoc(t_redirect *redirect, t_expander *expander);
void		heredoc_child(t_redirect *redirect, t_expander *expander,
				char *path);
char		*heredoc_get_path(void);

#endif
