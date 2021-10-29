# Compiladores-2021-II

Este es mi repositorio para para el curso de compiladores del ciclo 2021-II.  
El proyecto principal es la creación de un lenguaje de programación muy sencillo llamado: *_S_*.

## Requisitos y restricciones
- Los únicos sistemas operativos aceptados son aquellos basados en Linux.
- Python 3.6+.
- Instalador de paquetes **pip** para python.
- Manejador ede entornos virtuales en python **virtualenv**.
- Instalar la librería para graficar grafos en python **pygraphviz** 1.6+.
- Tener instalado **Cmake**.  

## Instrucciones de compilación
Para compilar el proyecto necesita de cmake, una vez descargado ejecute el siguiente comando en su terminal:  
```
cmake -S . -B build
```
entre dentro de la carpeta build y ejecute los siguientes pasos.  

## Instrucciones de ejecución
Una vez compilado el proyecto:
- dirigirse a la carpeta ```build```.
- si usa ```make``` como su compilador escriba el siguiente comando ```make```.
- por último ejecutará el binario de la siguiente manera:
```
./str_language source.txt
```
- tenemos incluidos en la carpeta tres ejemplos: ```vars.txt, source.txt, bucles.txt```, pruebe con alguno de ellos.
