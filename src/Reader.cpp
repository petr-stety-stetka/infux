#include "Reader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/utsname.h>
#include <sys/statvfs.h>
#include <cmath>

using namespace std;

bool Reader::removeSubString(string &input, const string &subString) {
    string::size_type foundpos(input.find(subString));
    if (foundpos != string::npos) {
        input.erase(input.begin() + foundpos, input.begin() + foundpos + subString.length());
        return true;
    }
    else
        return false;
}

template<typename T>
std::string to_string_one_decimal_place(T value) {
    value = ceil(value * 10) / 10; //round to one decimal place
    std::ostringstream out;
    out << value;
    return out.str();
}

std::string Reader::executeCommand(string command) {
    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    std::string result;
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}

Reader::HDD Reader::getHDD(string partition) {
    HDD HDD;
    struct statvfs statvfsBuffer;
    if ((statvfs(partition.c_str(), &statvfsBuffer)) < 0)
        cerr << "ERROR: Failed get information from statvfs for " << partition << "." << endl;
    else {
        double dTotal, dFree, dUsed, dUsedInPercentages;

        const double GB(1024 * 1024 * 1024);
        dTotal = statvfsBuffer.f_blocks * statvfsBuffer.f_frsize / GB;
        dFree = statvfsBuffer.f_bfree * statvfsBuffer.f_frsize / GB;
        dUsed = dTotal - dFree;
        dUsedInPercentages = (100 / dTotal) * dUsed;

        HDD.total = to_string_one_decimal_place(dTotal) + "GiB";
        HDD.free = to_string_one_decimal_place(dFree) + "GiB";
        HDD.used = to_string_one_decimal_place(dUsed) + "GiB";
        HDD.usedInPercentages = to_string_one_decimal_place(dUsedInPercentages) + "%";
    }
    return HDD;
}

Reader::Distro Reader::getDistro() {
    Distro distro;
    ifstream ifsOsRelease("/etc/os-release");

    if (!ifsOsRelease)
        cerr << "ERROR: Failed open file /etc/os-release." << endl;
    else {
        string line;
        bool IdFound = false;
        while (ifsOsRelease) {
            getline(ifsOsRelease, line);
            if (line.find("PRETTY_NAME=") != string::npos) {
                distro.name = line;
            }
            else if (line.find("ID=") != string::npos && !IdFound) {
                distro.ID = line;
                IdFound = true;
            }
        }

        removeSubString(distro.name, "PRETTY_NAME=");
        if (removeSubString(distro.name, "\"")) //Because " are two (if exist)
            removeSubString(distro.name, "\"");
        removeSubString(distro.ID, "ID=");
    }
    return distro;
}

Reader::OS Reader::getOS() {
    struct OS OS;
    struct utsname utsnameBuffer;

    if (uname(&utsnameBuffer) != 0) {
        cerr << "ERROR: Failed get information from uname." << endl;
    }
    else {
        OS.architecture = utsnameBuffer.machine;
        OS.kernelVersion = utsnameBuffer.release;
    }
    return OS;
}

Reader::RAM Reader::getRAM() {
    RAM RAM;
    string sRAMTotal, sRAMFree, sRAMBuffers, sRAMCached, sRAMSwapCached;

    ifstream memoryInfo("/proc/meminfo");
    if (!memoryInfo)
        cerr << "ERROR: Failed open file /proc/meminfo." << endl;
    else {
        bool foundRAMTotal(false), foundRAMFree(false), foundRAMBuffers(false), foundRAMCached(false),
                foundRAMSwapCached(false);

        while (memoryInfo &&
               (!foundRAMTotal || !foundRAMFree || !foundRAMBuffers || !foundRAMCached || !foundRAMSwapCached)) {
            string line;
            getline(memoryInfo, line);

            std::string::size_type posRAMTotal(line.find("MemTotal: "));
            std::string::size_type posRAMFree(line.find("MemFree: "));
            std::string::size_type posRAMBuffers(line.find("Buffers: "));
            std::string::size_type posRAMCached(line.find("Cached: "));
            std::string::size_type posRAMSwapCached(line.find("SwapCached: "));


            if (posRAMTotal != std::string::npos) {
                sRAMTotal = line;
                foundRAMTotal = true;
            }
            else if (posRAMFree != std::string::npos) {
                sRAMFree = line;
                foundRAMFree = true;
            }
            else if (posRAMBuffers != std::string::npos) {
                sRAMBuffers = line;
                foundRAMBuffers = true;
            }
            else if (posRAMSwapCached != std::string::npos) {
                sRAMSwapCached = line;
                foundRAMSwapCached = true;
            }
            else if (posRAMCached != std::string::npos) {
                sRAMCached = line;
                foundRAMCached = true;
            }
        }

        removeSubString(sRAMTotal, "MemTotal: ");
        removeSubString(sRAMTotal, " kB");
        removeSubString(sRAMFree, "MemFree: ");
        removeSubString(sRAMFree, " kB");
        removeSubString(sRAMBuffers, "Buffers: ");
        removeSubString(sRAMBuffers, " kB");
        removeSubString(sRAMCached, "Cached: ");
        removeSubString(sRAMCached, " kB");
        removeSubString(sRAMSwapCached, "SwapCached: ");
        removeSubString(sRAMSwapCached, " kB");

        int iTotal, iFree, iUsed;
        double dUsedInPercentages;
        iTotal = stoi(sRAMTotal);
        iUsed = iTotal - stoi(sRAMFree) - stoi(sRAMBuffers) - stoi(sRAMCached) - stoi(sRAMSwapCached);
        iFree = iTotal - iUsed;

        iUsed = iUsed / 1024; //To MB
        iTotal = iTotal / 1024; //To MB
        iFree = iFree / 1024; //To MB
        dUsedInPercentages = (100 / (double) iTotal) * iUsed;

        RAM.total = to_string(iTotal) + "MiB";
        RAM.used = to_string(iUsed) + "MiB";
        RAM.free = to_string(iFree) + "MiB";
        RAM.usedInPercentages = to_string_one_decimal_place(dUsedInPercentages) + "%";
    }
    return RAM;
}

Reader::CPU Reader::getCPU() {
    CPU CPU;
    ifstream ifsCpuInfo("/proc/cpuinfo");

    if (!ifsCpuInfo)
        cerr << "ERROR: Failed open file /proc/cpuinfo." << endl;
    else {
        bool found(false);
        while (ifsCpuInfo && !found) {
            string line;
            getline(ifsCpuInfo, line);

            std::string::size_type pos(line.find("model name"));
            if (pos != std::string::npos) {
                CPU.CPU = line;
                found = true;
            }
        }

        removeSubString(CPU.CPU, "model name\t: ");
        removeSubString(CPU.CPU, "(R)"); //For shortest length
        removeSubString(CPU.CPU, "(TM)"); //For shortest length
        removeSubString(CPU.CPU, "@ "); //For shortest length
        removeSubString(CPU.CPU, "CPU "); //For shortest length
    }
    return CPU;
}

Reader::GPU Reader::getGPU() {
    GPU GPU;
    stringstream glxInfo(executeCommand("glxinfo | grep OpenGL"));

    bool foundGPU(false);
    bool foundGLVersion(false);

    while (glxInfo && (!foundGPU || !foundGLVersion)) {
        string line;
        getline(glxInfo, line);

        std::string::size_type posGPU(line.find("OpenGL renderer string:"));
        std::string::size_type posGLVersion(line.find("OpenGL version string: "));
        if (posGPU != std::string::npos) {
            GPU.GPU = line;
            foundGPU = true;
        }
        else if (posGLVersion != std::string::npos) {
            GPU.GLVersion = line;
            foundGLVersion = true;
        }
    }
    removeSubString(GPU.GPU, "OpenGL renderer string: ");
    removeSubString(GPU.GLVersion, "OpenGL version string: ");
    return GPU;
}

Reader::HDD Reader::getHDDRoot() {
    return getHDD("/");
}

Reader::HDD Reader::getHDDHome() {
    return getHDD("/home");
}

Reader::Uptime Reader::getUptime() {
    Uptime uptime;
    ifstream ifsUptime("/proc/uptime");

    if (!ifsUptime)
        cerr << "ERROR: Failed open file /proc/uptime." << endl;
    else {
        getline(ifsUptime, uptime.uptime);

        int iUptime;
        uptime.uptime = uptime.uptime.substr(0, uptime.uptime.find(" "));
        iUptime = stoi(uptime.uptime);

        const int dayInSec(86400);
        const short dayInHours(24);
        const short dayInMinutes(1440);
        const short hourInSec(3600);
        const short minuteInSec(60);

        int uptimeDays = iUptime / dayInSec;
        string days, hours, minutes;
        if (uptimeDays > 0) {
            days = to_string(uptimeDays);
            days += uptimeDays > 1 ? " days " : " day ";
            int uptimeHours = (iUptime / hourInSec) - (dayInHours * uptimeDays);

            if (uptimeHours > 0) {
                hours = to_string(uptimeHours);
                hours += uptimeHours > 1 ? " hours " : " hour ";
            }

            int uptimeMinutes = (iUptime / minuteInSec) - (minuteInSec * uptimeHours) - (dayInMinutes * uptimeDays);

            minutes = to_string(uptimeMinutes);
            minutes += uptimeMinutes > 1 ? " minutes" : " minute";
        }
        else {
            int uptimeHours = iUptime / hourInSec;

            if (uptimeHours > 0) {
                hours = to_string(uptimeHours);
                hours += uptimeHours > 1 ? " hours " : " hour ";
            }

            int uptimeMinutes = (iUptime / minuteInSec) - (minuteInSec * uptimeHours);
            minutes = to_string(uptimeMinutes);
            minutes += uptimeMinutes > 1 ? " minutes" : " minute";
        }
        uptime.uptime = days + hours + minutes;
    }
    return uptime;
}
