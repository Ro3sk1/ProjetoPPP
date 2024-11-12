#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "header.h"

#define RESET_COR    "\x1b[0m"
#define AMARELO      "\x1b[33m"
#define VERMELHO     "\x1b[31m"
#define VERDE        "\x1b[32m"

int main() {
    int teste = 1, opcao, opcao_tipo_info, opcao_info, opcao_listar_doentes, opcao_adicionar_alterar_dados, opcao_remover, opcao_registros, opcao_definicoes, opcao_upload_fich, opcao_download_fich,opcao_registros_com_dados;
    int registros_com_dados = 0;
    ptr_list_d ptr_d;
    ptr_list_r ptr_r;
    ptr_d = cria_list_d();
    ptr_r = cria_list_r();

    ascii_art_inicialização();
    carregar_doentes_arquivo(ptr_d);
    carregar_registros_arquivo(ptr_r);

    while (teste == 1) {
        printf("\n+------------- | Opções | ---------------+\n");
        printf("| 1 - Adicionar/Alterar dados            |\n");
        printf("| 2 - Remover dados                      |\n");
        printf("| 3 - Obter informações sobre doente(s)  |\n");
        printf("| 4 - Outros                             |\n");
        printf("| 0 - Encerrar Programa                  |\n");
        printf("+----------------------------------------+\n");
        Negrito("OPÇÃO:  ");
        
        if (scanf("%d", &opcao) != 1) {
            AvisoCriticoSistema("Entrada inválida. Por favor, insira um número válido.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (opcao) {
            case 0:
                AvisoVerdeSistema("Salvando utentes no ficheiro...");
                upload_doentes_arquivo(ptr_d);
                AvisoVerdeSistema("Salvando registros no ficheiro...");
                upload_registos_arquivo(ptr_r);
                MsgSistema("Sistema a ser desligado. Até à próxima!\n");
                teste = 0;
                break;
            case 1:
                MsgSistema("Prentende:\n| 1 - Adicionar doente\n| 2 - Adicionar registro a um utente já existente\n| 3 - Alterar dados de um doente\n| 0 - Voltar\nOPÇÃO: ");
                
                if (scanf("%d", &opcao_adicionar_alterar_dados) != 1) {
                    AvisoCriticoSistema("Entrada inválida. Por favor, insira um número válido.\n");
                    while (getchar() != '\n');
                    break;
                }

                switch (opcao_adicionar_alterar_dados) {
                    case 0:
                        break;
                    case 1:
                        AdicionarDoente(ptr_d);
                        break;
                    case 2:
                        RegistrosDoente(ptr_r,ptr_d);
                        break;
                    case 3:
                        AlterarDados(ptr_d);
                        break;
                    default:
                        AvisoCriticoSistema("Opção inválida.\n");
                        break;
                }
                break;
            case 2:
                MsgSistema("Prentende remover:\n 1 - Doente e registros de um doente\n 2 - Registros de um doente (manter doente)\n 0 - Voltar\nOPÇÃO: ");
                
                if (scanf("%d", &opcao_remover) != 1) {
                    AvisoCriticoSistema("Entrada inválida. Por favor, insira um número válido.\n");
                    while (getchar() != '\n');
                    break;
                }

                switch (opcao_remover) {
                    case 0:
                        break;
                    case 1:
                        RemoverDoente(ptr_d, ptr_r);
                        break;
                    case 2:
                        RemoverRegistros(ptr_r);
                        break;
                    default:
                        AvisoCriticoSistema("Opção inválida.\n");
                        break;
                }
                break;
            case 3:
                MsgSistema("Prentende obter:\n 1 - Dados de utente(s)\n 2 - Registros de doente(s)\n 3 - Utente(s) com Tensão Máxima Altas\n 0 - Voltar\nOPÇÃO: ");
                
                if (scanf("%d", &opcao_tipo_info) != 1) {
                    AvisoCriticoSistema("Entrada inválida. Por favor, insira um número válido.\n");
                    while (getchar() != '\n');
                    break;
                }

                switch (opcao_tipo_info) {
                    case 0:
                        break;
                    case 1:
                        MsgSistema("Prentende obter informações:\n 1 - Todos os utentes\n 2 - Doente em específico\n 0 - Voltar\nOPÇÃO: ");
                        
                        if (scanf("%d", &opcao_info) != 1) {
                            AvisoCriticoSistema("Entrada inválida. Por favor, insira um número válido.\n");
                            while (getchar() != '\n');
                            break;
                        }

                        switch (opcao_info) {
                            case 0:
                                break;
                            case 1:
                                MsgSistema("Prentende obter listagem por ordem:\n 1 - De entrada\n 2 - Alfabética\n 0 - Voltar\nOPÇÃO: ");
                                
                                if (scanf("%d", &opcao_listar_doentes) != 1) {
                                    AvisoCriticoSistema("Entrada inválida. Por favor, insira um número válido.\n");
                                    while (getchar() != '\n');
                                    break;
                                }

                                switch (opcao_listar_doentes) {
                                    case 0:
                                        break;
                                    case 1:
                                        imprimir_todos_doentes(ptr_d,ptr_r,registros_com_dados);
                                        break;
                                    case 2:
                                        ListarAlfabeticamente(ptr_d);
                                        break;
                                    default:
                                        AvisoCriticoSistema("Opção inválida.\n");
                                        break;
                                }
                                break;
                            case 2:
                                imprimir_doente(ptr_d,ptr_r,registros_com_dados);
                                break;
                            default:
                                AvisoCriticoSistema("Opção inválida.\n");
                                break;
                        }
                        break;
                    case 2:
                        MsgSistema("Prentende obter registros de:\n 1 - Todos os utentes\n 2 - Doente em específico\n 0 - Voltar\nOPÇÃO: ");
                        
                        if (scanf("%d", &opcao_registros) != 1) {
                            AvisoCriticoSistema("Entrada inválida. Por favor, insira um número válido.\n");
                            while (getchar() != '\n');
                            break;
                        }

                        switch (opcao_registros) {
                            case 0:
                                break;
                            case 1:
                                imprimir_todos_registos(ptr_r);
                                break;
                            case 2:
                                imprimir_registros_doente(ptr_r,0);
                                break;
                            default:
                                AvisoCriticoSistema("Opção inválida.\n");
                                break;
                        }
                        break;
                    case 3:
                        ListarDoentesAcimaTMAX(ptr_r);
                        break;
                    default:
                        AvisoCriticoSistema("Opção inválida.\n");
                        break;
                }
                break;
            case 4:
                if(registros_com_dados == 0) {
                    printf(AMARELO"[SISTEMA]"RESET_COR"Prentende:\n| 1 - Carregar informações de ficheiro\n| 2 - Guardar informações para ficheiro\n| 3 - Imprimir registros junto com dados do doente [Atual: " VERMELHO "NÃO ATIVADO"RESET_COR"]\n| 0 - Voltar\nOPÇÃO: ");
                } else if(registros_com_dados == 1) {
                    printf(AMARELO"[SISTEMA]"RESET_COR"Prentende:\n| 1 - Carregar informações de ficheiro\n| 2 - Guardar informações para ficheiro\n| 3 - Imprimir registros junto com dados do doente [Atual: " VERDE "ATIVADO"RESET_COR"]\n| 0 - Voltar\nOPÇÃO: ");
                }
                
                if (scanf("%d", &opcao_definicoes) != 1) {
                    AvisoCriticoSistema("Entrada inválida. Por favor, insira um número válido.\n");
                    while (getchar() != '\n');
                    break;
                }

                switch (opcao_definicoes) {
                    case 0:
                        break;
                    case 1:
                        MsgSistema("Prentende carregar informações de:\n| 1 - Utentes\n| 2 - Registros\n| 3 - Ambos\n| 0 - Voltar\nOPÇÃO: ");
                        
                        if (scanf("%d", &opcao_download_fich) != 1) {
                            AvisoCriticoSistema("Entrada inválida. Por favor, insira um número válido.\n");
                            while (getchar() != '\n');
                            break;
                        }

                        switch (opcao_download_fich) {
                            case 0:
                                break;
                            case 1:
                                AvisoVerdeSistema("Carregando utentes a partir do ficheiro...");
                                carregar_doentes_arquivo(ptr_d);
                                break;
                            case 2:
                                AvisoVerdeSistema("Carregando registros a partir do ficheiro...");
                                carregar_registros_arquivo(ptr_r);
                                break;
                            case 3:
                                AvisoVerdeSistema("Carregando utentes a partir do ficheiro...");
                                carregar_doentes_arquivo(ptr_d);
                                AvisoVerdeSistema("Carregando registros a partir do ficheiro...");
                                carregar_registros_arquivo(ptr_r);
                                break;
                            default:
                                AvisoCriticoSistema("Opção inválida.\n");
                                break;
                        }
                        break;
                    case 2:
                        MsgSistema("Prentende guardar informações de:\n| 1 - Utentes\n| 2 - Registros\n| 3 - Ambos\n| 0 - Voltar\nOPÇÃO: ");
                        
                        if (scanf("%d", &opcao_upload_fich) != 1) {
                            AvisoCriticoSistema("Entrada inválida. Por favor, insira um número válido.\n");
                            while (getchar() != '\n');
                            break;
                        }

                        switch (opcao_upload_fich) {
                            case 0:
                                break;
                            case 1:
                                AvisoVerdeSistema("Salvando utentes no ficheiro...");
                                upload_doentes_arquivo(ptr_d);
                                break;
                            case 2:
                                AvisoVerdeSistema("Salvando registros no ficheiro...");
                                upload_registos_arquivo(ptr_r);
                                break;
                            case 3:
                                AvisoVerdeSistema("Salvando utentes no ficheiro...");
                                upload_doentes_arquivo(ptr_d);
                                AvisoVerdeSistema("Salvando registros no ficheiro...");
                                upload_registos_arquivo(ptr_r);
                                break;
                            default:
                                AvisoCriticoSistema("Opção inválida.\n");
                                break;
                        }
                        break;
                    case 3:
                        MsgSistema("Prentende:\n| 1 - Ativar\n| 2 - Desativar\n| 0 - Voltar\nOPÇÃO: ");
                        
                        if (scanf("%d", &opcao_registros_com_dados) != 1) {
                            AvisoCriticoSistema("Entrada inválida. Por favor, insira um número válido.\n");
                            while (getchar() != '\n');
                            break;
                        }

                        switch (opcao_registros_com_dados) {
                            case 0:
                                break;
                            case 1:
                                if(registros_com_dados == 1) {
                                    AvisoCriticoSistema("Esta opção já estava ativada.");
                                } else {
                                    registros_com_dados = 1;
                                }
                                break;
                            case 2:
                                if(registros_com_dados == 0) {
                                    AvisoCriticoSistema("Esta opção já estava desativada.");
                                } else {
                                    registros_com_dados = 0;
                                }
                                break;
                            default:
                                AvisoCriticoSistema("Opção inválida.\n");
                                break;
                        }
                        break;
                    default:
                        AvisoCriticoSistema("Opção inválida.\n");
                        break;
                }
                break;
            default:
                AvisoCriticoSistema("Opção inválida.\n");
                break;
        }
    }

    destroi_d(ptr_d);
    destroi_r(ptr_r);
    return 0;
}