#include <iostream>
#include "board.h"
using namespace std;

int main() {
    Board board;
    int** cubes = board.get_cubes();
    board.print();
    return 0;
}