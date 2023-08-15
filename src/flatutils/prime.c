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

#include <prime.h>

// Función para calcular (a^b) % m
long long module(long long a, long long b, long long m) {
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
int miller_rabin_test(long long n, long long d) {
    // Seleccionar un número aleatorio 'a' en el rango [2, n-2]
    long long a = 2 + rand() % (n - 4);

    // Calcular a^d % n
    long long x = module(a, d, n);

    if (x == 1 || x == n - 1) return 1;

    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;

        if (x == 1)
            return 0;
        if (x == n - 1)
            return 1;
    }

    return 0;
}


//Función principal para comprobar si un número es probablemente primo usando el Test de Miller-Rabin
int is_probable_prime(long long n, int k) {
    if (n == 1 || n == 4) return 0;
    if (n == 3) return 1;

    // Encontrar un valor de d tal que n-1 = d * 2^r
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;

    // Realizar k iteraciones del test de Miller-Rabin
    for (int i = 0; i < k; i++)
        if (!miller_rabin_test(n, d))
            return 0;

    return 1;
}


long long next_prime_size(long long actual) {
    long long prime = actual * 2;
    while (!is_probable_prime(prime, 100))
        prime++;
    return prime;
}