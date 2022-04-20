## 1) Há mudanças na ordem de execução das threads? Por que isso ocorre? 
   
   Sim. Isso porque as threads são colocadas na lista de tarefas para que o sistema operacional as execute, utilizando a política de escalonamento. 
  
   Durante a execução do programa não há controle sobre qual executará primeiro, levando à mudança de ordem entre as mesmas.



## 2) Qual foi a diferença em relação ao programa anterior?
   
   Passamos um argumento para a função que será executada pela thread (nesse caso um inteiro, identificador), distinguindo uma da outra e auxiliando 
   na criação de novas threads.
  
  
  
## 3) O programa funcionou como esperado?
   
   Sim. Isso porque cria uma estrutura de dados reunindo os campos necessários para a execução da thread, passando mais de um argumento para uma 
   thread, os preenchendo, a partir de uma variável auxiliar e convertendo o ponteiro do tipo int para void.
   


## 4) O que aconteceu de diferente em relação às versões/ execuções anteriores? 
  
   Utilizamos a função pthread_join(), permitindo que todas as threads terminassem de executar antes de encerrar o programa.
