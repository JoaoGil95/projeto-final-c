#include <stdio.h>
#include <unistd.h> //para sleep()

//---variáveis---//
int opcao_menu;     // opção menu principal
int opcao_melhoria; // opção das melhorias
int turno;          // turno do jogo
char quinta[3][3];  // a quinta
int sementes;       // sementes
int agua;           // água na quinta
int fertilizante;   // sacos de fertilizante

//---listagem das funções---//
// funções recorrentes do jogo
void iniciar_quinta(char quinta[3][3]);
void print_quinta(char quinta[3][3]);
// void specs_quinta;

// funções do menu (ações do jogo)
// void plantar_semente;
// void usar_fertilizante;
// void melhorias;
// void evento_intemperie;

//***---O JOGO---***//
int main(void)
{
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

    // imprimir a quinta
    iniciar_quinta(quinta);
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
    case 1:
        /* code */
        break;

    case 2:
        /* code */
        break;

    case 3:
        /* code */
        break;

    case 4:
        break;

    case 0:
        printf("A tua quinta foi abandonada.\n");
        usleep(2000000);
        printf("Parece que ser agricultor não é nada fácil...\n");
        usleep(2000000);
        break;

    default:
        printf("Opção inválida.\n");
        break;
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
    quinta[0][0] = 'C'; // começa com 1 cultura
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
    printf("\n");
}