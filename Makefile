# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tshimoda <tshimoda@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/23 15:02:10 by tshimoda          #+#    #+#              #
#    Updated: 2021/11/30 15:09:44 by tshimoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= fdf

AR= ar rc
RM= rm -rf

CC= gcc
CFLAGS= -Wall -Werror -Wextra -c -g
MFLAGS= -Lminilibx_macos -lmlx -framework OpenGL -framework Appkit

SDIR= sources
ODIR= objects

SRCS= fdf.c
OBJS= $(SRCS:.c=.o)

SFIX= $(addprefix $(SDIR)/, $(SRCS))
OFIX= $(addprefix $(ODIR)/, $(OBJS)) 

VPATH= $(SDIR)

$(ODIR)/%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(ODIR) $(OFIX)
	$(MAKE) -C ./libft
	$(MAKE) -C ./minilibx_macos
	$(CC) $(OFIX) $(MFLAGS) -lft -L./libft -o $(NAME)
	@echo "\033[1;32m 下田、徳太郎の鉄フレーム\033[0;39m"

all:	$(NAME)

$(ODIR):
		mkdir -p $(ODIR)

bonus: all

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(NAME) $(ODIR)

fclean: clean
	$(MAKE) fclean -C ./libft
	@echo "\033[1;34m make fclean done!\033[0;39m"
	
re:	clean all

.PHONY: all bonus clean flcean re