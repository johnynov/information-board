#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../class/controller/Controller.cpp"


bool is_json_array(const string& s) {
    regex array_regex("\\[.*\\]");
    return regex_match(s, array_regex);
}

TEST_CASE("Advert controller", "[controller]") {
    Controller controller;

    SECTION("should return response object with status 200 and list of adverts") {
        // when
        Response *response = controller.get_adverts();

        // then
        REQUIRE(response->getStatus() == 200);
        REQUIRE(is_json_array(response->getPayload()));
    }
}
