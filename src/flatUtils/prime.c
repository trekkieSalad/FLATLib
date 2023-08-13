#include <prime.h>

// Función para calcular (a^b) % m
long long modulo(long long a, long long b, long long m) {
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
int millerRabinTest(long long n, long long d) {
    // Seleccionar un número aleatorio 'a' en el rango [2, n-2]
    long long a = 2 + rand() % (n - 4);

    // Calcular a^d % n
    long long x = modulo(a, d, n);

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
int isProbablePrime(long long n, int k) {
    if (n == 1 || n == 4) return 0;
    if (n == 3) return 1;

    // Encontrar un valor de d tal que n-1 = d * 2^r
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;

    // Realizar k iteraciones del test de Miller-Rabin
    for (int i = 0; i < k; i++)
        if (!millerRabinTest(n, d))
            return 0;

    return 1;
}


long long nextPrimeSize(long long actual) {
    long long prime = actual * 2;
    while (!isProbablePrime(prime, 100))
        prime++;
    return prime;
}