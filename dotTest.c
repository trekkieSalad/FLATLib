#include <stdio.h>
#include <stdlib.h>

// Definición de la estructura de Estado
struct Estado {
    char nombre[50];
};

// Definición de la estructura de Terminal
struct Terminal {
    char simbolo[50];
};

// Definición de la estructura de Arco_af
struct Arco_af {
    struct Estado origen;
    struct Estado destino;
    struct Terminal etiqueta;
};

// Definición de la estructura de Af
struct Af {
    struct Estado estados[50];
    int num_estados;
    struct Estado inicial;
    struct Arco_af arcos[50];
    int num_arcos;
    struct Estado finales[50];
    int num_finales;
};

// Función auxiliar para convertir un char* en un string que contenga su representación en formato "cadena"
char* string_format(char* cadena) {
    char* resultado = (char*)malloc(strlen(cadena) + 3);
    strcpy(resultado, "\\\"");
    strcat(resultado, cadena);
    strcat(resultado, "\\\"");
    return resultado;
}

// Función auxiliar para generar la representación DOT de los Estados
char* aux1(struct Estado* estados, int num_estados) {
    char* resultado = (char*)malloc(1000); // Asumimos que el tamaño será suficiente para esta representación
    resultado[0] = '\0';
    for (int i = 0; i < num_estados; i++) {
        strcat(resultado, string_format(estados[i].nombre));
        strcat(resultado, "; ");
    }
    return resultado;
}

// Función auxiliar para generar la representación DOT de los Arcos
char* aux2(struct Arco_af* arcos, int num_arcos) {
    char* resultado = (char*)malloc(5000); // Asumimos que el tamaño será suficiente para esta representación
    resultado[0] = '\0';
    for (int i = 0; i < num_arcos; i++) {
        char* etiqueta = string_format(arcos[i].etiqueta.simbolo);
        char* origen = string_format(arcos[i].origen.nombre);
        char* destino = string_format(arcos[i].destino.nombre);

        if (strcmp(arcos[i].etiqueta.simbolo, "") == 0) {
            strcat(resultado, "   ");
            strcat(resultado, origen);
            strcat(resultado, " -> ");
            strcat(resultado, destino);
            strcat(resultado, " [label=\"&#949;\"];\n");
        } else {
            strcat(resultado, "   ");
            strcat(resultado, origen);
            strcat(resultado, " -> ");
            strcat(resultado, destino);
            strcat(resultado, " [label=");
            strcat(resultado, etiqueta);
            strcat(resultado, "];\n");
        }

        free(etiqueta);
        free(origen);
        free(destino);
    }
    return resultado;
}

// Función para generar la representación DOT del grafo
char* dot_of_af(char* titulo, struct Af* a) {
    char* resultado = (char*)malloc(10000); // Asumimos que el tamaño será suficiente para esta representación
    char* aux1_resultado = aux1(a->finales, a->num_finales);
    char* aux2_resultado = aux2(a->arcos, a->num_arcos);

    sprintf(resultado, "digraph grafo {\n   label=%s;\n   labelloc=top;\n   labeljust=left;\n   node [style=invis, height=0, width=0]; \\\"\\\";\n   node [shape=doublecircle, style=solid]; %s\n   node [shape=circle, style=solid];\n   rankdir=LR;\n%s}\n",
            string_format(titulo), aux1_resultado, aux2_resultado);

    free(aux1_resultado);
    free(aux2_resultado);

    return resultado;
}


// Función para dibujar el grafo utilizando DOT y xdot
void dibuja_af(char* titulo, struct Af* a) {
    char* dot_code = dot_of_af(titulo, a);
    char* command = (char*)malloc(strlen(dot_code) + 100);

    command[0] = '\0';
    strcat(command, "echo \"");
    strcat(command, dot_code);
    strcat(command, "\" | dot -Tx11 &");

    system(command);

    // Liberar memoria
    free(dot_code);
    free(command);
}

int main() {
    // Crear una estructura Af con los datos necesarios para dibujar el grafo
    struct Af mi_af;
    mi_af.num_estados = 3;

    strcpy(mi_af.estados[0].nombre, "A");
    strcpy(mi_af.estados[1].nombre, "B");
    strcpy(mi_af.estados[2].nombre, "C");

    mi_af.num_arcos = 2;

    strcpy(mi_af.arcos[0].origen.nombre, "A");
    strcpy(mi_af.arcos[0].destino.nombre, "B");
    strcpy(mi_af.arcos[0].etiqueta.simbolo, "0");

    strcpy(mi_af.arcos[1].origen.nombre, "B");
    strcpy(mi_af.arcos[1].destino.nombre, "C");
    strcpy(mi_af.arcos[1].etiqueta.simbolo, "1");

    mi_af.num_finales = 1;
    strcpy(mi_af.finales[0].nombre, "C");

    // Llamar a la función para dibujar el grafo
    dibuja_af("Mi AF", &mi_af);

    return 0;
}
