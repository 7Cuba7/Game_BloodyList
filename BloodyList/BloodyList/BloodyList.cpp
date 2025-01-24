#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <conio.h>
#include <windows.h>
#include <random>
#include <string>
#include <set>
#include <map>
#include <utility> // for std::pair
#include <cmath>
#include <set>
using namespace std;

#define RED "\033[1;31m"
#define RESET "\033[0m"
#define GOLD "\033[33m"
#define GREEN "\033[1;32m"

void pavadinimas()
{
    cout << "" << endl;
    cout << RED << " #####   ##        ####        ####     ####    ##    ##" << endl;
    cout << " ##  ##  ##      ##    ##    ##    ##   ##  ##   ##  ##" << endl;
    cout << " ##  ##  ##     ##      ##  ##      ##  ##   ##   ####" << endl;
    cout << " #####   ##     ##      ##  ##      ##  ##   ##    ##" << endl;
    cout << " ##  ##  ##     ##      ##  ##      ##  ##   ##    ##" << endl;
    cout << " ##  ##  ##      ##    ##    ##    ##   ##  ##     ##" << endl;
    cout << " #####   ######    ####        ####     ####       ##" << endl;
    cout << "                                                        " << endl;
    cout << GOLD << "             ##      ##    ####   ##########         " << endl;
    cout << "             ##      ##  ###  ###     ##             " << endl;
    cout << "             ##      ##  ##           ##             " << endl;
    cout << "             ##      ##   ######      ##             " << endl;
    cout << "             ##      ##       ###     ##             " << endl;
    cout << "             ##      ##  ###  ###     ##             " << endl;
    cout << "             ######  ##    ####       ##             " << endl;
    cout << "                                                     " << endl;
    cout << RED << "                 Press ENTER to start              " << endl;
    cout << RESET << endl;
}
void menu()
{
    cout << "STORY: your wife sent you to the supermatket and gave you a list of items to buy." << endl;
    cout << "GOAL: collect as many items as possible before the killers catches you." << endl;
    cout << "TIP: killers can't reach you while you in the box" << endl;
    cout << "The more items you collect, the greater the chance that your wife will not divorce you :)" << endl;
    cout << "Good luck!" << endl;
}
void gotoxy(int X, int Y)
{
    COORD coord;
    coord.X = X;
    coord.Y = Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class bazine
{
protected:
    int x, y;
    int speedX, speedY;
    static char map[21][81];
    int balance = 0;
    int total = 0;
public:
    //bazine() : x(0), y(0) {}
    //bazine(int startX, int startY) : x(startX), y(startY) {}
    ~bazine() {}

    std::map<char, pair<int, int>> list;
    set<char> money = { '1','2','3' };
    static void map_skaitymas()
    {
        try {
            ifstream ived("map.txt");
            for (int i = 0; i < 21; i++) {
                string line;
                getline(ived, line);
                for (int j = 0; j < line.length(); j++) {
                    map[i][j] = line[j];
                }
            }
            ived.close();
        }
        catch (const ifstream::failure& e) {
            cout << "Error: Could not open map.txt file!" << endl;
        }
    }
    void map_print()
    {
        for (int i = 0;i < 21;i++)
        {
            for (int j = 0;j < 81;j++)
                cout << map[i][j];
            cout << " " << endl;
        }
    }
    void coutList()
    {
        list['A'] = make_pair(83, 13);
        list['B'] = make_pair(83, 14);
        list['C'] = make_pair(83, 15);
        list['D'] = make_pair(83, 16);
        list['E'] = make_pair(83, 17);
        list['F'] = make_pair(83, 18);
        list['G'] = make_pair(83, 19);
        list['H'] = make_pair(95, 13);
        list['I'] = make_pair(95, 14);
        list['Z'] = make_pair(95, 15);
        list['Q'] = make_pair(95, 16);
        list['L'] = make_pair(95, 17);
        list['M'] = make_pair(95, 18);
        list['N'] = make_pair(95, 19);

    }
    void Produktuisvedimas()
    {
        gotoxy(83, 13);
        cout << "1.Apples" << endl;
        gotoxy(83, 14);
        cout << "2.Bananas" << endl;
        gotoxy(83, 15);
        cout << "3.Carrots" << endl;
        gotoxy(83, 16);
        cout << "4.Detergent" << endl;
        gotoxy(83, 17);
        cout << "5.Eggs" << endl;
        gotoxy(83, 18);
        cout << "6.Flour" << endl;
        gotoxy(83, 19);
        cout << "7.Grapes" << endl;
        gotoxy(95, 13);
        cout << "8.Honey" << endl;
        gotoxy(95, 14);
        cout << "9.Ice cream" << endl;
        gotoxy(95, 15);
        cout << "10.Zucchini" << endl;
        gotoxy(95, 16);
        cout << "11.Quinoa" << endl;
        gotoxy(95, 17);
        cout << "12.Lemons" << endl;
        gotoxy(95, 18);
        cout << "13.Milk" << endl;
        gotoxy(95, 19);
        cout << "14.Nuts" << endl;
    }
    int isvedimasX()
    {
        return x;
    }
    int isvedimasY()
    {
        return y;
    }
    int isvedimasTotal()
    {
        return total;
    }
    int isvedimasBalance()
    {
        return balance;
    }
};
char bazine::map[21][81];
class player : public bazine
{
private:
    int pX = 65, pY = 19;
    int laikX, laikY;
    int state = 0;
public:
    void movement()
    {

        gotoxy(pX, pY);

        if (map[pY][pX] == '|')
            cout << "|";
        else if (map[pY][pX] == '-')
            cout << "-";
        else {
            cout << ' ';
        }

        if (map[pY][pX] == '1')
        {
            balance++;
            map[pY][pX] = ' ';
        }
        if (map[pY][pX] == '2')
        {
            balance = balance + 2;
            map[pY][pX] = ' ';
        }
        if (map[pY][pX] == '3')
        {
            balance = balance + 3;
            map[pY][pX] = ' ';
        }

        if (GetAsyncKeyState(VK_UP) && map[pY - 1][pX] != '#' && map[pY - 1][pX] != '!')
            pY--;
        else if (GetAsyncKeyState(VK_DOWN) && map[pY + 1][pX] != '#' && map[pY + 1][pX] != '!')
            pY++;
        else if (GetAsyncKeyState(VK_LEFT) && map[pY][pX - 1] != '#' && map[pY][pX - 1] != '!')
            pX--;
        else if (GetAsyncKeyState(VK_RIGHT) && map[pY][pX + 1] != '#' && map[pY][pX + 1] != '!')
            pX++;

        x = pX;
        y = pY;

        gotoxy(pX, pY);
        if (map[pY][pX] == 'A' || map[pY][pX] == 'B' || map[pY][pX] == 'C' || map[pY][pX] == 'D'
            || map[pY][pX] == 'E' || map[pY][pX] == 'F' || map[pY][pX] == 'G' || map[pY][pX] == 'H'
            || map[pY][pX] == 'I' || map[pY][pX] == 'Z' || map[pY][pX] == 'Q' || map[pY][pX] == 'L'
            || map[pY][pX] == 'M' || map[pY][pX] == 'N')
        {
            for (auto pair : list)
            {
                if (map[pY][pX] == pair.first)
                {
                    map[pY][pX] = ' ';
                    total = total + 3;
                    state = state + 1;
                    gotoxy(pair.second.first, pair.second.second);
                    cout << "           " << endl;
                    gotoxy(pX, pY);
                }
            }
        }
        cout << GREEN << 'P';
        cout << RESET;

        gotoxy(83, 1);
        cout << "                " << endl;
        gotoxy(83, 1);
        cout << "Total: " << total << endl;
        gotoxy(83, 2);
        cout << "                " << endl;
        gotoxy(83, 2);
        cout << "Balance: " << balance << endl;

        if (balance >= total)
        {
            gotoxy(72, 2);
            cout << ' ';
            gotoxy(72, 3);
            cout << ' ';
            map[2][72] = ' ';
            map[3][72] = ' ';
        }
        else {
            gotoxy(72, 2);
            cout << '!';
            gotoxy(72, 3);
            cout << '!';
            map[2][72] = '!';
            map[3][72] = '!';
        }



    }
    int operator ++()
    {
        return state;
    }
    int getPX() const { return pX; }
    int getPY() const { return pY; }
};
class killer : public bazine
{
private:
    int kX, kY, pkX, pkY;
    int ran;
    int k1 = 0, k2 = 0;
    int laikX, laikY;
    int state = 0;
public:
    //killer() : x(0), y(0) {}
    killer(int startX, int startY) : kX(startX), kY(startY) {}
    void movement(player& P)
    {
        pkY = P.getPY();
        pkX = P.getPX();

        if (map[kY][kX] == '1' || map[kY][kX] == '2' || map[kY][kX] == '3')
            map[kY][kX] = ' ';


        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 30);
        ran = dis(gen);
        if (ran == 7)
        {
            gotoxy(kX, kY);
            uniform_int_distribution<> dis(1, 3);
            ran = dis(gen);
            if (ran == 1)
            {
                map[kY][kX] = '1';
                cout << GOLD << '1';
                cout << RESET;
            }
            else if (ran == 2)
            {
                map[kY][kX] = '2';
                cout << GOLD << '2';
                cout << RESET;
            }
            else if (ran == 3)
            {
                map[kY][kX] = '3';
                cout << GOLD << '3';
                cout << RESET;
            }

        }
        else {
            gotoxy(kX, kY);
            cout << ' ';
        }
        int kart = 0;
        if (abs(pkX - kX) <= 20 && abs(pkY - kY) <= 7)
        {


            if (kX > pkX && map[kY][kX - 1] != '#' && map[kY][kX - 1] != '-' && map[kY][kX - 1] != '|' && map[kY][kX - 1] != '+' && map[kY][kX - 1] != '!')
            {
                kX--;
            }
            else if (kX < pkX && map[kY][kX + 1] != '#' && map[kY][kX + 1] != '-' && map[kY][kX + 1] != '|' && map[kY][kX + 1] != '+' && map[kY][kX + 1] != '!')
            {
                kX++;
            }
            else if (kY > pkY && map[kY - 1][kX] != '#' && map[kY - 1][kX] != '-' && map[kY - 1][kX] != '|' && map[kY - 1][kX] != '+' && map[kY - 1][kX] != '!')
                kY--;
            else if (kY < pkY && map[kY + 1][kX] != '#' && map[kY + 1][kX] != '-' && map[kY + 1][kX] != '|' && map[kY + 1][kX] != '+' && map[kY + 1][kX] != '!')
                kY++;
            else {

            }
        }
        else {
            uniform_int_distribution<> dis(1, 4);
            ran = dis(gen);
            if (ran == 1 && map[kY - 1][kX] != '#' && map[kY - 1][kX] != '-' && map[kY - 1][kX] != '|' && map[kY - 1][kX] != '+' && map[kY - 1][kX] != '!')
            {
                kY--;
            }
            else if (ran == 2 && map[kY + 1][kX] != '#' && map[kY + 1][kX] != '-' && map[kY + 1][kX] != '|' && map[kY + 1][kX] != '+' && map[kY + 1][kX] != '!')
            {
                kY++;
            }
            else if (ran == 3 && map[kY][kX - 1] != '#' && map[kY][kX - 1] != '-' && map[kY][kX - 1] != '|' && map[kY][kX - 1] != '+' && map[kY][kX - 1] != '!')
            {
                kX--;
            }
            else if (ran == 4 && map[kY][kX + 1] != '#' && map[kY][kX + 1] != '-' && map[kY][kX + 1] != '|' && map[kY][kX + 1] != '+' && map[kY][kX + 1] != '!')
            {
                kX++;
            }
        }


        gotoxy(kX, kY);
        cout << RED << 'K';
        cout << RESET;

        x = kX;
        y = kY;

    }
};

int main() {
    bool game = true;
    int frame = 0;
    int speed = 3;
    int end;
    char type;
    int kiekis = 0, t = 0;
    pavadinimas();
    while (true)
    {
        char input = _getch();
        if (input == '\r')
        {
            system("cls");
            break;
        }
    }
    menu();
    while (true)
    {
        char input = _getch();
        if (input == '\r')
        {
            system("cls");
            break;
        }
    }

    cout << "Choose difficulty" << endl;
    cout << "Easy(type E)" << endl;
    cout << "Medium(type M)" << endl;
    cout << "Hard(type H)" << endl;
    cout << "Type: ";
    cin >> type;
    if (type == 'E')
        speed = 3;
    else if (type == 'M')
        speed = 2;
    else if (type == 'H')
        speed = 1;
    system("cls");

    player P;
    killer K(9, 9), K2(15, 15), K3(40, 15);
    P.map_skaitymas();
    P.map_print();
    P.coutList();
    P.Produktuisvedimas();
    while (game)
    {
        P.movement();
        if (frame % speed == 0)
        {
            K.movement(P);
            K2.movement(P);
            K3.movement(P);
        }
        if ((P.isvedimasX() == K.isvedimasX() && P.isvedimasY() == K.isvedimasY()) || (P.isvedimasX() == K2.isvedimasX() && P.isvedimasY() == K2.isvedimasY())
            || (P.isvedimasX() == K3.isvedimasX() && P.isvedimasY() == K3.isvedimasY()))
        {
            end = 0;
            break;
        }
        if ((P.isvedimasX() == 80 && P.isvedimasY() == 2) || (P.isvedimasX() == 80 && P.isvedimasY() == 3))
        {
            end = 1;
            break;
        }
        Sleep(100);
        frame++;
    }
    Sleep(100);
    system("cls");
    if (end == 0)
    {
        cout << "You lost and your wife will divorce you" << endl;

    }
    double chance;
    chance = ++P / 14 * 100;
    int ran;
    if (end == 1)
    {
        cout << "Congratulations! You escaped and collected " << ++P << " items " << endl;
        if (++P == 14)
            cout << "You are a good husband, and your wife will not divorce you." << endl;
        else if (++P == 0) {
            cout << "Your wife is unhappy because you did not bring enough items and will divorce you. Technically, you lose :(" << endl;
        }
        else {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(1, 100);
            ran = dis(gen);
            if (ran <= chance) {
                cout << "You are a good husband, and your wife will not divorce you." << endl;
            }
            else {
                cout << "Your wife is unhappy because you did not bring enough items and will divorce you. Technically, you lose :(" << endl;
            }
        }


    }
    return 0;
}
