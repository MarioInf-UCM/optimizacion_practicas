# Definir la variable para la dirección del archivo de datos
data_file = '/home/mario/Documentos/universidad/optimizacion/optimizacion_practicas/trabajoFinal/out/output.csv'

# Configuración de la terminal y la salida del gráfico
set terminal wxt persist
set title "Gráfica de Puntos"
set xlabel "Coordenada X"
set ylabel "Coordenada Y"

# Definir la paleta de colores
set palette model RGB defined (0 "red", 1 "green")

# Ocultar la barra lateral RGB
unset colorbox

# Mover la leyenda fuera de la gráfica
set key outside

# Leer datos desde el archivo y asignar colores según la etiqueta
plot data_file using 2:3:(strcol(1) eq 'DifferentialEvolution' ? 0 : 1) with points pointtype 7 pointsize 1 palette title '', \
     NaN title 'DifferentialEvolution' with points pt 7 ps 2 lc rgb 'green', \
     NaN title 'ParticleSwarmOptimization' with points pt 7 ps 2 lc rgb 'red'
#     NaN title 'ArtificialBeeColony' with points pt 7 ps 2 lc rgb 'blue', \
#     NaN title 'Fireworks' with points pt 7 ps 2 lc rgb 'orange'

