#include <map>
#include <vector>
#include "../model/Advert.cpp"
#include "../model/ErrorMessage.cpp"

using namespace std;


class Repository {
    int id_generator = -1;
    map<string, Advert*> adverts;

public:
    Repository() {
        // initialize advert repository with some adverts
        string id = get_new_id();
        adverts[id] = new Advert(id, "Title 0", "Body", "Pass");
        id = get_new_id();
        adverts[id] = new Advert(id, "Title 1", "Body", "Pass");
        id = get_new_id();
        adverts[id] = new Advert(id, "Title 2", "Body", "Pass");
        id = get_new_id();
        adverts[id] = new Advert(id, "Title 3", "Body", "Pass");
    }

    /**
     * Generate new unique advert id
     * @return advert id
     */
    string get_new_id() {
        id_generator++;
        return ::to_string(id_generator);
    }

    /**
     * Find advert saved under given id
     * @param id_advert - advert id
     * @return saved advert or nullptr when advert is not found
     */
    Advert* find_by_id(const string& id_advert) {
        map<string, Advert*>::iterator it;
        it = adverts.find(id_advert);

        if (it != adverts.end()) {
            return it -> second;
        } else {
            return nullptr;
        }
    }

    /**
     * Find all saved adverts
     * @return vector of saved adverts
     */
    vector<Advert*> find_all() {
        vector<Advert*> values;
        for (auto const& advert_entry: adverts) {
            values.push_back(advert_entry.second);
        }
        return values;
    }

    /**
     * Save passed advert in memory
     * @param id_advert - unique advert id
     * @param advert - new advert
     * @return
     *      1 -> success
     *      -1 -> id taken
     */
    int add(const string& id_advert, Advert *advert) {
        if (adverts.count(id_advert) == 0) {
            adverts[id_advert] = advert;
            return 1;
        } else {
            return -1;
        }
    }

    /**
     * Update advert saved under given id
     * @param new_advert - updated advert
     * @return
     *      1 -> success
     *      -1 -> advert not found, no advert under given id
     *      -2 -> not authorized, when password from new_advert is not equal to saved one
     */
    int update(Advert *updated_advert) {
        Advert *advert_to_update = find_by_id(updated_advert->getId());
        if (advert_to_update != nullptr) {
            if (advert_to_update->getPassword() == updated_advert->getPassword()) {
                adverts[updated_advert->getId()] = updated_advert;
                return 1;
            } else {
                return -2;
            }
        } else {
            return -1;
        }
    }

    /**
     * Remove advert saved under given id
     * @param id_advert - advert id
     * @param password - advert password
     * @return
     *      1 -> success
     *      -1 -> advert not found, no advert under given id
     *      -2 -> not authorized, when password from advert is not equal to saved one
     */
    int remove(const string& id_advert, const string& password) {
        Advert *advert_to_delete = find_by_id(id_advert);
        if (advert_to_delete != nullptr) {
            if (advert_to_delete->getPassword() == password) {
                adverts.erase(id_advert);
                return 1;
            } else {
                return -2;
            }
        } else {
            return -1;
        }
    }

};
