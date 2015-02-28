#include <iostream>
#include <sys/utsname.h>
#include <fstream>
#include <sys/statvfs.h>
#include <math.h>

#define GB (1024*1024*1024)
#define VERSION "0.4.1"

using namespace std;

//For getting information about os (machine - name...)
struct utsname utsnameBuffer;

//For getting information about memory (HDD)
struct statvfs statvfsBuffer;

string distroName;
string distroId;
string cpuName;
string machine; //x86_64 or i...
string hostname;
string kernelReleaseVersion;

int uptimeHours(0);
int uptimeMinutes(0);
int ramTotal(0);
int ramUsed(0);

double ramUsedInPct(0);
double memoryTotalRoot(0);
double memoryFreeRoot(0);
double memoryUsedRoot(0);
double memoryUsedRootInPct(0);
double memoryTotalHome(0);
double memoryFreeHome(0);
double memoryUsedHome(0);
double memoryUsedHomeInPct(0);

bool colors = true;

enum logo
{
    archLinux,
    tux
} logoSelected;

void getSpaceHome();

void getSpaceRoot();

void getRam();

void getCpu();

void getUptime();

void getOs();

void getDistro();

void getInfo();

void writeLogo(logo logo1);

void writeInfo();

void showVersion();

void showHelp();
void removeSubString(string &sInput, const string &subString);

void getSpaceHome()
{
    if((statvfs("/home", &statvfsBuffer)) < 0)
        cout << "ERROR: Failed statvfs for /home" << endl;

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
        cout << "ERROR: Failed statvfs for /" << endl;

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

    machine = utsnameBuffer.machine;
    hostname = utsnameBuffer.nodename;
    kernelReleaseVersion = utsnameBuffer.release;
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
            cout << blueLightBold << '\n' <<
                    "                  .`                    \n" <<
                    "                 `oo`                   " << "Hello,\n" <<
                    "                 +ss+                   " << "I'am " << distroName << ", best OS ever.\n" <<
                    "                /ssss/                  \n" <<
                    "               :ssssss/                 " << blueLightBold << "OS: " << offColor << distroName << " " << machine << '\n' << blueLightBold <<
                    "              .ssssssss:                " << blueLightBold << "Hostname: " << offColor << hostname << '\n' << blueLightBold <<
                    "             -+:/sssssss:               " << blueLightBold << "Kernel Release: " << offColor << kernelReleaseVersion << '\n' << blueLightBold <<
                    "            -sss" << blueLight << "+ARCH+" << blueLightBold << "sss:              \n" <<
                    "           -ssssssssssssss:             " << blueLightBold << "Uptime: " << offColor << uptimeHours << "h " << uptimeMinutes << "m\n" << blueLightBold <<
                    "          :ssss" << blueLight << "+LINUX+" << blueLightBold << "sssss:            " << "RAM: " << colorRamUsed << ramUsed << "MB" << offColor << " / " << ramTotal << " MB (" << ramUsedInPct << "%)\n" << blueLight <<
                    "         " << blueLightBold << ":s" << blueLight << "ssssssssssssssss" << blueLightBold << "s/           " << "CPU: " << offColor << cpuName << '\n' << blueLight <<
                    "        :sssssss+.  .+sssssss/          \n" <<
                    "       /sssssss+      /sssssss/         " << blueLightBold << "Root: " << colorUsedRoot << memoryUsedRoot << "GB" << offColor << " / " << memoryTotalRoot << "GB (" << memoryUsedRootInPct << "%)\n" << blueLight <<
                    "      /ssssssss.      `ssssssos+        " << blueLightBold << "Home: " << colorUsedHome << memoryUsedHome << "GB" << offColor << " / " << memoryTotalHome << "GB (" << memoryUsedHomeInPct << "%)\n" << blueLight <<
                    "     +sssssssss        sssssss+/.       \n" <<
                    "   `+sssssss+/:`       :/+sssssso/`     \n" <<
                    "  `osss+/-.                .-/+ssso`    \n" <<
                    " .oo/.`                        `-/oo.   \n" <<
                    " -`                                `-   \n" << offColor << endl;
            break;
        case tux:
            cout << bold << '\n' <<
                    "              .ohmNNmy+.              \n" <<
                    "             .NMMMMMNdNN.             " << yellowBold << "Hello,\n" << bold <<
                    "             yMNMMMNMMMMM.            " << yellowBold << "I'am " << distroName << ", best OS ever.\n" << bold <<
                    "             ho' 'bnd' 'Mo            \n" <<
                    "             ys " << offColor << "." << bold << " mnm " << offColor << "." << bold << " Mo            " << yellowBold << "OS: " << offColor << distroName << " " << machine << '\n' << bold <<
                    "             os" << yellowBold << "::::-::" << bold << "dMMm            " << yellowBold << "Hostname: " << offColor << hostname << '\n' << bold <<
                    "             +" << yellowBold << "y+////:-sM" << bold << "dmy           " << yellowBold << "Kernel Release: " << offColor << kernelReleaseVersion << '\n' << bold <<
                    "            /m-" << yellowBold << "`:/-`" << bold << "   oMMMh`         \n" <<
                    "          `hN.          hMMMN:        " << yellowBold << "Uptime: " << offColor << uptimeHours << "h " << uptimeMinutes << "m\n" << bold <<
                    "         .NMo.          :mMNMMo       " << yellowBold << "RAM: " << colorRamUsed << ramUsed << "MB" << offColor << " / " << ramTotal << " MB (" << ramUsedInPct << "%)\n" << bold <<
                    "        `mN+     " << offColor << "GNU" << bold << "     .mNNMMs      " << yellowBold << "CPU: " << offColor << cpuName << '\n' << bold <<
                    "        hNo               +MMNMM.     \n" <<
                    "       hNN`     " << offColor << "LINUX" << bold << "     :MNMMMd     " << yellowBold << "Root: " << colorUsedRoot << memoryUsedRoot << "GB" << offColor << " / " << memoryTotalRoot << "GB (" << memoryUsedRootInPct << "%)\n" << bold <<
                    "      `hyd`               /NNMNNh     " << yellowBold << "Home: " << colorUsedHome << memoryUsedHome << "GB" << offColor << " / " << memoryTotalHome << "GB (" << memoryUsedHomeInPct << "%)\n" << bold <<
                    "     `" << yellowBold << "---:" << bold << "ss.            " << yellowBold << "-/" << bold << "MMMN" << yellowBold << "o-     \n" <<
                    "  --::-----" << bold << "oNd " << yellowBold << "         " << bold << "/" << yellowBold << "::+" << bold << "so" << yellowBold << ":--`    \n" <<
                    "  ----------" << bold << "/dy        .y" << yellowBold << "/:--------.  \n" <<
                    " `-----------" << bold << ":/.` `.:ohMh" << yellowBold << ":---------`  \n" <<
                    " `-:///::---::" << bold << "+NMMMMNNMMs" << yellowBold << "/:--:/:-.`   \n" <<
                    "   ``-::///+++/" << bold << ":.....--:" << yellowBold << "+oo++/-.``    \n" <<
                    "         ``````          " << "``````       \n" << offColor << endl;
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
    cout << "Usage: infux [OPTIONS]\n\n"
            "infux is a program for display info about system.\n"
            "Created by Petr Štětka from Bohemia (CZ) in C++.\n\n"
            "OPTIONS:\n"
            "  -c, --no-colors              Turn off colors.\n"
            "  -l[LOGO], --logo[LOGO]       Show another logo.\n"
            "       LOGO: \"tux\", \"archlinux\"\n\n"
            "  -h, --help                   Show this help.\n"
            "  -v, --version                Show version." << endl;
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