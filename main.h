#ifndef MAIN_H
#define MAIN_H

#include "../Library/loadpng.h"
#include "../Library/process_image.h"

#include <list>

#include <GL/glut.h>

#include "../Library/gl_texture.h"

/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
*/

#define WIDTH 600
#define HEIGHT 600
#define MAX 8
#define TILE_SIZE 70
#define MAX_BOX 16
#define LEVEL 7

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

struct Point {
    int x, y;
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
    static float Color[3];
    static Image Img;
    float Offset, Size;

    void Reload(int x, int y);
    void Draw();
};

float c_Player::Color[3] = {0.150f, 0.700f, 0.150f};
Image c_Player::Img;

c_Player Player;

class c_Box_Small : public c_Unit {
  public:
    static int Count;
    static float Color[2][3];
    static float Offset, Size;
    static Image Img[4];
    int Drt, Type;

    void Init(int x, int y, int Drt, int Type);
    void Reload(int x, int y);
    void Draw();
};

int c_Box_Small::Count = 0;
float c_Box_Small::Color[2][3] = {{0.125f, 0.125f, 0.125f}, {0.945f, 0.325f, 0.125f}};
float c_Box_Small::Offset;
float c_Box_Small::Size;
Image c_Box_Small::Img[4];

c_Box_Small Box_Small[MAX_BOX];

class c_Box_Big : public c_Unit {
  public:
    static int Count;
    static float Color[2][3];
    static float Offset, Size;
    static Image Img[4];
    int Drt, Type;

    void Init(int x, int y, int Drt, int Type);
    void Reload(int x, int y);
    void Draw();
};

int c_Box_Big::Count = 0;
float c_Box_Big::Color[2][3] = {{0.125f, 0.125f, 0.125f}, {0.125f, 0.325f, 0.945f}};
float c_Box_Big::Offset;
float c_Box_Big::Size;
Image c_Box_Big::Img[4];

c_Box_Big Box_Big[MAX_BOX];

struct s_Undo {
    int x, y;
    c_Box_Small *Small;
    c_Box_Big *Big;
    s_Undo(int x, int y, c_Box_Small *Small, c_Box_Big *Big) {
        this->x = x;
        this->y = y;
        this->Small = Small;
        this->Big = Big;
    }
};

std::list<s_Undo *> List_Undo;

// Prototype

void Unit_Move_Up(c_Unit *Unit);
void Unit_Move_Right(c_Unit *Unit);
void Unit_Move_Down(c_Unit *Unit);
void Unit_Move_Left(c_Unit *Unit);

// Function_Pointer
void (*Unit_Move_Func[])(c_Unit *Unit) = {Unit_Move_Up, Unit_Move_Right, Unit_Move_Down, Unit_Move_Left};

// Variable
Image Img_Tile[2];
Rect Rct;

int Level = LEVEL, Max_Level;
int Max_X, Max_Y;
float Start_X, Start_Y;

float Color_White[] = {1.0f, 1.0f, 1.0f};

int Map[MAX][MAX];

int Drt_Reverse[] = {DOWN, LEFT, UP, RIGHT};
Point Drt_Offset[4] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

// including all referenced .c files, you don't need to compile all of them
#include "class.cpp"
#include "init.cpp"
#include "move.cpp"
#include "solve.cpp"

#endif
