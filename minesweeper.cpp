#include<iostream>

using namespace std;

void reveal(int, int);  
void create_mine_positions();
void cell_number();
void create_table(); 
void open_cell(); 
void game();
void print_table(char); 

char table[10][10]; 
char table_mine_positions[10][10]; 
char symbol; 
int flag_counter = 0;
int mines_flagged_counter = 0;
bool end_game_lose = false;

void cell_number(int i, int j)
{
    if (i >= 0 && i < 10 && j >= 0 && j < 10 && table_mine_positions[i][j] != 'B')
        table_mine_positions[i][j]++;
}

void create_mine_positions()
{
    int counter = 0;
    srand( time(NULL));

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            table_mine_positions[i][j] = '0';

    int i = 0;
    int j = 0;
    while (counter < 10)
    {
        int i = rand() % 10;
        int j = rand() % 10;
        if (table_mine_positions[i][j] == '0') {
            table_mine_positions[i][j] = 'B';

            cell_number(i - 1, j);
            cell_number(i + 1, j);
            cell_number(i, j - 1);
            cell_number(i, j + 1);
            cell_number(i - 1, j - 1);
            cell_number(i - 1, j + 1);
            cell_number(i + 1, j - 1);
            cell_number(i + 1, j + 1);
            counter++;
        }
    }
}

void create_table()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            table[i][j] = '*';
}

void print_table(char a[10][10])
{
    cout << "    ";
    for (int i = 0; i < 10; i++)
        cout << "  " << i;

    cout << endl << "  ";
    for (int i = 0; i < 32; i++)
        cout << "_";
    cout << endl;

    for (int i = 0; i < 10; i++) {
        cout << "  " << i << "|";
        for (int j = 0; j < 10; j++)
            cout << "  " << a[i][j];
        cout << endl;
    }
}

void open_cell()
{
    int i, j;

    do
        cin >> i >> j;
    while (i < 0 || i>9 || j < 0 || j>9);

    if (table_mine_positions[i][j] == 'B')
    {
        table[i][j] = 'B';
        end_game_lose = true;

        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                if (table_mine_positions[i][j] == 'B')
                    table[i][j] = 'B';
    }
    else 
        reveal(i,j);
}

void place_or_remove_flag()
{
    int i, j;
    do
        cin >> i >> j;
    while (i < 0 || i>9 || j < 0 || j>9);

    if (table[i][j] == '*')
    {
        table[i][j] = 'F';
        flag_counter++;

        if (table_mine_positions[i][j] == 'B')
            mines_flagged_counter++;
    }

    else if (table[i][j] == 'F')
    {
        table[i][j] = '*';
        flag_counter--;
        if (table_mine_positions[i][j] == 'B')
            mines_flagged_counter--;
    }
}

void input_symbol()
{
    cin >> symbol;
    switch (symbol) {
    case 'o': open_cell(); break;
    case 'f': place_or_remove_flag(); break;
    default: input_symbol();
    }
}

void reveal(int i, int j)
{
    if (table[i][j] == '*' && table_mine_positions[i][j] != 'B' && i >= 0 && i < 10 && j >= 0 && j < 10)
    {
        table[i][j] = table_mine_positions[i][j];

        if (table_mine_positions[i][j] == '0')
        {
            reveal(i, j - 1);
            reveal(i, j + 1);
            reveal(i - 1, j - 1);
            reveal(i + 1, j - 1);
            reveal(i + 1, j + 1);
            reveal(i - 1, j + 1);
            reveal(i - 1, j);
            reveal(i + 1, j);
        }
    }
}

bool end_game_win_check()
{
    if (flag_counter == 10 && mines_flagged_counter == 10)
        return 1;
    else
        return 0;
}

void game()
{
    create_table();
    create_mine_positions();

    while (!end_game_lose && !end_game_win_check())
    {
        print_table(table);
        cout << endl << "Flags:" << flag_counter << endl;

        input_symbol();
        
    }
    if (end_game_lose) {
        print_table(table);
        cout << endl << "GAME OVER" << endl;
    }

    else if (end_game_win_check()) {
        cout << "YOU WIN" << endl;
    }
}

int main() {
    cout << "Chao mung den voi tro choi do min!" << endl;
    cout << "Muc tieu cua tro choi la mo tat ca cac o khong chua min ma khong mo bat ky o nao chua min." << endl;
    cout << "luat choi:" << endl
    << "Nguoi choi nhap 'o', sau do nhap gia tri cua i và j de mo o[i][j]." << endl 
    << "Nhap 'f' , sau do nhap gia tri cua i và j de dat co tren o[i][j]" << endl;
    game();
        
    return 0;
}