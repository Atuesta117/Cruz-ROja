#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "BloodDatabase.h"
#include <fstream>
#include <sstream>
#include <string>
// g++ test_blood_database.cpp BloodDatabase.cpp Donor.cpp PhoneValidator.cpp -lcurl -o test_blood_database

TEST_CASE("Validacion de entrada entera con strings no validos", "[Input]") {
    std::istringstream input("abc\n-1\n5\n");
    std::cin.rdbuf(input.rdbuf());
    
    int result = BloodDatabase::getValidatedInput("Ingrese un numero: ");
    REQUIRE(result == 5);
}

TEST_CASE("Verificar que trim elimina espacios", "[Trim]") {
    REQUIRE(Donor::trim("   A+  ") == "A+");
    REQUIRE(Donor::trim("\tAB-\n") == "AB-");
    REQUIRE(Donor::trim("   ") == "");
}

TEST_CASE("Escribir y leer datos de archivo temporal", "[Archivo]") {
    BloodDatabase db;
    std::ofstream tempFile("temp_test_data.txt");
    tempFile << "1, Juan, Calle 1, 2, A+, 3000000000\n";
    tempFile << "2, Ana, Calle 2, 3, O-, 3111111111\n";
    tempFile.close();

    std::ifstream testRead("temp_test_data.txt");
    std::string line;
    std::getline(testRead, line);
    REQUIRE(line.find("Juan") != std::string::npos);
    testRead.close();

    std::remove("temp_test_data.txt");
}