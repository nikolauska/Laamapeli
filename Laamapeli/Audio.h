#ifndef audioDEF
#define audioDEF
#include "Header.h"

int main(int argc, char **argv)
{

	ALLEGRO_SAMPLE *lamasong = NULL;

	if(!al_init()){
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }
 
   if(!al_install_audio()){
      fprintf(stderr, "failed to initialize audio!\n");
      return -1;
   }
 
   if(!al_init_acodec_addon()){
      fprintf(stderr, "failed to initialize audio codecs!\n");
      return -1;
   }
 
   if (!al_reserve_samples(1)){
      fprintf(stderr, "failed to reserve samples!\n");
      return -1;
   }
 
   lamasong = al_load_sample( "llama song.ogg" );
 
   if (!lamasong){
      printf( "Audio clip sample not loaded!\n" ); 
      return -1;
   }


   al_play_sample(lamasong, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);  //atributes: volume (gain), pan (centering), speed, loop (ONCE/LOOP), ret_id?

   al_destroy_sample(lamasong);
   return 0;
}


#endif