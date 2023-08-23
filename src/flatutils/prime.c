/* prime.c - Functions for primality testing and prime number generation.
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

/**
 * SECTION: prime_functions
 * @title: Prime functions
 * @short_description: Functions for primality testing and prime number
 *      generation.
 * 
 * This module contains the implementation of functions for generating prime 
 * values for set sizes. It implements the Miller-Rabin primality test.
 * 
 * The Miller-Rabin test is based on Fermat's little theorem, which states that
 * if 'p' is a prime number, then for any integer 'a', the number 'a^p - a' is
 * an integer multiple of 'p'. The Miller-Rabin test uses this theorem to
 * determine if a number is prime or not.
 * 
 * On this way, the Miller-Rabin primality test is a probabilistic algorithm 
 * that determines whether a number is prime or not using a fixed number of 
 * iterations. This makes the algorithm highly efficient for numbers of any 
 * number of digits. Thus, it becomes feasible to generate prime numbers with 
 * a cyclomatic complexity of O(k log^3 n), where 'k' represents the number of 
 * iterations (30 in this context), and 'n' is the number of digits in the 
 * tested number.
 * 
 * It's important to note that the Miller-Rabin test is a probabilistic 
 * algorithm. Consequently, there is a possibility that the algorithm could 
 * label a number as prime when it is not. However, the likelihood of this 
 * occurrence is quite low. If the algorithm returns a non-prime number, it 
 * wouldn't pose a significant issue. This is due to the fact that hash tables 
 * can accommodate various sizes. Additionally, the use of prime numbers is 
 * merely a recommendation to optimize hash table usage and reduce collision 
 * occurrences.
 */

#include <stdlib.h>

#include <prime.h>

//==================================================================//
//              Private functions                                   //
//==================================================================//

// Función para calcular (a^b) % m
static long long module(long long a, long long b, long long m) {
    long long result = 1;
    a = a % m;
    while (b > 0) {
        if (b % 2 == 1) result = (result * a) % m;
        a = (a * a) % m;
        b /= 2;
    }
    return result;
}


//Función que realiza el test de Miller-Rabin
static int miller_rabin_test(long long n, long long d) {
    // Seleccionar un número aleatorio 'a' en el rango [2, n-2]
    long long a = 2 + rand() % (n - 4);

    // Calcular a^d % n
    long long x = module(a, d, n);

    if (x == 1 || x == n - 1) return 1;

    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1) return 0;
        if (x == n - 1) return 1;
    }

    return 0;
}


//Función principal para comprobar si un número es probablemente primo usando el Test de Miller-Rabin
static int is_probable_prime(long long n, int k) {
    if (n == 1 || n == 4) return 0;
    if (n == 3) return 1;

    // Encontrar un valor de d tal que n-1 = d * 2^r
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;

    // Realizar k iteraciones del test de Miller-Rabin
    for (int i = 0; i < k; i++)
        if (!miller_rabin_test(n, d)) return 0;

    return 1;
}

//==================================================================//
//              Public functions                                    //
//==================================================================//

long long next_prime_size(long long actual) {
    long long prime = actual * 2;
    while (!is_probable_prime(prime, 30)) prime++;
    return prime;
}