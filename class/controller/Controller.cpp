#include "../repository/Repository.cpp"
#include "../model/Response.cpp"


Repository repository;

class Controller {
public:

    /**
     * Get saved adverts
     * @return response object with advert list payload
     */
    Response *get_adverts() {
        string adverts_json = "[";
        for (auto const &advert: repository.find_all()) {
            adverts_json += advert->to_json() + ",";
        }
        adverts_json.replace(adverts_json.length() - 1, 1, "]");

        return new Response(200, adverts_json);
    }

    /**
     * Save advert
     * @param title - advert title
     * @param body - advert body
     * @param password - advert password
     * @return response object with added advert or error message
     */
    Response *add_advert(const string& title, const string& body, const string& password) {
        // todo: validate data

        string new_advert_id = repository.get_new_id();
        Advert *new_advert = new Advert(new_advert_id, title, body, password);

        int add_result = repository.add(new_advert_id, new_advert);

        switch (add_result) {
            case 1: {
                // advert added successfully
                Advert *added_advert = repository.find_by_id(new_advert_id);
                return new Response(200, added_advert->to_json());
            }
            case -1: {
                // advert with given id exists!
                return new Response(400);
            }
            default: {
                return new Response(400);
            }
        }
    }

};