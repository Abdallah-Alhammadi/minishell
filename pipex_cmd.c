/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:06:35 by naalzaab          #+#    #+#             */
/*   Updated: 2023/09/22 18:35:27 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*commant_path(char **env, char *cmd)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = -1;
	if (!cmd)
		return (NULL);
	while (env[++i])
	{
		tmp = ft_strjoin(env[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (ft_strdup(cmd));
}

void	free_arr(char **arr)
{
	int	i;

	i = -1;
	while (arr[++i])
	{
		if (arr[i])
			free(arr[i]);
	}
	if (arr)
		free(arr);
	arr = NULL;
}

char	*env_p(char **envp)
{
	int		i;
	char	**path;
	char	*tmp;

	i = -1;
	tmp = NULL;
	while (envp[++i])
	{
		path = ft_split(envp[i], '=');
		if (ft_strncmp(path[0], "PATH", ft_strlen(path[0])) == 0)
		{
			if (path[1])
				tmp = ft_strdup(path[1]);
			free_arr(path);
			return (tmp);
		}
		free_arr(path);
	}
	return (NULL);
}

char	**sep_commant(char *str)
{
	char	**arr;

	if (!str)
		return (NULL);
	arr = ft_split(str, ' ');
	return (arr);
}

t_strs	*has_struct(void)
{
	t_strs	*t_str;

	t_str = (t_strs *)malloc(sizeof(t_strs));
	if (!t_str)
		return (0);
	t_str->ind_p = NULL;
	t_str->env_p = NULL;
	t_str->lim = NULL;
	t_str->cmd_args = NULL;
	t_str->tmp_cmd = NULL;
	t_str->tmp = NULL;
	return (t_str);
}
