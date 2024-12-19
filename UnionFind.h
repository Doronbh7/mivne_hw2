#ifndef UNIONFIND_H
#define UNIONFIND_H

template<class Data_Type>
class UnionFind {
private:
    Data_Type** ObjectsArray;
    int* ParentsArray;
    int* GroupSizeArray;
    const int Object_number;

public:
    //defining ctor
    UnionFind(int s) : Object_number(s+1) {
        ObjectsArray = new Data_Type*[Object_number];
        ParentsArray = new int[Object_number];
        GroupSizeArray = new int[Object_number];
        for(int i = 0; i < Object_number; i++) {
            GroupSizeArray[i] = 1;
            ParentsArray[i] = i;
            ObjectsArray[i] = new Data_Type(i);
        }
    }

    //defining a dtor
    ~UnionFind() {

        delete[] ParentsArray;
        delete[] GroupSizeArray;
        for(int i = 0; i < Object_number; i++) {
            delete ObjectsArray[i];
        }
        delete[] ObjectsArray;
    }

    /**
        * Shrink the paths
        * @param count
        * @param index
        * @param root
        */
    void Shrink(int count,int index,int root){
        int tmp_key = index;
        for (int i = 0; i < count ; i++) {
            int nxt = ParentsArray[tmp_key];
            ParentsArray[tmp_key] = root;
            tmp_key = nxt;
        }
    }
/**
 *Get the root group by key i
 * @param i
 * @return
 */
    int getRootGroup(int i){
        int key,cnt;
        cnt=0;
        key = i;
        while(ParentsArray[key] != key){
            key = ParentsArray[key];
            cnt=cnt+1;
        }
        Shrink(cnt,i,key);
        return key;
    }


    /**
     * Find by key i
     * @param i
     * @return
     */
    Data_Type* Find(int i) {
        Data_Type* res=ObjectsArray[getRootGroup(i)];
        return res;
    }



    /**
 * Update group 1 and group 2 size to the sum of the two groups sizes
 * @param grp1
 * @param grp2
 */
    void updateGroupsSize(int grp1, int grp2){

        GroupSizeArray[getRootGroup(grp2)] = GroupSizeArray[getRootGroup(grp1)]+GroupSizeArray[getRootGroup(grp2)];
        GroupSizeArray[getRootGroup(grp1)] = GroupSizeArray[getRootGroup(grp1)]+GroupSizeArray[getRootGroup(grp2)];

    }
    /**
     * Union group1 and group2 and return the new group key
     * @param grp1
     * @param grp2
     * @return
     */
    int UnionGroups (int grp1, int grp2) {
        if ((getRootGroup(grp1))==(getRootGroup(grp2))) {
            return getRootGroup(grp1);
        }
        updateGroupsSize(grp1,grp2);


        if (GroupSizeArray[getRootGroup(grp1)] >= GroupSizeArray[getRootGroup(grp2)]){
            ParentsArray[getRootGroup(grp2)] = getRootGroup(grp1);
            return getRootGroup(grp1);
        }
        else{
            ParentsArray[getRootGroup(grp1)] = getRootGroup(grp2);
            return getRootGroup(grp2);

        }

    }




};
#endif