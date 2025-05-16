/**
 * @file functions.h
 * @author a24869
 * @brief Ficheiro para implementar todas as funções chamadas no functions.h
 * 
 * @date 2025-03-22
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lib/functions.h"

/**
 * @brief Liberta a memória alocada para uma lista encadeada de antenas.
 */
void freeAntennaList(Antenna* head) {
    Antenna* aux;
    while (head != NULL) {
        aux = head;
        head = head->link;
        free(aux);
    }
}

/**
 * @brief Insere uma nova antena na lista ligada.
 *
 * Esta função cria uma nova antena com as coordenadas e frequência especificadas,
 * insere-a na lista.
 *
 * @param head Ponteiro para a cabeça da lista de antenas.
 * @param x Coordenada x da nova antena.
 * @param y Coordenada y da nova antena.
 * @param freq Frequência da nova antena.
 * @return Antenna* Ponteiro para a nova cabeça da lista.
 */
Antenna* insertAntenna(Antenna* head, int x, int y, char freq) {
    // Verifica se já existe uma antena nas mesmas coordenadas
    Antenna* aux = head;
    while(aux != NULL){
        if(aux->x == x && aux->y == y){
            return head;
        }
        aux = aux->link;
    }

    // Cria uma nova antena
    Antenna* node = (Antenna *)malloc(sizeof(Antenna));
    if(node == NULL){
        return head;
    }

    // Definição de dados da nova antena
    node->x = x;
    node->y = y;
    node->frequency = freq;

    // Apontamos para a cabeça antiga, a nova antena torna-se a cabeça da lista
    node->link = head;

    return node;
}

/**
 * @brief Remove uma antena já existente na lista ligada.
 *
 * Esta função remove uma antena da lista com base nas coordenadas e frequência fornecidas.
 * Caso a antena removida seja a cabeça da lista, a cabeça será atualizada.
 *
 * @param head Ponteiro para a cabeça da lista de antenas.
 * @param x Coordenada x da antena a ser removida.
 * @param y Coordenada y da antena a ser removida.
 * @param freq Frequência da antena a remover.
 * @return Antenna* Ponteiro para a nova cabeça da lista após a remoção.
 */
Antenna* deleteAntenna(Antenna* head, int x, int y, char frequency) {
    if (head == NULL) return NULL;

    // Variaveis auxiliares para avançarmos na lista
    Antenna* aux = head;
    Antenna* prev = NULL;

    // É veficado se a cabeça da lista é a antena a remover
    if (aux->x == x && aux->y == y && aux->frequency == frequency) {
        head = aux->link;
        free(aux);
        return head;
    }

    // Procura a antena a remover
    while (aux != NULL) {
        if (aux->x == x && aux->y == y && aux->frequency == frequency) {
            prev->link = aux->link;
            free(aux);
            return head;
        }
        prev = aux;
        aux = aux->link;
    }

    return head;
}

/**
 * @brief Aplica o efeito nefasto às antenas na lista.
 *
 * Esta função percorre a lista de antenas e insere novas antenas, chamadas de efeito nefasto,
 * na posição intermediária entre pares de antenas cuja distância em X e Y seja par.
 * As novas antenas são marcadas com a frequência '#', que serão identificadas como ruídos.
 *
 * @param head Ponteiro para a cabeça da lista de antenas.
 * @return Ponteiro para a cabeça da lista de antenas atualizada.
 */
Antenna* applyNefastoEffect(Antenna* head) {

    // Variavel auxiliar para fazer de antenna
    Antenna* aux = head;
    
    while (aux != NULL) {
        Antenna* node = aux->link;
        
        while (node != NULL) {
            // Ignora as antenas já afetadas pelo efeito nefasto ('#')
            if (aux->frequency == '#' || node->frequency == '#') {
                node = node->link;
                continue;
            }

            // Calcula as distâncias absolutas em x e y entre as antenas
            int distX = abs(aux->x - node->x);
            int distY = abs(aux->y - node->y);

            // Verifica se ambas as distâncias são pares
            if (distX % 2 == 0 && distY % 2 == 0) {
                // Calcula a posição intermediária entre as duas antenas
                int midX = (aux->x + node->x) / 2;
                int midY = (aux->y + node->y) / 2;
                // Insere uma nova antena na posição intermediária com frequência '#'
                printf("Nefasto effect inserted on: (%d, %d)\n", midX, midY);
                
                head = insertAntenna(head, midX, midY, '#');
            }

            node = node->link;
        }

        aux = aux->link;
    }
    
    return head;
}

/**
 * @brief Lê a matriz de antenas de um ficheiro de texto.
 *
 * Esta função abre um ficheiro de texto que que representa uma matriz de antenas. Caracteres diferentes de '.' são 
 * considerados antenas e inseridos numa lista ligada com as respetivas coordenadas.
 *
 * @param filename Nome do ficheiro a ler.
 * @return Antenna* Cabeça da lista ligada com as antenas lidas, ou NULL em caso de erro.
 */
Antenna* readAntennaMatrixFile(const char* filename) {
    // Abre o ficheiro para leitura
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    Antenna* head = NULL;
    char* line = NULL; // Linha lida do ficheiro
    size_t len = 0; // Tamanho da linha
    int x = 0;

    while (getline(&line, &len, file) != -1) {
        int y = 0;
        // Percorre cada carácter da linha
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == ' ' || line[i] == '\t') continue;

            if (line[i] != '.' && line[i] != '\n') {
                // Insere antena se não for ponto ou quebra de linha
                head = insertAntenna(head, x, y, line[i]);
            }
            y++;
        }
        x++;
    }

    free(line);
    fclose(file);
    return head;
}

/**
 * @brief Guarda a lista ligada de antenas num ficheiro binário.
 * 
 * Esta função percorre a lista ligada de antenas e escreve cada antena
 * num ficheiro binário no formato AntennaFile. Retorna false se ocorrer
 * algum erro ao abrir o ficheiro ou se a lista estiver vazia.
 * 
 * @param filename Nome do ficheiro binário onde guardar.
 * @param head Ponteiro para o início da lista ligada de antenas.
 * @return true se a operação for bem-sucedida, false caso contrário.
 */
bool writeAntennaBinary(char* filename, Antenna* head) {
    if (head == NULL) return false;

    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) return false;

    Antenna* aux = head;
    // Struct separada para gravar só dados, sem ponteiros, no ficheiro binário.
    AntennaFile af;

    while (aux != NULL) {
        // Definição de dados da antena
        af.x = aux->x;
        af.y = aux->y;
        af.frequency = aux->frequency;
        fwrite(&af, sizeof(AntennaFile), 1, fp);
        aux = aux->link;
    }

    fclose(fp);
    return true;
}

/**
 * @brief Lê uma lista de antenas a partir de um ficheiro binário.
 * 
 * Abre um ficheiro binário previamente guardado e reconstrói a lista
 * ligada de antenas com base nos dados lidos em binário. Em caso de erro de alocação
 * de memória, liberta os nós já criados e termina.
 * 
 * @param filename Nome do ficheiro binário a ler.
 * @return Ponteiro para o início da lista ligada reconstruída, ou NULL em caso de erro.
 */
Antenna* readAntennaBinary(char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) return NULL;

    Antenna* head = NULL;
    Antenna* tail = NULL;
    AntennaFile af;

    while (fread(&af, sizeof(AntennaFile), 1, fp) == 1) {
        Antenna* newNode = (Antenna*) malloc(sizeof(Antenna));
        if (newNode == NULL) {
            fclose(fp);
            // Em caso de erro libertar memória já alocada
            while (head != NULL) {
                Antenna* temp = head;
                head = head->link;
                free(temp);
            }
            return NULL;
        }
        // Definição de dados da antena
        newNode->x = af.x;
        newNode->y = af.y;
        newNode->frequency = af.frequency;
        newNode->link = NULL;

        if (head == NULL) {
            // Caso especial: a lista está vazia, o novo nó será o primeiro
            head = newNode;
            tail = newNode;
        } else {
            // Liga o novo nó ao final da lista e atualiza o ponteiro tail
            tail->link = newNode;
            tail = newNode;
        }
    }

    fclose(fp);
    return head;
}

/**
 * @brief Apresenta no ecrã todas as antenas da lista ligada.
 * 
 * Percorre a lista de antenas e imprime no terminal a posição e frequência
 * de cada uma. Antenas com frequência '#' são identificadas como Nefasto.
 * 
 * @param head Ponteiro para o início da lista ligada de antenas.
 */
void showAntennaList(Antenna* head) {
    Antenna* aux = head;
    while (aux != NULL) {
        if (aux->frequency == '#') {
            printf("Nefasto at (%d, %d) with frequency '%c'\n", aux->x, aux->y, aux->frequency);
        } else {
            printf("Antenna at (%d, %d) with frequency '%c'\n", aux->x, aux->y, aux->frequency);
        }
        aux = aux->link;
    }
}
