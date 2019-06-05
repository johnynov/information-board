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

    SECTION("should remove advert") {
        // given
        int initial_adverts_count = repository.find_all().size();
        string advert_id = "1";
        Advert *initial_advert = repository.find_by_id(advert_id);

        // when
        int result = repository.remove(advert_id, initial_advert->getPassword());
        Advert *advert = repository.find_by_id(advert_id);
        int adverts_count = repository.find_all().size();

        // then
        REQUIRE(result == 1);
        REQUIRE(adverts_count == initial_adverts_count - 1);
        REQUIRE(advert == nullptr);
    }

    SECTION("should not remove advert, advert not found") {
        // given
        int initial_adverts_count = repository.find_all().size();
        string advert_id = "42";

        // when
        int result = repository.remove(advert_id, "abcd");
        int adverts_count = repository.find_all().size();

        // then
        REQUIRE(result == -1);
        REQUIRE(adverts_count == initial_adverts_count);
    }

    SECTION("should not remove advert, not authorized") {
        // given
        int initial_adverts_count = repository.find_all().size();
        string advert_id = "2";
        Advert *initial_advert = repository.find_by_id(advert_id);

        // when
        int result = repository.remove(advert_id, "wrong_password");
        Advert *advert = repository.find_by_id(advert_id);
        int adverts_count = repository.find_all().size();

        // then
        REQUIRE(result == -2);
        REQUIRE(adverts_count == initial_adverts_count);
        REQUIRE(advert == initial_advert);
    }

}
