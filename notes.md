Déroulement approche threadée

Afin de garantir une bonne vitesse d'exécution par le processeur, on maintient le nombre total de threads comme étant au maximum égal au plus petit nombre de coeurs des deux machines (client et serveur). Il faut pas oublier de prendre en compte que le programme tourne déjà sur un coeur

| STEP | RECEIVER                        | SENDER                            | BOTH                    |
|:----:|:-------------------------------:|:---------------------------------:|:-----------------------:|
| 1    | X                               | X                                 | CORE COUNTING           |
| 2    | SEND CORE COUNT                 | RECEIVE RECEIVERs CORE COUNT      | X                       |
| 3    | RECEIVE FINAL COUNT             | SEND FINAL COUNT + FILES INFO     | X                       |
| 4    | PREPARE BUFFERS AND SOCKETS     | X                                 | X                       |
| 5    | X                               | X                                 | ASSIGN FILES TO THREADS |
| 6    | CONNECT TO REMOTE SERVER        | ACCEPT NEW CONNECTIONS ON THREADS | X                       |
| 7    | EACH THREAD RECEIVE THEIR FILES | EACH THREAD SEND THEIR FILES      | X                       |


