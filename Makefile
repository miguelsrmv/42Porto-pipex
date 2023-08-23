# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 09:55:46 by mde-sa--          #+#    #+#              #
#    Updated: 2023/08/23 11:28:45 by mde-sa--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=   pipex

CC      = 	cc

CFLAGS  =   -Wall -Wextra -Werror

SRCDIR	=	src

INCDIR	=   includes

SRC		=	main.c

LIBS 	=   -L ./libft -lft -L./ft_printf -lftprintf -L./get_next_line -lget_next_line

OBJS	= 	$(addprefix $(SRCDIR)/, $(SRC:.c=.o))

RM      = 	rm -rf


all: libft ft_printf get_next_line $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) 

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h
	$(CC) $(CFLAGS) -c $< -I $(INCDIR) -I ./libft -I ./ft_printf -I ./get_next_line -o $@

libft:
	$(MAKE) -C ./libft

ft_printf:
	$(MAKE) -C ./ft_printf

get_next_line:
	$(MAKE) -C ./get_next_line

clean:
	$(MAKE) -C ./libft clean
	$(MAKE) -C ./ft_printf clean
	$(MAKE) -C ./get_next_line clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C ./libft fclean
	$(MAKE) -C ./ft_printf fclean
	$(MAKE) -C ./get_next_line fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re