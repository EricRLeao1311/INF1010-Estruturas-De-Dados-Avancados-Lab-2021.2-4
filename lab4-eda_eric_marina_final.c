/*INF1010 - ESTRUTURAS DE DADOS AVANCADAS - 2022.1 - 3WB
Laboratório 04 - trabalhando com tabela hash
Nome: Eric Leao     Matrícula: 2110694
Nome: Marina Schuler Martins    Matrícula: 2110075*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define MAX 1031
#define LEN 7

char **create_hash(int row, int collumn);

void print_hash(char **table);

unsigned int hash1(char *key, int c);

unsigned int hash2(char *key, int c);

int insert_key(char **table, char *key);

void delete_key(char **table, char *key);

int search_key(char **table, char *key);

int main(void) {
  FILE *file = fopen("placas.txt", "r");
  char **table = create_hash(MAX - 1, LEN);
  char *placa;
  int col = 0;
  int pos;
  clock_t start, stop;
  double total;
  if ((placa = (char *)malloc(sizeof(char *) * LEN)) == NULL) {
    fprintf(stderr, "erro alocar memoria.\n");
    exit(1);
  }
  start = clock();
  while (fscanf(file, "%s\n", placa) != EOF) {
    col += insert_key(table, placa);
  }
  stop = clock();
  total = (double)(stop - start) / CLOCKS_PER_SEC;
  printf("Tempo total para inserir = %f\n", total);
  printf("Colisões totais = %d\n", col);
  fclose(file);
  file = fopen("placas.txt", "r");
  start = clock();
  while (fscanf(file, "%s\n", placa) != EOF) {
    pos = search_key(table, placa);
  }
  stop = clock();
  total = (double)(stop - start) / CLOCKS_PER_SEC;
  printf("Tempo total para buscar = %f\n", total);
  fclose(file);
  file = fopen("placas.txt", "r");
  while (fscanf(file, "%s\n", placa) != EOF) {
    delete_key(table, placa);
  }
  fclose(file);
  free(placa);
  for (int w = 0; w <= MAX - 1; w++)
    free(table[w]);
  free(table);
  return 0;
}

char **create_hash(int row, int collumn) {
  char **hash;
  if ((hash = (char **)malloc(sizeof(char **) * row)) == NULL) {
    fprintf(stderr, "erro alocar memoria.\n");
    exit(1);
  }
  for (int c = 0; c <= row; c++)
    if ((hash[c] = (char *)calloc(collumn, sizeof(char *))) == NULL) {
      fprintf(stderr, "erro alocar memoria.\n");
      exit(1);
    }
  return hash;
}

unsigned int hash1(char *key, int c) {
  unsigned int aux = 0;
  unsigned int k;
  while ((k = *key++)) {
    aux += ((aux << 18) | ((aux >> 13) + k * 1037)) + c * c;
  }
  return aux % MAX;
}

unsigned int hash2(char *key, int c) {
  unsigned int aux = 6791;
  unsigned int k;
  while ((k = *key++)) {
    aux += ((aux << 19) ^ ((aux >> 15) + k * 1699)) + c * c;
  }
  return aux % MAX;
}

int insert_key(char **table, char *key) {
  int c = 0;
  int pos;
  while (1) {
    if (c % 2) {
      pos = hash1(key, c);
    } else {
      pos = hash2(key, c);
    }
    if (*table[pos] == '\0') {
      strcpy(table[pos], key);
      break;
    }
    if (strcmp(table[pos], key) == 0) {
      break;
    }
    c++;
  }
  return c;
}

void delete_key(char **table, char *key) {
  int c = 0;
  int pos;
  char vazio[] = "\0";
  while (1) {
    pos = search_key(table, key);
    if (strcmp(table[pos], key) == 0) {
      strcpy(table[pos], vazio);
      return;
    }
  }
  c++;
}

int search_key(char **table, char *key) {
  int c = 0;
  int pos;
  char vazio[] = "\0";
  while (1) {
    if (c % 2) {
      pos = hash1(key, c);
    } else {
      pos = hash2(key, c);
    }
    if (strcmp(table[pos], key) == 0) {
      return pos;
    }
    c++;
  }
}

void print_hash(char **table) {
  for (int c = 0; c < MAX; c++)
    printf("%s\n", table[c]);
}
