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

    // just for develop
    void print_adverts() {
        cout << endl<< "Adverts [" << adverts.size() << "]:" << endl;
        for (auto const& advert_entry: adverts) {
            cout << '\t' << advert_entry.first << " -> " << advert_entry.second->to_json() << endl;
        }
    }
};
