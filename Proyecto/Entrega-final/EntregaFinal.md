# Proyecto: Nombre de tu proyecto
La idea principal del proyecto es que el usuario puede cargar un serie de datos en formato CSV. Los datos para la 'aplicación' sera parecido a un tracker de música, como con Scrobbles de [Last.FM](https://www.last.fm/about/trackmymusic). El usuario podra ingresar otros numeros a la lista, y con cada jugada se incrementa la cantidad de veces que se ha escuchado al canción. Luego, el usuario podrá mirar a los canciones a cual escuchan más.

## Descripción del avance 1
El primer avance is puro un algoritmo de ordenamiento. Como estamos trabajando con un serie de strings en un array 2D, tenemos que seleccionar cual columna quieremos usar para ordenar. Ademas, strings son ordenados lo mas eficiente con uso de radix sort, que tiene una complejidad de tiempo de `O(nk)`, donde `n` es la cantidad de datos y `k` es la cantidad de elementos en el string mas grande. Por eso es muy eficiente, como se trabaja en (casi) una forma linear. Si `k = n`, pues tenemos una complejidad cuadratica, pero eso sera muy dificil en un gran almacen de datos.

Al momento, el primer avance solo ordena la columna seleccionada en forma ascendiente. Esto lo quiero cambiar para que el usuario puede ordenar en cualquier dirección ellos quieren. Ademas quiero agregar la posibilidad de filtrar datos. Para el momento usamos un array 2D nombrado en el codigo, pero tambien aquí quiero agregar funcionalidad para que el usuario selecciona el archivo.

Funcionamiento basico del codigo fuente es lo siguiente: el almacen de datos se interpreta como una array 2D. Cuando el usuario elige una columna para ordenar, la programma no cambia el array original, pero cambia un otro array donde se guardan los indices. Con eso, guardamos los datos originales para que si hacemos un error sera posible volver al estado original (aún esto todavía se tiene que integrar).

## Descripción del avance 2
Este avance agrega una estructura de datos para guardar los datos de la aplicación. Las estructuras escogidos fueron un `unordered_map` y un `stack`. Estos son dos estructuras muy eficientes en su complejidad de tiempo. Opino que, ademas el `unordered_map` es una estructura eficiente para la meta de la aplicación, cual se explica más en el parte abajo.

En el avance, solo trabaje en la mapa para guardar, leer, ingresar, y cambiar datos. No pude agregar la funcionalidad del primer avance adentro de este como no tení suficiente tiempo este ciclo para trabajar en ello. Con el tercer avance voy a trabajar más en ella y también para arreglar los errores del primer avance que me occurieron.

Un otro elemento en cual trabaje un poco fue el archivo `readCSV.h` para leer los datos. Aquí tome inspiración de algún repo, aún no recuerdo cual al momento y lo voy a buscar para la entrega final. Cambié algunos elementos para que se funciona a la manera que quiero para la aplicación final.

Se puede cambiar el `main.cpp` para hacer más casos de prueba. Al momento el `main.cpp` solo ingresa los datos del archivo `rock-songs.csv` y hace una prueba de ingresar un elemento con la cantidad de filas incorrecto.

Ya hay alguna manera de manejar con los errores que pueden salir de la programa, aún voy a cambiar estos para la aplicación final para que solo se da un error y no cierra la aplicación. Estos son algunos cosas que quiero cambiar cuando tengo más tiempo.

### Cambios sobre el primer avance
1. Escribe la lista de cambios realizados sobre el planteamiento original: Argumenta la razón por la que decidiste el cambio. Estos argumentos puedes retomarlos más adelante en tu argumentación de competencias.
2. Cambio 2: Razón del cambio
3. Cambio 3: Razón del cambio
4. etc...: etc...

### Cambios sobre el segundo avance
1. Cambio en la logica de `insertRow` para añadir la primera fila. Esto no lo había visto en la entrega del segundo avance, por lo cual se cambio ahora.
1. Cambio de `getCell` en donde se devuelve un valor vacia en caso de una celda incorecta.
1. cambio minima in `printRow` para hacerlo más lindo en imprimiendo las filas.
1. Saque de expections para evitar que la programa rompe cuando el usuario hace un error. Ahora funciona con otra forma de manejar a los errores.

## Descripción de la entrega final
Escribe aquí la descripción de lo que contiene este avance.

## Instrucciones para compilar el avance de proyecto
Ejecuta el siguiente comando en la terminal:

`g++ -std=c++14 header.h address.h readCSV.h  radixSort.h writeCSV.h main.cpp -o musicList` 

## Instrucciones para ejecutar el avance de proyecto
Ejecuta el siguiente comando en la terminal:

`./musicList` 

## Descripción de las entradas del avance de proyecto
Escribe aquí la descripción de las entradas del proyecto, por ejemplo, si de entrada se requieren varios archivos, hay que indicar el formato de cada uno de ellos, y proporcionar un ejemplo de los datos de cada archivo.

## Descripción de las salidas del avance de proyecto
Escribe aquí la descripción de los resultados de la ejecución de tu programa.

## Desarrollo de competencias

### SICT0301: Evalúa los componentes
#### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.
Si lograste este criterio anteriormente, copia aquí tu argumentación. Si no, ésta es una nueva oportunidad para lograrlo. Escribe aquí tu aprendizaje y tus argumentos sobre por qué consideras que ahora ya has desarrrollado este criterio y dónde se puede observar el desarrollo que mencionas.

#### Hace un análisis de complejidad correcto y completo de todas las estructuras de datos y cada uno de sus usos en el programa.
Si lograste este criterio anteriormente, copia aquí tu argumentación. Si no, ésta es una nueva oportunidad para lograrlo. Escribe aquí tu aprendizaje y tus argumentos sobre por qué consideras que ahora ya has desarrrollado este criterio y dónde se puede observar el desarrollo que mencionas.

#### Hace un análisis de complejidad correcto y completo para todos los demás componentes del programa y determina la complejidad final del programa.
Escribe aquí tus argumentos sobre por qué consideras que has desarrrollado esta competencia y dónde se puede observar el desarrollo que mencionas.

### SICT0302: Toma decisiones
#### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.
Si lograste este criterio anteriormente, copia aquí tu argumentación. Si no, ésta es una nueva oportunidad para lograrlo. Escribe aquí tu aprendizaje y tus argumentos sobre por qué consideras que ahora ya has desarrrollado este criterio y dónde se puede observar el desarrollo que mencionas.

#### Selecciona una estructura de datos adecuada al problema y la usa correctamente.
Si lograste este criterio anteriormente, copia aquí tu argumentación. Si no, ésta es una nueva oportunidad para lograrlo. Escribe aquí tu aprendizaje y tus argumentos sobre por qué consideras que ahora ya has desarrrollado este criterio y dónde se puede observar el desarrollo que mencionas.

### SICT0303: Implementa acciones científicas
#### Implementa mecanismos para consultar información de las estructras correctos.
Si lograste este criterio anteriormente, copia aquí tu argumentación. Si no, ésta es una nueva oportunidad para lograrlo. Escribe aquí tu aprendizaje y tus argumentos sobre por qué consideras que ahora ya has desarrrollado este criterio y dónde se puede observar el desarrollo que mencionas.

#### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.
Si lograste este criterio anteriormente, copia aquí tu argumentación. Si no, ésta es una nueva oportunidad para lograrlo. Escribe aquí tu aprendizaje y tus argumentos sobre por qué consideras que ahora ya has desarrrollado este criterio y dónde se puede observar el desarrollo que mencionas.

### Implementa mecanismos de escritura de archivos para guardar los datos  de las estructuras de manera correcta
Escribe aquí tus argumentos sobre por qué consideras que has desarrrollado esta competencia y dónde se puede observar el desarrollo que mencionas.