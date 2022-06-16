<h2>Atividade 1:
<h4>3. Sim. Isso ocorre porque depende da velocidade de cada thread. Podendo ser explicada a partir da falta de simultaneidade entre as threads gerando uma condição de corrida.

<br>
<h4>5. A mensagem "Terminou" aparece apenas após o término de todas as threads. Isso ocorre porque a main aguarda o término de todas as threads antes de printar a mensagem.


<br><br>

<h2>Atividade 3:
<h4>1. O valor de s é acessado e modificado por cada uma das threads. Dessa forma temos como seção crítica do código a tarefa realizada pelas threads. <br>
A saída esperada para o programa (valor final de s) seria 200000.

<br>
<h4>2. Não. Isso ocorre a partir da falta de sincronização entre as threads ocasionando uma condição de corrida (já que não há exclusão mútua).


<br><br>


<h2>Atividade 4:
<h4>3. Sim. Isso ocorre porque há uma sincronização entre as threads, dessa forma a necessidade da exclusão mútua foi atendida.