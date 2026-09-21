#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

struct Pipe {
    string name;
    double len;
    int diametr;
    int thickness;
    bool remont;
};

struct CS {
    string name;
    int shop;
    int workshop;
    int stationclass;
};

int main()
{
    SetConsoleCP(65001); //https:learn.microsoft.com
    SetConsoleOutputCP(65001);

    Pipe pipe;
    bool pipebe = false;

    CS cs;
    bool csbe = false;

    int x = -1;

    while (x != 0) {
        cout << "Menu\n";
        cout << "1. Add a pipe\n";
        cout << "2. Add CS\n";
        cout << "3. Viewing all objects\n";
        cout << "4. Edit the pipe\n";
        cout << "5. Eit the CS \n";
        cout << "6. Save\n";
        cout << "7. Download\n";
        cout << "0. Exit\n";
        cout << "Choose one:"; cin >> x; cout << "\n";

        if (!(cin)) {
            cout << "no choice\n";
            cin.clear();
            string trash;
            cin >> trash;
            continue;
        }

        switch (x) {
        case 1:
            cout << "Enter the pipe name\n";
            cin >> pipe.name;

            cout << "Enter the length of the pipe (km)\n";
            cin >> pipe.len;

            cout << "Enter the pipe diameter (mm)\n";
            cin >> pipe.diametr;

            cout << "Enter the thickness of the pipe (mm)\n";
            cin >> pipe.thickness;

            pipe.remont = false;
            pipebe = true;
            cout << "Pipe added\n";
            cout << "\n";

            break;

        case 2:
            cout << "Enter the CS name\n";
            cin >> cs.name;

            cout << "Enter the number of shops (count)\n";
            cin >> cs.shop;

            cout << "Enter the number of workshops in operation (count) \n";
            cin >> cs.workshop;

            cout << "Enter the station class\n";
            cin >> cs.stationclass;
            csbe = true;
            cout << "CS added\n";
            cout << "\n";

            break;

        case 3:
            if (pipebe) {
                cout << "Pipe\n";
                cout << "Name: " << pipe.name << "\n";
                cout << "Len: " << pipe.len << "\n";
                cout << "Diameter: " << pipe.diametr << "\n";
                cout << "Thickness: " << pipe.thickness << "\n";
                if (pipe.remont) {
                    cout << "Status under repair\n";
                }
                else {
                    cout << "Status in operation\n";
                    cout << "\n";
                }
            }

            else {
                cout << "The pipe has not been created\n";
                cout << "\n";
            }
            if (csbe) {
                cout << "CS\n";
                cout << "Name: " << cs.name << "\n";
                cout << "Shop: " << cs.shop << "\n";
                cout << "Workshop: " << cs.workshop << "\n";
                cout << "Stationclass: " << cs.stationclass << "\n";
                cout << "\n";
            }
            else {
                cout << "CS has not been created yet" << "\n";
                cout << "\n";
            }
            break;
        case 4:
            if (pipebe) {
                if (pipe.remont) {
                    cout << "in remont\n";
                }
                else {
                    cout << "in work\n";
                }

                cout << "Enter 1 - to repair, 0 - to remove from repair\n";
                int y;
                cin >> y;


                if (y == 1) {
                    pipe.remont = true;
                    cout << "The pipe is under repair\n";
                }
                else if (y == 0) {
                    pipe.remont = false;
                    cout << "The pipe is in operation\n";
                }
                else {
                    cout << "Nothing has changed, choose 0 or 1\n";
                }

            }
            else {
                cout << "Create a pipe\n";
                cout << "\n";
            }

            break;
        case 5:
            if (csbe) {
                cout << "In work:" << cs.workshop << "from" << cs.shop << "\n";
                cout << "Enter 1 - start shop, 0 - stop shop\n";
                int z;
                cin >> z;

                if (z == 1) {
                    if (cs.workshop < cs.shop) {
                        cs.workshop = cs.workshop + 1;
                        cout << "The workshop is running\n";
                    }
                    else {
                        cout << "All workshops are working\n";
                    }
                }
                else if (z == 0) {
                    if (cs.workshop > 0) {
                        cs.workshop = cs.workshop - 1;
                        cout << "The workshop is stopped\n";
                    }
                    else {
                        cout << "There are no working workshops\n";
                    }
                }
                else {
                    cout << "An incomprehensible choice\n";
                }
            }
            else {
                cout << "Create CS!";
            }
            break;
        default:
            cout << "No such menu item\n";
            break;



        }
    }

}

