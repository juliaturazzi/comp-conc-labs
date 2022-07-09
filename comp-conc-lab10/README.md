<h2>Atividade 1:
  <h4>(a) O valor inicial dos semáforos (em_e, em_l, escr, leit) deve ser igual a 1 para que o algoritmo funcione corretamente.
    
  <br>
  <h4>(b) Não é possível reduzir o uso dos mecanismos de sincronização, visto que os quatro semáforos presentes no programa são necessários para que a sincronização ocorra entre as threads de mesmo tipo (escritora e escritora, leitora e leitora)e de tipos diferentes (escritora e leitora).

  <br>
  <h4>(c)  Threads Leitoras = 2 e Escritoras = 6 <br>
  '''Escritor: 1 quer escrever!
Escritor: 1 esta escrevendo!
Escritor: 1 terminou de escrever!
Escritor: 2 quer escrever!
Escritor: 2 esta escrevendo!
Escritor: 2 terminou de escrever!
Escritor: 3 quer escrever!
Escritor: 3 esta escrevendo!
Escritor: 3 terminou de escrever!
Escritor: 4 quer escrever!
Escritor: 6 quer escrever!
Escritor: 6 esta escrevendo!
Escritor: 6 terminou de escrever!
Escritor: 4 esta escrevendo!
Escritor: 4 terminou de escrever!
Leitor: 2 quer ler!
Leitor: 2 esta lendo!
Leitor: 1 quer ler!
Leitor: 1 esta lendo!
Escritor: 5 quer escrever!
Escritor: 1 quer escrever!
Escritor: 2 quer escrever!
Escritor: 3 quer escrever!
Escritor: 6 quer escrever!
Escritor: 4 quer escrever!
Leitor: 2 terminou de ler!
Leitor: 2 quer ler!
Leitor: 1 terminou de ler!
Leitor: 1 quer ler!
Escritor: 5 esta escrevendo!
'''
  
   
<br>
Threads Leitoras = 4 e Escritoras = 3 <br>
'''Escritor: 1 quer escrever!
Escritor: 1 esta escrevendo!
Escritor: 1 terminou de escrever!
Escritor: 2 quer escrever!
Leitor: 2 quer ler!
Escritor: 2 esta escrevendo!
Leitor: 1 quer ler!
Escritor: 3 quer escrever!
Leitor: 3 quer ler!
Escritor: 2 terminou de escrever!
Escritor: 3 esta escrevendo!
Escritor: 3 terminou de escrever!
Leitor: 2 esta lendo!
Leitor: 1 esta lendo!
Leitor: 4 quer ler!
Leitor: 4 esta lendo!
Leitor: 3 esta lendo!
Escritor: 1 quer escrever!
Escritor: 2 quer escrever!
Escritor: 3 quer escrever!
Leitor: 2 terminou de ler!
Leitor: 3 terminou de ler!
Leitor: 3 quer ler!
Leitor: 2 quer ler!
Leitor: 1 terminou de ler!
Leitor: 1 quer ler!
Leitor: 4 terminou de ler!
Escritor: 1 esta escrevendo!
Escritor: 1 terminou de escrever!
Leitor: 4 quer ler!
'''