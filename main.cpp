#include <iostream>
#include <unistd.h>  //For system()
#include <windows.h> //For Sleep()

using namespace std;

char grid[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char fpSign, spSign, pos;

void initilize(char sign)
{
    if (sign == 'X')
    {
        spSign = 'O';
    }
    else if (sign == 'O')
    {
        spSign = 'X';
    }
    else
    {
        cout << "Error Input.." << endl;
        Sleep(300);
    }
}

void showGrid(void)
{
    system("cls");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (j != 2)
            {
                cout << grid[i][j] << " | ";
            }
            else
            {
                cout << grid[i][j];
            }
        }
        cout << endl;
    }
    Sleep(500);
}

int win()
{
    /*
    Winning Chances : 
    00-01-02    00-10-20
    10-11-12    01-11-21    00-11-22  02-11-20
    20-21-22    02-12-22
    */
    for (int i = 0; i < 3; i++)
    {
        if ((grid[i][0] == fpSign && grid[i][1] == fpSign && grid[i][2] == fpSign) || (grid[0][i] == fpSign && grid[1][i] == fpSign && grid[2][i] == fpSign))
        {
            //    Fp wins
            return 1;
        }
        else if ((grid[i][0] == spSign && grid[i][1] == spSign && grid[i][2] == spSign) || (grid[0][i] == spSign && grid[1][i] == spSign && grid[2][i] == spSign))
        {
            //    Sp Wins
            return 2;
        }
    }

    if ((grid[0][0] == fpSign && grid[1][1] == fpSign && grid[2][2] == fpSign) || (grid[0][2] == fpSign && grid[1][1] == fpSign && grid[2][0] == fpSign))
    {
        //    Fp Wins
        return 1;
    }
    else if ((grid[0][0] == spSign && grid[1][1] == spSign && grid[2][2] == spSign) || (grid[0][2] == spSign && grid[1][1] == spSign && grid[2][0] == spSign))
    {
        //    Sp Wins
        return 2;
    }

    // Check for Draw.
    int flag = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] == fpSign || grid[i][j] == spSign)
            {
                flag++;
            }
            else
            {
                flag--;
            }
        }
    }

    if (flag == 9)
    {
        return 3;
    }

    return 0;
}

bool pushSign(char turn, int player)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid[i][j] == turn)
            {
                if (player == 1)
                {
                    grid[i][j] = fpSign;
                }
                else if (player == 2)
                {
                    grid[i][j] = spSign;
                }
                else
                {
                    return false;
                }
                return true;
            }
        }
    }
    return false;
}

void game(void)
{
    while (true)
    {
        showGrid();
        cout << endl
             << "Choose Place (1P) '"<<fpSign<<"' : ";
        cin >> pos;
        if (pushSign(pos, 1))
        {
            if (win() == 0)
            {
            secondPStart:
                showGrid();
                cout << endl
                     << "Choose Place (2P) '"<<spSign<<"' : ";
                cin >> pos;
                if (pushSign(pos, 2))
                {
                    if (win() == 0)
                    {
                        continue;
                    }
                    else if (win() == 2)
                    {
                        showGrid();
                        cout << "\nPlayer 2 (" << spSign << ") Wins !!" << endl;
                        Sleep(500);
                        break;
                    }
                    else if (win() == 3)
                    {
                        showGrid();
                        cout << "\n!! DRAW !!" << endl;
                        Sleep(500);
                        break;
                    }
                }
                else
                {
                    cout << "Error Input !!" << endl;
                    Sleep(300);
                    goto secondPStart;
                }
            }
            else if (win() == 1)
            {
                showGrid();
                cout << "\nPlayer 1 (" << fpSign << ") Wins !!" << endl;
                Sleep(500);
                break;
            }
            else if (win() == 3)
            {
                showGrid();
                cout << "\n!! DRAW !!" << endl;
                Sleep(500);
                break;
            }
        }
        else
        {
            cout << "Error Input !!" << endl;
            Sleep(300);
            continue;
        }
    }
}

int main()
{
    char qExit;
    while (true)
    {
        system("cls");
        cout << "Welcome" << endl;
        cout << "Choose First Player's Sign (X , O) : " << endl;
        cin >> fpSign;
        initilize(fpSign);
        if (spSign)
        {
            game();
        }
        else
        {
            continue;
        }
        cout << endl
             << "Want to Exit the Game? (y/n) : ";
        cin >> qExit;
        if (qExit == 'Y' || qExit == 'y')
        {
            exit(0);
        }
        else
        {
            continue;
        }
    }
    return 0;
}