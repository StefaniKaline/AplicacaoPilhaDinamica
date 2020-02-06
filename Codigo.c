#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <locale.h>
#include<ctype.h>

//Criar a struct para o tipo ENCOMENDA
typedef struct sENCOMENDA {
    float volume;
    float distancia;
    int tentativa_ent; //Vari�vel referente ao n�mero de tentativas de entrega
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

//Criar uma nova c�lula
CELULA* Criar_Celula () {
    return (CELULA*)malloc(sizeof(CELULA));
}

//Liberar c�lula
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

//Fun��es implementadas para as pilhas
//Fun��o para empilhar
void Empilhar (PILHA* pilha, ENCOMENDA x) {
    CELULA* q;
    q = Criar_Celula();
    if (q == NULL) {
        printf("ERRO: Falha na aloca��o de um n�.\n");
    } else {
        q->info = x;
        q->next = (pilha->pTopo);
        (pilha->pTopo) = q;
        pilha->tamanho++;
    }
}

//Fun��o para empilhar na pilha de n�o entregues
void EmpilharNEntregue (PILHA* pilha, ENCOMENDA x) {
    CELULA* q;
    q = Criar_Celula();
    if (q == NULL) {
        printf("ERRO: Falha na aloca��o do n�.\n");
    } else {
        q->info = x;
        q->info.tentativa_ent = (q->info.tentativa_ent) + 1;
        q->next = pilha->pTopo;
        pilha->pTopo = q;
        pilha->tamanho++;
    }
}

//Fun��o para desempilhar
ENCOMENDA Desempilhar (PILHA* pilha) {
    ENCOMENDA x;
    x.distancia = -1;
    x.volume = -1;
    x.tentativa_ent = -1;
    strcpy(x.endereco, "Inv�lido");
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

//Fun��es implementadas para a lista ordenada
//Inicializar a lista
void Inicializar_Lista (CELULA** pLista) {
     *pLista = NULL;
}

//Verificar se a lista est� vazia
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
        printf("ERRO: Falha na aloca��o do n�.\n");
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
    strcmp(x.endereco, "Inv�lido");
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

//Tamanho da lista (Fun��o recursiva)
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

//FUN��ES PR�PRIAS PARA O APLICATIVO
//Carregar caminh�o
void Carregar_Caminhao (PILHA* pilha, CELULA** pLista) {
    if (Lista_Vazia(*pLista)) {
        printf("*N�o h� entregas a serem feitas.\n*Registre as encomendas no sistema para come�ar!");
    } else {
        int contador, i;
        float volume = 0;
        contador = Tamanho_Lista(*pLista);
        ENCOMENDA enc;
        printf("\n*********************************************************\n\n");
        printf("\tENCOMENDAS A SEREM ENTREGUES NA PR�XIMA VIAGEM\n");
        printf("\n*********************************************************\n\n");
        for(i = 1; i <= contador; i++) {
            enc = Remover_ListaO(pLista);
            volume = volume + enc.volume;
            printf("Endereco: %sVolume: %0.2f m�\nTentativas de entregas: %d\nDist�ncia: %0.2f km\n\n", enc.endereco, enc.volume, enc.tentativa_ent, enc.distancia);
            Empilhar(pilha, enc);
        }
        printf("Volume da carga total: %0.2f m�\n", volume);
        printf("\n*********************************************************\n\n");
    }
}

//Entregar encomenda
//Deve verificar se a entrega foi realmente feita
void Entregar_Encomenda (PILHA* pilha, PILHA* pilhaAux) {
    if (Pilha_Vazia(*pilha)) {
        printf("*N�o h� mais encomendas a serem entregues! Volte a central\n");

    } else {
        ENCOMENDA enc;
        enc = Desempilhar(pilha);
        printf("******************************************************************");
        printf("\n\nENCOMENDA:\nEndereco: %s\nVolume: %0.2f m�\nTentativas de entregas: %d\nDist�ncia: %0.2f km\n\n", enc.endereco, enc.volume, enc.tentativa_ent, enc.distancia);
        printf("Encomendas restantes: %d\n", pilha->tamanho );
        printf("******************************************************************\n\n");
        char entrega;
        do {
            printf("*A encomenda foi entregue � seu destinat�rio? (S ou N)\n");
            fflush(stdin);
            scanf("%c", &entrega);
        } while ((entrega != 'S') && (entrega != 'N'));

        if (entrega == 'N') {
            printf("\n\nViagem perdida! \nA encomenda retornar� a central\n");
            EmpilharNEntregue(pilhaAux, enc); //Passando a encomenda n�o entregue para a pilha auxiliar
        } else {
            printf("Entrega bem sucedida!\n");
        }
    }
}

//Inserir as encomendas da pilha de n�o entregues na lista ordenada
void Reorganizar_ListaO (PILHA* pilhaAux, CELULA** pLista) {
    if (Pilha_Vazia(*pilhaAux)) {
        printf("*Todas as encomendas da �ltima viagem foram entregues!\n");
    } else {
        ENCOMENDA enc;
        int i, contador = pilhaAux->tamanho;
        for (i = 0; i < contador; i++) {
            enc = Desempilhar(pilhaAux);
            if (enc.tentativa_ent <= 3) {
                InserirOrdenado(pLista, enc);
            } else {
                printf("*O limite de tentativas de entrega j� foi atingido!\nA encomenda permanecer� na central at� que o propriet�rio v� retir�-la\n");
                printf("\n\nENCOMENDA:\nEndereco: %sVolume: %0.2f m�\nTentativas de entregas: %d\nDist�ncia: %0.2f km\n\n", enc.endereco, enc.volume, enc.tentativa_ent, enc.distancia);
            }
        }
    }
}

//Exibir a lista ordenada
void Exibir_Lista (CELULA* pLista) {
    if (Lista_Vazia(pLista)) {
        printf("A lista est� vazia\n");

    } else {
        CELULA* aux;
        aux = pLista;
        while (aux != NULL) {
            printf("\nEndereco: %sVolume: %0.2f m�\nTentativas de entregas: %d\nDist�ncia: %0.2f km\n\n", (aux->info.endereco), (aux->info.volume), (aux->info.tentativa_ent), (aux->info.distancia));
            aux=aux->next;
        }
        printf("\n");
    }
}
int main() {

    //Acentua��o
    setlocale(LC_ALL, "Portuguese");

    //Cores de fonte e fundo
    system("color 0B");

    PILHA pilha; //Pilha de encomendas
    PILHA pilhaAux; //Pilha para as encomendas n�o entregues
    CELULA* lista; //Lista para ordenar as encomendas

    //Inicializa��o das estruturas utilizadas
    Inicializar_Pilha(&pilhaAux);
    Inicializar_Pilha(&pilha);
    Inicializar_Lista(&lista);

    //Vari�vel para escolher a op��o
    int opcao;

    //Vari�veis auxiliares
    int cont, i, v;

    ENCOMENDA enc;
    //Menu
    do {
        printf("\n\n\t\tBEM - VINDO AO SEU NOVO GERENCIADOR DE ENTREGAS!\n");
        printf("*******************************************************************************\n");
        printf("Hora de come�ar o dia! Escolha uma das op��es:\n\n");
        printf("( 0 ) Para sair do programa\n( 1 ) Verificar se h� encomendas a serem entregues\n( 2 ) Inserir encomendas\n( 3 ) Carregar caminh�o\n( 4 ) Entregar encomenda\n( 5 ) Reorganizar a lista de entregas\n");
        printf("*******************************************************************************\n");
        printf("Op��o: ");
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
                    printf("Digite a dist�ncia entre a central de Correio e o destino: ");
                    fflush(stdin); //Foi preciso limpar o buffer, pois n�o estava sendo feita a leitura da dist�ncia
                    scanf("%f", &enc.distancia);
                } while (enc.distancia <= 0);
                do {
                    printf("Digite o endere�o do destino: ");
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
                printf("As encomendas n�o entregues retornaram a central e foram reorganizadas!\n");
                printf("*******************************************************************************\n");
                break;
            default:
                system("cls");
                printf("*******************************************************************************\n");
                printf("Op��o inv�lida!\n");
                printf("*******************************************************************************\n");
        }
    } while(opcao != 0);
    system("cls");
    printf("*******************************************************************************\n");
    printf("Fim das opera��es!\n");
    printf("*******************************************************************************\n");
    return 0;
}


