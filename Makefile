SHELL				=	/bin/zsh

# Executable name
NAME_VM				=	corewar
NAME_ASM			=	asm

# Compilation mode
WALL				=	yes
WEXTRA				=	yes
WERROR				=	yes
FSANITIZE			=	no
DEBUG				=	no
O2					=	yes

CC					:=	gcc
GEN					:=	"Generation in mode"

ifeq ($(WALL), yes)
	CC				:=	$(CC) -Wall
	GEN				:=	$(GEN) all
endif

ifeq ($(WEXTRA), yes)
	CC				:=	$(CC) -Wextra
	GEN				:=	$(GEN) extra
endif

ifeq ($(WERROR), yes)
	CC				:=	$(CC) -Werror
	GEN				:=	$(GEN) error
endif

ifeq ($(FSANITIZE), yes)
	CC				:=	$(CC) -fsanitize=address
	GEN				:=	$(GEN) sanitize
endif

ifeq ($(DEBUG), yes)
	CC				:=	$(CC) -g
	GEN				:=	$(GEN) debug
endif

ifeq ($(O2),yes)
	CC				:=	$(CC) -O2
	GEN				:=	$(GEN) O2
endif

ifeq ($(GEN), "Generation in mode")
	GEN				:=	$(GEN) no flags
endif

# Name
SRC_NAME_VM		=	arg.c					\
					main.c					\
					list.c					\
					error.c					\
					utiles.c				\
					opcode.c				\
					utiles2.c				\
					parsing.c				\
					idx_mod.c				\
											\
					opcode/ld.c				\
					opcode/st.c				\
					opcode/or.c				\
					opcode/add.c			\
					opcode/sub.c			\
					opcode/and.c			\
					opcode/xor.c			\
					opcode/ldi.c			\
					opcode/sti.c			\
					opcode/lld.c			\
					opcode/aff.c			\
					opcode/live.c			\
					opcode/zjmp.c			\
					opcode/fork.c			\
					opcode/lldi.c			\
					opcode/lfork.c			\
											\
					visu/input.c			\
					visu/init_desc.c		\
					visu/refresh_hud.c		\
					visu/refresh_live.c		\
					visu/init_visu_hud.c	\
					visu/init_visu_arena.c

SRC_NAME_ASM	=	asm.c					\
					list.c					\
					file.c					\
					ft_is.c					\
					error.c					\
					header.c				\
					utiles.c				\
					ft_struct.c				\
					ft_instru.c				\
					ft_output.c				\
					ft_one_arg.c 			\
					ft_get_line.c			\
					ft_two_args.c 			\
					ft_dispatch.c			\
					ft_is_labels.c			\
					ft_is_direct.c			\
					ft_three_args.c 		\
					ft_gnl_parsing.c		\
					ft_calcule_val.c		\
					ft_index_label.c		\
					ft_set_args_to_tabs.c

LIBFT_NAME		=	libft.a

# Path
SRC_PATH_VM		=	./Vm/src/
OBJ_PATH_VM 	=	./Vm/obj/
INC_PATH_VM		=	./Vm/include/
SRC_PATH_ASM	=	./Assembleur/src/
OBJ_PATH_ASM	=	./Assembleur/obj/
INC_PATH_ASM	=	./Assembleur/include/
LIBFT_PATH		=	./Libft/

# Name + Path
SRC_VM			=	$(addprefix	$(SRC_PATH_VM),		$(SRC_NAME_VM))
OBJ_VM			=	$(patsubst	$(SRC_PATH_VM)%.c,	$(OBJ_PATH_VM)%.o,	$(SRC_VM))
SRC_ASM			=	$(addprefix	$(SRC_PATH_ASM),	$(SRC_NAME_ASM))
OBJ_ASM			=	$(patsubst	$(SRC_PATH_ASM)%.c,	$(OBJ_PATH_ASM)%.o,	$(SRC_ASM))

# Text format
_DEF			=	$'\033[0m
_END			=	$'\033[0m
_GRA			=	$'\033[1m
_SOU			=	$'\033[4m
_CLI			=	$'\033[5m
_SUR			=	$'\033[7m

# Colors
_BLA			=	$'\033[30m
_RED			=	$'\033[31m
_GRE			=	$'\033[32m
_YEL			=	$'\033[33m
_BLU			=	$'\033[34m
_PUR			=	$'\033[35m
_CYA			=	$'\033[36m
_WHI			=	$'\033[37m

# Background
_IBLA			=	$'\033[40m
_IRED			=	$'\033[41m
_IGRE			=	$'\033[42m
_IYEL			=	$'\033[43m
_IBLU			=	$'\033[44m
_IPUR			=	$'\033[45m
_ICYA			=	$'\033[46m
_IWHI			=	$'\033[47m

all: $(NAME_VM) $(NAME_ASM)

$(LIBFT_PATH)$(LIBFT_NAME):
	@make -C $(LIBFT_PATH) -j8
	@echo ""

$(NAME_VM): $(LIBFT_PATH)$(LIBFT_NAME) $(OBJ_VM)
	@echo "\nVm : $(GEN)"
	@echo "\n$(_WHI)====================================================$(_END)"
	@echo "$(_YEL)		COMPILING $(NAME_VM)$(_END)"
	@echo "$(_WHI)====================================================$(_END)"
	@$(CC) -o $(NAME_VM) $(OBJ_VM) $(LIBFT_PATH)/$(LIBFT_NAME) -lncurses
	@echo "\n$(_WHI)$@\t$(_END)$(_GRE)[OK]\n$(_END)"

$(OBJ_PATH_VM)%.o: $(SRC_PATH_VM)%.c
	@mkdir -p $(OBJ_PATH_VM)
	@mkdir -p $(OBJ_PATH_VM)opcode/
	@mkdir -p $(OBJ_PATH_VM)visu/
	@$(CC) -I $(INC_PATH_VM) -I $(LIBFT_PATH)include/ \
		-I $(INC_PATH_VM) -c $< -o $@
	@echo "$(_END)$(_GRE)[OK]\t$(_YEL)\t"	\
		"COMPILE :$(_END)$(_WHI)\t$<"

$(NAME_ASM): $(LIBFT_PATH)$(LIBFT_NAME) $(OBJ_ASM)
	@echo "\nAsm : $(GEN)"
	@echo "\n$(_WHI)====================================================$(_END)"
	@echo "$(_YEL)		COMPILING $(NAME_ASM)$(_END)"
	@echo "$(_WHI)====================================================$(_END)"
	@$(CC) -o $(NAME_ASM) $(OBJ_ASM) $(LIBFT_PATH)/$(LIBFT_NAME)
	@echo "\n$(_WHI)$@\t$(_END)$(_GRE)[OK]\n$(_END)"

$(OBJ_PATH_ASM)%.o: $(SRC_PATH_ASM)%.c
	@mkdir -p $(OBJ_PATH_ASM)
	@$(CC) -I $(INC_PATH_ASM) -I $(LIBFT_PATH)include/ \
		-I $(INC_PATH_ASM) -c $< -o $@
	@echo "$(_END)$(_GRE)[OK]\t$(_YEL)\t"	\
		"COMPILE :$(_END)$(_WHI)\t$<"

clean:
	@rm -rf $(OBJ_PATH_VM) 2> /dev/null || true
	@echo "$(_YEL)Remove :\t$(_RED)" $(LDFLAGS)$(OBJ_PATH_VM)"$(_END)"
	@rm -rf $(OBJ_PATH_ASM) 2> /dev/null || true
	@echo "$(_YEL)Remove :\t$(_RED)" $(LDFLAGS)$(OBJ_PATH_ASM)"$(_END)"
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -f $(NAME_VM)
	@echo "$(_YEL)Remove :\t$(_RED)" $(LDFLAGS)$(NAME_VM)
	@rm -f $(NAME_ASM)
	@echo "$(_YEL)Remove :\t$(_RED)" $(LDFLAGS)$(NAME_ASM)
	@rm -f $(LIBFT_PATH)$(LIBFT_NAME)
	@echo "$(_YEL)Remove :\t$(_RED)" $(LIBFT_PATH)$(LIBFT_NAME)"$(_END)"

re: fclean all

.PHONY: all clean fclean re
