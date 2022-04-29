## 1) Calcule o desempenho obtido em cada caso e registre todos os resultados:

Utilizando dim = 500 e nthreads = 1:
Tempo de multiplicacao sequencial: 0.772230 segundos.
Tempo de multiplicacao concorrente com 1 thread(s): 1.156927 segundos.

Desempenho: 0.667

Utilizando dim = 500 e nthreads = 2:
Tempo de multiplicacao sequencial: 0.836028 segundos.
Tempo de multiplicacao concorrente com 2 thread(s): 0.798052 segundos.

Desempenho: 1.047


Utilizando dim = 1000 e nthreads = 1:
Tempo de multiplicacao sequencial: 4.981020 segundos.
Tempo de multiplicacao concorrente com 1 thread(s): 6.934273 segundos.

Deseempenho: 0.718

Utilizando dim = 1000 e nthreads = 2:
Tempo de multiplicacao sequencial: 8.842614 segundos.
Tempo de multiplicacao concorrente com 2 thread(s): 6.341367 segundos.

Desempenho: 1.394


Utilizando dim = 2000 e nthreads = 1:
Tempo de multiplicacao sequencial: 40.802178 segundos.
Tempo de multiplicacao concorrente com 1 thread(s): 53.497067 segundos.

Desempenho: 0.762

Utilizando dim = 2000 e nthreads = 2:
Tempo de multiplicacao sequencial: 40.585683 segundos.
Tempo de multiplicacao concorrente com 2 thread(s): 35.572970 segundos.

Desempenho: 1.140



## 2) Avalie se os resultados obtidos estão de acordo com o esperado, arescente a informação sobre a configuração ao lado do hardware da maquina usada para a avaliação (número de processadores).

Sim, isso porque verificamos que quando utilizamos um programa concorrente, com apenas uma thread, gastamos tempo na alocação de memória, aumentando o tempo necessário para executar o programa, sendo menos vantajoso que o sequencial.

Quando utilizamos um programa concorrente, com mais de uma thread, dividimos a tarefa, dessa forma otimizamos o tempo que o código executa a tarefa, comparado com execução o sequencial.