
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "DoublyLinkedList.h"
#define INITIAL_SIZE 10

template<class Data_Type>
class hashTable {
    DoublyLinkedList<Data_Type>** hash_table;
    int hash_table_size;
    int current_number_of_objects;

public:

    //defining ctor
    hashTable(): hash_table_size(INITIAL_SIZE),current_number_of_objects(0) {
        hash_table = new DoublyLinkedList<Data_Type>* [INITIAL_SIZE];
        for (int i = 0; i < INITIAL_SIZE ; i++) {
            hash_table[i]=new DoublyLinkedList<Data_Type>;
        }
    }

    //defining a dtor
    ~hashTable(){
        for(int i = 0; i < hash_table_size; i++) {
            hash_table[i]->deleteListData();
            delete hash_table[i];
            hash_table[i]= nullptr;
        }
        delete[] hash_table;
    }

    /**
     * Calculate hash
     * @param Id the id of the data
     * @return The Calculate hash
     */

    int hashCalculate (int Id){
        return Id%hash_table_size;
    }

    /**
     * copy the hash table to a new hash table
     * @param array the new hash table
     * @param size the size of the old hash table
     */
    void changeToNewArray (DoublyLinkedList<Data_Type>** array,int size){
        for (int i = 0; i < hash_table_size ; i++) {
            array[i]=new DoublyLinkedList<Data_Type>;
        }
        for (int i=0;i<size; i++){
            if(hash_table[i]== nullptr){
                continue;
            }
            ListNode<Data_Type>* current = hash_table[i]->GetFirstNode();
            while (current){
                int Id = current->getData()->getId();
                int hash_calculation=hashCalculate(Id);
                array[hash_calculation]->addToTheBegin(current->getData());
                current=hash_table[i]->GetListNextNode(current);
            }
        }
    }

    /**
     * get the node by id
     * @param id
     * @return the node
     */

    ListNode<Data_Type>* getById(int id){
        int hash_calculation=hashCalculate(id);
        if((hash_table[hash_calculation])== nullptr){
            return nullptr;
        }
        ListNode<Data_Type>* current = hash_table[hash_calculation]->GetFirstNode();
        while (current){
            int current_id = current->getData()->getId();
            if(id==current_id){
                return current;
            }
            current=hash_table[hash_calculation]->GetListNextNode(current);
        }

        return nullptr;

    }

    /**
     * insert the data to the hash table
     * @param data
     * @return true- if inserted
     * false- if the data is already inserted
     */

    bool insert(Data_Type* data){
        if(getById(data->getId()) != nullptr){
            return false;
        }
        hash_table[hashCalculate(data->getId())]->addToTheBegin(data);
        this->current_number_of_objects++;
        if (current_number_of_objects == hash_table_size){
            DoublyLinkedList<Data_Type>** new_hash_table =
                    new  DoublyLinkedList<Data_Type>* [2*hash_table_size];
            int old_size=hash_table_size;
            hash_table_size = 2*hash_table_size;
            changeToNewArray(new_hash_table,old_size);
            for(int i = 0; i < old_size; i++) {
                delete hash_table[i];
            }

            delete[] hash_table;
            hash_table= new_hash_table;
        }
        return true;
    }

    /**
     * delete the data from the hash table by id
     * @param id
     * @return true- if deleted
     * false- if the data is not in the hash table
     */

    bool Delete(int id) {
        DoublyLinkedList<Data_Type> *current_list =  hash_table[hashCalculate(id)];
        ListNode<Data_Type> *current_node = getById(id);
        if (current_node == nullptr) {
            return false;
        }
        current_number_of_objects--;
        current_list->DeleteNodeByPointer(current_node);
        if (current_number_of_objects<=(hash_table_size/4)){
            DoublyLinkedList<Data_Type>** new_hash_table =
                    new  DoublyLinkedList<Data_Type>* [hash_table_size/2];
            int old_size=hash_table_size;
            hash_table_size = hash_table_size/2;
            changeToNewArray(new_hash_table,old_size);
            for(int i = 0; i < old_size; i++) {
                delete hash_table[i];
            }

            delete[] hash_table;
            hash_table= new_hash_table;
        }
        return true;
        }


};

#endif //HASHTABLE_H
