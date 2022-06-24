//classe da estrutura de dados (recurso) compartilhado entre as threads
class Var {
    //recurso compartilhado
    private int var;
    
    //construtor
    public Var() { this.var = 0; }

    //lê var
    public int getVar() { return this.var; }

    //incrementa var
    public void incrementaVar() { this.var++; }

    //modifica var
    public void modificaVar(int x) { this.var = x; }
}

// Monitor que implementa a logica do padrao leitores/escritores
class LE {
    private int leit, escr;  
    
    // Construtor
    LE() { 
       this.leit = 0; //leitores lendo (0 ou mais)
       this.escr = 0; //escritor escrevendo (0 ou 1)
    } 
    
    // Entrada para leitores
    public synchronized void EntraLeitor (int id) {
      try { 
        while (this.escr > 0) {
        //if (this.escr > 0) {
           System.out.println ("le.leitorBloqueado("+id+")");
           wait();  //bloqueia pela condicao logica da aplicacao 
        }
        this.leit++;  //registra que ha mais um leitor lendo
        System.out.println ("le.leitorLendo("+id+")");
      } catch (InterruptedException e) { }
    }
    
    // Saida para leitores
    public synchronized void SaiLeitor (int id) {
       this.leit--; //registra que um leitor saiu
       if (this.leit == 0) 
             this.notify(); //libera escritor (caso exista escritor bloqueado)
       System.out.println ("le.leitorSaindo("+id+")");
    }
    
    // Entrada para escritores
    public synchronized void EntraEscritor (int id) {
      try { 
        while ((this.leit > 0) || (this.escr > 0)) {
        //if ((this.leit > 0) || (this.escr > 0)) {
           System.out.println ("le.escritorBloqueado("+id+")");
           wait();  //bloqueia pela condicao logica da aplicacao 
        }
        this.escr++; //registra que ha um escritor escrevendo
        System.out.println ("le.escritorEscrevendo("+id+")");
      } catch (InterruptedException e) { }
    }
    
    // Saida para escritores
    public synchronized void SaiEscritor (int id) {
       this.escr--; //registra que o escritor saiu
       notifyAll(); //libera leitores e escritores (caso existam leitores ou escritores bloqueados)
       System.out.println ("le.escritorSaindo("+id+")");
    }
  }
  
  //Aplicacao de exemplo--------------------------------------------------------
  // Thread 1
  class T1 extends Thread {
    int id; //identificador da thread
    int delay; //atraso bobo...
    LE monitor; //objeto monitor para coordenar a lógica de execução das threads
    Var var; //recurso compartilhado

    // Construtor
    T1 (int id, int delayTime, LE m, Var var) {
      this.id = id;
      this.delay = delayTime;
      this.monitor = m;
      this.var = var;
    }
  
    // Método executado pela thread
    public void run () {
      double j=777777777.7, i;
      try {
        for (;;) {
          this.monitor.EntraEscritor(this.id); 
          for (i=0; i<100000000; i++) {j=j/2;} //...loop bobo para simbolizar o tempo de escrita
          
          this.var.incrementaVar();
          
          this.monitor.SaiEscritor(this.id); 
          sleep(this.delay); //atraso bobo...
        }
      } catch (InterruptedException e) { return; }
    }
  }

  //--------------------------------------------------------
  // Thread 2
  class T2 extends Thread {
    int id; //identificador da thread
    int delay; //atraso bobo
    LE monitor; //objeto monitor para coordenar a lógica de execução das threads
    Var var; //recurso compartilhado

    // Construtor
    T2 (int id, int delayTime, LE m, Var var) {
      this.id = id;
      this.delay = delayTime;
      this.monitor = m;
      this.var = var;
    }
    
    // Método executado pela thread
    public void run () {
      double j=777777777.7, i;
      int varL;

      try {
        for (;;) {
          this.monitor.EntraLeitor(this.id);
          for (i=0; i<100000000; i++) {j=j/2;} //...loop bobo para simbolizar o tempo de leitura
          
          varL = this.var.getVar(); 

          if ((varL % 2) == 0) { System.out.println("O valor da variável é par.\n"); }
          else { System.out.println("O valor da variável é ímpar.\n"); }

          this.monitor.SaiLeitor(this.id);
          sleep(this.delay); 
        }
      } catch (InterruptedException e) { return; }
    }
  }

//--------------------------------------------------------
// Thread 3
class T3 extends Thread {
    int id; //identificador da thread
    int delay; //atraso bobo...
    LE monitor; //objeto monitor para coordenar a lógica de execução das threads
    Var var; //recurso compartilhado
  
    // Construtor
    T3 (int id, int delayTime, LE m, Var var) {
      this.id = id;
      this.delay = delayTime;
      this.monitor = m;
      this.var = var;
    }
  
    // Método executado pela thread
    public void run () {
      double j=777777777.7, i;
      int varL;

      try {
        for (;;) {
          this.monitor.EntraLeitor(this.id);
          
          varL = this.var.getVar();
          System.out.println("O valor da variávl é igual a " + varL);
          
          this.monitor.SaiLeitor(this.id);
  
          this.monitor.EntraEscritor(this.id);
          for (i=0; i<100000000; i++) {j=j/2;} //...loop bobo para simbolizar o tempo de escrita
          
          this.var.modificaVar(this.id);
          
          this.monitor.SaiEscritor(this.id); 
          sleep(this.delay); //atraso bobo...
        }
      } catch (InterruptedException e) { return; }
    }
  }
  
  //--------------------------------------------------------
  // Classe principal
  class LeitorEscritor {
    static final int x = 4;
    static final int y = 3;
    static final int z = 3;
  
    public static void main (String[] args) {
        int i;
        LE monitor = new LE();  // Monitor (objeto compartilhado entre leitores e escritores)
        
        Var var = new Var();  
      
      T1[] t1 = new T1[x]; // Threads escritores
      T2[] t2 = new T2[y];
      T3[] t3 = new T3[z]; // Threads leitores
  
      //inicia o log de saida
      System.out.println ("import verificaLE");
      System.out.println ("le = verificaLE.LE()");
      
      for (i=0; i<x; i++) {
         t1[i] = new T1(i+1, (i+1)*500, monitor, var);
         t1[i].start(); 
      }
      for (i=0; i<y; i++) {
         t2[i] = new T2(i+1, (i+1)*500, monitor, var);
         t2[i].start(); 
      }
      for (i=0; i<z; i++) {
        t3[i] = new T3(i+1, (i+1)*500, monitor, var);
        t3[i].start(); 
     }
  }
}