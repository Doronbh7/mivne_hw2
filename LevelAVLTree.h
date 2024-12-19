#ifndef LEVELAVLTREE_H
#define LEVELAVLTREE_H
#include "Level.h"
template<class Key_Type>
class LevelAVLNode {
private:
    Key_Type key_val;
    Level* data_val;
    int height_val;
    LevelAVLNode *right_node, *left_node, *parent_node;
    int balance_val;
    int sub_tree_node_num;
    int* sub_tree_score_players;//pointer to array

public:
    //defining ctor
    LevelAVLNode(Key_Type key_val, Level* data_val):key_val(key_val),data_val(data_val),height_val(0),right_node(
            nullptr),left_node(nullptr),parent_node(nullptr),balance_val(0),sub_tree_node_num(1) {

        int* current_node_players_score=data_val->getPlayersScoreArray();
        sub_tree_score_players = new int[201];
        for (int i=0;i<201;i++){
            sub_tree_score_players[i]=current_node_players_score[i];
        }
    }

    //defining a dtor
    ~LevelAVLNode() {
        delete[] sub_tree_score_players;
    }

    //defining gets and sets
/**
 * The function set the node's  key
 */
    void setKey(Key_Type key_val) {
        this->key_val = key_val;
    }
/**
 * The function set the node's  data
  */
    void setData(Level* data_val) {
        this->data_val = data_val;
    }
/**
 * The function set the node's  left son
  */
    void setLeft(LevelAVLNode<Key_Type>* node) {
        this->left_node = node;
        if (left_node != nullptr) {
            left_node->setParent(this);
        }
    }
/**
 * The function set  the node's  parent
 */
    void setParent(LevelAVLNode<Key_Type>* node) {
        this->parent_node = node;
    }
/**
 * The function set the node's  height
 */
    void setHeight(int height_val) {
        this->height_val=height_val;
    }

    /**
* The function set the node's  sub_tree_node_num
*/
    void setSubTreeNodeNum(int sub_tree_node_num) {
        this->sub_tree_node_num=sub_tree_node_num;
    }


/**
 * The function set the node's  balance
 */
    void setBalance(int balance_val) {
        this->balance_val=balance_val;
    }

 /**
 * The function set the node's  right son
 */
    void setRight(LevelAVLNode<Key_Type>* node) {
        this->right_node = node;
        if (right_node != nullptr) {
            right_node->setParent(this);
        }
    }
/**
 * The function return the node's  key
 * @return
 */
    Key_Type getKey() {
        return key_val;
    }
/**
 * The function return the node's  data
 * @return
 */
    Level* getData() {
        return data_val;
    }
/**
 * The function return the node's  height
 * @return
 */
    int getHeight() {
        return height_val;
    }

    /**
* The function return the node's  sub_tree_node_num
* @return
*/
    int getSubTreeNodeNum() {
        return sub_tree_node_num;
    }

    /**
* The function return the node's  sub_tree_score_players array pointer
* @return
*/
    int* getSubTreeScoreArray() {
        return sub_tree_score_players;
    }


/**
 * The function return the node's  balance
 * @return
 */
    int getBalance() {
        return balance_val;
    }

    /**
 * The function return the node's  right son
 * @return
 */
    LevelAVLNode* getRight() {
        return right_node;
    }
/**
 * The function return the node's  lefts son
 * @return
 */
    LevelAVLNode* getLeft() {
        return left_node;
    }
/**
 * The function return the node's  parent
 * @return
 */
    LevelAVLNode* getParent() {
        return parent_node;
    }

};


template<class Key_Type>
class LevelAVLTree {
private:
    LevelAVLNode<Key_Type>* root_node;
    LevelAVLNode<Key_Type>* biggest_node; //biggest node according to key_val value
    LevelAVLNode<Key_Type>* smallest_node; //smallest node according to key_val value
    int size_val; //number of nodes
public:
    //defining ctor
    LevelAVLTree():
            root_node(nullptr), biggest_node(nullptr),smallest_node(nullptr), size_val(0) {
    }

    //defining dtor
    ~LevelAVLTree() {
        deleteTree(root_node);
    }

    //help function in order to delete tree with post order search
    void deleteTree(LevelAVLNode<Key_Type>* node) {
        //stop condition, if we reach dead end
        if (node == nullptr) {
            return;
        }
            //else, we perform post order search
        else {
            deleteTree(node->getLeft());
            deleteTree(node->getRight());
        }
        //checks if we need to remove value from root_node or biggest node
        if (node == biggest_node) {
            biggest_node = node->getParent();
        }
        if (node == smallest_node) {
            smallest_node = node->getParent();
        }

        //deletes current node after search, reduces size_val
        delete node;
        node= nullptr;
        size_val--;
    }

    /**
     *
     * @return the number of nodes in the tree
     */
    int getSize() {
        return size_val;
    }

    /**
     * insert a node to the tree
     * @param key_val
     * @param data_val
     * @return the pointer of the node
     */
    LevelAVLNode<Key_Type>* insertNode(Key_Type key_val, Level* data_val) {
        LevelAVLNode<Key_Type>* node=new LevelAVLNode<Key_Type>(key_val,data_val);
        Key_Type curr_node_key=node->getKey();


        if (biggest_node == nullptr) {
            biggest_node = node;
        }else{
            Key_Type biggest_node_key=biggest_node->getKey();

            if (curr_node_key>biggest_node_key) {
                biggest_node = node;
            }
        }

        if (smallest_node == nullptr) {
            smallest_node = node;
        }else{
            Key_Type smallest_node_key=smallest_node->getKey();

            if (curr_node_key<smallest_node_key) {
                smallest_node = node;
            }
        }




        if (root_node == nullptr) {
            root_node = node;
            size_val++;
            root_node->setParent(nullptr);
            return node;
        }
        insertNodeHelp(node,root_node);

        size_val++;
        return node;

    }

    /**
     * help to insert the node to the tree. We use this function if the new node is isn't the root_node.
     * @param new_node the node we insert to the tree
     * @param current_node the current node
     * @return the current node
     */
    LevelAVLNode<Key_Type>* insertNodeHelp(
            LevelAVLNode<Key_Type> *new_node, LevelAVLNode<Key_Type> *current_node) {
        if(current_node== nullptr){
            current_node= new_node;
            return new_node;
        }
        LevelAVLNode<Key_Type>* right_node=current_node->getRight();
        LevelAVLNode<Key_Type>* left_node=current_node->getLeft();

        Key_Type new_node_key=new_node->getKey();
        Key_Type current_node_key=current_node->getKey();


        if (new_node_key<current_node_key) {
            current_node->setLeft(insertNodeHelp(new_node,left_node));
        }
        else if (new_node_key >= current_node_key) {
            current_node->setRight(insertNodeHelp(new_node,right_node));
        }

        updateNodeHeight(current_node);
        subTreeNodeNumAndArrayUpdate(current_node);

        int right_node_height;
        int left_node_height;
        if(right_node== nullptr){
            right_node_height=-1;
        }
        else{
            right_node_height=right_node->getHeight();
        }
        if(left_node== nullptr){
            left_node_height=-1;
        }
        else{
            left_node_height=left_node->getHeight();

        }


        int balance_val=left_node_height-right_node_height;

        current_node->setBalance(balance_val);
        if((current_node->getBalance()==2)||(current_node->getBalance()==-2)){
            return balanceTree(current_node);

        }

        return current_node;

    }

    /**
     * delete node in the tree by key_val
     * @param key_val
     */
    void deleteNodeByKey(Key_Type key_val) {
        if(size_val<=0){
            return;
        }
        if ( (root_node->getHeight()==0)&&(root_node->getKey()==key_val)){
            delete root_node;
            root_node= nullptr;
            size_val=0;
            biggest_node= nullptr;
            smallest_node= nullptr;
            return;
        }
        if (biggest_node->getKey()==key_val) {
            if(biggest_node->getLeft()!= nullptr){
                biggest_node = biggest_node->getLeft();
            }else{
                biggest_node = biggest_node->getParent();
            }
        }

        if (smallest_node->getKey()==key_val) {
            if(smallest_node->getRight()!= nullptr){
                smallest_node = smallest_node->getRight();
            }else{
                smallest_node = smallest_node->getParent();
            }
        }
        deleteNodeByKeyHelp(key_val, root_node);
        size_val=size_val-1;
        if(size_val==1){
            biggest_node = smallest_node;
        }
        if(size_val==0){
            biggest_node= nullptr;
            smallest_node= nullptr;
            root_node= nullptr;
        }



    }

    /**
     * Help to delete the node by key_val.We use this function if the key_val is isn't the root_node and the root_node height_val is isn't 0.
     * @param key_val The key_val of the node that we want to delete.
     * @param current_node The current node.
     * @return The current node
     */

    LevelAVLNode<Key_Type>* deleteNodeByKeyHelp(Key_Type key_val,
                                           LevelAVLNode<Key_Type> *current_node) {

        if (current_node== nullptr) {
            return nullptr;
        }

        if(current_node->getKey() > key_val) {
            current_node->setLeft(deleteNodeByKeyHelp(key_val,current_node->getLeft())) ;
        }
        if(current_node->getKey() == key_val) {
            bool first_condition= false;
            if(!(current_node->getLeft())){
                first_condition= true;
            }
            bool second_condition= false;
            if(!(current_node->getRight())){
                second_condition= true;
            }
            if (first_condition || second_condition) {
                LevelAVLNode<Key_Type> *temp_node = current_node->getLeft();
                if (!temp_node) {
                    if (current_node->getRight()== nullptr) {
                        temp_node = current_node;
                        current_node = nullptr;
                    }
                    else {
                        temp_node = current_node->getRight();
                    }
                }
                if (current_node != nullptr) {
                    if(temp_node==smallest_node){
                        smallest_node=current_node;
                    }
                    if(temp_node==biggest_node){
                        biggest_node=current_node;
                    }
                    Level* current_node_data=current_node->getData();
                    current_node->setLeft(temp_node->getLeft());
                    current_node->setRight(temp_node->getRight());
                    current_node->setData(temp_node->getData());
                    temp_node->setData(current_node_data);
                    current_node->setKey(temp_node->getKey());

                }
                delete temp_node;
                temp_node= nullptr;
            }
            else {
                LevelAVLNode<Key_Type> *temp_node = current_node->getRight();
                while (temp_node->getLeft()) {
                    temp_node = temp_node->getLeft();
                }
                if(temp_node==smallest_node){
                    smallest_node=current_node;
                }
                if(temp_node==biggest_node){
                    biggest_node=current_node;
                }

                Level* temp_data = current_node->getData();
                Key_Type temp_key = current_node->getKey();
                current_node->setData(temp_node->getData());
                current_node->setKey(temp_node->getKey());
                temp_node->setData(temp_data);
                temp_node->setKey(temp_key);

                current_node->setRight(deleteNodeByKeyHelp(key_val,current_node->getRight()));
            }
        }
        else {
            current_node->setRight(deleteNodeByKeyHelp(key_val,current_node->getRight())) ;
        }

        if (current_node== nullptr) {
            return current_node;
        }

        LevelAVLNode<Key_Type>* right_node=current_node->getRight();
        LevelAVLNode<Key_Type>* left_node=current_node->getLeft();

        updateNodeHeight(current_node);
        subTreeNodeNumAndArrayUpdate(current_node);

        int right_node_height;
        int left_node_height;
        if(right_node== nullptr){
            right_node_height=-1;
        }
        else{
            right_node_height=right_node->getHeight();
        }
        if(left_node== nullptr){
            left_node_height=-1;
        }
        else{
            left_node_height=left_node->getHeight();

        }


        int balance_val=left_node_height-right_node_height;

        current_node->setBalance(balance_val);

        if((current_node->getBalance()==2)||(current_node->getBalance()==-2)){
            return balanceTree(current_node);

        }

        return current_node;

    }


    /**
	 * balance_val the tree
	 * @param node
	 * @return The updated node
	 */
    LevelAVLNode<Key_Type>* balanceTree(LevelAVLNode<Key_Type> *node) {

        int left_node_balance;
        int right_node_balance;

        if(node->getBalance()==2){
            LevelAVLNode<Key_Type>* left_node=node->getLeft();
            int left_right_node_height;
            int left_left_node_height;
            LevelAVLNode<Key_Type> *left_right_node = left_node->getRight();
            LevelAVLNode<Key_Type> *left_left_node = left_node->getLeft();

            if (left_right_node == nullptr) {
                left_right_node_height = -1;
            } else {
                left_right_node_height = left_right_node->getHeight();
            }

            if (left_left_node == nullptr) {
                left_left_node_height = -1;
            } else {
                left_left_node_height = left_left_node->getHeight();

            }
            left_node_balance = left_left_node_height - left_right_node_height;

            if(left_node_balance>=0){ //LL

                Key_Type root_key=root_node->getKey();
                Key_Type node_key=node->getKey();

                if(root_key == node_key){
                    root_node=left_node;
                    root_node->setParent(nullptr);
                }
                left_node->setRight(node);
                node->setLeft(left_right_node);
                updateNodeHeight(node);
                updateNodeHeight(left_node);
                subTreeNodeNumAndArrayUpdate(node);
                subTreeNodeNumAndArrayUpdate(left_node);
                return left_node;

            }

            if(left_node_balance==-1){ //LR
                LevelAVLNode<Key_Type>* node_left_right=node->getLeft()->getRight();
                LevelAVLNode<Key_Type>* node_left_right_left=node_left_right->getLeft();

                Key_Type root_key=root_node->getKey();

                LevelAVLNode<Key_Type>* LeftNode=node->getLeft();


                Key_Type LeftNode_key=LeftNode->getKey();


                if(root_key == LeftNode_key){
                    root_node=node_left_right;
                    root_node->setParent(nullptr);
                }

                node_left_right->setLeft(node->getLeft());
                node->getLeft()->setRight(node_left_right_left);
                updateNodeHeight(node->getLeft());
                updateNodeHeight(node_left_right);
                subTreeNodeNumAndArrayUpdate(node->getLeft());
                subTreeNodeNumAndArrayUpdate(node_left_right);
                node->setLeft(node_left_right);


                LevelAVLNode<Key_Type>* node_left=node->getLeft();
                node_left_right=node->getLeft()->getRight();


                root_key=root_node->getKey();
                Key_Type node_key=node->getKey();

                if(root_key == node_key){
                    root_node=node_left;
                    root_node->setParent(nullptr);
                }
                node_left->setRight(node);
                node->setLeft(node_left_right);
                updateNodeHeight(node);
                updateNodeHeight(node_left);
                subTreeNodeNumAndArrayUpdate(node);
                subTreeNodeNumAndArrayUpdate(node_left);
                return node_left ;
            }
            return node;
        }

        if(node->getBalance()==(-2)){
            LevelAVLNode<Key_Type>* right_node=node->getRight();
            int right_right_node_height;
            int right_left_node_height;
            LevelAVLNode<Key_Type> *right_right_node = right_node->getRight();
            LevelAVLNode<Key_Type> *right_left_node = right_node->getLeft();

            if (right_right_node == nullptr) {
                right_right_node_height = -1;
            } else {
                right_right_node_height = right_right_node->getHeight();
            }

            if (right_left_node == nullptr) {
                right_left_node_height = -1;
            } else {
                right_left_node_height = right_left_node->getHeight();

            }
            right_node_balance =
                    right_left_node_height - right_right_node_height;
            if(right_node_balance<=0){ //RR

                Key_Type root_key=root_node->getKey();
                Key_Type node_key=node->getKey();

                if(root_key == node_key){
                    root_node=right_node;
                    root_node->setParent(nullptr);
                }
                right_node->setLeft(node);
                node->setRight(right_left_node);
                updateNodeHeight(node);
                updateNodeHeight(right_node);
                subTreeNodeNumAndArrayUpdate(node);
                subTreeNodeNumAndArrayUpdate(right_node);
                return right_node;

            }

            if(right_node_balance==1){ //RL

                LevelAVLNode<Key_Type>* node_right_left=node->getRight()->getLeft();
                LevelAVLNode<Key_Type>* node_right_left_right=node_right_left->getRight();

                Key_Type root_key=root_node->getKey();
                Key_Type Right_node_key=node->getRight()->getKey();

                if(root_key == Right_node_key){
                    root_node=node_right_left;
                    root_node->setParent(nullptr);
                }

                node_right_left->setRight(node->getRight());
                node->getRight()->setLeft(node_right_left_right);
                updateNodeHeight(node->getRight());
                updateNodeHeight(node_right_left);
                subTreeNodeNumAndArrayUpdate((node->getRight()));
                subTreeNodeNumAndArrayUpdate(node_right_left);
                node->setRight(node_right_left);


                LevelAVLNode<Key_Type>* node_right=node->getRight();
                node_right_left=node->getRight()->getLeft();

                root_key=root_node->getKey();
                Key_Type node_key=node->getKey();

                if(root_key == node_key){
                    root_node=node_right;
                    root_node->setParent(nullptr);
                }
                node_right->setLeft(node);
                node->setRight(node_right_left);
                updateNodeHeight(node);
                updateNodeHeight(node_right);
                subTreeNodeNumAndArrayUpdate(node);
                subTreeNodeNumAndArrayUpdate(node_right);
                return node_right ;

            }
            return node;

        }
        return node;

    }

    /**
     *
     * @param key_val
     * @return true-if the node is exist in the tree
     * false-if the node is not exist in the tree
     */
    bool isExist(Key_Type key_val) {
        if(this->root_node== nullptr){
            return false;
        }
        if(isExistHelp(key_val,root_node)== nullptr){
            return false;
        }
        return true;
    }

    /**
     * Help to find if the node is exist in the tree. We use this function if the root_node is not nullptr.
     * @param key_val The key_val of the node we search.
     * @param node The root_node of the tree.
     * @return
     * nullptr-The node is not exist
     * other- The node is exist
     */
    LevelAVLNode<Key_Type>* isExistHelp(Key_Type key_val, LevelAVLNode<Key_Type> *node) {
        if(node == nullptr) {
            return nullptr;
        }
        if(key_val < node->getKey()) {
            return isExistHelp(key_val, node->getLeft());
        }

        if(key_val > node->getKey()) {
            return isExistHelp(key_val, node->getRight());
        }else{
            if(key_val==node->getKey()) {
                return node;
            }
        }

        return nullptr;
    }

    /**
     *
     * @param key_val
     * @return the tree node by key_val
     */
    LevelAVLNode<Key_Type>* getNodeByKey(Key_Type key_val) {
        return isExistHelp(key_val,root_node);
    }

    /**
       * Get Ith node in the tree
       * @param i
       * @return The Ith node in the tree
       */
    LevelAVLNode<Key_Type>* Select(int i){
        LevelAVLNode<Key_Type>* current_node = root_node;
        int check=i-1;
        while (current_node != nullptr)
        {
            int left_sub_tree_node_num;
            LevelAVLNode<Key_Type>* left_node=current_node->getLeft();
            if (left_node == nullptr)
            {
                left_sub_tree_node_num=0;
            }
            else{
                left_sub_tree_node_num=left_node->getSubTreeNodeNum();
            }
            if (left_sub_tree_node_num < check)
            {
                check = check - left_sub_tree_node_num - 1;
                current_node=current_node->getRight();
            }
            else if (left_sub_tree_node_num > check)
            {
                current_node=current_node->getLeft();
            }
            else if (left_sub_tree_node_num == check)
            {
                return current_node;
            }
        }
        return nullptr;
    }









/**
 * Update the node height_val
 * @param node The node that we update
 */
    void updateNodeHeight(LevelAVLNode<Key_Type> *node) {


        int right_node_height;
        int left_node_height;
        if(node->getRight()== nullptr){
            right_node_height=-1;
        }
        else{
            LevelAVLNode<Key_Type>* right_node=node->getRight();
            right_node_height=right_node->getHeight();
        }

        if(node->getLeft()== nullptr){
            left_node_height=-1;
        }
        else{
            LevelAVLNode<Key_Type>* left_node=node->getLeft();
            left_node_height=left_node->getHeight();

        }


        if(left_node_height>right_node_height){
            node->setHeight(left_node_height+1);
        }
        else{
            node->setHeight(right_node_height+1);
        }
    }


    /**
     * insert to the array the k biggest nodes in the tree
     * @param array
     * @param K
     */
    void GetKLargestReversedInOrderArray(Level** array,int K) {
        if(this->size_val==1){
            smallest_node=root_node;
            biggest_node=root_node;
        }
        LevelAVLNode<Key_Type> *max_node_iterator=this->getBiggestNode();
        LevelAVLNode <Key_Type>** KLargestReversedInOrderArray=new LevelAVLNode <Key_Type>* [K];
        LevelAVLNode <Key_Type> * current_node_iterator=max_node_iterator;
        for (int i = 0; i < K; i++) {
            KLargestReversedInOrderArray[i]=current_node_iterator;
            current_node_iterator=getPreviusNodeInOrderPredeccessor(current_node_iterator);
        }


        for (int i = 0; i < K; i++) {
            array[i]=KLargestReversedInOrderArray[i]->getData();
        }


        delete [] KLargestReversedInOrderArray;

        return ;
    }

    /**
     * insert to the array the k smallest nodes in the tree(inorder)
     * @param array
     * @param K
     */
    void GetKSmallestInOrderArray(Level** array,int K) {
        if(this->size_val==1){
            smallest_node=root_node;
            biggest_node=root_node;
        }
        LevelAVLNode<Key_Type> *min_node_iterator=this->getSmallestNode();
        LevelAVLNode <Key_Type>** KSmallestInOrderArray=new LevelAVLNode <Key_Type>* [K];
        LevelAVLNode <Key_Type> * current_node_iterator=min_node_iterator;
        for (int i = 0; i < K; i++) {
            KSmallestInOrderArray[i]=current_node_iterator;
            current_node_iterator=getNextNodeInOrderSuccessor(current_node_iterator);
        }
        for (int i = 0; i < K; i++) {
            array[i]= KSmallestInOrderArray[i]->getData();
        }
        delete [] KSmallestInOrderArray;

        return ;
    }


/**
 * Successor implemention
 * @param curr_node
 * @return  the next node of curr_node  inorder
 */
    LevelAVLNode<Key_Type>* getNextNodeInOrderSuccessor(LevelAVLNode<Key_Type>* curr_node){
        if(curr_node== nullptr){
            return nullptr;
        }

        if (curr_node->getRight() != nullptr){
            return getLeftMostRightChild(curr_node);
        }

        else
            return getFirstRightParent(curr_node);

    }

/**
 * return the leftest (smaller) child in the right subtree.
 * @param node
 * @return
 */
    LevelAVLNode<Key_Type>* getLeftMostRightChild(LevelAVLNode<Key_Type>* node){
        if(node== nullptr){
            return nullptr;
        }
        node = node->getRight();
        if(node== nullptr){
            return nullptr;
        }
        while (node->getLeft() != nullptr){
            if(node== nullptr){
                return nullptr;
            }
            node = node->getLeft();
            if(node== nullptr){
                return nullptr;
            }
        }
        return node;
    }

/**
 * The function go up until the first parent that has left son.
 * @param node
 * @return
 */
    LevelAVLNode<Key_Type>* getFirstRightParent(LevelAVLNode<Key_Type>* node){
        if(node== nullptr){
            return nullptr;
        }
        LevelAVLNode<Key_Type>* parent_node = node->getParent();
        if (parent_node == nullptr)
            return nullptr;

        while (parent_node != nullptr && parent_node->getLeft() != node){
            node = parent_node;
            if(node== nullptr){
                return nullptr;
            }
            parent_node = node->getParent();
        }
        return parent_node;
    }


/**
 * Predeccessor implemention
 * @param curr_node
 * @return  the previous node of curr_node  inorder
 */
    LevelAVLNode<Key_Type>* getPreviusNodeInOrderPredeccessor(LevelAVLNode<Key_Type>* curr_node){
        if(curr_node== nullptr){
            return nullptr;
        }
        if (curr_node->getLeft() != nullptr){
            return getRightMostLeftChild(curr_node);
        }

        else
            return getFirstLeftParent(curr_node);

    }

 /**
 * return the rightest (biggest) child in the left subtree.
 * @param node
 * @return
 */
    LevelAVLNode<Key_Type>* getRightMostLeftChild(LevelAVLNode<Key_Type>* node){
        if(node== nullptr){
            return nullptr;
        }
        node = node->getLeft();
        if(node== nullptr){
            return nullptr;
        }
        while (node->getRight() != nullptr){
            if(node== nullptr){
                return nullptr;
            }
            node = node->getRight();
            if(node== nullptr){
                return nullptr;
            }
        }
        return node;
    }

    /**
 * The function go up until the first parent that has right son.
 * @param node
 * @return
 */
    LevelAVLNode<Key_Type>* getFirstLeftParent(LevelAVLNode<Key_Type>* node){
        if(node== nullptr){
            return nullptr;
        }
        LevelAVLNode<Key_Type>* parent_node = node->getParent();
        if (parent_node == nullptr)
            return nullptr;

        while (parent_node != nullptr && parent_node->getRight() != node){
            node = parent_node;
            if(node== nullptr){
                return nullptr;
            }
            parent_node = node->getParent();
        }
        return parent_node;
    }

/**
 * The function return the Biggest Node in the avl tree
 * @return
 */
    LevelAVLNode<Key_Type>* getBiggestNode() {
        return this->biggest_node;
    }


    /**
 * The function return the Smallest Node in the avl tree
 * @return
 */
    LevelAVLNode<Key_Type>* getSmallestNode() {
        return this->smallest_node;
    }


    /**
 * The function return the Biggest Data in the avl tree
 * @return
 */
    Level* getBiggestData() {
        return this->biggest_node->getData();
    }


    /**
 * The function return the Smallest Data in the avl tree
 * @return
 */
    Level* getSmallestData() {
        return this->smallest_node->setData();
    }



/*  */
/**
 *  Constructs AVL Tree from a sorted array
 * @param DataArr Array of the data
 * @param KeyArr Array of the Data keys
 * @param Size Size of the array
 */

    void sortedArrayToAVL(Level* DataArr[],Key_Type KeyArr[],int Size)
    {
        size_val=Size;
        sortedArrayToAVLHelp(DataArr,KeyArr,0, Size-1);

    }

/**
 * Help to construct AVL Tree from a sorted array with recursive
 * @param DataArr Array of the data
 * @param KeyArr Array of the Data keys
 * @param start Start of the array
 * @param end End of the array
 * @return The current node
 */
    LevelAVLNode<Key_Type>* sortedArrayToAVLHelp(Level* DataArr[],Key_Type KeyArr[],
                            int start, int end)
    {
        /* Base Case */
        if (start > end)
            return nullptr;

        /* Get the middle element  */
        int mid = (start + end)/2;

        LevelAVLNode<Key_Type>* node=new LevelAVLNode<Key_Type>(KeyArr[mid],DataArr[mid]);
        Key_Type curr_node_key=node->getKey();


        if (biggest_node == nullptr) {
            biggest_node = node;
        }else{
            Key_Type biggest_node_key=biggest_node->getKey();

            if (curr_node_key>biggest_node_key) {
                biggest_node = node;
            }
        }

        if (smallest_node == nullptr) {
            smallest_node = node;
        }else{
            Key_Type smallest_node_key=smallest_node->getKey();

            if (curr_node_key<smallest_node_key) {
                smallest_node = node;
            }
        }




        if (root_node == nullptr) {
            root_node = node;

            root_node->setParent(nullptr);
        }



        /* Recursively construct the left subtree
        and make it left child of node */
        node->setLeft(sortedArrayToAVLHelp(DataArr,KeyArr, start,mid - 1));

        /* Recursively construct the right subtree
        and make it right child of node */
        node->setRight(sortedArrayToAVLHelp(DataArr,KeyArr, mid + 1,end));
        updateNodeHeight(node);
        subTreeNodeNumAndArrayUpdate(node);
        return node;
    }

    /**
     * Delete the data in every node in the tree by inorder
     */
    void deleteAllDataInTree(){

        Level** data_array=new Level*[this->size_val];

        GetKSmallestInOrderArray(data_array,this->size_val);

        for(int i=0;i<(this->size_val);i++){
            delete data_array[i];
        }
        delete[] data_array;
    }

    /**
* Update the sub tree node number and the sub_tree_score_players array
* @param node the root of the sub tree
*/
    void subTreeNodeNumAndArrayUpdate(LevelAVLNode<Key_Type>* node) {
        if (node == nullptr) {
            return;
        }
        int* SubTree_score_players_right_son = nullptr;
        int* SubTree_score_players_left_son = nullptr;
        int subTreeNodeNumRightSon = 0;
        int subTreeNodeNumLeftSon = 0;

        if (node->getRight() != nullptr) {
            subTreeNodeNumRightSon = node->getRight()->getSubTreeNodeNum();
            SubTree_score_players_right_son = node->getRight()->getSubTreeScoreArray();
        }
        if (node->getLeft() != nullptr) {
            subTreeNodeNumLeftSon = node->getLeft()->getSubTreeNodeNum();
            SubTree_score_players_left_son = node->getLeft()->getSubTreeScoreArray();
        }
        int sum = subTreeNodeNumLeftSon +
                  subTreeNodeNumRightSon + 1;
        node->setSubTreeNodeNum(sum);

        int* SubTree_score_players_current= node->getSubTreeScoreArray();

        Level* data_val=node->getData();

        int* current_node_players_score=data_val->getPlayersScoreArray();

        if((SubTree_score_players_right_son== nullptr)&&(SubTree_score_players_left_son == nullptr)){
            for(int i=0;i<201;i++){
                SubTree_score_players_current[i]=current_node_players_score[i];


            }

            return;

        }

        if((SubTree_score_players_right_son != nullptr)&&(SubTree_score_players_left_son == nullptr)){
            for(int i=0;i<201;i++){
                SubTree_score_players_current[i]=current_node_players_score[i]+SubTree_score_players_right_son[i];


            }

        }

        if((SubTree_score_players_right_son == nullptr)&&(SubTree_score_players_left_son != nullptr)){
            for(int i=0;i<201;i++){
                SubTree_score_players_current[i]=current_node_players_score[i]+SubTree_score_players_left_son[i];


            }

        }

        if((SubTree_score_players_right_son != nullptr)&&(SubTree_score_players_left_son != nullptr)){
            for(int i=0;i<201;i++){
                SubTree_score_players_current[i]=current_node_players_score[i]+SubTree_score_players_left_son[i]+SubTree_score_players_right_son[i];


            }

        }


        return;
    }




    /**
     * Update sub_tree_score_players array in level and in search route
     * If sign is true-add 1 to SubTree_score_players[score] .If sign is false-decrease 1 from SubTree_score_players[score]
     * key_val- the key of the level with the new score
     *
     */
    void UpdateScoreInLevel(bool sign,int score,Key_Type key_val){
        UpdateScoreInLevelHelp(sign,score,key_val,root_node);
    }

    /**
     * Help function to UpdateScoreInLevel
     */
    LevelAVLNode<Key_Type>* UpdateScoreInLevelHelp(bool sign,int score,Key_Type key_val, LevelAVLNode<Key_Type> *node) {
        if(node == nullptr) {
            return nullptr;
        }
        if(key_val < node->getKey()) {
            int* SubTree_score_players_current= node->getSubTreeScoreArray();
            if(sign==true){
                SubTree_score_players_current[score]++;
            }
            if(sign==false){
                SubTree_score_players_current[score]--;
            }
            return UpdateScoreInLevelHelp(sign,score,key_val, node->getLeft());
        }

        if(key_val > node->getKey()) {
            int* SubTree_score_players_current= node->getSubTreeScoreArray();
            if(sign==true){
                SubTree_score_players_current[score]++;
            }
            if(sign==false){
                SubTree_score_players_current[score]--;
            }
            return UpdateScoreInLevelHelp(sign,score,key_val, node->getRight());
        }else{
            if(key_val==node->getKey()) {
                int* SubTree_score_players_current= node->getSubTreeScoreArray();
                if(sign==true){
                    SubTree_score_players_current[score]++;
                }
                if(sign==false){
                    SubTree_score_players_current[score]--;
                }

                return node;
            }
        }

        return nullptr;
    }


    /**
     * Get the sum of the score of levels until key
     * @param key the key
     * @param sum_array a pointer to zero array.In this array we sum the score
     * @param sum_array lower_level - if 0 its lower level , if 1 its higher
     */
    void getSumArrayUntilKey(int key,int* sum_array,int higher_level ){

        LevelAVLNode<Key_Type>* current_node = root_node;

        while (current_node != nullptr)
        {
            int* SubTree_score_players_left_son;
            Level* data_val=current_node->getData();
            int* temp=data_val->getPlayersScoreArray();
            LevelAVLNode<Key_Type>* left_node=current_node->getLeft();
            if (left_node == nullptr)
            {
                SubTree_score_players_left_son= nullptr;
            }
            else{
                SubTree_score_players_left_son = left_node->getSubTreeScoreArray();
            }
            if ((current_node->getKey()) < key)
            {

                if(SubTree_score_players_left_son != nullptr){
                    for(int i=0;i<201;i++){
                        sum_array[i]=sum_array[i]+temp[i]+SubTree_score_players_left_son[i];

                    }

                }
                if(SubTree_score_players_left_son == nullptr){
                    for(int i=0;i<201;i++){
                        sum_array[i]=sum_array[i]+temp[i];

                    }

                }
                current_node=current_node->getRight();
            }
            else if ((current_node->getKey()) > key)
            {
                current_node=current_node->getLeft();
            }
            else if ((current_node->getKey()) == key)
            {
                if(higher_level==1){

                    if(SubTree_score_players_left_son != nullptr){
                        for(int i=0;i<201;i++){
                            sum_array[i]=sum_array[i]+temp[i]+SubTree_score_players_left_son[i];

                        }

                    }
                    if(SubTree_score_players_left_son == nullptr){
                        for(int i=0;i<201;i++){
                            sum_array[i]=sum_array[i]+temp[i];

                        }

                    }



                }


                if(higher_level==0){

                    if(SubTree_score_players_left_son != nullptr){
                        for(int i=0;i<201;i++){
                            sum_array[i]=sum_array[i]+SubTree_score_players_left_son[i];

                        }

                    }



                }



                return;
            }
        }


    }






};

#endif