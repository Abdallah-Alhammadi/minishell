/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:06:42 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 18:39:07 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_hd_checker(t_token **tokens, int j, int flag, t_ints *t_int)
{
	char	*hdname;
	char	*hdnum;
	int		k;

	(void)tokens;
	hdnum = ft_itoa(j);
	hdname = ft_strjoin(".heredoc", hdnum);
	free(hdnum);
	k = open(hdname, O_RDONLY);
	free(hdname);
	if (k < 0)
	{
		if (!flag)
			t_int->e_status = error_rediractor("heredoc file error", "", 1);
		return (-1);
	}
	close(k);
	return (0);
}

int	error_checker_rin(t_token **tokens, int j, int flag, t_ints *t_int)
{
	int	k;

	k = open(tokens[j + 1]->token, O_RDONLY);
	if (k < 0)
	{
		if (!flag)
			t_int->e_status = error_rediractor(strerror(errno),
					tokens[j + 1]->token, 1);
		return (-1);
	}
	close(k);
	return (0);
}

int	check_rout(t_token **tokens, int j, int flag, t_ints *t_int)
{
	int	k;

	k = open(tokens[j + 1]->token, O_RDWR | O_CREAT | O_TRUNC, 0000644);
	if (k < 0)
	{
		if (!flag)
			t_int->e_status = error_rediractor(strerror(errno),
					tokens[j + 1]->token, 1);
		return (-1);
	}
	close(k);
	return (0);
}

int	shell_out_checker(t_token **tokens, int j, int flag, t_ints *t_int)
{
	int	k;

	k = open(tokens[j + 1]->token, O_RDWR | O_CREAT | O_APPEND, 0000644);
	if (k < 0)
	{
		if (!flag)
			t_int->e_status = error_rediractor(strerror(errno),
					tokens[j + 1]->token, 1);
		return (-1);
	}
	close(k);
	return (0);
}

int	error_rediractor(char *msg, char *file, int err)
{
	ft_putstr_fd("bash: ", 2);
	if (file)
		ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	return (err);
}
