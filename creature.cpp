#include "creature.h"

Creature::Creature() {  return; }

Creature::Creature(Board* in_board) {
    board = in_board;
}

int Creature::get_row() {   return row; }

int Creature::get_col() {   return col; }

int Creature::get_pos() {
    return 10 * row + col;
}

bool Creature::on_board() {
    return  row > 0 &&
            col > 0 &&
            row < board->get_board_len() - col;
}