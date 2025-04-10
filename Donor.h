#ifndef DONOR_H
#define DONOR_H
#pragma once
#include <string>
#include <vector>
using namespace std;

class Donor {

    private:
        //atributos
        //numero a double/long para evitar error de telefono
        int donorId, district;
        string name, address, bloodType, number;

        //cambie el numero de int a string
    public:

    const vector<string> validBloodTypes = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
     //vectorsito para poder verifivar el tipo de sangre

        //funciones
        static string trim(const string& str);
        bool validBlood(const string& type); //el bool para validar si es correcto o no el tipo de sangre
        void donorDetails() const;
        static Donor parseLine(const string& line); //funcion que construte objeto donor, desde una linea de texto

        //getters
        int getDonorId()const {return donorId;}
        int getDistrict()const {return district;}
        string getNumber()const {return number;}
        string getName()const {return name;}
        string getAddress() const {return address;}
        string getBloodType() const {return bloodType;}

        //setters importantes para ingresar los datos al donor
        
        void setDonorId(int id);
        void setDistrict(int dist);
        void setNumber(const string& num);
        void setName(const string& nam);
        void setAddress(const string& addr);
        void setBloodType(const string& type);
        
        
        
    };

#endif // DONOR_H

