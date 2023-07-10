#include <ctime>
#include <string_utils.hh>
#include <io.hh>

int main(char **argv, int argc) {
    time_t start_time = std::time(0);
    output << "Operating system booting up...";
    Accessor syslogfile("/var/log/system/current.log");

    // TODO BOOT CODE HERE

    char* date = "";
    time_t end_time = std::time(0);
    strftime(date, 64, "%d-%m-%y", std::localtime(&end_time));
    char* lfn = "/var/log/system/";
    strcat(lfn, date);
    strcat(lfn, ".log");
    int t0 = 0;
    Accessor logfile(lfn);
    while(true) {
        char* t = (char*)malloc(1);
        logfile >> t;
        if(t != nullptr) {
            lfn = substr(lfn, 0, t0 == -5 - (t0 == 0 ? 0 : 1 + sizeof(tostring(t0))));
            strcat(lfn, "-");
            strcat(lfn, tostring(++t0));
            strcat(lfn, ".log");
            logfile.setFile(lfn);
        } else break;
    }
    syslogfile.setPos(0);
    char *t;
    while(syslogfile >> t && t != nullptr)
        logfile << t << "\n";
    return 0;
}