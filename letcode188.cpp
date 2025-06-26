#include <vector>
#include <algorithm> 
#include <climits> 

class Solution {
public:
    int maxProfit(int k, std::vector<int>& prices) {
        int n = prices.size();

        // Caso lucro zero:
        // Se não tem dias suficientes para, no mínimo, uma compra e uma venda,
        // ou se o enunciado não permite transações (k=0), o lucro é impossível.
        if (n < 2 || k == 0) {
            return 0;
        }

        // Para resolver, farei uso da programação dinâmica. A ideia é ter um controle do melhor resultado para cada transação, a cada dia que passa
        // O vetor vendas[j] irá guardar o lucro máximo, após concluir a j-ésima venda. Outro ponto, antes de qualquer operação, o lucro é 0.
        std::vector<int> vendas(k + 1, 0);

        // Compras[j] é o valor máximo após a j-ésima compra.
        // Pensando que uma compra sempre tem um custo, o valor fica negativo. Com o `INT_MIN`, consigo garantir que a primeira compra real 
        // (lucro da venda anterior - o preço de hoje) seja sempre um valor melhor do que este ponto de partida.
        std::vector<int> compras(k + 1, INT_MIN);

        // Percorrendo cada dia
        for (int price : prices) {
            // Para cada dia, será reavaliado qual é a melhor opção para cada transação j.
            for (int j = 1; j <= k; ++j) {
                // Para a j-ésima compra, é possível manter a ação que já havia sido comprada antes ou comprar a ação hoje. 
                // Para esta decisão, optei por subtrair o lucro da venda anterior vendas[j-1] e subtrair pelo preço de hoje. No fim, escolhe a melhor opção entre as duas.
                compras[j] = std::max(compras[j], vendas[j - 1] - price);

                // Para a j-ésima venda, também são duas opções:
                // Manter o lucro que já tem ( vendas[j] ) ou vender a ação. O lucro sera o valor da compra ( compras[j] ) + o valor de venda de hoje. No fim, escolhe a melhor opção entre as duas.
                vendas[j] = std::max(vendas[j], compras[j] + price);
            }
        }

        // Depois de passar por todos os dias, vendas[k] será o lucro máximo que pode ser obtido até k transações.
        return vendas[k];
    }
};
