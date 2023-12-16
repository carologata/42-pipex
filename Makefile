NAME	:= pipex
CFLAGS	:= -Wextra -Wall -Werror -w -g3
LIBFT	:= ./libft

HEADERS	:= -I $(LIBFT)
LIBS	:= $(LIBFT)/libft.a

SRCS	:= pipex.c pipex_process.c pipex_exec.c pipex_utils.c
OBJS	:= ${SRCS:.c=.o}

all: libft $(NAME)

libft:
	@make -C $(LIBFT)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

bonus: libmlx libft $(NAME_BONUS)

clean:
	@rm -rf $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean

re: clean all

norm:
	norminette -R CheckForbiddenSourceHeader $(SRCS) $(SRCS_BONUS) ./include

.PHONY: all, clean, fclean, re, libft
