#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Donor.h"
#include <stdexcept>
//g++ test_donor.cpp Donor.cpp -o test_donor
TEST_CASE("Validar tipos de sangre válidos e inválidos", "[Donor]") {
    Donor d;
    REQUIRE(d.validBlood("A+") == true);
    REQUIRE(d.validBlood("O-") == true);
    REQUIRE(d.validBlood("AB+") == true);
    REQUIRE(d.validBlood("X+") == false);
    REQUIRE(d.validBlood("") == false);
}

TEST_CASE("Verificar parseo de una línea válida", "[Donor]") {
    std::string linea = "1, Juan Perez, Calle Falsa 123, 2, A+, 3210001111";
    Donor d = Donor::parseLine(linea);

    REQUIRE(d.getDonorId() == 1);
    REQUIRE(d.getName() == "Juan Perez");
    REQUIRE(d.getAddress() == "Calle Falsa 123");
    REQUIRE(d.getDistrict() == 2);
    REQUIRE(d.getBloodType() == "A+");
    REQUIRE(d.getNumber() == "3210001111");
}

TEST_CASE("Validaciones en setters", "[Donor]") {
    Donor d;

    REQUIRE_THROWS_AS(d.setDonorId(-5), std::invalid_argument);
    REQUIRE_THROWS_AS(d.setDistrict(8), std::invalid_argument);
    REQUIRE_THROWS_AS(d.setName(""), std::invalid_argument);
    REQUIRE_THROWS_AS(d.setAddress(""), std::invalid_argument);
    REQUIRE_THROWS_AS(d.setNumber("123"), std::invalid_argument);
    REQUIRE_THROWS_AS(d.setBloodType("X+"), std::invalid_argument);

    // Casos válidos
    REQUIRE_NOTHROW(d.setDonorId(100));
    REQUIRE_NOTHROW(d.setDistrict(3));
    REQUIRE_NOTHROW(d.setName("Maria"));
    REQUIRE_NOTHROW(d.setAddress("Av. Siempre Viva 742"));
    REQUIRE_NOTHROW(d.setNumber("3123456789"));
    REQUIRE_NOTHROW(d.setBloodType("O+"));
} 
