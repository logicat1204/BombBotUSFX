# Documentación: BombBot
## 1. Introducción
BomberBot es un videojuego desarrollado en Unreal Engine, inspirado en el clásico "BomberMan". El proyecto no solo busca recrear una experiencia de juego entretenida, sino también servir como un caso de estudio práctico para la implementación de patrones de diseño de software fundamentales en el contexto del desarrollo de videojuegos con C++.
El uso de estos patrones permite construir un sistema modular, flexible y escalable, facilitando la adición de nuevos tipos de niveles, enemigos, bloques y power-ups en el futuro. Este documento se enfoca en la descripción y análisis de tres patrones de diseño clave utilizados en la arquitectura del proyecto:
- **Patrón Builder:** Para la construcción paso a paso de los niveles.
- **Patrón Abstract Factory:** Para crear familias de objetos temáticos (ej. todos los elementos del "Mundo 1").
- **Patrón Factory Method:** Para la creación de objetos específicos como los diferentes tipos de bloques.
## 2. Patrones de Diseño Implementados
### 2.1. Patrón Builder
#### Concepto General:
El patrón Builder separa la construcción de un objeto complejo de su representación final. Esto permite que el mismo proceso de construcción pueda crear diferentes representaciones del objeto. Se compone de un **Director**, que conoce la secuencia de construcción, y un **Builder**, que sabe cómo ejecutar cada paso.
#### Aplicación en el Proyecto:
En BomberBot, la creación de un nivel completo es un proceso complejo que involucra varios pasos: generar el mapa de bloques, crear el terreno, posicionar a los enemigos, distribuir los power-ups y definir el punto de inicio y fin. El patrón Builder es ideal para orquestar este proceso.
- IILevels_Builder **(Interface):** Es la interfaz abstracta del Builder (ILevels_Builder.h). Define todos los pasos necesarios para construir un nivel (BuildMap(), BuildEnemy(), SetStartPosition(), etc.).
- AWorld1_Builder **(Concrete Builder):** Es la implementación concreta para construir los niveles del "Mundo 1" (World1_Builder.h, World1_Builder.cpp). Implementa los métodos de la interfaz utilizando una fábrica específica (AWorld1_Factory) para crear los elementos correspondientes a la temática de este mundo.
- ALevels_Director **(Director):** Es el director (Levels_Director.h, Levels_Director.cpp). Contiene una referencia a un IILevels_Builder. Sus métodos (CreateLevel1(), CreateLevel2(), etc.) dictan el orden en que se deben llamar los métodos del Builder para construir un nivel específico, sin conocer los detalles de cómo se implementa cada paso.
- ABuilder_Main **(Cliente):** Esta clase (Builder_Main.cpp) actúa como el cliente que inicializa el Director y el Builder, y da la orden de empezar la construcción.
Este patrón permite que en el futuro se pueda crear un AWorld2_Builder con una temática completamente diferente (ej. un mundo de hielo o lava) y el ALevels_Director podría usarlo sin necesidad de modificar su propio código, demostrando una gran flexibilidad.

![image](https://github.com/user-attachments/assets/6709d159-4e0d-4fa4-bb22-e863f7035aae)
### 2.2. Patrón Abstract Factory
#### Concepto General:
El patrón Abstract Factory proporciona una interfaz para crear familias de objetos relacionados o dependientes sin especificar sus clases concretas. Es un "super-factory" o una "fábrica de fábricas" que agrupa un conjunto de fábricas con una temática común.
#### Aplicación en el Proyecto:
Mientras que el Builder se enfoca en el proceso de construcción, la Abstract Factory se enfoca en la creación de un conjunto temático de objetos. En el proyecto, todos los elementos de un mundo (bloques, terreno, enemigos, etc.) forman una "familia".
- IIWorld_Factory **(Abstract Factory Interface):** Es la interfaz (IWorld_Factory.h) que define los métodos para crear todos los productos de la familia de un mundo: CreateMap(), CreateEnemy(), etc.
- AWorld1_Factory **(Concrete Factory):** Es la fábrica concreta para el "Mundo 1" (World1_Factory.h, World1_Factory.cpp). Implementa la interfaz IIWorld_Factory y es responsable de instanciar todos los elementos con la estética y comportamiento del "Mundo 1".
- AWorld1_FactoryBloques **(Helper Factory):** Esta clase (World1_FactoryBloques.cpp) es una fábrica auxiliar que se especializa únicamente en la creación de bloques. AWorld1_Factory la crea y la utiliza para delegar la tarea de instanciar los bloques, manteniendo el código organizado.
- **Productos (Blocks, Enemies, etc.):** Son las familias de objetos creados. Por ejemplo, AWorld1_Factory crea un mapa con ABloque_Pasto, ABloque_Madera, y podría estar configurada para crear AEnemigo_Comun como los enemigos base de ese mundo.
Si se quisiera crear un "Mundo 2" con bloques de hielo y enemigos de nieve, se crearía una AWorld2_Factory que implemente IIWorld_Factory, y el resto del sistema (como el AWorld2_Builder) podría usarla para generar un nivel con una temática completamente nueva.

![image](https://github.com/user-attachments/assets/327a3ce8-ab2a-4175-8d10-816cbea0e3b6)
### 2.3. Patrón Factory Method
#### Concepto General:
El patrón Factory Method define una interfaz para crear un objeto, pero delega la instanciación a las subclases. Es decir, una clase "creadora" tiene un método (Factory Method) que produce objetos, pero la clase exacta del objeto producido es determinada por la subclase que implementa ese método.
#### Aplicación en el Proyecto:
Este patrón se utiliza de forma muy clara dentro de la AWorld1_FactoryBloques para la creación de los diferentes tipos de bloques que componen el mapa.
- AFactoryBloques **(Creator Abstract Class):** Aunque no es estrictamente abstracta en el código, FactoryBloques.h representa el concepto de un creador de bloques.
- AWorld1_FactoryBloques **(Concrete Creator):** Es la clase que implementa la lógica de creación (World1_FactoryBloques.cpp).
- CrearBloque(FString TypeBlock, FVector Position) **(Factory Method):** Este es el método fábrica. Recibe un string ("BloqueMadera", "BloquePiedra", etc.) y, basándose en este parámetro, decide qué clase concreta de bloque debe instanciar y retornar. Centraliza la lógica de creación de bloques en un solo lugar.
- ABloqueGeneral **(Product Interface/Base Class):** Es la clase base de la que heredan todos los bloques (BloqueGeneral.h). El Factory Method devuelve punteros a esta clase base.
- ABloque_Madera, ABloque_Pasto, etc. **(Concrete Products):** Son las clases concretas de bloques que son instanciadas por el Factory Method.
El principal beneficio aquí es el desacoplamiento. El código que solicita un bloque (en este caso, AWorld1_Factory) no necesita saber cómo se crea un ABloque_Madera o un ABloque_Piedra. Simplemente le pide a la AWorld1_FactoryBloques que le dé un bloque de un tipo específico, y la fábrica se encarga de los detalles.

![image](https://github.com/user-attachments/assets/92e60bbb-7e85-48ea-bb64-56dc37031be6)
