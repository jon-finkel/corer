/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nc/init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 18:15:51 by alucas-           #+#    #+#             */
/*   Updated: 2018/03/12 18:15:53 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal.h"

#define DIGITS "0123456789abcdefg"

WINDOW			*g_wboard;
WINDOW			*g_wstats;

static float	ft_sqrt7(float x)
{
	unsigned int i;

	i = *(unsigned int*) &x;
	i += 127 << 23;
	i >>= 1;
	return (*(float*)&i);
}

static void		nc_colors(void)
{
	start_color();
	init_color(COLOR_WHITE, 0x12c, 0x12c, 0x12c);
	init_pair(0x2a, 0x8, COLOR_BLACK);
	init_pair(0, COLOR_WHITE, COLOR_RED);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_WHITE, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_WHITE);
	init_pair(6, COLOR_GREEN, COLOR_WHITE);
	init_pair(7, COLOR_BLUE, COLOR_WHITE);
	init_pair(8, COLOR_RED, COLOR_WHITE);
	init_pair(9, COLOR_WHITE, COLOR_WHITE);
	init_pair(10, COLOR_WHITE, COLOR_WHITE);
	init_pair(11, COLOR_WHITE, COLOR_GREEN);
	init_pair(12, COLOR_WHITE, COLOR_BLUE);
	init_pair(13, COLOR_WHITE, COLOR_GREEN);
	init_pair(14, COLOR_WHITE, COLOR_WHITE);

}

static int		nc_draw(t_cw *cw)
{
	int mx;
	int my;
	int x;
	int y;

	(void)cw;
	mx = getmaxx(g_wboard);
	my = getmaxy(g_wboard);
	x = 2;
	y = 1;
	for (int i = 0; i < MEM_SIZE; ++i)
	{
		if (y + 1 >= my)
			break ;
		if (x + 4 > mx)
		{
			x = 2;
			++y;
		}
		mvwaddch(g_wboard, y, x++, (chtype)DIGITS[(cw->mem[i] / 16) % 16]);
		mvwaddch(g_wboard, y, x++, (chtype)DIGITS[cw->mem[i] % 16]);
		mvwaddch(g_wboard, y, x++, ' ');
	}
	wrefresh(g_wboard);
	return (YEP);
}

int				cw_nc_init(t_cw *cw)
{
	int sq;

	if (!cw->opt.n)
		return (YEP);
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	curs_set(FALSE);
	nc_colors();
	sq = (int)ft_sqrt7(MEM_SIZE);
	if (!(g_wboard = subwin(stdscr, sq + 2, sq * 3 + 3, 0, 0)))
		return (WUT);
	if (!(g_wstats = subwin(stdscr, sq + 2, 50, 0, sq * 3 + 2)))
		return (WUT);
	wattr_on(g_wboard, 0x242a00, 0);
	box(g_wboard, 0x2a, 0x2a);
	wattr_off(g_wboard, 0x242a00, 0);
	wattr_on(g_wstats, 0x242a00, 0);
	box(g_wstats, 0x2a, 0x2a);
	wattr_off(g_wstats, 0x242a00, 0);
	wrefresh(g_wstats);
	return (nc_draw(cw));
}

