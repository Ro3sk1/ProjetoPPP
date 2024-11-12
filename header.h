#ifndef STRUCTS_PROJ
#define STRUCTS_PROJ

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_nascimento_str {
    int dia;
    int mes;
    int ano;
} data_nascimento_str;

typedef struct doente_dados{
    int id;
    char nome[41];
    data_nascimento_str data;
    char num_cidadao[16];
    int num_telefone;
    char email[41];
} doente_dados;

typedef struct doente_registos{
    int id;
    data_nascimento_str data;
    float ten_max;
    float ten_min;
    int peso;
    float altura;
} doente_registos;

typedef struct element_list_d{
    doente_dados data_doente;
    struct element_list_d *prox;
} element_list_d;

typedef struct element_list_r{
    doente_registos registo;
    struct element_list_r *prox;
}element_list_r;

typedef element_list_d *ptr_list_d;
typedef element_list_r *ptr_list_r;

ptr_list_d cria_list_d();
ptr_list_r cria_list_r();
int vazia_d(ptr_list_d ptr);
int vazia_r(ptr_list_r ptr);
ptr_list_d destroi_d(ptr_list_d ptr);
ptr_list_r destroi_r(ptr_list_r ptr);
void procura_lista_d(ptr_list_d lista, int chave, ptr_list_d *ant, ptr_list_d *actual);
int procura_lista_r(ptr_list_r lista, int chave, ptr_list_r *ant, ptr_list_r *actual);
void inserir_lista_d(ptr_list_d ptr_d, doente_dados p1);
void inserir_lista_r(ptr_list_r ptr_r, doente_registos p1);
void elimina_d(ptr_list_d ptr, int chave);
void elimina_r(ptr_list_r ptr, int chave);
void procura_alfabeto(ptr_list_d lista, char chave[], ptr_list_d *ant, ptr_list_d *actual);
void insere_alfabeto(ptr_list_d lista, doente_dados p1);
void MsgSistema(const char *mensagem);
void AvisoSistema(const char *mensagem);
void AvisoCriticoSistema(const char *mensagem);
void AvisoVerdeSistema(const char *mensagem);
void Negrito(const char *mensagem);
void AdicionarDoente(ptr_list_d ptr_d);
void RemoverDoente(ptr_list_d ptr_d, ptr_list_r ptr_r);
void RemoverRegistros(ptr_list_r ptr_r);
void EliminaRegistros(ptr_list_r ptr, int id);
void ListarAlfabeticamente(ptr_list_d ptr_d);
void ListarDoentesAcimaTMAX(ptr_list_r ptr);
void RegistrosDoente(ptr_list_r ptr, ptr_list_d ptr_d);
void imprimir_doente(ptr_list_d ptr_d, ptr_list_r ptr_r, int registros_com_dados);
void imprimir_todos_doentes(ptr_list_d ptr_d,ptr_list_r ptr_r,int registros_com_dados);;
void AlterarDados(ptr_list_d ptr_d);
void carregar_doentes_arquivo(ptr_list_d ptr_d);
void carregar_registros_arquivo(ptr_list_r ptr_r);
void imprimir_registros_doente(ptr_list_r ptr_r, int nid);
void imprimir_todos_registos(ptr_list_r ptr_r);
void LimparEntrada();
int VerificaData(int dia, int mes, int ano);
void upload_doentes_arquivo(ptr_list_d ptr_d);
void upload_registos_arquivo(ptr_list_r ptr_r);
void ascii_art_inicialização();

#endif