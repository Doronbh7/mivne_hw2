#ifndef DS_EX2_LEVEL
#define DS_EX2_LEVEL

class Level {

private:
	int level;
	int number_of_players;
	int* players_score;

public:

    //consructor
	Level(int Level,int Num_players):level(Level),number_of_players(Num_players){
        players_score=new int[201];
        for (int i=0;i<201;i++){
            players_score[i]=0;
        }

    }
    //destructor
	~Level();
    //consructor
	Level(const Level& other_level) = default;
    //consructor
	Level& operator=(const Level& other_level) = default;

	/**
	 * Get a pointer to players score array
	 * @return
	 */
	int* getPlayersScoreArray();

	/**
	 * Get level number
	 * @return
	 */
	int getLevel();

	/**
	 * Get the number of players in the level
	 * @return
	 */
	int getPlayersNum();

	/**
	 * Set level
	 * @param level_num
	 */
	void setLevel(int level_num);

	/**
	 * Set number of players in the level
	 * @param num
	 */
	void setPlayersNum(int num);


};

#endif
