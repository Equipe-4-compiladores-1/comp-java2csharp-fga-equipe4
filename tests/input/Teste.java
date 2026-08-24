class Teste {
    public static void main(String[] args) {
        int a = 10;
        char b = 25;
        boolean resultado = true;
        
        System.out.println("--- Teste do Transpilador ---");
        
        System.out.print("O valor de a eh: ");
        System.out.println(a);
        
        System.out.printf("O resultado de %c + %c eh: %b\n", a, b, resultado);
    }
}