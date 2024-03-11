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

int construirArray(const char *nom_fitxer, int valors[], FILE *fitxer_traça);
Estadistiques calcularEstadistiques(int valors[], int contador_valors, FILE *fitxer_traça);
void mostrarEstadistiques(Estadistiques estadistiques);

int main(int argc, char *argv[])
{

    // Obrim el fitxer.
    FILE *fitxer_traça = fopen("tr_estadistic.prg", "w");

    // Comprovem que no hi hagi error.
    if (fitxer_traça == NULL)
    {
        printf("No es pot obrir el fitxer de traça %s.\n", "tr_estadistic.prg");
        exit(EXIT_FAILURE);
    }

    // Control d'errors
    if (argc != 2)
    {
        printf("Ús: %s <fitxer_valors>\n", argv[0]);
        fprintf(fitxer_traça, "%d %p\n", 2, &argv[0]);
        exit(EXIT_FAILURE);
    }
    fprintf(fitxer_traça, "%d %p\n", 2, &argc);

    int valors[MAX_VALORS];
    int contador_valors = construirArray(argv[1], valors, fitxer_traça);
    fprintf(fitxer_traça, "%d %p\n", 3, &contador_valors);
    Estadistiques estadistiques = calcularEstadistiques(valors, contador_valors, fitxer_traça);
    fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques);

    fclose(fitxer_traça);

    mostrarEstadistiques(estadistiques);
}

int construirArray(const char *nom_fitxer, int valors[], FILE *fitxer_traça)
{

    // Obrim el fitxer.
    FILE *fitxer = fopen(nom_fitxer, "r");

    // Comprovem que eno hi hagi error.
    if (fitxer == NULL)
    {
        printf("No es pot obrir el fitxer %s.\n", nom_fitxer);
        exit(1);
    }

    int contador_valors = 0;
    fprintf(fitxer_traça, "%d %p\n", 3, &contador_valors);

    // Passem els valors del fitxer a l'array i els contem.
    while (contador_valors < MAX_VALORS && fscanf(fitxer, "%d", &valors[contador_valors]) == 1)
    {
        fprintf(fitxer_traça, "%d %p\n", 2, &contador_valors);
        fprintf(fitxer_traça, "%d %p\n", 3, &valors[contador_valors]);
        contador_valors++;
        fprintf(fitxer_traça, "%d %p\n", 3, &contador_valors);
    }
    fprintf(fitxer_traça, "%d %p\n", 2, &contador_valors);

    fclose(fitxer);
    return contador_valors;
}

Estadistiques calcularEstadistiques(int valors[], int contador_valors, FILE *fitxer_traça)
{

    // Control d'errors
    if (contador_valors < 1)
    {
        printf("El fitxer és buit.\n");
        exit(1);
    }
    fprintf(fitxer_traça, "%d %p\n", 2, &contador_valors);

    Estadistiques estadistiques;
    estadistiques.valor_min = valors[0];
    fprintf(fitxer_traça, "%d %p\n", 2, &valors[0]);
    fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques.valor_min);
    estadistiques.valor_max = valors[0];
    fprintf(fitxer_traça, "%d %p\n", 2, &valors[0]);
    fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques.valor_max);
    estadistiques.posicio_min = 0;
    fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques.posicio_min);
    estadistiques.posicio_max = 0;
    fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques.posicio_max);
    estadistiques.mitjana = 0;
    fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques.mitjana);
    estadistiques.desv = 0;
    fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques.desv);

    int i;
    for (i = 1; i < contador_valors; i++)
    {

        fprintf(fitxer_traça, "%d %p\n", 2, &i);
        fprintf(fitxer_traça, "%d %p\n", 3, &i);
        fprintf(fitxer_traça, "%d %p\n", 2, &contador_valors);

        // Mínim
        if (valors[i] < estadistiques.valor_min)
        {
            estadistiques.valor_min = valors[i];
            fprintf(fitxer_traça, "%d %p\n", 2, &valors[i]);
            fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques.valor_min);
            estadistiques.posicio_min = i;
            fprintf(fitxer_traça, "%d %p\n", 2, &i);
            fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques.posicio_min);
        }
        fprintf(fitxer_traça, "%d %p\n", 2, &valors[i]);
        fprintf(fitxer_traça, "%d %p\n", 2, &estadistiques.valor_min);

        // Màxim
        if (valors[i] > estadistiques.valor_max)
        {
            estadistiques.valor_max = valors[i];
            fprintf(fitxer_traça, "%d %p\n", 2, &valors[i]);
            fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques.valor_max);
            estadistiques.posicio_max = i;
            fprintf(fitxer_traça, "%d %p\n", 2, &i);
            fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques.posicio_min);
        }
        fprintf(fitxer_traça, "%d %p\n", 2, &valors[i]);
        fprintf(fitxer_traça, "%d %p\n", 2, &estadistiques.valor_max);

        // Mitjana
        estadistiques.mitjana += (valors[i] / contador_valors);
        fprintf(fitxer_traça, "%d %p\n", 2, &valors[i]);
        fprintf(fitxer_traça, "%d %p\n", 2, &contador_valors);
        fprintf(fitxer_traça, "%d %p\n", 2, &estadistiques.mitjana);
        fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques.mitjana);
    }

    fprintf(fitxer_traça, "%d %p\n", 2, &i);
    fprintf(fitxer_traça, "%d %p\n", 2, &contador_valors);

    // Desviació típica
    for (i = 0; i < contador_valors; i++)
    {
        fprintf(fitxer_traça, "%d %p\n", 2, &i);
        fprintf(fitxer_traça, "%d %p\n", 3, &i);
        fprintf(fitxer_traça, "%d %p\n", 2, &contador_valors);
        estadistiques.desv += pow(valors[i] - estadistiques.mitjana, 2);
        fprintf(fitxer_traça, "%d %p\n", 2, &estadistiques.desv);
        fprintf(fitxer_traça, "%d %p\n", 2, &estadistiques.mitjana);
        fprintf(fitxer_traça, "%d %p\n", 2, &valors[i]);
        fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques.desv);
    }
    fprintf(fitxer_traça, "%d %p\n", 2, &i);
    fprintf(fitxer_traça, "%d %p\n", 2, &contador_valors);

    estadistiques.desv = sqrt(estadistiques.desv / contador_valors);
    fprintf(fitxer_traça, "%d %p\n", 2, &estadistiques.desv);
    fprintf(fitxer_traça, "%d %p\n", 2, &contador_valors);
    fprintf(fitxer_traça, "%d %p\n", 3, &estadistiques.desv);

    return estadistiques;
}

void mostrarEstadistiques(Estadistiques estadistiques)
{

    printf("Valor mínim: %d, Posició: %d\n", estadistiques.valor_min, estadistiques.posicio_min);
    printf("Valor màxim: %d, Posició: %d\n", estadistiques.valor_max, estadistiques.posicio_max);
    printf("Mitjana: %.2f\n", estadistiques.mitjana);
    printf("Desviació: %.2f\n", estadistiques.desv);
}