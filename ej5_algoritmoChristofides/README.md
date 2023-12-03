# ALORITMO DE CHRISTOFIDES v1-> PROBLEMA DEL VIAJANTE EN UN GRAFO MÉTRICO COMPLETO

DUCUMENTACIÓN: Libro 2 página 30

PASOS:
1) **Encuentra un Árbol Generador de Costo Mínimo (MST):**
Utiliza un algoritmo para encontrar un árbol generador de costo mínimo en el grafo ponderado completo que representa el problema TSP. El algoritmo de Prim o el algoritmo de Kruskal son opciones comunes.

2) **Duplica las aristas del MST:**
Duplica cada arista en el árbol generador de costo mínimo para obtener un multiconjunto de aristas.

3) **Encuentra un emparejamiento perfecto mínimo en los vértices de grado impar:**
Identifica los vértices en el grafo que tienen grado impar en el árbol duplicado y encuentra un emparejamiento perfecto mínimo en estos vértices. Puedes utilizar algoritmos como el algoritmo de emparejamiento perfecto mínimo en grafos bipartitos.

4) **Combina el MST duplicado con el emparejamiento mínimo:**
Combina las aristas del árbol duplicado con las aristas del emparejamiento mínimo para obtener un grafo euleriano.

5) **Encuentra un ciclo euleriano en el grafo euleriano:**
Utiliza algoritmos para encontrar un ciclo euleriano en el grafo euleriano resultante. Un algoritmo clásico para esto es el algoritmo de Hierholzer.

6) **Elimina las repeticiones para obtener un circuito hamiltoniano:**
Elimina las repeticiones de vértices en el ciclo euleriano para obtener un circuito hamiltoniano. Puedes hacer esto mientras sigues el ciclo euleriano y agregas vértices que no se han visitado antes.

DEF: Un árbol recubridor es un subgrado dentro de otro grafo que abarca todos los nodos del mismo sin formar ciclos.	

DEF: Un ciclo aureliano es un subgrado dentro de otro grafo que abarca todos los nodos del mismo pasando una única vez por cada arista y forma ciclos.

NOTA: Si quitamos una arista del recorrido optimo del TSP obtenemos un árbol recubridor.



coste(ARM) <= coste(TSP) 	//El coste del árbol recubridor mínimo obtenido será siempre menor que el coste del TSP.

coste(ciclo-aureliano) = 2*coste(ARM) <= 2*coste(TSP)

coste(algoritmo) <= coste(ciclo-aureliano) <= coste(TSP)


>**Proceso corregido para obtener un ciclo euleriano a partir de un árbol recubridor mínimo:**
>
>1) Duplicar aristas: Duplica cada arista del árbol recubridor mínimo. Cada arista se duplica con el mismo origen y destino, de modo que tendrás dos aristas que conectan cada par de vértices.
>
>2) Conectar vértices impares (si es necesario): Después de duplicar las aristas, verifica si hay vértices con grado impar. Si hay exactamente dos vértices de grado impar, simplemente agrega una arista entre ellos para que ambos tengan grado par. Si hay más de dos vértices de grado impar, agrega aristas adicionales para convertirlos en vértices de grado par.
>
>3) Encontrar ciclo euleriano: Utiliza un algoritmo para encontrar un ciclo euleriano en el grafo modificado. Puedes emplear el algoritmo de Hierholzer, que es comúnmente utilizado para encontrar ciclos eulerianos.
>
>    a. Comienza en cualquier vértice.
>
>    b. Sigue un camino no visitado hasta que regreses al vértice inicial.
>
>    c. Si hay aristas no visitadas en el grafo, selecciona el vértice más reciente del camino actual que tiene aristas no visitadas y extiende el camino desde ese vértice.
>
>    d. Repite los pasos b y c hasta que todas las aristas estén visitadas.


		
		
		
# ALORITMO DE CHRISTOFIDES v2-> PROBLEMA DEL VIAJANTE EN UN GRAFO MÉTRICO COMPLETO

PASOS:
1. Encontramos un árbol recubridos mínimo.
2. Encontramos un matching optimo para los nodos de aridad impar de dicho árbol.
3. Juntamos el árbol de recubrimiento mínimo y el matching.
4. Encontramos un ciclo aureliano.
5. Eliminar las repeticiones del camino resultante.

NOTA: Para encontrar el árbol recubridad mínimo seleccionamos un subgrafo conformado por todos los nodos con aridad impar.
NOTA: Al ser un grafo completo debe haber al menos dos nodos con aridad impar.

coste(solucion) <= coste(ARM) + coste(matcingMinimo)
coste(solucion) <= coste(TSP) +1/2 coste(TSP)
coste <= 3/2 coste(TSP)
