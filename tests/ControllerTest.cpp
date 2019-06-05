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

TEST_CASE("Controller::add_advert", "[controller]") {

    SECTION("should return response object with status 200 and added advert") {
        // when
        Response *response = controller.add_advert("title", "body", "abcd");
        int status = response->getStatus();
        const string& payload = response->getPayload();

        // then
        REQUIRE(status == 200);
        REQUIRE(is_json_advert(payload));
    }


}

TEST_CASE("Controller::update_advert", "[controller]") {

    SECTION("should return response object with status 200 and updated advert") {
        // given
        string advert_id = "2";
        Advert *initial_advert = repository.find_by_id(advert_id);

        // when
        Response *response = controller.update_advert(
                advert_id,
                "Updated title",
                initial_advert->getBody(),
                initial_advert->getPassword()
        );
        int status = response->getStatus();
        const string &payload = response->getPayload();

        cout << payload << endl;

        // then
        REQUIRE(status == 200);
        REQUIRE(is_json_advert(payload));
    }

    SECTION("should return response object with status 404") {
        // given
        string advert_id = "42";

        // when
        Response *response = controller.update_advert(advert_id, "title", "body", "password");
        int status = response->getStatus();
        const string &payload = response->getPayload();

        // then
        REQUIRE(status == 404);
    }

    SECTION("should return response object with status 401 and error message") {
        // given
        string advert_id = "2";
        Advert *initial_advert = repository.find_by_id(advert_id);

        // when
        Response *response = controller.update_advert(
                advert_id,
                "Updated title",
                initial_advert->getBody(),
                "wrong_password"
        );
        int status = response->getStatus();
        const string &payload = response->getPayload();

        // then
        REQUIRE(status == 401);
        REQUIRE(is_json_error_message(payload));
    }

}

TEST_CASE("Controller::remove_advert", "[controller]") {

    SECTION("should return response object with status 200") {
        // given
        string advert_id = "2";
        Advert *initial_advert = repository.find_by_id(advert_id);

        // when
        Response *response = controller.remove_advert(advert_id, initial_advert->getPassword());
        int status = response->getStatus();
        const string &payload = response->getPayload();

        // then
        REQUIRE(status == 200);
    }

    SECTION("should return response object with status 404") {
        // given
        string advert_id = "2";

        // when
        Response *response = controller.remove_advert(advert_id, "abcd");
        int status = response->getStatus();
        const string &payload = response->getPayload();

        // then
        REQUIRE(status == 404);
    }

    SECTION("should return response object with status 401") {
        // given
        string advert_id = "1";

        // when
        Response *response = controller.remove_advert(advert_id, "wrong_password");
        int status = response->getStatus();
        const string &payload = response->getPayload();

        // then
        REQUIRE(status == 401);
        REQUIRE(is_json_error_message(payload));
    }

}
