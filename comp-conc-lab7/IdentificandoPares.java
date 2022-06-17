// import para utilizar o array
import java.util.ArrayList;

// classe da estrutura de dados (recurso) compartilhado entre as threads
class Pares {
    // recurso compartilhado
    private ArrayList<Integer> vetorNumeros;
    private int par;

    // construtor
    public Pares(ArrayList<Integer> vetor) {
        this.par = 0;
        this.vetorNumeros = vetor; 
    }
    
    // operacao de leitura sobre o recurso compartilhado
    public int getVar(int r) { return this.vetorNumeros.get(r); }
    
    // incremento da variavel que guarda a quantidade de numeros pares
    public synchronized int numPar() { return this.par++; }

    // retorna os numeros pares
    public int getNumPares() { return this.par; }

    // recebe a quantidade de numeros presentes na lista
    public int quantNum() { return this.vetorNumeros.size(); }

  }

  // classe que estende Thread e implementa a tarefa de cada thread do programa 
  class T extends Thread {

    // identificador da thread
    private int id;

    // objeto compartilhado com outras threads
    Pares pares;

    // construtor
    public T(int tid, Pares pares) {
        this.id = tid;
        this.pares = pares;
    }

    // metodo main da thread
    public void run() {
        for (int i = id; i < this.pares.quantNum(); i+=IdentificandoPares.NTHREADS) { 
            if(((this.pares.getVar(i))%2) == 0) { pares.numPar(); }
        }

    }

  }

  // classe da aplicacao
  public class IdentificandoPares {
      static final int NTHREADS = 6;
      static final int TAM_LISTA = 20000;
      
      public static void main (String[] args) {
      
      // reserva espaço para um vetor de threads
      Thread[] threads = new Thread[NTHREADS];

      // cria e inicializa o array
      ArrayList<Integer> par = new ArrayList<>();
      for (int i = 0; i < TAM_LISTA; i++) { par.add(i); }

      // cria uma instancia do recurso compartilhado entre as threads
      Pares pares = new Pares(par);

      // cria as threads da aplicacao
      for (int i=0; i<threads.length; i++) { threads[i] = new T(i, pares); }

      // inicia as threads
      for (int i=0; i<threads.length; i++) { threads[i].start(); }

      // espera pelo termino de todas as threads
      for (int i=0; i<threads.length; i++) {
        try { threads[i].join(); } catch (InterruptedException e) { return; }
     }

     System.out.printf("Há %d números pares presentes na lista com %d números.", pares.getNumPares(), TAM_LISTA);

  }

}
