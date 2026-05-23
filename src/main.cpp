#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_random.h"
#include "bn_vector.h"
#include "bn_sprite_ptr.h"
#include "bn_bg_palettes.h"
// Inclusiones para el motor de texto
#include "common_variable_8x16_sprite_font.h"
#include "bn_sprite_text_generator.h"
#include "bn_string.h"

// Archivos de cabecera para los sprites de las cartas
#include "bn_sprite_items_imaback.h"
#include "bn_sprite_items_ima.h"
#include "bn_sprite_items_ima2.h"
#include "bn_sprite_items_ima3.h"
#include "bn_sound_items.h" 
struct Carta {
    int id;
    int x;
    int y;
    bool descubierta;
    bool resuelta;
    bn::sprite_ptr sprite;
};
int obtener_grupo_imagen(int id) {
    if (id == 1 || id == 4) return 1; // Grupo de la imagen 'ima'
    if (id == 2 || id == 5) return 2; // Grupo de la imagen 'ima2'
    if (id == 3 || id == 6) return 3; // Grupo de la imagen 'ima3'
    return 0;
}
// Función auxiliar para renderizar la cara correcta según el ID de la carta
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

int main()
{
    bn::core::init();
    bn::bg_palettes::set_transparent_color(bn::color(0, 0, 0));

     // Inicializar el generador de texto con la fuente de 8x8 píxeles por defecto
    bn::sprite_text_generator text_generator(common::variable_8x16_sprite_font);
    text_generator.set_center_alignment(); // Centrar el texto en sus coordenadas

    // Contenedor dinámico para almacenar los sprites de las letras del mensaje
    bn::vector<bn::sprite_ptr, 64> texto_sprites;
    bn::vector<bn::sprite_ptr, 16> puntaje_sprites; // <-- Vector exclusivo para el puntaje
    bool actualizar_marcador = true; // <-- Bandera para redibujar el puntaje solo cuando cambia

    // Matriz de posiciones fijas para 12 cartas (4 columnas x 3 filas)
    // Centradas en la pantalla de la GBA (240x160)
    int pos_x[12] = { -60, -20, 20, 60,  -60, -20, 20, 60,  -60, -20, 20, 60 };
    int pos_y[12] = { -35, -35, -35, -35,  0, 0, 0, 0,      35, 35, 35, 35 };
    
    // 6 parejas de IDs
    int ids[12] = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6 };

    bn::random random;
    bn::vector<Carta, 12> cartas; // Vector expandido a 12 espacios

    int cursor_index = 0;
    int primer_seleccionada = -1;
    int segundo_seleccionada = -1;
    int tiempo_espera = 0;
    int frame_count = 0; 
    int parejas_resueltas = 0; 
    bool juego_ganado = false; 
    int tiempo_victoria = 0; 

    // Función Lambda para inicializar o reiniciar el tablero por completo
    auto iniciar_juego = [&]() {
        cartas.clear();
        texto_sprites.clear(); 
        puntaje_sprites.clear(); // <-- Borra los sprites del número anterior al reiniciar
        actualizar_marcador = true; // <-- Fuerza al juego a dibujar el marcador en el primer frame

        // Volver a llenar y mezclar la lista de IDs
        int nuevos_ids[12] = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6 };
        for (int i = 11; i > 0; --i) {
            int j = random.get_int(i + 1);
            int temp = nuevos_ids[i];
            nuevos_ids[i] = nuevos_ids[j];
            nuevos_ids[j] = temp;
        }

        // Crear los sprites boca abajo
        for(int i = 0; i < 12; ++i) {
            bn::sprite_ptr sp = bn::sprite_items::imaback.create_sprite(pos_x[i], pos_y[i]);
            cartas.push_back({nuevos_ids[i], pos_x[i], pos_y[i], false, false, sp});
        }

        // Restablecer variables del sistema
        cursor_index = 0;
        primer_seleccionada = -1;
        segundo_seleccionada = -1;
        tiempo_espera = 0;
        parejas_resueltas = 0;
        tiempo_victoria = 0;
        juego_ganado = false;
    };

    // Inicializar el tablero en el primer inicio de la consola
    iniciar_juego();

    while(true)
    {
        // Botón SELECT: Reinicia el juego en cualquier momento
        if (bn::keypad::select_pressed()) {
            iniciar_juego();
        }

         // Lógica de impresión del puntaje (se ejecuta al inicio o cuando sumas un punto)
        if (actualizar_marcador) {
            puntaje_sprites.clear(); // Borra los sprites viejos del número anterior
            text_generator.set_left_alignment(); // Alinea el texto a la izquierda para la esquina
            
            bn::string<16> texto_puntaje = "PTS: ";
            texto_puntaje += bn::to_string<4>(parejas_resueltas);
            
            // Dibuja arriba a la izquierda (X = -110, Y = -70)
            if (puntaje_sprites.empty()) {
            text_generator.generate(-110, -70, texto_puntaje, puntaje_sprites);}
            actualizar_marcador = false; // Bloquea hasta el siguiente cambio
        }
        // Si ya se ganaron las 6 parejas, congelamos las mecánicas normales
        if (juego_ganado) {
            
            text_generator.set_center_alignment(); 
            if (texto_sprites.empty()) {
            text_generator.generate(0, -65, "¡HAS GANADO!", texto_sprites);}
            
            for(int i = 0; i < 12; ++i) {
                cartas[i].sprite.set_visible(true);
            }
            tiempo_victoria++;
             // 120 frames = 2 segundos exactos a 60 FPS
            if (tiempo_victoria >= 120) { // <-- NUEVO: Condición de tiempo cumplido
                iniciar_juego();          // <-- NUEVO: Reinicia el juego automáticamente
            }
            bn::core::update();
            continue; 
        }

        // 1. Lógica de Espera (oculta las cartas si el jugador se equivoca de pareja)
        if (tiempo_espera > 0) {
            --tiempo_espera;
            if (tiempo_espera == 0) {
                cartas[primer_seleccionada].sprite = bn::sprite_items::imaback.create_sprite(cartas[primer_seleccionada].x, cartas[primer_seleccionada].y);
                cartas[segundo_seleccionada].sprite = bn::sprite_items::imaback.create_sprite(cartas[segundo_seleccionada].x, cartas[segundo_seleccionada].y);
                cartas[primer_seleccionada].descubierta = false;
                cartas[segundo_seleccionada].descubierta = false;
                primer_seleccionada = -1;
                segundo_seleccionada = -1;
                texto_sprites.clear();
            }
        }
        else {
            // 2. Control del Cursor adaptado a 4 columnas y 3 filas
            if (bn::keypad::left_pressed() && cursor_index % 4 > 0) cursor_index -= 1;
            if (bn::keypad::right_pressed() && cursor_index % 4 < 3) cursor_index += 1;
            if (bn::keypad::up_pressed() && cursor_index >= 4) cursor_index -= 4;
            if (bn::keypad::down_pressed() && cursor_index < 8) cursor_index += 4;

            // 3. Selección de Carta con el Botón A
            if (bn::keypad::a_pressed() && !cartas[cursor_index].descubierta && !cartas[cursor_index].resuelta) {
                
                // Mostrar la cara oculta de la carta actual
                mostrar_cara_carta(cartas[cursor_index]);
                cartas[cursor_index].descubierta = true;

                if (primer_seleccionada == -1) {
                    primer_seleccionada = cursor_index;
                } else {
                    segundo_seleccionada = cursor_index;
                    
                    // Comprobar coincidencia
                     if (obtener_grupo_imagen(cartas[primer_seleccionada].id) == obtener_grupo_imagen(cartas[segundo_seleccionada].id)) {
                        cartas[primer_seleccionada].resuelta = true;
                        cartas[segundo_seleccionada].resuelta = true;
                        primer_seleccionada = -1;
                        segundo_seleccionada = -1;
                        
                        parejas_resueltas++;
                        bn::sound_items::cure.play(); 
                        actualizar_marcador = true; // <-- Fuerza a redibujar el marcador

                        // Condición de victoria: completar las 6 parejas
                        if (parejas_resueltas == 6) {
                            juego_ganado = true;
                        }
                    } else {
                        if (texto_sprites.empty()) {
                        text_generator.set_center_alignment();
                        text_generator.generate(0, -65, "¡No es Par!", texto_sprites);}
                        bn::sound_items::flame.play();
                        tiempo_espera = 45; // 0.75 segundos para memorizar el error
                    }
                }
            }
        }

        // Feedback visual de parpadeo sobre la carta seleccionada
        for(int i = 0; i < 12; ++i) {
            if(i == cursor_index ) {
                cartas[i].sprite.set_visible((frame_count % 16) < 8); 
            } else {
                cartas[i].sprite.set_visible(true);
            }
        }

        frame_count = (frame_count + 1) % 16; 
        bn::core::update();
    }
}
