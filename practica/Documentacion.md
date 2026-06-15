# Práctica 1 — Lógica Binaria y Combinational

**Universidad San Carlos de Guatemala**
**Facultad de Ingeniería**
**Ingeniería en Ciencias y Sistemas**

**Curso:** Organización Computacional
**Práctica:** 1 Lógica Binaria y Combinational
**Grupo:** G9
**Fecha:** Junio 2026

**Grupo:**

**Nombre: Fabián Dario Godoy Ruiz Carne: 202248928**

**Nombre: Mynor Gilberto Gutiérrez García Carne: 202246527**

**Nombre: José Humberto Melchor Pérez Carne: 202145925**

**Nombre: Raúl Antonio Ruiz Sagastume Carne: 201941152**

**Nombre: Clara Isabel Solís González Carne: 202146478**

**Nombre: Daniel José Camposeco Recinos Carne: 201941081**

**Nombre: Dante Alceo Rivera del Cid Carne: 202246956**

**Guatemala, 15 de junio de 2026**

# Introducción

Los sistemas digitales y organizacion computacional juegan un papel fundamental para el diseño y análisis de sistemas combinacionales. Realizar operaciones lógicas y aritméticas a partir de señales binarias.

La presente práctica de laboratorio tiene el diseño e implemetación un sistema digital denominado LogicCalc, el cual funciona como una unidad aritmética lógica básica. El sistema desarrollado es capaz realizar las operaciones aritméticas: suma, resta, multiplicación y potencia; así como operaciones lógicas como AND, OR, NAND Y XNOR.

Adicionalmente el sistema muestra los resultados binarios obtenidos de manera clara mediante displays, para su obtención se usaron compuertas lógicas e integrados permitidos, asimismo el diseño fue desarrollado en la herramienta Proteus para verificación y posteriormente construir su versión física en protoboard.

# Objetivos

General

Diseñar e implementar un sistema aritmetica lógica, aplicando el uso de funciones booleanas, mapas de karnaugh, álgebra booleana, operaciones aritmeticas y lógicas, fortaleciendo habilidades técnicas y comprensión a los conocimientos necesarios para el funcionamiento del sistema combinacional.

Especificos

- Crear una Unidad Aritmética Lógica para hacer cálculos numéricos sobre valores binarios.
- Crear una unida con operaciones logicas AND, OR, NAND Y XNOR, junto con la unidad comparativa correctamente e implementarlo en el sistema.
- Mostrar datos numéricos y comparados en pantallas de siete segmentos, asegurando una lectura comprensible y operativa.

# Funciones Booleanas

Sumador

| A1  | B1  | C1  | S1  | Cout |
| --- | --- | --- | --- | ---- |
| 0   | 0   | 0   | 0   | 0    |
| 0   | 0   | 1   | 1   | 0    |
| 0   | 1   | 0   | 1   | 0    |
| 0   | 1   | 1   | 0   | 1    |
| 1   | 0   | 0   | 1   | 0    |
| 1   | 0   | 1   | 0   | 1    |
| 1   | 1   | 0   | 0   | 1    |
| 1   | 1   | 1   | 1   | 1    |

Función: S=A′B′C+A′BC′+AB′C′+ABC

Función de acarreo: Cout=AB+AC+BC

Funcion lógica de 3 variables

| A   | B   | C   | A+B | (A+B)C |
| --- | --- | --- | --- | ------ |
| 1   | 1   | 1   | 1   | 1      |
| 1   | 1   | 0   | 1   | 0      |
| 1   | 0   | 1   | 1   | 1      |
| 1   | 0   | 0   | 1   | 0      |
| 0   | 1   | 1   | 1   | 1      |
| 0   | 1   | 0   | 1   | 0      |
| 0   | 0   | 1   | 0   | 0      |
| 0   | 0   | 0   | 0   | 0      |

F=AC+BC

Función Lógica de 4 variables

| A   | B   | C   | D   | A+B | (A+B)C | ((A+B)C)+D |
| --- | --- | --- | --- | --- | ------ | ---------- |
| 1   | 1   | 1   | 1   | 1   | 1      | 1          |
| 1   | 1   | 1   | 0   | 1   | 1      | 1          |
| 1   | 1   | 0   | 1   | 1   | 0      | 1          |
| 1   | 1   | 0   | 0   | 1   | 0      | 0          |
| 1   | 0   | 1   | 1   | 1   | 1      | 1          |
| 1   | 0   | 1   | 0   | 1   | 1      | 1          |
| 1   | 0   | 0   | 1   | 1   | 0      | 1          |
| 1   | 0   | 0   | 0   | 1   | 0      | 0          |
| 0   | 1   | 1   | 1   | 1   | 1      | 1          |
| 0   | 1   | 1   | 0   | 1   | 1      | 1          |
| 0   | 1   | 0   | 1   | 1   | 0      | 1          |
| 0   | 1   | 0   | 0   | 1   | 0      | 0          |
| 0   | 0   | 1   | 1   | 0   | 0      | 1          |
| 0   | 0   | 1   | 0   | 0   | 0      | 0          |
| 0   | 0   | 0   | 1   | 0   | 0      | 1          |
| 0   | 0   | 0   | 0   | 0   | 0      | 0          |

F=AC+BC+D

Detector de número mayor o igual a 10

| **S4** | **S3** | **S2** | **S3+S2** | **F** |
| ------ | ------ | ------ | --------- | ----- |
| 0      | 0      | 0      | 0         | 0     |
| 0      | 0      | 1      | 1         | 0     |
| 0      | 1      | 0      | 1         | 0     |
| 0      | 1      | 1      | 1         | 0     |
| 1      | 0      | 0      | 0         | 0     |
| 1      | 0      | 1      | 1         | 1     |
| 1      | 1      | 0      | 1         | 1     |
| 1      | 1      | 1      | 1         | 1     |

F=S4S3+S4S2

Función letra E en display

| **A < B** | **Mayor10** | **Segmentos A, D, E, F, G** |
| --------- | ----------- | --------------------------- |
| 0         | 0           | 0                           |
| 0         | 1           | 0                           |
| 1         | 0           | 1                           |
| 1         | 1           | 1                           |

F=A<B

Función para número 1 en display

| **A < B** | **Mayor10** | **Segmentos B, C** |
| --------- | ----------- | ------------------ |
| 0         | 0           | 0                  |
| 0         | 1           | 1                  |
| 1         | 0           | 0                  |
| 1         | 1           | 0                  |

F=(A<B)′⋅Mayor10

Funciones para unidad lógica

| **A** | **B** | **AND** | **OR** | **NAND** | **XNOR** |
| ----- | ----- | ------- | ------ | -------- | -------- |
| 0     | 0     | 0       | 0      | 1        | 1        |
| 0     | 1     | 0       | 1      | 1        | 0        |
| 1     | 0     | 0       | 1      | 1        | 0        |
| 1     | 1     | 1       | 1      | 0        | 1        |

AND: F=AB

OR: F=A+B

NAND: F=(AB)′

XNOR: F=AB+A′B′

# Mapas de Karnaugh

Sumadores

| A1  | B1  | C1  | S1  | Cout |
| --- | --- | --- | --- | ---- |
| 0   | 0   | 0   | 0   | 0    |
| 0   | 0   | 1   | 1   | 0    |
| 0   | 1   | 0   | 1   | 0    |
| 0   | 1   | 1   | 0   | 1    |
| 1   | 0   | 0   | 1   | 0    |
| 1   | 0   | 1   | 0   | 1    |
| 1   | 1   | 0   | 0   | 1    |
| 1   | 1   | 1   | 1   | 1    |

Mapa para S1

|     | 00  | 01  | 11  | 10  |
| --- | --- | --- | --- | --- |
| 0   | 0   | 1   | 0   | 1   |
| 1   | 1   | 0   | 1   | 0   |

S= A'B'C+A'BC'+AB'C'+ABC

Mapa para Cout

|     | 00  | 01  | 11  | 10  |
| --- | --- | --- | --- | --- |
| 0   |     |     | 1   |     |
| 1   |     | 1   | 1   | 1   |

Co= BC + AC + AB


| A   | B   | C   | A+B | (A+B)C |
| --- | --- | --- | --- | ------ |
| 1   | 1   | 1   | 1   | 1      |
| 1   | 1   | 0   | 1   | 0      |
| 1   | 0   | 1   | 1   | 1      |
| 1   | 0   | 0   | 1   | 0      |
| 0   | 1   | 1   | 1   | 1      |
| 0   | 1   | 0   | 1   | 0      |
| 0   | 0   | 1   | 0   | 0      |
| 0   | 0   | 0   | 0   | 0      |

| A\\BC | 00  | 01  | 11  | 10  |
| ----- | --- | --- | --- | --- |
| 0     | 0   | 0   | 1   | 0   |
| 1     | 0   | 1   | 1   | 0   |

F= AC + BC

F=C(A+B)


| A   | B   | C   | D   | A+B | (A+B)C | ((A+B)C)+D |
| --- | --- | --- | --- | --- | ------ | ---------- |
| 1   | 1   | 1   | 1   | 1   | 1      | 1          |
| 1   | 1   | 1   | 0   | 1   | 1      | 1          |
| 1   | 1   | 0   | 1   | 1   | 0      | 1          |
| 1   | 1   | 0   | 0   | 1   | 0      | 0          |
| 1   | 0   | 1   | 1   | 1   | 1      | 1          |
| 1   | 0   | 1   | 0   | 1   | 1      | 1          |
| 1   | 0   | 0   | 1   | 1   | 0      | 1          |
| 1   | 0   | 0   | 0   | 1   | 0      | 0          |
| 0   | 1   | 1   | 1   | 1   | 1      | 1          |
| 0   | 1   | 1   | 0   | 1   | 1      | 1          |
| 0   | 1   | 0   | 1   | 1   | 0      | 1          |
| 0   | 1   | 0   | 0   | 1   | 0      | 0          |
| 0   | 0   | 1   | 1   | 0   | 0      | 1          |
| 0   | 0   | 1   | 0   | 0   | 0      | 0          |
| 0   | 0   | 0   | 1   | 0   | 0      | 1          |
| 0   | 0   | 0   | 0   | 0   | 0      | 0          |

| AB\\CD | 00  | 01  | 11  | 10  |
| ------ | --- | --- | --- | --- |
| 00     | 0   | 1   | 1   | 0   |
| 01     | 0   | 1   | 1   | 1   |
| 11     | 0   | 1   | 1   | 1   |
| 10     | 0   | 1   | 1   | 1   |

F= D + BC + AC

F=C(A + B) + D

| **8** | **4** | **2** | **Mayor a 10** |
| ----- | ----- | ----- | -------------- |
| S4    | S3    | S2    | 0              |
| 0     | 0     | 0     | 0              |
| 0     | 0     | 1     | 0              |
| 0     | 1     | 0     | 0              |
| 0     | 1     | 1     | 0              |
| 1     | 0     | 0     | 1              |
| 1     | 0     | 1     | 1              |
| 1     | 1     | 0     | 1              |
| 1     | 1     | 1     |                |

S4(S3 + S2)

S4S3 +S42

|         | "E" | "1"      |
| ------- | --- | -------- |
|         | A<B | Mayor 10 |
| Apagado | 0   | 0        |
| "1"     | 0   | 1        |
| "E"     | 1   | 0        |
| "E"     | 1   | 1        |

A<B: A, D, E, F, G

Mayor 10: B, C

| A<B\\M10 | 00  | 01  |
| -------- | --- | --- |
| 0        | 0   | 0   |
| 1        | 1   | 1   |

Segmentos:

A, D, E

F, G

| A<B\\M10 | 00  | 01  |
| -------- | --- | --- |
| 0        | 0   | 1   |
| 1        | 0   | 0   |

Segmentos:

B, C

| C3  | S4  | C4  | S3 v S4 | (S3 v S4)C4 |
| --- | --- | --- | ------- | ----------- |
| 0   | 0   | 0   | 1       | 1           |
| 0   | 0   | 1   | 0       | 0           |
| 0   | 1   | 0   | 1       | 1           |
| 0   | 1   | 1   | 1       | 0           |
| 1   | 0   | 0   | 1       | 1           |
| 1   | 0   | 1   | 1       | 0           |
| 1   | 1   | 0   | 0       | 0           |
| 1   | 1   | 1   | 0       | 0           |

| S3\\S4C4 | 00  | 01  | 11  | 10  |
| -------- | --- | --- | --- | --- |
| 0        | 0   | 0   | 1   | 0   |
| 1        | 0   | 1   | 1   | 0   |

F=S3C4+S4C4

F=C4(S3+S4)

# Diagramas de Diseño

Unidad Aritmética

La unidad aritmética se encarga de las operaciones numéricas con valores binarios. En este módulo se introducen dos números binarios, que se denominan A y B, y el circuito procesa estos datos para obtener resultados como sumas, restas, multiplicaciones y potencias.  
<br/>Para realizar la suma se usan sumadores binarios, en los cuales cada bit se combina con otro bit y con un posible acarreo de entrada. El resultado da una salida de suma. Para la resta se opera utilizando lógica combinacional y circuitos integrados que posibilitan la representación de la operación entre los bits de entrada.

Unidad Lógica

La unidad lógica se encarga de hacer operaciones booleanas con los bits de entrada: AND, OR, NAND y XNOR. Cada una de estas operaciones compara las entradas A y B bit a bit. Si el AND solo da un 1 cuando los dos valores son 1, el OR da 1 si al menos uno de los valores es 1, el NAND es lo contrario del AND, y el XNOR da 1 si los dos valores son iguales.

Unidad Comparativa

La unidad de comparación se usa para ver si dos valores binarios son iguales, o si uno es menor que el otro. El sistema puede mostrar símbolos en los displays utilizando los segmentos correspondientes del display de siete segmentos.

Este módulo recibe señales binarias que llegan desde las entradas. Después, usando compuertas lógicas, evalúa estas señales para activar una salida según el resultado de una comparación. Si el circuito se da cuenta de que el valor de A es menor que el de B, se activa una señal que indica esa condición.

# Material Utilizado

| **Material**                                 | **Contidad** |
| -------------------------------------------- | ------------ |
| 74LS157                                      | 10           |
| 74LS93                                       | 15           |
| Resistencia de 10k 1/4W                      | 16           |
| Resistencia de 330 Ohm 1/4W                  | 14           |
| Resistencia de 220 Ohm 1/4W                  | 16           |
| 74LS08 AND                                   | 6            |
| 74LS47                                       | 2            |
| Protoboard                                   | 10           |
| Dip Switch de 4 posiciones                   | 10           |
| Compuertas AND                               | 8            |
| Compuertas OR                                | 3            |
| Compuertas NOT                               | 3            |
| 74LS86                                       | 1            |
| 74LS83                                       | 7            |
| 74LS47                                       | 2            |
| Display de 7 segmentos de ánodo común        | 2            |
| Alambre para protoboard 22 AWG (Color rojo)  | 3mts         |
| Alambre para protoboard 22 AWG (Color negro) | 3mts         |
| Resistencias de 1k                           | 30           |

# Presupuesto

|     |     |     |     |
| --- | --- | --- | --- |
| **Presupuesto Practica #1 Grupo 9** |     |     |     |
| **Cantidad** | **Producto** | **Precio Unitario** | **Costo Total** |
| 10  | 74LS157 | Q9.00 | Q90.00 |
| 15  | 74LS93 | Q10.80 | Q162.00 |
| 16  | Resistencia de 10k 1/4W | Q0.50 | Q8.00 |
| 14  | Resistencia de 330 Ohm 1/4W | Q0.50 | Q7.00 |
| 16  | Resistencia de 220 Ohm 1/4W | Q0.50 | Q8.00 |
| 6   | 74LS08 AND | Q7.00 | Q42.00 |
| 2   | 74LS47 | Q12.00 | Q24.00 |
| 10  | Protoboard | Q45.00 | Q450.00 |
| 10  | Dip Switch de 4 posiciones | Q4.00 | Q40.00 |
| 8   | Compuertas And | Q7.00 | Q56.00 |
| 3   | Compuertas Or | Q8.00 | Q24.00 |
| 3   | Compuertas NOT | Q7.00 | Q21.00 |
| 1   | 74LS86 | Q10.00 | Q10.00 |
| 7   | 74LS83 | Q12.00 | Q84.00 |
| 2   | 74LS47 | Q10.00 | Q20.00 |
| 2   | Display de 7 segmentos de ánodo común | Q5.00 | Q10.00 |
| 30  | Resistencias de 1k | Q0.50 | Q15.00 |
|     | Total |     | Q1,071.00 |

# Roles de Equipo

| **Fabián Dario Godoy Ruiz**         | Simulación en Proteus, Montaje en Fisico, Compra de Componentes, Documentación, Presupuesto, Mapas Karnaugh y funciones booleanas. |
| ----------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------- |
| **Mynor Gilberto Gutiérrez García** | Simulación en Proteus, Montaje en Fisico, Compra de Componentes, Documentación, Presupuesto, Mapas Karnaugh y funciones booleanas. |
| **José Humberto Melchor Pérez**     | Simulación en Proteus, Montaje en Fisico, Compra de Componentes, Documentación, Presupuesto, Mapas Karnaugh y funciones booleanas. |
| **Raúl Antonio Ruiz Sagastume**     | Simulación en Proteus, Montaje en Fisico, Compra de Componentes, Documentación, Presupuesto, Mapas Karnaugh y funciones booleanas. |
| **Clara Isabel Solís González**     | Simulación en Proteus, Montaje en Fisico, Compra de Componentes, Documentación, Presupuesto, Mapas Karnaugh y funciones booleanas. |
| **Daniel José Camposeco Recinos**   | Simulación en Proteus, Montaje en Fisico, Compra de Componentes, Documentación, Presupuesto, Mapas Karnaugh y funciones booleanas. |
| **Dante Alceo Rivera del Cid**      | Simulación en Proteus, Montaje en Fisico, Compra de Componentes, Documentación, Presupuesto, Mapas Karnaugh y funciones booleanas. |

# Conclusiones

- Se realizo la unidad aritmética de forma efectiva las operaciones aritméticas para realizar operaciones básicas como suma, resta, multiplicación y potencia entre binarios. Así mismo se integró una unidad lógica de operaciones AND, OR, NAND Y XNOR.
- Se mostraron los resultados aritméticos y comparativos correctamente en displays, mientras que los resultados logicos se visualizan por medio de leds, garantizando que las unidades aritmética, lógica y comparativa trabajen de manera ordenada y exitosa.
- La simulación en proteus se consólido en un único archivo funcional y el montaje físico cumplió los requerimientos de ejecutar las operaciones tanto aritméticas, lógicas y comparativa.

# Anexos

<https://github.com/danTeri04/ORGA_1S2026_G9/tree/eae2e09181408d39c834794ad87fb2f30f371bf6/practica>

