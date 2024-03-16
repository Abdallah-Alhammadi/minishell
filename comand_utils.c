/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:50:39 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 17:51:54 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_pip_command(t_token **tokens, int i)
{
	int	j;

	j = ++i;
	while (tokens + j && tokens[j] && tokens[j]->type != pip
		&& tokens[j]->type != cmd)
		j++;
	return (j);
}

int	check_file(char *file, int j)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-5);
	close(fd);
	return (j);
}

int	argument_size(t_token **tokens, int j)
{
	int	i;

	i = 0;
	while (tokens + j && tokens[j] && (tokens[j]->type == option
			|| tokens[j]->type == arg))
	{
		i++;
		j++;
	}
	return (i);
}

int	argument_nums(t_token **tokens, int *i)
{
	int	j;
	int	count;

	j = *i;
	count = 0;
	while (tokens + j && tokens[j] && tokens[j]->type != pip)
	{
		if (tokens[j]->type == option || tokens[j]->type == 2)
			count++;
		j++;
	}
	return (count);
}

char	**cmd_arguments(t_token **tokens, int *i)
{
	char	**arg;
	int		count;
	int		j;
	int		k;

	count = argument_nums(tokens, i);
	arg = (char **)malloc(sizeof(char *) * (count + 2));
	if (!arg)
		return (0);
	j = *i;
	k = 0;
	arg[k++] = ft_strdup(tokens[j++]->token);
	while (tokens + j && tokens[j] && tokens[j]->type != pip)
	{
		if (tokens[j]->type == option || tokens[j]->type == 2)
			arg[k++] = ft_strdup(tokens[j]->token);
		j++;
	}
	arg[k] = 0;
	return (arg);
}
