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
