#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VALORS 100

typedef struct
{
    int valor_min;
    int valor_max;
    int posicio_min;
    int posicio_max;
    double mitjana;
    double desv;
} Estadistiques;

int construirArray(const char *nom_fitxer, int valors[])
{

    // Obrim el fitxer.
    FILE *fitxer = fopen(nom_fitxer, "r");

    // Comprovem que el fixter no sigui NULL.
    if (fitxer == NULL)
    {
        printf("No es pot obrir el fitxer %s.\n", nom_fitxer);
        exit(1);
    }

    int contador_valors = 0;

    // Passem els valors del fitxer a l'array i els contem.
    while (contador_valors < MAX_VALORS && fscanf(fitxer, "%d", &valors[contador_valors]) == 1)
    {
        contador_valors++;
    }

    fclose(fitxer);
    return contador_valors;
}

Estadistiques calcularEstadistiques(int valors[], int contador_valors)
{

    // Control d'errors
    if (contador_valors < 1)
    {
        printf("El fitxer és buit.");
        exit(1);
    }

    Estadistiques estadistiques;
    estadistiques.valor_min = valors[0];
    estadistiques.valor_max = valors[0];
    estadistiques.posicio_min = 0;
    estadistiques.posicio_max = 0;
    estadistiques.desv = 0;

    for (int i = 1; i < contador_valors; i++)
    {

        // Mínim
        if (valors[i] < estadistiques.valor_min)
        {
            estadistiques.valor_min = valors[i];
            estadistiques.posicio_min = i;
        }

        // Màxim
        if (valors[i] > estadistiques.valor_max)
        {
            estadistiques.valor_max = valors[i];
            estadistiques.posicio_max = i;
        }

        // Mitjana
        estadistiques.mitjana += (valors[i] / contador_valors);
    }

    // Desviació típica
    for (int i = 0; i < contador_valors; i++)
    {
        estadistiques.desv += pow(valors[i] - estadistiques.mitjana, 2);
    }
    estadistiques.desv = sqrt(estadistiques.desv / contador_valors);

    return estadistiques;
}

void mostrarEstadistiques(Estadistiques estadistiques)
{

    printf("Valor mínim: %d, Posició: %d\n", estadistiques.valor_min, estadistiques.posicio_min);
    printf("Valor màxim: %d, Posició: %d\n", estadistiques.valor_max, estadistiques.posicio_max);
    printf("Mitjana: %.2f\n", estadistiques.mitjana);
    printf("Desviació: %.2f\n", estadistiques.desv);
}

int main(int argc, char *argv[])
{

    // Comntrol d'errors
    if (argc != 2)
    {
        printf("Ús: %s <fitxer_valors>\n", argv[0]);
    }

    int valors[MAX_VALORS];
    int contador_valors = construirArray(argv[1], valors);
    Estadistiques estadistiques = calcularEstadistiques(valors, contador_valors);

    mostrarEstadistiques(estadistiques);
}
