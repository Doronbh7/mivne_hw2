#include "Player.h"

int Player::getId() {
	return playerID;
}
int Player::getLevel() {
	return level;
}
void Player::setLevel(int new_level) {
	level = new_level;
	return;
}
int Player::getGroup() {
	return groupID;
}
void Player::setGroup(int new_group_id) {
	groupID = new_group_id;
	return;
}

int Player::getScore() {
    return score;
}

void Player::setScore(int new_score) {
    this->score=new_score;
}