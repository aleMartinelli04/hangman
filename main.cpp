#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <fstream>
#include <vector>

#define notFound string::npos

using namespace std;

string usedChars;
bool endFor = false;
int errors = 0;

const string HANGMEN[] = {
        (
                "  +---+\n"
                "  |   |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "========="
        ),
        (
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                "      |\n"
                "      |\n"
                "      |\n"
                "========="
        ),
        (
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                "  |   |\n"
                "      |\n"
                "      |\n"
                "========="
        ),
        (
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|   |\n"
                "      |\n"
                "      |\n"
                "========="
        ),
        (
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|\\  |\n"
                "      |\n"
                "      |\n"
                "========="
        ),
        (
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|\\  |\n"
                " /    |\n"
                "      |\n"
                "========="
        ),
        (
                "  +---+\n"
                "  |   |\n"
                "  O   |\n"
                " /|\\  |\n"
                " / \\  |\n"
                "      |\n"
                "========="
        )
};

// stampa la parola
void printWord(const string &word) {

    cout << HANGMEN[errors] << endl;

    for (char c : word) {
        if (usedChars.find(c) == notFound) {
            cout << (c != ' ' ? "_ " : "  "); // se la lettera non è ancora stata usata stampa un tratto basso
        } else {
            cout << c << " "; // altrimenti stampa la lettera
        }
    }
}

// Stampa 'O' per le vite che rimangono e 'X' per quelle già usate
void printLives() {
    int remainingLives = 5 - errors;

    cout << "Vite: ";

    for (; remainingLives > 0; remainingLives--) {
        cout << "O ";
    }

    for (int i = errors; i > 0; i--) {
        cout << "X ";
    }

    cout << endl;
}

int main() {
    srand(time(nullptr));

    ifstream file("words.txt");

    vector<string> wordList;

    string line;

    while (getline(file, line)) {
        wordList.push_back(line);
    }

    string word = wordList[rand() % wordList.size()];

    char inserted;
    do {
        printLives();
        printWord(word);

        cout << "\n\nInserisci carattere:\n   >";
        cin >> inserted;

        // aggiungo il carattere usato (solo se non c'è già)
        if (usedChars.find(inserted) == notFound) {
            usedChars += inserted;
        }

        // se il carattere non è nella parola c'è un errore
        if (word.find(inserted) == notFound) {
            cout << "ERRORE!!" << endl;
            errors++;
        }

        // controllo se tutte le lettere della parola sono state già usate -> parola indovinata
        for (char c : word) {
            if (usedChars.find(c) == notFound) {
                endFor = false;
                break;
            }

            endFor = true;
        }

    } while (!endFor && errors < 5);

    cout << "\n\n";

    if (errors == 5) {
        cout << "Hai perso!" << endl;
        cout << "La parola era \"" << word << "\"";
    } else {
        cout << "Hai vinto!" << endl;
        cout << "Hai indovinato la parola \"" << word << "\" con " << errors << " error" << (errors == 1 ? "e" : "i")
             << "!";
    }

    return 0;
}
