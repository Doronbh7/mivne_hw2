#include "PlayersManager.h"
#include "helper_functions.h"
#include <cstdlib>


PlayersManager::~PlayersManager() {
    LevelTree->deleteAllDataInTree();
    delete LevelTree;
    delete playersTree;
    delete[] sumScoreSystemPlayersLevelZero;
    delete groups;
    delete players;
}

StatusType PlayersManager::MergeGroups(int GroupID1, int GroupID2) {
    try{
        if((GroupID1>(this->k)) || (GroupID2>(this->k))){
            return INVALID_INPUT;
        }
        Group* group1 = groups->Find(GroupID1);
        Group* group2 = groups->Find(GroupID2);
        if (group1 == group2) {
            return SUCCESS;
        }
        groups->UnionGroups(GroupID1, GroupID2);
        int group1_root_id = groups->getRootGroup(GroupID1);
        Group* group1_root = groups->Find(group1_root_id);

        int group1_players = group1->getPlayersTree()->getSize();
        int group2_players = group2->getPlayersTree()->getSize();
        int combined_players_array_size = group1_players + group2_players;

        int group1_levels = group1->getLevelTree()->getSize();
        int group2_levels = group2->getLevelTree()->getSize();
        int combined_levels_array_size = group1_levels + group2_levels;
        int combined_levels_array_size_no_duplicates = 0;

        Player** group_a_players_array = new Player * [group1_players];
        Player** group_b_players_array = new Player * [group2_players];
        Player** combined_players_array = new Player * [combined_players_array_size];
        Key* player_keys_array = new Key[combined_players_array_size];

        Level** group_a_levels_array = new Level * [group1_levels];
        Level** group_b_levels_array = new Level * [group2_levels];
        Level** tmp_combined_levels_array = new Level * [combined_levels_array_size];

        (group1->getPlayersTree())->GetKSmallestInOrderArray(group_a_players_array, group1_players);
        (group2->getPlayersTree())->GetKSmallestInOrderArray(group_b_players_array, group2_players);
        (group1->getLevelTree())->GetKSmallestInOrderArray(group_a_levels_array, group1_levels);
        (group2->getLevelTree())->GetKSmallestInOrderArray(group_b_levels_array, group2_levels);

        mergeLevelArrays(group_a_levels_array, group1_levels, group_b_levels_array, group2_levels, tmp_combined_levels_array);
        Level** combined_levels_array = removeDuplicatesFromLevelArray(tmp_combined_levels_array, combined_levels_array_size, &combined_levels_array_size_no_duplicates);

        combined_levels_array_size = combined_levels_array_size_no_duplicates;
        int* level_keys_array = new int[combined_levels_array_size];

        for (int i = 0; i < combined_levels_array_size; i++) {
            level_keys_array[i] = combined_levels_array[i]->getLevel();
        }
        LevelAVLTree<int>* combined_levels_tree = new LevelAVLTree<int>;
        combined_levels_tree->sortedArrayToAVL(combined_levels_array, level_keys_array, combined_levels_array_size);

        mergePlayerArrays(group_a_players_array, group1_players, group_b_players_array, group2_players, combined_players_array);

        PlayerAVLTree<Key>* combined_players_tree = new PlayerAVLTree<Key>;

        for (int i = 0; i < combined_players_array_size; i++) {
            Key tmp_key(combined_players_array[i]->getId(),combined_players_array[i]->getLevel());
            player_keys_array[i] = tmp_key;
        }
        combined_players_tree->sortedArrayToAVL(combined_players_array, player_keys_array, combined_players_array_size);
        
        delete group1->getPlayersTree();
        delete group1->getLevelTree();
        delete group2->getPlayersTree();
        delete group2->getLevelTree();

        if (group1_root == group1) {
            //root is group 1
            group1->setLevelTree(combined_levels_tree);
            group1->setPlayersTree(combined_players_tree);
            group2->setPlayersTree(nullptr);
            group2->setLevelTree(nullptr);
            uniteGroups(group1, group2);
        }
        else {
            //root is group 2
            group2->setLevelTree(combined_levels_tree);
            group2->setPlayersTree(combined_players_tree);
            group1->setPlayersTree(nullptr);
            group1->setLevelTree(nullptr);
            uniteGroups(group2, group1);
        }
        delete[] group_a_players_array;
        delete[] group_a_levels_array;
        delete[] group_b_players_array;
        delete[] group_b_levels_array;
        delete[] player_keys_array;
        delete[] level_keys_array;
        delete[] tmp_combined_levels_array;
        delete[] combined_levels_array;
        delete[] combined_players_array;

    }catch(std::bad_alloc& exception){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;

}

StatusType PlayersManager::AddPlayer(int PlayerID, int GroupID, int score) {
    try{

        if((GroupID>(this->k)) || (score>(this->scale))){
            return INVALID_INPUT;
        }

        Player* data=new Player(PlayerID,0,score,GroupID);



        if((players->insert(data))==false){
            delete(data);
            return FAILURE;
        }
        this->systemPlayersLevelZero=(systemPlayersLevelZero+1);
        this->sumScoreSystemPlayersLevelZero[score]++;
        Group* current_group=groups->Find(GroupID);
        current_group->increaseSumScoreGroupPlayersLevelZeroByScore(score);
        current_group->increaseGroupPlayersLevelZeroByOne();
        current_group->increaseNumGroupPlayersByOne();


    }catch(std::bad_alloc& exception){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType PlayersManager::RemovePlayer(int PlayerID)  {
    try{


        ListNode<Player>* player_node=players->getById(PlayerID);
        if(player_node== nullptr){
            return FAILURE;
        }

        Player* player_data=player_node->getData();
        int player_score=player_data->getScore();
        int player_level=player_data->getLevel();
        int group_id=player_data->getGroup();
        Group* current_group=groups->Find(group_id);
        if(player_level==0){
            this->systemPlayersLevelZero=(systemPlayersLevelZero-1);
            this->sumScoreSystemPlayersLevelZero[player_score]--;

            current_group->decreaseSumScoreGroupPlayersLevelZeroByScore(player_score);
            current_group->decreaseGroupPlayersLevelZeroByOne();
            current_group->decreaseNumGroupPlayersByOne();

        }
        if(player_level>0){

            LevelAVLTree<int>* group_level_tree=current_group->getLevelTree();
            LevelAVLNode<int>* group_level_node =group_level_tree->getNodeByKey(player_level);
            Level* group_level_data = group_level_node->getData();
            int group_level_players_num=group_level_data->getPlayersNum();
            if(group_level_players_num==1){
                group_level_tree->deleteNodeByKey(player_level);
                delete group_level_data;
            }
            if(group_level_players_num!=1){
                group_level_players_num=group_level_players_num-1;
                group_level_data->setPlayersNum(group_level_players_num);
                int* score_group_array=group_level_data->getPlayersScoreArray();
                score_group_array[player_score]--;
                group_level_tree->UpdateScoreInLevel(false,player_score,player_level);

            }

            LevelAVLNode<int>* level_node =LevelTree->getNodeByKey(player_level);
            Level* level_data = level_node->getData();
            int level_players_num=level_data->getPlayersNum();
            if(level_players_num==1){
                LevelTree->deleteNodeByKey(player_level);
                delete level_data;
            }

            if(level_players_num!=1){
                level_players_num=level_players_num-1;
                level_data->setPlayersNum(level_players_num);
                int* score_array=level_data->getPlayersScoreArray();
                score_array[player_score]--;
                LevelTree->UpdateScoreInLevel(false,player_score,player_level);

            }


            current_group->decreaseNumGroupPlayersByOne();
            current_group->removePlayerFromTree(player_data);
            Key temp_key(player_data->getId(), player_data->getLevel());
            playersTree->deleteNodeByKey(temp_key);

        }

        players->Delete(PlayerID);


    }catch(std::bad_alloc& exception){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType PlayersManager::IncreasePlayerIDLevel(int PlayerID,
                                                 int LevelIncrease) {
    try {

        ListNode<Player>* player_node = players->getById(PlayerID);
        if (player_node == nullptr) {
            return FAILURE;
        }
        Player* player_data = player_node->getData();
        int current_player_level = player_data->getLevel();
        int group_id = player_data->getGroup();
        int player_score = player_data->getScore();
        int new_player_level = current_player_level + LevelIncrease;
        Key current_player_key(PlayerID, current_player_level);
        Key new_player_key(PlayerID, new_player_level);

        Group* current_group = groups->Find(group_id);
        if (current_player_level == 0) {
            sumScoreSystemPlayersLevelZero[player_score]--;
            this->systemPlayersLevelZero = (systemPlayersLevelZero - 1);
            current_group->decreaseGroupPlayersLevelZeroByOne();
            current_group->decreaseSumScoreGroupPlayersLevelZeroByScore(player_score);

            LevelAVLTree<int>* group_levels_tree = current_group->getLevelTree();
            LevelAVLNode<int>* new_level_node = LevelTree->getNodeByKey(new_player_level);
            if (new_level_node != nullptr) {
                Level* new_level = new_level_node->getData();
                int* new_level_score_array = new_level->getPlayersScoreArray();
                new_level_score_array[player_score]++;

                int players_in_level = new_level->getPlayersNum();
                new_level->setPlayersNum(players_in_level + 1);
                LevelTree->UpdateScoreInLevel(true, player_score, new_player_level);
                LevelAVLNode<int>* group_new_level_node = group_levels_tree->getNodeByKey(new_player_level);
                if (group_new_level_node != nullptr) {
                    Level* group_new_level = group_new_level_node->getData();
                    int* group_new_level_score_array = group_new_level->getPlayersScoreArray();
                    group_new_level_score_array[player_score]++;

                    int group_players_in_level = group_new_level->getPlayersNum();
                    group_new_level->setPlayersNum(group_players_in_level + 1);
                    group_levels_tree->UpdateScoreInLevel(true, player_score, new_player_level);
                }

                if (group_new_level_node == nullptr) {
                    Level* group_new_level = new Level(new_player_level, 1);
                    int* group_new_level_score_array = group_new_level->getPlayersScoreArray();
                    group_new_level_score_array[player_score]++;
                    group_levels_tree->insertNode(new_player_level, group_new_level);
                }

            }
            else {
                Level* new_level = new Level(new_player_level, 1);
                int* score_array = new_level->getPlayersScoreArray();
                score_array[player_score]++;
                LevelTree->insertNode(new_player_level, new_level);

                Level* group_new_level = new Level(new_player_level, 1);
                int* group_new_level_score_array = group_new_level->getPlayersScoreArray();
                group_new_level_score_array[player_score]++;
                group_levels_tree->insertNode(new_player_level, group_new_level);
            }
            player_data->setLevel(new_player_level);
            PlayerAVLTree<Key>* group_players_tree = current_group->getPlayersTree();
            group_players_tree->insertNode(new_player_key, player_data);
            playersTree->insertNode(new_player_key, player_data);

        }

        if (current_player_level != 0) {
            LevelAVLTree<int>* group_levels_tree = current_group->getLevelTree();
            LevelAVLNode<int>* current_level_node = LevelTree->getNodeByKey(current_player_level);
            LevelAVLNode<int>* new_level_node = LevelTree->getNodeByKey(new_player_level);
            Level* current_level = current_level_node->getData();
            LevelAVLNode<int>* group_current_level_node = group_levels_tree->getNodeByKey(current_player_level);
            LevelAVLNode<int>* group_new_level_node = group_levels_tree->getNodeByKey(new_player_level);
            Level* group_current_level = group_current_level_node->getData();

            int current_level_number_of_players = current_level->getPlayersNum();
            int group_current_level_number_of_players = group_current_level->getPlayersNum();

            if (new_level_node != nullptr) {
                Level* new_level = new_level_node->getData();
                int* new_level_score_array = new_level->getPlayersScoreArray();
                new_level_score_array[player_score]++;
                int players_in_level = new_level->getPlayersNum();
                new_level->setPlayersNum(players_in_level + 1);
                LevelTree->UpdateScoreInLevel(true, player_score, new_player_level);

                if (group_new_level_node != nullptr) {
                    Level* group_new_level = group_new_level_node->getData();
                    int* group_new_level_score_array = group_new_level->getPlayersScoreArray();
                    group_new_level_score_array[player_score]++;

                    int group_players_in_level = group_new_level->getPlayersNum();
                    group_new_level->setPlayersNum(group_players_in_level + 1);
                    group_levels_tree->UpdateScoreInLevel(true, player_score, new_player_level);
                }

                if (group_new_level_node == nullptr) {
                    Level* group_new_level = new Level(new_player_level, 1);
                    int* group_new_level_score_array = group_new_level->getPlayersScoreArray();
                    group_new_level_score_array[player_score]++;
                    group_levels_tree->insertNode(new_player_level, group_new_level);
                }
            }
            if (new_level_node == nullptr) {
                Level* new_level = new Level(new_player_level, 1);
                int* new_level_score_array = new_level->getPlayersScoreArray();
                new_level_score_array[player_score]++;
                LevelTree->insertNode(new_player_level, new_level);

                Level* group_new_level = new Level(new_player_level, 1);
                int* group_new_level_score_array = group_new_level->getPlayersScoreArray();
                group_new_level_score_array[player_score]++;
                group_levels_tree->insertNode(new_player_level, group_new_level);

            }

            if (current_level_number_of_players == 1) {
                LevelTree->deleteNodeByKey(current_player_level);
                delete current_level;
                group_levels_tree->deleteNodeByKey(current_player_level);
                delete group_current_level;
            }
            if (current_level_number_of_players != 1) {

                if (group_current_level_number_of_players == 1) {
                    group_levels_tree->deleteNodeByKey(current_player_level);
                    delete group_current_level;

                }
                if (group_current_level_number_of_players != 1) {
                    group_current_level_number_of_players = group_current_level_number_of_players - 1;
                    group_current_level->setPlayersNum(group_current_level_number_of_players);
                    int* score_group_array = group_current_level->getPlayersScoreArray();
                    score_group_array[player_score]--;
                    group_levels_tree->UpdateScoreInLevel(false, player_score, current_player_level);

                }

                current_level_number_of_players = current_level_number_of_players - 1;
                current_level->setPlayersNum(current_level_number_of_players);
                int* score_array = current_level->getPlayersScoreArray();
                score_array[player_score]--;
                LevelTree->UpdateScoreInLevel(false, player_score, current_player_level);


            }

            player_data->setLevel(new_player_level);
            PlayerAVLTree<Key>* group_players_tree = current_group->getPlayersTree();
            group_players_tree->deleteNodeByKey(current_player_key);
            playersTree->deleteNodeByKey(current_player_key);
            group_players_tree->insertNode(new_player_key, player_data);
            playersTree->insertNode(new_player_key, player_data);
        }


    }
    catch (std::bad_alloc& exception) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType PlayersManager::ChangePlayerIDScore(int PlayerID, int NewScore) {
    try{

        if(NewScore> (this->scale)){
            return INVALID_INPUT;
        }
        ListNode<Player>* player_node = players->getById(PlayerID);
        if (player_node == nullptr) {
            return FAILURE;
        }
        Player* player_data = player_node->getData();
        int current_player_level = player_data->getLevel();
        int old_player_score = player_data->getScore();
        int group_id = player_data->getGroup();
        Group* current_group = groups->Find(group_id);

        if (current_player_level == 0) {
            player_data->setScore(NewScore);
            sumScoreSystemPlayersLevelZero[old_player_score]--;
            sumScoreSystemPlayersLevelZero[NewScore]++;
            current_group->getSumScoreGroupPlayersLevelZero()[old_player_score]--;
            current_group->getSumScoreGroupPlayersLevelZero()[NewScore]++;

        } else {
            player_data->setScore(NewScore);
            LevelAVLTree<int>* group_levels_tree = current_group->getLevelTree();
            LevelAVLNode<int>* group_level_node = group_levels_tree->getNodeByKey(current_player_level);
            Level* group_level_data = group_level_node->getData();
            int* group_level_score_array = group_level_data->getPlayersScoreArray();

            LevelAVLNode<int>* system_level_node = LevelTree->getNodeByKey(current_player_level);
            Level* system_level_data = system_level_node->getData();
            int* system_level_score_array = system_level_data->getPlayersScoreArray();

            system_level_score_array[old_player_score]--;
            system_level_score_array[NewScore]++;
            group_level_score_array[old_player_score]--;
            group_level_score_array[NewScore]++;

            LevelTree->UpdateScoreInLevel(false, old_player_score, current_player_level);
            group_levels_tree->UpdateScoreInLevel(false, old_player_score, current_player_level);
            LevelTree->UpdateScoreInLevel(true, NewScore, current_player_level);
            group_levels_tree->UpdateScoreInLevel(true, NewScore, current_player_level);
        }
    }catch(std::bad_alloc& exception){
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType PlayersManager::GetPercentOfPlayersWithScoreInBounds(int GroupID,
    int score,
    int lowerLevel,
    int higherLevel,
    double* players) {
    try {

        if (GroupID > (this->k)) {
            return INVALID_INPUT;
        }
        if ((lowerLevel > higherLevel) || (higherLevel < 0)) {
            return FAILURE;
        }

        int* sum_array_lower = new int[201];
        int* sum_array_higher = new int[201];
        int* sum_array = new int[201];

        for (int i = 0; i < 201; i++) {
            sum_array_lower[i] = 0;
            sum_array_higher[i] = 0;
            sum_array[i] = 0;
        }

        if (GroupID > 0) {

            Group* current_group = groups->Find(GroupID);
            int* level_zero_score_array_group = current_group->getSumScoreGroupPlayersLevelZero();
            LevelAVLTree<int>* group_level_tree = current_group->getLevelTree();
            group_level_tree->getSumArrayUntilKey(lowerLevel, sum_array_lower,
                0);
            group_level_tree->getSumArrayUntilKey(higherLevel, sum_array_higher,
                1);

            if (lowerLevel <= 0) {
                for (int i = 0; i < 201; i++) {
                    sum_array[i] = sum_array_higher[i] - sum_array_lower[i] +
                        level_zero_score_array_group[i];

                }

            }
            else {
                for (int i = 0; i < 201; i++) {
                    sum_array[i] = sum_array_higher[i] - sum_array_lower[i];

                }

            }

        }

        if (GroupID == 0) {

            LevelTree->getSumArrayUntilKey(lowerLevel, sum_array_lower, 0);
            LevelTree->getSumArrayUntilKey(higherLevel, sum_array_higher, 1);

            if (lowerLevel <= 0) {
                for (int i = 0; i < 201; i++) {
                    sum_array[i] = sum_array_higher[i] - sum_array_lower[i] +
                        this->sumScoreSystemPlayersLevelZero[i];

                }

            }
            else {
                for (int i = 0; i < 201; i++) {
                    sum_array[i] = sum_array_higher[i] - sum_array_lower[i];

                }

            }

        }

        double num_players_in_bounds = 0;

        for (int i = 0; i < 201; i++) {
            num_players_in_bounds += sum_array[i];
        }
        if (num_players_in_bounds == 0) {
            return FAILURE;
        }

        if ((score < 1) || (score > (this->scale))) {
            delete[] sum_array_lower;
            delete[] sum_array_higher;
            delete[] sum_array;
            *players = 0;
            return SUCCESS;

        }
        double num_of_players_with_score_in_bounds = sum_array[score];


        double temp = (num_of_players_with_score_in_bounds / num_players_in_bounds);
        double percent = temp * 100;
        *players = percent;



        delete[] sum_array_lower;
        delete[] sum_array_higher;
        delete[] sum_array;

    }
    catch (std::bad_alloc& exception) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType PlayersManager::AverageHighestPlayerLevelByGroup(int GroupID, int m,
    double* level) {
    try {

        if (GroupID > (this->k)) {
            return INVALID_INPUT;
        }




        if (GroupID > 0) {

            int group_level_sum = 0;

            Group* current_group = groups->Find(GroupID);
            int num_players_group = current_group->getNumberOfPlayers();

            if (num_players_group < m) {
                return FAILURE;
            }

            PlayerAVLTree<Key>* group_players_tree = current_group->getPlayersTree();
            int tree_size = group_players_tree->getSize();
            int group_all_tree_sum = group_players_tree->getSumLevelUntilIndex(tree_size);
            if (m >= tree_size) {
                group_level_sum = group_all_tree_sum;

            }
            else {
                int temp_group = tree_size - m;
                int temp_sum_group = group_players_tree->getSumLevelUntilIndex(temp_group);
                group_level_sum = group_all_tree_sum - temp_sum_group;

            }
            double avergae_group = double(group_level_sum)/m;
            *level = avergae_group;
        }

        if (GroupID == 0) {
            int level_sum = 0;

            int num_players = (this->systemPlayersLevelZero) + (this->playersTree->getSize());

            if (num_players < m) {
                return FAILURE;
            }

            int size = this->playersTree->getSize();
            int all_tree_sum = this->playersTree->getSumLevelUntilIndex(size);

            if (m >= size) {
                level_sum = all_tree_sum;

            }
            else {
                int temp = size - m;
                int temp_sum = this->playersTree->getSumLevelUntilIndex(temp);
                level_sum = all_tree_sum - temp_sum;

            }

            double avergae = double(level_sum)/m;
            *level = avergae;

        }


    }
    catch (std::bad_alloc& exception) {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

