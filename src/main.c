// Código-fonte disponível em https://github.com/mpeschke/contadeagua.git
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define NUMCONTAS 3
// ----------|--------|
// 12345678901234567890
// RESIDENCIAL
// COMERCIAL
// INDUSTRIAL
#define TIPOBUFFSIZE 11
static const char* TIPORESIDENCIAL = "RESIDENCIAL";
static const char* TIPOCOMERCIAL = "COMERCIAL";
static const char* TIPOINDUSTRIAL = "INDUSTRIAL";

enum enumTipoConta {industrial, comercial, residencial};

struct Conta
{
    enum enumTipoConta tipo;
    int consumo;
    char idconta[100];
    float valor;
} typedef stConta;

stConta contas[NUMCONTAS];

void calc_valor_conta(stConta* pconta);

void sort_contas(stConta* pcontas, int numcontas);

void imprime_contas(stConta* pcontas, int numcontas);

int main()
{
    for(int i = 0; i < NUMCONTAS; i++)
    {
        printf("\nDigite a conta do cliente: ");
        scanf("%s", contas[i].idconta);
        printf("Digite o consumo (m3): ");
        scanf("%d", &(contas[i].consumo));
        printf("Digite o tipo de consumidor (RESIDENCIAL, COMERCIAL, INDUSTRIAL): ");
        char buff[TIPOBUFFSIZE+1] = {'\0'};
        scanf("%s", buff);

        if(strcmp(buff, TIPORESIDENCIAL) == 0)
            contas[i].tipo = residencial;
        else if(strcmp(buff, TIPOCOMERCIAL) == 0)
            contas[i].tipo = comercial;
        else if(strcmp(buff, TIPOINDUSTRIAL) == 0)
            contas[i].tipo = industrial;

        calc_valor_conta(&contas[i]);
    }
    sort_contas(contas, NUMCONTAS);
    imprime_contas(contas, NUMCONTAS);

    return 0;
}

void calc_valor_conta(stConta* pconta)
{
    float taxa = 0.0f;
    float totalporm3 = 0.0f;

    if(pconta->tipo == residencial)
    {
        taxa = 5.0f;
        totalporm3 = pconta->consumo * 0.05f;
    }
    else if(pconta->tipo == comercial)
    {
        taxa = 500.0f;
        totalporm3 = pconta->consumo * 0.25f;
    }
    else if(pconta->tipo == industrial)
    {
        taxa = 800.0f;
        totalporm3 = pconta->consumo * 0.04f;
    }

    pconta->valor = taxa + totalporm3;
}

void sort_contas(stConta* pcontas, int numcontas)
{
    for (int i = 0; i < numcontas; ++i)
        for (int j = 0; j < numcontas; j++)
        {
            if (pcontas[i].tipo < pcontas[j].tipo)
            {
                stConta tmp = pcontas[i];
                pcontas[i] = pcontas[j];
                pcontas[j] = tmp;
            }
        }
}

void imprime_contas(stConta* pcontas, int numcontas)
{
    printf("\n");
    for (int i = 0; i < numcontas; ++i)
    {
        const char* TIPO = NULL;

        if(pcontas[i].tipo == residencial)
            TIPO = TIPORESIDENCIAL;
        if(pcontas[i].tipo == comercial)
            TIPO = TIPOCOMERCIAL;
        if(pcontas[i].tipo == industrial)
            TIPO = TIPOINDUSTRIAL;

        printf("Cliente %s '%s': valor %f\n", TIPO, pcontas[i].idconta, pcontas[i].valor);
    }
}
