# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 20:54:07 by mjacquet          #+#    #+#              #
#    Updated: 2022/04/24 04:45:52 by mjacquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

# FOLDERS

SRCSFOLDER		=	srcs/

OBJSFOLDER		=	OBJS/

INCLUDESFOLDER 	= 	includes/

# SOURCES

SRC				=	main.c \
					utils.c \
					utils_bis.c \
					env.c \
					splitting.c \
					splitting_creat_tab.c \
					splitting_count.c \
					command.c \
					token.c \
					builtins/unset.c \
					builtins/cd.c \
					builtins/cd2.c \
					builtins/cd3.c \
					builtins/echo.c \
					builtins/echo2.c \
					builtins/export.c \
					builtins/export_utils.c \
					builtins/tri.c \
					builtins/builtins_exit.c \
					cmd_box.c \
					new_exec.c \
					exit.c \
					exec_utils.c			\
					exec.c					\
					expand.c				\
					handler.c				\
					sublist.c				\
					redir.c

SRCS			=	$(addprefix $(SRCSFOLDER), $(SRC))

INCLUDES		=	minishell.h

# COMPILATION AND LINKING

OBJS 			=	${SRC:%.c=$(OBJSFOLDER)%.o}

$(OBJSFOLDER)%.o	:	$(SRCSFOLDER)%.c
					$(CC) $(CFLAGS) -MD -c $< -o $@ -I $(INCLUDESFOLDER)

RM				=	rm -rf

CC				=	clang

CFLAGS			=	-Wall -Wextra -Werror  -g #-g3  -fsanitize=address

LFLAGS			=	-lreadline

.PHONY: all
all			:	$(OBJSFOLDER) $(cobjects) $(NAME) includes/minishell.h

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $@ -I $(INCLUDESFOLDER) $(LFLAGS)


.PHONY: fsanitize
fsanitize	:	$(SRCS)
				$(CC) $(CFLAGS) -o1 -g3 -fsanitize=address $(SRCS) -o $(NAME) -I $(INCLUDESFOLDER) $(LFLAGS)


.PHONY: clean
clean		:
		    	${RM} ${OBJS}
				${RM} ${OBJSFOLDER}


.PHONY: fclean
fclean		:
				make clean
				$(RM) $(NAME)


.PHONY: re
re			:
				make fclean
				make all


$(OBJSFOLDER)	:
				mkdir -p $@
				mkdir OBJS/builtins

-include $(OBJS:.o=.d)
