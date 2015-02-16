#include <iostream>
#include <sys/utsname.h>
#include <fstream>
#include <sys/statvfs.h>
#include <math.h>

#define GB (1024*1024*1024)
#define VERSION "0.3.5"

using namespace std;

//For getting information about os (machine - name...)
struct utsname utsnameBuffer;
string distroName;
string distroId;
int uptimeHours = 0;
int uptimeMinutes = 0;
string cpuName;
int ramTotal = 0;
int ramUsed = 0;
double ramUsedInPct = 0;
//For getting information about memory (HDD)
struct statvfs statvfsBuffer;
double memoryTotalRoot = 0;
double memoryFreeRoot = 0;
double memoryUsedRoot = 0;
double memoryUsedRootInPct = 0;
double memoryTotalHome = 0;
double memoryFreeHome = 0;
double memoryUsedHome = 0;
double memoryUsedHomeInPct = 0;
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

    memoryTotalHome = statvfsBuffer.f_blocks * statvfsBuffer.f_frsize / (double) GB;
    memoryTotalHome = ceil(memoryTotalHome * 10) / 10; //round to one decimal place
    memoryFreeHome = statvfsBuffer.f_bfree * statvfsBuffer.f_frsize / (double) GB;
    memoryFreeHome = ceil(memoryFreeHome * 10) / 10;
    memoryUsedHome = memoryTotalHome - memoryFreeHome;
    memoryUsedHome = ceil(memoryUsedHome * 10) / 10;
    memoryUsedHomeInPct = (100 / memoryTotalHome) * memoryUsedHome;
    memoryUsedHomeInPct = ceil(memoryUsedHomeInPct * 10) / 10;
}

void getSpaceRoot()
{
    if((statvfs("/", &statvfsBuffer)) < 0)
        cout << "ERROR: Failed statvfs /" << endl;

    memoryTotalRoot = statvfsBuffer.f_blocks * statvfsBuffer.f_frsize / (double) GB;
    memoryTotalRoot = ceil(memoryTotalRoot * 10) / 10; //round to one decimal place
    memoryFreeRoot = statvfsBuffer.f_bfree * statvfsBuffer.f_frsize / (double) GB;
    memoryFreeRoot = ceil(memoryFreeRoot * 10) / 10;
    memoryUsedRoot = memoryTotalRoot - memoryFreeRoot;
    memoryUsedRoot = ceil(memoryUsedRoot * 10) / 10;
    memoryUsedRootInPct = (100 / memoryTotalRoot) * memoryUsedRoot;
    memoryUsedRootInPct = ceil(memoryUsedRootInPct * 10) / 10;
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
    ramUsedInPct = (100 / (double) ramTotal) * ramUsed;
    ramUsedInPct = ceil(ramUsedInPct * 10) / 10;
}

void getCpu()
{
    ifstream ifsCpuInfo;
    ifsCpuInfo.open("/proc/cpuinfo");
    if(ifsCpuInfo.is_open())
    {
        for(int i = 0; i < 5; i++)
        {
            getline(ifsCpuInfo, cpuName);
        }
        ifsCpuInfo.close();
    }
    removeSubString(cpuName, "model name\t: ");
    removeSubString(cpuName, "(R)"); //For shortest lenght
    removeSubString(cpuName, "(TM)"); //For shortest lenght
    removeSubString(cpuName, "@ "); //For shortest lenght
    removeSubString(cpuName, "CPU "); //For shortest lenght
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
        getline(ifslsbRelease, distroName);
        getline(ifslsbRelease, distroName);
        ifslsbRelease.close();
    }
    removeSubString(distroId, "DISTRIB_ID=");
    removeSubString(distroName, "DISTRIB_DESCRIPTION=\"");
    removeSubString(distroName, "\"");
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

        if(memoryUsedRootInPct < 50)
            colorUsedRoot = "\033[1;32m";
        else if(memoryUsedRootInPct < 75)
            colorUsedRoot = "\033[1;33m";
        else
            colorUsedRoot = "\033[1;31m";

        if(memoryUsedHomeInPct < 50)
            colorUsedHome = "\033[1;32m";
        else if(memoryUsedHomeInPct < 75)
            colorUsedHome = "\033[1;33m";
        else
            colorUsedHome = "\033[1;31m";


        if(ramUsedInPct < 50)
            colorRamUsed = "\033[1;32m";
        else if(ramUsedInPct < 75)
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
                    "                 +ss+                   " << "I'am " << distroName << ", best OS ever." << endl <<
                    "                /ssss/                  " << endl <<
                    "               :ssssss/                 " << blueLightBold << "OS: " << offColor << distroName << " " << utsnameBuffer.machine << blueLightBold << endl <<
                    "              .ssssssss:                " << blueLightBold << "Hostname: " << offColor << utsnameBuffer.nodename << blueLightBold << endl <<
                    "             -+:/sssssss:               " << blueLightBold << "Kernel Release: " << offColor << utsnameBuffer.release << blueLightBold << endl <<
                    "            -sss" << blueLight << "+ARCH+" << blueLightBold << "sss:              " << endl <<
                    "           -ssssssssssssss:             " << blueLightBold << "Uptime: " << offColor << uptimeHours << "h " << uptimeMinutes << "m" << blueLightBold << endl <<
                    "          :ssss" << blueLight << "+LINUX+" << blueLightBold << "sssss:            " << "RAM: " << colorRamUsed << ramUsed << "MB" << offColor << " / " << ramTotal << " MB (" << ramUsedInPct << "%)" << blueLight << endl <<
                    "         " << blueLightBold << ":s" << blueLight << "ssssssssssssssss" << blueLightBold << "s/           " << "CPU: " << offColor << cpuName << blueLight << endl <<
                    "        :sssssss+.  .+sssssss/          " << endl <<
                    "       /sssssss+      /sssssss/         " << blueLightBold << "Root: " << colorUsedRoot << memoryUsedRoot << "GB" << offColor << " / " << memoryTotalRoot << "GB (" << memoryUsedRootInPct << "%)" << blueLight << endl <<
                    "      /ssssssss.      `ssssssos+        " << blueLightBold << "Home: " << colorUsedHome << memoryUsedHome << "GB" << offColor << " / " << memoryTotalHome << "GB (" << memoryUsedHomeInPct << "%)" << blueLight << endl <<
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
                    "             yMNMMMNMMMMM.            " << yellowBold << "I'am " << distroName << ", best OS ever." << bold << endl <<
                    "             ho' 'bnd' 'Mo            " << endl <<
                    "             ys " << offColor << "." << bold << " mnm " << offColor << "." << bold << " Mo            " << yellowBold << "OS: " << offColor << distroName << " " << utsnameBuffer.machine << bold << endl <<
                    "             os" << yellowBold << "::::-::" << bold << "dMMm            " << yellowBold << "Hostname: " << offColor << utsnameBuffer.nodename << bold << endl <<
                    "             +" << yellowBold << "y+////:-sM" << bold << "dmy           " << yellowBold << "Kernel Release: " << offColor << utsnameBuffer.release << bold << endl <<
                    "            /m-" << yellowBold << "`:/-`" << bold << "   oMMMh`         " << endl <<
                    "          `hN.          hMMMN:        " << yellowBold << "Uptime: " << offColor << uptimeHours << "h " << uptimeMinutes << "m" << bold << endl <<
                    "         .NMo.          :mMNMMo       " << yellowBold << "RAM: " << colorRamUsed << ramUsed << "MB" << offColor << " / " << ramTotal << " MB (" << ramUsedInPct << "%)" << bold << endl <<
                    "        `mN+     " << offColor << "GNU" << bold << "     .mNNMMs      " << yellowBold << "CPU: " << offColor << cpuName << bold << endl <<
                    "        hNo               +MMNMM.     " << endl <<
                    "       hNN`     " << offColor << "LINUX" << bold << "     :MNMMMd     " << yellowBold << "Root: " << colorUsedRoot << memoryUsedRoot << "GB" << offColor << " / " << memoryTotalRoot << "GB (" << memoryUsedRootInPct << "%)" << bold << endl <<
                    "      `hyd`               /NNMNNh     " << yellowBold << "Home: " << colorUsedHome << memoryUsedHome << "GB" << offColor << " / " << memoryTotalHome << "GB (" << memoryUsedHomeInPct << "%)" << bold << endl <<
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