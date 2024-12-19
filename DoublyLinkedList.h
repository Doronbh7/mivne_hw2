
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template<class Data_Type>
struct ListNode{
    Data_Type* data;

    ListNode* next;

    ListNode* previous;

    //constructor
    ListNode(Data_Type* data,ListNode* next,ListNode* previous):
    data(data),next(next),previous(previous){}
    //destructor
    ~ListNode()=default;
    Data_Type* getData(){
        return this->data;
    }



};
template<class Data_Type>
class DoublyLinkedList{
    ListNode<Data_Type>* begin;
    int size;
    ListNode<Data_Type>* end;


public:
    //constructor
    DoublyLinkedList():begin(nullptr),size(0),end(nullptr){}

    //destructor
    ~DoublyLinkedList(){

        while((begin!= nullptr)&&(size!=0)){
            if(size==1){
                delete begin;
                size--;
                begin= nullptr;
                end= nullptr;
            }
            else{
                ListNode<Data_Type>* next_node=begin->next;
                delete begin;
                begin= nullptr;
                size--;
                if(size==0){
                    break;
                }
                this->begin=next_node;
                if(begin!= nullptr){
                    begin->previous= nullptr;
                }


            }
        }

    }

    void deleteListData(){
        ListNode<Data_Type>* current=begin;
        for(int i=0;i<size;i++){
            delete (current->data);
            current->data= nullptr;
            current=current->next;

        }
        
    }

    /**
     * Add new node with the data after the node
     * @param data
     * @param node
     * @return the added node
     */
    ListNode<Data_Type>* addToTheBegin(Data_Type* data){
     this->begin=new ListNode<Data_Type>(data,this->begin, nullptr);
     if(end== nullptr){
         end=begin;
     }

     if(begin->next!= nullptr){
         begin->next->previous=(this->begin);
     }
     size++;
        return begin;
    }

    /**
     *
     * @return the pointer of the first node in the list
     */
    ListNode<Data_Type>* GetFirstNode(){
        return this->begin;
    }

    /**
     * Delete node in the list by the node pointer
     * @param ptr
     * @return true-if the node has been deleted
     * false-if ptr is null
     */

    bool DeleteNodeByPointer(ListNode<Data_Type>* ptr){
        if(ptr== nullptr){
            return false;
        }

        ListNode<Data_Type>* next_ptr=ptr->next;
        ListNode<Data_Type>* previous_ptr=ptr->previous;
        if(ptr==end){
            end=previous_ptr;
        }
        if(size==1){
            end= nullptr;
        }
        delete (ptr->data);
        ptr->data= nullptr;
        delete ptr;
        ptr= nullptr;

        if(next_ptr!= nullptr){
            next_ptr->previous=previous_ptr;
        }

        if(previous_ptr== nullptr){
            begin=next_ptr;
        }
        else{
            previous_ptr->next=next_ptr;
        }

        size--;

        return true;
    }

    /**
     * get the size of the list
     * @return size
     */

    int getSize(){
        return size;
    }


    /**
     * insert to the array the Data of the last (stop-start) nodes in the list
     * @param array the array we insert to
     * @param start the first place to insert in the array
     * @param stop-1 the last place to insert in the array
     */
    void getLastNodesInTheList(Data_Type** array,int start,int stop){
        ListNode<Data_Type>* temp=end;
        for(int i=start;i<stop;i++){
            array[i]=temp->getData();
            temp=temp->previous;
        }
    }

    /**
     * get the list next node after the given pointer
     * @param node
     * @return
     */

    ListNode<Data_Type>* GetListNextNode(ListNode<Data_Type>* node){
        if(node==end){
            return nullptr;
        }
        return node->next;

    }


};

#endif //DOUBLYLINKEDLIST_H
