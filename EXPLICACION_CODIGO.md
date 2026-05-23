# Explicación del Código del Juego "Memorizar" en Butano para GBA

## 📋 Resumen General

Este es un **juego de memoria (Memory Match)** desarrollado con **Butano**, un framework C++ optimizado para Nintendo Game Boy Advance (GBA). El juego consiste en:
- 12 cartas organizadas en una cuadrícula de 4x3
- 6 parejas de imágenes idénticas
- El jugador debe emparejar todas las cartas antes de ganar
- Controles: flechas direccionales para mover el cursor, botón A para voltear cartas, SELECT para reiniciar

---

## 🎮 Secciones del Código

### 1. **Includes y Dependencias** (Líneas 1-13)

```cpp
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_random.h"
#include "bn_vector.h"
#include "bn_sprite_ptr.h"
```

Estas son las librerías principales de Butano:
- **`bn_core.h`**: Inicialización y actualización del motor de juego
- **`bn_keypad.h`**: Lectura de entrada de los botones de la GBA
- **`bn_random.h`**: Generador de números aleatorios para mezclar cartas
- **`bn_vector.h`**: Contenedor dinámico optimizado (similar a `std::vector`)
- **`bn_sprite_ptr.h`**: Punteros inteligentes para manejar sprites (imágenes)
- **`bn_string.h`**: Para manejo de texto dinámico (marcador de puntos)

Los includes de `bn_sprite_items_imaXXX.h` contienen datos gráficos precompilados:
- **`imaback`**: La cara trasera de las cartas
- **`ima`, `ima2`, `ima3`**: Las imágenes frontales de las cartas

---

### 2. **Función `obtener_grupo_imagen()`** (Nuevo)

```cpp
int obtener_grupo_imagen(int id) {
    if (id == 1 || id == 4) return 1; // Grupo 'ima'
    if (id == 2 || id == 5) return 2; // Grupo 'ima2'
    if (id == 3 || id == 6) return 3; // Grupo 'ima3'
    return 0;
}
```

Esta función permite agrupar diferentes IDs bajo una misma imagen gráfica. Esto es clave para que el juego detecte un "par" incluso si los IDs técnicos de las cartas son distintos (ej: 1 y 4), siempre que visualmente sean la misma imagen.

---

### 3. **Estructura Carta** (Líneas 15-21)

```cpp
struct Carta {
    int id;              // Identificador (1-6) que determina la pareja
    int x, y;            // Posición en pantalla
    bool descubierta;    // ¿Está boca arriba mostrando su imagen?
    bool resuelta;       // ¿Ya fue emparejada correctamente?
    bn::sprite_ptr sprite; // El gráfico que se dibuja en pantalla
};
```

Cada carta es un objeto con:
- **`id`**: Número del 1 al 6 (dos cartas con el mismo ID forman una pareja)
- **Posición**: Coordenadas X, Y en la pantalla de la GBA
- **Estados**: `descubierta` (está visible) y `resuelta` (fue encontrada)
- **Sprite**: La imagen gráfica que Butano renderiza

---

### 4. **Función `mostrar_cara_carta()`**

```cpp
void mostrar_cara_carta(Carta& carta) {
    int x = carta.x;
    int y = carta.y;
    switch(carta.id) {
        case 1: carta.sprite = bn::sprite_items::ima.create_sprite(x, y); break;
        case 2: carta.sprite = bn::sprite_items::ima2.create_sprite(x, y); break;
        case 3: carta.sprite = bn::sprite_items::ima3.create_sprite(x, y); break;
        case 4: carta.sprite = bn::sprite_items::ima.create_sprite(x, y); break;
        case 5: carta.sprite = bn::sprite_items::ima2.create_sprite(x, y); break;
        case 6: carta.sprite = bn::sprite_items::ima3.create_sprite(x, y); break;
    }
}
```

Esta función:
1. Toma una carta y sus coordenadas
2. Según el `id` (1-6), crea el sprite correspondiente. Nota que los IDs 1 y 4 comparten imagen, al igual que 2-5 y 3-6.
3. Esto "voltea" la carta mostrando su imagen frontal.

---

### 5. **Función Main**

#### A. Inicialización de Butano
```cpp
bn::core::init();
```
Configura el hardware de la GBA.

#### B. Posiciones y Marcador (Líneas 68-75)

```cpp
bn::vector<bn::sprite_ptr, 16> puntaje_sprites;
bool actualizar_marcador = true;
```
Se añade un sistema para mostrar el puntaje en la esquina superior izquierda.

#### C. Inicialización de Variables

```cpp
int cursor_index = 0;         // Carta apuntada (0-11)
int primer_seleccionada = -1; // Primera carta elegida
int segundo_seleccionada = -1;// Segunda carta elegida
int tiempo_espera = 0;        // Frames de espera tras error
int frame_count = 0;          // Contador efectos visuales
int parejas_resueltas = 0;    // Parejas encontradas
bool juego_ganado = false;    // ¿Ganó?
int tiempo_victoria = 0;      // Temporizador para reinicio automático
```

---

### 6. **Lambda `iniciar_juego`**

Resetea todo el tablero, mezcla las cartas y limpia los sprites de texto del marcador y mensajes.

---

### 7. **Loop Principal del Juego**

#### **7.1 Marcador de Puntos**
Cada vez que `actualizar_marcador` es true, el juego regenera el texto "PTS: X" en la esquina (-110, -70).

#### **7.2 Condición de Victoria**
Si `juego_ganado` es true:
- Muestra el mensaje "¡HAS GANADO!".
- Inicia un contador `tiempo_victoria`.
- Al llegar a 120 frames (2 segundos), llama a `iniciar_juego()` automáticamente.

#### **7.3 Lógica de Selección y Comparación**

```cpp
if (obtener_grupo_imagen(cartas[primer_seleccionada].id) == obtener_grupo_imagen(cartas[segundo_seleccionada].id)) {
    // Es un par correcto
}
```
Aquí es donde se aplica la mejora: no se comparan los IDs directamente, sino el **grupo de imagen** al que pertenecen. Esto permite que imágenes repetidas en diferentes IDs cuenten como pareja.

---

## 📊 Variables Importantes

| Variable | Rango | Significado |
|----------|-------|-------------|
| `cursor_index` | 0-11 | Índice de la carta apuntada |
| `primer_seleccionada` | -1 a 11 | Primera carta seleccionada |
| `segundo_seleccionada` | -1 a 11 | Segunda carta seleccionada |
| `tiempo_espera` | 0-45 | Frames restantes de espera |
| `parejas_resueltas` | 0-6 | Parejas encontradas |
| `actualizar_marcador` | bool | Indica si hay que redibujar los puntos |
| `tiempo_victoria` | 0-120 | Tiempo antes del reinicio automático |

---

## 🎨 Imágenes Usadas

- **`imaback`**: Dorso de las cartas
- **`ima1` - `ima6`**: Frente de cada pareja (6 imágenes diferentes)

Total: **12 sprites** (12 cartas con 2 imágenes cada una: dorso + frente)

---

## ⚙️ Compilación y Ejecución

```bash
make -j16  # Compila el proyecto
# Genera: memorizar.gba (ejecutable de GBA)
```

El juego se ejecuta en un emulador de GBA (ej: mGBA, VBA) o en una GBA física con flashcart.
