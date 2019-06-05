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

    SECTION("should add new advert") {
        // given
        int initial_adverts_count = repository.find_all().size();
        string new_advert_id = repository.get_new_id();
        Advert *new_advert = new Advert(new_advert_id, "Title", "Body", "qwer");

        // when
        int result = repository.add(new_advert_id, new_advert);
        int adverts_count = repository.find_all().size();

        // then
        REQUIRE(result == 1);
        REQUIRE(adverts_count == initial_adverts_count + 1);
        REQUIRE(repository.find_by_id(new_advert_id) == new_advert);
    }
}
