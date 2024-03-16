/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:10:28 by abalhamm          #+#    #+#             */
/*   Updated: 2023/09/22 19:44:47 by naalzaab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
# define BUFFER_SIZE 42
# define MAX_FD 256

int		g_e_stat;

enum e_input_type
{
	cmd,
	option,
	arg,
	pip,
	redir_in,
	redir_out,
	here_doc,
	redir_out_append,
	file,
	delimiter,
	delimiter_q,
	empty_expansion,
	unset,
	redirection
};

typedef struct s_expand
{
	int		i;
	int		j;
	int		sq;
	int		dq;
	int		flag;
	char	*l;
}	t_expand;

typedef struct s_token
{
	char				*token;
	enum e_input_type	type;
}	t_token;

typedef struct cmd_op
{
	char	*cmd;
	char	**cmd_args;
	int		redir_in;
	int		redir_out;
}	t_cmd_op;

typedef struct strs {
	char	*env_p;
	char	**ind_p;
	char	*lim;
	char	*tmp_cmd;
	char	**cmd_args;
	char	*tmp;
	int		cmd_len;
}	t_strs;

typedef struct s_ints
{
	int	counter;
	int	cmd_count;
	int	pip_count;
	int	rlstdin;
	int	rlstdout;
	int	*pipes;
	int	e_status;
	int	child_id;
	int	hd;
}	t_ints;

void		del_node(void *node);
void		free_commands(t_cmd_op **cmds);
t_cmd_op	**create_commands(t_strs **cmd_list, t_token **tokens);
int			check_stdout(t_token	**tokens, int i);
int			check_strdin(t_token	**tokens, int i);
int			execution(t_list *env_pack[2], t_token **tokens, t_ints *t_int);
int			run_loop(t_list *env_pack[2], t_token **tokens,
				t_cmd_op **cmds, t_ints *t_int);
char		*env_p(char **envp);
char		*commant_path(char **env, char *cmd);
char		**sep_commant(char *str);
t_strs		*has_struct(void);
void		free_arr(char **arr);
char		*get_next_line(int fd);
t_dict		*directory_create(char *key, char *value, int flag);
int			directory_update(char *key, char *value, t_list **head);
char		*get_val(t_list **lst, char *key);
void		shell_print_env(t_list **lst, t_ints *t_int);
void		print_list(t_list **lst, t_ints *t_int);
void		remake_environment(t_dict *cmd, t_list **env);
void		send_build(t_list **lst, char **cmd_utils, t_list **export,
				t_ints *t_int);				
char		*recive_pwd(char **cmd_utils);
void		pwd_print(char **cmd_utils);
int			chg_dir(char **cmd_utils, t_list **lst, t_list **export,
				t_ints *t_int);
void		sort_list(t_list **head);
void		delete_heredoc(t_token **tokens);
void		exe_heredoc(t_token **tokens, t_list *env_pack[2], t_ints *t_int);
int			heredoc(int num, t_token **delim, t_list *lst, t_ints *t_int);
int			heredoc_files(int num, int flag);
int			start_heredoc(t_ints	*t_int, int num);
void		delete_heredoc(t_token **tokens);
void		handle_signal2(int sig);
int			is_builtin(char *cmd);
void		exec_builtin(t_cmd_op **cmd, t_list *env_pack[2], t_ints *t_int,
				int is_child);
int			is_name(char *cmd, char *arg);
int			is_alpha_num(char *cmd);
void		handle_signal(int sig);
void		create_key_val(t_dict **dict, char *cmd_utils);
int			update_shell(t_list *envp[2]);
void		free_tokens(t_token ***tokens_p);
void		free_commands(t_cmd_op **cmds);
void		free_str_array(char **str);
void		free_environment(t_strs	*cmd_list);
void		free_child(t_cmd_op **cmds, t_list *env_pack[2], t_ints *t_int,
				t_token **tokens);
int			open_import(t_cmd_op **cmds, t_ints *t_int, t_token **tokens);
int			open_export(t_cmd_op **cmds, t_ints *t_int, t_token **tokens);
int			exit_duplicats(t_cmd_op **cmds, t_ints *t_int, t_token **tokens);
int			its_space(char c);
int			its_redirect(char c);
void		check_quotes(char c, int *s_quote, int *d_quote);
void		increment(int *num1, int *num2);
char		*join_free(char *s1, char *s2);
t_token		**malloc_error(t_token **res, int i);
t_token		**empty_token(void);
char		**make_environments_vars(t_list **lst);
void		make_environment(t_list **head, char **envp);
int			argument_size(t_token **tokens, int j);
int			argument_nums(t_token **tokens, int *i);
char		**cmd_arguments(t_token **tokens, int *i);
int			n_pip_command(t_token **tokens, int i);
int			check_file(char *file, int j);
int			redirect(t_token **tokens, t_ints *t_int, int i);
int			next_pipe(t_token **tokens, int i);
int			command_find(t_token **tokens, int i);
void		counter_update(t_ints *t_int);
int			*make_pipe(t_ints *t_int);
int			pipe_counter(t_token	**tokens);
void		pipe_end(t_ints *t_int);
int			error_args(char *msg, char **args, int num, int err);
void		error_message_create(char *cmd, char *arg);
void		exit_error(t_cmd_op *cmd, char **args, t_ints *t_int);
void		read_first_t(int *j, int *num, const char *s);
void		read_pip(int *index, int *num,
				char const *s, t_token **res);
void		check_label(int *index, int *num, char const *s, t_token **res);
int			send_label(t_token *token);
int			check_syntax(int index, t_token ***tokens);
int			sent(enum e_input_type type);
int			valid_file(char *name);
void		set_index(int *i, int *j, int *s_quote, int *d_quote);
int			its_quote(char c1, char c2, int s_quote, int d_quote);
int			in_exit(char c1, char c2, int type, int s_quote);
int			exit_length(int exit_stat, int *len);
int			exit_begin(int *i, int *j, char *new_line, int exit_stat);
int			has_variable(char c1, char c2, int type, t_list *lst);
int			variable_len(int *len, char *line, t_list *lst);
int			find_var(t_expand *t, t_token **token, char *new_line, t_list *lst);
int			is_var(t_expand	*t_e, t_token **token, t_list *lst, char *nl);
char		*variable_name(char *line);
char		*get_value(char *var_name, t_list *lst);
char		*expand(t_token **token, t_list *lst, t_ints *t_int);
void		check_quotes(char c, int *s_quote, int *d_quote);
void		free_tokens(t_token ***tokens_p);
t_token		**parse(char *line, t_list *lst, t_ints *t_int);
int			token_lab(t_token ***tokens);
t_token		**start_tokens(char const *line);
void		directory_free(t_dict	*dict, int flag);
int			key_exists(char *s, t_list **new);
void		remove_list(t_list **head, char *str);
int			echo(char **arg);
int			build_unset(char **cmd_utils, t_list **lst, t_list **export);
int			exit_shell(t_list *env_pack[2], t_cmd_op **cmd, t_ints *t_int,
				int is_child);
void		free_str_array(char **str);
int			argument_num(char **args);
int			redir(t_token **tokens, t_ints *t_int);
int			do_in_redir(t_token **tokens, int i, int flag, t_ints *t_int);
int			do_out_redir(t_token **tokens, int i, int flag, t_ints *t_int);
int			get_right_pipe(t_token **tokens, int i);
int			get_left_pipe(t_token **tokens, int i);
int			error_rediractor(char *msg, char *file, int err);
int			error_hd_checker(t_token **tokens, int j, int flag, t_ints *t_int);
int			error_checker_rin(t_token **tokens, int j, int flag, t_ints *t_int);
int			shell_out_checker(t_token **tokens, int j, int flag, t_ints *t_int);
int			check_rout(t_token **tokens, int j, int flag, t_ints *t_int);
int			count_command(t_token	**tokens);
void		reset_fd(t_ints *t_int);
int			wait_command(t_ints *t_int);
int			init_utils(t_token **tokens, t_ints *t_int);

#endif
