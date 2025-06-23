# 🎮 **Documentación del Proyecto: BombBot**

---

## 🕹️ **Controles del Juego**

| Acción                  | Tecla(s)                |
|-------------------------|-------------------------|
| **Caminar**             | WASD o Flechas          |
| **Colocar bombas**      | Espacio                 |
| **Encender/Apagar linterna** | F              |
| **Pausa**               | P and ESCAPE            |

---

## 📑 **Tabla de Contenido**

### 1. [👥 Participantes e Información General](#participantes-e-información-general)
*   [1.1 Participantes](#participantes)
*   [1.2 Datos Académicos](#datos-académicos)
*   [1.3 Presentación del Proyecto](#presentación-del-proyecto)

### 2. [📘 Documentación General del Proyecto](#documentación-del-proyecto-bombbot)
*   [2.1 Introducción](#1-introducción)
*   [2.2 Arquitectura General del Software](#2-arquitectura-general-del-software)
    *   [Dominios Lógicos Principales](#dominios-lógicos-principales)
*   [2.3 Sistemas Clave del Juego](#3-sistemas-clave-del-juego)
    *   [2.3.1 Personaje del Jugador (ABombBotCharacter)](#31-personaje-del-jugador-–-abombbotcharacter)
    *   [2.3.2 Objetos del Mundo](#32-objetos-del-mundo)
        *   [Bloques](#321-bloques)
        *   [Bombas (ABomba)](#322-bombas-–-abomba)
        *   [Explosiones (AExplosion)](#323-explosiones-–-aexplosion)
        *   [Power-Ups (APowerUp y Derivados)](#324-power-ups-–-apowerup-y-derivados)
    *   [2.3.3 Sistema de Enemigos](#33-sistema-de-enemigos)
    *   [2.3.4 Interfaz de Usuario (UI/HUD)](#34-interfaz-de-usuario-uihud)
    *   [2.3.5 Gestión del Juego (UBombBotGameInstance)](#35-gestión-del-juego-–-ubombbotgameinstance)

### 3. [💻 Documentación Técnica del Proyecto: Patrones de Diseño](#documentación-técnica-del-proyecto-bombbot)
*   [3.1 Introducción a los Patrones](#introducción-a-los-patrones)
*   [3.2 Patrones de Diseño Aplicados](#patrones-de-diseño-aplicados)
    *   [3.2.1 Builder Pattern (Constructor)](#1-builder-pattern-–-constructor)
    *   [3.2.2 Abstract Factory Pattern (Fábrica Abstracta)](#2-abstract-factory-pattern-–-fábrica-abstracta)
    *   [3.2.3 Factory Method Pattern (Método de Fábrica)](#3-factory-method-pattern-–-método-de-fábrica)
        *   [Sistema de Bloques](#a-sistema-de-bloques)
        *   [Sistema de Power-Ups](#b-sistema-de-power-ups)
    *   [3.2.4 Facade Pattern (Patrón Fachada)](#4-facade-pattern-–-patrón-fachada)
*   [3.3 Gameplay Grabado del Juego](#gameplay-grabado)
*   [3.4 Cómo Instalar el Juego](#cómo-instalar-el-juego)
    *   [Instrucciones](#instrucciones)
*   [3.5 Conclusión General](#conclusión-general)

---

## 👥 **Participantes**

**Trabajo realizado por:**
- **Arancibia Estrada Álvaro David** — `Ing. Ciencias de la Computación`
- **Mollinedo Siles Renzo Sebastián** — `Ing. Ciencias de la Computación`
- **Quispe Ticona Josias Asael** — `Ing. Ciencias de la Computación`, `Ing. Tecnologías de la Información y Seguridad`
- **Magne Ordoñez Pedro Jhoel Antonio** — `Ing. Ciencias de la Computación`
- **Cornejo Moscoso Gabriel Orlando** — `Ing. Ciencias de la Computación`

---

## 🎓 **Datos Académicos**

- **Materia:** SIS 457 - *Programación Avanzada*  
- **Docente:** Ing. Carlos Walter Pacheco Lora  
- **Facultad:** Ciencia y Tecnología  
- **Universidad:** Universidad Mayor, Real y Pontificia San Francisco Xavier de Chuquisaca


---

## 📽️ **Presentación del Proyecto**

[🎬 **Haz clic aquí para ver la presentación del juego en Google Slides**](https://docs.google.com/presentation/d/1gwHen4h_9wBLuj7uPDwHeS0FxZE_c7yZeHTUA4ozb_8/edit?usp=sharing)

---

![Imagen de Portada](https://github.com/user-attachments/assets/e67e43f8-82da-47de-9bc1-c84012331841)

---

# 📘 **Documentación del Proyecto: BombBot**

---

## 🧩 **1. Introducción**

**BombBot** es un videojuego estratégico inspirado en el clásico *Bomberman*, desarrollado en **Unreal Engine** utilizando **C++**.  
El objetivo principal de este proyecto académico es ofrecer una experiencia de juego que combine **acción táctica**, **colocación precisa de bombas** y **exploración de niveles generados proceduralmente**.

Esta documentación proporciona una visión integral de la arquitectura del software, los sistemas principales del juego y los patrones de diseño aplicados para asegurar un desarrollo **modular**, **extensible** y **mantenible**.

---

## 🏗️ **2. Arquitectura General del Software**

La arquitectura de **BombBot** sigue un enfoque **modular y orientado a componentes**, común en proyectos desarrollados con **Unreal Engine**. Se ha priorizado la **separación de responsabilidades** y el uso de **clases base abstractas** junto con **patrones de diseño** para gestionar la complejidad inherente a un juego con generación procedural.

### 🔍 **Dominios Lógicos Principales**

- 🎮 **Personaje del Jugador**  
  Control del movimiento, salud, interacción y la interfaz de usuario (UI).

- 🧱 **Objetos del Mundo**  
  Incluye bloques, bombas y power-ups, cada uno con comportamientos específicos.

- 🤖 **Sistema de Enemigos**  
  Inteligencia artificial básica, patrullaje y aparición dinámica.

- 🗺️ **Generación de Niveles**  
  Sistema robusto que permite construir mapas dinámicos de forma procedural.

- 🎯 **Gestión del Juego**  
  Control del estado de la partida, sistema de puntuación y visualización de la UI global.

---


---

## 🎮 **3. Sistemas Clave del Juego**

![Imagen Visual del Sistema](https://github.com/user-attachments/assets/06b64b94-f013-4839-9d3c-8d03e157b6c0)

---

### 🧍‍♂️ **3.1. Personaje del Jugador – `ABombBotCharacter`**

Clase principal que representa al jugador en el entorno de juego.

**🔧 Funcionalidades Principales:**

- 🧭 **Movimiento y Cámara:**  
  Utiliza `USpringArmComponent` y `UCameraComponent` para el seguimiento dinámico del jugador, junto con `UCharacterMovementComponent`.

- 🎮 **Entrada (Input):**  
  Integración con el sistema `Enhanced Input` para accionar movimientos, saltos, colocación de bombas y pausa.

- ❤️ **Gestión de Vidas y Respawn:**  
  Control de durabilidad, invulnerabilidad temporal, y lógica de reaparecimiento (`RespawnDelay`).

- 💣 **Colocación de Bombas:**  
  Instanciación de objetos `ABomba` con control de distancia y cantidad máxima activa.

- ⚡ **Interacción con Power-Ups:**  
  Activación de efectos como velocidad, curación o inmortalidad mediante temporizadores.

- 🖥️ **Interfaz de Usuario (UI):**  
  Control y actualización de widgets como `UWUI_Principal`, Game Over y Pausa (`UUserWidget`).

- 🏆 **Puntuación:**  
  Registro y actualización de puntos a través de `UBombBotGameInstance`.

---

### 🌍 **3.2. Objetos del Mundo**

#### 🧱 **3.2.1. Bloques**

Tipos de bloques y su comportamiento estructural:

- `ABloque` — Bloque básico no destructible.
- `ABloqueGeneral` — Clase base de bloques destructibles.
- `ABloqueDestructibleBase` — Implementación intermedia que contiene subfragmentos.
- `ASubBloqueBase` — Fragmentos individuales generados tras una destrucción.
- **Bloques Concretos:**  
  - `ABloque_Madera`, `ABloque_Piedra`, `ABloque_Pasto`, `ABloque_Tierra`.

#### 💣 **3.2.2. Bombas – `ABomba`**

Componentes y lógica asociados a las bombas:

- ⏱️ **Temporizador de Explosión**
- 🔊 **Efectos Visuales y Sonoros:**  
  Animaciones, partículas (`UParticleSystem`) y audio (`USoundBase`).
- 🔥 **Rango de Explosión:**  
  Creación de múltiples instancias `AExplosion` para simular el área de daño.
- 🧿 **Mecanismo de Bloqueo:**  
  Uso de `ALockSphere` para control de proximidad del jugador.
- 🧮 **Gestión de Bombas Colocadas**

#### 💥 **3.2.3. Explosiones – `AExplosion`**

- 📈 **Propagación:**  
  Movimiento en múltiples direcciones.
- 🧱 **Detección de Impacto:**  
  Interacción con entorno y enemigos.
- 🌠 **Efectos Visuales**
- 🎯 **Puntuación y Daño**

#### 🧪 **3.2.4. Power-Ups – `APowerUp` y Derivados**

Objetos recolectables con efectos especiales:

- `APowerUp` – Clase abstracta base.  
- `APowerUp_Inmortalidad` – Invulnerabilidad temporal.  
- `APowerUp_Velocidad` – Aumento de velocidad.  
- `APoweUp_Curacion` – Restauración de vidas.

---

### 🤖 **3.3. Sistema de Enemigos**

Inteligencia artificial y comportamiento de enemigos:

- `AEnemigo` – Clase base con lógica de patrullaje y detección.  
- `AEnemigo_Bomb` – Enemigo kamikaze con explosión.  
- `AEnemigo_Comun` – Contacto físico con daño + drop aleatorio de power-up.  
- `AGenerador_Enemigos` – Spawn periódico configurable.

---

### 🧩 **3.4. Interfaz de Usuario (UI/HUD)**

- `UWUI_Principal` – Muestra vidas y puntuación.  
- **Widgets de Estado:**  
  Activación al pausar o morir (`UUserWidget`).

---

### 🧠 **3.5. Gestión del Juego – `UBombBotGameInstance`**

Clase persistente para el estado global:

- 🎯 **Puntuación Global:**  
  Registro centralizado del score, accesible desde cualquier parte del juego.

---



---

# 🛠️ Documentación Técnica del Proyecto BombBot

Este apartado detalla la arquitectura del videojuego **BombBot**, con un enfoque especial en el uso de **patrones de diseño de software** aplicados a la generación procedural de niveles, gestión de objetos y lógica central del juego.

---

## 📌 Introducción

El proyecto **BombBot** adopta múltiples **patrones de diseño** para lograr un sistema:

- 📦 **Modular**
- 🧩 **Flexible**
- 🔧 **Fácil de mantener y extender**

Esto permite incorporar nuevos tipos de mundos, enemigos y power-ups sin reescribir el núcleo del código, apoyándose en principios SOLID y reutilización de componentes.

---

## 📐 Patrones de Diseño Aplicados

Los siguientes patrones están implementados de forma destacada:

- 🧱 **Builder Pattern (Constructor)**
- 🏭 **Abstract Factory Pattern (Fábrica Abstracta)**
- ⚙️ **Factory Method Pattern (Método de Fábrica)**
- 🎛️ **Facade Pattern (Fachada)**

---

## 🧱 1. Builder Pattern – *Constructor*

### 📖 Definición

El **Builder Pattern** separa la construcción de un objeto complejo de su representación. Un **Director** controla el proceso de construcción, mientras que diferentes **Builders** definen las implementaciones específicas.

---

### 🎯 Aplicación en BombBot: Generación de Niveles

Cada mundo (`World1`, `World2`, `World3`) tiene su propio builder que sigue una estructura común orquestada por un director (`ALevels_Director`).  
Esto permite reutilizar lógica general y adaptar la construcción a diferentes entornos con mínima duplicación.

---

### 🧩 Componentes Clave

#### 🎬 Director → `ALevels_Director`

- **Rol:** Controla el proceso de construcción.
- **Métodos:**  
  - `CreateLevel1()`, `CreateLevel2()`, etc.
  - Ejecutan pasos de construcción definidos por el builder activo.
- **Archivo:** `Levels_Director.h / .cpp`

---

#### 🧱 Abstract Builder → `IILevels_Builder`

- **Rol:** Interfaz para definir los métodos de construcción del mapa, enemigos y objetos.
- **Archivo:** `ILevels_Builder.h`

---

#### 🧰 Concrete Builders

- `AWorld1_Builder`  
- `AWorld2_Builder`  
- `AWorld3_Builder`

**Rol:**  
Implementan la lógica específica de construcción de cada mundo. Utilizan una **Factory** propia para delegar la creación de objetos concretos (bloques, enemigos, power-ups).

---

#### 🗺️ Producto Final → El Nivel

- Es el conjunto completo de bloques, enemigos y objetos generados.
- Se considera el "objeto complejo" que resulta del proceso de construcción.

---

### 📊 Diagrama UML – Builder Pattern

![Diagrama UML - Builder Pattern](https://github.com/user-attachments/assets/0aee3dad-a3a9-4833-ae48-a05fbd7b481f)

---

### 🧠 Flujo de Construcción (Explicación)

1. Se instancia el `ALevels_Director`.
2. Se le asigna un `Concrete Builder` (por ejemplo, `AWorld1_Builder`).
3. El director llama a métodos como:
   - `BuildMap()`
   - `BuildEnemy()`
   - `BuildPowerUps()`
4. El builder ejecuta estas funciones con lógica personalizada.
5. Cada builder invoca a su **Factory** correspondiente (`AWorldX_Factory`) para crear los objetos reales del mundo.

---

### ✅ Ventajas

- 🔁 **Reutilización de lógica de construcción**
- 🛠️ **Facilidad para crear nuevos tipos de niveles**
- 🔄 **Cambio dinámico del entorno sin modificar el código base**
- 🎯 **Separación clara entre la lógica de construcción y los objetos concretos**

---

---

## 🏭 2. Abstract Factory Pattern – *Fábrica Abstracta*

### 📖 Definición

El **Abstract Factory Pattern** proporciona una interfaz para crear **familias de objetos relacionados** sin especificar sus clases concretas.  
Este patrón permite al cliente generar componentes que mantienen **consistencia temática y funcional**.

---

### 🌍 Aplicación en BombBot: Creación de Objetos del Mundo

En *BombBot*, se utiliza este patrón para generar todos los elementos pertenecientes a un mundo específico:  
🏞️ **bloques**, 🧨 **enemigos**, ⚡ **power-ups**, y 🌀 **portales** se producen a través de una misma fábrica, garantizando coherencia estética y funcional en cada nivel.

---

### 🧩 Componentes Clave

#### 🧪 Abstract Factory → `IIWorld_Factory`

- **Rol:**  
  Interfaz para construir componentes clave de un mundo:
  - Mapa
  - Terreno
  - Enemigos
  - Power-Ups
  - Portales
- **Archivo:** `IWorld_Factory.h`

---

#### 🏗️ Concrete Factories

- `AWorld1_Factory`  
- `AWorld2_Factory`  
- `AWorld3_Factory`

**Responsabilidad:**  
Implementan la lógica para construir objetos específicos según el mundo.  
Por ejemplo, `AWorld1_Factory` construye enemigos y bloques con las propiedades visuales y de comportamiento del Mundo 1.

**Ubicación:** Archivos `.h` y `.cpp` por fábrica (`World1_Factory.h`, etc.).

---

#### 📦 Abstract Products

Interfaces o clases base que definen las características comunes de los objetos que se generan:

- `ABloqueGeneral`  
- `AEnemigo`  
- `APowerUp`

**Archivo:** Archivos base como `BloqueGeneral.h`, `Enemigo.h`, `PowerUp.h`

---

#### 🧱 Concrete Products

Instancias concretas creadas por cada fábrica:

- `ABloque_Madera`, `ABloque_Piedra`, `ABloque_Pasto`
- `AEnemigo_Comun`
- `APowerUp_Inmortalidad`, `APowerUp_Velocidad`, `APowerUp_Curacion`

**Archivo:** Por ejemplo, `Bloque_Madera.h`, `Enemigo_Comun.h`, `PowerUp_Inmortalidad.h`

---

### 📊 Diagrama UML – Abstract Factory Pattern

![Diagrama UML - Abstract Factory](https://github.com/user-attachments/assets/54bf9a22-c22b-4f4f-aa03-cb43a688ccaf)

---

### ⚙️ Flujo de Uso en el Proyecto

1. Cada `Concrete Builder` (`AWorld1_Builder`, etc.) **recibe una instancia de fábrica** (`IIWorld_Factory`) para construir sus componentes.
2. Llama a métodos como:
   - `CrearBloque()`
   - `CrearEnemigo()`
   - `CrearPowerUp()`
3. La fábrica devuelve las implementaciones específicas según el mundo.
4. Así, el constructor puede armar el mundo sin preocuparse por los detalles de implementación de cada objeto.

---

### 🔄 Expansión: Agregar un Nuevo Mundo

Para añadir, por ejemplo, un **Mundo 4**:

✅ Solo se necesita crear una clase `AWorld4_Factory` que herede de `IIWorld_Factory`.  
✅ No se modifica el código del `Director` ni los `Builders` existentes.  
✅ Se conserva la coherencia visual y lógica del nuevo entorno.

---

### 🧬 Relación con otros Patrones

- Las **subfábricas internas** (`AWorld1_FactoryBloques`) implementan el **Factory Method Pattern**.
- La creación de enemigos y power-ups utiliza también `SpawnActor` con clases dinámicas, delegando la variabilidad a nivel de instancia.

---

### ✅ Ventajas

- 🎨 **Estética y funcionalidad coherentes por mundo**
- 📚 **Código extensible y desacoplado**
- 🔄 **Cambios o nuevos mundos sin refactorización masiva**
- 💡 **Complemento perfecto para el Builder Pattern**

---

---

## 🧪 3. Factory Method Pattern – *Método de Fábrica*

### 📖 Definición

El **Factory Method** define una interfaz para la creación de objetos, pero permite que las subclases decidan qué clase concreta instanciar.  
🔧 Este enfoque permite delegar la lógica de instanciación, favoreciendo la **flexibilidad**, **extensibilidad** y **desacoplamiento**.

---

### 🧱 Aplicación en BombBot: Creación de Bloques y Power-Ups

El patrón se implementa claramente en dos módulos del juego:

1. **Generación de Bloques del Mapa**  
2. **Generación de Power-Ups tras eliminar enemigos**

Ambos sistemas utilizan **parámetros de entrada** para decidir qué tipo específico de objeto generar.

---

## 🔷 A. Sistema de Bloques

### 🧩 Componentes Clave

#### 🏗️ Creator (Concreto): `AWorld1_FactoryBloques`

- **Responsabilidad:**  
  Implementa el método `CrearBloque(TypeBlock)`, que recibe una cadena de texto (`"BloqueMadera"`, `"BloquePiedra"`, etc.) y genera el bloque correspondiente.

---

#### 🧱 Producto Abstracto: `ABloqueGeneral`

- **Rol:**  
  Clase base para todos los bloques.  
  En muchos casos, extiende `ABloqueDestructibleBase`.

---

#### 🧱 Productos Concretos

- `ABloque_Madera`  
- `ABloque_Piedra`  
- `ABloque_Pasto`  
- `ABloque_Tierra`

> Cada clase representa un tipo de bloque con estética y comportamiento propio.

---

### 📊 Diagrama UML – Bloques (Factory Method)

![Diagrama Factory Method - Bloques](https://github.com/user-attachments/assets/bca971bf-f44c-4373-83cb-2e77a4ff5d40)

---

### ⚙️ Flujo de Uso

1. Dentro de `AWorld1_Factory`, al construir un nivel, se llama a `CrearBloque(TypeBlock)`.
2. Este método analiza el tipo de bloque solicitado.
3. Instancia dinámicamente el bloque con `SpawnActor<>()`.
4. Devuelve el bloque al builder o al mundo.

✅ Agregar nuevos bloques es tan simple como:
- Crear la nueva clase (e.g., `ABloque_Arena`)
- Añadir una línea en `CrearBloque()`.

---

## 🔶 B. Sistema de Power-Ups

### 🧩 Componentes Clave

#### 🏗️ Creator (Concreto): `APowerUps_Factory`

- **Responsabilidad:**  
  Implementa `CreatePowerUp(PowerUpType)`, que genera un power-up basado en un código entero.

---

#### ⚡ Producto Abstracto: `APowerUp`

- **Rol:**  
  Clase base de todos los objetos power-up.  
  Define interfaz común para efectos, activación, etc.

---

#### ⚡ Productos Concretos

- `APowerUp_Inmortalidad`  
- `APowerUp_Velocidad`  
- `APowerUp_Curacion`

> Cada uno aplica un efecto distinto al jugador tras ser recogido.

---

### 📊 Diagrama UML – Power-Ups (Factory Method)

![Diagrama Factory Method - PowerUps](https://github.com/user-attachments/assets/68f1cad0-4cb6-468d-b07b-50610bd6c5e1)

---

### ⚙️ Flujo de Uso

1. Un enemigo muere (`AEnemigo_Comun`).
2. Se determina aleatoriamente si se genera un power-up.
3. Se llama a `CreatePowerUp(PowerUpType)` desde `APowerUps_Factory`.
4. El método instancia el tipo adecuado mediante `SpawnActor`.

✅ El enemigo **no necesita conocer la clase específica** del power-up.

---

### 🚀 Ventajas del Enfoque

- 📦 **Centraliza la lógica de creación**
- 🔁 **Facilita añadir nuevos tipos**
- 🧼 **Reduce acoplamiento entre subsistemas**
- 🔧 **Permite configuraciones dinámicas o parametrizadas**
- 💡 **Extensible sin alterar el cliente (Principio de Abierto/Cerrado)**

---

---

## 🧱 4. Facade Pattern – *Patrón Fachada*

### 📖 Definición

El patrón **Facade** proporciona una **interfaz simplificada** a un conjunto de subsistemas complejos, ocultando los detalles internos y exponiendo una API clara para el cliente.  
🎯 Su objetivo es **reducir el acoplamiento**, **mejorar la organización** y **facilitar la interacción** con sistemas complejos.

---

### 🧠 Aplicación en BombBot: Comportamiento del Jefe Final

En *BombBot*, el **JefeFinal** es una entidad con múltiples capacidades de ataque. Para orquestar su comportamiento, se implementa el patrón **Fachada**, encapsulando subsistemas como:

- 🌪️ Ataques de esbirros  
- 💣 Caída de escombros  
- 🔫 Disparos en ráfagas

Todo esto queda detrás de la interfaz principal `JefeFinal`, que se encarga de coordinar y ejecutar los ataques de forma sincronizada.

---

## 🧩 Componentes Clave

### 🧷 Fachada: `JefeFinal`

- **Responsabilidad:**  
  Gestiona los ataques y comportamientos generales del jefe final, coordinando múltiples subsistemas sin exponer su complejidad.

- **Ubicación:**  
  `JefeFinal.h`, `JefeFinal.cpp`

---

### 🔧 Subsistemas

| Subsistema             | Función                                       |
|------------------------|-----------------------------------------------|
| `FSpawnerEsbirros`     | Genera esbirros para dificultar el combate    |
| `FSpawnerEscombros`    | Lanza escombros sobre el jugador              |
| `FSpawnerDisparos`     | Dispara proyectiles en ráfagas                |

> 🧬 Cada subsistema tiene una única responsabilidad, siguiendo el **principio de responsabilidad única**, lo cual permite mantener modularidad y facilidad de prueba.

---

### ⚙️ Explicación del Uso

- El cliente (por ejemplo, el sistema de juego) no se comunica directamente con `FSpawnerEsbirros`, `FSpawnerDisparos`, ni `FSpawnerEscombros`.
- En su lugar, llama a métodos del objeto `JefeFinal`, que se encarga de **delegar** y **coordinar** las acciones en sus subsistemas internos.

🔄 Este diseño permite que:
- Se agreguen nuevos ataques fácilmente (solo hay que crear un nuevo subsistema).
- Se mantenga un control centralizado y limpio.
- Se respete la **abstracción de alto nivel** sin ensuciar el código cliente.

---

## 🎮 Gameplay Grabado

[![Gameplay BombBot](https://github.com/user-attachments/assets/05c1c8c9-1b26-4fc6-9e58-b423d4df9216)](https://youtu.be/_IjVIPqWHDM?si=VkpBT7_jAyxYNzRl)
➡️ *Haz clic en la imagen para ver el video.*

---

## 💾 ¿Cómo instalar el juego?

> ⚠️ El juego se encuentra en **fase Pre-Alpha**.

### Instrucciones:
1. Clona el repositorio del proyecto desde GitHub.
2. Abre el archivo ejecutable. caso contrario:
3. Abre el proyecto en **Unreal Engine**.
4. Ejecuta el juego desde el Editor o genera el ejecutable.

---

## Conclusión

Este proyecto ha demostrado cómo los **patrones de diseño** permiten construir videojuegos complejos de forma estructurada y escalable:

🔧 **Builder Pattern**  
Permite la creación paso a paso de niveles personalizados y fácilmente intercambiables.

🏭 **Abstract Factory Pattern**  
Facilita la creación coherente de objetos relacionados por "mundo", manteniendo la estética y reglas uniformes.

🏗️ **Factory Method Pattern**  
Desacopla la lógica de instanciación de bloques y power-ups, permitiendo extensibilidad sin alterar el código cliente.

🎯 **Facade Pattern**  
Simplifica el control del jefe final al ocultar múltiples comportamientos bajo una interfaz limpia, haciendo que su lógica sea fácil de expandir y mantener.

---

Con esta arquitectura, *BombBot* queda preparado para futuras expansiones:  
🌍 nuevos mundos, 👾 enemigos más complejos y 🔮 nuevas mecánicas… todo sin romper el código ya existente.

---
