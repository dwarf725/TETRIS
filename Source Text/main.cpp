#include <SFML/Graphics.hpp>
#include "tetris Blocks.h"
#include "Header.h"
using namespace std; 
using namespace sf;

void Score(int LinesCleared, int& Score, int Level ) {
    Score = 100 * LinesCleared;
}

void LevelUp(int &Level, int Score, float& Speed) {
    Level++;

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


void drawgrid(char**& dgrid,RectangleShape**& grid, RenderWindow& win) {
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
        L->setTexture(&LTexture);;

        J = new RectangleShape;
        J->setSize(Vector2f(30.f, 30.f));
        J->setTexture(&JTexture);;

        O = new RectangleShape;
        O->setSize(Vector2f(30.f, 30.f));
        O->setTexture(&OTexture);;

        I = new RectangleShape;
        I->setSize(Vector2f(30.f, 30.f));
        I->setTexture(&ITexture);;


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

void lineClear(char**& grid,char**&dgrid,Tetrino& t,int &S, int Level) {
    int index = 0;
    bool valid = true, LineCleared = false;
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
            for (int z = 0; z < 10; z++) {
                grid[0][z] = '*';
                dgrid[0][z] = '*';

            }


            for (int w = 0; w < 4; w++) {
                int o = t.getCoord(w).GetX();
                int p = t.getCoord(w).GetY();
                if (0 >= 0 && o < 20 && p >= 0 && p < 10) {
                    grid[o][p] = '*';
                    dgrid[o][p] = '*';
                }
            }

            
        }
       
    }


   
}


void playermove(Tetrino* block, char**& grid) {
    if (sf::Keyboard::isKeyPressed(Keyboard::Key::A)) {
        block->Move(0, -1, grid);
    }
    if (sf::Keyboard::isKeyPressed(Keyboard::Key::S)) {
        block->Move(1, 0, grid);
    }
    if (sf::Keyboard::isKeyPressed(Keyboard::Key::D)) {
        block->Move(0, 1, grid);
    }
    if (sf::Keyboard::isKeyPressed(Keyboard::Key::W)) {
        block->Move(-1, 0, grid);
    }
}




int main() {
    Game g1;
    g1.game1();
    /*Clock AutoMove;
    int Speed = 1.5; 
    Clock MoveCooldown;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Tetris ");
    window.setFramerateLimit(60);
    float xpos = 0;
    float ypos = 0;
    int Score = 0; 
    Tetrino* T = new TBlock;
    Tetrino *Queue = new ZBlock;
    RectangleShape** grid = new RectangleShape*[20];
    char** drawinggrid = new char* [20];
    
    for (int i = 0; i < 20; i++) {
        drawinggrid[i] = new char[10];
    }
    
    for (int i = 0; i < 20; i++) {
        grid[i] = new RectangleShape[10];
    }
    char** backend = new char*[20];
    for (int i = 0; i < 20; i++) {
        backend[i] = new char[10];
    }
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            backend[i][j] = '*';
        }
    }

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
        xpos = 0;
        ypos += 30;
    }
    
    T->Create(backend);

    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if (backend[i][j] != 'A') {
                drawinggrid[i][j] = backend[i][j];
            }
        }
    }

    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::R) {
                    T->rotate(backend);
                }
            }
        }
   
        if (MoveCooldown.getElapsedTime().asSeconds() >0.07) {
            playermove(T, backend);
            MoveCooldown.restart();
        }

        if (AutoMove.getElapsedTime().asSeconds() > Speed) {
            T->Move(1, 0, backend);
            AutoMove.restart();
        }
 
        T->collision(backend,drawinggrid);
        lineClear(backend, drawinggrid, *T, Score);
        if (T->Getstatus() == false) {
            delete T;
            Spawn(Queue);
            if (Queue->getId() == 'T') {
                T = new TBlock;
            }
            else if(Queue->getId() == 'Z') {
                T = new ZBlock;
            }
            else if(Queue->getId() == 'S'){
                T = new SBlock;
            }
            else if(Queue->getId() == 'L'){
                T = new LBlock;
            }
            else if(Queue->getId() == 'O') {
                T = new OBlock; 
            }
            else if(Queue->getId() == 'I'){
                T = new IBlock;
            }
            else {
                T = new JBlock;
            }
            T->Create(backend);
            T->assign(Queue);
            delete Queue;
            Queue = new IBlock;             
        }
     
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
        window.display();
  
    }*/
	return 0;
}