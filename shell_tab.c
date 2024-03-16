/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:10:06 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 19:28:42 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	shell_value(t_list *envp[2], t_dict *dict, unsigned long long n)
{
	if (get_val(&(envp)[0], "SHLVL"))
	{
		n = mini_atoi(get_val(&(envp)[0], "SHLVL"));
		if (n >= 9999 && n <= 2147483646)
		{
			n++;
			ft_putstr_fd("N&A: Error: shell level (", 2);
			ft_putnbr_fd(n, 2);
			ft_putendl_fd(") too high, going back to 1", 2);
			n = 0;
		}
		else if (n > 2147483646)
			n = -1;
		n++;
	}
	else
		n = 1;
	dict->value = ft_itoa(n);
	remake_environment(dict, &(envp)[0]);
	remake_environment(dict, &(envp)[1]);
	directory_free(dict, 0);
	return (0);
}

int	update_shell(t_list *envp[2])
{
	unsigned long long	n;
	t_dict				*dict;

	dict = (t_dict *)malloc(sizeof(t_dict));
	if (!dict)
	{
		perror("malloc");
		return (1);
	}
	dict->key = ft_strdup("SHLVL");
	dict->flag = 1;
	n = 0;
	if (key_exists("SHLVL", &(envp)[0]))
		return (shell_value(envp, dict, n));
	n = 1;
	dict->value = ft_itoa(n);
	remake_environment(dict, &(envp)[0]);
	remake_environment(dict, &(envp)[1]);
	directory_free(dict, 0);
	return (0);
}
