/*#include "inicia.h"
#include <allegro.h>

void inicia_allegro(int ANCHO_ , int ALTO_){
   allegro_init();
   install_keyboard();

   set_color_depth(32);
   set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO_, ALTO_, 0, 0);
}

int inicia_audio(int izquierda, int derecha,SAMPLE *archivo_sonido){
    //SAMPLE *sonido;
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
       allegro_message("Error: inicializando sistema de sonido\n%s\n", allegro_error);
       return 1;
    }

    //sonido = load_wav(archivo_sonido);
    play_sample(archivo_sonido,200,150,1000,0);
    //play_midi(sonido,FALSE);
	set_volume(izquierda,derecha);
	return 0;
}*/
