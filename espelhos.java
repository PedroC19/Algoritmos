import java.math.BigInteger;

public class espelhos {

    public static BigInteger contarCaminhos(int n, int k) {
        if (n <= 0 || k < 0) return BigInteger.ZERO;

        BigInteger[] descendo = vetorZerado(n + 2);
        BigInteger[] subindo  = vetorZerado(n + 2);

        for (int i = 1; i <= n; i++) descendo[i] = BigInteger.ONE;

        for (int r = 1; r <= k; r++) {
            BigInteger[] novoDescendo = vetorZerado(n + 2);
            BigInteger[] novoSubindo  = vetorZerado(n + 2);
            for (int i = 1; i <= n; i++)
                novoDescendo[i] = novoDescendo[i - 1].add(subindo[i]);
            for (int i = n; i >= 1; i--)
                novoSubindo[i] = novoSubindo[i + 1].add(descendo[i]);
            descendo = novoDescendo;
            subindo  = novoSubindo;
        }
        return descendo[n].add(subindo[1]);
    }

    private static BigInteger[] vetorZerado(int tamanho) {
        BigInteger[] v = new BigInteger[tamanho];
        for (int i = 0; i < tamanho; i++) v[i] = BigInteger.ZERO;
        return v;
    }

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Uso: java espelhos <placas> <reflexoes>");
            return;
        }
        int n, k;
        try {
            n = Integer.parseInt(args[0]);
            k = Integer.parseInt(args[1]);
        } catch (NumberFormatException e) {
            System.err.println("Erro: informe dois numeros inteiros.");
            return;
        }
        if (n < 1 || k < 0) {
            System.err.println("Erro: placas deve ser >= 1 e reflexoes >= 0.");
            return;
        }
        System.out.println(contarCaminhos(n, k) + " reflexões");
    }
}
