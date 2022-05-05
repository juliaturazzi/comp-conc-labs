Roteiro:
1. Implemente a func ̧ao de inicializac ̧  ̃ ao do vetor de entrada preenchendo seus cam-  ̃
pos com valores aleatorios  ́ do tipo float. O numero de elementos (N) do vetor  ́
deve ser informado pelo usuario na chamada do programa.  ́ Sugestao: defina  ̃
a variavel N do tipo  ́ long long int e use a func ̧ao ̃ atoll() para converter o valor
recebido do usuario (string) para long long int.  ́

2. Implemente uma func ̧ao sequencial  ̃ para resolver o problema e mec ̧a o seu tempo
de execuc ̧ao.  ̃

3. Implemente uma func ̧ao concorrente  ̃ para resolver o problema e mec ̧a o seu
tempo de execuc ̧ao. O  ̃ numero de threads (NTHREADS) deve ser informado  ́
pelo usuario na chamada do programa.  ́

4. Verifique a corretude da soluc ̧ao concorrente comparando seus resultados com os  ̃
resultados da versao sequencial para o mesmo vetor de entrada.  ̃

5. Calcule o ganho de desempenho (acelerac ̧ao) obtido com a vers  ̃ ao concorrente:  ̃
(Tsequencial/Tconcorrente). Considere os seguintes valores de N: 10ˆ5, 10ˆ7, 10ˆ8
(caso tenha espac ̧o de memoria suficiente). Para a vers  ́ ao concorrente, experimente  ̃
com 1, 2 e 4 threads. Repita a execuc ̧ao do programa ao menos  ̃ 5 vezes para
cada configurac ̧ao dos par  ̃ ametros de entrada. Use o menor tempo obtido nessas ˆ
execuc ̧oes para a vers  ̃ ao sequencial e para a vers  ̃ ao concorrente e ent  ̃ ao calcule a  ̃
acelerac ̧ao.  ̃ Escreva os resultados de acelerac ̧ao obtidos no README do c  ̃ odigo  ́
no GitHub ou GitLab.
