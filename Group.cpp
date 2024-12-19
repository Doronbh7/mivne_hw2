#include "Group.h"

Group::Group(int id) {
	groupID = id;
	numGroupPlayers=0;
	groupPlayersLevelZero=0;
	LevelTree = new LevelAVLTree<int>;
	playersTree=new PlayerAVLTree<Key>;
    sumScoreGroupPlayersLevelZero=new int[201];
    for (int i=0;i<201;i++){
        sumScoreGroupPlayersLevelZero[i]=0;
    }

}
Group::~Group() {
    if (LevelTree != nullptr) {
        LevelTree->deleteAllDataInTree();
        delete LevelTree;
    }
    if (playersTree != nullptr) {
        delete playersTree;
    }
    delete [] sumScoreGroupPlayersLevelZero;
}


PlayerAVLTree<Key>* Group::getPlayersTree() {
    return playersTree;
}

void Group::setPlayersTree(PlayerAVLTree<Key> *tree) {
    (this->playersTree)=tree;
}

LevelAVLTree<int>* Group::getLevelTree() {
    return LevelTree;
}

void Group::setLevelTree(LevelAVLTree<int>* tree) {
    this->LevelTree=tree;
}


int Group::getGroupID() {
    return this->groupID;
}

void Group::setSumScoreGroupPlayersLevelZero(int* new_array) {
    this->sumScoreGroupPlayersLevelZero=new_array;

}

int* Group::getSumScoreGroupPlayersLevelZero() {
    return sumScoreGroupPlayersLevelZero;

}

void Group::increaseSumScoreGroupPlayersLevelZeroByScore(int score) {
    this->sumScoreGroupPlayersLevelZero[score]++;

}

void Group::decreaseSumScoreGroupPlayersLevelZeroByScore(int score) {
    this->sumScoreGroupPlayersLevelZero[score]--;

}

void Group::setNumberOfPlayers(int new_number) {
    this->numGroupPlayers = new_number;
}

int Group::getNumberOfPlayers() {
    return this->numGroupPlayers;
}

void Group::SetGroupPlayersLevelZero(int new_number) {
    this->groupPlayersLevelZero = new_number;
}

int Group::getGroupPlayersLevelZero() {
    return this->groupPlayersLevelZero;
}

void Group::increaseNumGroupPlayersByOne() {
    numGroupPlayers=numGroupPlayers+1;
}

void Group::decreaseNumGroupPlayersByOne() {
    numGroupPlayers=numGroupPlayers-1;
}

void Group::increaseGroupPlayersLevelZeroByOne() {
    groupPlayersLevelZero=groupPlayersLevelZero+1;
}

void Group::decreaseGroupPlayersLevelZeroByOne() {
    groupPlayersLevelZero=groupPlayersLevelZero-1;
}

void Group::addPlayerToPlayerTree(Player *player) {
    Key tmp_key(player->getId(), player->getLevel());
    playersTree->insertNode(tmp_key, player);
    player->setGroup(groupID);
    return;

}


void Group::removePlayerFromTree(Player *player) {
    Key temp_key(player->getId(), player->getLevel());
    playersTree->deleteNodeByKey(temp_key);
    return;

}


