# Documentación Técnica del Proyecto BombBot

Este documento detalla la arquitectura del videojuego **BombBot**, un título inspirado en el clásico *Bomberman*, con un enfoque particular en la aplicación de **patrones de diseño de software** para la generación procedural de niveles y la creación de objetos del juego.

---

## Introducción

El proyecto **BombBot** utiliza varios patrones de diseño para mejorar la **modularidad**, la **flexibilidad** y la **mantenibilidad** del código, especialmente en los subsistemas de **creación de mundos**, **gestión de objetos** y **lógica de juego**.  
La implementación de estos patrones facilita la expansión del juego con nuevos tipos de niveles, enemigos y power-ups sin modificar el código existente de manera extensiva.

---

## Patrones de Diseño Aplicados

Los siguientes patrones de diseño están implementados de manera prominente en la arquitectura del proyecto:

- **Builder Pattern (Constructor)**
- **Abstract Factory Pattern (Fábrica Abstracta)**
- **Factory Method Pattern (Método de Fábrica)**

---

## 1. Builder Pattern (Constructor)

### Definición

El patrón **Builder** separa la construcción de un objeto complejo de su representación, permitiendo que el mismo proceso de construcción cree diferentes representaciones. Un **Director** controla el proceso, delegando la creación de las partes a un **Builder (constructor)** específico.

---

### Contexto en el Proyecto: Generación de Niveles

En *BombBot*, el **Builder Pattern** es fundamental para la construcción de los diferentes niveles del juego.  
Cada "mundo" o nivel (`World1`, `World2`, `World3`) se construye siguiendo una secuencia de pasos definida por un **Director**, pero la implementación de esos pasos (cómo se construyen los mapas, se colocan enemigos, etc.) varía entre los constructores de cada mundo.

---

### Componentes Clave

#### Director: `ALevels_Director`
- **Responsabilidad:** Orquesta el proceso de construcción del nivel, definiendo la secuencia de pasos.
- **Métodos:** `CreateLevel1()`, `CreateLevel2()`, etc., que invocan los métodos del constructor asignado.
- **Ubicación:** `Levels_Director.h` y `Levels_Director.cpp`

#### Abstract Builder: `IILevels_Builder`
- **Responsabilidad:** Declara una interfaz para la construcción de las partes del objeto Nivel. Define los métodos para construir el mapa, enemigos, power-ups, etc.
- **Ubicación:** `ILevels_Builder.h`

#### Concrete Builders: `AWorld1_Builder`, `AWorld2_Builder`, `AWorld3_Builder`
- **Responsabilidad:** Implementan la interfaz `IILevels_Builder`.  
  Cada constructor concreto (por ejemplo, `AWorld1_Builder` para el Mundo 1) sabe cómo construir las partes del nivel específico, utilizando una **Factory** particular para la creación de los componentes.
- **Ubicación:** Archivos `.h` y `.cpp` correspondientes de cada builder.

#### Producto: El Nivel
- Representado por el conjunto de bloques, enemigos y power-ups en el mundo.  
- Este es el **objeto complejo** que se está construyendo mediante el patrón *Builder*.
