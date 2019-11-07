/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 17:17:11 by anmauffr          #+#    #+#             */
/*   Updated: 2019/10/04 15:59:10 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "../../Libft/includes/libft.h"
# include "op.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <ncurses.h>

# define DEF				"\033[0m"

# define BOLD				"\033[1m"

# define RED				"\033[31m"
# define GRE				"\033[32m"
# define YEL				"\033[33m"
# define BLU				"\033[34m"
# define MAG				"\033[35m"
# define CYA				"\033[36m"

# define BACK_RED			"\033[41m"
# define BACK_GRE			"\033[42m"
# define BACK_YEL			"\033[43m"
# define BACK_BLU			"\033[44m"
# define BACK_MAG			"\033[45m"
# define BACK_CYA			"\033[46m"

# define ERROR_OPEN			0
# define ERROR_READ			1
# define ERROR_CLOSE		2
# define ERROR_MAGIC		3
# define ERROR_LABEL		4
# define ERROR_OPTION		5
# define ERROR_NB_LIVE		6
# define ERROR_NAME_LEN		7
# define ERROR_COMM_LEN		8
# define ERROR_PROG_SIZE	9
# define EXIT_DUMP			10
# define ERROR_MALLOC		11

typedef struct	s_proc
{
	int				creation;
	int				alive;
	int				carry;
	int				last_live;
	int				number;
	t_header		head;
	unsigned int	wait;
	unsigned int	pc;
	unsigned int	n_champ;
	unsigned int	r[REG_NUMBER];
	unsigned char	opcode;
	struct s_proc	*next;
}				t_proc;

typedef	struct	s_visu
{
	int				cps;
	WINDOW			*arena;
	WINDOW			*hud;
	WINDOW			*desc;
	WINDOW			*winner;
}				t_visu;

typedef struct	s_vm
{
	int				nb_proc;
	int				nb_champ;
	int				fd[MAX_PLAYERS];
	int				tab_wait[17];
	long			option_dump;
	long			option_verbose;
	long			option_visu;
	long			option_visu_d;
	long			option_color;
	long			option_i;
	t_proc			*proc;
	t_proc			*beg;
	t_visu			visu;
	unsigned int	cycle;
	unsigned int	cycle_to_die;
	unsigned int	total_to_die;
	unsigned int	nb_check_cycle;
	unsigned int	nb_live_champ[MAX_PLAYERS];
	unsigned char	arena[MEM_SIZE][2];
}				t_vm;

typedef void	(*t_opcode)(t_vm *, unsigned int *);

void			t_opcode_set(t_opcode t_opcode_array[17]);
void			tab_wait_set(t_vm *vm);

void			ft_error(int err, int nb_line, t_vm *vm);
void			ft_print_vm(t_vm vm);
void			ft_put_instruct(int pc, unsigned int arg_value[3],
					unsigned int arg_size[3]);
void			ft_init_vm(t_vm *vm);
void			ft_cycle_to_die(t_vm *vm);

void			ft_wait(t_vm *vm, unsigned char opcode);

void			ft_dead_proc(t_vm *vm, t_proc **current);
void			ft_reverse_list(t_proc **beg);
unsigned int	idx_mod(unsigned int realpc, unsigned int index);

void			ft_parsing(t_vm *vm, char **av);

int				recup_opc(unsigned char opc, unsigned int *arg_size,
					int size_dir, int arg);
int				ft_opcode(t_vm *vm, unsigned int *arg_value,
					unsigned int *arg_size, int size_dir);

void			ft_args(int ac, char **av, t_vm *vm, char *tab[5]);

void			op_live(t_vm *vm, unsigned int *pc);
void			op_ld(t_vm *vm, unsigned int *pc);
void			op_st(t_vm *vm, unsigned int *pc);
void			op_add(t_vm *vm, unsigned int *pc);
void			op_sub(t_vm *vm, unsigned int *pc);
void			op_and(t_vm *vm, unsigned int *pc);
void			op_or(t_vm *vm, unsigned int *pc);
void			op_xor(t_vm *vm, unsigned int *pc);
void			op_zjmp(t_vm *vm, unsigned int *pc);
void			op_ldi(t_vm *vm, unsigned int *pc);
void			op_sti(t_vm *vm, unsigned int *pc);
void			op_fork(t_vm *vm, unsigned int *pc);
void			op_lld(t_vm *vm, unsigned int *pc);
void			op_lldi(t_vm *vm, unsigned int *pc);
void			op_lfork(t_vm *vm, unsigned int *pc);
void			op_aff(t_vm *vm, unsigned int *pc);

void			free_chaine(t_proc *proc);
int				ft_list_lenght(t_proc *beg_real);
void			ft_print_dump(t_vm *vm);
void			ft_introduce(t_vm *vm);
void			ft_victory(t_vm *vm, t_proc *current);
void			ft_invert_byte(unsigned int *val);
int				ft_list_count_vm(t_proc *begin_list);

void			ft_init_visu(t_vm *vm);
void			get_key(t_vm *vm);
void			visual_every_cycle(t_vm *vm);
void			refresh_pc(t_vm *vm);
void			refresh_process(t_vm *vm);
void			refresh_live(t_vm *vm, int barre);
void			refresh_cycle_to_die(t_vm *vm);
char			*get_hexa(int nb);
void			init_visual_hud(t_vm *vm);
void			init_description(t_vm *vm);
void			ft_visu_wait(t_vm *vm);
void			ft_visu_d_message(t_vm *vm, char *str);
void			add_description(t_vm *vm);
void			ft_victory_visu(t_vm *vm, t_proc *winner);

#endif
