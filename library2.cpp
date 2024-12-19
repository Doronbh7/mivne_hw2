
#include "library2.h"
#include "PlayersManager.h"

void *Init(int k, int scale){
    try{

        if((k<=0) || (scale<=0) || (scale>200)){
            return nullptr;
        }
        PlayersManager* PlayersManager_ptr=new PlayersManager(k,scale);

        return (void*)PlayersManager_ptr;

    }
    catch(std::bad_alloc& exception ){
        return nullptr;

    }

}

StatusType MergeGroups(void *DS, int GroupID1, int GroupID2){

    if((DS== nullptr) || (GroupID1<=0) || (GroupID2<=0)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->MergeGroups(GroupID1,GroupID2);

}


StatusType AddPlayer(void *DS, int PlayerID, int GroupID, int score){
    if((DS== nullptr) || (GroupID<=0) || (PlayerID<=0) || (score<=0)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->AddPlayer(PlayerID,GroupID,score);

}

StatusType RemovePlayer(void *DS, int PlayerID){
    if((DS== nullptr) || (PlayerID<=0)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->RemovePlayer(PlayerID);

}

StatusType IncreasePlayerIDLevel(void *DS, int PlayerID, int LevelIncrease){
    if((DS== nullptr) || (PlayerID<=0) || (LevelIncrease<=0)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->IncreasePlayerIDLevel(PlayerID,LevelIncrease);

}

StatusType ChangePlayerIDScore(void *DS, int PlayerID, int NewScore){
    if((DS== nullptr) || (PlayerID<=0) || (NewScore<=0)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->ChangePlayerIDScore(PlayerID,NewScore);

}

StatusType GetPercentOfPlayersWithScoreInBounds(void *DS, int GroupID, int score, int lowerLevel, int higherLevel,
                                                    double * players){
    if((DS== nullptr) || (GroupID<0) || (players== nullptr)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->GetPercentOfPlayersWithScoreInBounds(GroupID,score,lowerLevel,higherLevel,players);

}

StatusType AverageHighestPlayerLevelByGroup(void *DS, int GroupID, int m, double * level){
    if((DS== nullptr) || (GroupID<0) || (m<=0)  || (level== nullptr)){
        return INVALID_INPUT;
    }

    PlayersManager* PlayersManager_ptr=((PlayersManager*)DS);
    return PlayersManager_ptr->AverageHighestPlayerLevelByGroup(GroupID,m,level);

}

StatusType GetPlayersBound(void* DS, int GroupID, int score, int m,
    int* LowerBoundPlayers, int* HigherBoundPlayers) {

    return SUCCESS;
}

void Quit(void** DS){
    if(DS== nullptr){
        return;
    }
    if((*DS)== nullptr){
        return;
    }
    delete ((PlayersManager*)(*DS));

    *DS= nullptr;
}





