/* flatMem.h
 *
 * FLATLib - Library of formal languages and automata theory algorithms.
 * Copyright (C) 2023  Daniel José García Paz
 * 
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 * This library  is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 * 
 * Author: Daniel José García Paz <daniel.garcia.paz@udc.es>
 */

#ifndef FLAT_MEM_H
#define FLAT_MEM_H

#include <stdlib.h>
#include <flatPointer.h>

/**
 * @brief Frees the memory allocated for a flat pointer.
 * 
 * Frees the memory allocated for a flat pointer. If the flat pointer is NULL,
 * nothing is done.
 * 
 * @param x Flat pointer to be freed.
 */
void flat_free(flat_pointer x);

#endif