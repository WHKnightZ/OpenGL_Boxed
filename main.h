#ifndef MAIN_H
#define MAIN_H

#include "../../Library/loadpng.h"
#include "../../Library/process_image.h"

#include <GL/glut.h>

#include "../../Library/gl_texture.h"

/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
*/

#define WIDTH 600
#define HEIGHT 600
#define MAX 8
#define TILE_SIZE 70
#define MAX_BOX 20
#define LEVEL 1

int POS_X, POS_Y;

enum GAME_STATE {
    GAME_STT
};

enum DIRECTION {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

enum BOX_TYPE {
    NORMAL,
    GOAL
};

class c_Unit {
  public:
    int x, y;
    Rect Rct;
    void Dec_X();
    void Dec_Y();
    void Inc_X();
    void Inc_Y();
};

class c_Player : public c_Unit {
  public:
    float Offset, Size;
    void Reload(int x, int y);
    void Draw();
};
c_Player Player;
float Player_Color[] = {0.150f, 0.700f, 0.150f};

class c_Box : public c_Unit {
  public:
    c_Box(int x, int y) {
        this->x = x;
        this->y = y;
    }
    static int Count;
    int Drt, Type;
    virtual void Reload(int x, int y) {}
    virtual void Draw() {}
};
int c_Box::Count = 0;

class c_Box_Small : public c_Box {
  public:
    c_Box_Small(int x, int y, int Drt, int Type);
    void Reload(int x, int y);
    void Draw();
};
float Box_Small_Offset, Box_Small_Size;
float Box_Small_Color[2][3] = {{0.125f, 0.125f, 0.125f}, {0.945f, 0.325f, 0.125f}};

class c_Box_Big : public c_Box {
  public:
    c_Box_Big(int x, int y, int Drt, int Type);
    void Reload(int x, int y);
    void Draw();
};
float Box_Big_Offset, Box_Big_Size;
float Box_Big_Color[2][3] = {{0.125f, 0.125f, 0.125f}, {0.125f, 0.325f, 0.945f}};

c_Box *Box[MAX_BOX];

// Prototype

// main.h

void Unit_Move_Up(c_Unit *Unit);
void Unit_Move_Right(c_Unit *Unit);
void Unit_Move_Down(c_Unit *Unit);
void Unit_Move_Left(c_Unit *Unit);

// Function_Pointer
void (*Unit_Move_Func[])(c_Unit *Unit) = {Unit_Move_Up, Unit_Move_Right, Unit_Move_Down, Unit_Move_Left};

// Variable
Image Img_Tile[2];
Image Img_Player, Img_Box_Small[4], Img_Box_Big[4];
Rect Rct;

int Level = LEVEL;
int Max_X, Max_Y;
float Start_X, Start_Y;

float Color_White[] = {1.0f, 1.0f, 1.0f};

int Map[MAX][MAX], Map_Box_Small[MAX][MAX], Map_Box_Big[MAX][MAX];

int Drt_Reverse[] = {DOWN, LEFT, UP, RIGHT};
int Drt_Offset[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

// including all referenced .c files, you don't need to compile all of them
#include "afunc.cpp"
#include "class.cpp"
#include "init.cpp"
#include "move.cpp"

#endif
