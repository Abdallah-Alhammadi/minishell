/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:26:18 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 19:41:10 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_child(t_cmd_op **cmds, t_list *env_pack[2], t_ints *t_int,
	t_token **tokens)
{
	char	**envp;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(t_int->rlstdin);
	close(t_int->rlstdout);
	exit_duplicats(cmds, t_int, tokens);
	if (is_builtin(cmds[t_int->counter]->cmd))
	{
		if (!ft_strcmp(cmds[t_int->counter]->cmd, "exit")
			&& argument_num(cmds[t_int->counter]->cmd_args) <= 2)
			free_tokens(&tokens);
		exec_builtin(cmds, env_pack, t_int, 1);
		free_child(cmds, env_pack, t_int, tokens);
		exit(t_int->e_status);
	}
	envp = make_environments_vars(env_pack + 0);
	if (ft_strchr(cmds[t_int->counter]->cmd, '/'))
		execve(cmds[t_int->counter]->cmd, cmds[t_int->counter]->cmd_args, envp);
	exit_error(cmds[t_int->counter], cmds[t_int->counter]->cmd_args, t_int);
	free_arr(envp);
	free_child(cmds, env_pack, t_int, tokens);
	exit(t_int->e_status);
}

int	run_command(t_cmd_op **cmds, t_list *env_pack[2], t_ints *t_int,
	t_token **tokens)
{
	int		pid;

	if (!(cmds + t_int->counter) || !(cmds[t_int->counter]))
		return (0);
	if ((is_builtin(cmds[t_int->counter]->cmd) && t_int->pip_count < 1))
	{
		exit_duplicats(cmds, t_int, tokens);
		if (!ft_strcmp(cmds[t_int->counter]->cmd, "exit")
			&& argument_num(cmds[t_int->counter]->cmd_args) <= 2)
			free_tokens(&tokens);
		exec_builtin(cmds, env_pack, t_int, 0);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror(""), -1);
		t_int->child_id = pid;
		if (pid == 0)
			run_child(cmds, env_pack, t_int, tokens);
		else
			signal(SIGINT, SIG_IGN);
	}
	return (0);
}

void	end_execution(t_token **tokens, t_cmd_op **cmds, t_ints *t_int)
{
	if (t_int->pip_count > 0)
		pipe_end(t_int);
	if (t_int->cmd_count > 0 && (!(t_int->cmd_count == 1)
			|| !(is_builtin(cmds[0]->cmd))))
		wait_command(t_int);
	reset_fd(t_int);
	delete_heredoc(tokens);
	if (t_int->pipes)
	{
		free(t_int->pipes);
		t_int->pipes = 0;
	}
}

int	run_loop(t_list *env_pack[2], t_token **tokens,
					t_cmd_op **cmds, t_ints *t_int)
{
	int	i;

	if (init_utils(tokens, t_int) == -1)
		return (1);
	exe_heredoc(tokens, env_pack, t_int);
	i = 0;
	while (tokens + i && tokens[i])
	{
		if (redirect(tokens, t_int, i) != -5)
		{	
			if (command_find(tokens, i) >= 0)
			{
				cmds[t_int->counter]->redir_in = check_strdin(tokens,
						command_find(tokens, i));
				cmds[t_int->counter]->redir_out = check_stdout(tokens,
						command_find(tokens, i));
				run_command(cmds, env_pack, t_int, tokens);
				t_int->counter++;
			}
		}
		else if (command_find(tokens, i) >= 0)
			counter_update(t_int);
		i = next_pipe(tokens, i);
	}
	return (end_execution(tokens, cmds, t_int), 0);
}

int	execution(t_list *env_pack[2], t_token **tokens, t_ints *t_int)
{
	t_strs		*cmd_list;
	t_cmd_op	**cmds;

	cmd_list = has_struct();
	cmd_list->env_p = ft_strdup(get_val(env_pack + 0, "PATH"));
	cmd_list->ind_p = ft_split(cmd_list->env_p, ':');
	cmd_list->cmd_len = count_command(tokens);
	cmds = create_commands(&cmd_list, tokens);
	free_environment(cmd_list);
	if (!cmds)
	{
		t_int->e_status = 1;
		return (EXIT_FAILURE);
	}
	t_int->e_status = 0;
	g_e_stat = t_int->e_status;
	run_loop(env_pack, tokens, cmds, t_int);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	free_commands(cmds);
	cmds = 0;
	g_e_stat = t_int->e_status;
	return (EXIT_SUCCESS);
}
