#include "Level.h"

Level::~Level() {
    delete [] players_score;
}

int Level::getLevel() {
    return this->level;
}

int Level::getPlayersNum() {
    return this->number_of_players;
}

int *Level::getPlayersScoreArray() {
    return this->players_score;
}

void Level::setLevel(int level_num) {
    level=level_num;
}

void Level::setPlayersNum(int num) {
    number_of_players=num;
}

