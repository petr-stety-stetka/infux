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

    void colorUpUsed(string &strUsed, string strUsedInPercentages);

    Reader::Distro &distro;
    Reader::OS &OS;
    Reader::RAM &RAM;
    Reader::CPU &CPU;
    Reader::GPU &GPU;
    Reader::HDD &HDDRoot;
    Reader::HDD &HDDHome;
    Reader::Uptime &uptime;
public:
    Logos(Reader::Distro &distro, Reader::OS &OS, Reader::RAM &RAM, Reader::CPU &CPU, Reader::GPU &GPU,
          Reader::HDD &HDDRoot,
          Reader::HDD &HDDHome, Reader::Uptime &uptime, bool &color);

    void arch();

    void fedora();

    void debian();

    void gnome();

    void gnomeCircle();

    void kde();

    void linuxMint();

    void linuxMint2();

    void nothing();

    void rhel();

    void tux();

    void ubuntu();
};