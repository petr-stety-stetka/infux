#pragma once

#include <string>

using namespace std;

class Reader {
public:
    struct Distro {
        string ID;
        string name;
    };

    struct OS {
        string architecture;
        string kernelVersion;
    };

    struct RAM {
        string total;
        string used;
        string usedInPercentages;
        string free;
    };

    struct CPU {
        string CPU;
    };

    struct GPU {
        string GPU;
        string GLVersion;
    };

    struct HDD {
        string total;
        string free;
        string used;
        string usedInPercentages;
    };

    struct Uptime {
        string uptime;
    };

    Distro getDistro();

    OS getOS();

    RAM getRAM();

    CPU getCPU();

    GPU getGPU();

    HDD getHDDRoot();

    HDD getHDDHome();

    Uptime getUptime();

private:
    /**
     * Return true if sub string was found and deleted, else false.
     */
    bool removeSubString(string &input, const string &subString);

    /**
     * Execute command and return output of command;
     */
    std::string executeCommand(string command);

    Reader::HDD getHDD(string partition);
};