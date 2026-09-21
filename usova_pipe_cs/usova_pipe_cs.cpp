﻿#include <iostream>
using namespace std;

int main()
{
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
        cin >> x;

        if (x == 1) {
            cout << "Pipe";
            break;

        }
    }
}