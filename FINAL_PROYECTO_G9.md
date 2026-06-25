# SMARTHOME GT: SISTEMA DE CONTROL INTELIGENTE

**Universidad de San Carlos de Guatemala**  
Carreras de Ingeniería — Escuela de Ciencias y Sistemas  
Área: Ciencias de la Computación  
**Catedrático:** Ing. Carlos Lozano

**Grupo No. 9** | Guatemala, 25 de junio de 2026

| Integrante | Carné |
|---|---|
| Fabián Dario Godoy Ruiz | 202248928 |
| Mynor Gilberto Gutiérrez García | 202246527 |
| José Humberto Melchor Pérez | 202145925 |
| Raúl Antonio Ruiz Sagastume | 201941152 |
| Clara Isabel Solís González | 202146478 |
| Daniel José Camposeco Recinos | 201941081 |
| Dante Alceo Rivera del Cid | 202246956 |

---

## Índice

1. [Introducción](#1-introducción)
2. [Descripción del Problema](#2-descripción-del-problema)
3. [Lógica del Sistema](#3-lógica-del-sistema)
4. [Funciones Booleanas y Diagramas de Estado](#4-funciones-booleanas-y-diagramas-de-estado)
5. [Diagrama del Circuito](#5-diagrama-del-circuito)
6. [Equipo y Presupuesto](#6-equipo-y-presupuesto)
7. [Conclusiones y Recomendaciones](#7-conclusiones-y-recomendaciones)
8. [Configuración Bluetooth](#8-configuración-bluetooth)
9. [Manual del Usuario](#9-manual-del-usuario)
10. [Manual Técnico](#10-manual-técnico)
11. [Anexos](#11-anexos)

---

## 1. Introducción

En los hogares convencionales, el control de iluminación y dispositivos eléctricos se realiza de forma manual e independiente, limitando la eficiencia energética y la comodidad. El sistema **Smart Home GT** soluciona esto mediante una maqueta funcional que integra control centralizado de luces, ventilación y puertas desde una interfaz remota, usando un microcontrolador Arduino, memoria EEPROM, comunicación Bluetooth y dispositivos como LEDs, motores y pantalla LCD. El proyecto permite aplicar de forma práctica conceptos de electrónica digital, programación de microcontroladores y sistemas embebidos.

### Objetivo General

Diseñar e implementar una maqueta de casa inteligente capaz de controlar luces y dispositivos mediante comandos locales e inalámbricos, con escenas luminosas almacenadas en EEPROM y configurables desde una PC mediante un archivo `.org`.

### Objetivos Específicos

1. Almacenar escenas luminosas en la EEPROM del Arduino para que persistan tras reinicios sin intervención manual.
2. Cargar y procesar escenas desde un archivo `.org` enviado por PC, validando su sintaxis y actualizando los dispositivos correspondientes.
3. Integrar Bluetooth para control remoto desde móvil, con retroalimentación en pantalla LCD y LEDs.
4. Controlar individualmente la iluminación de cada ambiente (sala, comedor, cocina, baño, habitación) y activar escenas completas simultáneamente.
5. Sincronizar LEDs, pantalla LCD y respuestas inalámbricas para reflejar el estado del sistema en tiempo real.
6. Documentar el proyecto con diagramas, código comentado y tablas de direcciones EEPROM.

---

## 2. Descripción del Problema

### Problemática

En las viviendas tradicionales, el control de iluminación y sistemas eléctricos presenta limitaciones significativas:

- **Falta de centralización:** Los dispositivos se controlan de forma independiente e aislada, requiriendo múltiples interacciones manuales.
- **Baja eficiencia energética:** No existe mecanismo para coordinar el consumo de energía o crear escenas optimizadas.
- **Limitada personalización:** La adaptación del ambiente requiere ajustes manuales repetitivos.
- **Ausencia de automatización:** No hay integración entre dispositivos ni secuencias automáticas programables.

### Solución Propuesta

Se desarrolló un sistema de automatización residencial basado en:

- **Control centralizado:** Un Arduino como unidad central gestiona todos los dispositivos.
- **Almacenamiento en EEPROM:** Configuración persistente de hasta 4 escenas predefinidas (Fiesta, Relajado, Noche, Encender Todo) más 2 modos personalizados.
- **Interfaz de configuración (`.org`):** Archivo de texto que permite definir estados de luces y ventilador desde una PC.
- **Comunicación remota:** Módulo Bluetooth HC-06 para control desde dispositivo móvil.
- **Retroalimentación en tiempo real:** LCD 16x2 e indicadores LED (azul, verde, rojo) para validar operaciones.

### Alcance del Proyecto

El sistema controla:

- 5 zonas de iluminación (5–16 LEDs según complejidad)
- 1 ventilador (motor DC)
- 1 puerta automática (servomotor)
- Comunicación USB y Bluetooth
- Pantalla LCD I2C para visualización de estado
- 3 LEDs indicadores para retroalimentación

---

## 3. Lógica del Sistema

El sistema opera como una **máquina de estados finita** controlada por un microcontrolador Arduino. Las entradas provienen de dos fuentes: el puerto serial USB (carga del archivo `.org` desde PC) y el módulo Bluetooth HC-06 (comandos remotos desde móvil). Las salidas son las señales digitales hacia LEDs por ambiente, motor DC (ventilador), servomotor (puerta) y pantalla LCD.

El sistema distingue dos fases de operación:

**Fase de configuración:** el Arduino recibe el archivo `.org` línea por línea. Valida su sintaxis, extrae los estados de cada ambiente y ventilador, y los escribe en direcciones específicas de la EEPROM. Durante esta fase se bloquean los comandos Bluetooth. Al finalizar correctamente, el LED verde parpadea 3 veces; si hay error, el LED rojo se enciende y el LCD muestra el mensaje de error.

**Fase de operación:** el sistema escucha comandos Bluetooth. Al recibir un comando válido, lee el estado correspondiente desde EEPROM y activa las salidas digitales según la configuración almacenada. El LCD se actualiza inmediatamente y los LEDs de estado reflejan el resultado.

---

## 4. Funciones Booleanas y Diagramas de Estado

### 4.1. Funciones Booleanas

**Variables de entrada:**

| Variable | Descripción |
|---|---|
| `CMD` | Comando recibido (Bluetooth o Serial) |
| `VAL` | Archivo `.org` válido (sin errores de sintaxis) |
| `CONF` | Proceso de configuración activo |
| `BT` | Fuente: Bluetooth (1) o Serial (0) |

**Variables de salida:**

| Variable | Descripción |
|---|---|
| `LED_AMB[i]` | Estado del LED del ambiente i (sala, comedor, cocina, baño, habitación) |
| `FAN` | Estado del ventilador |
| `L1` (azul) | LED indicador — sistema activo |
| `L2` (verde) | LED indicador — éxito de configuración |
| `L3` (rojo) | LED indicador — error |

**Expresiones booleanas:**

```
LED_AMB[i] = (CMD_VALIDO · EEPROM_STATE[i]) + (encender_todo)
LED_AMB[i] = 0   si  apagar_todo = 1

FAN = modo_fiesta + encender_todo
FAN = 0   si  modo_relajado + modo_noche + apagar_todo = 1

L1 (Sistema activo)   = NOT(CONF) · NOT(ERROR)
L2 (Éxito config)     = CONF · VAL · FIN_CARGA
L3 (Error)            = CONF · NOT(VAL) + EEPROM_FAIL

CMD_BT_HABILITADO   = NOT(CONF)
ESCRITURA_EEPROM    = CONF · VAL · BT̄   (solo Serial, no Bluetooth)
```

### 4.2. Diagramas de Estado

```
                          ●
                          │
                       [Inicio]
                          │
          Sistema encendido / Puerta=CERRADA / L1=ON
                          │
                       [Espera]
                    ┌─────┴─────────┐
            Serial recibe .org   Bluetooth recibe CMD
                    │                    │
             [Configuración]       [ValidarCMD]
             ┌─────┴─────┐        ┌──────┴──────┐
          VAL=1        VAL=0   CMD válido   CMD inválido
             │              │       │              │
      [GuardarEEPROM]  [ErrorConfig] [AplicarModo] [ErrorCMD]
             │                       │
      L2 parpadea 3x           Leer EEPROM
      LCD="Configuracion       Activar salidas
           guardada"           L2 parpadea
             └───────────────────────┘
                          │
                      [ModoActivo]
                          │
                       [Espera]  ←── Reinicio del sistema
```

---

## 5. Diagrama del Circuito

> *(Ver diagrama esquemático en Proteus adjunto al proyecto)*

El circuito integra los siguientes bloques principales:

- Arduino UNO como unidad central
- LEDs de ambiente (D1–D11) con resistencias limitadoras
- LEDs indicadores azul, verde y rojo (D12–D14)
- Módulo Bluetooth HC-05/HC-06
- Pantalla LCD 16x2 con módulo I2C (PCF8574)
- Motor DC con transistor NPN como driver
- Servomotor para control de puerta

---

## 6. Equipo y Presupuesto

### 6.1 Equipo Utilizado

| Componente | Cantidad | Precio unitario | Total |
|---|---|---|---|
| LED | 5 | Q 1.00 | Q 5.00 |
| Resistencia 600 Ω | 1 | Q 0.50 | Q 0.50 |
| Resistencia 330 Ω | 6 | Q 0.50 | Q 0.50 |
| Resistencia 1 kΩ | 2 | Q 0.50 | Q 1.00 |
| Resistencia 2 kΩ | 2 | Q 0.50 | Q 1.00 |
| Motor DC | 1 | Q 12.00 | Q 12.00 |
| Servomotor | 1 | Q 30.00 | Q 30.00 |
| Módulo Bluetooth HC-05 | 1 | Q 80.00 | Q 80.00 |
| Pantalla LCD 20×4 | 1 | Q 80.00 | Q 80.00 |
| Módulo I2C | 1 | Q 20.00 | Q 20.00 |
| Arduino UNO | 1 | Q 75.00 | Q 75.00 |
| Diodo 1N4007 | 1 | Q 1.00 | Q 1.00 |
| Transistor NPN | 1 | Q 1.50 | Q 1.50 |
| Protoboard | 2 | Q 40.00 | Q 80.00 |
| Cables UTP | 3 m | — | Q 25.00 |
| Casa de juguete | 1 | Q 5.00 | Q 5.00 |
| Caja de cartón | 1 | Q 50.00 | Q 50.00 |
| **Total** | | | **Q 467.50** |

---

## 7. Conclusiones y Recomendaciones

### 7.1. Conclusiones

1. **Persistencia de escenas en EEPROM:** Se implementó exitosamente un sistema de almacenamiento en EEPROM que garantiza la persistencia de hasta 4 escenas luminosas predefinidas tras reinicios del sistema, permitiendo recuperación automática de configuraciones sin intervención manual.

2. **Validación exitosa de interfaz `.org`:** La interfaz de configuración procesa correctamente archivos `.org` desde PC mediante puerto serial, validando sintaxis completa y actualizando estados de ambientes y ventilador, generando mensajes de error claros en LCD cuando se detectan inconsistencias.

3. **Control remoto Bluetooth funcional:** El módulo Bluetooth HC-06 integrado permite recibir y procesar comandos desde dispositivos móviles de forma confiable, activando modos predefinidos y personalizados con respuesta inmediata y comunicación estable.

4. **Control individual y coordinado de iluminación:** Se logró implementar una matriz de iluminación que controla independientemente 5 zonas de ambiente (sala, comedor, cocina, baño, habitación) con capacidad simultánea de activar escenas coordinadas mediante 4 modos predefinidos más 2 personalizados.

5. **Sincronización en tiempo real:** Los sistemas de retroalimentación (LEDs indicadores azul/verde/rojo, pantalla LCD, respuestas Bluetooth) funcionan de forma sincronizada y coordinada, proporcionando información clara y verificable del estado del sistema tras cada operación.

6. **Documentación técnica completa:** Se generó documentación integral que incluye diagramas esquemáticos en Proteus, código fuente comentado, tablas de direcciones EEPROM, ejemplos de archivos `.org`, presupuesto detallado y análisis técnico profesional.

### 7.2. Recomendaciones

**Para la Implementación:**

1. **Validación temprana de hardware:** Antes de escribir el código completo, probar cada módulo individualmente (LEDs, motor DC, servo, LCD, Bluetooth) con sketches simples de prueba.
2. **Interfaz Bluetooth clara:** Documentar todos los comandos soportados. Usar una app como "Serial Bluetooth Terminal" para pruebas y considerar agregar comando `estado` para consultar configuración actual.

**Para la Maqueta Física:**

1. **Construcción ordenada:** Mantener circuitos limpios y bien etiquetados. Usar protoboards para desarrollo y transferir a PCB o circuito soldado solo si es posible.
2. **Representación realista:** Diseñar una maqueta clara que represente los 5 ambientes de forma visiblemente diferenciada. Etiquetar cada LED por ambiente y modo.
3. **Protección de componentes:** Para motores y servomotores, usar transistores o MOSFETs como drivers. Verificar consumo de corriente total y dimensionar fuente de alimentación adecuadamente.

**Para Documentación:**

1. **Diagramas claros:** Generar esquemas en Proteus o herramienta similar. Incluir pinout de Arduino, conexiones de cada componente y tabla de pines utilizados.
2. **Código comentado:** Documentar todas las funciones, variables globales y secciones lógicas principales. Incluir descripción del flujo de ejecución y cómo se integran los módulos.
3. **Archivo `.org` de prueba:** Proporcionar ejemplos funcionales de archivos `.org` con sintaxis correcta e incorrecta para facilitar comprensión y debugging.
4. **Presupuesto detallado:** Listar todos los componentes con cantidad, costo unitario y total. Incluir alternativas de bajo costo si es relevante.

**Para Consideraciones Operacionales:**

1. **Manejo de errores:** Implementar estados de error claros: LED rojo encendido/parpadeante, mensaje en LCD, y posibilidad de reintentar carga de archivo.
2. **Pruebas exhaustivas:** Realizar ciclos completos de: cargar configuración → activar modos → validar estado → cambiar modos → verificar persistencia tras reinicio.

---

## 8. Configuración Bluetooth

### Módulo HC-05

| Parámetro | Valor |
|---|---|
| Tecnología | Bluetooth 2.0 + EDR |
| Comunicación | Serial UART |
| Voltaje de alimentación | 3.6 V – 6 V |
| Alcance | ~10 metros |
| Velocidad configurada | 9600 bps |
| Modo | Esclavo (Slave) |

### Conexiones

| HC-05 | Arduino UNO |
|---|---|
| VCC | 5V |
| GND | GND |
| TXD | RX (Pin 0) |
| RXD | TX (Pin 1) |

### Proceso de Emparejamiento

1. Energizar el módulo HC-05.
2. Activar Bluetooth en el teléfono móvil.
3. Buscar el dispositivo "HC-05".
4. Emparejar usando la contraseña predeterminada `1234`.
5. Una vez conectado, la app móvil puede enviar comandos al Arduino mediante comunicación serial.

### Comandos Implementados

| Comando | Acción |
|---|---|
| `F` | Modo Fiesta |
| `R` | Modo Relajado |
| `N` | Modo Noche |
| `E` | Encender todas las luces |
| `A` | Apagar todas las luces |
| `B1` | Estado personalizado 1 |
| `B2` | Estado personalizado 2 |
| `P` | Control de puerta |

---

## 9. Manual del Usuario

### 1. Inicio Rápido

- Conectar la fuente de alimentación al Arduino.
- El **LED azul** se encenderá indicando que el sistema está listo.
- La **LCD** mostrará el modo activo y estado del ventilador.
- La puerta se cerrará automáticamente al encender.

### 2. Cargar Configuración (`.org`)

Desde una PC usando Arduino IDE, PuTTY o Python:

1. Abrir el puerto serial del Arduino (`COM3`, `COM4`, `/dev/ttyUSB0`, etc.)
2. Cargar archivo `.org` línea por línea mediante puerto USB.
3. **LED verde parpadea 3 veces** = Configuración guardada exitosamente.
4. **LED rojo encendido** = Error en sintaxis (revisar archivo `.org`).

### 3. Control vía Bluetooth

Usar app "Serial Bluetooth Terminal" o similar.

| Comando | Efecto |
|---|---|
| `modo_fiesta` | Luces alternándose, ventilador ON |
| `modo_relajado` | Todas las luces OFF, ventilador OFF |
| `modo_noche` | Luces OFF, ventilador OFF |
| `encender_todo` | Todas las luces ON, ventilador ON |
| `apagar_todo` | Todas las luces OFF, ventilador OFF |
| `modo_custom_1` | Activa modo personalizado 1 |
| `modo_custom_2` | Activa modo personalizado 2 |

### 4. Indicadores Visuales

| LED | Estado | Significado |
|---|---|---|
| Azul | Encendido | Sistema listo para recibir comandos |
| Verde | Parpadea | Configuración guardada correctamente |
| Rojo | Encendido/parpadeante | Error en archivo `.org` o EEPROM |

### 5. Pantalla LCD

- **Línea 1:** Modo activo (ej. `Modo: FIESTA.`)
- **Línea 2:** Estado del ventilador y LEDs
- Actualización inmediata tras cada comando.

### 6. Control de Puerta (Servomotor)

- Presionar botón físico para abrir/cerrar puerta.
- Se cierra automáticamente al encender el Arduino.
- No requiere comandos Bluetooth adicionales.

### 7. Solución de Problemas

| Problema | Solución |
|---|---|
| LED rojo al cargar `.org` | Verificar sintaxis: `sala:ON` no `sala:on` |
| Bluetooth no responde | Verificar que HC-06 está conectado. No cargar código mientras HC-06 está en RX/TX |
| LCD en blanco | Ajustar potenciómetro de contraste. Reiniciar Arduino |
| Motor DC no gira | Verificar alimentación. Revisar pin del motor en Arduino |

### 8. Especificaciones Técnicas Básicas

| Parámetro | Detalle |
|---|---|
| Microcontrolador | Arduino Uno/Nano/Compatible |
| Memoria | EEPROM interna — 4 modos predefinidos + 2 personalizados |
| Comunicación | Serial USB + Bluetooth HC-06 (9600 baud) |
| Pantalla | LCD I2C 16×2 |
| Zonas de iluminación | 5 ambientes (5–16 LEDs total) |
| Salidas adicionales | Motor DC + Servomotor |

---

## 10. Manual Técnico

### 1. Componentes Principales

| Componente | Modelo | Función |
|---|---|---|
| Microcontrolador | Arduino Uno/Nano | Unidad central de control |
| Módulo Bluetooth | HC-06 | Comunicación inalámbrica (9600 baud) |
| Pantalla LCD | I2C 16×2 | Visualización de estado (dirección I2C: `0x27`) |
| Motor DC | 3–5V | Ventilador (gira en un sentido) |
| Servomotor | SG90 o compatible | Control de puerta (abrir/cerrar) |
| Transistor NPN | 2N2222 | Driver para motor DC |
| LEDs | 5 mm (1/4W) | Iluminación ×5 ambientes + 3 indicadores |

### 2. Tabla de Pines Arduino

| Pin Arduino | Conexión | Tipo |
|---|---|---|
| D2–D6 | LEDs ambientes 1–5 | Digital Output |
| D7 | Motor DC | Digital Output |
| D8 | Servomotor | PWM Output |
| D9–D11 | LEDs indicadores (A, V, R) | Digital Output |
| RX (D0) | HC-06 TX | Serial Input |
| TX (D1) | HC-06 RX | Serial Output |
| A4 (SDA) | LCD I2C SDA | I2C Data |
| A5 (SCL) | LCD I2C SCL | I2C Clock |

### 3. Tabla de Direcciones EEPROM

| Dirección | Modo | Tamaño |
|---|---|---|
| 0 | `modo_fiesta` | 12 bytes |
| 12 | `modo_relajado` | 12 bytes |
| 24 | `modo_noche` | 12 bytes |
| 36 | `modo_personalizado_1` | 12 bytes |
| 48 | `modo_personalizado_2` | 12 bytes |

### 4. Estructura de Datos por Modo (12 bytes en EEPROM)

| Byte(s) | Contenido |
|---|---|
| 0 | Ventilador (0 = OFF, 1 = ON) |
| 1–5 | Estado LEDs (sala, comedor, cocina, baño, habitación) |
| 6–11 | Reservado |

### 5. Formato de Archivo `.org`

```
conf_ini
modo_[nombre]
Ventilador: [ON/OFF]
LED'S: [sala:ON/OFF], [comedor:ON/OFF], [cocina:ON/OFF], [baño:ON/OFF], [habitacion:ON/OFF]
conf_fin
```

### 6. Protocolo de Comunicación

**Puerto Serial (USB):**
- Velocidad: 9600 baud
- Fin de línea: `\r\n` (CRLF)
- Uso: Cargar archivos `.org`

**Bluetooth (HC-06):**
- Velocidad: 9600 baud
- Comandos: `modo_fiesta`, `modo_relajado`, `modo_noche`, `encender_todo`, `apagar_todo`, `estado`, `modo_custom_1`, `modo_custom_2`
- Respuesta: Confirmación vía LCD y serial

### 7. Flujo de Control Principal

- **Setup:** Inicializar pines, EEPROM, LCD, Bluetooth. Cerrar puerta.
- **Loop:** Leer serial USB y Bluetooth (no bloqueante). Procesar comandos.
- **Actualizar salidas:** LEDs, motor, LCD según modo activo.
- Usar `millis()` para gestión de tiempos (parpadeos, secuencias).

### 8. Requisitos de Compilación

- Arduino IDE 1.8.x o superior
- Librerías: `LiquidCrystal_I2C.h`, `EEPROM.h`, `SoftwareSerial.h` (si es necesaria)
- No usar `delay()` excesivos — preferir `millis()` para loops no bloqueantes.

### 9. Validación de Errores

- **Sintaxis `.org`:** Verificar claves requeridas (`Ventilador`, `LED'S` en ambientes).
- **Rango de datos:** Validar que valores sean `ON`/`OFF` únicamente.
- **Escritura EEPROM:** Comprobar integridad antes de guardar.
- **Comandos inválidos:** Ignorar y responder con error.

### 10. Testing y Debugging

- Usar Monitor Serial (Arduino IDE) para visualizar entrada/salida.
- Verificar cada pin con multímetro.
- Probar módulos aisladamente antes de integración.
- Ciclo completo: Cargar config → Activar modos → Verificar persistencia.

---

## 11. Anexos

> *(Fotografías del proceso de construcción y prueba del prototipo físico)*
