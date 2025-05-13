#pragma once
#include <SFML/Graphics.hpp>
#include "tetris Blocks.h"
using namespace std;
using namespace sf; 
class Game {
protected:
    Tetrino* Queue;
    Tetrino* CurrentBlock;
    float xpos;
    float ypos;
    int Score;
    int Level;
    int LevelCap = 600; 
    float Speed;
    bool gamended; 
    bool QueueSpawned;
public:

    Game() {
        Queue = nullptr;
        CurrentBlock = nullptr;
        xpos = 500;
        ypos = 30;
        Score = 0;
        Level = 1;
        Speed = 1.50;
        gamended = false;
        QueueSpawned = false; 
    }

    void calc(int LinesCleared) {
        Score += 100 * LinesCleared;
        cout << "Score is: " << Score << endl;
        LevelUp();
    }

    void LevelUp() {
        if (Score >= LevelCap * Level) {
            Level++;
            Speed = Speed - 0.45;
            cout << "level Increased " << endl;
        }
    }

    void Spawn(Tetrino*& Queue) {
        srand(time(NULL));
        int chance = rand() % 7;
        if (chance == 0) {
            Queue = new IBlock;
        }
        else if (chance == 1) {
            Queue = new OBlock;
        }
        else if (chance == 2) {
            Queue = new TBlock;
        }
        else if (chance == 3) {
            Queue = new ZBlock;
        }
        else if (chance == 4) {
            Queue = new SBlock;
        }
        else if (chance == 5) {
            Queue = new LBlock;
        }
        else if (chance == 6) {
            Queue = new JBlock;
        }
    }


    void drawgrid(char**& dgrid, RectangleShape**& grid, RenderWindow& win) {
        RectangleShape* T;
        RectangleShape* Z;
        RectangleShape* S;
        RectangleShape* L;
        RectangleShape* J;
        RectangleShape* O;
        RectangleShape* I;

        Texture TTexture;
        TTexture.loadFromFile("TetrisPurple.png");
        Texture ZTexture;
        ZTexture.loadFromFile("TetrisGreen.png");
        Texture STexture;
        STexture.loadFromFile("TetrisRed.png");
        Texture LTexture;
        LTexture.loadFromFile("TetrisBlue.png");
        Texture JTexture;
        JTexture.loadFromFile("TetrisOrange.png");
        Texture OTexture;
        OTexture.loadFromFile("TetrisYellow.png");
        Texture ITexture;
        ITexture.loadFromFile("TetrisCyan.png");

        T = new RectangleShape;

        T->setSize(Vector2f(30.f, 30.f));
        T->setTexture(&TTexture);


        Z = new RectangleShape;
        Z->setSize(Vector2f(30.f, 30.f));
        Z->setTexture(&ZTexture);

        S = new RectangleShape;
        S->setSize(Vector2f(30.f, 30.f));
        S->setTexture(&STexture);

        L = new RectangleShape;
        L->setSize(Vector2f(30.f, 30.f));
        L->setTexture(&LTexture);

        J = new RectangleShape;
        J->setSize(Vector2f(30.f, 30.f));
        J->setTexture(&JTexture);

        O = new RectangleShape;
        O->setSize(Vector2f(30.f, 30.f));
        O->setTexture(&OTexture);

        I = new RectangleShape;
        I->setSize(Vector2f(30.f, 30.f));
        I->setTexture(&ITexture);


        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                if (dgrid[i][j] == 'T') {
                    T->setPosition(grid[i][j].getPosition());
                    win.draw(*T);

                }
            }
        }

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                if (dgrid[i][j] == 'Z') {
                    Z->setPosition(grid[i][j].getPosition());
                    win.draw(*Z);

                }
            }
        }

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                if (dgrid[i][j] == 'S') {
                    S->setPosition(grid[i][j].getPosition());
                    win.draw(*S);

                }
            }
        }

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                if (dgrid[i][j] == 'L') {
                    L->setPosition(grid[i][j].getPosition());
                    win.draw(*L);

                }
            }
        }

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                if (dgrid[i][j] == 'J') {
                    J->setPosition(grid[i][j].getPosition());
                    win.draw(*J);

                }
            }
        }

        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                if (dgrid[i][j] == 'O') {
                    O->setPosition(grid[i][j].getPosition());
                    win.draw(*O);

                }
            }
        }


        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                if (dgrid[i][j] == 'I') {
                    I->setPosition(grid[i][j].getPosition());
                    win.draw(*I);

                }
            }
        }
    }

    void lineClear(char**& grid, char**& dgrid, Tetrino& t) {
        int index = 0;
        bool valid = true;
        int linesCleared = 0;


        for (int i = 19; i >= 0; i--) {
            index = 0;
            valid = true;


            for (int j = 0; j < 10; j++) {
                if (grid[i][j] != 'A') {
                    valid = false;
                }


            }

            if (valid == true) {
                linesCleared++;
                index = i;
                for (int x = index - 1; x >= 0; x--) {
                    for (int y = 0; y < 10; y++) {
                        grid[x + 1][y] = grid[x][y];
                        dgrid[x + 1][y] = dgrid[x][y];

                    }
                }
                i++;

                for(int z = 0; z < 10; z++) {
                   grid[0][z] = '*';
                   dgrid[0][z] = '*';

                }


    


            }

        }
        if (linesCleared != 0) {
            cout << "Lines Cleared = " << linesCleared << endl;
            calc(linesCleared);
        }
    }


    void virtual playermove(Tetrino* block, char**& grid) {
        if (sf::Keyboard::isKeyPressed(Keyboard::Key::A)) {
            block->Move(0, -1, grid);
        }
        if (sf::Keyboard::isKeyPressed(Keyboard::Key::S)) {
            block->Move(1, 0, grid);
        }
        if (sf::Keyboard::isKeyPressed(Keyboard::Key::D)) {
            block->Move(0, 1, grid);
        }
    }

    void Endscreen() {

    }


    void game1() {
        Font font;
        font.loadFromFile("Fonts/Retro60Prime.ttf");

        Text text;
        text.setFont(font);
        text.setCharacterSize(50);
        text.setString("GAME OVER");
        text.setPosition(400.0f, 300.0f);
        text.setFillColor(Color::Red);

        Text TScore;
        TScore.setFont(font);
        TScore.setCharacterSize(18);
        TScore.setPosition(875.0f, 250.0f);
        TScore.setFillColor(Color::White);
        
        Text TLevel;
        TLevel.setFont(font);
        TLevel.setCharacterSize(18);
        TLevel.setPosition(875.0f, 350.0f);
        TLevel.setFillColor(Color::White);

        Text TQueue;
        TQueue.setFont(font);
        TQueue.setCharacterSize(18);
        TQueue.setPosition(75.f, 80.0f);
        TQueue.setFillColor(Color::White);
        TQueue.setString("Queue: ");

        RectangleShape Item;
        Item.setSize(Vector2f(150.f,80.f));
        Item.setPosition(Vector2f(150.f, 200.f));

        Texture IT;
        IT.loadFromFile("Tblock.png");
        Texture IZ;
        IZ.loadFromFile("Zblock.png");
        Texture IS;
        IS.loadFromFile("Sblock.png");
        Texture IL;
        IL.loadFromFile("Lblock.png");
        Texture IJ;
        IJ.loadFromFile("Jblock.png");
        Texture IO;
        IO.loadFromFile("Oblock.png");
        Texture II;
        II.loadFromFile("Iblock.png");

        RectangleShape QUEUE;
        QUEUE.setSize(Vector2f(200.f, 200.f));
        QUEUE.setPosition(Vector2f(150.f, 150.f));
        QUEUE.setFillColor(Color::Transparent);
        QUEUE.setOutlineColor(Color::White);
        QUEUE.setOutlineThickness(4);
        
            Clock AutoMove;
            Clock MoveCooldown;
            sf::RenderWindow window(sf::VideoMode(1280, 720), "Tetris ");
            window.setFramerateLimit(60);
                RectangleShape** grid = new RectangleShape * [20];
                Spawn(CurrentBlock);
                Spawn(Queue);
                char** drawinggrid = new char* [20];
                for (int i = 0; i < 20; i++) {
                    drawinggrid[i] = new char[10];
                }

                for (int i = 0; i < 20; i++) {
                    grid[i] = new RectangleShape[10];
                }
                char** backend = new char* [20];
                for (int i = 0; i < 20; i++) {
                    backend[i] = new char[10];
                }
                for (int i = 0; i < 20; i++) {
                    for (int j = 0; j < 10; j++) {
                        backend[i][j] = '*';
                    }
                }
                CurrentBlock->Create(backend,gamended);
                for (int i = 0; i < 20; i++) {
                    for (int j = 0; j < 10; j++) {
                        grid[i][j].setSize(Vector2f(30.f, 30.f));
                    }
                }

                for (int i = 0; i < 20; i++) {
                    for (int j = 0; j < 10; j++) {
                        grid[i][j].setPosition(Vector2f(xpos, ypos));
                        xpos += 30;
                    }
                    xpos = 500;
                    ypos += 30;
                }
                for (int i = 0; i < 20; i++) {
                    for (int j = 0; j < 10; j++) {
                        if (backend[i][j] != 'A') {
                            drawinggrid[i][j] = backend[i][j];
                        }
                    }
                }
                Spawn(Queue);
                while (window.isOpen())
                {

                    sf::Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                            window.close();

                        if (event.type == Event::KeyPressed) {
                            if (event.key.code == Keyboard::R) {
                                CurrentBlock->rotate(backend);
                            }
                        }
                    }

                    CurrentBlock->collision(backend, drawinggrid);


                    lineClear(backend, drawinggrid, *CurrentBlock);
                    TScore.setString("SCORE:: " + to_string(Score));
                    TLevel.setString("Level:: " + to_string(Level));
                    
                    if (QueueSpawned == false) {
                        Spawn(Queue);
                        QueueSpawned = true;
                    }

                    if (Queue->getId() == 'T') {
                        Item.setTexture(&IT);
                    }
                    else if (Queue->getId() == 'Z') {
                        Item.setTexture(&IZ);
                    }
                    else if (Queue->getId() == 'S') {
                        Item.setTexture(&IS);
                    }
                    else if (Queue->getId() == 'L') {
                        Item.setTexture(&IL);
                    }
                    else if (Queue->getId() == 'O') {
                        Item.setTexture(&IO);
                    }
                    else if (Queue->getId() == 'I') {
                        Item.setTexture(&II);
                    }
                    else {
                        Item.setTexture(&IJ);;
                    }



                    if (CurrentBlock->Getstatus() == false) {
                        
                   

                        delete CurrentBlock;                    
                        if (Queue->getId() == 'T') {
                            CurrentBlock = new TBlock;
                        }
                        else if (Queue->getId() == 'Z') {
                            CurrentBlock = new ZBlock;
                        }
                        else if (Queue->getId() == 'S') {
                            CurrentBlock = new SBlock;
                        }
                        else if (Queue->getId() == 'L') {
                            CurrentBlock = new LBlock;
                        }
                        else if (Queue->getId() == 'O') {
                            CurrentBlock = new OBlock;
                        }
                        else if (Queue->getId() == 'I') {
                            CurrentBlock = new IBlock;
                        }
                        else {
                            CurrentBlock = new JBlock;
                        }
                        CurrentBlock->Create(backend,gamended);
                        CurrentBlock->assign(Queue);
                        delete Queue;
                        QueueSpawned = false;
                    }
                  
                   

                    if (MoveCooldown.getElapsedTime().asSeconds() > 0.07) {
                        playermove(CurrentBlock, backend);
                        MoveCooldown.restart();
                    }

                    if (AutoMove.getElapsedTime().asSeconds() > Speed) {
                        CurrentBlock->Move(1, 0, backend);
                        AutoMove.restart();
                    }

               

                    if (gamended == false) {
                        window.clear();
                        for (int i = 0; i < 20; i++) {
                            for (int j = 0; j < 10; j++) {
                                window.draw(grid[i][j]);
                            }
                        }

                        for (int i = 0; i < 20; i++) {
                            for (int j = 0; j < 10; j++) {
                                if (backend[i][j] != 'A') {
                                    drawinggrid[i][j] = backend[i][j];
                                }
                            }
                        }

                        drawgrid(drawinggrid, grid, window);
                        window.draw(TQueue);
                        window.draw(QUEUE);
                        window.draw(TScore);
                        window.draw(Item);
                        window.draw(TLevel);
                        window.display();
                    }
                    else{
                        window.clear();
                        window.draw(text);
                        window.display();
                    }
                }


    }

};
