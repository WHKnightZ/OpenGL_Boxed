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
    for (int i = 0; i < c_Box::Count; i++)
        Box[i]->Draw();
    glutSwapBuffers();
}

void Resize(int x, int y) {
    glutPositionWindow(POS_X, POS_Y);
    glutReshapeWindow(WIDTH, HEIGHT);
}

void Special(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        Move(UP);
        break;
    case GLUT_KEY_RIGHT:
        Move(RIGHT);
        break;
    case GLUT_KEY_DOWN:
        Move(DOWN);
        break;
    case GLUT_KEY_LEFT:
        Move(LEFT);
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
    glutSpecialFunc(Special);
    glutMainLoop();
    return 0;
}
