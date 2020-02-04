#include "main.h"

void Unit_Move_Up(c_Unit *Unit) {
    Unit->Dec_Y();
}

void Unit_Move_Right(c_Unit *Unit) {
    Unit->Inc_X();
}

void Unit_Move_Down(c_Unit *Unit) {
    Unit->Inc_Y();
}

void Unit_Move_Left(c_Unit *Unit) {
    Unit->Dec_X();
}

int Check_Win(int Id_Small, int Id_Big) {
    if (Id_Small == -1 || Id_Big == -1)
        return 0;
    if (Box[Id_Small]->Type != GOAL || Box[Id_Big]->Type != GOAL)
        return 0;
    return 1;
}

void Move(int Drt) {
    int x_Current = Player.x, y_Current = Player.y;
    int x_Next = Player.x + Drt_Offset[Drt][0], y_Next = Player.y + Drt_Offset[Drt][1];
    if (Map[y_Next][x_Next] != 1)
        return;
    int *Id_Small_Current = &Map_Box_Small[y_Current][x_Current];
    int *Id_Big_Current = &Map_Box_Big[y_Current][x_Current];
    int *Id_Small_Next = &Map_Box_Small[y_Next][x_Next];
    int *Id_Big_Next = &Map_Box_Big[y_Next][x_Next];
    int Reverse = Drt_Reverse[Drt];
    if (*Id_Big_Current > -1) {
        if (Box[*Id_Big_Current]->Drt != Drt) {
            if (*Id_Small_Next != -1 || *Id_Big_Next != -1)
                return;
            if (*Id_Small_Current != -1 && (Box[*Id_Big_Current]->Drt != Reverse || Box[*Id_Small_Current]->Drt != Drt)) {
                Unit_Move_Func[Drt](Box[*Id_Small_Current]);
                *Id_Small_Next = *Id_Small_Current;
                *Id_Small_Current = -1;
            }
            Unit_Move_Func[Drt](Box[*Id_Big_Current]);
            *Id_Big_Next = *Id_Big_Current;
            *Id_Big_Current = -1;
            Unit_Move_Func[Drt](&Player);
            if (Check_Win(*Id_Small_Next, *Id_Big_Next))
                Game_Win();
            glutPostRedisplay();
            return;
        }
    }
    if (*Id_Small_Current > -1) {
        if (Box[*Id_Small_Current]->Drt != Drt) {
            if (*Id_Small_Next != -1 || (*Id_Big_Next != -1 && Box[*Id_Big_Next]->Drt != Reverse))
                return;
            Unit_Move_Func[Drt](Box[*Id_Small_Current]);
            *Id_Small_Next = *Id_Small_Current;
            *Id_Small_Current = -1;
            Unit_Move_Func[Drt](&Player);
            if (Check_Win(*Id_Small_Next, *Id_Big_Next))
                Game_Win();
            glutPostRedisplay();
            return;
        }
    }
    if (*Id_Small_Next != -1 && Box[*Id_Small_Next]->Drt != Reverse)
        return;
    if (*Id_Big_Next != -1 && Box[*Id_Big_Next]->Drt != Reverse)
        return;
    Unit_Move_Func[Drt](&Player);
    glutPostRedisplay();
}
