# Sistema de Evaluación de Exámenes Médicos

Práctica final del curso de Sistemas Operativos de la Universidad EAFIT para el 2019-1.

## Integrantes
- Stiven Ramírez Arango - sramir70@eafit.edu.co
- Anderson Daniel Grajales Alzate - agrajal7@eafit.edu.co
- Julián Sánchez Alzate - jsanch89@eafit.edu.co

# Herramientas a instalar
- Git.
- C++11.

# Compilación
	$ cd evaluador/
	$ make

# Ejecución

Se implementaron 5 comandos: **init**, **reg**, **ctlr**, **rep** y **stop** y para su correcta ejecución se deben abrir 2 consolas:

## Consola 1

### Comando init

	$ ./bin/evaluator init [-i <integer>] [-ie <integer>] [-oe <integer>] [-n <string>] [-b <integer>] [-d <integer>] [-s <integer>] [-q <integer>]

- **-i: ** Es el número de entradas que es es un valor positivo, si no es indicado el sistema tiene 5 entradas por omisión. 
- **-ie:** Es el número de posiciones en cada una de las colas de entrada, si no se indica tiene 6 posiciones por entrada. 
- **-oe:** Es el número de entradas en la cola de salida, sino se indica un valor el valor por omisión es 10. 
- **-n:** Indica el nombre del segmento de memoria compartida, por omisión es **evaluator**. 
- **-b:** Es el nivel de reactivo de sangre, por omisión tiene el valor máximo 100 de reactivo. 
- **-d:** Es el nivel de reactivo de detritos, por omisión tiene el valor máximo 100 de reactivo. 
- **-s:** Es el nivel de reactivo de piel, por omisión tiene el valor máximo 100 de reactivo. 
- **-q:** Es el tamaño de las colas internas por omisión 6.

Y se deja corriendo sin cerrar la consola.

## Consola 2

Se ejecuta el resto de comandos.

### Comando reg

	$ ./bin/evaluator reg [-n <string>] {{<filename>} ... | - }

- **-n:** Indica el nombre del segmento de memoria compartido string que guarda los recursos del sistema.
- **filename:** Es el nombre de un fichero válido, si el fichero no existe se ignora y no se envı́a ningún mensaje.

Tanto si es interactivo o por archivo cada registro tiene el siguiente formato:

	<integer> {B|D|S} <integer> NL

- **< integer >:** Indica la bandeja de entrada (0 a i − 1).
- **{B|D|S}:** Indica que la muestra es: **Blood**, **Detritus** o **Skin**.
- **< integer >:** Indica la cantidad de la muestra (1 . . . 5).
- **NL:** Representa una lı́nea nueva.

### Comando ctlr

	$ ./bin/evaluator ctlr [-n <string>]

- **-n:** Nombre de la región de memoria compartida.

Con éste comienza un modo interactivo donde se aceptan los siguientes subcomandos: **list** y **update**.

#### Subcomando list

	> list [ processing | waiting | reported | reactive | all ] NL

- **processing:** Permite listar los exámenes que están siendo procesados.
- **waiting:** Permite listar los exámenes que se encuentran esperando.
- **reported:** Permite listar los exámenes que serán reportados pero todavía no han sido tomados.
- **reactive:** Cantidad de reactivo para **Blood**, **Detritus** y **Skin**.
- **all:** Todo lo anterior.
- **NL:** Representa una lı́nea nueva.

#### Subcomando update

	> update { B | D | S } <integer> NL

- **{B|D|S}:** Indica que la muestra es: **Blood**, **Detritus** o **Skin**.
- **< integer >:** Indica la carga que se le añadirá a la actual.
- **NL:** Representa una lı́nea nueva.

### Comando rep

	$ ./bin/evaluator rep [-n <string>] { -i <integer> | -m <integer> }

- **-n:** Nombre del segmento de memoria compartida para borrar y parar el evaluador.
- **-i:** Indica que el reporte queda en modo interactivo esperando un tiempo indicado por el parámetro entero (en segundos).
- **-m:** Indica que el reporte obtiene hasta un número determinado de exámenes, sino hay espera hasta completar la cifra.

### Comando stop

	$ ./bin/evaluator stop [-n <string>]

- **-n:** Nombre del segmento de memoria compartida para borrar y parar el evaluador.
