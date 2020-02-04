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
    glColor3fv(Player_Color);
    Map_Texture(&Img_Player);
    Draw_Rect(&this->Rct);
}

c_Box_Small::c_Box_Small(int x, int y, int Drt, int Type) : c_Box(x, y) {
    this->Drt = Drt;
    this->Type = Type;
    this->Rct.Left = Start_X + x * TILE_SIZE + Box_Small_Offset;
    this->Rct.Bottom = Start_Y + y * TILE_SIZE + Box_Small_Offset;
    this->Rct.Right = this->Rct.Left + Box_Small_Size;
    this->Rct.Top = this->Rct.Bottom + Box_Small_Size;
}

void c_Box_Small::Reload(int x, int y) {
    this->x = x;
    this->y = y;
    this->Rct.Left = Start_X + x * TILE_SIZE + Box_Small_Offset;
    this->Rct.Bottom = Start_Y + y * TILE_SIZE + Box_Small_Offset;
    this->Rct.Right = this->Rct.Left + Box_Small_Size;
    this->Rct.Top = this->Rct.Bottom + Box_Small_Size;
}

void c_Box_Small::Draw() {
    glColor3fv(Box_Small_Color[Type]);
    Map_Texture(&Img_Box_Small[Drt]);
    Draw_Rect(&this->Rct);
}

c_Box_Big::c_Box_Big(int x, int y, int Drt, int Type) : c_Box(x, y) {
    this->Drt = Drt;
    this->Type = Type;
    this->Rct.Left = Start_X + x * TILE_SIZE + Box_Big_Offset;
    this->Rct.Bottom = Start_Y + y * TILE_SIZE + Box_Big_Offset;
    this->Rct.Right = this->Rct.Left + Box_Big_Size;
    this->Rct.Top = this->Rct.Bottom + Box_Big_Size;
}

void c_Box_Big::Reload(int x, int y) {
    this->x = x;
    this->y = y;
    this->Rct.Left = Start_X + x * TILE_SIZE + Box_Big_Offset;
    this->Rct.Bottom = Start_Y + y * TILE_SIZE + Box_Big_Offset;
    this->Rct.Right = this->Rct.Left + Box_Big_Size;
    this->Rct.Top = this->Rct.Bottom + Box_Big_Size;
}

void c_Box_Big::Draw() {
    glColor3fv(Box_Big_Color[Type]);
    Map_Texture(&Img_Box_Big[Drt]);
    Draw_Rect(&this->Rct);
}
