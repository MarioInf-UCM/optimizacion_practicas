# ALORITMO DE CHRISTOFIDES v1-> PROBLEMA DEL VIAJANTE EN UN GRAFO MÉTRICO COMPLETO

DUCUMENTACIÓN: Libro 2 página 30

PASOS:
1. Encontrar un árbol recubridor mínimo (TSP). //Algoritmo Kruskal o algoritmo de prim
2. Duplicar todas las aristas del árbol.
3. Encontrar un ciclo euleriano.
4. Eliminar repeticiones de dicho camino


DEF: Un árbol recubridor es un subgrado dentro de otro grafo que abarca todos los nodos del mismo sin formar ciclos.	
DEF: Un ciclo aureliano es un subgrado dentro de otro grafo que abarca todos los nodos del mismo pasando una única vez por cada arista y forma ciclos.
NOTA: Si quitamos una arista del recorrido optimo del TSP obtenemos un árbol recubridor.
		
coste(ARM) <= coste(TSP) 	//El coste del árbol recubridor mínimo obtenido será siempre menor que el coste del TSP.
coste(ciclo-aureliano) = 2*coste(ARM) <= 2*coste(TSP)
coste(algoritmo) <= coste(ciclo-aureliano) <= coste(TSP)
		
		
		
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
