#ifndef DS_EX1_GROUP
#define DS_EX1_GROUP

#include "Player.h"
#include "PlayerAVLTree.h"
#include "LevelAVLTree.h"
#include "Key.h"

class Group {

private:
	int groupID;
	int numGroupPlayers;
	int groupPlayersLevelZero;
	int* sumScoreGroupPlayersLevelZero;
	LevelAVLTree<int>* LevelTree;
	PlayerAVLTree<Key>* playersTree;

public:

    //consructor
	Group(int id);
    //destructor
	~Group();
    //consructor
	Group(const Group& other_group) = default;
    //consructor
	Group& operator=(const Group& other_group) = default;

	/**
	 * Get a pointer to the players tree
	 * @return playersTree
	 */
	PlayerAVLTree<Key>* getPlayersTree();

	/**
	 * Set a new players tree
	 * @param tree - pointer to new tree
	 */
	void setPlayersTree(PlayerAVLTree<Key>* tree);


	/**
	 * Get a pointer to the level tree
	 * @return LevelTree
	 */
	LevelAVLTree<int>* getLevelTree();

	/**
	 * Set a new level tree
	 * @param tree - pointer to new tree
	 */
	void setLevelTree(LevelAVLTree<int>* tree);

	/**
	 * Get the group id
	 * @return groupID
	 */
	int getGroupID();

	/**
	 * Set sumScoreGroupPlayersLevelZero
	 * @param new_array
	 */
	void setSumScoreGroupPlayersLevelZero(int* new_array);
	/**
	 * Get sumScoreGroupPlayersLevelZero
	 * @return
	 */
	int* getSumScoreGroupPlayersLevelZero();

	/**
	 * Increase SumScoreGroupPlayersLevelZero By Score
	 * @param score
	 */
	void increaseSumScoreGroupPlayersLevelZeroByScore(int score);

	/**
	 * Decrease SumScoreGroupPlayersLevelZero By Score
	 * @param score
	 */
	void decreaseSumScoreGroupPlayersLevelZeroByScore(int score);

	/**
	 * Get number of players in the group
	 * @return number of players in the group
	 */
	int getNumberOfPlayers();


	/**
	 * Get number of players in level 0
	 * @return
	 */
	int getGroupPlayersLevelZero();

	/**
	 * Set number of players in the group
	 */
	void setNumberOfPlayers(int new_number);

	/**
	 * Set number of players in level 0
	 */
	void SetGroupPlayersLevelZero(int new_number);

	/**
	 * Increase NumGroupPlayers by one
	 */
	void increaseNumGroupPlayersByOne();

	/**
	 * Decrease NumGroupPlayers by one
	 */
	void decreaseNumGroupPlayersByOne();

	/**
	 * Increase GroupPlayersLevelZero by one
	 */
	void increaseGroupPlayersLevelZeroByOne();

	/**
	 * Decrease GroupPlayersLevelZero by one
	 */
	void decreaseGroupPlayersLevelZeroByOne();




	/**
	 * Add player to players tree
	 * @param player -new player
	 */
	void addPlayerToPlayerTree(Player* player);

	/**
	 * Remove player from players tree
	 * @param player the removed player
	 */
	void removePlayerFromTree(Player* player);
};

#endif
