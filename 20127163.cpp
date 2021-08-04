#include<iostream>
#include<fstream>
#include<string>
#include<windows.h>
#include<stdlib.h>

struct Node {
    std::string text;
    Node* yes_ans;
    Node* no_ans;
};
typedef Node* Tree;

void readFromFile(Tree& T, std::fstream& f) {
    std::string input;
    std::getline(f, input);

    if (input != "#") {
        T = new Node;
        T->text = input;
        readFromFile(T->yes_ans, f);
        readFromFile(T->no_ans, f);
    }
    else
        T = NULL;
}

void writeToFile(Tree& T, std::fstream& f) {
    if (T != NULL) {
        f << T->text << std::endl;
        writeToFile(T->yes_ans, f);
        writeToFile(T->no_ans, f);
    }
    else
        f << "#" << std::endl;
}

void dot(int n) {
    for (int i = 0; i < n; i++)
    {
        Sleep(800);
        std::cout << ".";
    }
    std::cout << std::endl;
}

int menu() {
    int temp;

    std::system("cls");
    std::system("color 03");
    std::cout << " ---------------------- " << std::endl;
    std::cout << "| *** ANIMALS GAME *** |" << std::endl;
    std::cout << "|                      |" << std::endl;
    std::cout << "|     1. Play game     |" << std::endl;
    std::cout << "|     2. Quit game     |" << std::endl;
    std::cout << " ---------------------- " << std::endl;
    std::cout << "Please make your selection: ";
    std::cin >> temp;
    std::cout << "Loading ";
    dot(3);

    return temp;
}

void header() {
    std::system("cls");
    std::cout << " ---------------------- " << std::endl;
    std::cout << "  *** ANIMALS GAME ***  " << std::endl;
    std::cout << " ---------------------- " << std::endl;
}

void expandGame(Tree& T) {
    char temp;

    std::cout << "Would you like to expand the game tree (y/n): ";
    std::cin >> temp;
    std::cin.ignore();

    if (temp == 'y') {
        T->yes_ans = new Node;
        T->yes_ans->no_ans = NULL;
        T->yes_ans->yes_ans = NULL;
        T->no_ans = new Node;
        T->no_ans->no_ans = NULL;
        T->no_ans->yes_ans = NULL;

        T->no_ans->text = T->text;
        std::cout << "Enter a new animal in the form of a question," << std::endl
            << "e.g., 'Is it a duck?':" << std::endl;
        std::getline(std::cin, T->yes_ans->text);
        std::cout << "Now enter a question for which the answer is 'yes' for your new animal" << std::endl
            << "and which does not contradict your previous answers:" << std::endl;
        std::getline(std::cin, T->text);
    }
}

void playGame(Tree& T) {
    if (T != NULL) {
        char temp;

        std::cout << T->text << "(y/n): ";
        std::cin >> temp;
        std::cin.ignore();

        if (temp == 'y') {
            if (T->yes_ans == NULL)
                std::cout << "HEY! I guessed your animal!" << std::endl;
            else
                playGame(T->yes_ans);
        }
        else {
            if (T->no_ans == NULL) {
                std::cout << "NAH! I don't know!" << std::endl;
                expandGame(T);
            }
            else
                playGame(T->no_ans);
        }
    }
}

void processingGame() {
    Tree T = NULL;
    std::fstream f;
    int temp;

    do {
        temp = menu();

        if (temp == 1) {
            header();

            f.open("animals.txt", std::ios::in);
            readFromFile(T, f);
            f.close();

            playGame(T);

            f.open("animals.txt", std::ios::out);
            writeToFile(T, f);
            f.close();

            system("pause");
        }
        else {
            header();

            std::cout << "Goodbye ";
            dot(3);
        }
    } while (temp == 1);
}

int main() {
    processingGame();

    return 0;
}