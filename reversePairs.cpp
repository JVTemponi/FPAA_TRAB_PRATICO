#include <vector>

class Solution {
public:
    int reversePairs(std::vector<int>& numeros) {
        // Caso onde o vetor está vazio:
        // Se o vetor estiver vazio, não há o que fazer.
        if (numeros.empty()) {
            return 0;
        }
        // A contagem e ordenação é realizada do índice 0 até o final do vetor.
        return ordenaEConta(numeros, 0, numeros.size() - 1);
    }

private:
    // Função recursiva que ordena uma porção do array e conta os pares reversos.
    int ordenaEConta(std::vector<int>& numeros, int inicio, int fim) {
        // Caso base da recursão: se o trecho do vetor tem 1 ou 0 elementos, não há pares.
        if (inicio >= fim) {
            return 0;
        }

        // Encontrando o meio do trecho para a divisão.
        int meio = inicio + (fim - inicio) / 2;
        int contagem = 0;

        // A contagem é a soma dos pares da metade esquerda com os da metade direita.
        contagem += ordenaEConta(numeros, inicio, meio);
        contagem += ordenaEConta(numeros, meio + 1, fim);

        int j = meio + 1;

        // Dividindo o trabalho
        for (int i = inicio; i <= meio; ++i) {
            // Para cada elemento i na esquerda, é verificado quantos elementos j na direita satisfazem a condição do par reverso (numeros[i] > 2 * numeros[j]).
            // A conversão para long long (2LL) é para evitar estouro em números grandes.
            while (j <= fim && (long long)numeros[i] > 2LL * numeros[j]) {
                j++;
            }
            contagem += (j - (meio + 1));
        }

        // Merge dds duas metades de forma ordenada.
        // Fiz uma implementação padrão do Merge Sort. Ela garante que a contagem funcione nos níveis superiores da recursão.
        std::vector<int> temp;
        int i = inicio, k = meio + 1;
        while (i <= meio && k <= fim) {
            if (numeros[i] <= numeros[k]) {
                temp.push_back(numeros[i++]);
            } else {
                temp.push_back(numeros[k++]);
            }
        }
        while (i <= meio) {
            temp.push_back(numeros[i++]);
        }
        while (k <= fim) {
            temp.push_back(numeros[k++]);
        }

        // Copiando o trecho ordenado do vetor temporário de volta para o vetor original.
        for (int p = 0; p < temp.size(); ++p) {
            numeros[inicio + p] = temp[p];
        }

        return contagem;
    }
};
