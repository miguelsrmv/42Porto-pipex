# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 09:55:46 by mde-sa--          #+#    #+#              #
#    Updated: 2023/08/23 18:08:12 by mde-sa--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=   pipex

CC      = 	cc

CFLAGS  =   -Wall -Wextra -Werror

SRCDIR	=	src

INCDIR	=   includes

SRC		=	main.c

LIBS 	=   -L./ft_printf -lft_printf -L./libft -lft -L./get_next_line -lget_next_line

OBJS	= 	$(addprefix $(SRCDIR)/, $(SRC:.c=.o))

RM      = 	rm -rf


all: libft ft_printf get_next_line $(NAME) 

$(NAME): $(OBJS)
	@ $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) 

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h
	@ $(CC) $(CFLAGS) -c $< -I $(INCDIR) -I ./libft -I ./ft_printf -I ./get_next_line -o $@

libft:
	@cd libft && make -s && make -s clean

ft_printf:
	@cd ft_printf && make -s && make -s clean

get_next_line:
	@cd get_next_line && make -s && make -s clean

clean:
	@ $(MAKE) -s -C ./libft clean
	@ $(MAKE) -s -C ./ft_printf clean
	@$(MAKE) -s -C ./get_next_line clean
	@ $(RM) $(OBJS)

fclean: clean
	@ $(MAKE) -s -C ./libft fclean
	@ $(MAKE) -s -C ./ft_printf fclean
	@ $(MAKE) -s -C ./get_next_line fclean
	@ $(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft ft_printf get_next_line