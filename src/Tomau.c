#include <stdio.h>
#include <stdlib.h>

#include "Tomau.h"


void ToMau(char *filename) {
    FILE *fp;
    FILE *fp1;
    int vertex, edge, m, n, index = 0;
    fp = fopen(filename, "r");
    fscanf(fp, "%d", &vertex);
    fgetc(fp);
    fscanf(fp, "%d", &edge);
    int graph[vertex][vertex], draw[vertex];
    
    for (int i = 0; i < vertex; i++) {
        draw[i] = 0;
        for (int j = 0; j < vertex; j++) {
            graph[i][j] = 0;
        }
    }
    while (!feof(fp)) {
        
        fscanf(fp, "%d", &m);
        fgetc(fp);
        fscanf(fp, "%d", &n);
        graph[m - 1][n - 1] = 1;    
        graph[n - 1][m - 1] = 1;
        index++;
        if (index == edge)
            break;
    }
    fclose(fp);

    int a = 0;
    for (int i = 0; i < vertex; i++) {
        if(draw[i] == 0) {      
            draw[i] = a + 1;
        }
        else
            continue;

        for (int j = 0; j < vertex; j++) {
            if((graph[i][j] == 0) && (draw[j] == 0)) {    
                draw[j] = a + 1;
                for (int k = 0; k < vertex; k++) {                          
                    if((graph[j][k] == 1) && (draw[j] == draw[k])) {      
                        if(j < k) 
                            draw[k] = 0;
                        else
                            draw[j] = 0;
                    }
                      
                }
            }
                
        }
        a++;
    }

    printf("\nCach to mau:\n");
    for (int i = 0; i < vertex; i++){
        printf("draw[%d] = %d\n", i+1, draw[i]);
    }

    fp1 = fopen("graph.gv", "w");
    fprintf(fp1, "graph {\nrankdir=LR;\n");
    for (int i = 0; i < vertex; i++) {
        int temp = draw[i] % 8;
        if(temp == 1) {
            fprintf(fp1, "%d [fillcolor=cyan, style=filled];\n", i + 1);
        }
        else if (temp == 2) {
            fprintf(fp1, "%d [fillcolor=red, style=filled];\n", i + 1);
        }
        else if (temp == 3)
        {
            fprintf(fp1, "%d [fillcolor=green, style=filled];\n", i + 1);
        }
        else if (temp == 4)
        {
            fprintf(fp1, "%d [fillcolor=yellow, style=filled];\n", i + 1);
        }
        else if (temp == 5)
        {
            fprintf(fp1, "%d [fillcolor=blue, style=filled];\n", i + 1);
        }
        else if (temp == 6)
        {
            fprintf(fp1, "%d [fillcolor=purple, style=filled];\n", i + 1);
        }
        else if (temp == 7)
        {
            fprintf(fp1, "%d [fillcolor=black, style=filled];\n", i + 1);
        }
        else if (temp == 0)
        {
            fprintf(fp1, "%d [fillcolor=white, style=filled];\n", i + 1);
        }
    }
    index = 0;
    fp = fopen(filename, "r");
    fscanf(fp, "%d", &vertex);
    fgetc(fp);
    fscanf(fp, "%d", &edge);
    while (!feof(fp))
    {

        fscanf(fp, "%d", &m);
        fgetc(fp);
        fscanf(fp, "%d", &n);
        fprintf(fp1, "%d -- %d;\n", m, n);
        index++;
        if (index == edge)
            break;
    }
    fclose(fp);
    fprintf(fp1, "}");
    fclose(fp1);
    system("dot -Tpdf -O graph.gv");
}

void black()
{
    printf("\033[1;30m");
}

void red()
{
    printf("\033[1;31m");
}

void green()
{
    printf("\033[1;32m");
}

void yellow()
{
    printf("\033[1;33m");
}

void blue()
{
    printf("\033[1;34m");
}

void purple()
{
    printf("\033[1;35m");
}

void cyan()
{
    printf("\033[0;36m");
}
void white()
{
    printf("\033[0;37m");
}
void reset()
{
    printf("\033[0m");
}