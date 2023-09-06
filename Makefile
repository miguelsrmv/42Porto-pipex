# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mde-sa-- <mde-sa--@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/23 09:55:46 by mde-sa--          #+#    #+#              #
#    Updated: 2023/09/06 09:59:19 by mde-sa--         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=   pipex

CC      = 	cc

CFLAGS  =   -g -Wall -Wextra -Werror 

SRCDIR	=	src/mandatory

SRCBONDIR = src/bonus

INCDIR	=   includes

LIBFTDIR =  src/libft

SRC		=	main.c commands.c ft_command_split.c manage_infile.c free_memory.c

SRCBON	=	main_bonus.c ft_command_split_bonus.c manage_infile_bonus.c \
			free_memory_bonus.c process_bonus.c commands_bonus.c

LIBS 	=   -L$(LIBFTDIR) -lft

OBJS	= 	$(addprefix $(SRCDIR)/, $(SRC:.c=.o))

OBJSBON =   $(addprefix $(SRCBONDIR)/, $(SRCBON:.c=.o))

RM      = 	rm -rf


all: libft $(NAME) 

$(NAME): $(OBJS)
	@ $(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) 

bonus: $(OBJSBON) libft
	@ $(CC) $(CFLAGS) $(OBJSBON) $(LIBS) -o $(NAME)

$(SRCDIR)/%.o: $(SRCDIR)/%.c $(INCDIR)/*.h
	@ $(CC) $(CFLAGS) -c $< -I $(INCDIR) -I $(LIBFTDIR) -o $@

$(SRCBONDIR)/%.o: $(SRCBONDIR)/%.c $(INCDIR)/*.h
	@ $(CC) $(CFLAGS) -c $< -I $(INCDIR) -I $(LIBFTDIR) -o $@

libft:
	@cd $(LIBFTDIR) && make -s && make -s clean

clean:
	@ $(MAKE) -s -C $(LIBFTDIR) clean
	@ $(RM) $(OBJS) $(OBJSBON)

fclean: clean
	@ $(MAKE) -s -C $(LIBFTDIR) fclean
	@ $(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re libft