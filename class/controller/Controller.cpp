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
        std::string adverts_json = "[";
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
    Response *add_advert(const std::string &title, const std::string &body, const std::string &password) {
        // todo: validate data

        std::string new_advert_id = repository.get_new_id();
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

    /**
     * Update advert
     * @param id - advert id
     * @param title - updated advert title
     * @param body - updated advert body
     * @param password - advert password, must match already saved one
     * @return response object with updated advert or error message
     */
    Response *update_advert(const std::string &id, const std::string &title, const std::string &body,
                            const std::string &password) {
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

    /**
     * Remove advert
     * @param id - advert id
     * @param password - advert password, must match already saved one
     * @return response object with optional error message
     */
    Response *remove_advert(const std::string &id, const std::string &password) {
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