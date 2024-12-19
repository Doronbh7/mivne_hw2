//
// Created by doron ben horin on 07/12/2020.
//

#ifndef KEY_H
#define KEY_H


class Key {
    int id;
    int level;
public:
    Key(int id=0, int level=0):id(id),level(level){}

    ~Key()=default;

    /**
     * overriding operator== in to check if the keys are equals
     * @param key2  - the key we want to check
     * @return true\ false if the condition is true or false
     */
    bool operator==(Key &key2) const {
        if((id==key2.getId())&&(level==key2.getLevel())){
            return true;
        }
        else{
            return false;
        }

    }

    /**
     *  overriding operator> check if the level of key 2 is smaller than this key.
     *  if equals,check if the id of key 2 is bigger than this key.
     * @param key2  - the key we want to check
     * @return true\ false according to the condition.
     */
    bool operator>(Key& key2) const {

        if(level>key2.getLevel()){
            return true;
        }
        if(level==key2.getLevel()){
            if(id<key2.getId()){
                return true;
            }
        }
        return false;


    }

    /**
     * overriding operator!= in order to check if the given key is the same
     * as the this key
     * @param key2 - the key  we want to check
     * @return
     */
    bool operator!=(Key &key2) const {
        return !(*this==(key2));

    }
    /**
 *
 * @param key2  - the key we want to check
 * @return true\ false according to the condition.
 */

    bool operator<(Key &key2) const {
        if(level<key2.getLevel()){
            return true;
        }
        if(level==key2.getLevel()){
            if(id>key2.getId()){
                return true;
            }
        }
        return false;


    }

    /**
 * @param key2  - the key we want to check
 * @return true\ false according to the condition.
 */

    bool operator<=(Key &key2) const {
        return ((*this==key2)||(*this<key2));

    }

    /**
 * @param key2  - the key we want to check
 * @return true\ false according to the condition.
 */

    bool operator>=(Key &key2) const {
        return ((*this==key2)||(*this>key2));

    }

    //gets

    int getId() {
        return id;
    }

    int getLevel() {
        return level;
    }



};




#endif //KEY_H
