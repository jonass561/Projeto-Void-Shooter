#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include<time.h>

typedef enum{
    Tela_menu=0,
    Tela_jogo,
    Tela_gameover,

}TELAS;

typedef struct{
    Vector2 posicao;
    float velocidade;
    int vida;
    bool ativo;
}nave;

typedef struct{
    Vector2 posicao;
    float velocidade;
    float dano;
    bool ativo;
}Disparo;

typedef struct{
    Vector2 posicao;
    Vector2 velocidade;
    bool ativo;
    float raio;
    float angulo;
    float vida;
}met;

typedef struct{
    Vector2 posicao;
    int frame_atual,frames_total;
    float timer;
    bool ativo;
}explosao;



int main(void)
{
    srand(time(NULL));
    const int largura_tela=850;
    const int altura_tela=950;

    InitWindow(largura_tela,altura_tela,"projeto de jogo");
    InitAudioDevice();

//TEXTURAS-----------------------------------------------------------------------------------
    Texture2D sprite_nave=LoadTexture("Sprites/Ships/spaceShips_001.png");
    Texture2D sprite_met=LoadTexture("Seperated/astroid.png");
    Texture2D sprite_tiro=LoadTexture("PNG/Lasers/laserBlue16.png");
    Texture2D sprite_background=LoadTexture("Backgrounds/bd_space_seamless_fl1.png");
    Texture2D sprite_background2=LoadTexture("Backgrounds/bd_space_seamless_fl1.png");
    Texture2D sprite_background3=LoadTexture("Backgrounds/tela de morte.png");

    Texture2D frames_destruicao[7];
    frames_destruicao[0]=LoadTexture("PNG/ezgif-split/frame_0_delay-0.09s.png");
    frames_destruicao[1]=LoadTexture("PNG/ezgif-split/frame_1_delay-0.09s.png");
    frames_destruicao[2]=LoadTexture("PNG/ezgif-split/frame_2_delay-0.09s.png");
    frames_destruicao[3]=LoadTexture("PNG/ezgif-split/frame_3_delay-0.09s.png");
    frames_destruicao[4]=LoadTexture("PNG/ezgif-split/frame_4_delay-0.09s.png");
    frames_destruicao[5]=LoadTexture("PNG/ezgif-split/frame_5_delay-0.09s.png");
    frames_destruicao[6]=LoadTexture("PNG/ezgif-split/frame_6_delay-0.09s.png");
    frames_destruicao[7]=LoadTexture("PNG/ezgif-split/frame_7_delay-0.09s.png");

    Font minha_fonte=LoadFontEx("Fonte/upheaval/upheavtt.ttf",32,0,0);
    Font minha_fonte2=LoadFontEx("Fonte/fonte1/fonte_p.ttf",32,0,0);

    Texture2D frames_disparo[3];
    frames_disparo[0]=LoadTexture("PNG/Lasers/laser1.png");
    frames_disparo[1]=LoadTexture("PNG/Lasers/laser2.png");
    frames_disparo[2]=LoadTexture("PNG/Lasers/laser3.png");
    frames_disparo[3]=LoadTexture("PNG/Lasers/laser4.png");
//SONS----------------------------------------------------------------------------------------
    Music musica_fundo=LoadMusicStream("Sons/retro_wave_1/Retro Wave 1/musica-boa.mp3");
    SetMusicVolume(musica_fundo,0.5f);
    PlayMusicStream(musica_fundo);
    Sound som_tiro=LoadSound("Sons/Misc Lasers/Fire 1.mp3");
    SetSoundVolume(som_tiro,0.3f);
    Sound som_explosao=LoadSound("Sons/explosao.wav");
    SetSoundVolume(som_explosao,0.3f);
    Sound som_hit=LoadSound("Sons/Misc Lasers/Hit 1.mp3");
    SetSoundVolume(som_hit,0.5f);
    Sound som_morte=LoadSound("Sons/Misc Lasers/Game Over.mp3");
    SetSoundVolume(som_morte,0.5f);

//---------------------------------------------------------------------------------------------
    SetTargetFPS(60);

    nave nave_in={{400.0f,500.0f},5.0f,3};
    nave_in.vida=3;
    nave_in.ativo=true;
    Disparo tiro[4]={0};
    met meteoro[20]={0};
    explosao destruicao[10]={0};
    explosao tiro_an[4]={0};
    float fundo1=0.0f,fundo2=GetScreenHeight(),velocidade_fundo=5.0f;
    float score=0,limite=1000;
    int i,j,k;


    TELAS tela_atual=Tela_menu;


    while(!WindowShouldClose()){
            UpdateMusicStream(musica_fundo);

//TELAS-------------------------------------------------------------------------
        switch(tela_atual){
        case Tela_menu:
            fundo1+=velocidade_fundo;
            fundo2+=velocidade_fundo;

            if(fundo1>=GetScreenHeight()){
                fundo1=fundo2-GetScreenHeight();
            }
            if(fundo2>=GetScreenHeight()){
                fundo2=fundo1-GetScreenHeight();
            }


            if(IsKeyPressed(KEY_ENTER)|| IsKeyPressed(KEY_SPACE)){
                tela_atual=Tela_jogo;

                nave_in.vida=3.0f;
                nave_in.ativo=true;
                nave_in.posicao=(Vector2){400.f,960};
                score=0;
            }

        break;
        case Tela_jogo:

//NAVE---------------------------------------------------------------------

            if(nave_in.ativo){

                double tempo_ativo=GetTime();
                if(tempo_ativo<3.0){
                        nave_in.posicao.y-=3.0f;
                }


                float velocidade_atual=nave_in.velocidade;
                if(IsKeyDown(KEY_LEFT_SHIFT)||IsKeyDown(KEY_RIGHT_SHIFT)){
                    velocidade_atual+=3.5f;
                }
                if(IsKeyDown(KEY_RIGHT)|| IsKeyDown(KEY_D)){
                    nave_in.posicao.x+=velocidade_atual;
                }
                if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)){
                    nave_in.posicao.x-=velocidade_atual;
                }
                if(IsKeyDown(KEY_DOWN)|| IsKeyDown(KEY_S)){
                    nave_in.posicao.y+=velocidade_atual;
                }
                if(IsKeyDown(KEY_UP)||IsKeyDown(KEY_W)){
                    nave_in.posicao.y-=velocidade_atual;
                }

                float raio_nave=20.0f;

                if(nave_in.posicao.x<raio_nave){
                    nave_in.posicao.x=raio_nave;
                }
                if(nave_in.posicao.x>largura_tela-raio_nave){
                    nave_in.posicao.x=largura_tela-raio_nave;
                }

                if(nave_in.posicao.y<raio_nave){
                    nave_in.posicao.y=raio_nave;
                }
                if(nave_in.posicao.y>altura_tela-raio_nave){
                    nave_in.posicao.y=altura_tela-raio_nave;
                }
            }

//TIRO---------------------------------------------------------------------

            if(nave_in.ativo){
                if(IsKeyPressed(KEY_SPACE)){
                    for(i=0;i<4;i++){
                        if(!tiro[i].ativo){
                            tiro[i].ativo=true;
                            PlaySound(som_tiro);
                            tiro[i].velocidade=15.00f;
                            tiro[i].posicao.x=nave_in.posicao.x;
                            tiro[i].posicao.y=nave_in.posicao.y-15;
                            break;
                        }
                    }
                }
            }
            for(i=0;i<4;i++){
                if(tiro[i].ativo==true){
                    tiro[i].posicao.y-=tiro[i].velocidade;

                }
                if(tiro[i].posicao.y<0){
                    tiro[i].ativo=false;
                }
            }

//METEORO----------------------------------------------------------------------
            static float tempo_ac=0.0f, prox_s=2.0f;
            tempo_ac+= GetFrameTime();

            if(tempo_ac>=prox_s){

                for(i=0;i<20;i++){

                    if(!meteoro[i].ativo){
                        meteoro[i].ativo=true;
                        meteoro[i].raio=15.0f+(float)(rand()%300)/10.f;
                        meteoro[i].vida=(int)(meteoro[i].raio/15.0f);
                        meteoro[i].velocidade.y=8.0f-(meteoro[i].raio*0.08f);
                        meteoro[i].velocidade.x=-2.0f+(float)(rand()%6);
                        if(score>limite){
                            meteoro[i].velocidade.y+=0.2f;

                            limite+=1000;
                        }
                        meteoro[i].posicao.x=(float)(rand()%(int)GetScreenWidth());
                        meteoro[i].posicao.y=-30.f;
                        break;
                    }
                }
                tempo_ac=0.0f;
                prox_s=0.2f+(float)(rand()%7)/10.f;
            }
            for(i=0;i<20;i++){

                if(meteoro[i].ativo==true){
                    meteoro[i].posicao.y+=meteoro[i].velocidade.y;
                    meteoro[i].posicao.x+=meteoro[i].velocidade.x;
                    meteoro[i].angulo+=1.5f;

                    if(meteoro[i].angulo>=360.0f){
                        meteoro[i].angulo=0.0f;
                    }
                }
                if(meteoro[i].posicao.y>970.0f){
                    meteoro[i].ativo=false;
                }
            }
//FUNDO-------------------------------------------------------------------------
            fundo1+=velocidade_fundo;
            fundo2+=velocidade_fundo;

            if(fundo1>=GetScreenHeight()){
                fundo1=fundo2-GetScreenHeight();
            }
            if(fundo2>=GetScreenHeight()){
                fundo2=fundo1-GetScreenHeight();
            }

//ATIVANDO ANIMAÇÂO--------------------------------------------------------------------------------
            for(k=0;k<10;k++){
                if(destruicao[k].ativo){
                    destruicao[k].timer+=GetFrameTime();

                    if(destruicao[k].timer>=0.1f){
                        destruicao[k].timer=0.0f;
                        destruicao[k].frame_atual++;

                        if(destruicao[k].frame_atual>=destruicao[k].frames_total){
                            destruicao[k].ativo=false;
                        }
                    }
                }
            }
            for(k=0;k<4;k++){
                if(tiro_an[k].ativo){
                    tiro_an[k].timer+=GetFrameTime();

                    if(tiro_an[k].timer>=0.1f){
                        tiro_an[k].timer=0.0f;
                        tiro_an[k].frame_atual++;

                        if(tiro_an[k].frame_atual>=tiro_an[k].frames_total){
                            tiro_an[k].ativo=false;
                        }
                    }

                }
            }

//COLISÕES----------------------------------------------------------------------

            for(i=0;i<4;i++){
                if(tiro[i].ativo){
                    for(j=0;j<20;j++){
                        if(meteoro[j].ativo){
                            bool colidiu=CheckCollisionCircles(
                                tiro[i].posicao, 3.0f,
                                meteoro[j].posicao,meteoro[j].raio


                            );
                            if(colidiu){
                                meteoro[j].vida-=1.0f;
                                tiro[i].ativo=false;

                                for(k=0;k<4;k++){
                                    if(!tiro_an[k].ativo){
                                        tiro_an[k].ativo=true;
                                        tiro_an[k].posicao=tiro[i].posicao;
                                        tiro_an[k].frame_atual=0;
                                        tiro_an[k].frames_total=3;
                                        tiro_an[k].timer=0.0f;
                                        break;
                                    }
                                }

                                if(meteoro[j].vida<1){
                                    score+=5.0f*meteoro[j].raio;

                                    meteoro[j].ativo=false;

                                    for(k=0;k<10;k++){

                                        if(!destruicao[k].ativo){
                                            destruicao[k].ativo=true;
                                            PlaySound(som_explosao);
                                            destruicao[k].posicao=meteoro[j].posicao;
                                            destruicao[k].frame_atual=0;
                                            destruicao[k].frames_total=3;
                                            destruicao[k].timer=0.0f;
                                            break;
                                        }
                                    }

                                break;
                                }
                            }
                        }
                    }
                }
            }
            for(j=0;j<20;j++){
                if(meteoro[j].ativo){
                    bool colidiu_n=CheckCollisionCircles(nave_in.posicao,20.0f,meteoro[j].posicao,meteoro[j].raio);
                    if(colidiu_n){
                        meteoro[j].ativo=false;
                        nave_in.vida--;
                        for(k=0;k<10;k++){
                            if(!destruicao[k].ativo){
                                destruicao[k].ativo=true;
                                PlaySound(som_hit);
                                destruicao[k].posicao=meteoro[j].posicao;
                                destruicao[k].frame_atual=0;
                                destruicao[k].frames_total=3;
                                destruicao[k].timer=0.0f;
                                break;
                            }
                        }
                        if(nave_in.vida==0){
                            nave_in.ativo=false;
                            PlaySound(som_morte);
                            StopMusicStream(musica_fundo);
                            tela_atual=Tela_gameover;
                        }
                    }
                }
            }
        break;
        case Tela_gameover:
            if(IsKeyPressed(KEY_M)){
                tela_atual=Tela_menu;
                StopMusicStream(musica_fundo);
                PlayMusicStream(musica_fundo);
            }
        break;
        }

//DESENHO=======================================================================

        BeginDrawing();

        ClearBackground(BLACK);

            switch(tela_atual){
            case Tela_menu:

                Rectangle sourceRec2={0.0f,0.0f,(float)sprite_background2.width,(float)sprite_background2.height};
                Rectangle destRec3={0.0f,fundo1,(float)GetScreenWidth(),(float)GetScreenHeight()};
                Rectangle destRec4={0.0f,fundo2,(float)GetScreenWidth(),(float)GetScreenHeight()};
                Vector2 origin2={0.0f,0.0f};

                DrawTexturePro(sprite_background,sourceRec2,destRec3,origin2,0.0f,WHITE);
                DrawTexturePro(sprite_background,sourceRec2,destRec4,origin2,0.0f,WHITE);

                DrawTextEx(minha_fonte2,"Void Shooter",(Vector2){100,300},70,2.0f,RAYWHITE);
                DrawTextEx(minha_fonte,"Pressione ENTER para jogar",(Vector2){230,400},20,2.0f,YELLOW);


            break;

            case Tela_jogo:

                Rectangle sourceRec={0.0f,0.0f,(float)sprite_background.width,(float)sprite_background.height};
                Rectangle destRec1={0.0f,fundo1,(float)GetScreenWidth(),(float)GetScreenHeight()};
                Rectangle destRec2={0.0f,fundo2,(float)GetScreenWidth(),(float)GetScreenHeight()};
                Vector2 origin={0.0f,0.0f};

                DrawTexturePro(sprite_background,sourceRec,destRec1,origin,0.0f,WHITE);
                DrawTexturePro(sprite_background,sourceRec,destRec2,origin,0.0f,WHITE);


                DrawText(TextFormat("Score:%.0f",score),650.f,30.0f,30.0f,YELLOW);
//VIDA--------------------------------------------------------------------------
                for(i=0;i<nave_in.vida;i++){
                    Rectangle sourceRec={0.0f,0.0f,(float)sprite_nave.width,(float)sprite_nave.height};
                    float altura_vida=40.0f,largura_vida=40.0f;
                    float posicaovida_x=40.0+(i*50.0f),posicaovida_y=20.0f;

                    Rectangle destRec={posicaovida_x,posicaovida_y,altura_vida,largura_vida};
                    Vector2 origin={0.0f,0.0f};
                    DrawTexturePro(sprite_nave,sourceRec,destRec,origin,0.0f,WHITE);

                }
//NAVE--------------------------------------------------------------------------
                if(nave_in.ativo){

                    Rectangle sourceRec={0.0f,0.0f,(float)sprite_nave.width,(float)sprite_nave.height};
                    float largura_nave=40.0f,altura_nave=40.0f;
                    Rectangle destRec={nave_in.posicao.x,nave_in.posicao.y,largura_nave,altura_nave};
                    Vector2 origin={largura_nave/2.0f,altura_nave/2.0f};
                    DrawTexturePro(sprite_nave,sourceRec,destRec,origin,0.0,WHITE);
                }
//TIRO--------------------------------------------------------------------------
                for(i=0;i<4;i++){
                    if(tiro[i].ativo){
                        Rectangle sourceRec={0.0f,0.0f,(float)sprite_tiro.width,(float)sprite_tiro.height};
                        float largura_tiro=10.0f,altura_tiro=35.0f;
                        Rectangle destRec={tiro[i].posicao.x,tiro[i].posicao.y,largura_tiro,altura_tiro};
                        Vector2 origin={largura_tiro/2.0f,altura_tiro/2.0f};
                        DrawTexturePro(sprite_tiro,sourceRec,destRec,origin,0.0,WHITE);
                    }
                }
//METEORO-------------------------------------------------------------------------------------------------------------------------------------
                for(i=0;i<20;i++){
                    if(meteoro[i].ativo){
                        Rectangle sourceRec={0.0f,0.0f,(float)sprite_met.width,(float)sprite_met.height};
                        float tamanho=meteoro[i].raio*2.0f;

                        Rectangle destRec={meteoro[i].posicao.x,meteoro[i].posicao.y,tamanho,tamanho};
                        Vector2 origin={tamanho/2.0f,tamanho/2.0f};
                        DrawTexturePro(sprite_met,sourceRec,destRec,origin,meteoro[i].angulo,WHITE);
                    }
                }
//ANIMACOES------------------------------------------------------------------------------------------------------------------------------------
                for(i=0;i<10;i++){
                    if(destruicao[i].ativo){
                        int j=destruicao[i].frame_atual;

                        Rectangle sourceRec={0.0f,0.0f,(float)frames_destruicao[j].width,(float)frames_destruicao[j].height};
                        Rectangle destRec={destruicao[i].posicao.x,destruicao[i].posicao.y,140.0f,140.0f};
                        Vector2 origin={20.0f,20.0f};
                        DrawTexturePro(frames_destruicao[j],sourceRec,destRec,origin,0.0f,WHITE);
                    }
                }
                for(i=0;i<4;i++){
                    if(tiro_an[i].ativo){
                        int j=tiro_an[i].frame_atual;

                        Rectangle sourceRec={0.0f,0.0f,(float)frames_disparo[j].width,(float)frames_disparo[j].height};
                        Rectangle destRec={tiro_an[i].posicao.x,tiro_an[i].posicao.y,30.0f,30.0f};
                        Vector2 origin={20.0f,20.0f};
                        DrawTexturePro(frames_disparo[j],sourceRec,destRec,origin,0.0f,WHITE);
                    }
                }

            break;
            case Tela_gameover:

                Rectangle sourceRec3={0.0f,0.0f,(float)sprite_background3.width,(float)sprite_background3.height};
                Rectangle destRec={0.0f,0.0f,(float)GetScreenWidth(),(float)GetScreenHeight()};
                Vector2 origin3={0.0f,0.0f};
                DrawTexturePro(sprite_background3,sourceRec3,destRec,origin3,0.0f,WHITE);

                DrawTextEx(minha_fonte2,"FIM DE JOGO",(Vector2){130,350},60,2.0,RED);
                DrawTextEx(minha_fonte,"Pressione M para voltar ao menu",(Vector2){200,440},20,2.0f,RAYWHITE);

            break;

            }
        EndDrawing();
    }
    CloseWindow();
    CloseAudioDevice();
    UnloadMusicStream(musica_fundo);
    UnloadTexture(sprite_background);
    UnloadTexture(sprite_background2);
    UnloadTexture(sprite_background3);
    UnloadTexture(sprite_nave);
    UnloadTexture(sprite_met);
    UnloadFont(minha_fonte);
    UnloadFont(minha_fonte2);
    for(i=0;i<8;i++){
        UnloadTexture(frames_destruicao[i]);
    }
    for(i=0;i<4;i++){
        UnloadTexture(frames_disparo[i]);
    }
    return 0;

}
