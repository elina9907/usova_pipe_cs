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

int readInt(string text, int minValue = 0, int maxValue= 7) {
    int value = 0;
    while (true) {
        cout << text;
        cin >> value;
        bool Correct = !cin.fail() && cin.peek() == '\n' && value >= minValue && value <= maxValue;

        if (Correct)
            cin.ignore();
            return value;
        
        cin.clear();
        cin.ignore(1000, '\n');
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

        if (isCorrect)
            cin.ignore();
            return value;

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error, enter a number > 0\n";
    }
}

string readName(string text) {
    string name;
    while (true) {
        cout << text;
        getline(cin, name);
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

void printPipe(Pipe& pipe) {
    cout << "Pipe\n";
    cout << "Name: " << pipe.name << "\n";
    cout << "Length (km): " << pipe.len << "\n";
    cout << "Diameter (mm): " << pipe.diametr << "\n";
    cout << "Status:" << (pipe.remont ? "under repair" : "in operation") << "\n";
    
}

void editPipe(Pipe& pipe) {
    cout << "Current status:" << (pipe.remont ? "under repair" : "in operation") << "\n";

    int choice = readInt("Enter 1 - send to repair, 0 - remove from repair: ", 0, 1);

    pipe.remont = (choice == 1);
    cout << (pipe.remont ? "The pipe is under repair" : "The pipe is in operation");


};
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

void printCS(CS& cs) {
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

bool savePandC(Pipe& pipe, bool hasPipe, CS& cs, bool hasCS) {
    ofstream out("data.txt");
    if (!out) {
        return false;
    }

    out << hasPipe << "\n";
    if (hasPipe) {
        out << pipe.name << "\n";
        out << pipe.len << "\n";
        out << pipe.diametr << "\n";
        out << pipe.remont << "\n";
    }

    out << hasCS << "\n";
    if (hasCS) {
        out << cs.name << "\n";
        out << cs.shopcount << "\n";
        out << cs.workShopcount << "\n";
        out << cs.stationClass << "\n";
    }

    return true;
}

bool loadPandC(Pipe& pipe, bool& hasPipe, CS& cs, bool& hasCS) 
{
    ifstream in("data.txt");
    if (!in) {
        return false;
    }

    bool pipeFlag = false;
    in >> pipeFlag;
    in.ignore();

    if (pipeFlag) {
        Pipe loaded;
        getline(in, loaded.name);
        in >> loaded.len;
        in >> loaded.diametr;
        in >> loaded.remont;
        in.ignore();

        if (in.fail() || loaded.name == "" || loaded.len <= 0 || loaded.diametr <= 0) {
            return false;
        }
        pipe = loaded;
        hasPipe = true;
    }

    bool csFlag = false;
    in >> csFlag;
    in.ignore();

    if (csFlag) {
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
        hasCS = true;
    }

    return true;
}


void printMenu() {
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
        printMenu();
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
                printPipe(pipe);
            }
            else {
                cout << "The pipe has not been created yet\n\n";
            }
            if (hasCS) {
                printCS(cs);
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
            else if ((pipe, hasPipe, cs, hasCS)) {
                cout << "Saved to data.txt\n";
            }
            else {
                cout << "Error: could not write data.txt\n";
            }
            cout << "\n";
            break;

        case 7:
            if (loadPandC(pipe, hasPipe, cs, hasCS)) {
                cout << "Loaded from data.txt\n";
            }
            else {
                cout << "The data was not loaded\n";
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

