#include <iostream>
#include <sys/utsname.h>
#include <fstream>
#include <sys/statvfs.h>
#include <math.h>

#define GB (1024*1024*1024)
#define VERSION 0.3

using namespace std;

struct utsname utsnameBuffer;
string distro;
string distroId;
int uptimeHours = 0;
int uptimeMinutes = 0;
string cpu;
int ramTotal = 0;
int ramUsed = 0;
double ramUsedInPercentages = 0;
struct statvfs statvfsBuffer;
double totalRoot = 0;
double freeRoot = 0;
double usedRoot = 0;
double usedRootInPercentages = 0;
double totalHome = 0;
double freeHome = 0;
double usedHome = 0;
double usedHomeInPercentages = 0;
bool colors = true;

enum logo
{
    archLinux,
    tux
} logoSelected;

void removeSubString(string &sInput, const string &subString);

void getSpaceHome()
{
    if((statvfs("/home", &statvfsBuffer)) < 0)
        cout << "ERROR: Failed statvfs /home" << endl;

    totalHome = statvfsBuffer.f_blocks * statvfsBuffer.f_frsize / (double) GB;
    totalHome = ceil(totalHome * 10) / 10; //round to one decimal place
    freeHome = statvfsBuffer.f_bfree * statvfsBuffer.f_frsize / (double) GB;
    freeHome = ceil(freeHome * 10) / 10;
    usedHome = totalHome - freeHome;
    usedHome = ceil(usedHome * 10) / 10;
    usedHomeInPercentages = (100 / totalHome) * usedHome;
    usedHomeInPercentages = ceil(usedHomeInPercentages * 10) / 10;
}

void getSpaceRoot()
{
    if((statvfs("/", &statvfsBuffer)) < 0)
        cout << "ERROR: Failed statvfs /" << endl;

    totalRoot = statvfsBuffer.f_blocks * statvfsBuffer.f_frsize / (double) GB;
    totalRoot = ceil(totalRoot * 10) / 10; //round to one decimal place
    freeRoot = statvfsBuffer.f_bfree * statvfsBuffer.f_frsize / (double) GB;
    freeRoot = ceil(freeRoot * 10) / 10;
    usedRoot = totalRoot - freeRoot;
    usedRoot = ceil(usedRoot * 10) / 10;
    usedRootInPercentages = (100 / totalRoot) * usedRoot;
    usedRootInPercentages = ceil(usedRootInPercentages * 10) / 10;
}

void getRam()
{
    ifstream ifsMemInfo;
    string sRamTotal;
    string sRamFree;
    string sRamBuffers;
    string sRamCached;
    string sRamSwapCached;
    ifsMemInfo.open("/proc/meminfo");
    if(ifsMemInfo.is_open())
    {
        getline(ifsMemInfo, sRamTotal);
        getline(ifsMemInfo, sRamFree);
        getline(ifsMemInfo, sRamBuffers);//skip this line
        getline(ifsMemInfo, sRamBuffers);
        getline(ifsMemInfo, sRamCached);
        getline(ifsMemInfo, sRamSwapCached);
        ifsMemInfo.close();
    }

    removeSubString(sRamTotal, "MemTotal: ");
    removeSubString(sRamTotal, " kB");

    removeSubString(sRamFree, "MemFree: ");
    removeSubString(sRamFree, " kB");
    removeSubString(sRamBuffers, "Buffers: ");
    removeSubString(sRamBuffers, " kB");
    removeSubString(sRamCached, "Cached: ");
    removeSubString(sRamCached, " kB");
    removeSubString(sRamSwapCached, "SwapCached: ");
    removeSubString(sRamSwapCached, " kB");

    ramTotal = stoi(sRamTotal);
    ramUsed = ramTotal - stoi(sRamFree) - stoi(sRamBuffers) - stoi(sRamCached) - stoi(sRamSwapCached);

    ramUsed = ramUsed / 1024; //To MB
    ramTotal = ramTotal / 1024;
    ramUsedInPercentages = (100 / (double) ramTotal) * ramUsed;
    ramUsedInPercentages = ceil(ramUsedInPercentages * 10) / 10;
}

void getCpu()
{
    ifstream ifsCpuInfo;
    ifsCpuInfo.open("/proc/cpuinfo");
    if(ifsCpuInfo.is_open())
    {
        for(int i = 0; i < 5; i++)
        {
            getline(ifsCpuInfo, cpu);
        }
        ifsCpuInfo.close();
    }
    removeSubString(cpu, "model name\t: ");
    removeSubString(cpu, "(R)"); //For shortest lenght
    removeSubString(cpu, "(TM)"); //For shortest lenght
    removeSubString(cpu, "@ "); //For shortest lenght
    removeSubString(cpu, "CPU "); //For shortest lenght
}

void getUptime()
{
    ifstream ifsUptime;
    string sUptime;
    ifsUptime.open("/proc/uptime");
    if(ifsUptime.is_open())
    {
        getline(ifsUptime, sUptime);
        ifsUptime.close();
    }

    int uptime;
    sUptime = sUptime.substr(0, sUptime.find(" "));
    uptime = stoi(sUptime);
    uptimeHours = uptime / 3600;
    uptimeMinutes = (uptime / 60) - (60 * uptimeHours);
}

void getOs()
{
    if(uname(&utsnameBuffer) != 0)
    {
        cout << "ERROR: Failed uname" << endl;
        exit(EXIT_FAILURE);
    }
}

void getDistro()
{
    ifstream ifslsbRelease;
    ifslsbRelease.open("/etc/lsb-release");
    if(ifslsbRelease.is_open())
    {
        getline(ifslsbRelease, distroId);
        getline(ifslsbRelease, distroId);
        getline(ifslsbRelease, distro);
        getline(ifslsbRelease, distro);
        ifslsbRelease.close();
    }
    removeSubString(distroId, "DISTRIB_ID=");
    removeSubString(distro, "DISTRIB_DESCRIPTION=\"");
    removeSubString(distro, "\"");
}

void getInfo()
{
    getDistro();
    getOs();
    getUptime();
    getCpu();
    getRam();
    getSpaceRoot();
    getSpaceHome();
}

void writeLogo(logo logo1)
{
    string bold;
    string blueLightBold;
    string blueLight;
    string yellowBold;

    string offColor;

    string colorUsedRoot;
    string colorUsedHome;
    string colorRamUsed;
    if(colors)
    {
        bold = "\033[0;1m";
        blueLightBold = "\033[1;36m";
        blueLight = "\033[0;36m";
        yellowBold = "\033[1;33m";

        offColor = "\033[0m";

        if(usedRootInPercentages < 50)
            colorUsedRoot = "\033[1;32m";
        else if(usedRootInPercentages < 75)
            colorUsedRoot = "\033[1;33m";
        else
            colorUsedRoot = "\033[1;31m";

        if(usedHomeInPercentages < 50)
            colorUsedHome = "\033[1;32m";
        else if(usedHomeInPercentages < 75)
            colorUsedHome = "\033[1;33m";
        else
            colorUsedHome = "\033[1;31m";


        if(ramUsedInPercentages < 50)
            colorRamUsed = "\033[1;32m";
        else if(ramUsedInPercentages < 75)
            colorRamUsed = "\033[1;33m";
        else
            colorRamUsed = "\033[1;31m";
    }

    switch(logo1)
    {
        case archLinux:
            cout << blueLightBold << endl <<
                    "                  .`                    " << endl <<
                    "                 `oo`                   " << "Hello," << endl <<
                    "                 +ss+                   " << "I'am " << distro << ", best OS ever." << endl <<
                    "                /ssss/                  " << endl <<
                    "               :ssssss/                 " << blueLightBold << "OS: " << offColor << distro << " " << utsnameBuffer.machine << blueLightBold << endl <<
                    "              .ssssssss:                " << blueLightBold << "Hostname: " << offColor << utsnameBuffer.nodename << blueLightBold << endl <<
                    "             -+:/sssssss:               " << blueLightBold << "Kernel Release: " << offColor << utsnameBuffer.release << blueLightBold << endl <<
                    "            -sss" << blueLight << "+ARCH+" << blueLightBold << "sss:              " << endl <<
                    "           -ssssssssssssss:             " << blueLightBold << "Uptime: " << offColor << uptimeHours << "h " << uptimeMinutes << "m" << blueLightBold << endl <<
                    "          :ssss" << blueLight << "+LINUX+" << blueLightBold << "sssss:            " << "RAM: " << colorRamUsed << ramUsed << "MB" << offColor << " / " << ramTotal << " MB (" << ramUsedInPercentages << "%)" << blueLight << endl <<
                    "         " << blueLightBold << ":s" << blueLight << "ssssssssssssssss" << blueLightBold << "s/           " << "CPU: " << offColor << cpu << blueLight << endl <<
                    "        :sssssss+.  .+sssssss/          " << endl <<
                    "       /sssssss+      /sssssss/         " << blueLightBold << "Root: " << colorUsedRoot << usedRoot << "GB" << offColor << " / " << totalRoot << "GB (" << usedRootInPercentages << "%)" << blueLight << endl <<
                    "      /ssssssss.      `ssssssos+        " << blueLightBold << "Home: " << colorUsedHome << usedHome << "GB" << offColor << " / " << totalHome << "GB (" << usedHomeInPercentages << "%)" << blueLight << endl <<
                    "     +sssssssss        sssssss+/.       " << endl <<
                    "   `+sssssss+/:`       :/+sssssso/`     " << endl <<
                    "  `osss+/-.                .-/+ssso`    " << endl <<
                    " .oo/.`                        `-/oo.   " << endl <<
                    " -`                                `-   " << offColor << endl << endl;
            break;
        case tux:
            cout << bold << endl <<
                    "              .ohmNNmy+.              " << endl <<
                    "             .NMMMMMNdNN.             " << yellowBold << "Hello," << bold << endl <<
                    "             yMNMMMNMMMMM.            " << yellowBold << "I'am " << distro << ", best OS ever." << bold << endl <<
                    "             ho' 'bnd' 'Mo            " << endl <<
                    "             ys " << offColor << "." << bold << " mnm " << offColor << "." << bold << " Mo            " << yellowBold << "OS: " << offColor << distro << " " << utsnameBuffer.machine << bold << endl <<
                    "             os" << yellowBold << "::::-::" << bold << "dMMm            " << yellowBold << "Hostname: " << offColor << utsnameBuffer.nodename << bold << endl <<
                    "             +" << yellowBold << "y+////:-sM" << bold << "dmy           " << yellowBold << "Kernel Release: " << offColor << utsnameBuffer.release << bold << endl <<
                    "            /m-" << yellowBold << "`:/-`" << bold << "   oMMMh`         " << endl <<
                    "          `hN.          hMMMN:        " << yellowBold << "Uptime: " << offColor << uptimeHours << "h " << uptimeMinutes << "m" << bold << endl <<
                    "         .NMo.          :mMNMMo       " << yellowBold << "RAM: " << colorRamUsed << ramUsed << "MB" << offColor << " / " << ramTotal << " MB (" << ramUsedInPercentages << "%)" << bold << endl <<
                    "        `mN+     " << offColor << "GNU" << bold << "     .mNNMMs      " << yellowBold << "CPU: " << offColor << cpu << bold << endl <<
                    "        hNo               +MMNMM.     " << endl <<
                    "       hNN`     " << offColor << "LINUX" << bold << "     :MNMMMd     " << yellowBold << "Root: " << colorUsedRoot << usedRoot << "GB" << offColor << " / " << totalRoot << "GB (" << usedRootInPercentages << "%)" << bold << endl <<
                    "      `hyd`               /NNMNNh     " << yellowBold << "Home: " << colorUsedHome << usedHome << "GB" << offColor << " / " << totalHome << "GB (" << usedHomeInPercentages << "%)" << bold << endl <<
                    "     `" << yellowBold << "---:" << bold << "ss.            " << yellowBold << "-/" << bold << "MMMN" << yellowBold << "o-     " << endl <<
                    "  --::-----" << bold << "oNd " << yellowBold << "         " << bold << "/" << yellowBold << "::+" << bold << "so" << yellowBold << ":--`    " << endl <<
                    "  ----------" << bold << "/dy        .y" << yellowBold << "/:--------.  " << endl <<
                    " `-----------" << bold << ":/.` `.:ohMh" << yellowBold << ":---------`  " << endl <<
                    " `-:///::---::" << bold << "+NMMMMNNMMs" << yellowBold << "/:--:/:-.`   " << endl <<
                    "   ``-::///+++/" << bold << ":.....--:" << yellowBold << "+oo++/-.``    " << endl <<
                    "         ``````          " << "``````       " << offColor << endl << endl;
            break;
    }
}

void writeInfo()
{
    switch(logoSelected)
    {
        case archLinux:
            writeLogo(archLinux);
            break;
        case tux:
            writeLogo(tux);
            break;
        default:
            if(distroId == "Arch")
                writeLogo(archLinux);
            else
                writeLogo(tux);
            break;
    }
}

void showVersion()
{
    cout << "infux " << VERSION << endl;
}

void showHelp()
{
    cout << "Usage: infux [OPTIONS]" << endl << endl;
    cout << "infux is a program for display info about system." << endl;
    cout << "Created by Petr Štětka from Bohemia (CZ) in C++." << endl << endl;

    cout << "OPTIONS:" << endl;
    cout << "  -c, --no-colors              Turn off colors." << endl;
    cout << "  -l[LOGO], --logo[LOGO]       Show another logo." << endl;
    cout << "       LOGO: \"tux\", \"archlinux\"" << endl << endl;
    cout << "  -h, --help                   Show this help." << endl;
    cout << "  -v, --version                Show version." << endl;
}

void removeSubString(string &sInput, const string &subString)
{
    string::size_type foundpos = sInput.find(subString);
    if(foundpos != string::npos)
        sInput.erase(sInput.begin() + foundpos, sInput.begin() + foundpos + subString.length());
}

int main(int argc, char *argv[])
{
    bool print = false;

    switch(argc)
    {
        default:
            for(int i = 1; i < argc; i++)
            {
                if(argv[i] == string("-h") || argv[i] == string("--h") || argv[i] == string("-help") || argv[i] == string("--help"))
                    showHelp();
                else
                {
                    if(argv[i] == string("-v") || argv[i] == string("--version"))
                        showVersion();
                    else
                    {
                        if(argv[i] == string("-c") || argv[i] == string("--no-colors"))
                        {
                            colors = false;
                            print = true;
                        }
                        else
                        {
                            if(argv[i] == string("-logo[archlinux]") || argv[i] == string("-l[archlinux]"))
                            {
                                logoSelected = archLinux;
                                print = true;
                            }
                            else
                            {
                                if(argv[i] == string("-logo[tux]") || argv[i] == string("-l[tux]"))
                                {
                                    logoSelected = tux;
                                    print = true;
                                }
                                else
                                    showHelp();
                            }
                        }
                    }
                }
            }
            break;
        case 1:
            colors = true;
            print = true;
            break;
    }

    if(print)
    {
        getInfo();
        writeInfo();
    }
    return 0;
}