#ifndef DS_EX2_PLAYER
#define DS_EX2_PLAYER

class Player {

private:
	int playerID;
	int level;
	int score;
    int groupID;

public:
    //consructor
    Player(int id, int player_level,int score, int group_id) : playerID(id), level(player_level),score(score), groupID(group_id) {};
    //destructor
	~Player() = default;
    //consructor
	Player(const Player& other_player) = default;
    //consructor
	Player& operator=(const Player& other_player) = default;

	/**
	 * Get player group id
	 * @return groupID
	 */
    int getGroup();

    /**
     * Get player level
     * @return level
     */
	int getLevel();

	/**
	 * Get player id
	 * @return playerID
	 */
	int getId();

	/**
	 * Get player score
	 * @return
	 */
	int getScore();

	/**
	 * Set a new player level
	 * @param new_level
	 */
	void setLevel(int new_level);

	/**
	 * Set a new group id
	 * @param new_group_id
	 */
	void setGroup(int new_group_id);

	/**
	 * Set player score
	 * @param score
	 */
	void setScore(int score);
};

#endif