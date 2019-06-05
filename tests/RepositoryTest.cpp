#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../class/repository/Repository.cpp"


TEST_CASE("Advert repository", "[repository]") {
    Repository repository;

    SECTION("should init repository with initial 4 adverts") {
        // when
        int adverts_count = repository.find_all().size();

        // then
        REQUIRE(adverts_count == 4);
    }

    SECTION("should update advert") {
        // given
        string advert_id = "2";
        Advert *initial_advert = repository.find_by_id(advert_id);
        Advert *updated_advert = new Advert(
                advert_id,
                "Updated title",
                initial_advert->getBody(),
                initial_advert->getPassword()
        );

        // when
        int result = repository.update(updated_advert);
        Advert *advert = repository.find_by_id(advert_id);

        // then
        REQUIRE(result == 1);
        REQUIRE(advert->getTitle() == updated_advert->getTitle());
        REQUIRE(advert->getBody() == initial_advert->getBody());
        REQUIRE(advert->getPassword() == initial_advert->getPassword());
    }

    SECTION("should not update advert, advert not found") {
        // given
        string advert_id = "42";
        Advert *updated_advert = new Advert(advert_id, "title", "body", "password");

        // when
        int result = repository.update(updated_advert);
        Advert *advert = repository.find_by_id(advert_id);

        // then
        REQUIRE(result == -1);
        REQUIRE(advert == nullptr);
    }

    SECTION("should not update advert, not authorized") {
        // given
        string advert_id = "2";
        Advert *initial_advert = repository.find_by_id(advert_id);
        Advert *updated_advert = new Advert(
                advert_id,
                "Updated title",
                initial_advert->getBody(),
                "wrong_password"
        );

        // when
        int result = repository.update(updated_advert);
        Advert *advert = repository.find_by_id(advert_id);

        // then
        REQUIRE(result == -2);
        REQUIRE(advert == initial_advert);
    }
}
