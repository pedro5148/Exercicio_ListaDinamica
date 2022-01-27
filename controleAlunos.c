#include <stdio.h>
#include <stdlib.h>

typedef struct dadosAlunos{
    char nome[20];
    int matricula;
    float nota1, nota2, nota3;
} tDadosAlunos; 

typedef struct No{
    tDadosAlunos dados;
    struct No *proximo;
} tNoEscola;

tNoEscola *criaNo(){
    tNoEscola *novoNo = (tNoEscola *) malloc(sizeof(tNoEscola));
    return novoNo;
}

void criaEstrutura(tNoEscola **info){
    *info = NULL;
}

void cabecalho(){
    for (int i = 0; i < 60; i++) printf("-"); printf("\n");
}

int menu(){
    int opcao;
    cabecalho();
    printf("\tGerenciamento de alunos da escola\n\nEscolha uma opção: \n\t1 - Incluir aluno no inicio da lista\n\t2 - Inserir aluno no final da lista\n\t3 - Inserir aluno numa posição especifica\n\t4 - Remover aluno\n\t5 - Calcular a media das notas dos alunos\n\t6 - Salvar lista num arquivo\n\t7 - Limpar a lista\n\t8 - Pesquisar aluno pela matricula\n\t9 - Ver relação de alunos\n\t0 - Sair\nOpção escolhida: "); 
    scanf("%d", &opcao);
    cabecalho();
    return opcao;
}

int insereInicio(tNoEscola **lista, tDadosAlunos aluno){
    tNoEscola *novoNo = criaNo();

    if (novoNo){
        novoNo->dados = aluno;
        novoNo->proximo = *lista;
        *lista = novoNo;
        return 0;
    } else 
        return 1;
}

int insereFinal(tNoEscola **lista, tDadosAlunos aluno){
    tNoEscola *aux, *novoNo = criaNo();
    if (novoNo) {
        novoNo->dados = aluno;
        novoNo->proximo = NULL;                 //Marca a ultima posicao
        if (*lista == NULL) {                   //Se a lista estiver vazia
            *lista = novoNo;
        } else {
            aux = *lista;
            while (aux->proximo != NULL) {      //Procura o fim da lista
                aux = aux->proximo;
            }
            aux->proximo = novoNo;
        }
        return 0;
    } else 
        return 1;
}

int insereNaPosicao(tNoEscola **lista, tDadosAlunos aluno, int posicao){
    tNoEscola *atual, *anterior, *novoNo = criaNo();
    int contador;
    if (novoNo) {
        novoNo->dados = aluno;
        atual = *lista;                 // Marcando inicio da lista
        anterior = NULL;                // Marcando fim da lista
        contador = 1;
        while (atual != NULL && contador < posicao) {
            anterior = atual;
            atual = atual->proximo;
            contador++;
        }
        if (posicao < 1 || atual == NULL) {
            return 2;                   //Posicao invalida
        } else if (posicao == 1) {
            novoNo->proximo = *lista;
            *lista = novoNo;
        } else {                        //Inserindo na posicao escolhida.
            novoNo->proximo = atual;
            anterior->proximo = novoNo;
        }
        return 0;
    } else 
        return 1;
}

int removeAluno(tNoEscola **lista, tDadosAlunos *aluno, int posicao){
    tNoEscola *atual, *anterior;
    int contador;

    atual = *lista;
    anterior = NULL;
    contador = 1;
    while (atual != NULL && contador < posicao)  {
        anterior = atual;
        atual = atual->proximo;
        contador++;
    }
    if (posicao < 1 || atual == NULL) {
        return 1;
    } else if (posicao == 1) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
        *aluno = atual->dados;
    }
    free(atual);
    return 0;
}

int calculaMedia(tNoEscola *lista, tDadosAlunos *aluno, int matricula){
    tNoEscola *atual;
    // Corrigir erro ao informar matricula errada
    for (atual = lista; atual != NULL && atual->dados.matricula != matricula; atual = atual->proximo);
    *aluno = atual->dados;
    
    return 0;
}

void imprimiAlunos(tNoEscola *lista){
    tNoEscola *aux = lista;
    int i = 0,j = 0, opcao;
    printf("\n\tOs alunos cadastrados sao:\n");
    if (aux == NULL) {
        printf("\n--> A lista esta vazia.\n\n"); 
    } else {
        while (aux != NULL){
        printf("\n\t### Posição [%d]\n", i + 1);
        printf("--> Nome: %s\n", aux->dados.nome);
        printf("--> Matricula: %d\n", aux->dados.matricula);
        printf("--> %dª Nota: %.2f\n",++j, aux->dados.nota1);
        printf("--> %dª Nota: %.2f\n",++j, aux->dados.nota2);
        printf("--> %dª Nota: %.2f\n",++j, aux->dados.nota3);
        aux = aux->proximo;
        i++;
        j = 0;
        }
    }
}

int mostrarAluno(tNoEscola *lista, tDadosAlunos *aluno, int matricula){
    //Corrigir se matricula estiver errada
    tNoEscola *atual, *anterior;
    int contador;

    atual = lista;
    anterior = NULL;
    contador = 1;
    while (atual != NULL && atual->dados.matricula != matricula) {
        anterior = atual;
        atual = atual->proximo;
        contador++;
    }
    if (atual->dados.matricula != matricula) {
        return 1;
    } else if (atual == NULL) {
        return 2;
    }else {
        *aluno = atual->dados;
        return 0;
    }
}

void gravaArquivo(tNoEscola *lista, tDadosAlunos aluno, char nome[]){
    tNoEscola *atual;
    int i = 0, cont = 0;
    FILE *arq = fopen(nome,"w");
    for (atual = lista; atual != NULL; atual = atual->proximo) {
        cont++;
        fprintf(arq, "--> Relação de alunos cadastrados: \n");
        fprintf(arq, "Posição[%d]: \n", i + 1);
        fprintf(arq, "\tNome: %s\n", atual->dados.nome);
        fprintf(arq, "\tMatricula: %d\n", atual->dados.matricula);
        fprintf(arq, "\t%d Nota: %.2f\n", i, atual->dados.nota1);
        fprintf(arq, "\t%d Nota: %.2f\n", i, atual->dados.nota2);
        fprintf(arq, "\t%d Nota: %.2f\n", i, atual->dados.nota3);
    }
    printf("O nome escolhido foi: %s\n", nome);
    printf("O valor do contador é: %d\n", cont);
    
    fclose(arq);
}

void limpaLista(tNoEscola **lista){
    tNoEscola *atual, *anterior;
    atual = *lista;
    anterior = NULL;
    while (atual != NULL) {
        anterior = atual;
        atual = atual->proximo;
        free(anterior);
    }
    printf("\n--> Lista apagada com sucesso!\n");
}

int main(){
    tDadosAlunos alunos;
    tNoEscola *info;
    int valida, opcao, aux, pos, i = 0, j = 0;
    char nomeArq[20];

    criaEstrutura(&info);

    do {
        opcao = menu();
        //printf("\nA opcao escolhida foi %d\n", opcao);
        switch (opcao) {
        case 1:             // Insere no inicio
            system("clear");
            printf("Digite as informações do aluno:\n");
            do {
                printf("-->Digite o nome do aluno: "); scanf(" %[^\n]", alunos.nome);
                printf("-->Digite a matricula: "); scanf("%d", &alunos.matricula);
                printf("-->Digite a [%d] nota do aluno: ", ++i); scanf("%f", &alunos.nota1);
                printf("-->Digite a [%d] nota do aluno: ", ++i); scanf("%f", &alunos.nota2);
                printf("-->Digite a [%d] nota do aluno: ", ++i); scanf("%f", &alunos.nota3);
                valida = insereInicio(&info, alunos);
                printf("\n\tDeseja inserir um novo aluno? (1-sim / 0-nao): "); scanf("%d", &aux);
                system("clear");
                i = 0;
                j++;
            } while (aux != 0);
            if (valida == 0) {
                printf("\n\t[%d] Alunos cadastrados com sucesso!\n", j);
            } else {
                printf("\nErro");
            }
            break;
        case 2:             // Insere no fim
            system("clear");
            printf("Digite as informações do aluno:\n");
            do {
                printf("-->Digite o nome do aluno: "); scanf(" %[^\n]", alunos.nome);
                printf("-->Digite a matricula: "); scanf("%d", &alunos.matricula);
                printf("-->Digite a [%d] nota do aluno: ", ++i); scanf("%f", &alunos.nota1);
                printf("-->Digite a [%d] nota do aluno: ", ++i); scanf("%f", &alunos.nota2);
                printf("-->Digite a [%d] nota do aluno: ", ++i); scanf("%f", &alunos.nota3);
                valida = insereFinal(&info, alunos);
                printf("\n\tDeseja inserir um novo aluno? (1-sim / 0-nao): "); scanf("%d", &aux);
                system("clear");
                i = 0;
                j++;
            } while (aux != 0);
            if (valida == 0) {
                printf("\n\t[%d] Alunos cadastrados com sucesso!\n", j);
            } else {
                printf("\nErro");
            }
            break;
        case 3:             // insere na posicao 
            system("clear");
            printf("\nNao sabe a posição?\nDeseja ver a lista de alunos? (1-sim / 0-nao): "); scanf("%d", &aux);
            if (aux == 0) {
                printf("\nInforme em qual posição deseja adicionar o novo aluno: "); scanf("%d", &aux);
                printf("\nDigite as informações do aluno:\n");
                printf("-->Digite o nome do aluno: "); scanf(" %[^\n]", alunos.nome);
                printf("-->Digite a matricula: "); scanf("%d", &alunos.matricula);
                printf("-->Digite a [%d] nota do aluno: ", i + 1); scanf("%f", &alunos.nota1);
                printf("-->Digite a [%d] nota do aluno: ", i + 2); scanf("%f", &alunos.nota2);
                printf("-->Digite a [%d] nota do aluno: ", i + 3); scanf("%f", &alunos.nota3);
                valida = insereNaPosicao(&info, alunos, aux);
                system("clear");
                if (valida == 0) 
                    printf("\n\tAluno cadastrado com sucesso na posição %d!\n", aux);
                else if (valida == 1) {
                    printf("\nA lista esta vazia!\n");
                } else if (valida == 2){
                    printf("\nPosição invalida!\n");
                }
            } else if (aux == 1) {
                imprimiAlunos(info);    
            }
            break;
        case 4:             // Remover aluno
            system("clear");
            printf("\nNao sabe o numero da posicao?\nDeseja ver a lista de alunos? (1-sim / 0-nao): "); scanf("%d", &aux);
            if (aux == 0) {
                printf("\nInforme o numero da posicao que deseja remover: "); scanf("%d", &aux);
                valida = removeAluno(&info, &alunos, aux);
                if (valida == 0) {
                    printf("\nAluno(a) [%s] removido com sucesso!\n", alunos.nome);
                } else if (valida == 1) {
                    printf("\nNao existe aluno cadastrado nessa posicao.\n");
                }
            } else if (aux == 1) {
                imprimiAlunos(info);
            }
            break;
        case 5:             // Calcular media
            system("clear");
            printf("\nCalculando a media\n");
            printf("\nInforme o numero da matricula: "); scanf("%d", &aux);
            system("clear");
            valida = calculaMedia(info, &alunos, aux);
            if (valida == 0) {
                printf("\nMatricula: %d\n", aux);
                printf("--> Nome: %s\n", alunos.nome);
                printf("--> 1ª Nota: %.2f\n",alunos.nota1);
                printf("--> 2ª Nota: %.2f\n",alunos.nota2);
                printf("--> 3ª Nota: %.2f\n",alunos.nota3);
                printf("\nResultado final: %.2f\n", (alunos.nota1 + alunos.nota2 + alunos.nota3) / 3);
            } else if (valida != 0) {
                printf("\nA lista esta invalida\n");
            }
            break;
        case 6:             // Salvar num arquivo
            system("clear");
            printf("\nDeseja informar um nome para o arquivo? (1-sim / 2-nao): "); scanf("%d", &aux);
            if (aux == 1) {
                printf("Infome o nome desejado: "); scanf(" %[^\n]", nomeArq);
                gravaArquivo(info, alunos, nomeArq);
            }
            
            break;
        case 7:
            system("clear");
            limpaLista(&info);
            break;
        case 8:
            system("clear");
            printf("\nInforme o numero da matricula: "); scanf("%d", &aux);
            valida = mostrarAluno(info, &alunos, aux);
            if (valida == 0) {
            printf("\nMatricula: %d\n", aux);
            printf("--> Nome: %s\n", alunos.nome);
            printf("--> 1ª Nota: %.2f\n",alunos.nota1);
            printf("--> 2ª Nota: %.2f\n",alunos.nota2);
            printf("--> 3ª Nota: %.2f\n",alunos.nota3);
        } else if (valida == 1) {
            printf("\nNumero de matricula nao encontrado, verifique!\n");
        } else if (valida == 2)
        {
            printf("\nA lista esta vazia.\n");
        }
            break;
        case 9:
            system("clear");
            imprimiAlunos(info);
            break;
        case 0:
            system("clear");
            printf("\nSaindo...\n");
            exit (1);
            break;
        default:
            system("clear");
            printf("\nOpcao Invalida, verifique!\n");
            break;
        }
    } while (opcao != 0);
    


    

    return 0;
}