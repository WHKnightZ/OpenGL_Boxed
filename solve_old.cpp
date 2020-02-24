#include "main.h"

#define MAX_STEP 50

enum RETURN_STATE {
    CANT_MOVE,
    ONLY_PLAYER,
    BOTH
};

struct s_Box {
    char Type, Drt;
};

struct s_Box_Coord {
    char x, y;
};

char Count_Small, Count_Big;
s_Box Small_T[MAX], Big_T[MAX];

struct s_Return {
    char State;
    char Small, Big;
};

class c_Case {
  public:
    c_Case() {
        Prev = nullptr;
    }
    c_Case(char x, char y, c_Case *p, s_Return *r, char Drt);
    int x, y, Drt, Sum;
    s_Box_Coord Small[MAX];
    s_Box_Coord Big[MAX];
    s_Return Return;
    c_Case *Prev;

    char Find_Small(char &x, char &y);
    char Find_Big(char &x, char &y);
    bool Check_Win(char &x, char &y);
    void Move(char x, char y, char Drt);
    bool BFS();
};

c_Case::c_Case(char x, char y, c_Case *p, s_Return *r, char Drt) {
    this->x = x;
    this->y = y;
    this->Drt = Drt;
    for (int i = 0; i < Count_Small; i++)
        Small[i] = p->Small[i];
    for (int i = 0; i < Count_Big; i++)
        Big[i] = p->Big[i];
    if (r->Small != -1) {
        Small[r->Small].x = x;
        Small[r->Small].y = y;
    }
    if (r->Big != -1) {
        Big[r->Big].x = x;
        Big[r->Big].y = y;
    }
    Sum = x + y;
    for (int i = 0; i < Count_Small; i++)
        Sum += (Small[i].x + Small[i].y);
    for (int i = 0; i < Count_Big; i++)
        Sum += (Big[i].x + Big[i].y);
    Prev = p;
}

char c_Case::Find_Small(char &x, char &y) {
    for (int i = 0; i < Count_Small; i++) {
        if (Small[i].x == x && Small[i].y == y)
            return i;
    }
    return -1;
}

char c_Case::Find_Big(char &x, char &y) {
    for (int i = 0; i < Count_Big; i++) {
        if (Big[i].x == x && Big[i].y == y)
            return i;
    }
    return -1;
}

bool c_Case::Check_Win(char &x, char &y) {
    char Small = Find_Small(x, y);
    char Big = Find_Big(x, y);
    if (Small == -1 || Big == -1)
        return false;
    if (Small_T[Small].Type != GOAL || Big_T[Big].Type != GOAL)
        return false;
    return true;
}

void c_Case::Move(char x, char y, char Drt) {
    Return.State = CANT_MOVE;
    char x_Next = x + Drt_Offset[Drt].x, y_Next = y + Drt_Offset[Drt].y;
    if (Map[y_Next][x_Next] != 1)
        return;
    char Small_C = Find_Small(x, y);
    char Big_C = Find_Big(x, y);
    char Small_N = Find_Small(x_Next, y_Next);
    char Big_N = Find_Big(x_Next, y_Next);
    char Reverse = Drt_Reverse[Drt];
    if (Big_C != -1) {
        if (Big_T[Big_C].Drt != Drt) {
            if (Small_N != -1 || Big_N != -1)
                return;
            Return.Small = -1;
            if (Small_C != -1 && (Big_T[Big_C].Drt != Reverse || Small_T[Small_C].Drt != Drt))
                Return.Small = Small_C;
            Return.Big = Big_C;
            Return.State = BOTH;
            return;
        }
    }
    if (Small_C != -1) {
        if (Small_T[Small_C].Drt != Drt) {
            if (Small_N != -1 || (Big_N != -1 && Big_T[Big_N].Drt != Reverse))
                return;
            Return.Small = Small_C;
            Return.Big = -1;
            Return.State = BOTH;
            return;
        }
    }
    if (Small_N != -1 && Small_T[Small_N].Drt != Reverse)
        return;
    if (Big_N != -1 && Big_T[Big_N].Drt != Reverse)
        return;
    Return.State = ONLY_PLAYER;
    return;
}

struct s_List {
    c_Case *Data;
    s_List *Next;
};

void Insert(s_List **List, c_Case *p) {
    s_List *l = new s_List();
    l->Data = p;
    l->Next = *List;
    *List = l;
}

s_List *List_Case[MAX_STEP];
int Count_Case = 0;
int Count_Per_Case[MAX_STEP];

bool Box_Coord_Equal(s_Box_Coord *p, s_Box_Coord *q) {
    if (p->x == q->x && p->y == q->y)
        return true;
    return false;
}

bool Case_Equal(c_Case *p, c_Case *q) {
    if (p->Sum != q->Sum)
        return false;
    if (p->x != q->x || p->y != q->y)
        return false;
    for (int i = 0; i < Count_Small; i++) {
        if (!Box_Coord_Equal(&p->Small[i], &q->Small[i]))
            return false;
    }
    for (int i = 0; i < Count_Big; i++)
        if (!Box_Coord_Equal(&p->Big[i], &q->Big[i]))
            return false;
    return true;
}

bool Check_In_List(c_Case *p) {
    s_List *ptr;
    for (int i = Count_Case; i >= 0; i--) {
        ptr = List_Case[i];
        while (ptr != nullptr) {
            if (Case_Equal(p, ptr->Data))
                return true;
            ptr = ptr->Next;
        }
    }
    return false;
}

bool c_Case::BFS() {
    bool Mark[MAX][MAX];
    char Max = MAX - 1;
    for (int i = 1; i < Max; i++)
        for (int j = 1; j < Max; j++)
            Mark[i][j] = false;
    Point Queue[36];
    int First = 0, Last = 0;
    Mark[y][x] = true;
    Point *q = &Queue[Last];
    q->x = x;
    q->y = y;
    Last++;
    int Count_Case_1 = Count_Case + 1;
    int *c = &Count_Per_Case[Count_Case_1];
    char x1, y1, x2, y2;
    while (First < Last) {
        q = &Queue[First];
        x1 = q->x;
        y1 = q->y;
        First++;
        for (int i = 0; i < 4; i++) {
            x2 = x1 + Drt_Offset[i].x;
            y2 = y1 + Drt_Offset[i].y;
            Move(x1, y1, i);
            if (Return.State == ONLY_PLAYER) {
                if (!Mark[y2][x2]) {
                    Mark[y2][x2] = true;
                    q = &Queue[Last];
                    q->x = x2;
                    q->y = y2;
                    Last++;
                }
            } else if (Return.State == BOTH) {
                c_Case *p = new c_Case(x2, y2, this, &Return, i);
                if (!Check_In_List(p)) {
                    Insert(&List_Case[Count_Case_1], p);
                    (*c)++;
                    if (p->Check_Win(x2, y2))
                        return true;
                } else
                    delete p;
            }
        }
    }
    return false;
}

struct s_Step {
    char x1, y1, x2, y2;
    s_Step(char x1, char y1, char x2, char y2) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
};

void Solve() {
    Count_Small = c_Box_Small::Count;
    Count_Big = c_Box_Big::Count;
    c_Case *p = new c_Case();
    for (int i = 0; i < Count_Small; i++) {
        Small_T[i].Type = Box_Small[i].Type;
        Small_T[i].Drt = Box_Small[i].Drt;
        p->Small[i].x = Box_Small[i].x;
        p->Small[i].y = Box_Small[i].y;
    }
    for (int i = 0; i < Count_Big; i++) {
        Big_T[i].Type = Box_Big[i].Type;
        Big_T[i].Drt = Box_Big[i].Drt;
        p->Big[i].x = Box_Big[i].x;
        p->Big[i].y = Box_Big[i].y;
    }
    p->x = Player.x;
    p->y = Player.y;
    Count_Case = 0;
    Count_Per_Case[0] = 1;
    List_Case[Count_Case] = nullptr;
    Insert(&List_Case[Count_Case], p);
    s_List *ptr;
    while (List_Case[Count_Case] != nullptr) {
        List_Case[Count_Case + 1] = nullptr;
        Count_Per_Case[Count_Case + 1] = 0;
        printf("*%d-%d\n", Count_Case, Count_Per_Case[Count_Case]);
        ptr = List_Case[Count_Case];
        while (ptr != nullptr) {
            if (ptr->Data->BFS()) {
                c_Case *Case = List_Case[Count_Case + 1]->Data;
                std::list<s_Step> List;
                printf("Answer:\n");
                while (Count_Case > -1) {
                    List.push_front(s_Step(Case->x - Drt_Offset[Case->Drt].x, Case->y - Drt_Offset[Case->Drt].y, Case->x, Case->y));
                    Case = Case->Prev;
                    Count_Case--;
                }
                for (std::list<s_Step>::iterator it = List.begin(); it != List.end(); it++)
                    printf("%d %d -> %d %d\n", it->x1, it->y1, it->x2, it->y2);
                return;
            }
            ptr = ptr->Next;
        }
        Count_Case++;
    }
}
