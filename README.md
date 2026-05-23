# 🎮 MemorizarGBA - Juego de Memoria para Game Boy Advance

Un juego clásico de memoria (Memory Match) desarrollado con **Butano**, un framework C++ optimizado para Nintendo Game Boy Advance (GBA).

## 📋 Descripción

**MemorizarGBA** es un juego educativo y entretenido en el que el jugador debe emparejar todas las cartas en la menor cantidad de intentos posible. El juego presenta:

- **12 cartas** organizadas en una cuadrícula de 4×3
- **6 parejas** de imágenes diferentes
- **Mecánica simple pero desafiante**: voltea dos cartas, si coinciden se quedan descubiertas, si no, se voltean de nuevo
- **Sistema de puntos** que muestra las parejas encontradas
- **Reinicio automático** tras completar el juego

## 🎯 Características

✅ Interfaz gráfica intuitiva  
✅ Controles simples con flechas direccionales  
✅ Sistema de puntuación en tiempo real  
✅ Retroalimentación visual (parpadeo del cursor)  
✅ Efectos de sonido para acertos y errores  
✅ Reinicio automático tras ganar  
✅ Desarrollado en C++ con Butano Framework  

## 🕹️ Controles

| Botón | Acción |
|-------|--------|
| **Flechas ↑↓←→** | Mover el cursor entre cartas |
| **A** | Voltear carta actual |
| **SELECT** | Reiniciar juego en cualquier momento |

## 📁 Estructura del Proyecto

```
memorizarGBA/
├── README.md                    # Este archivo
├── EXPLICACION_CODIGO.md        # Documentación técnica detallada
├── Makefile                     # Configuración de compilación
├── src/
│   └── main.cpp                # Código fuente principal del juego
├── include/                    # Archivos de cabecera (si los hay)
├── graphics/                   # Assets gráficos (imágenes de cartas)
│   ├── ima.json               # Imagen del grupo 1 (apareador 1 y 4)
│   ├── ima2.json              # Imagen del grupo 2 (apareador 2 y 5)
│   ├── ima3.json              # Imagen del grupo 3 (apareador 3 y 6)
│   ├── imaback.json           # Dorso de las cartas
│   └── ... (más assets)
├── audio/                      # Efectos de sonido
└── *.sav                       # Archivos de guardado (opcional)
```

## 🛠️ Requisitos

### Para Compilar
- **Butano Framework** instalado y configurado
- **Compilador ARM** compatible con GBA (arm-none-eabi-gcc)
- **Make** para ejecutar el Makefile
- **Windows PowerShell** o terminal compatible

### Para Ejecutar
- **Emulador de GBA** (recomendado: mGBA, VBA-M)
- O una **Game Boy Advance física** con flashcart compatible

## 📦 Compilación

```bash
# Compilar el proyecto con 16 hilos
make -j16

# Salida esperada:
# memorizarGBA.gba (ejecutable compilado)
# memorizar.sav (archivo de configuración de Butano)
```

## ▶️ Ejecución

### En Emulador
1. Abre tu emulador de GBA favorito (mGBA, VBA, etc.)
2. Carga el archivo `memorizarGBA.gba`
3. ¡A jugar!

### En GBA Física
1. Copia `memorizarGBA.gba` a tu flashcart GBA
2. Inserta el cartucho en tu Game Boy Advance
3. Selecciona el juego y presiona A para iniciar

## 🎨 Sistema de Imágenes

El juego utiliza un sistema inteligente de agrupación de imágenes:

| Pareja | ID Cartas | Imagen | Archivo |
|--------|-----------|--------|---------|
| 1 | 1, 4 | Imagen 1 (`ima`) | `ima.json` |
| 2 | 2, 5 | Imagen 2 (`ima2`) | `ima2.json` |
| 3 | 3, 6 | Imagen 3 (`ima3`) | `ima3.json` |
| Dorso | Todas | Dorso (`imaback`) | `imaback.json` |

> **Nota**: Este sistema permite que diferentes IDs de cartas muestren la misma imagen visual, facilitando la detección de parejas.

## 🔊 Efectos de Sonido

- **`cure.wav`** → Se reproduce al encontrar una pareja correcta ✓
- **`flame.wav`** → Se reproduce al seleccionar una pareja incorrecta ✗

## 💡 Mecánica del Juego

### Flujo Principal
1. Se muestra una cuadrícula de 12 cartas boca abajo
2. El jugador navega con flechas y presiona A para voltear cartas
3. El juego compara las dos cartas volteadas:
   - **Coinciden** → Se marcan como resueltas, puntaje +1
   - **No coinciden** → Se voltean de nuevo tras 0.75 segundos
4. Al resolver las 6 parejas → **¡HAS GANADO!**
5. Tras 2 segundos, el juego reinicia automáticamente

### Variables Clave
- `cursor_index` → Índice de la carta bajo el cursor (0-11)
- `parejas_resueltas` → Contador de parejas encontradas (0-6)
- `tiempo_espera` → Frames de espera al cometer error
- `juego_ganado` → Bandera de victoria
- `actualizar_marcador` → Indicador para redibujar puntuación

## 🚀 Optimizaciones Implementadas

- **Vectores dinámicos optimizados** de Butano para gestión eficiente de memoria
- **Sprites inteligentes** que reutilizan imágenes para múltiples cartas
- **Generación de texto dinámico** solo cuando es necesario
- **Control visual con parpadeo** para feedback inmediato
- **Mezcla aleatoria de cartas** en cada partida

## 📖 Documentación Adicional

Para una explicación técnica detallada del código, consulta:
→ [EXPLICACION_CODIGO.md](EXPLICACION_CODIGO.md)

En este archivo encontrarás:
- Descripción de cada función y estructura
- Explicación de inclusiones de Butano
- Detalles de la lambda `iniciar_juego()`
- Lógica del loop principal
- Variables importantes y su rango

## 🏆 Objetivo del Juego

**Resolver todas las 6 parejas en el menor tiempo y con la menor cantidad de intentos posible.**

El juego mantiene un contador de parejas encontradas que se muestra en la esquina superior izquierda (PTS: X/6).

## 🐛 Solución de Problemas

| Problema | Solución |
|----------|----------|
| Compilation error | Asegúrate de que Butano esté correctamente instalado |
| No se generan gráficos | Verifica que los archivos `.json` en `graphics/` existan |
| Sin sonido | Comprueba que los archivos `.wav` estén en `audio/` |
| Emulador no carga | Usa un emulador compatible (mGBA recomendado) |

## 👨‍💻 Tecnología

- **Lenguaje**: C++ (C++20)
- **Framework**: Butano (https://github.com/butano-framework/butano)
- **Plataforma**: Nintendo Game Boy Advance (GBA)
- **Compilador**: arm-none-eabi-gcc

## 📝 Licencia

Este es un proyecto educativo basado en Butano Framework.

## 🎓 Aprendizaje

Este proyecto es ideal para aprender:
- Programación en C++ para plataformas embebidas
- Uso de Butano Framework para desarrollo GBA
- Desarrollo de juegos simples
- Gestión de entrada/salida en sistemas limitados
- Optimización de memoria en plataformas retro

---

**¡Que disfrutes del juego!** 🎮✨

Última actualización: Mayo 2026
