# Proyecto: Nombre de tu proyecto
La idea principal del proyecto es que el usuario puede cargar un serie de datos en formato CSV. Aquí tome inspiración del metodo que usan en PANDAS con Python, donde es muy facil de manipular datos entrados. Mas de eso, es importante que se puede ordenar, filtrar, y cambiar datos. Aquí lo quieremos hacer tan eficiente posible.

## Descripción del avance 1
El primer avance is puro un algoritmo de ordenamiento. Como estamos trabajando con un serie de strings en un array 2D, tenemos que seleccionar cual columna quieremos usar para ordenar. Ademas, strings son ordenados lo mas eficiente con uso de radix sort, que tiene una complejidad de tiempo de `O(nk)`, donde `n` es la cantidad de datos y `k` es la cantidad de elementos en el string mas grande. Por eso es muy eficiente, como se trabaja en (casi) una forma linear. Si `k = n`, pues tenemos una complejidad cuadratica, pero eso sera muy dificil en un gran almacen de datos.

Al momento, el primer avance solo ordena la columna seleccionada en forma ascendiente. Esto lo quiero cambiar para que el usuario puede ordenar en cualquier dirección ellos quieren. Ademas quiero agregar la posibilidad de filtrar datos. Para el momento usamos un array 2D nombrado en el codigo, pero tambien aquí quiero agregar funcionalidad para que el usuario selecciona el archivo.

Funcionamiento basico del codigo fuente es lo siguiente: el almacen de datos se interpreta como una array 2D. Cuando el usuario elige una columna para ordenar, la programma no cambia el array original, pero cambia un otro array donde se guardan los indices. Con eso, guardamos los datos originales para que si hacemos un error sera posible volver al estado original (aún esto todavía se tiene que integrar).

## Instrucciones para compilar el avance de proyecto
Ejecuta el siguiente comando en la terminal:

`g++ radixSort.cpp -o primer_avance` 

## Instrucciones para ejecutar el avance de proyecto
Ejecuta el siguiente comando en la terminal:

`./primer_avance` 

## Descripción de las entradas del avance de proyecto
Al momento no hay entradas para el proyecto. Si es la idea que mas tarde se usa un archivo de formato CSV para analizar y modificar datos. Ahora pueden usar el array que se encuentra en el codigo fuente y se puede modificar este. Luego el usuario solo tiene que ingresar al mano de cual columna quiere ordenar el array.

## Descripción de las salidas del avance de proyecto
Salida del codigo al momento solo da el array ordenado al mano de la columna.

## Desarrollo de competencias

### SICT0301: Evalúa los componentes
#### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.
Como indicado en la descripción del avance 1, explico que el radix sort, el algoritmo de ordenamiento usado, tiene una complejidad de `O(nk)` en el peor de los casos, donde `k` es es el numero de elementos en el string mas largo. Al razon por cual tiene que ver con esta complejidad lo explico mas abajo:

1. Empezamos con el array desordenado.
1. El algoritmo mira al primer caracter del string, ordena el array a mano de esta caracter.
1. Si hay dos o mas strings con el mismo caracter, lo compara estes dos de la misma forma, ahorra mirando al proximo caracter.
1. Continua esto recursivamente hasta que no puede ordenar mas.

En el mejor de los casos, todos los strings tiene un primer caracter unico y ya esta ordenado. Cuando esto pasa, solo hacemos un paso para asegurar que esta ordenado, por lo cual tenemos un caso mejor de `O(n)`. En el caso que tenemos `n` strings de `k` elementos que son iguales hasta el ultimo elemento, tenemos un caso peor de `O(nk)`.

### SICT0302: Toma decisiones
#### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.
Para ordenar strings, el uso del algoritmo de radix sort de la forma explicado arriba me parece la mejor opción. Esta integración se llama MSD radix sort (Most Significant Digit), como empieza mirando al primer elemento de los strings. Usando LSD radix sort (Least Significant Digit), tendramos una complejidad temporal de `O(nk)` en cualquier de los casos (peor, promedio y mejor de los casos).

La unica mejora sera que tiene una complejidad de espacio mejor, de `O(n+B)`, donde `B=256` como es el radix de posibles caracteres. Para el MSD radix sort, sera una complejidad de espacio de `O(n+Bk)`. A cualquier caso, aquí sacrificamos un poco de espacio de memoria para mejorar nuestro tiempo de ejecución. Ademas, para ordenar strings, es mas logico para empezar al inicio del string, como ya podemos simplificar el proceso de ordenamiento si podemos eliminar strings del flujo de ordenamiento al inicio del algoritmo.