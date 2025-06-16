# Documentación Técnica del Proyecto BombBot

Este documento detalla la arquitectura del videojuego **BombBot**, un título inspirado en el clásico *Bomberman*, con un enfoque particular en la aplicación de patrones de diseño de software para la generación procedural de niveles y la creación de objetos del juego.

---

## Tabla de Contenido

1. [Introducción](#introducción)
2. [Patrones de Diseño Aplicados](#patrones-de-diseño-aplicados)
   - [Builder Pattern (Constructor)](#1-builder-pattern-constructor)
   - [Abstract Factory Pattern (Fábrica Abstracta)](#2-abstract-factory-pattern-fábrica-abstracta)
   - [Factory Method Pattern (Método de Fábrica)](#3-factory-method-pattern-método-de-fábrica)
3. [Conclusión](#conclusión)

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

###  Diagrama UML de Clases (Builder Pattern)

  ![image](https://github.com/user-attachments/assets/0aee3dad-a3a9-4833-ae48-a05fbd7b481f)

### Explicación del Uso del Builder Pattern

El `ALevels_Director` es el componente central que decide la estructura de cada nivel.  
Cuando se le solicita crear un nivel (`CreateLevel1`, `CreateLevel2`, etc.), ejecuta una secuencia de llamadas como `BuildMap()`, `BuildEnemy()`, etc., sobre una instancia concreta de `IILevels_Builder`.

Los `AWorldX_Builder` son implementaciones concretas que traducen estas llamadas genéricas en lógica específica para construir el mundo correspondiente.  
Delegan finalmente la creación de los "productos" (bloques, enemigos, power-ups) a sus respectivas fábricas (`AWorldX_Factory`).

Este diseño permite cambiar fácilmente el tipo de mundo que se construye (por ejemplo, Mundo 1, Mundo 2, Mundo 3) simplemente asignando un `Concrete Builder` distinto al director, sin modificar la lógica de construcción general.

---

## 2. Abstract Factory Pattern (Fábrica Abstracta)

### Definición

El patrón **Abstract Factory** proporciona una interfaz para crear **familias de objetos relacionados o dependientes** sin especificar sus clases concretas.  
Permite a un cliente crear objetos que son coherentes entre sí.

---

### Contexto en el Proyecto: Creación de Objetos del Mundo

En *BombBot*, el patrón **Abstract Factory** se emplea para crear familias de objetos que pertenecen a un mundo específico (por ejemplo, Mundo 1, Mundo 2, Mundo 3).  
Esto asegura que todos los componentes de un nivel (mapa, terreno, enemigos, power-ups, portales) mantengan coherencia con la estética, reglas y diseño del mundo correspondiente.

---

### Componentes Clave

#### Abstract Factory: `IIWorld_Factory`
- **Responsabilidad:** Define la interfaz para crear una familia de objetos relacionados:
  - Mapas
  - Terrenos
  - Enemigos
  - Power-ups
  - Portales
- **Ubicación:** `IWorld_Factory.h`

#### Concrete Factories:
- `AWorld1_Factory`
- `AWorld2_Factory`
- `AWorld3_Factory`

**Responsabilidad:**  
Cada clase implementa `IIWorld_Factory` para producir productos concretos acordes a su mundo.  
Por ejemplo, `AWorld1_Factory` genera enemigos, bloques y power-ups específicos del Mundo 1.

**Ubicación:** Archivos `.h` y `.cpp` correspondientes a cada fábrica.

#### Abstract Products  
Son las interfaces o clases base de los objetos que se crean a través de la fábrica abstracta. Algunos ejemplos:
- `ABloqueGeneral`
- `AEnemigo`
- `APowerUp`

**Ubicación:** Archivos de definición de clases base como `BloqueGeneral.h`, `Enemigo.h`, `PowerUp.h`

#### Concrete Products
Son las implementaciones concretas de los productos creados por cada fábrica, tales como:
- `ABloque_Madera`, `ABloque_Piedra`
- `AEnemigo_Comun`
- `APowerUp_Inmortalidad`, `APowerUp_Velocidad`, `APowerUp_Curacion`

**Ubicación:** Archivos como `Bloque_Madera.h`, `Enemigo_Comun.h`, `PowerUp_Inmortalidad.h`, etc.

---

### Diagrama UML de Clases (Abstract Factory Pattern)

   ![image](https://github.com/user-attachments/assets/54bf9a22-c22b-4f4f-aa03-cb43a688ccaf)

### Explicación del Uso

Los *Concrete Builders* (por ejemplo, `AWorld1_Builder`) dependen de una instancia de `IIWorld_Factory` para obtener los componentes específicos de cada mundo.  
Por ejemplo, `AWorld1_Factory` contiene la lógica necesaria para crear los bloques, enemigos y power-ups del Mundo 1.

Si se desea añadir un nuevo mundo (como un "Mundo 4") con estilos visuales o comportamientos distintos, bastaría con implementar una nueva clase `AWorld4_Factory` que herede de `IIWorld_Factory`.  
No sería necesario modificar los constructores existentes ni al `Director`.

Dentro de cada `AWorldX_Factory`, la creación de bloques se delega a `AWorld1_FactoryBloques`, lo cual representa una aplicación del **Factory Method Pattern**.  
La creación de enemigos se realiza directamente mediante `SpawnActor<AEnemigo_Comun>` o `SpawnActor<AGenerador_Enemigos>`, y los power-ups se generan a través de `APowerUps_Factory`.

---

## 3. Factory Method Pattern (Método de Fábrica)

### Definición

El patrón **Factory Method** define una interfaz para la creación de objetos, pero permite que las subclases decidan qué clase instanciar.  
Esto permite delegar la responsabilidad de instanciación a las subclases, logrando una mayor flexibilidad y extensibilidad.

---

### Contexto en el Proyecto: Creación de Bloques y Power-Ups Específicos

Este patrón se observa principalmente en dos subsistemas del juego:

- **Creación de Tipos de Bloques:** Una fábrica especializada implementa un método que, dependiendo del tipo o identificador recibido, instancia un bloque específico.
- **Creación de Tipos de Power-Ups:** Similar al caso anterior, pero aplicado a los power-ups.

---

### Componentes Clave (Bloques)

#### Creator (Concrete): `AWorld1_FactoryBloques`
- **Responsabilidad:**  
  Implementa el método `CrearBloque()`, encargado de instanciar diferentes tipos de bloques (`ABloque_Madera`, `ABloque_Piedra`, `ABloque_Pasto`, `ABloque_Tierra`) según un parámetro de entrada (`TypeBlock`).

#### Product (Abstract): `ABloqueGeneral`  
- **Responsabilidad:**  
  Define la interfaz base para todos los bloques del juego. En muchos casos, estos heredan también de `ABloqueDestructibleBase`.

#### Concrete Products:
- `ABloque_Madera`
- `ABloque_Piedra`
- `ABloque_Pasto`
- `ABloque_Tierra`

**Responsabilidad:**  
Implementan la funcionalidad concreta de los diferentes tipos de bloques presentes en el juego.

---

### Diagrama UML de Clases (Factory Method Pattern)

![image](https://github.com/user-attachments/assets/bca971bf-f44c-4373-83cb-2e77a4ff5d40)

### Explicación del Uso (Bloques)

Dentro de `AWorld1_Factory`, cuando se necesita crear un bloque para el mapa (en el método `CreateBlocks()`), se delega la creación a una instancia de `AWorld1_FactoryBloques` mediante su método `CrearBloque()`.

Este método actúa como un **Factory Method parametrizado**:  
Recibe una cadena (`TypeBlock`) que indica el tipo de bloque a instanciar (por ejemplo, `"BloqueMadera"`, `"BloquePiedra"`, etc.), y luego crea la instancia correspondiente utilizando `GetWorld()->SpawnActor`.

Esta centralización de la lógica de creación permite:

- Añadir nuevos tipos de bloques simplemente extendiendo `CrearBloque()` con un nuevo `else if`.
- Implementar una nueva clase concreta de bloque sin modificar otras clases consumidoras.
- Mantener bajo acoplamiento y alta cohesión.

---

### Componentes Clave (Power-Ups)

#### Creator (Concrete): `APowerUps_Factory`

- **Responsabilidad:**  
  Contiene el método `CreatePowerUp()`, un Factory Method que instancia diferentes tipos de power-ups según un parámetro entero `PowerUpType`.

#### Product (Abstract): `APowerUp`

- **Responsabilidad:**  
  Define la interfaz base que todos los objetos PowerUp deben implementar.

#### Concrete Products:

- `APowerUp_Inmortalidad`
- `APowerUp_Velocidad`
- `APoweUp_Curacion`

- **Responsabilidad:**  
  Representan implementaciones específicas de power-ups con efectos distintos.

---

### Diagrama UML de Clases (Power-Ups - Factory Method Pattern)

![image](https://github.com/user-attachments/assets/68f1cad0-4cb6-468d-b07b-50610bd6c5e1)

### Explicación del Uso (Power-Ups)

Cuando un enemigo (`AEnemigo_Comun`) es destruido, existe una probabilidad de que invoque a `APowerUps_Factory` para generar un power-up. El método `CreatePowerUp()` de `APowerUps_Factory` toma como parámetro un entero (`PowerUpType`), que determina qué tipo específico de power-up instanciar:

- `APowerUp_Inmortalidad`
- `APowerUp_Velocidad`
- `APoweUp_Curacion`

Este enfoque abstrae completamente la lógica de creación de power-ups. La clase del enemigo simplemente solicita un power-up por tipo, sin preocuparse por detalles de implementación ni por conocer las clases concretas involucradas. Esto promueve el principio de inversión de dependencias y facilita la extensión del sistema.

---

### Conclusión

Esta fue nuestra aplicación de los patrones **Builder**, **Abstract Factory** y **Factory Method** en nuestro proyecto *BombBot* que ha sido clave para lograr una arquitectura robusta, modular y extensible.

- **Builder Pattern**: Permite la construcción paso a paso de niveles complejos, posibilitando que cada "mundo" tenga una configuración única sin modificar la lógica central del flujo de creación.
  
- **Abstract Factory Pattern**: Garantiza la coherencia temática de cada mundo al proporcionar familias de objetos relacionadas entre sí (bloques, enemigos, power-ups), asegurando compatibilidad y facilitando cambios globales por mundo.

- **Factory Method Pattern**: Facilita la creación específica de tipos de bloques y power-ups mediante métodos parametrizados, aislando el código cliente de las decisiones de instanciación concretas.

En conjunto, estos patrones no solo mejoran la mantenibilidad y escalabilidad del código, sino que también sientan las bases para futuras expansiones del juego, como la incorporación de nuevos mundos, enemigos, o mecánicas de juego, con un mínimo impacto en el código existente.


## Creditos
Trabajo realizado por:
- Arancibia Estrada Alvaro David.
- Mollinedo Siles Renzo Sebastián.
- Quispe Ticona Josias Asael.
- Magne Ordoñez Pedro Jhoel Antonio.
- Cornejo Moscoso Gabriel Orlando.

### SIS 457 - Programacion Avanzada

