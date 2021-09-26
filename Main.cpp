# include <Siv3D.hpp> // OpenSiv3D v0.6.1
#include "CurrentMino.hpp"
#include "Field.hpp"
#include "Mino.hpp"
#include "NextMino.hpp"
#include "Player.hpp"
short Init[100][100];//仮 後で要修正

void game(){
    CurrentMino currentMino(0, Vec2(5, 0), -1, false);
    NextMino preNextMino(0, 1, 2);
    NextMino nextMino;
    Field field(Init);
    const Font font(30);
    Stopwatch time;
    time.start();
    const Audio audio(U"example/bgm.m4a");
    const Audio bgm(Audio::Stream,U"example/bgm.m4a", Loop::Yes);
    bgm.play();
    while (System::Update())
    {
        Stopwatch stopwatch;
        Stopwatch IsStop;
        stopwatch.start();
        bool outer_break = false;
        while (System::Update()) {
            field.DrawField();
            currentMino.DrawMino();
            preNextMino.DrawMino(font);
            currentMino.MoveMino(field.field);
            if (stopwatch.ms() >= 250) {
                if (!currentMino.IsConflict(Vec2(currentMino.pos.x, currentMino.pos.y + 1), field.field))currentMino.FreeFall(field.field);
                stopwatch.restart();
            }
            if (KeyX.down()) {
                currentMino.RightRotateMino(field.field);
            }
            if (KeyZ.down()) {
                currentMino.LeftRotateMino(field.field);
            }
            if (KeyEnter.down()) {
                currentMino.ForceFall(field.field);
                field.ConstructField(currentMino.pos, currentMino);
                field.VanishColumn();
                field.DrawField();
                currentMino = CurrentMino(preNextMino.second, Vec2(5, 0), currentMino.holdMinoNumber, false);
                double minoIndex = std::min(6, (int)(Random() * 7));
                preNextMino = NextMino(preNextMino.second, preNextMino.third, minoIndex);
                break;
            }
            if (KeyShift.down()) {
                if (!currentMino.isUsedHold) {
                    if (currentMino.holdMinoNumber != -1) {
                        currentMino = CurrentMino(currentMino.holdMinoNumber, Vec2(5, 0), currentMino.minoNumber, true);
                        break;
                    }
                    else {
                        currentMino = CurrentMino(preNextMino.second, Vec2(5, 0), currentMino.minoNumber, true);
                        preNextMino = NextMino(preNextMino.second, preNextMino.third, rand() % 7);
                        break;
                    }
                }
            }
            if (currentMino.IsStop(field.field))IsStop.start();
            else IsStop.reset();
            if (IsStop.ms() >= 1000 && currentMino.IsStop(field.field)) {
                IsStop.reset();
                if(currentMino.GameOver()) {
                    outer_break = true;
                    break;
                    bgm.stop();
                }
                field.ConstructField(currentMino.pos, currentMino);
                field.VanishColumn();
                field.DrawField();
                currentMino = CurrentMino(preNextMino.second, Vec2(5, 0), currentMino.holdMinoNumber, false);
                preNextMino = NextMino(preNextMino.second, preNextMino.third, rand() % 7);
                break;
            }
            font(U"Score:", field.score).draw(300, 320);
            font(U"Hold").draw(500, 50);
            if (currentMino.holdMinoNumber != -1) {
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        if (currentMino.mino[currentMino.holdMinoNumber][i][j] == 1) {
                            Rect(500 + j * 20, 100 + i * 20, 20, 20).draw(Color(64, 64, 255));
                        }
                    }
                }
            }
            else {
                font(U"NULL").draw(500, 100,Palette
                ::Red);
            }
        }
        if(outer_break) break;
    }
}


void Main()
{
    Window::SetFullscreen(true);
    Scene::SetBackground(Palette::Black);
    while(System::Update()){
        bool outer_break = false;
        while(System::Update()){
            static Font menu_font(70);
            static Font tetris_font(100);
            tetris_font(U"**Tetris**").draw(390,190,Palette::Yellow);
            menu_font(U"1:Play").draw(540,300,Palette::Green);
            menu_font(U"2:End").draw(540,380,Palette::Green);
            int Menu=0;
            if(Key1.down()) Menu=1;
            if(Key2.down()) Menu=2;
            if(Menu==1) break;
            if(Menu==2){
                outer_break = true;
                break;
            }
        }
        if(outer_break) break;
        game();
        while(System::Update()){
            static Font font(70);
            font(U"Game Over").drawAt(Scene::Center(),Palette::Red);
            font(U"Press Enter").draw(490,420,Palette::Red);
            if(KeyEnter.down()) break;
        }
    }
    
}
