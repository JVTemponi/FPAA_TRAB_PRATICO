import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner leitor = new Scanner(System.in);
        int n = leitor.nextInt();
        leitor.close();

        // Crio o objeto resolvedor e chamo o método que inicia o processo.
        ResolvedorNQueens resolvedor = new ResolvedorNQueens(n);
        List<List<String>> solucoes = resolvedor.resolver();

        // Após a conclusão da busca, percorro a lista de soluções e as imprimo.
        // Coloco também a linha em branco exigida.
        boolean primeiraSolucao = true;
        for (List<String> solucao : solucoes) {
            if (!primeiraSolucao) {
                System.out.println();
            }
            for (String linhaDoTabuleiro : solucao) {
                System.out.println(linhaDoTabuleiro);
            }
            primeiraSolucao = false;
        }
    }

    private static class ResolvedorNQueens {
        private final int tamanho; // Guarda o N do problema
        private final List<List<String>> todasAsSolucoes; // Armazena as soluções finais

        // Mapas de ataque para verificação 
        private final boolean[] colunasOcupadas;
        private final boolean[] diagPrincipalOcupadas; // Indexado por (linha - coluna)
        private final boolean[] diagSecundariaOcupadas; // Indexado por (linha + coluna)

        // Em vez de um tabuleiro char[][], guardo apenas a posição da rainha em cada linha.
        private final int[] posicoesRainhas;

        // Construtor: Prepara o ambiente para a resolução.
        public ResolvedorNQueens(int n) {
            this.tamanho = n;
            this.todasAsSolucoes = new ArrayList<>();
            this.colunasOcupadas = new boolean[n];
            this.diagPrincipalOcupadas = new boolean[2 * n - 1];
            this.diagSecundariaOcupadas = new boolean[2 * n - 1];
            this.posicoesRainhas = new int[n];
        }

        // Método público que inicia o processo e retorna a lista de soluções.
        public List<List<String>> resolver() {
            if (this.tamanho > 0) {
                 buscarSolucaoNaLinha(0);
            }
            return todasAsSolucoes;
        }

        //backtracking.
        private void buscarSolucaoNaLinha(int linha) {
            // Caso base: Se cheguei em uma linha que não existe (n), uma solução foi encontrada.
            if (linha == tamanho) {
                todasAsSolucoes.add(construirSolucaoVisual());
                return;
            }

            // Para a linha atual, testo cada coluna possível.
            for (int coluna = 0; coluna < tamanho; coluna++) {
                int indiceDiagPrincipal = linha - coluna + tamanho - 1;
                int indiceDiagSecundaria = linha + coluna;

                // Verifico nos meus mapas de ataque se a posição é segura.
                if (colunasOcupadas[coluna] || diagPrincipalOcupadas[indiceDiagPrincipal] || diagSecundariaOcupadas[indiceDiagSecundaria]) {
                    continue; // Se não for seguro, simplesmente pulo para a próxima coluna.
                }

                // Escolha
                posicoesRainhas[linha] = coluna;
                colunasOcupadas[coluna] = true;
                diagPrincipalOcupadas[indiceDiagPrincipal] = true;
                diagSecundariaOcupadas[indiceDiagSecundaria] = true;

                // Recursão
                buscarSolucaoNaLinha(linha + 1);

                //Backtrack 
                colunasOcupadas[coluna] = false;
                diagPrincipalOcupadas[indiceDiagPrincipal] = false;
                diagSecundariaOcupadas[indiceDiagSecundaria] = false;
            }
        }

        // Constrói a representação visual de uma solução (com '.' e 'Q') a partir do array de posições.
        private List<String> construirSolucaoVisual() {
            List<String> solucaoVisual = new ArrayList<>();
            for (int i = 0; i < tamanho; i++) {
                char[] linhaChars = new char[tamanho];
                for (int j = 0; j < tamanho; j++) {
                    if (posicoesRainhas[i] == j) {
                        linhaChars[j] = 'Q';
                    } else {
                        linhaChars[j] = '.';
                    }
                }
                solucaoVisual.add(new String(linhaChars));
            }
            return solucaoVisual;
        }
    }
}