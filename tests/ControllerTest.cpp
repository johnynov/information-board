#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "../class/controller/Controller.cpp"


Controller controller;

bool is_json_array(const string &s) {
    regex array_regex("\\[.*\\]");
    return regex_match(s, array_regex);
}

bool is_json_advert(const string &s) {
    regex json_advert("\\{\"id\":.*,\"title\":.*,\"body\":.*\\}");
    return regex_match(s, json_advert);
}

bool is_json_error_message(const string &s) {
    regex json_error_message("\\{\"field\":.*,\"message\":.*\\}");
    return regex_match(s, json_error_message);
}

TEST_CASE("Controller::get_adverts", "[controller]") {

    SECTION("should return response object with status 200 and list of adverts") {
        // when
        Response *response = controller.get_adverts();
        int status = response->getStatus();
        const string &payload = response->getPayload();

        // then
        REQUIRE(status == 200);
        REQUIRE(is_json_array(payload));
    }
}
