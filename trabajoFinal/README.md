# Aplicación de procesamiento de heurísticas distribuidas 

El siguiente proyecto tiene como objetivo plantear las bases del funcionamiento de una aplicación futura destinada al cálculo distribuido de heurísticas mediante una arquitectura cliente-servidor, cuyos objetivos serán:
- Facilitar la comunicación entre procesos para la distribución de información relevante.
- Permitir llevar a cabo un despliegue distribuido y automatizado.
- Disponer de una gran versatilidad de configuración para las diferentes heurísticas participantes.
- Brindar a los usuarios la posibilidad de colaborar conjuntamente en la búsqueda de los puntos óptimos.



<br />

## Requisitos previos

Para poder utilizar la aplicación, antes de su uso será necesarios realizar los siguientes pasos previos:
- **Instalación de la biblioteca MPI para la de comunicación de procesos distribuidos:** Para la correcta instalación de la biblioteca, se recomienda seguir las instrucciones descritas en el siguiente [enlace](https://lsi2.ugr.es/jmantas/ppr/ayuda/datos/instalaciones/Instalacion_OpenMPI.pdf).
- **Instalación de la herramienta gnuplot para llevar a cabo la correcta proyección de gráficas en con resultados:** Para esto se debe ejecutar el siguiente comando:
    ```BASH
    sudo apt install gnuplot
    ```


<br />

## Arquitectura del proyecto

El proyecto se encuentra organizado en directorios y archivos. Pasamos a describir la funcionalidad de aquellos que consideramos relevantes:
- `src/:` Directorio que contiene el desarrollo del proyecto.
    - `FitnessFunction/:` Directorio que contiene las diferentes clases que definen las posibles funciones de fitness a utilizar por el sistema. Estas deben heredar de la clase `FitnessFunction`.
    - `Heuristic/:` Directorio que contiene las diferentes clases que definen las posibles heurísticas a utilizar por el sistema. Estas deben heredar de la clase `Heuristic`.
    - `Interface/:` Directorio que contiene las clases encargada de interaccionar con los elementos externos de a la aplicación.
        - `FileWriter_interface/:` Contiene la clase encargada de interaccionar con los ficheros de guardado de datos.
        - `Json_interface/:` Contiene la clase encargada de interaccionar con el fichero de configuración y extraer la misma.
- `bin/:` Directorio que contiene los archivos de compilación que ejecutarán el proyecto.
- `docs/:` Directorio que contiene tanto archivos externos importantes para la ejecución del proyecto como documentación relacionada con el mismo:
    - `config.json:` Archivo que contiene la definición de toda la configuración con la que se desarrollará el despliegue y funcionamiento del sistema.
    - `hots:` Archivo que contiene la dirección de aquellos equipos distribuidos que formarán parte del sistema y los núcleos involucrados en el mismo.
- `out/:` Directorio que almacena los datos de salida relevantes tras la ejecución del proyecto.
    - `logFile_*.txt:` Archivo que almacena los datos de salida relevantes tras la ejecución del proyecto.
    - `output.csv:` Archivo que almacena los datos estructurados necesarios para la proyección de gráficas.
- `scripts/:` Directorio que almacena lso scripts para la generación de gráficas mediante gnuplot.



<br />

## Descripción del proyecto

El paso para poder ejecutar correctamente el proyecto es la definición de un fichero de configuración donde se desarrollen 

```JSON
{
    "worldConfiguration":{
        "id": "MundoCirculo1",
        "fitnessFunctionID": "Pow2",
        "limitUp": 100,
        "limitDown": -100, 
        "limitRight": 100,
        "limitLeft": -100
    },
    "computerConfiguration": [{
        "IP": "0.0.0.0",
        "logCommonFile":"/home/mario/Documentos/universidad/optimizacion_practicas/trabajoFinal/out/logFile_MundoCirculo1.txt",
        "rankConfigurationList": [{
            "rankList": [0],
            "heuristicID": "ParticleSwarmOptimization",
            "outFIleURL": "/home/mario/Documentos/universidad/optimizacion_practicas/trabajoFinal/out/output.csv",
            "iterations": 500,
            "poblation" : 25,
            "dimensions": 4,
            "valueList":[0.3925, 2.5586, 1.3358]
        },
        {
            "rankList": [1],
            "heuristicID": "DifferentialEvolution",
            "outFIleURL": "/home/mario/Documentos/universidad/optimizacion_practicas/trabajoFinal/out/output.csv",
            "iterations": 500,
            "poblation" : 25,
            "dimensions": 4,
            "valueList":[0.7450, 0.9096]
        },
.
.
.
```



<br />

## Ejemplo de ejecución



<br />

## Aspectos a desarrollar

### Desarrollo del un programa servidor dedicado

Llevar a cabo una versión del proyecto dedicada al despliegue del programa servidor con el objetivo de que este pueda permanecer escuchando la posible anexión de nuevos clientes que ejecuten diferentes heurísticas. Este aspecto trae consigo las siguientes complicaciones:
- Desarrollo de un demonio ejecutado mediante hilos o procesos hijos que pueda encargarse de la escucha de nuevos mensajes y actuar en consecuencia.
- Adaptación de las direcciones de los nuevos clientes para poder enviar y recibir mensajes de los mismos mediante el uso de la biblioteca MPI.



<br />

### Envío de los parámetros de configuración iniciales desde el proceso principal o servidor

El proceso principal o el proceso servidor deben ser el encargado de obtener los parámetros de configuración, analizar los mismos y enviar a cada proceso que compone el proyecto su configuración correspondiente. Este aspecto trae consigo las siguientes complicaciones:
- Necesidad de creación de un tipo de dato derivado por cada tipo de dato necesario a enviar.



<br />

### Implementación de relojes de secuenciación

Es necesario la implementación de relojes para controlar correctamente la secuencialización de los mensajes enviados por el conjunto de procesos, con el objetivo de poder mostrar los resultados gráficos con un mayor pulido. Este aspecto trae consigo las siguientes complicaciones:
- Incremento de la dificultad en la transmisión de información mediante el paso de mensajes.