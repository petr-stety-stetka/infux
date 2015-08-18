#pragma once

#include <string>
#include "Reader.h"

using namespace std;

class Logos {
private:
    string bold;
    string green;
    string yellow;
    string red;
    string offAll;
    bool color;

    void colorupUsed(string &strUsed, string strUsedInPercentages);

    Reader::OS &OS;
    Reader::RAM &RAM;
    Reader::CPU &CPU;
    Reader::GPU &GPU;
    Reader::HDD &HDDRoot;
    Reader::HDD &HDDHome;
    Reader::Uptime &uptime;
public:
    Logos(Reader::OS &OS, Reader::RAM &RAM, Reader::CPU &CPU, Reader::GPU &GPU,
          Reader::HDD &HDDRoot,
          Reader::HDD &HDDHome, Reader::Uptime &uptime, bool &color);

    enum class logos {
        arch,
        debian,
        fedora,
        gnome,
        gnomeCircle,
        kde,
        linuxMint,
        linuxMint2,
        nothing,
        openSuse,
        rhel,
        ubuntu,
        tux
    };

    void arch();
    void fedora();
    void debian();
    void gnome();
    void gnomeCircle();
    void kde();
    void linuxMint();
    void linuxMint2();
    void nothing();

    void openSuse();
    void rhel();
    void tux();
    void ubuntu();
};