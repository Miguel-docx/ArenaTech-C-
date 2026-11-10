#include <stdio.h>
#include <locale.h>

#define ORCAMENTO 1000.0
#define POTENCIA_W 800.0
#define PRECO_KWH 1.2
#define PRECO_KIT 20.0

int main(void)
{
    setlocale(LC_CTYPE, "");

    /* Entradas */
    int qte_participantes;
    int qte_jogadores_por_time;
    int qte_computadores;

    double duracao;
    double outros_custos;

    printf("Qual a quantidade de participantes? ");
    if (scanf("%d", &qte_participantes) != 1 ||
        qte_participantes <= 0) {
        printf("Erro: informe uma quantidade positiva de participantes.\n");
        return 1;
    }

    printf("Quantos jogadores em cada time? ");
    if (scanf("%d", &qte_jogadores_por_time) != 1 ||
        qte_jogadores_por_time <= 0) {
        printf("Erro: informe uma quantidade positiva de jogadores.\n");
        return 1;
    }

    printf("Quantos computadores estao disponiveis? ");
    if (scanf("%d", &qte_computadores) != 1 ||
        qte_computadores < 0) {
        printf("Erro: a quantidade de computadores deve ser zero ou maior.\n");
        return 1;
    }

    printf("Duracao do evento em horas: ");
    if (scanf("%lf", &duracao) != 1 ||
        !(duracao > 0.0 && duracao <= 168.0)) {
        printf("Erro: informe uma duracao maior que zero e de ate 168 horas.\n");
        return 1;
    }

    printf("Outros custos do evento (R$, use ponto para decimais): ");
    if (scanf("%lf", &outros_custos) != 1 ||
        !(outros_custos >= 0.0 && outros_custos <= 1000000000.0)) {
        printf("Erro: informe um custo entre zero e 1 bilhao de reais.\n");
        return 1;
    }

    /* Quantidade de times, permitindo um time incompleto */
    int times_completos =
        qte_participantes / qte_jogadores_por_time;

    int participantes_restantes =
        qte_participantes % qte_jogadores_por_time;

    int qte_times = times_completos;

    if (participantes_restantes > 0) {
        qte_times++;
    }

    /* Infraestrutura: um computador por participante */
    int computadores_faltantes = 0;

    if (qte_computadores < qte_participantes) {
        computadores_faltantes =
            qte_participantes - qte_computadores;
    }

    /* Energia: todos os computadores disponiveis ligados */
    double consumo_energia =
        (qte_computadores * POTENCIA_W * duracao) / 1000.0;

    double custo_energia = consumo_energia * PRECO_KWH;

    /* Custos */
    double custo_alimentacao = qte_participantes * PRECO_KIT;

    double custo_total =
        custo_energia + custo_alimentacao + outros_custos;

    double custo_por_participante =
        custo_total / qte_participantes;

    double saldo = ORCAMENTO - custo_total;

    /* Relatorio */
    printf("\n======= ARENA TECH =======\n\n");

    printf("Participantes: %d\n", qte_participantes);
    printf("Jogadores por time: %d\n", qte_jogadores_por_time);
    printf("Quantidade de times: %d\n", qte_times);
    printf("Times completos: %d\n", times_completos);

    if (participantes_restantes > 0) {
        printf("Time incompleto: %d participante(s)\n",
               participantes_restantes);
    }

    printf("Computadores disponiveis: %d\n", qte_computadores);

    if (computadores_faltantes == 0) {
        printf("Infraestrutura: SUFICIENTE\n");
    } else {
        printf("Infraestrutura: INSUFICIENTE\n");
        printf("Computadores faltantes: %d\n", computadores_faltantes);
    }

    printf("\nDuracao: %.2f horas\n", duracao);
    printf("Consumo estimado: %.2f kWh\n", consumo_energia);

    if (consumo_energia <= 20.0) {
        printf("Classificacao do consumo: BAIXO\n");
    } else if (consumo_energia <= 40.0) {
        printf("Classificacao do consumo: MODERADO\n");
    } else {
        printf("Classificacao do consumo: ALTO\n");
    }

    printf("\n======= CUSTOS =======\n\n");

    printf("Energia: R$ %.2f\n", custo_energia);
    printf("Alimentacao: R$ %.2f\n", custo_alimentacao);
    printf("Outros custos: R$ %.2f\n", outros_custos);
    printf("CUSTO TOTAL: R$ %.2f\n", custo_total);
    printf("CUSTO POR PARTICIPANTE: R$ %.2f\n",
           custo_por_participante);

    printf("\n======= ORCAMENTO =======\n\n");

    printf("Orcamento disponivel: R$ %.2f\n", ORCAMENTO);
    printf("Saldo: R$ %.2f\n", saldo);

    if (custo_total > ORCAMENTO) {
        printf("Situacao: ACIMA DO ORCAMENTO\n");
    } else if (saldo <= ORCAMENTO * 0.05) {
        printf("Situacao: NO LIMITE DO ORCAMENTO\n");
    } else {
        printf("Situacao: DENTRO DO ORCAMENTO\n");
    }

    return 0;
}

