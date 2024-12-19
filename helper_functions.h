#ifndef DS_EX1_HELPER_FUNCS
#define DS_EX1_HELPER_FUNCS

#include <memory>
#include "Player.h"
#include "Key.h"
#include "Level.h"

void mergePlayerArrays(Player** array_a, int array_a_size, Player** array_b, int array_b_size, 
	Player** array_c) {

	int i = 0;
	int j = 0;
	int k = 0;

	while ((i < array_a_size) && (j < array_b_size)) {
		Key tmp_key_a(array_a[i]->getId(), array_a[i]->getLevel());
		Key tmp_key_b(array_b[j]->getId(), array_b[j]->getLevel());
		if (tmp_key_a < tmp_key_b) {
			array_c[k++] = array_a[i++];
		}
		else {
			array_c[k++] = array_b[j++];
		}
	}
	while (i < array_a_size) {
		array_c[k++] = array_a[i++];
	}
	while (j < array_b_size) {
		array_c[k++] = array_b[j++];
	}
}

void uniteLevelZeroPlayerArrays(int* array_a, int* array_b, int array_size) {
	for (int i = 0; i < array_size; i++) {
		array_a[i] += array_b[i];
	}
}
void uniteLevels(Level* level1, Level* level2) {
	if (level1->getLevel() == level2->getLevel()) {
		int* level1_score_array = level1->getPlayersScoreArray();
		int* level2_score_array = level2->getPlayersScoreArray();

		for (int i = 0; i < 201; i++) {
			(level1_score_array[i] = level1_score_array[i] + level2_score_array[i]);
		}
		level1->setPlayersNum(level1->getPlayersNum() + level2->getPlayersNum());
	}
}
void uniteGroups(Group* group1, Group* group2) {
	if (group1->getGroupID() != group2->getGroupID()) {
		int* group1_score_array = group1->getSumScoreGroupPlayersLevelZero();
		int* group2_score_array = group2->getSumScoreGroupPlayersLevelZero();

		for (int i = 0; i < 201; i++) {
			(group1_score_array[i] = group1_score_array[i] + group2_score_array[i]);
		}
		int updatedGroupPlayersLevelZero = group1->getGroupPlayersLevelZero() + group2->getGroupPlayersLevelZero();
		int updatedNumberOfPlayersInGroup = group1->getNumberOfPlayers() + group2->getNumberOfPlayers();
		group1->SetGroupPlayersLevelZero(updatedGroupPlayersLevelZero);
		group1->setNumberOfPlayers(updatedNumberOfPlayersInGroup);
	}
}

void mergeLevelArrays(Level** array_a, int array_a_size, Level** array_b, int array_b_size,
	Level** array_c) {
	int i = 0;
	int j = 0;
	int k = 0;

	while ((i < array_a_size) && (j < array_b_size)) {
		if (array_a[i]->getLevel() < array_b[j]->getLevel()) {
			array_c[k++] = array_a[i++];
		}
		else {
			array_c[k++] = array_b[j++];
		}
	}
	while (i < array_a_size) {
		array_c[k++] = array_a[i++];
	}
	while (j < array_b_size) {
		array_c[k++] = array_b[j++];
	}
}
Level** removeDuplicatesFromLevelArray(Level** array_a, int array_a_size, int* updated_array_a_size) {
	int slim_array_size = 0;
	if (array_a_size > 1) {
		Level** tmp_result_array = new Level * [array_a_size];
		for (int i = 0; i < array_a_size; i++) {
			tmp_result_array[i] = nullptr;
		}
		for (int i = 0; i < array_a_size; i++) {
			if (i == (array_a_size - 1)) {
				tmp_result_array[i] = array_a[i];
			} else {
				if ((array_a[i]->getLevel()) == (array_a[i + 1]->getLevel())) {
					uniteLevels(array_a[i], array_a[i + 1]);
					delete array_a[i + 1];
					tmp_result_array[i] = array_a[i];
					i++;
				} else {
					tmp_result_array[i] = array_a[i];
				}
			}
		}
		for (int i = 0; i < array_a_size; i++) {
			if (tmp_result_array[i] != nullptr) {
				slim_array_size++;
			}
		}
		Level** result_array = new Level * [slim_array_size];
		int j = 0;
		for (int i = 0; i < slim_array_size; i++) {
			if (tmp_result_array[j] != nullptr) {
				result_array[i] = tmp_result_array[j];
			}
			if (tmp_result_array[j] == nullptr) {
				j++;
				result_array[i] = tmp_result_array[j];
			}
			j++;
		}
		delete[] tmp_result_array;
		*updated_array_a_size = slim_array_size;
		return result_array;
	}else {
	    Level** result_array = new Level* [array_a_size];
	    if(array_a_size==1){
	        result_array[0]=array_a[0];
	    }
		*updated_array_a_size = array_a_size;
		return result_array;
	}
}


#endif

