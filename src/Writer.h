#pragma once

#include <string>
#include "Reader.h"
#include "Logos.h"

using namespace std;

class Writer {
private:
    bool color = true;
    Reader::OS OS;
    Reader::RAM RAM;
    Reader::CPU CPU;
    Reader::GPU GPU;
    Reader::HDD HDDRoot;
    Reader::HDD HDDHome;
    Reader::Uptime uptime;

    Logos::logos logo;

public:

    void init(Reader::OS OS, Reader::RAM RAM, Reader::CPU CPU, Reader::GPU GPU,
              Reader::HDD HDDRoot,
              Reader::HDD HDDHome, Reader::Uptime uptime);

    void write();

    void setColor(bool color) {
        Writer::color = color;
    }


    void setLogo(Logos::logos logo) {
        Writer::logo = logo;
    }
};