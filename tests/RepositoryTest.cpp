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
}
