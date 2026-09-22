#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct Pipe {
    string name;
    double len;
    int diametr;
    bool remont;
};

struct CS {
    string name;
    int shopcount;
    int workShopcount;
    int stationClass;
};

void stopInputClosed() {
    if (cin.eof()) {
        cout << "Input closed, exiting\n";
        exit(0);
    }
}

int readInt(string text, int minValue, int maxValue) {
    int value = 0;
    while (true) {
        cout << text;
        cin >> value;
        bool Correct = !cin.fail() && cin.peek() == '\n' && value >= minValue && value <= maxValue;

        stopInputClosed();
        cin.clear();
        cin.ignore(1000, '\n');
        if (Correct) {
            return value;
        }
        cout << "Error, enter a whole number from " << minValue << " to " << maxValue << "\n";
    }
}

double readDouble(string text) 
{
    double value = 0;
    while (true) {
        cout << text;
        cin >> value;

        bool isCorrect = !cin.fail() && cin.peek() == '\n' && value > 0;

        stopInputClosed();
        cin.clear();
        cin.ignore(1000, '\n');
        if (isCorrect) {
            return value;
        }
        cout << "Error, enter a number > 0\n";
    }
}

string readName(string text) {
    string name;
    while (true) {
        cout << text;
        getline(cin, name);
        stopInputClosed();
        if (name != "") {
            return name;
        }
        cout << "Error, the name must not be empty\n";
    }
}


Pipe readPipe() {
    Pipe pipe;
    pipe.name = readName("Enter the pipe name: ");
    pipe.len = readDouble("Enter the length of the pipe (km): ");
    pipe.diametr = readInt("Enter the pipe diameter (mm): ", 1, 1000000);
    pipe.remont = false;
    return pipe;
}

void pPipe(Pipe& pipe) {
    cout << "Pipe\n";
    cout << "Name: " << pipe.name << "\n";
    cout << "Length (km): " << pipe.len << "\n";
    cout << "Diameter (mm): " << pipe.diametr << "\n";
    if (pipe.remont) {
        cout << "Status: under repair\n";
    }
    else {
        cout << "Status: in operation\n";
    }
    cout << "\n";
}

void editPipe(Pipe& pipe) {
    if (pipe.remont) {
        cout << "Current status: under repair\n";
    }
    else {
        cout << "Current status: in operation\n";
    }

    int choice = readInt("Enter 1 - send to repair, 0 - remove from repair: ", 0, 1);
    if (choice == 1) {
        pipe.remont = true;
        cout << "The pipe is under repair\n";
    }
    else {
        pipe.remont = false;
        cout << "The pipe is in operation\n";
    }
}

bool savePipe(Pipe& pipe) {
    ofstream out("pipe.txt");
    if (!out) {
        return false;
    }
    out.precision(15);
    out << pipe.name << "\n";
    out << pipe.len << "\n";
    out << pipe.diametr << "\n";
    out << pipe.remont << "\n";
    return true;
}

bool loadPipe(Pipe& pipe) {
    ifstream in("pipe.txt");
    if (!in) {
        return false;
    }

    Pipe loaded;
    getline(in, loaded.name);
    in >> loaded.len;
    in >> loaded.diametr;
    in>> loaded.remont;

    if (in.fail() || loaded.name == "" || loaded.len <= 0 || loaded.diametr <= 0) {
        return false;
    }
    pipe = loaded;
    return true;
}


CS readCS() {
    CS cs;
    cs.name = readName("Enter the CS name: ");
    cs.shopcount = readInt("Enter the number of shops: ", 1, 1000000);
    cs.workShopcount = readInt("Enter the number of shops in operation: ", 0, cs.shopcount);
    cs.stationClass = readInt("Enter the station class: ", 1, 1000000);
    return cs;
}

void pCS(CS& cs) {
    cout << "CS\n";
    cout << "Name: " << cs.name << "\n";
    cout << "Shops: " << cs.shopcount << "\n";
    cout << "Shops in operation: " << cs.workShopcount << "\n";
    cout << "Station class: " << cs.stationClass << "\n";
    cout << "\n";
}

void editCS(CS& cs) {
    cout << "Shops in operation: " << cs.workShopcount << " of " << cs.shopcount << "\n";

    int choice = readInt("Enter 1 - start a shop, 0 - stop a shop: ", 0, 1);
    if (choice == 1) {
        if (cs.workShopcount < cs.shopcount) {
            cs.workShopcount++;
            cout << "A shop has been started\n";
        }
        else {
            cout << "All shops are already working\n";
        }
    }
    else {
        if (cs.workShopcount > 0) {
            cs.workShopcount--;
            cout << "A shop has been stopped\n";
        }
        else {
            cout << "There are no working shops\n";
        }
    }
}

bool saveCS(CS& cs) {
    ofstream out("cs.txt");
    if (!out) {
        return false;
    }
    out << cs.name << "\n";
    out << cs.shopcount << "\n";
    out << " " << cs.workShopcount <<"\n";
    out << " " << cs.stationClass << "\n";
    return true;
}

bool loadCS(CS& cs) {
    ifstream in("cs.txt");
    if (!in) {
        return false;
    }

    CS loaded;
    getline(in, loaded.name);
    in >> loaded.shopcount;
    in >> loaded.workShopcount;
    in >> loaded.stationClass;

    if (in.fail() || loaded.name == "" || loaded.shopcount <= 0 || loaded.stationClass <= 0) {
        return false;
    }
    if (loaded.workShopcount < 0 || loaded.workShopcount > loaded.shopcount) {
        return false;
    }
    cs = loaded;
    return true;
}


void pMenu() {
    cout << "Menu\n";
    cout << "1. Add a pipe\n";
    cout << "2. Add CS\n";
    cout << "3. View all objects\n";
    cout << "4. Edit the pipe\n";
    cout << "5. Edit the CS\n";
    cout << "6. Save\n";
    cout << "7. Load\n";
    cout << "0. Exit\n";
}

int main() {
    Pipe pipe;
    bool hasPipe = false;

    CS cs;
    bool hasCS = false;

    int menuChoice = -1;

    while (menuChoice != 0) {
        pMenu();
        menuChoice = readInt("Choose one: ", 0, 7);
        cout << "\n";

        switch (menuChoice) {
        case 1:
            pipe = readPipe();
            hasPipe = true;
            cout << "Pipe added\n\n";
            break;

        case 2:
            cs = readCS();
            hasCS = true;
            cout << "CS added\n\n";
            break;

        case 3:
            if (hasPipe) {
                pPipe(pipe);
            }
            else {
                cout << "The pipe has not been created yet\n\n";
            }
            if (hasCS) {
                pCS(cs);
            }
            else {
                cout << "The CS has not been created yet\n\n";
            }
            break;

        case 4:
            if (hasPipe) {
                editPipe(pipe);
            }
            else {
                cout << "Create a pipe first\n";
            }
            cout << "\n";
            break;

        case 5:
            if (hasCS) {
                editCS(cs);
            }
            else {
                cout << "Create a CS first\n";
            }
            cout << "\n";
            break;

        case 6:
            if (!hasPipe && !hasCS) {
                cout << "There is nothing to save\n";
            }
            if (hasPipe) {
                if (savePipe(pipe)) {
                    cout << "Pipe saved to pipe.txt\n";
                }
                else {
                    cout << "Error: could not write pipe.txt\n";
                }
            }
            if (hasCS) {
                if (saveCS(cs)) {
                    cout << "CS saved to cs.txt\n";
                }
                else {
                    cout << "Error: could not write cs.txt\n";
                }
            }
            cout << "\n";
            break;

        case 7:
            if (loadPipe(pipe)) {
                hasPipe = true;
                cout << "Pipe loaded from pipe.txt\n";
            }
            else {
                cout << "The pipe was not loaded\n";
            }
            if (loadCS(cs)) {
                hasCS = true;
                cout << "CS loaded from cs.txt\n";
            }
            else {
                cout << "The CS was not loaded\n";
            }
            cout << "\n";
            break;

        case 0:
            cout << "You are out of the menu\n";
            break;
        }
    }
    return 0;
}

