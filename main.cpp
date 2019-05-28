#include <stdlib.h>
#include <allegro.h>
#include "inicia.h"
#include <locale.h>

const int maxdisp = 10, ANCHO = 500, ALTO = 450;


class Nave{
    int x,y;
    int dir;

public:
    Nave(int _x,int _y,int _dir) : x(_x), y(_y), dir(_dir){};
    virtual void mostrar_nave(BITMAP*,BITMAP*);
    virtual void mover();
    virtual int getX(){return x;}
    virtual int getY(){return y;}
    virtual void setDir(const int _dir) {dir = _dir;}
    virtual void setX(const int _x){x = _x;}
    virtual void setY(const int _y){y = _y;}
    void tipo_nave();
};

void Nave::mostrar_nave(BITMAP* nave,BITMAP* buffer){
    masked_blit(nave, buffer, 40*dir, 0, x, y, 40, 47);
}

void Nave::mover(){
    if(key[KEY_UP] && y > 0)
       { dir = 1; y -= 2; }

       else if(key[KEY_DOWN] && y < ALTO-47)
       { dir = 1; y += 2; }

       if(key[KEY_RIGHT] && x < ANCHO-40)
       { dir = 2; x += 2; }

       else if(key[KEY_LEFT] && x > 0)
       { dir = 0; x -= 2; }

       else dir = 1;
}


class Bala : public Nave{
    int dx,dy;
public:
    Bala();
    Bala(int _x,int _y,int _dir,int _dx,int _dy) : Nave(_x,_y,_dir){dx=_dx,dy=_dy;};
    void mostrar_nave(BITMAP*,BITMAP*);
    int getX(){};
    int getY(){};
    void setX(const int _x){};
    void setY(const int _y){};
    void setDir(const int _dir){};
    int getdX(){return dx;}
    int getdY(){return dy;}
    void setdX(const int _dx){dx = _dx;}
    void setdY(const int _dy){dy = _dy;}
    //void mover();
};

void Bala::mostrar_nave(BITMAP* bala,BITMAP* buffer){
    masked_blit(bala, buffer, 0, 0, dx, dy, 6, 6);
}

/*void Bala::mover(){
    int flag_dispara = 0,nro_disparos = 0;
    if(key[KEY_SPACE]  && flag_dispara == 0)
       {
        if(nro_disparos < maxdisp)
        {
         nro_disparos++;
         dx = 0;
         dy = -3;
         flag_dispara = 1;
        }
       }
       if (contt++ > 10){
        flag_dispara = 0; contt = 0;
       }
       if(nro_disparos > 0)
       {
        for(int cont = 1; cont <= nro_disparos; cont++)
        {
         x += dx;
         y += dy;
         masked_blit(bala, buffer, 0, 0,x ,y, 6, 6);

         if (y > ALTO || y < 0 || x > ANCHO || x < 0){
            nro_disparos--;
            if (nro_disparos < 0)
                nro_disparos = 0;
         }

        }
       }
}*/


int main()
{
    setlocale(LC_ALL,"spanish");//gramática

    Nave nave_jugador(ANCHO/2-20,3*ALTO/4,1);

    Bala municion_jugador[maxdisp]=Bala(ANCHO/2-1,3*ALTO/4+2,0,0,-3);


    /*municion_jugador[0].setX(300);
    municion_jugador[0].setY(200);
    municion_jugador[0].setDir(0);
    municion_jugador[0].setdX(0);
    municion_jugador[0].setdY(-3);*/

    //municion_jugador[0](0,0,0,0,0);

    //inicia la libreria de allegro...
    inicia_allegro(ANCHO,ALTO);

    //sonido...
    SAMPLE *archivo_sonido = load_wav("audio01.wav");

    inicia_audio(330,300,archivo_sonido);

    BITMAP *nave = load_bitmap("nave.bmp",NULL);
    BITMAP *fondo = load_bitmap("espacio.bmp",NULL);
    BITMAP *bala = load_bitmap("bala.bmp", NULL);  // otra cosa
    BITMAP *buffer = create_bitmap(ANCHO,ALTO);


    int i = ALTO ,flag_dispara=0, contt = 0,nro_disparos = 0;
    while(!key[KEY_ESC]){

        blit(fondo,buffer,0,--i,0,0,ANCHO,ALTO);  if(i == 0) i=ALTO;
        //mostrar_nave(nave,buffer,nav);
        nave_jugador.mostrar_nave(nave,buffer);

        textout_centre_ex(buffer, font, "Vidas: ", 50, 25, 0xffffff, 0x999999);
        textprintf_centre_ex(buffer, font, 75, 25, 0xffffff, 0x999999,"%d",4);//vidas...

        textout_centre_ex(buffer, font, "SHOOTING PLANES", 150, 25, 0xffffff, 0x999999);

        nave_jugador.mover();

       ////rutina de disparos
       if(key[KEY_SPACE]  && flag_dispara == 0)
       {

        if(nro_disparos < maxdisp){
         municion_jugador[nro_disparos].setX(nave_jugador.getX() + 19);
         municion_jugador[nro_disparos].setY(nave_jugador.getY() + 2);
         municion_jugador[nro_disparos].setDir(0);
         municion_jugador[nro_disparos].setdX(0);
         municion_jugador[nro_disparos].setdY(-3);
            nro_disparos++;
         flag_dispara = 1;
        }

       }

       if(nro_disparos > 0)
       {
        for(int cont = 0; cont < nro_disparos; cont++)
        {
         municion_jugador[cont].setX(municion_jugador[cont].getX() + municion_jugador[cont].getdX());
         municion_jugador[cont].setY(municion_jugador[cont].getX() + municion_jugador[cont].getdY());
         masked_blit(bala, buffer, 0, 0,municion_jugador[cont].getX() ,municion_jugador[cont].getY(), 6, 6);

         if (municion_jugador[cont].getY() > ALTO || municion_jugador[cont].getY() < 0 ||
             municion_jugador[cont].getX() > ANCHO || municion_jugador[cont].getX() < 0){

            municion_jugador[cont] = municion_jugador[nro_disparos];
            nro_disparos--;
            if (nro_disparos < 0)
                nro_disparos= 0;
         }

        }
       }

       if (contt++ > 10){
        flag_dispara = 0; contt = 0;
       }


       /*if(key[KEY_SPACE]  && flag_dispara == 0)
       {
        if(nav.ndisparos < maxdisp)
        {
         nav.ndisparos++;
         disparos[nav.ndisparos].x = nav.x + 19;
         disparos[nav.ndisparos].y = nav.y + 2;
         disparos[nav.ndisparos].dx = 0;
         disparos[nav.ndisparos].dy = -3;
         flag_dispara = 1;
        }

       }
       if (contt++ > 10){
        flag_dispara = 0; contt = 0;
       }
       if(nav.ndisparos > 0)
       {
        for(int cont = 1; cont <= nav.ndisparos; cont++)
        {
         disparos[cont].x += disparos[cont].dx;
         disparos[cont].y += disparos[cont].dy;
         masked_blit(bala, buffer, 0, 0,disparos[cont].x ,disparos[cont].y, 6, 6);

         if (disparos[cont].y > ALTO || disparos[cont].y < 0 || disparos[cont].x > ANCHO || disparos[cont].x < 0){

            disparos[cont] = disparos[nav.ndisparos];
            nav.ndisparos--;
            if (nav.ndisparos < 0)
                nav.ndisparos = 0;
         }

        }
       }*/
       blit(buffer,screen,0,0,0,0,ANCHO,ALTO);
       rest(10);

    }
    destroy_sample(archivo_sonido);
    destroy_bitmap(buffer);
    destroy_bitmap(nave);
    destroy_bitmap(fondo);

    return 0;
}
END_OF_MAIN();
