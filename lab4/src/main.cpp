#include "task.h"


int main() {
    SetConsoleOutputCP(CP_UTF8);
    task1::main_task1();
    cout << "Методом простых итераций:\n";
    task2::main_task2();
    cout << "Методом Ньютона:\n";
    task3::main_task3();
    system("python ../src/check_minimum.py");
    return 0;
}