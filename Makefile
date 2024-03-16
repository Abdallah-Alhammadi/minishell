# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: naalzaab <naalzaab@student.42.ae>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 15:52:42 by abalhamm          #+#    #+#              #
#    Updated: 2023/09/22 19:53:59 by naalzaab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell

CC = cc -I/usr/local/opt/readline/include -g3

CFLAGS = -Wextra -Werror -Wall -g3

SRCS = main.c comand_utils.c comand_utils2.c directory.c duplicats.c error_ft.c execution_ft.c execution.c\
		list_cmd.c list_ft.c parse.c pipes.c pipex_cmd.c print_shell_tab.c pwd_cd.c redir_cmd.c shell_tab.c token_lab.c \
		exit_cmd.c expand_cd.c expand_ft.c expand_ft2.c export_cmd.c free_ft.c heredoc_cmd.c heredoc_ft.c label_ft.c \
		tokens.c tokens1.c tokens2.c unset_echo_cmd.c utils.c utils1.c get_next_line.c\

OBJS = $(SRCS:.c=.o)

LIBFT = ./libft/libft.a

all: $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $?

$(NAME): $(LIBFT) $(OBJS)
# # for mac
# 		$(CC) $(CFLAGS) -Ilibft $(LIBFT) $(OBJS) -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -o $@
#for linux
		$(CC) $(CFLAGS) $(SRCS) -Ilibft ./libft/libft.a -lreadline  -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include -o $@

leak_check:
	 valgrind --trace-children=yes --show-leak-kinds=all --leak-check=full --show-reachable=yes --track-fds=yes --error-limit=no --suppressions=./readline.supp ./minishell

$(LIBFT):
	@make -C libft

clean:
	@make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	@make fclean -C libft
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re