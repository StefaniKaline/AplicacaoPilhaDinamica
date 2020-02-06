#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <locale.h>
#include<ctype.h>

//Criar a struct para o tipo ENCOMENDA
typedef struct sENCOMENDA {
    float volume;
    float distancia;
    int tentativa_ent; //Variável referente ao número de tentativas de entrega
    char endereco[50];

} ENCOMENDA;

//Criar a struct para o tipo CELULA
typedef struct sCELULA {
    ENCOMENDA info;
    struct sCELULA *next;
} CELULA;

//Criar o a struct para o tipo PILHA
typedef struct sPILHA {
    CELULA* pTopo;
    int tamanho;
} PILHA;

//Criar uma nova célula
CELULA* Criar_Celula () {
    return (CELULA*)malloc(sizeof(CELULA));
}

//Liberar célula
void Liberar_Celula (CELULA* q) {
    free(q);
}

//Inicializar a pilha
void Inicializar_Pilha (PILHA* pilha) {
    pilha->pTopo = NULL;
    pilha->tamanho = 0;
}

//Verificar se a pilha
int Pilha_Vazia (PILHA pilha) {
    if (pilha.pTopo == NULL) {
        return 1;
    }
    return 0;
}

//Funções implementadas para as pilhas
//Função para empilhar
void Empilhar (PILHA* pilha, ENCOMENDA x) {
    CELULA* q;
    q = Criar_Celula();
    if (q == NULL) {
        printf("ERRO: Falha na alocação de um nó.\n");
    } else {
        q->info = x;
        q->next = (pilha->pTopo);
        (pilha->pTopo) = q;
        pilha->tamanho++;
    }
}

//Função para empilhar na pilha de não entregues
void EmpilharNEntregue (PILHA* pilha, ENCOMENDA x) {
    CELULA* q;
    q = Criar_Celula();
    if (q == NULL) {
        printf("ERRO: Falha na alocação do nó.\n");
    } else {
        q->info = x;
        q->info.tentativa_ent = (q->info.tentativa_ent) + 1;
        q->next = pilha->pTopo;
        pilha->pTopo = q;
        pilha->tamanho++;
    }
}

//Função para desempilhar
ENCOMENDA Desempilhar (PILHA* pilha) {
    ENCOMENDA x;
    x.distancia = -1;
    x.volume = -1;
    x.tentativa_ent = -1;
    strcpy(x.endereco, "Inválido");
    if (Pilha_Vazia(*pilha)) {
        printf("A pilha se encontra sem encomendas!\n");
        return x;
    } else {
        CELULA* aux;
        aux = (pilha->pTopo);
        x = aux->info;
        (pilha->pTopo) = aux->next;
        Liberar_Celula(aux);
        pilha->tamanho--;
        return x;
    }
}

//Funções implementadas para a lista ordenada
//Inicializar a lista
void Inicializar_Lista (CELULA** pLista) {
     *pLista = NULL;
}

//Verificar se a lista está vazia
int Lista_Vazia (CELULA* pLista) {
    if (pLista == NULL) {
        return 1;
    }
    return 0;
}

//Inserir de maneira ordenada na lista encadeada
void InserirOrdenado (CELULA** pLista, ENCOMENDA x) {
    CELULA* q;
    q = Criar_Celula();
    if (q == NULL) {
        printf("ERRO: Falha na alocação do nó.\n");
    } else {
        q->info = x;
        if (Lista_Vazia(*pLista)) {
            (*pLista) = q;
            (*pLista)->next = NULL;
        } else {
            CELULA* aux;
            CELULA* ant;
            aux = (*pLista);
            while (aux != NULL) {
                if (x.distancia < (aux->info.distancia)) {
                    ant = aux;
                    aux = aux->next;
                } else {
                    break;
                }
            }
            if (aux == (*pLista)) {
                q->next = (*pLista);
                (*pLista) = q;
            } else {
                if (aux == NULL) {
                    q->next = NULL;
                    ant-> next = q;
                } else {
                    q->next = aux;
                    ant->next = q;
                }
            }
        }
    }
}

//Remover da lista ordenada
ENCOMENDA Remover_ListaO (CELULA** pLista) {
    ENCOMENDA x;
    x.distancia = -1;
    x.tentativa_ent = -1;
    strcmp(x.endereco, "Inválido");
    if (Lista_Vazia(*pLista)) {
        printf("A lista esta vazia\n");
        return x;
    }
    CELULA* aux;
    aux = *pLista;
    x = aux->info;
    *pLista = (*pLista)->next;
    Liberar_Celula(aux);
    return x;
}

//Retornar quantas encomendas devem ser entregar/reentregar
int Tamanho_Pilha (PILHA pilha) {
    return pilha.tamanho;
}

//Tamanho da lista (Função recursiva)
int Tamanho_Lista (CELULA* pLista) {
        CELULA* aux;
        aux = pLista;
        if (aux == NULL) {
            return 0;
        } else {
            aux = aux->next;
            return (1 + Tamanho_Lista(aux));
        }
}

//FUNÇÕES PRÓPRIAS PARA O APLICATIVO
//Carregar caminhão
void Carregar_Caminhao (PILHA* pilha, CELULA** pLista) {
    if (Lista_Vazia(*pLista)) {
        printf("*Não há entregas a serem feitas.\n*Registre as encomendas no sistema para começar!");
    } else {
        int contador, i;
        float volume = 0;
        contador = Tamanho_Lista(*pLista);
        ENCOMENDA enc;
        printf("\n*********************************************************\n\n");
        printf("\tENCOMENDAS A SEREM ENTREGUES NA PRÓXIMA VIAGEM\n");
        printf("\n*********************************************************\n\n");
        for(i = 1; i <= contador; i++) {
            enc = Remover_ListaO(pLista);
            volume = volume + enc.volume;
            printf("Endereco: %sVolume: %0.2f m³\nTentativas de entregas: %d\nDistância: %0.2f km\n\n", enc.endereco, enc.volume, enc.tentativa_ent, enc.distancia);
            Empilhar(pilha, enc);
        }
        printf("Volume da carga total: %0.2f m³\n", volume);
        printf("\n*********************************************************\n\n");
    }
}

//Entregar encomenda
//Deve verificar se a entrega foi realmente feita
void Entregar_Encomenda (PILHA* pilha, PILHA* pilhaAux) {
    if (Pilha_Vazia(*pilha)) {
        printf("*Não há mais encomendas a serem entregues! Volte a central\n");

    } else {
        ENCOMENDA enc;
        enc = Desempilhar(pilha);
        printf("******************************************************************");
        printf("\n\nENCOMENDA:\nEndereco: %s\nVolume: %0.2f m³\nTentativas de entregas: %d\nDistância: %0.2f km\n\n", enc.endereco, enc.volume, enc.tentativa_ent, enc.distancia);
        printf("Encomendas restantes: %d\n", pilha->tamanho );
        printf("******************************************************************\n\n");
        char entrega;
        do {
            printf("*A encomenda foi entregue à seu destinatário? (S ou N)\n");
            fflush(stdin);
            scanf("%c", &entrega);
        } while ((entrega != 'S') && (entrega != 'N'));

        if (entrega == 'N') {
            printf("\n\nViagem perdida! \nA encomenda retornará a central\n");
            EmpilharNEntregue(pilhaAux, enc); //Passando a encomenda não entregue para a pilha auxiliar
        } else {
            printf("Entrega bem sucedida!\n");
        }
    }
}

//Inserir as encomendas da pilha de não entregues na lista ordenada
void Reorganizar_ListaO (PILHA* pilhaAux, CELULA** pLista) {
    if (Pilha_Vazia(*pilhaAux)) {
        printf("*Todas as encomendas da última viagem foram entregues!\n");
    } else {
        ENCOMENDA enc;
        int i, contador = pilhaAux->tamanho;
        for (i = 0; i < contador; i++) {
            enc = Desempilhar(pilhaAux);
            if (enc.tentativa_ent <= 3) {
                InserirOrdenado(pLista, enc);
            } else {
                printf("*O limite de tentativas de entrega já foi atingido!\nA encomenda permanecerá na central até que o proprietário vá retirá-la\n");
                printf("\n\nENCOMENDA:\nEndereco: %sVolume: %0.2f m³\nTentativas de entregas: %d\nDistância: %0.2f km\n\n", enc.endereco, enc.volume, enc.tentativa_ent, enc.distancia);
            }
        }
    }
}

//Exibir a lista ordenada
void Exibir_Lista (CELULA* pLista) {
    if (Lista_Vazia(pLista)) {
        printf("A lista está vazia\n");

    } else {
        CELULA* aux;
        aux = pLista;
        while (aux != NULL) {
            printf("\nEndereco: %sVolume: %0.2f m³\nTentativas de entregas: %d\nDistância: %0.2f km\n\n", (aux->info.endereco), (aux->info.volume), (aux->info.tentativa_ent), (aux->info.distancia));
            aux=aux->next;
        }
        printf("\n");
    }
}
int main() {

    //Acentuação
    setlocale(LC_ALL, "Portuguese");

    //Cores de fonte e fundo
    system("color 0B");

    PILHA pilha; //Pilha de encomendas
    PILHA pilhaAux; //Pilha para as encomendas não entregues
    CELULA* lista; //Lista para ordenar as encomendas

    //Inicialização das estruturas utilizadas
    Inicializar_Pilha(&pilhaAux);
    Inicializar_Pilha(&pilha);
    Inicializar_Lista(&lista);

    //Variável para escolher a opção
    int opcao;

    //Variáveis auxiliares
    int cont, i, v;

    ENCOMENDA enc;
    //Menu
    do {
        printf("\n\n\t\tBEM - VINDO AO SEU NOVO GERENCIADOR DE ENTREGAS!\n");
        printf("*******************************************************************************\n");
        printf("Hora de começar o dia! Escolha uma das opções:\n\n");
        printf("( 0 ) Para sair do programa\n( 1 ) Verificar se há encomendas a serem entregues\n( 2 ) Inserir encomendas\n( 3 ) Carregar caminhão\n( 4 ) Entregar encomenda\n( 5 ) Reorganizar a lista de entregas\n");
        printf("*******************************************************************************\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("cls");
                printf("*******************************************************************************\n");
                printf("%d encomendas a serem entregues\n", Tamanho_Lista(lista));
                Exibir_Lista(lista);
                printf("*******************************************************************************\n");
                break;
            case 2:
                system("cls");
                printf("*******************************************************************************\n");
                printf("Registrando encomenda:\n");
                do {
                    printf("Digite o volume da caixa: ");
                    scanf("%f", &enc.volume);
                } while ( enc.volume <= 0);
                do {
                    printf("Digite a distância entre a central de Correio e o destino: ");
                    fflush(stdin); //Foi preciso limpar o buffer, pois não estava sendo feita a leitura da distância
                    scanf("%f", &enc.distancia);
                } while (enc.distancia <= 0);
                do {
                    printf("Digite o endereço do destino: ");
                    fflush(stdin);
                    fgets(enc.endereco,50,stdin);
                    cont = strlen(enc.endereco);
                    for (i = 0; i < cont; i++){
                            v = 0;
                            if(isdigit(enc.endereco[i])){
                                v++;
                                break;
                            }
                    }
                } while(!strcmp("\n", enc.endereco) || !(strcmp(" \n", enc.endereco)) || (v != 0));
                enc.tentativa_ent = 0;
                InserirOrdenado(&lista, enc);
                printf("*******************************************************************************\n");
                printf("Encomenda registrada com sucesso\n");
                printf("*******************************************************************************\n");
                break;
            case 3:
                system("cls");
                Carregar_Caminhao(&pilha, &lista);
                break;
            case 4:
                system("cls");
                Entregar_Encomenda(&pilha, &pilhaAux);
                break;
            case 5:
                system("cls");
                Reorganizar_ListaO(&pilhaAux, &lista);
                printf("*******************************************************************************\n");
                printf("As encomendas não entregues retornaram a central e foram reorganizadas!\n");
                printf("*******************************************************************************\n");
                break;
            default:
                system("cls");
                printf("*******************************************************************************\n");
                printf("Opção inválida!\n");
                printf("*******************************************************************************\n");
        }
    } while(opcao != 0);
    system("cls");
    printf("*******************************************************************************\n");
    printf("Fim das operações!\n");
    printf("*******************************************************************************\n");
    return 0;
}


