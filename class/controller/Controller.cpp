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
     * Update advert
     * @param id - advert id
     * @param title - updated advert title
     * @param body - updated advert body
     * @param password - advert password, must match already saved one
     * @return response object with updated advert or error message
     */
    Response *update_advert(const string& id, const string& title, const string& body, const string& password) {
        // todo: validate data

        Advert *updated_advert = new Advert(id, title, body, password);
        int update_result = repository.update(updated_advert);

        switch (update_result) {
            case 1: {
                // advert updated successfully
                Advert *advert = repository.find_by_id(id);
                return new Response(200, advert->to_json());
            }
            case -1: {
                // advert with given id not found
                return new Response(404);
            }
            case -2: {
                // no authorized
                ErrorMessage *error = new ErrorMessage("password", "Wrong password!");
                return new Response(401, error->to_json());
            }
            default: {
                return new Response(400);
            }
        }
    }

};