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

c_Box_Small *Find_Box_Small(int &x, int &y) {
    for (int i = 0; i < c_Box_Small::Count; i++) {
        if (Box_Small[i].x == x && Box_Small[i].y == y)
            return &Box_Small[i];
    }
    return nullptr;
}

c_Box_Big *Find_Box_Big(int &x, int &y) {
    for (int i = 0; i < c_Box_Big::Count; i++) {
        if (Box_Big[i].x == x && Box_Big[i].y == y)
            return &Box_Big[i];
    }
    return nullptr;
}

bool Check_Win(int &x, int &y) {
    c_Box_Small *Small = Find_Box_Small(x, y);
    c_Box_Big *Big = Find_Box_Big(x, y);
    if (Small == nullptr || Big == nullptr)
        return false;
    if (Small->Type != GOAL || Big->Type != GOAL)
        return false;
    return true;
}

void Move(int Drt) {
    int x_Current = Player.x, y_Current = Player.y;
    int x_Next = Player.x + Drt_Offset[Drt].x, y_Next = Player.y + Drt_Offset[Drt].y;
    if (Map[y_Next][x_Next] != 1)
        return;
    c_Box_Small *Small_C = Find_Box_Small(x_Current, y_Current);
    c_Box_Big *Big_C = Find_Box_Big(x_Current, y_Current);
    c_Box_Small *Small_N = Find_Box_Small(x_Next, y_Next);
    c_Box_Big *Big_N = Find_Box_Big(x_Next, y_Next);
    int Reverse = Drt_Reverse[Drt];
    bool Undo_Small = false;
    if (Big_C != nullptr) {
        if (Big_C->Drt != Drt) {
            if (Small_N != nullptr || Big_N != nullptr)
                return;
            if (Small_C != nullptr && (Big_C->Drt != Reverse || Small_C->Drt != Drt)) {
                Undo_Small = true;
                Unit_Move_Func[Drt](Small_C);
            }
            Unit_Move_Func[Drt](Big_C);
            Unit_Move_Func[Drt](&Player);
            if (Check_Win(x_Next, y_Next))
                Game_Next_Level();
            List_Undo.push_front(new s_Undo(x_Current, y_Current, Undo_Small ? Small_C : nullptr, Big_C));
            glutPostRedisplay();
            return;
        }
    }
    if (Small_C != nullptr) {
        if (Small_C->Drt != Drt) {
            if (Small_N != nullptr || (Big_N != nullptr && Big_N->Drt != Reverse))
                return;
            Unit_Move_Func[Drt](Small_C);
            Unit_Move_Func[Drt](&Player);
            if (Check_Win(x_Next, y_Next))
                Game_Next_Level();
            List_Undo.push_front(new s_Undo(x_Current, y_Current, Small_C, nullptr));
            glutPostRedisplay();
            return;
        }
    }
    if (Small_N != nullptr && Small_N->Drt != Reverse)
        return;
    if (Big_N != nullptr && Big_N->Drt != Reverse)
        return;
    Unit_Move_Func[Drt](&Player);
    List_Undo.push_front(new s_Undo(x_Current, y_Current, nullptr, nullptr));
    glutPostRedisplay();
}
