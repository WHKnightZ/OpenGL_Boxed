#include "main.h"

void c_Unit::Dec_X() {
    x--;
    this->Rct.Left -= TILE_SIZE;
    this->Rct.Right -= TILE_SIZE;
}

void c_Unit::Dec_Y() {
    y--;
    this->Rct.Bottom -= TILE_SIZE;
    this->Rct.Top -= TILE_SIZE;
}

void c_Unit::Inc_X() {
    x++;
    this->Rct.Left += TILE_SIZE;
    this->Rct.Right += TILE_SIZE;
}

void c_Unit::Inc_Y() {
    y++;
    this->Rct.Bottom += TILE_SIZE;
    this->Rct.Top += TILE_SIZE;
}

void c_Player::Reload(int x, int y) {
    this->x = x;
    this->y = y;
    this->Rct.Left = Start_X + x * TILE_SIZE + Offset;
    this->Rct.Bottom = Start_Y + y * TILE_SIZE + Offset;
    this->Rct.Right = this->Rct.Left + Size;
    this->Rct.Top = this->Rct.Bottom + Size;
}

void c_Player::Draw() {
    glColor3fv(Color);
    Map_Texture(&Img);
    Draw_Rect(&this->Rct);
}

void c_Box_Small::Init(int x, int y, int Drt, int Type) {
    this->x = x;
    this->y = y;
    this->Drt = Drt;
    this->Type = Type;
    this->Rct.Left = Start_X + x * TILE_SIZE + Offset;
    this->Rct.Bottom = Start_Y + y * TILE_SIZE + Offset;
    this->Rct.Right = this->Rct.Left + Size;
    this->Rct.Top = this->Rct.Bottom + Size;
}

void c_Box_Small::Reload(int x, int y) {
    this->x = x;
    this->y = y;
    this->Rct.Left = Start_X + x * TILE_SIZE + Offset;
    this->Rct.Bottom = Start_Y + y * TILE_SIZE + Offset;
    this->Rct.Right = this->Rct.Left + Size;
    this->Rct.Top = this->Rct.Bottom + Size;
}

void c_Box_Small::Draw() {
    glColor3fv(Color[Type]);
    Map_Texture(&Img[Drt]);
    Draw_Rect(&this->Rct);
}

void c_Box_Big::Init(int x, int y, int Drt, int Type) {
    this->x = x;
    this->y = y;
    this->Drt = Drt;
    this->Type = Type;
    this->Rct.Left = Start_X + x * TILE_SIZE + Offset;
    this->Rct.Bottom = Start_Y + y * TILE_SIZE + Offset;
    this->Rct.Right = this->Rct.Left + Size;
    this->Rct.Top = this->Rct.Bottom + Size;
}

void c_Box_Big::Reload(int x, int y) {
    this->x = x;
    this->y = y;
    this->Rct.Left = Start_X + x * TILE_SIZE + Offset;
    this->Rct.Bottom = Start_Y + y * TILE_SIZE + Offset;
    this->Rct.Right = this->Rct.Left + Size;
    this->Rct.Top = this->Rct.Bottom + Size;
}

void c_Box_Big::Draw() {
    glColor3fv(Color[Type]);
    Map_Texture(&Img[Drt]);
    Draw_Rect(&this->Rct);
}
