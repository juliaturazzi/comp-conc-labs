<h2>Atividade 1:
  <h4>2. 
    Sim, as mensagens "HELLO" foram printadas antes da "BYE" (a thread B encerra apenas após a thread A).
  <br>
  <h4>3. 
    Não, o programa não encerrou já que o contador x (variável global utilizada no programa) nunca chegou ao valor 2, que é a condição de desbloqueio da thread B.
  <br>
  <h4>5.
    O programa apresentou dois comportamentos diferentes:
   <h5>&emsp; 1. As mensagens "HELLO" foram printadas antes das "BYE".
   <h5>&emsp; 2. A thread B possui somente um sinal de desbloqueio, resultando no print de apenas um "BYE".
     

<br><br>
<h2>Atividade 2:
  <h4>2. 
    Sim, a mensagem "HELLO" foi printada antes das "BYE" (a thread A encerra apenas após a thread B).
 
    
<br><br>
<h2>Atividade 3:
   <h4>2.
     Não, a thread B printou alguns números fora do padrão como 19 e 23.
 <br>
   <h4>3.
     Sim, utilizando o while, temos uma verificação constante da condição, já com o if, verificamos apenas uma vez.
  <br>
   <h4>4. 
     Sim, é uma maneira de sempre retornar e verificar a condição, aumentando a precisão do código.
