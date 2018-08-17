# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syamada <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/06 21:25:07 by syamada           #+#    #+#              #
#    Updated: 2018/08/17 11:36:41 by syamada          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= gcc
CFLAGS		:= -Wall -Werror -Wextra
DEBUG		:= -g
SANITIZER	:= -fsanitizer=address

LIB			:= libft.a
LIBDIR		:= libft

SRCDIR		:= srcs
INCDIR		:= includes

LS			:= ft_ls
LSSRC		:= $(addprefix $(SRCDIR)/, ft_ls.c check_option.c sort_funcs.c \
						error_exit.c get_info.c get_filetype.c bubble_sort.c \
						data_utils.c print_funcs.c data_handlers.c)

#colors
COM_COLOR	:= \033[0;34m
OK_COLOR	:= \033[0;32m
EXEC_COLOR	:= \033[1;32m
DEBUG_COLOR	:= \033[0;33m
NO_COLOR	:= \033[m

.PHONY: all
all: $(LS)

$(LS): $(LIBDIR) $(LIBDIR)/$(LIB)
	@printf "%b" "$(NO_COLOR)Creating $(EXEC_COLOR)$@"
	@$(CC) -o $@ $(CFLAG) $(LSSRC) -I$(INCDIR) -L$< -lft
	@printf "%b" " ✔\n"

$(LIBDIR)/$(LIB):
	@make -C $(LIBDIR)

.PHONY: clean
clean:
	@make -C $(LIBDIR) clean

.PHONY: fclean
fclean:
	@make -C $(LIBDIR) fclean
	@printf "%b" "$(NO_COLOR)Removing $(LS)...\n"
	@rm -f $(LS)
	@printf "%b" "$(OK_COLOR)[OK]: $(NO_COLOR)$(LS) were successfully removed\n"

.PHONY: re
re: fclean all

.PHONY: debug
debug:
	@rm -f d$(LS)
	@make d$(LS)

d$(LS): $(LIBDIR) $(LIBDIR)/$(LIB)
	@printf "%b" "$(DEBUG_COLOR)[DEBUG MODE] $(NO_COLOR)Creating $(EXEC_COLOR)$@"
	@$(CC) -o $@ $(CFLAG) $(DEBUG) $(LSSRC) -I$(INCDIR) -L$< -lft
	@printf "%b" " ✔\n"

.PHONY: cleandebug
cleandebug:
	@rm -rf d$(LS).dSYM
	@rm -f d$(LS)

.PHONY: rels
rels:
	@printf "%b" "Quick recompile for $(CHECKER)\n"
	@rm -f $(LS)
	@make $(LS)
