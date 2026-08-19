#include <stdio.h>
#include <unistd.h>  //para sleep()
#include <stdbool.h> //booleans
#include <stdlib.h>  // rand() e srand()
#include <time.h>    // time()

//---variáveis---//
int opcao_menu;     // opção menu principal
int opcao_melhoria; // opção das melhorias
int turno;          // turno do jogo
char quinta[3][3];  // a quinta
int evento;         // escolher o evento/intempérie

int contador_culturas; // para contar as culturas no terreno
int sementes;          // sementes na quinta
int regen_sementes;    // regeneração de sementes pelas culturas

int agua;            // água na quinta
int capacidade_agua; // reservatório de água
int regen_agua;      // regeneração de água
int consumo_agua;    // consumo de água das culturas

int fertilizante; // sacos de fertilizante
int comida;       // unidades de comida
int regen_comida; // regeneração de comida
bool divino;      // proteção divina

// variáveis de produção com define
// define chuva - regeneração natural
// define os vários custos das melhorias
// meter define das condições iniciais?

//---listagem das funções---//
// funções recorrentes do jogo
void iniciar_quinta(char quinta[3][3]);
void print_quinta(char quinta[3][3]);
void specs_quinta(void);
void analisar_quinta(char quinta[3][3]);
void crescer_sementes(char quinta[3][3]);

// funções do menu (ações do jogo)
void plantar_semente(char quinta[3][3]); // planta uma semente
void usar_fertilizante();
void melhorias(void);
void recursos_quinta(void); // faz todas as ações necessárias

// funções aleatórias do jogo (eventos e intempéries)
int evento_intemperie(void);

// void seca(char quinta[3][3]);
// void tempestade(char quinta[3][3]);
void passaros(void);
// void furo_deposito(void);

// função de finalização do jogo
//  void fim_do_jogo; //calcula pontuação

//***---O JOGO---***//
int main(void)
{
    srand(time(NULL));
    /*
    usleep(500000);
    printf("Com que então decidiste jogar a Quinta da Sobrevivência...\n");
    usleep(2000000);
    printf("Muito bem. Tens de semear culturas, crescê-las e resistir às intempéries.\n");
    usleep(2000000);
    printf("Começas com uma cultura e alguns recursos. Sobrevive o máximo tempo possível. Boa sorte!\n");
    usleep(2000000);

    usleep(500000);
    printf("            _\\,;;;;;;;,/_\n");
    usleep(500000);
    printf("         .-\"; ;;;;;;;;; ;\"-.\n");
    usleep(500000);
    printf("         '.__/`_ / \\ _`\\__.'\n");
    usleep(500000);
    printf("            | (')| |(') |\n");
    usleep(500000);
    printf("            | .--' '--. |\n");
    usleep(500000);
    printf("            |/ o     o \\|\n");
    usleep(500000);
    printf("            |           |\n");
    usleep(500000);
    printf("           / \\ _..=.._ / \\\n");
    usleep(500000);
    printf("          /:. '._____.'   \\\n");
    usleep(500000);
    printf("         ;::'    / \\      .;\n");
    usleep(500000);
    printf("         |     _|_ _|_   ::|\n");
    usleep(500000);
    printf("       .-|     '==o=='    '|-.\n");
    usleep(500000);
    printf("      /  |  . /       \\    |  \\\n");
    usleep(500000);
    printf("      |  | ::|         |   | .|\n");
    usleep(500000);
    printf("      |  (  ')         (.  )::|\n");
    usleep(500000);
    printf("      |: |   |; U U U ;|:: | `|\n");
    usleep(500000);
    printf("      |' |   | \\ U U / |'  |  |\n");
    usleep(500000);
    printf("      ##V|   |_/`\"\"\"`\\_|   |V##\n");
    usleep(500000);
    printf("jgs      ##V##         ##V##\n");
    usleep(500000); */

    // iniciar a quinta
    iniciar_quinta(quinta);
    analisar_quinta(quinta);

    while (1) // loop do jogo
    {
        // mostra a quinta
        specs_quinta();
        print_quinta(quinta);

        // mostrar menu
        printf("\nO que vais fazer agora?\n");
        printf("1. Plantar Semente\n");
        printf("2. Usar fertilizante\n");
        printf("3. Melhorias\n");
        printf("4. Processar turno\n");
        printf("0. Sair\n");

        scanf("%d", &opcao_menu);
        getchar();

        switch (opcao_menu)
        {
        case 1: // plantar semente
            plantar_semente(quinta);
            break;

        case 2: // usar fertilizante
            usar_fertilizante();
            break;

        case 3:
            melhorias();
            break;

        case 4:
            analisar_quinta(quinta);
            recursos_quinta();
            // eventos e intempéries
            int evento = evento_intemperie();
            if (divino == true)
            {
                evento = 0;
                printf("Safaste-te da intempérie.\n");
                divino = false;
            }
            else
            {
                switch (evento)
                {
                case 1:
                    // tempestade
                    break;

                case 2:
                    // seca
                    break;

                case 3:
                    passaros();
                    break;

                case 4:
                    // furo depósito
                    break;

                default:
                    break;
                }
            }

            // verificar condições de fim de jogo
            if (agua <= 0)
            {
                printf("FICASTE SEM ÁGUA!!! FIM DO JOGO\n");
                // calcula pontuação
                return 0;
            }
            // crescer sementes
            crescer_sementes(quinta);
            analisar_quinta(quinta);
            turno++;
            break;

        case 0:
            usleep(1000000);
            printf("A tua quinta foi abandonada. Parece que ser agricultor não é nada fácil...\n");
            usleep(1000000);
            printf("\n");
            return 0;

        default:
            printf("Opção inválida.\n");
            break;
        }
    }

    return 0;
}
//---***FIM DO JOGO***---//

void iniciar_quinta(char quinta[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            quinta[i][j] = '.';
        }
    }
    quinta[0][0] = 'C';
    sementes = 10;
    agua = 100000;
    capacidade_agua = 200000000;
    fertilizante = 1;
    comida = 2;
    regen_agua = 1; // lençóis freáticos
    turno = 1;
}

void specs_quinta(void)
{
    printf("Turno: %d\n", turno);
    printf("=== RECURSOS ===\n");
    printf("Sementes: %d | Água: %d/%d | Fertilizante: %d | Comida: %d\n",
           sementes, agua, capacidade_agua, fertilizante, comida);
    printf("================\n");
    printf("Prod. água: %d | Prod. comida: %d | Prod. sementes: %d\n",
           regen_agua - consumo_agua, regen_comida, regen_sementes);
}

void print_quinta(char quinta[3][3])
{
    printf("\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("[%c]", quinta[i][j]);
        }
        printf("\n");
    }
}

void plantar_semente(char quinta[3][3])
{
    if (sementes <= 0)
    {
        printf("Sem sementes.\n");
        return;
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (quinta[i][j] == '.')
            {
                quinta[i][j] = 's';
                sementes--;
                agua--;
                return; // Sai da função logo após plantar a primeira
            }
        }
    }
    printf("Não tens hectares disponíveis.\n");
}

void usar_fertilizante(void)
{
    if (fertilizante > 0)
    {
        regen_comida++;
        fertilizante--;
        return;
    }
    printf("Sem fertilizante.\n");
}

void melhorias(void)
{
    while (1)
    {
        // mostrar menu
        printf("\nMelhoria:\n");
        printf("1. Regadio: +2 regen. água. Custa 2 comidas.\n");
        printf("2. Depósito melhorado: +10 capacidade de água. Custa 4 comidas.\n");
        printf("3. Saco fertilizante. +1 regen. comida. Custa 1 comida.\n");
        printf("4. Proteção divina. Protege-te de qualquer intempérie num turno. Custa 10 comidas.\n");
        printf("0. Voltar à quinta\n");

        scanf("%d", &opcao_melhoria);
        getchar();

        switch (opcao_melhoria)
        {
        case 1:             // regadio
            if (comida < 2) // depois tenho de alterar isto para um custo fixo do regadio
            {
                printf("Não tens comida suficiente.\n");
                break;
            }
            regen_agua += 2;
            comida -= 2;
            break;

        case 2:             // depósito
            if (comida < 4) // depois tenho de alterar isto para um custo fixo do depósito
            {
                printf("Não tens comida suficiente.\n");
                break;
            }
            capacidade_agua += 10;
            comida -= 4;
            break;

        case 3:             // saco fertilizante
            if (comida < 1) // depois tenho de alterar isto para um custo fixo do fertilizante
            {
                printf("Não tens comida suficiente.\n");
                break;
            }
            fertilizante++;
            comida--;
            break;

        case 4: // proteção divina
            if (divino == false && comida >= 10)
            {
                divino = true;
                break;
            }
            else if (comida < 10) // depois tenho de alterar isto para um custo fixo do fertilizante
            {
                printf("Não tens comida suficiente.\n");
                break;
            }
            else if (divino == true) // depois tenho de alterar isto para um custo fixo do fertilizante
            {
                printf("Já estás protegido.\n");
                break;
            }
            break;

        case 0:
            return;

        default:
            printf("Opção inválida.\n");
            break;
        }
    }
}

void analisar_quinta(char quinta[3][3]) // ver o que têm os hectares de terreno
{
    // analisa a quinta
    contador_culturas = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (quinta[i][j] == 'C')
            {
                contador_culturas++;
            }
        }
    }
    consumo_agua = contador_culturas * 3;
    regen_comida = contador_culturas * 1;
    regen_sementes = contador_culturas * 1;
}

void recursos_quinta(void)
{
    // atualizar recursos com consumos e regenerações (comida, água, sementes)
    printf("A actualizar os recursos da quinta...\n");
    usleep(1000000);
    comida += regen_comida;
    sementes += regen_sementes;
    agua += regen_agua - consumo_agua;
    if (agua >= capacidade_agua)
    {
        agua = capacidade_agua; // depósito cheio
    }
}

int evento_intemperie(void)
{
    // Gera um número entre 1 e 100
    int evento = (rand() % 100) + 1;

    if (evento <= 50)
    {
        return 0; // 50%
    }
    else if (evento <= 70)
    {
        return 1; // 20%; vai ser usada para tempestade
    }
    else if (evento <= 80)
    {
        return 2; // 10%; vai ser usada para seca
    }
    else if (evento <= 90)
    {
        return 3; // 10%; vai ser usado para pássaros
    }
    else
    {
        return 4; // 10%; furo no depósito
    }
}

void crescer_sementes(char quinta[3][3]) // ver o que têm os hectares de terreno
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (quinta[i][j] == 's')
            {
                quinta[i][j] = 'C';
            }
        }
    }
}

void passaros(void)
{
    printf("Um bando de pássaros atacou o celeiro! Perdeste metade das sementes.\n");
    sementes /= 2;
}