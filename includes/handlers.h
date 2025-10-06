/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narek <narek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:39:49 by maghumya          #+#    #+#             */
/*   Updated: 2025/09/30 19:44:28 by narek            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLERS_H
# define HANDLERS_H

# include "../libft/libft.h"

typedef struct s_shell	t_shell;

void					handle_exit(t_shell *shell);
void					handle_clear_input(t_shell *shell);

#endif