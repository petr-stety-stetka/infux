#pragma once

#include <string>
#include "Reader.h"

using namespace std;

class Writer {
private:
    bool color = true;
    Reader::Distro distro;
    Reader::OS OS;
    Reader::RAM RAM;
    Reader::CPU CPU;
    Reader::GPU GPU;
    Reader::HDD HDDRoot;
    Reader::HDD HDDHome;
    Reader::Uptime uptime;
public:

    void init(Reader::Distro distro, Reader::OS OS, Reader::RAM RAM, Reader::CPU CPU, Reader::GPU GPU,
              Reader::HDD HDDRoot,
              Reader::HDD HDDHome, Reader::Uptime uptime);

    void write();

    void setColor(bool color) {
        Writer::color = color;
    }


    void setLogoID(const string &ID) {
        distro.ID = ID;
    }
};