#include "PhoneValidator.h"
#include <curl/curl.h>
#include <string>
#include <iostream>
#include "json.hpp"



using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

PhoneValidator::PhoneValidator(const std::string& apiKey) : apiKey(apiKey) {}

bool PhoneValidator::esNumeroValido(const std::string& numero) {
    CURL* curl = curl_easy_init();
    std::string readBuffer;
    std::string url = "https://api.veriphone.io/v2/verify?phone=" + numero + "&key=" + apiKey;

    if (!curl) return false;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "Error de curl: " << curl_easy_strerror(res) << "\n";
        return false;
    }
    

    try {
        json respuesta = json::parse(readBuffer);

    if (respuesta.contains("phone_valid") && respuesta["phone_valid"].is_boolean()) {
        return respuesta["phone_valid"].get<bool>();
    } else {
        std::cerr << " Respuesta inválida de la API o campo faltante.\n";
        return false;
}

    } catch (...) {
        return false;
    }
}
