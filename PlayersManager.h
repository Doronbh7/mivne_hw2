#ifndef LIBRARY2_CPP_PLAYERSMANAGER_H
#define LIBRARY2_CPP_PLAYERSMANAGER_H

#include <memory>

#include "Group.h"
#include "Level.h"
#include "Player.h"
#include "library2.h"
#include "Key.h"
#include "PlayerAVLTree.h"
#include "LevelAVLTree.h"
#include "UnionFind.h"
#include "hashTable.h"

class PlayersManager {


    int k;
    int scale;
    int systemPlayersLevelZero;
    int* sumScoreSystemPlayersLevelZero;
    LevelAVLTree<int>* LevelTree;
    PlayerAVLTree<Key>* playersTree;
    UnionFind<Group>* groups;
    hashTable<Player>* players;




public:
    PlayersManager(int k, int scale):k(k),scale(scale){
        systemPlayersLevelZero=0;
        sumScoreSystemPlayersLevelZero=new int[201];
        for (int i=0;i<201;i++){
            sumScoreSystemPlayersLevelZero[i]=0;
        }
        this->LevelTree=new LevelAVLTree<int>;
        this->playersTree=new PlayerAVLTree<Key>;
        this->groups=new UnionFind<Group>(k);
        this->players=new hashTable<Player>;
    }
    ~PlayersManager();




    /*
     * Merge GroupID1 and GroupID2
     * @param GroupID1
     * @param GroupID2
     * @return
     */
    StatusType MergeGroups(int GroupID1, int GroupID2);


    /*
     * Add new player to the system
     * @param PlayerID
     * @param GroupID
     * @param score
     * @return
     */
    StatusType AddPlayer(int PlayerID, int GroupID, int score);

    /*
     * Remove player from the system
     * @param PlayerID
     * @return
     */
    StatusType RemovePlayer(int PlayerID);

    /*
     *Increase player level by LevelIncrease
     * @param PlayerID
     * @param LevelIncrease
     * @return
     */
    StatusType IncreasePlayerIDLevel(int PlayerID, int LevelIncrease);

    /*
     *Change player score to NewScore
     * @param PlayerID
     * @param NewScore
     * @return
     */
    StatusType ChangePlayerIDScore(int PlayerID, int NewScore);

    /*
     *Get Percent of the players with the score in levels that in range [lowerLevel, higherLevel] in the group(or in all system if groupid=0)
     * @param GroupID
     * @param score
     * @param lowerLevel
     * @param higherLevel
     * @param players
     * @return
     */
    StatusType GetPercentOfPlayersWithScoreInBounds(int GroupID, int score, int lowerLevel, int higherLevel,
                                                    double * players);

    /*
     *Calculate the average level of the m players with the highest level in group(or in all system if groupid=0)
     * @param GroupID
     * @param m
     * @param level
     * @return
     */
    StatusType AverageHighestPlayerLevelByGroup(int GroupID, int m, double * level);

};

#endif //LIBRARY2_CPP_PLAYERSMANAGER_H
