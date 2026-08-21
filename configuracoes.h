#ifndef CONFIGURACOES_H

#define CONFIGURACOES_H
//-todas as bibliotecas nativas que são usadas no jogo-//
#include <stdio.h>
#include <unistd.h>  //para usleep()
#include <stdbool.h> //booleans
#include <stdlib.h>  // rand() e srand()
#include <time.h>    // time()
//---//

//-variáveis iniciais de jogo-//
#define SEMENTES_INICIAL 10
#define AGUA_INICIAL 100
#define DEPOSITO_INICIAL 200
#define COMIDA_INICIAL 2
#define FERTILIZANTE_INICIAL 1
#define REGEN_AGUA_INICIAL 1
//---//

//-variáveis da quinta-//
#define TAMANHO 3
#define HECTARE_VAZIO '.'
#define HECTARE_SEMENTE 's'
#define HECTARE_CULTURA 'C'
#define HECTARE_SECO 'X'
//---//

//-Consumos e regenerações-//
#define CONSUMO_AGUA_CULTURA 3
#define REGEN_COMIDA_CULTURA 1
#define REGEN_SEMENTES_CULTURA 1
#define CONSUMO_AGUA_SEMENTE 1
#define REGEN_COMIDA_FERTILIZANTE 1

//---//

//-Melhorias-//
#define CUSTO_REGADIO 2
#define AGUA_REGADIO 2

#define CUSTO_DEPOSITO 4
#define CAPACIDADE_DEPOSITO 10

#define CUSTO_FERTILIZANTE 1
#define COMIDA_FERTILIZANTE 1

#define CUSTO_DIVINO 10
//---//

//-Eventos e intempéries-//
// ID dos eventos
#define ID_SEM_EVENTO 0
#define ID_TEMPESTADE 1
#define ID_SECA 2
#define ID_PASSAROS 3
#define ID_FURO 4

// Probabilidades (Acumulados até 100)
#define PROB_SEM_EVENTO 50 // 1 a 50 (50%)
#define PROB_TEMPESTADE 70 // 51 a 70 (20%)
#define PROB_SECA 80       // 71 a 80 (10%)
#define PROB_PASSAROS 90   // 81 a 90 (10%)
#define PROB_FURO 100      // 91 a 100 (10%)

// danos específicos
#define DANO_PASSAROS 2 // quanto maior, mais sementes tira
#define DANO_FURO_NUM 2 // quanto maior, menos água tira
#define DANO_FURO_DEN 3 // quanto maior, mais água tira
// NUM deve ser inferior ao DEN

//-pesos da pontuação-//
#define PESO_TURNO 5
#define PESO_COMIDA 2
//---//

#endif