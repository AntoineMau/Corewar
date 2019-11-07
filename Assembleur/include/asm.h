/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 11:42:27 by judumay           #+#    #+#             */
/*   Updated: 2019/09/23 13:31:05 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "../../Libft/includes/libft.h"
# include "op.h"

/*
** COLOR
*/

# define DEF						"\033[0m"
# define RED						"\033[0;31m"
# define B_RED						"\033[1;31m"
# define GRE						"\033[0;32m"
# define B_GRE						"\033[1;32m"
# define YEL						"\033[0;33m"
# define B_YEL						"\033[1;33m"
# define BLU						"\033[0;34m"
# define B_BLU						"\033[1;34m"
# define MAG						"\033[0;35m"
# define B_MAG						"\033[1;35m"
# define CYA						"\033[0;36m"
# define B_CYA						"\033[1;36m"

/*
** OPCODE
*/

# define LIVE						0x01
# define LD							0x02
# define ST							0x03
# define ADD						0x04
# define SUB						0x05
# define AND						0x06
# define OR							0x07
# define XOR						0x08
# define ZJMP						0x09
# define LDI						0x0a
# define STI						0x0b
# define FORK						0x0c
# define LLD						0x0d
# define LLDI						0x0e
# define LFORK						0x0f
# define AFF						0x10

/*
** ERROR
*/

# define ERROR_OPEN					1
# define ERROR_READ					2
# define ERROR_WRITE				3
# define ERROR_CLOSE				4
# define ERROR_MALLOC				5
# define ERROR_NB_ARG				6
# define ERROR_HEADER				7
# define ERROR_LEN_COMM				8
# define ERROR_LEN_NAME				9
# define ERROR_HEAD_COMM			10
# define ERROR_HEAD_NAME			11
# define ERROR_MULT_COMM			12
# define ERROR_MULT_NAME			13
# define ERROR_WRONG_FILE			14
# define ERROR_HEAD_NO_COMM			15
# define ERROR_HEAD_NO_NAME			16
# define ERROR_BAD_LABEL			17
# define ERROR_BAD_INSTRU_NAME		18
# define ERROR_BAD_PARAM_NAME		19
# define ERROR_BAD_COMMA			20
# define ERROR_BAD_PARAM_NB			21
# define ERROR_BAD_LABEL_NAME		22
# define ERROR_NO_CODE				23
# define ERROR_LENGHT_NUMBER		24
# define ERROR_NEWLINE				25

typedef struct		s_label
{
	char			*name;
	int				pos;

	struct s_label	*next;
}					t_label;

typedef struct		s_asm
{
	char			*label[3];
	char			*params[3];

	int				param_size[3];
	int				pos_label[3];
	int				param_code[3];
	int				ocp;
	int				size;
	int				opcode;
	int				line;
	int				index;

	struct s_asm	*next;
}					t_asm;

typedef struct		s_struct
{
	int				size;
	int				nameok;
	int				commentok;
	int				index;
	int				nfo;
	int				cfo;

	int				tabsize;
	int				i;
	int				j;
	int				k;
	int				ac;
	int				error;
	int				nb_line;
	int				name;
	int				comment;
	int				fd;
	int				ret;
	int				sav_pos;
	int				last_line_valid;
	int				check_last_line_valid;

	long long		val;

	char			**av;
	char			**tab_line;
	char			**tab;

	char			*nsline;
	char			*line;
	unsigned char	*str;

	t_asm			*beg;
	t_asm			*first;
	t_label			*label;
	t_label			*first_label;
}					t_struct;

void				ft_get_first_line_name(t_struct *s, t_header *header);
void				ft_get_others_line_name(t_struct *s, t_header *header);
void				ft_get_first_line_comm(t_struct *s, t_header *header);
void				ft_get_others_line_comment(t_struct *s, t_header *header);

long long			ft_calcule_val(t_struct *s, int i);

void				ft_parcing(t_header *header, t_struct *s);

int					ft_is_instru(char *nsline, int pos);
int					ft_is_separator(char *nsline, int pos);
int					ft_is_reg(char *nsline, int pos);
int					ft_is_comment(char *nsline, int pos);

int					ft_is_direct(char *nsline, int pos, t_struct *s);
int					ft_is_direct_digit(char *nsline, int pos, int pos2
						, t_struct *s);
int					ft_is_lab(char *nsline, int pos, t_struct *s);

int					ft_first_is_label(char *str, t_struct *s);
int					ft_is_label_chars(char c, t_struct *s);

int					ft_read_labelin(t_struct *s, int last, int save, int octet);
int					ft_check_value(t_struct *s, int last, int j);
int					ft_check_index(t_struct *s, int i, int last);

int					ft_check_direct(t_struct *s, int i, int last, int octet);
int					ft_check_registre(t_struct *s, int i, int last);

int					ft_dispatch(t_struct *s, int j, int i, unsigned char *str);

void				ft_output(char *name_asm, t_header header, t_struct *s
						, unsigned char *com);
void				ft_make_line_dispatch(t_struct *s, int *j, int *i
						, unsigned char *str);
void				ft_make_line(t_struct *s, unsigned char *str);

void				ft_three_args(t_struct *s, int i);

void				ft_two_args(t_struct *s, int i);

int					ft_check_more(t_struct *s, int nb, int i);
void				ft_one_arg(t_struct *s, int i);

void				ft_set_struct_core(t_struct *s, int ac, char **av);

int					ft_is_label(t_struct *s);

void				ft_finish(t_struct *s);
void				ft_error(int err, t_struct *s, char **str);

int					ft_ocp(int a, int b, int c);
void				ft_check_arg(t_struct *s);
void				ft_init_header(t_header *header);
void				ft_invert_byte(unsigned int *val);

void				ft_check_syntax(t_struct *s);

void				ft_check_header(t_struct *s, t_header *header);
int					ft_find_occu(char *str);

t_label				*ft_lst_create_label(t_struct *s);
t_asm				*ft_lst_create(t_struct *s);

char				**ft_set_args_to_tabs(char *line, t_struct *s);
int					ft_chck(char c);

#endif
