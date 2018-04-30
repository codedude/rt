# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: valentin <valentin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/04/30 11:47:50 by valentin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	rt
CC			=	clang

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	libft
ENVD		=	env
OBJECTSD	=	objects
PARSERD		=	parser
RENDERD		=	render
UTILSD		=	utils
LIBTPOOLD	=	libtpool
SDLD		=	sdl
GUID		=	gui
SDLLIBD		=	$(HOME)/.brew/lib -lSDL2
SDLINCD		=	$(HOME)/.brew/include/SDL2 -D_THREAD_SAFE

FILES		=	main.c render_test.c
FILES		+=	$(ENVD)/rt.c $(ENVD)/env.c \
				$(ENVD)/camera_set.c $(ENVD)/canvas_set.c \
				$(ENVD)/camera_get.c $(ENVD)/canvas_get.c
FILES		+=	$(UTILSD)/vec1.c $(UTILSD)/types.c $(UTILSD)/vec2.c \
				$(UTILSD)/matrix.c
FILES		+=	$(OBJECTSD)/objects.c $(OBJECTSD)/objects_queue.c \
				$(OBJECTSD)/objects_format.c \
				$(OBJECTSD)/objects_set1.c $(OBJECTSD)/objects_set2.c \
				$(OBJECTSD)/objects_set3.c
FILES		+=	$(PARSERD)/reader.c $(PARSERD)/parser.c \
				$(PARSERD)/parse_funs1.c $(PARSERD)/parse_funs2.c \
				$(PARSERD)/parse_funs3.c $(PARSERD)/parse_funs4.c \
				$(PARSERD)/parse_details.c $(PARSERD)/parse_data.c\
				$(PARSERD)/parse_type.c $(PARSERD)/parse_type_2.c
FILES		+=	$(RENDERD)/dispatch.c $(RENDERD)/rt.c $(RENDERD)/refraction.c\
				$(RENDERD)/perlin.c $(RENDERD)/perturbation.c \
				$(RENDERD)/intersect_paraboloid.c \
				$(RENDERD)/render_update.c $(RENDERD)/compute_color.c $(RENDERD)/reflexion.c
FILES		+=	$(RENDERD)/intersect_sphere.c $(RENDERD)/intersect_plane.c \
				$(RENDERD)/intersect_cone.c $(RENDERD)/intersect_cylinder.c\
				$(RENDERD)/solve_quadra.c $(RENDERD)/trace.c
FILES		+=	$(SDLD)/sdl.c $(GUID)/gtk.c

SRCS		=	$(addprefix $(SRCD)/, $(FILES))
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

GTK_CFLAGS	=	$(shell pkg-config --cflags gtk+-3.0)
GTK_LDFLAGS	=	$(shell pkg-config --libs gtk+-3.0)
CFLAGS		+=	-O3 -flto -march=native -mtune=native -std=c11 -pedantic \
				-g $(GTK_CFLAGS) \
				-I$(LIBFTD)/includes -I$(LIBTPOOLD)/includes -I$(INCD) \
				-I$(SDLINCD)
LDFLAGS		+=	-Wextra -Wall -Wno-unused-result
LDLIBS		+=	-L$(LIBFTD) -lft -lm -L$(LIBTPOOLD) -ltpool \
				-L$(SDLLIBD) -lsdl2 $(GTK_LDFLAGS)

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTD)
	make -C $(LIBTPOOLD)
	$(CC) $(CFLAGS) -o $(NAME) $^ $(LDLIBS)
	@echo "rt - compiled"

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	make -C $(LIBFTD) clean
	make -C $(LIBTPOOLD) clean
	@rm -f $(OBJS)
	@echo "rt - cleaned"

fclean: clean
	make -C $(LIBFTD) __fclean
	make -C $(LIBTPOOLD) __fclean
	@rm -f $(NAME)
	@echo "rt - lib cleaned"

re: fclean all

rer:
	@rm -f $(NAME)
	@rm -f $(OBJS)
	make $(NAME)
