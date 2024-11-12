#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>
#include "header.h"

#define RESET_COR    "\x1b[0m"

#define PRETO        "\x1b[30m"
#define VERMELHO     "\x1b[31m"
#define VERDE        "\x1b[32m"
#define AMARELO      "\x1b[33m"
#define AZUL         "\x1b[34m"
#define MAGENTA      "\x1b[35m"
#define CIANO        "\x1b[36m"
#define BRANCO       "\x1b[37m"

#define ANSI_BACKGROUND_BLACK   "\x1b[40m"
#define ANSI_BACKGROUND_RED     "\x1b[41m"
#define ANSI_BACKGROUND_GREEN   "\x1b[42m"
#define ANSI_BACKGROUND_YELLOW  "\x1b[43m"
#define ANSI_BACKGROUND_BLUE    "\x1b[44m"
#define ANSI_BACKGROUND_MAGENTA "\x1b[45m"
#define ANSI_BACKGROUND_CYAN    "\x1b[46m"
#define ANSI_BACKGROUND_WHITE   "\x1b[47m"

#define NEGRITO       "\x1b[1m"
#define ITALICO       "\x1b[3m"
#define SUBLINHADO    "\x1b[4m"

ptr_list_d cria_list_d(){   //função que cria lista de doentes
    ptr_list_d aux;
    doente_dados p1;
    p1.id = 0;
    strcpy(p1.nome, "");
    p1.data.dia = 0;
    p1.data.mes = 0;
    p1.data.ano = 0;
    strcpy(p1.num_cidadao, "");
    p1.num_telefone = 0;
    strcpy(p1.email, "");

    aux = (ptr_list_d) malloc (sizeof (element_list_d));
    if (aux != NULL) {
        aux->data_doente = p1;
        aux->prox = NULL;
    }
    return aux;
}

ptr_list_r cria_list_r(){   //função que cria lista de registos
    ptr_list_r aux;
    doente_registos p1;
    p1.id = 0;
    p1.data.dia = 0;
    p1.data.mes = 0;
    p1.data.ano = 0;
    p1.ten_max = 0;
    p1.ten_min = 0;
    p1.peso = 0;
    p1.altura = 0;

    aux = (ptr_list_r) malloc (sizeof (element_list_r));
    if (aux != NULL) {
        aux->registo = p1;
        aux->prox = NULL;
    }
    return aux;
}

int vazia_d(ptr_list_d ptr){    //função que verifica que a lista de doentes está vazia
    return ptr == NULL || ptr->prox == NULL;
}

int vazia_r(ptr_list_r ptr){    //função que verifica que a lista de registos está vazia
    return ptr == NULL || ptr->prox == NULL;
}

ptr_list_d destroi_d(ptr_list_d ptr){   //função que destroi a lista de doentes
    ptr_list_d temp_ptr;
    while (!vazia_d (ptr)) {
        temp_ptr = ptr;
        ptr = ptr->prox;
        free (temp_ptr);
    }
    free(ptr);
    return NULL;
}

ptr_list_r destroi_r(ptr_list_r ptr){   //função que destroi a lista de registos
    ptr_list_r temp_ptr;
    while (!vazia_r (ptr)) {
        temp_ptr = ptr;
        ptr = ptr->prox;
        free (temp_ptr);
    }
    free(ptr);
    return NULL;
}

void procura_lista_d(ptr_list_d lista, int chave, ptr_list_d *ant, ptr_list_d *actual){    //função que procura um elemento por id na lista de doentes
    *ant = lista; 
    *actual = lista->prox;
    while ((*actual) != NULL && (*actual)->data_doente.id < chave){
        *ant = *actual;
        *actual = (*actual)->prox;
    }
    if ((*actual) != NULL && (*actual)->data_doente.id != chave)
        *actual = NULL;
}

int procura_lista_r(ptr_list_r lista, int chave, ptr_list_r *ant, ptr_list_r *actual) {
    *ant = lista; 
    *actual = lista->prox;
    while ((*actual) != NULL && (*actual)->registo.id < chave) {
        *ant = *actual;
        *actual = (*actual)->prox;
    }
    if (*actual == NULL || (*actual)->registo.id != chave) {
        *actual = NULL;
        return 0;
    }
    return 1;
}

void inserir_lista_d(ptr_list_d ptr_d, doente_dados p1){    //função que insere um elemento na lista de doentes por ordem de id
    ptr_list_d no, ant, inutil;
    no = (ptr_list_d) malloc (sizeof (element_list_d));
    if (no != NULL){
        no->data_doente = p1;
        procura_lista_d(ptr_d, p1.id, &ant, &inutil);
        no->prox = ant->prox;
        ant->prox = no;
    }
}

void inserir_lista_r(ptr_list_r ptr_r, doente_registos p1){    //função que insere um elemento na lista de registos
    ptr_list_r no, ant, inutil;
    no = (ptr_list_r) malloc (sizeof (element_list_r));
    if (no != NULL){
        no->registo = p1;
        procura_lista_r(ptr_r, p1.id, &ant, &inutil);
        no->prox = ant->prox;
        ant->prox = no;
    }
}

void elimina_d(ptr_list_d ptr, int chave){  //função que elimina um elemento da lista de doente
    ptr_list_d ant;
    ptr_list_d actual;
    procura_lista_d(ptr, chave, &ant, &actual);
    if (actual != NULL) {
        ant->prox = actual->prox;
        free (actual);
    }
}

void elimina_r(ptr_list_r ptr, int chave){  //função que elimina um elemento da lista de registos
    ptr_list_r ant;
    ptr_list_r actual;
    procura_lista_r(ptr, chave, &ant, &actual);
    if (actual != NULL) {
        ant->prox = actual->prox;
        free (actual);
    }
}

void procura_alfabeto(ptr_list_d lista, char chave[], ptr_list_d *ant, ptr_list_d *actual){     //função que procura um elemento na lista de doentes que está por ordem alfabética
    *ant = lista; *actual = lista->prox;
    while ((*actual) != NULL && (strcasecmp((*actual)->data_doente.nome, chave) < 0)){
        *ant = *actual;
        *actual = (*actual)->prox;
    }
    if ((*actual) != NULL && !(strcasecmp((*actual)->data_doente.nome, chave))){
        *actual = NULL;
    }
}

void insere_alfabeto(ptr_list_d lista, doente_dados p1){    //função que insere um elemento na lista de doentes organizada alfabéticamente
    ptr_list_d no, ant, inutil;
    no = (ptr_list_d) malloc (sizeof(doente_dados));
    if (no != NULL){
        no->data_doente = p1;
        procura_alfabeto(lista, p1.nome, &ant, &inutil);
        no->prox = ant->prox;
        ant->prox = no;
    }
}

void MsgSistema(const char *mensagem) {
    printf(AMARELO"\n[SISTEMA] " RESET_COR "%s", mensagem);
}

void AvisoSistema(const char *mensagem) {
    printf(AMARELO"[\nSISTEMA] %s" RESET_COR, mensagem);
}

void AvisoCriticoSistema(const char *mensagem) {
    printf(VERMELHO"\n[SISTEMA] %s" RESET_COR, mensagem);
}

void AvisoVerdeSistema(const char *mensagem) {
    printf(VERDE"\n[SISTEMA] %s" RESET_COR, mensagem);
}

void Negrito(const char *mensagem) {
    printf(NEGRITO"%s" RESET_COR, mensagem);
}

void AdicionarDoente(ptr_list_d ptr_d) {    //função pedida na enunciado 1#
    doente_dados p1;
    int id = 0, name_check = 0, telemovel_check = 0, email_check = 0;
    char str[41], num_telemovel[12];

    ptr_list_d temp = ptr_d->prox;    
    while (temp != NULL) {
        if (temp->data_doente.id > id) {
            id = temp->data_doente.id;
        }
        temp = temp->prox;
    }
    p1.id = id + 1;

    while (name_check == 0)
    {
        MsgSistema("Introduza o nome do utente: ");
        getchar();
        fgets(str, 41, stdin);
        str[strlen(str) - 1] = '\0';
        
        int valid_name = 1;
        for (size_t i = 0; i < strlen(str); i++) {
            if (isdigit(str[i])) {
                valid_name = 0;
                break;
            }
        }

        if (valid_name) {
            strcpy(p1.nome, str);
            name_check = 1;
        } else {
            AvisoSistema("O nome não pode conter dígitos. Por favor, tente novamente.");
        }
    }

    int info_correta = 0;
    while (info_correta == 0)
    {
        MsgSistema("Introduza a data de nascimento do utente (formato: DD/MM/AAAA): ");
        scanf("%d/%d/%d", &p1.data.dia, &p1.data.mes, &p1.data.ano);
        info_correta = VerificaData(p1.data.dia, p1.data.mes, p1.data.ano);
    }

    MsgSistema("Introduza o número do cartão de cidadão do utente: ");
    scanf("%*[^\n]");
    getchar();
    fgets(str, 41, stdin);
    str[strlen(str) - 1] = '\0';
    strcpy(p1.num_cidadao, str);

    while (telemovel_check == 0) {
        MsgSistema("Introduza o número de telefone do utente: ");
        fgets(num_telemovel, sizeof(num_telemovel), stdin);
        num_telemovel[strcspn(num_telemovel, "\n")] = '\0';
        if (num_telemovel[0] == '\0') {
            AvisoSistema("Nenhum número de telefone foi inserido. Por favor, tente novamente.");
        } else {
            for (int i = 0; num_telemovel[i] != '\0'; i++) {
                if (num_telemovel[i] < '0' || num_telemovel[i] > '9') {
                    AvisoSistema("Apenas pode introduzir dígitos! Tente novamente.");
                    break;
                } else {
                    telemovel_check = 1;
                    p1.num_telefone = atoi(num_telemovel);
                }
            }
        }
    }

    while (email_check == 0) {
        MsgSistema("Introduza o email do utente: ");
        fgets(str, sizeof(str), stdin);
        str[strcspn(str, "\n")] = '\0';
        strcpy(p1.email, str);
        if (strchr(p1.email, '@') == NULL) {
            AvisoSistema("Email introduzido não contem @");
        } else {
            email_check = 1;
        }
    }

    inserir_lista_d(ptr_d, p1);
    printf(VERDE"✅ Utente inserido com sucesso com o ID: %d!\n"RESET_COR, p1.id);
    upload_doentes_arquivo(ptr_d);
}

void RemoverDoente(ptr_list_d ptr_d, ptr_list_r ptr_r) {    //função pedida no enunciado 2#
    ptr_list_d doente, ant;
    int n, confirmacao;
    MsgSistema("Introduza o ID do utente que quer eliminar: ");
    scanf("%d", &n);
    procura_lista_d(ptr_d, n, &ant, &doente);
    if (doente != NULL) {
        printf("[SISTEMA] ⚠️ Pretende eliminar o utente %s ? (1 - Sim | 2 - Não): ",doente->data_doente.nome);
        scanf("%d",&confirmacao);
        if(confirmacao == 1) {
            printf("[SISTEMA] ⚠️ O utente %s (ID: %d) foi eliminado.\n",doente->data_doente.nome,doente->data_doente.id);
            EliminaRegistros(ptr_r, n);
            elimina_d(ptr_d, n);
        } else if (confirmacao == 2) {
            AvisoCriticoSistema("⚠️ Eliminação do utente abortada!\n");
        } else {
            AvisoCriticoSistema("⚠️ Opção não válida.\n");
        }
        upload_doentes_arquivo(ptr_d);
    } else {
        printf("[SISTEMA] ⚠️ Utente com o ID %d não encontrado.\n", n);
    }
}

void RemoverRegistros(ptr_list_r ptr_r) {   //função que elimina os registos de um doente
    ptr_list_r doente, ant;
    int n, confirmacao;
    MsgSistema("Introduza o ID do utente que quer eliminar os registos: ");
    scanf("%d", &n);
    procura_lista_r(ptr_r, n, &ant, &doente);
    if (doente != NULL) {
        printf("[SISTEMA] ⚠️ Pretende eliminar o utente com o ID %d ? (1 - Sim | 2 - Não): ", doente->registo.id);
        scanf("%d",&confirmacao);
        if(confirmacao == 1) {
            printf("[SISTEMA] ⚠️ Os registos do utente com o ID %d foram eliminados.\n", doente->registo.id);
            EliminaRegistros(ptr_r, n);
        } else if (confirmacao == 2) {
            printf("[SISTEMA] ⚠️ Eliminação do utente abortada!\n");
        } else {
            printf("[SISTEMA] ⚠️ Opção não válida.\n");
        }
        upload_registos_arquivo(ptr_r);
    } else {
        printf("⚠️ Utente com o ID %d não encontrado.\n", n);
    }
}


void EliminaRegistros(ptr_list_r ptr, int id) { //função que elimina os registos de um doente(parte 2)
    ptr_list_r temp_r = ptr;
    int cont = 0;
    while (temp_r != NULL) {
        if (temp_r->registo.id == id) {
            cont++;
        }
        temp_r = temp_r->prox;
    }
    for (int i = 0; i < cont; i++){
        elimina_r(ptr, id);
    }
}

void ListarAlfabeticamente(ptr_list_d ptr_d){   //função pedida no enunciado 3#
    ptr_list_d lista_ordenada = cria_list_d();
    doente_dados p1;
    ptr_list_d current;
    current = ptr_d->prox;

    while (current != NULL){
        p1 = current->data_doente;
        insere_alfabeto(lista_ordenada, p1);
        current = current->prox;
    }

    current = lista_ordenada->prox;
    while (current != NULL){
        printf("------\n");
        printf("%s\n", current->data_doente.nome);
        current = current->prox;
    }
    printf("------");

    destroi_d(lista_ordenada);
}

void ListarDoentesAcimaTMAX(ptr_list_r ptr){    //função pedida no enunciado 4# 
    float limite;
    ptr_list_r lista_ordenada = cria_list_r();
    ptr_list_r atual = ptr->prox;

    MsgSistema("Introduza o valor a partir do qual quer que as tensões sejam apresentadas: ");
    scanf("%f", &limite);

    while (atual != NULL) {  
        if (atual->registo.ten_max > limite){
            ptr_list_r novo_no = (ptr_list_r)malloc(sizeof(element_list_r));
            if (novo_no == NULL) {
                printf("erro!");
            }
            novo_no->registo = atual->registo;
            novo_no->prox = NULL;

            ptr_list_r temp = lista_ordenada;
            while (temp->prox != NULL && temp->prox->registo.ten_max > atual->registo.ten_max) {
                temp = temp->prox;
            }
            novo_no->prox = temp->prox;
            temp->prox = novo_no;
        }
        atual = atual->prox;
    }

    ptr_list_r current = lista_ordenada->prox;

    while (current != NULL){
        printf("------------\n");
        printf("ID : %d\n", current->registo.id);
        printf("Valor: %f\n", current->registo.ten_max);
        current = current->prox;
    }

    printf("------------\n");

    destroi_r(lista_ordenada);
    free(atual);
}

void RegistrosDoente(ptr_list_r ptr, ptr_list_d ptr_d) {
    doente_registos p1;
    int n;
    char id_str[10];
    int id;
    float f;
    ptr_list_d findID,aux;
    
    MsgSistema("Introduza o ID do utente: ");
    while (1) {
        if (scanf("%s", id_str) != 1) {
            AvisoSistema("Entrada inválida. Por favor, insira um número inteiro: ");
            while (getchar() != '\n');
        } else {
            id = atoi(id_str);
            procura_lista_d(ptr_d, id, &aux, &findID);
            if (id == 0 && id_str[0] != '0') {
                AvisoSistema("Entrada inválida. Por favor, insira um número inteiro: ");
            } else if (findID == NULL) {
                AvisoSistema("Nenhum utente encontrado com o ID fornecido. Por favor, tente novamente: ");
            } else {
                break;
            }
        }
    }
    p1.id = id;

    MsgSistema("Introduza a data do registo (DD/MM/AAAA): ");
    int info_correta = 0;
    while (info_correta == 0) {
        scanf("%d/%d/%d", &p1.data.dia, &p1.data.mes, &p1.data.ano);
        info_correta = VerificaData(p1.data.dia, p1.data.mes, p1.data.ano);
        if (!info_correta) {
            AvisoSistema("Data inválida. Tente novamente.");
        }
    }

    MsgSistema("Introduza a tensão máxima do utente: ");
    while (scanf("%f", &f) != 1) {
        AvisoSistema("Introduza apenas dígitos: ");
        while (getchar() != '\n');
    }
    getchar();
    p1.ten_max = f;

    MsgSistema("Introduza a tensão mínima do utente: ");
    while (scanf("%f", &f) != 1) {
        AvisoSistema("Introduza apenas dígitos: ");
        while (getchar() != '\n');
    }
    p1.ten_min = f;

    MsgSistema("Introduza o peso do utente em KG: ");
    while (scanf("%d", &n) != 1) {
        AvisoSistema("Introduza apenas dígitos: ");
        while (getchar() != '\n');
    }
    p1.peso = n;

    MsgSistema("Introduza a altura do utente em metros: ");
    while (scanf("%f", &f) != 1) {
        AvisoSistema("Introduza apenas dígitos: ");
        while (getchar() != '\n');
    }
    p1.altura = f;

    inserir_lista_r(ptr, p1);
    upload_registos_arquivo(ptr);
}

void imprimir_doente(ptr_list_d ptr_d, ptr_list_r ptr_r, int registros_com_dados) {    //função pedida no enunciado 5#
    ptr_list_d doente, ant;
    int n;
    MsgSistema("Introduza o ID do utente que quer obter informações: ");
    scanf("%d", &n);
    procura_lista_d(ptr_d, n, &ant, &doente);
    if (doente != NULL) {
        struct tm *data_atual;
        time_t t;
        time(&t);
        data_atual = localtime(&t);
        int ano_atual = data_atual->tm_year + 1900;
        int mes_atual = data_atual->tm_mon + 1;
        int dia_atual = data_atual->tm_mday;

        MsgSistema("Informações do Doente:\n");
        printf("| --------------------------- | --------------------------- |\n\n");

        int anos, meses, dias;

        if (ano_atual - doente->data_doente.data.ano < 0) {
            anos = ano_atual - doente->data_doente.data.ano + 1;
        } else {
            anos = ano_atual - doente->data_doente.data.ano;
        }

        if (mes_atual - doente->data_doente.data.mes < 0) {
            meses = mes_atual - doente->data_doente.data.mes + 12;
            anos--;
        } else {
            meses = mes_atual - doente->data_doente.data.mes;
        }

        if (dia_atual - doente->data_doente.data.dia < 0) {
            dias = dia_atual - doente->data_doente.data.dia + 30;
            meses--;
        } else {
            dias = dia_atual - doente->data_doente.data.dia;
        }

        printf(NEGRITO"ID: %d\n"RESET_COR, doente->data_doente.id);
        printf(NEGRITO"Nome: "RESET_COR"%s\n", doente->data_doente.nome);
        printf(NEGRITO"Data de Nascimento: "RESET_COR"%d/%d/%d "SUBLINHADO"(%d anos, %d meses e %d dias)\n"RESET_COR, 
               doente->data_doente.data.dia, 
               doente->data_doente.data.mes,
               doente->data_doente.data.ano,
               anos, meses, dias);
        printf(NEGRITO"Número de Cartão de Cidadão: "RESET_COR"%s\n", doente->data_doente.num_cidadao);
        printf(NEGRITO"Número de telemóvel: "RESET_COR"%d\n", doente->data_doente.num_telefone);
        printf(NEGRITO"Email: "RESET_COR"%s\n\n", doente->data_doente.email);
        printf("| --------------------------- | --------------------------- |\n");
        if(registros_com_dados == 1) {
            imprimir_registros_doente(ptr_r,n);
        }
        printf("\n");
    } else {
        AvisoCriticoSistema("❌ Utente não encontrado!\n");
    }
}


void imprimir_todos_doentes(ptr_list_d lista, ptr_list_r ptr_r, int registros_com_dados) {     //função que imprime as informações de todos os doentes
    ptr_list_d atual = lista->prox;
    struct tm *data_atual;
    time_t t;
    time(&t);
    data_atual = localtime(&t);
    int ano_atual = data_atual->tm_year + 1900;
    int mes_atual = data_atual->tm_mon + 1;
    int dia_atual = data_atual->tm_mday;

    MsgSistema("Informações do Doente:\n");
    printf("| --------------------------- | --------------------------- |\n\n");

    while (atual != NULL) {
        int anos, meses, dias;

        if (ano_atual - atual->data_doente.data.ano < 0) {
            anos = ano_atual - atual->data_doente.data.ano + 1;
        } else {
            anos = ano_atual - atual->data_doente.data.ano;
        }

        if (mes_atual - atual->data_doente.data.mes < 0) {
            meses = mes_atual - atual->data_doente.data.mes + 12;
            anos--;
        } else {
            meses = mes_atual - atual->data_doente.data.mes;
        }

        if (dia_atual - atual->data_doente.data.dia < 0) {
            dias = dia_atual - atual->data_doente.data.dia + 30;
            meses--;
        } else {
            dias = dia_atual - atual->data_doente.data.dia;
        }

        printf(NEGRITO"ID: %d\n"RESET_COR, atual->data_doente.id);
        printf(NEGRITO"Nome: " RESET_COR "%s\n", atual->data_doente.nome);
        printf(NEGRITO"Data de Nascimento: " RESET_COR "%d/%d/%d "SUBLINHADO"(%d anos, %d meses e %d dias)\n"RESET_COR, 
               atual->data_doente.data.dia, 
               atual->data_doente.data.mes,
               atual->data_doente.data.ano,
               anos, meses, dias);
        printf(NEGRITO"Número de Cartão de Cidadão: " RESET_COR "%s\n", atual->data_doente.num_cidadao);
        printf(NEGRITO"Número de telemóvel: " RESET_COR "%d\n", atual->data_doente.num_telefone);
        printf(NEGRITO"Email: " RESET_COR "%s\n\n", atual->data_doente.email);
        
        if(registros_com_dados == 1) {
            imprimir_registros_doente(ptr_r,atual->data_doente.id);
        }
        printf("| --------------------------- | --------------------------- |\n");
        printf("\n");

        atual = atual->prox;
    }
}

void AlterarDados(ptr_list_d ptr_d) {   //função que alterar dados de um doente já existente
    ptr_list_d doente, ant;
    int n, opcao_alterar_dados, info_correta;
    MsgSistema("Introduza o ID do utente que quer alterar dados: ");
    scanf("%d", &n);
    procura_lista_d(ptr_d, n, &ant, &doente);
    if (doente != NULL) {
        printf("Prentende alterar:\n 1 - Nome [Atual: %s]\n 2 - Data de nascimento [Atual: %d/%d/%d]\n 3 - Número de Cartão de Cidadão [Atual: %s]\n 4 - Número de telemóvel [Atual: %d]\n 5 - Email [Atual: %s]\n 6 - Voltar\nOPÇÃO: ", doente->data_doente.nome,doente->data_doente.data.dia, doente->data_doente.data.mes, doente->data_doente.data.ano,doente->data_doente.num_cidadao,doente->data_doente.num_telefone,doente->data_doente.email);
        scanf("%d", &opcao_alterar_dados);
        switch (opcao_alterar_dados) {
            case 1:
                printf(" -> Insira o novo nome do utente: ");
                getchar();
                fgets(doente->data_doente.nome, sizeof(doente->data_doente.nome), stdin);
                doente->data_doente.nome[strcspn(doente->data_doente.nome, "\n")] = 0;
                break;
            case 2:
                info_correta = 0;
                while (info_correta == 0)
                {
                    printf(" -> Insira a nova data de nascimento do utente (DD/MM/AAAA): ");
                    scanf("%d/%d/%d", &doente->data_doente.data.dia, &doente->data_doente.data.mes, &doente->data_doente.data.ano);
                    info_correta = VerificaData(doente->data_doente.data.dia, doente->data_doente.data.mes, doente->data_doente.data.ano);
                }
                break;
            case 3:
                printf(" -> Insira o novo número de Cartão de Cidadão do utente: ");
                getchar();
                fgets(doente->data_doente.num_cidadao, sizeof(doente->data_doente.num_cidadao), stdin);
                doente->data_doente.num_cidadao[strcspn(doente->data_doente.num_cidadao, "\n")] = 0;
                break;
            case 4:
                printf(" -> Insira o novo número de telemóvel do utente : ");
                scanf("%d", &doente->data_doente.num_telefone);
                break;
            case 5:
                printf(" -> Insira o novo email do utente: ");
                getchar();
                fgets(doente->data_doente.email, sizeof(doente->data_doente.email), stdin);
                doente->data_doente.email[strcspn(doente->data_doente.email, "\n")] = 0;
                break;
            case 6:
                AvisoCriticoSistema("🛑 Alteração de dados cancelada.\n");
                return;
            default:
                AvisoCriticoSistema("❌ Opção inválida.\n");
                return;
        }
        AvisoVerdeSistema("✅ Dados do utente alterados com sucesso!\n");
        upload_doentes_arquivo(ptr_d);
    } else {
        AvisoCriticoSistema("❌ Utente não encontrado!\n");
    }
}

void carregar_doentes_arquivo(ptr_list_d ptr_d) {   //função que lê os dados do doente no ficheiro doentes.txt
    FILE *arquivo;
    arquivo = fopen("doentes.txt", "r");

    if (arquivo == NULL) {
        AvisoCriticoSistema("Não foi possível encontrar/abrir o ficheiro dos doentes!\n");
        return;
    }

    while (!feof(arquivo)) {
        doente_dados novo_doente;
        if(fscanf(arquivo, "%d\n", &novo_doente.id) != 1) {
            break;
        } else {
            fgets(novo_doente.nome, sizeof(novo_doente.nome), arquivo);
            novo_doente.nome[strcspn(novo_doente.nome, "\n")] = '\0';
            fscanf(arquivo, "%d/%d/%d\n", &novo_doente.data.dia, &novo_doente.data.mes, &novo_doente.data.ano);
            fgets(novo_doente.num_cidadao, sizeof(novo_doente.num_cidadao), arquivo);
            novo_doente.num_cidadao[strcspn(novo_doente.num_cidadao, "\n")] = '\0';
            fscanf(arquivo, "%d\n", &novo_doente.num_telefone);
            fgets(novo_doente.email, sizeof(novo_doente.email), arquivo);
            novo_doente.email[strcspn(novo_doente.email, "\n")] = '\0';
            inserir_lista_d(ptr_d, novo_doente);
        }
    }

    fclose(arquivo);
}

void carregar_registros_arquivo(ptr_list_r ptr_r) {     //função que lê os registos do doente no ficheiro registos.txt
    FILE *arquivo;
    arquivo = fopen("registos.txt", "r");

    if (arquivo == NULL) {
        AvisoCriticoSistema("Não foi possível encontrar/abrir o ficheiro dos registos!\n");
        return;
    }

    while (!feof(arquivo)) {
        doente_registos novo_registo;
        if (fscanf(arquivo, "%d\n", &novo_registo.id) != 1) {
            break;
        } else {
            fscanf(arquivo, "%d/%d/%d\n", &novo_registo.data.dia, &novo_registo.data.mes, &novo_registo.data.ano);
            fscanf(arquivo, "%f\n", &novo_registo.ten_max);
            fscanf(arquivo, "%f\n", &novo_registo.ten_min);
            fscanf(arquivo, "%d\n", &novo_registo.peso);
            fscanf(arquivo, "%f\n", &novo_registo.altura);
            inserir_lista_r(ptr_r, novo_registo);
        }
    }

    fclose(arquivo);
}

void imprimir_registros_doente(ptr_list_r ptr_r, int nid) {
    ptr_list_r doente;
    int n;

    if (nid == 0) {
        MsgSistema("Introduza o ID do utente que quer obter informações: ");
        scanf("%d", &n);
    } else {
        n = nid;
    }

    int encontrado = 0;
    doente = ptr_r->prox;

    while (doente != NULL) {
        if (doente->registo.id == n) {
            encontrado = 1;

            struct tm *data_atual;
            time_t t;
            time(&t);
            data_atual = localtime(&t);
            int ano_atual = data_atual->tm_year + 1900;
            int mes_atual = data_atual->tm_mon + 1;
            int dia_atual = data_atual->tm_mday;

            int anos, meses, dias;

            if (ano_atual - doente->registo.data.dia < 0) {
                anos = ano_atual - doente->registo.data.ano + 1;
            } else {
                anos = ano_atual - doente->registo.data.ano;
            }

            if (mes_atual - doente->registo.data.mes < 0) {
                meses = mes_atual - doente->registo.data.mes + 12;
                anos--;
            } else {
                meses = mes_atual - doente->registo.data.mes;
            }

            if (dia_atual - doente->registo.data.dia < 0) {
                dias = dia_atual - doente->registo.data.dia + 30;
                meses--;
            } else {
                dias = dia_atual - doente->registo.data.dia;
            }
            printf("+------ REGISTO -------+\n");
            printf("| "NEGRITO"ID"RESET_COR"                    | "VERDE"%-35d"RESET_COR"\n", doente->registo.id);
            printf("| "NEGRITO"Data do Registo"RESET_COR"       | %02d/%02d/%04d "SUBLINHADO"(%d dia(s), %d mes(es), %d ano(s) atrás)"RESET_COR"\n", 
                   doente->registo.data.dia, doente->registo.data.mes, doente->registo.data.ano, dias, meses, anos);
            printf("| "NEGRITO"Tensão Máxima"RESET_COR"         | %-35.2f \n", doente->registo.ten_max);
            printf("| "NEGRITO"Tensão Mínima"RESET_COR"         | %-35.2f \n", doente->registo.ten_min);
            printf("| "NEGRITO"Peso"RESET_COR"                  | %-35d \n", doente->registo.peso);
            printf("| "NEGRITO"Altura"RESET_COR"                | %-35.2f\n", doente->registo.altura);
            printf("+-----------------------+\n");
            printf("\n");
        }

        doente = doente->prox;
    }

    if (!encontrado) {
        AvisoCriticoSistema("❌ Registos do utente não encontrado!\n");
    }
}

void imprimir_todos_registos(ptr_list_r ptr_r) {
    ptr_list_r atual = ptr_r->prox;
    MsgSistema("Registos de Utentes:\n");
    int ultimo_id_impresso = -1; // Inicializa com um valor que não é um ID válido
    while (atual != NULL) {
        if (atual->registo.id != ultimo_id_impresso) {
            imprimir_registros_doente(ptr_r, atual->registo.id);
            ultimo_id_impresso = atual->registo.id;
        }
        atual = atual->prox;
    }  
}

void LimparEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int VerificaData(int dia, int mes, int ano) { // função que verifica se a data de nascimento inserida é válida
    time_t t = time(NULL);
    struct tm *data_atual = localtime(&t);
    int ano_atual = data_atual->tm_year + 1900;
    int mes_atual = data_atual->tm_mon + 1;
    int dia_atual = data_atual->tm_mday;

    int erro = 0;

    if(dia > 31 || mes > 12 || ano < 1900) {
        erro = 1;
    } else if((ano > ano_atual) || 
              (ano == ano_atual && mes > mes_atual) || 
              (ano == ano_atual && mes == mes_atual && dia > dia_atual)) {
        erro = 1;
    }

    if(erro) {
        AvisoSistema("A data inserida não é válida!\n");
        LimparEntrada();
        return 0;
    }

    return 1;
}

void upload_doentes_arquivo(ptr_list_d ptr_d) {     //função que escreve os dados do doentes no ficheiro doentes.txt
    FILE *arquivo;
    ptr_list_d atual = ptr_d->prox;
    arquivo = fopen("doentes.txt", "w");

    if (arquivo == NULL) {
        AvisoCriticoSistema("Não foi possível encontrar/abrir o ficheiro dos doentes!\n");
        return;
    }

    while (atual != NULL) {
        fprintf(arquivo, "%d\n",atual->data_doente.id);
        fprintf(arquivo, "%s\n",atual->data_doente.nome);
        fprintf(arquivo, "%d/%d/%d\n",atual->data_doente.data.dia,atual->data_doente.data.mes,atual->data_doente.data.ano);
        fprintf(arquivo, "%s\n",atual->data_doente.num_cidadao);
        fprintf(arquivo, "%d\n",atual->data_doente.num_telefone);
        fprintf(arquivo, "%s\n",atual->data_doente.email);

        atual = atual->prox;
    }

    fclose(arquivo);
}

void upload_registos_arquivo(ptr_list_r ptr_r) {    //função que escreve os registos do doentes no ficheiro registos.txt
    FILE *arquivo;
    ptr_list_r atual = ptr_r->prox;
    arquivo = fopen("registos.txt", "w");

    if (arquivo == NULL) {
        AvisoCriticoSistema("Não foi possível encontrar/abrir o ficheiro dos registos!\n");
        return;
    }

    while (atual != NULL) {
        fprintf(arquivo, "%d\n",atual->registo.id);
        fprintf(arquivo, "%d/%d/%d\n", atual->registo.data.dia, atual->registo.data.mes, atual->registo.data.ano);
        fprintf(arquivo, "%f\n", atual->registo.ten_max);
        fprintf(arquivo, "%f\n", atual->registo.ten_min);
        fprintf(arquivo, "%d\n", atual->registo.peso);
        fprintf(arquivo, "%f\n", atual->registo.altura);

        atual = atual->prox;
    }

    fclose(arquivo);
}

void ascii_art_inicialização() {
    printf(AMARELO"\n  /$$$$$$  /$$   /$$  /$$$$$$        /$$$$$$$  /$$$$$$$$ /$$$$$$\n");
    usleep(100000);
    printf(" /$$__  $$| $$$ | $$ /$$__  $$      | $$__  $$| $$_____/|_  $$_/\n");
    usleep(100000);
    printf("| $$  \\__/| $$$$| $$| $$  \\__/      | $$  \\ $$| $$        | $$  \n");
    usleep(100000);
    printf("|  $$$$$$ | $$ $$ $$|  $$$$$$       | $$  | $$| $$$$$     | $$  \n");
    usleep(100000);
    printf(" \\____  $$| $$  $$$$ \\____  $$      | $$  | $$| $$__/     | $$  \n");
    usleep(100000);
    printf(" /$$  \\ $$| $$\\  $$$ /$$  \\ $$      | $$  | $$| $$        | $$  \n");
    usleep(100000);
    printf("|  $$$$$$/| $$ \\  $$|  $$$$$$/      | $$$$$$$/| $$$$$$$$ /$$$$$$\n");
    usleep(100000);
    printf(" \\______/ |__/  \\__/ \\______/       |_______/ |________/|______/\n"RESET_COR);
    usleep(500000);
    printf("\n");
}