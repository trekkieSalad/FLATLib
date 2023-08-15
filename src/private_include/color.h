/* color.h - Definitions for color codes in terminal
 *
 *  FLATLib - Library of formal languages and automata theory.
 *  Copyright (C) 2023  Daniel José García Paz
 * 
 *      SPDX-License-Identifier: LGPL-2.1-or-later
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 2.1 of the License, or (at your option) any later version.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 *    USA or see <https://www.gnu.org/licenses/>.
 * 
 *  Author: Daniel José García Paz <daniel.garcia.paz@udc.es>
 */

#ifndef COLOR_H
#define COLOR_H

#define RESET               "\033[0m"

// Styles

#define BOLD                "\033[1m"
#define FAINT               "\033[2m"
#define ITALIC              "\033[3m"
#define UNDERLINE           "\033[4m"
#define BLINK               "\033[5m"
#define BLINK_FAST          "\033[6m"
#define INVERTED            "\033[7m"
#define HIDDEN              "\033[8m"
#define CROSS_OUT           "\033[9m"
#define DEFAULT             "\033[10m"

// Alternative styles

#define ALT_BOLD            "\033[11m"
#define ALT_FAINT           "\033[12m"
#define ALT_ITALIC          "\033[13m"
#define ALT_UNDERLINE       "\033[14m"
#define ALT_BLINK           "\033[15m"
#define ALT_BLINK_FAST      "\033[16m"
#define ALT_INVERTED        "\033[17m"
#define ALT_HIDDEN          "\033[18m"
#define ALT_CROSS_OUT       "\033[19m"

// Quit alternative styles

#define FRAKTUR             "\033[20m"
#define NO_BOLD             "\033[21m"
#define NO_FAINT_BOLD       "\033[22m"
#define NO_ITALIC           "\033[23m"
#define NO_UNDERLINE        "\033[24m"
#define NO_BLINK            "\033[25m"
#define NO_INVERTED         "\033[27m"
#define NO_HIDDEN           "\033[28m"
#define NO_CROSS_OUT        "\033[29m"

//Colors

#define BLACK               "\033[30m"
#define RED                 "\033[31m"
#define GREEN               "\033[32m"
#define YELLOW              "\033[33m"
#define BLUE                "\033[34m"
#define MAGENTA             "\033[35m"
#define CYAN                "\033[36m"
#define WHITE               "\033[37m"
#define DEFAULT_COLOR       "\033[39m"
#define COLOR(r, g, b)      "\033[38;2;" #r ";" #g ";" #b "m"

// Background colors

#define BG_BLACK            "\033[40m"
#define BG_RED              "\033[41m"
#define BG_GREEN            "\033[42m"
#define BG_YELLOW           "\033[43m"
#define BG_BLUE             "\033[44m"
#define BG_MAGENTA          "\033[45m"
#define BG_CYAN             "\033[46m"
#define BG_WHITE            "\033[47m"
#define BG_DEFAULT          "\033[49m"
#define BG_COLOR(r, g, b)   "\033[48;2;" #r ";" #g ";" #b "m"

// Bright colors

#define BRIGHT_BLACK        "\033[90m"
#define BRIGHT_RED          "\033[91m"
#define BRIGHT_GREEN        "\033[92m"
#define BRIGHT_YELLOW       "\033[93m"
#define BRIGHT_BLUE         "\033[94m"
#define BRIGHT_MAGENTA      "\033[95m"
#define BRIGHT_CYAN         "\033[96m"
#define BRIGHT_WHITE        "\033[97m"

// Bright background colors

#define BG_BRIGHT_BLACK     "\033[100m"
#define BG_BRIGHT_RED       "\033[101m"
#define BG_BRIGHT_GREEN     "\033[102m"
#define BG_BRIGHT_YELLOW    "\033[103m"
#define BG_BRIGHT_BLUE      "\033[104m"
#define BG_BRIGHT_MAGENTA   "\033[105m"
#define BG_BRIGHT_CYAN      "\033[106m"
#define BG_BRIGHT_WHITE     "\033[107m"

#endif // COLOR_H