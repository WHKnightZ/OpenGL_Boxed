#include "main.h"

void Image_Draw_Rect(Image *Img, int x, int y, int w, int h, int Color[]) {
    int w4 = Img->w * 4;
    int offset = w4 - w * 4;
    Image_Data img = Img->img + w4 * y + x * 4;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            *img++ = Color[0];
            *img++ = Color[1];
            *img++ = Color[2];
            *img++ = 255;
        }
        img += offset;
    }
}

void Image_Draw_Rect(Image *Img, int x, int y, int w, int h, int Color_Main[], int Color_Aux[]) {
    int Color[2][3] = {
        {Color_Main[0], Color_Main[1], Color_Main[2]},
        {Color_Aux[0], Color_Aux[1], Color_Aux[2]}};
    int k, *c, w4 = Img->w * 4;
    int offset = w4 - w * 4;
    Image_Data img = Img->img + w4 * y + x * 4;
    for (int i = 0; i < h; i++) {
        k = i % 2;
        for (int j = 0; j < w; j++) {
            c = &Color[k][0];
            *img++ = c[0];
            *img++ = c[1];
            *img++ = c[2];
            *img++ = 255;
            k = 1 - k;
        }
        img += offset;
    }
}

void Image_Draw_Wall() {
    int x = 10;
    int x_Max = TILE_SIZE - x;
    Create_Image(&Img_Tile[0], TILE_SIZE, TILE_SIZE);
    int Color_Main[] = {0, 0, 0};
    int Color_Aux[] = {96, 96, 96};
    Image_Draw_Rect(&Img_Tile[0], 0, 0, x_Max, x_Max, Color_Aux);
    Image_Draw_Rect(&Img_Tile[0], x, x, x_Max, x_Max, Color_Main);
    Image_Draw_Rect(&Img_Tile[0], x, x, x_Max - x, x_Max - x, Color_Main, Color_Aux);
}

void Image_Draw_Space() {
    Create_Image(&Img_Tile[1], TILE_SIZE, TILE_SIZE);
    int Color_Main[] = {192, 192, 192};
    int Color_Aux[] = {192, 255, 255};
    int Width = 20, Thickness = 7;
    Image_Draw_Rect(&Img_Tile[1], 0, 0, Width, Thickness, Color_Main, Color_Aux);
    Image_Draw_Rect(&Img_Tile[1], TILE_SIZE - Width, 0, Width, Thickness, Color_Main, Color_Aux);
    Image_Draw_Rect(&Img_Tile[1], 0, Thickness, Thickness, Width - Thickness, Color_Main, Color_Aux);
    Image_Draw_Rect(&Img_Tile[1], TILE_SIZE - Thickness, Thickness, Thickness, Width - Thickness, Color_Main, Color_Aux);
    Image_Draw_Rect(&Img_Tile[1], 0, TILE_SIZE - Thickness, Width, Thickness, Color_Main, Color_Aux);
    Image_Draw_Rect(&Img_Tile[1], TILE_SIZE - Width, TILE_SIZE - Thickness, Width, Thickness, Color_Main, Color_Aux);
    Image_Draw_Rect(&Img_Tile[1], 0, TILE_SIZE - Width, Thickness, Width - Thickness, Color_Main, Color_Aux);
    Image_Draw_Rect(&Img_Tile[1], TILE_SIZE - Thickness, TILE_SIZE - Width, Thickness, Width - Thickness, Color_Main, Color_Aux);
}

void Image_Draw_Box_Small() {
    int Color[] = {255, 255, 255};
    int Width = 34, Thickness = 6;
    Create_Image(&Img_Box_Small[UP], Width, Width);
    Swap_Image(Img_Box_Small[UP].img, Width, Width);
    Image_Draw_Rect(&Img_Box_Small[UP], 0, 0, Thickness, Width, Color);
    Image_Draw_Rect(&Img_Box_Small[UP], Width - Thickness, 0, Thickness, Width, Color);
    Image_Draw_Rect(&Img_Box_Small[UP], Thickness, Width - Thickness, Width - 2 * Thickness, Thickness, Color);
    Box_Small_Offset = (TILE_SIZE - Width) / 2.0f;
    Box_Small_Size = Width;
    Rotate_Left(&Img_Box_Small[UP], &Img_Box_Small[LEFT]);
    Rotate_Right(&Img_Box_Small[UP], &Img_Box_Small[RIGHT]);
    Rotate_180(&Img_Box_Small[UP], &Img_Box_Small[DOWN]);
}

void Image_Draw_Box_Big() {
    int Color[] = {255, 255, 255};
    int Width = 56, Thickness = 6;
    Create_Image(&Img_Box_Big[UP], Width, Width);
    Image_Draw_Rect(&Img_Box_Big[UP], 0, 0, Thickness, Width, Color);
    Image_Draw_Rect(&Img_Box_Big[UP], Width - Thickness, 0, Thickness, Width, Color);
    Image_Draw_Rect(&Img_Box_Big[UP], Thickness, Width - Thickness, Width - 2 * Thickness, Thickness, Color);
    Box_Big_Offset = (TILE_SIZE - Width) / 2.0f;
    Box_Big_Size = Width;
    Rotate_Left(&Img_Box_Big[UP], &Img_Box_Big[LEFT]);
    Rotate_Right(&Img_Box_Big[UP], &Img_Box_Big[RIGHT]);
    Rotate_180(&Img_Box_Big[UP], &Img_Box_Big[DOWN]);
}

void Image_Draw_Player() {
    int Color[] = {255, 255, 255};
    int Width = 14;
    Create_Image(&Img_Player, Width, Width);
    Image_Draw_Rect(&Img_Player, 0, 0, Width, Width, Color);
    Player.Offset = (TILE_SIZE - Width) / 2.0f;
    Player.Size = Width;
}

int Load_Map() {
    char Str[40];
    sprintf(Str, "Maps/%02d.txt", Level);
    FILE *f = fopen(Str, "r");
    if (f == NULL)
        return 0;
    fscanf(f, "%d%d", &Max_X, &Max_Y);
    for (int i = 0; i < Max_Y; i++) {
        for (int j = 0; j < Max_X; j++) {
            fscanf(f, "%d", &Map[i + 1][j + 1]);
            Map_Box_Small[i + 1][j + 1] = Map_Box_Big[i + 1][j + 1] = -1;
        }
    }
    Max_X++;
    Max_Y++;
    for (int i = 0; i <= Max_X; i++)
        Map[0][i] = Map[Max_Y][i] = 0;
    for (int i = 1; i < Max_Y; i++)
        Map[i][0] = Map[i][Max_X] = 0;
    Max_X++;
    Max_Y++;
    Start_X = (WIDTH - Max_X * TILE_SIZE) / 2.0f;
    Start_Y = (HEIGHT - Max_Y * TILE_SIZE) / 2.0f;
    int x, y, Drt, Type, n, k = 0;
    fscanf(f, "%d%d", &x, &y);
    Player.Reload(x + 1, y + 1);
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d%d%d%d", &x, &y, &Drt, &Type);
        Box[k] = new c_Box_Small(++x, ++y, Drt, Type);
        Map_Box_Small[y][x] = k;
        k++;
    }
    fscanf(f, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d%d%d%d", &x, &y, &Drt, &Type);
        Box[k] = new c_Box_Big(++x, ++y, Drt, Type);
        Map_Box_Big[y][x] = k;
        k++;
    }
    c_Box::Count = k;
    fclose(f);
    return 1;
}

void Init_Game() {
    Image_Draw_Wall();
    Image_Draw_Space();
    Image_Draw_Player();
    Image_Draw_Box_Small();
    Image_Draw_Box_Big();
    Load_Map();
}

void Init_GL() {
    glClearColor(0.75f, 1.00f, 1.00f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, WIDTH, HEIGHT);
    gluOrtho2D(0, WIDTH, HEIGHT, 0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glutIgnoreKeyRepeat(GL_TRUE);
    glEnable(GL_TEXTURE_2D);
}

void Game_Win() {
    Level++;
    if (!Load_Map()) {
        Level = 1;
        Load_Map();
    }
}
