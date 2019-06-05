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
     * Remove advert
     * @param id - advert id
     * @param password - advert password, must match already saved one
     * @return response object with optional error message
     */
    Response *remove_advert(const string &id, const string &password) {
        int remove_result = repository.remove(id, password);

        switch (remove_result) {
            case 1: {
                // advert removed successfully
                return new Response(200);
            }
            case -1: {
                // advert with given id not found
                return new Response(404);
            }
            case -2: {
                // not authorized
                ErrorMessage *error = new ErrorMessage("password", "Wrong password!");
                return new Response(401, error->to_json());
            }
            default: {
                return new Response(400);
            }
        }
    }

};