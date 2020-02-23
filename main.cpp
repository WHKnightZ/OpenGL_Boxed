#include "main.h"

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3fv(Color_White);
    for (int i = 0; i < Max_Y; i++) {
        for (int j = 0; j < Max_X; j++) {
            if (Map[i][j] >= 0) {
                Map_Texture(&Img_Tile[Map[i][j]]);
                Rct.Left = Start_X + j * TILE_SIZE;
                Rct.Bottom = Start_Y + i * TILE_SIZE;
                Rct.Right = Rct.Left + TILE_SIZE;
                Rct.Top = Rct.Bottom + TILE_SIZE;
                Draw_Rect(&Rct);
            }
        }
    }
    Player.Draw();
    for (int i = 0; i < c_Box_Small::Count; i++)
        Box_Small[i].Draw();
    for (int i = 0; i < c_Box_Big::Count; i++)
        Box_Big[i].Draw();
    glutSwapBuffers();
}

void Resize(int x, int y) {
    glutPositionWindow(POS_X, POS_Y);
    glutReshapeWindow(WIDTH, HEIGHT);
}

void Keyboard(GLubyte key, int x, int y) {
    switch (key) {
    case 'w':
        Move(UP);
        break;
    case 'd':
        Move(RIGHT);
        break;
    case 's':
        Move(DOWN);
        break;
    case 'a':
        Move(LEFT);
        break;
    case 'q':
        Undo();
        break;
    case 'e':
        Game_Prev_Level();
        break;
    case 'r':
        Game_Restart_Level();
        break;
    case 't':
        Game_Next_Level();
        break;
    case 'f':
        Solve();
        break;
    }
}

int main(int argc, char **argv) {
    Init_Game();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) >> 1;
    POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) >> 1;
    glutInitWindowPosition(POS_X, POS_Y);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Boxed");
    Init_GL();
    glutDisplayFunc(Display);
    glutReshapeFunc(Resize);
    glutKeyboardFunc(Keyboard);
    glutMainLoop();
    return 0;
}
