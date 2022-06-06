#include <iostream> // kni�nica iostream
#include <conio.h> // kni�nica conio.h (conInputOutput.h)
#include <windows.h> //kni�nica windows.h v�aka ktorej m��me hru spomali�

using namespace std;

bool gameOver; // premenn� gameOver bude boolean
const int width = 20; // premenn� width bude const integer (const = ned� sa zamie�a�)
const int height = 20; // premenn� height bude const integer
int x, y, fruitX, fruitY, score; // premenn� x, y, fruitX, fruitY a score bud� integer
int tailX[100], tailY[100]; // premenn� tailX a tailY bud� integer, s maxim�lnou hodnotou 100
int nTail; // premenn� nTail bude integer, d��ka chvostu had�ka
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN}; // enumera�n� premenn� eDirection ktor� m� hodnoty STOP = 0, LEFT, RIGHT, UP a DWON
eDirecton dir; //premenn� dir (direction)

void Setup() // funkcia Setup
{
    gameOver = false; // gameOver nastav�me na False
    dir = STOP; // dir nadobudne hodnotu STOP aby had�k na za�iatku hry st�l na mieste
    x = width / 2; // x nadobudne hodnotu 10 (polovica width)
    y = height / 2; // y nadobudne hodnotu 10 (polovica height)
    fruitX = rand() % width; // x-ova pozicia ovocia ktor� sa n�hodne spawne na hracej ploche
    fruitY = rand() % height; //y-ova pozicia ovocia ktor� sa n�hodne spawne na hracej ploche
    score = 0; // defaultn� sk�re je 0
}

void Draw() //funkcia Draw
{
    system("cls"); // konzola sa vy�ist� pred zapnut�m hry
    for (int i = 0; i < width+2; i++) // vykresl�me horn� stranu mapy
        cout << "#"; //strana bude vykreslen� ###
    cout << endl; //vykres�ovanie sa posunie o riadok ni��ie
 
    for (int i = 0; i < height; i++) 
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0) // ak premenn� j == 0, vykresl� n�m # na �av� okraj hracej ploche
                cout << "#"; // vykresl� n�m ###
            if (i == y && j == x) // ak i == y spolu aj j == x, vykresl� n�m hlavu hada
                cout << "O"; // vykresl� n�m O (Hlava hada)
            else if (i == fruitY && j == fruitX) //ak i == fruitY spolu aj j == fruitX, vykresl� n�m ovocie
                cout << "F"; // vykresli n�m F (Fruit)
            else
            {
                bool print = false; // premenn� print ktor� bude boolean s hodnotou false
                for (int k = 0; k < nTail; k++) // loop v ktorom premenn� k bude ma� d�ku chvostu
                {
                    if (tailX[k] == j && tailY[k] == i) // ak d�ka chvosta X sa zhoduje so s�radnicou j a z�rove� d�ka chvosta Y sa zhoduje so s�radnicou i
                    {
                        cout << "o"; // vykresl�me chvost ako o
                        print = true; // print sa zmen� na true ak sa vykresl� chvost had�ka
                    }
                }
                if (!print) // ak print ostane false
                    cout << " "; // vykresl� sa pr�zdnota
            }
                 
 
            if (j == width - 1) // ak premenn� j == width - 1 (19), vykresl� # na prav� okraj hracej plochy
                cout << "#"; // vykresl� n�m ###
        }
        cout << endl; //kreslenie prejde na �al�� riadok
    }
 
    for (int i = 0; i < width+2; i++) // vykresl�me doln� stranu mapy
        cout << "#"; // strana bude vykreslen� ###
    cout << endl; // vykres�ovanie prejde o riadok ni��ie
    cout << "Score:" << score << endl; // na obrazovke n�m to printne moment�lne sk�re
}

void Input()
{
    if (_kbhit()) // ak je stla�en� kl�vesa (kbhit = KeyBoardHIT)
    {
        switch (_getch()) // switch case (getch n�m vr�ti boolean hodnotu pod�a toho, �i sme stla�ili kl�vesu)
        {
        case 'a': // ak sme stla�ili a
            dir = LEFT; // hadik p�jde do�ava, premenne dir sa zmen� hodnota
            break; // case sa "breakne", �i�e hadik p�jde st�le v�avo
            
        case 'd': // ak sme stla�ili d
            dir = RIGHT; // hadik p�jde doprava, premenne dir sa zmen� hodnota
            break; // case sa "breakne", �ize hadik p�jde st�le vpravo
            
        case 'w': //ak sme stla�ili w
            dir = UP; // hadik p�jde hore, premenne dir sa zmen� hodnota
            break; // case sa "breakne", �ize hadik p�jde st�le hore
            
        case 's': // ak sme stla�ili s
            dir = DOWN; // hadik p�jde dole, premenne dir sa zmen� hodnota
            break; // case sa "breakne", �i�e hadik p�jde st�le dole
            
        case 'x': // ak sme stla�ili x
            gameOver = true; // hra sa skon��
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0]; // premenn� prevX, ktor� obsahuje minul� hodnotu X s�radnice za�iatku chvosta
    int prevY = tailY[0]; // premenn� prevY, ktor� obsahuje minul� hodnotu Y s�radnice za�iatku chvosta
    int prev2X, prev2Y; // premenn� prev2X, prev2Y, ktor� s� integer
    tailX[0] = x; // nastav�me aby prv� �as� chvostu sledovala ss�radnicu X (hlavu hada)
    tailY[0] = y; // nastav�me aby prv� �as� chvostu sledovala ss�radnicu Y (hlavu hada)
    for (int i = 1; i < nTail; i++) // loop na zv��ovanie chvostu had�ka
    {
        prev2X = tailX[i]; // prev2X bude ma� hodnotu moment�lnej s�radnice X za�iatku chvosta
        prev2Y = tailY[i]; // prev2Y nude ma� hodnotu moment�lnej s�radnice Y za�iatku chvosta
        tailX[i] = prevX; // zmen�me p�vodnu hodnotu na prevX
        tailY[i] = prevY; // zmen�me p�vodnu hodnotu na prevY
        prevX = prev2X; // aktualizujeme prevX na prev2X
        prevY = prev2Y; // aktualizujeme prevY na prev2Y
    }
    switch (dir) // zmen�me premenn� dir
    {
    case LEFT: // ak hadik p�jde v�avo
        x--; // hadikove s�radnice sa zmenia 
        break;
        
    case RIGHT: // ak hadik p�jde vpravo
        x++; //hadikove s�radnice sa zmenia
        break;
        
    case UP: // ak hadik p�jde hore
        y--; // hadikove s�radnice sa zmenia
        break;
        
    case DOWN: // ak hadik p�jde dole
        y++; // hadikove s�radnice sa zmenia
        break;
        
    default: // ni� sa nestane (xd)
        break;
    }
    
    if (x >= width) x = 0; else if (x < 0) x = width - 1; // ak x bude viac ako ��rka (20), x sa presunie na 0, a naopak
    if (y >= height) y = 0; else if (y < 0) y = height - 1; // ak y bude viac ako v��ka (20), y sa presunie na 0, a naopak
 
    for (int i = 0; i < nTail; i++) // loop ktor� prejde ka�d� �ast chvostu
        if (tailX[i] == x && tailY[i] == y) // ak sa hlava had�ka nab�ra s hociakou �as�ou chvostu
            gameOver = true; // hra skon�i
 
    if (x == fruitX && y == fruitY) // ak s�radnica hlavy hada je toto�n� so s�radnicou ovocia (ak hadik zje jedlo)
    {
        score += 10; // sk�re sa zv��i o 10
        fruitX = rand() % width; // x-ova pozicia ovocia ktor� sa n�hodne spawne na hracej ploche
    	fruitY = rand() % height; //y-ova pozicia ovocia ktor� sa n�hodne spawne na hracej ploche
        nTail++; // chvost sa zv��� o 1
    }
}
int main() // hlavn� hra
{
    Setup(); // povol�me funkciu Setup
    while (!gameOver) // pokia� neni koniec hry
    {
        Draw(); // povol�me funkcie Draw(), Input(), Logic()
        Input();
        Logic();
        Sleep(10); // spoma�uje hru
    }
    return 0;
}
