/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_ft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:09:53 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 18:18:52 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_heredoc(t_ints	*t_int, int num)
{
	int	hd;

	if (signal(SIGINT, handle_signal2) != SIG_ERR)
		t_int->e_status = 1;
	if (signal(SIGQUIT, SIG_IGN) != SIG_ERR)
		t_int->e_status = 0;
	hd = heredoc_files(num, 1);
	if (hd < 0)
		return (-1);
	return (hd);
}

void	delete_heredoc(t_token **tokens)
{
	int		i;
	int		j;
	char	*fname;
	char	*num;

	i = 0;
	j = 0;
	while (tokens + i && tokens[i])
	{
		if (tokens[i]->type == here_doc)
		{
			num = ft_itoa(i);
			fname = ft_strjoin(".heredoc", num);
			if (!access(fname, F_OK))
				unlink(fname);
			free(num);
			free(fname);
			j++;
		}
		i++;
	}
	(void)j;
}
