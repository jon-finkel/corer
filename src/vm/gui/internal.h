/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm/gui/internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfinkel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 16:16:50 by nfinkel           #+#    #+#             */
/*   Updated: 2018/03/31 18:54:36 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NC_INTERNAL_H
# define NC_INTERNAL_H

# include <ncurses.h>

/*
** for signal / SIGWINCH
*/
# include <signal.h>

# include "corewar.h"

# define DGTS "0123456789abcdefg"

# define STATS_PAUSED 0
# define STATS_CYCLEL 1
# define STATS_CYCLE 2
# define STATS_PROCS 3
# define STATS_CYCLE_TO_DIE 4
# define STATS_CYCLE_DELTA 5
# define STATS_NBR_LIVE 6
# define STATS_MAX_CHECKS 7
# define STATS_STEPI 8
# define STATS_PLAYERS 9

typedef int		(t_keyh)(int ch);

extern WINDOW	*g_wboard;
extern WINDOW	*g_wstats;
extern WINDOW	*g_wprocs;
extern int		g_cyclel;
extern int		g_running;
extern int		g_stepi;
extern t_proc	*g_uiproc;

typedef struct	s_cell
{
	uint8_t		color;
	uint8_t		lifetime;
	uint8_t		attrs;
	uint8_t		print;
}				t_cell;

extern t_cell	g_map[MEM_SIZE];

int				gui_onkey(int ch);
void			gui_stats(int id, ...);
void			gui_drawboard(void);
void			gui_drawstats(void);
int				gui_cellattrs(t_cell *cell);

#endif
