#include "configuracoes.h"

//---variáveis---//
int opcao_menu;                // opção menu principal
int opcao_melhoria;            // opção das melhorias
int turno;                     // turno do jogo
char quinta[TAMANHO][TAMANHO]; // a quinta
int evento;                    // escolher o evento/intempérie
int pontuacao;                 // pontuação final do jogo

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

//-coisas a fazer (se tiver tempo)-//
// variáveis de produção com define
// define chuva - regeneração natural
// define os vários custos das melhorias
// meter define das condições iniciais?

//---listagem das funções---//
// funções recorrentes do jogo
void iniciar_quinta(char quinta[TAMANHO][TAMANHO]);
void print_quinta(char quinta[TAMANHO][TAMANHO]);
void specs_quinta(void);
void analisar_quinta(char quinta[TAMANHO][TAMANHO]);
void crescer_sementes(char quinta[TAMANHO][TAMANHO]);

// funções do menu (ações do jogo)
void plantar_semente(char quinta[TAMANHO][TAMANHO]); // planta uma semente
void usar_fertilizante(void);
void melhorias(void);
void recursos_quinta(void); // faz todas as ações necessárias

// funções aleatórias do jogo (eventos e intempéries)
int evento_intemperie(void);
void seca(char quinta[TAMANHO][TAMANHO]);
void tempestade(char quinta[TAMANHO][TAMANHO]);
void passaros(void);
void furo_deposito(void);

// função de pontuação do jogo
void fim_do_jogo(void); // calcula pontuação

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

        case 3: // menu melhorias
            melhorias();
            break;

        case 4: // processar turno
            analisar_quinta(quinta);
            crescer_sementes(quinta);
            recursos_quinta();
            // eventos e intempéries
            int evento = evento_intemperie();
            if (divino == true)
            {
                evento = ID_SEM_EVENTO;
                printf("Safaste-te da intempérie.\n");
                divino = false;
            }
            else
            {
                switch (evento)
                {
                case ID_TEMPESTADE:
                    tempestade(quinta);
                    break;

                case ID_SECA:
                    seca(quinta);
                    break;

                case ID_PASSAROS:
                    passaros();
                    break;

                case ID_FURO:
                    furo_deposito();
                    break;

                default:
                    break;
                }
            }
            analisar_quinta(quinta);
            // verificar condições de fim de jogo
            if (agua <= 0)
            {
                printf("FICASTE SEM ÁGUA!!! FIM DO JOGO\n");
                fim_do_jogo();
                return 0;
            }

            if (contador_culturas == 0)
            {
                printf("PERDESTE AS CULTURAS TODAS!!! FIM DO JOGO\n");
                fim_do_jogo();
                return 0;
            }
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

void iniciar_quinta(char quinta[TAMANHO][TAMANHO])
{
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            quinta[i][j] = HECTARE_VAZIO;
        }
    }
    quinta[0][0] = HECTARE_CULTURA;
    sementes = SEMENTES_INICIAL;
    agua = AGUA_INICIAL;
    capacidade_agua = DEPOSITO_INICIAL;
    fertilizante = FERTILIZANTE_INICIAL;
    comida = COMIDA_INICIAL;
    regen_agua = REGEN_AGUA_INICIAL;
    turno = 1;
    divino = false;
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

void print_quinta(char quinta[TAMANHO][TAMANHO])
{
    printf("\n");
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            printf("[%c]", quinta[i][j]);
        }
        printf("\n");
    }
}

void plantar_semente(char quinta[TAMANHO][TAMANHO]) // planta a semente no primeiro hectare vazio
{
    if (sementes <= 0)
    {
        printf("Sem sementes.\n");
        return;
    }
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            if (quinta[i][j] == HECTARE_VAZIO)
            {
                quinta[i][j] = HECTARE_SEMENTE;
                sementes--;
                agua -= CONSUMO_AGUA_SEMENTE;
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
        regen_comida += REGEN_COMIDA_FERTILIZANTE;
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
        printf("1. Regadio: +%d regen. água. Custa %d comidas.\n", AGUA_REGADIO, CUSTO_REGADIO);
        printf("2. Depósito melhorado: +%d capacidade de água. Custa %d comidas.\n", CAPACIDADE_DEPOSITO, CUSTO_DEPOSITO);
        printf("3. Saco fertilizante. +%d regen. comida. Custa %d comida.\n", COMIDA_FERTILIZANTE, CUSTO_FERTILIZANTE);
        printf("4. Proteção divina. Protege-te de qualquer intempérie num turno. Custa %d comidas.\n", CUSTO_DIVINO);
        printf("0. Voltar à quinta\n");

        scanf("%d", &opcao_melhoria);
        getchar();

        switch (opcao_melhoria)
        {
        case 1: // regadio
            if (comida < CUSTO_REGADIO)
            {
                printf("Não tens comida suficiente.\n");
                break;
            }
            regen_agua += AGUA_REGADIO;
            comida -= CUSTO_REGADIO;
            break;

        case 2: // depósito
            if (comida < CUSTO_DEPOSITO)
            {
                printf("Não tens comida suficiente.\n");
                break;
            }
            capacidade_agua += CAPACIDADE_DEPOSITO;
            comida -= CUSTO_DEPOSITO;
            break;

        case 3: // saco fertilizante
            if (comida < CUSTO_FERTILIZANTE)
            {
                printf("Não tens comida suficiente.\n");
                break;
            }
            fertilizante += COMIDA_FERTILIZANTE;
            comida -= CUSTO_FERTILIZANTE;
            break;

        case 4: // proteção divina
            if (divino == false && comida >= CUSTO_DIVINO)
            {
                divino = true;
                comida -= CUSTO_DIVINO;
                break;
            }
            else if (comida < CUSTO_DIVINO)
            {
                printf("Não tens comida suficiente.\n");
                break;
            }
            else if (divino == true)
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

void analisar_quinta(char quinta[TAMANHO][TAMANHO]) // ver o que têm os hectares de terreno
{
    // conta as culturas
    contador_culturas = 0;
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            if (quinta[i][j] == HECTARE_CULTURA)
            {
                contador_culturas++;
            }
        }
    }
    consumo_agua = contador_culturas * CONSUMO_AGUA_CULTURA;
    regen_comida = contador_culturas * REGEN_COMIDA_CULTURA;
    regen_sementes = contador_culturas * REGEN_SEMENTES_CULTURA;
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
    int evento = (rand() % 100) + 1; // gera um número entre 1 e 100

    if (evento <= PROB_SEM_EVENTO) // não ocorre nenhum evento
    {
        return ID_SEM_EVENTO; // 50%
    }
    else if (evento <= PROB_TEMPESTADE)
    {
        return ID_TEMPESTADE; // 20%; vai ser usada para tempestade
    }
    else if (evento <= PROB_SECA)
    {
        return ID_SECA; // 10%; vai ser usada para seca
    }
    else if (evento <= PROB_PASSAROS)
    {
        return ID_PASSAROS; // 10%; vai ser usado para pássaros
    }
    else if (evento <= PROB_FURO)
    {
        return ID_FURO; // 10%; furo no depósito
    }
}

void crescer_sementes(char quinta[TAMANHO][TAMANHO]) // crescer as sementes no turno seguinte
{
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            if (quinta[i][j] == HECTARE_SEMENTE)
            {
                quinta[i][j] = HECTARE_CULTURA;
            }
        }
    }
}

void passaros(void)
{
    printf("Um bando de pássaros roubou metade das sementes.\n");
    sementes /= DANO_PASSAROS;
}

void seca(char quinta[TAMANHO][TAMANHO])
{
    printf("As temperaturas altas causaram uma seca num hectare do terreno.\n");
    for (int i = 0; i < TAMANHO; i++)
    {
        for (int j = 0; j < TAMANHO; j++)
        {
            if (quinta[i][j] == HECTARE_VAZIO)
            {
                quinta[i][j] = HECTARE_SECO;
                return; // Sai da função logo após causar a seca
            }
        }
    }
}

void furo_deposito(void)
{
    printf("Um furo no depósito fez-te perder um terço da água.\n");
    agua = (agua * DANO_FURO_NUM) / DANO_FURO_DEN; // se fizer *2/3, assumo que é 0 e perde-se logo o jogo
}

void tempestade(char quinta[TAMANHO][TAMANHO])
{
    if (contador_culturas > 0)
    {
        printf("Uma tempestade tirou-te uma cultura.\n");
        for (int i = 0; i < TAMANHO; i++)
        {
            for (int j = 0; j < TAMANHO; j++)
            {
                if (quinta[i][j] == HECTARE_CULTURA)
                {
                    quinta[i][j] = HECTARE_VAZIO;
                    return; // Sai da função logo após causar a tempestade
                }
            }
        }
    }
}

void fim_do_jogo(void)
{
    pontuacao = turno * PESO_TURNO + comida * PESO_COMIDA;
    printf("PONTUAÇÃO FINAL: %d pontos\n", pontuacao);
}