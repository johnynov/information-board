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

};