#pragma once

#ifndef _IO_

#define _IO_


#include <fstream>
#include <ctime>


Logger output("/var/log/system/current.log", false);

char *gettime(char *format) {
    time_t time = std::time(0);
    char *r;
    strftime(r, 64, format, std::localtime(&time));
    return r;
}

enum LogLevel {
    INFO,
    WARN,
    ERROR,
    DEBUG
};

class Logger {
    private:
        std::fstream logfile;
        bool log_to_output;
    public:
        Logger(char *path, bool log_to_output = false) {
            logfile.open(path);
            this->log_to_output = log_to_output;
        }

        void setLogFile(char *path) {
            if(logfile.is_open()) logfile.close();
            logfile.open(path);
        }

        void log(char *message, LogLevel level = INFO) {
            if(log_to_output) output << message;
            char *x[] = { "92m", "93m", "31m", "36m" };
            logfile << "\u001b[1;" << x[level] << gettime("[%I:%M:%S %P]\u001b[0m: ") << message << "\n";
        }

        Logger &operator<<(char *message) {
            log(message);
            return *this;
        }

        Logger() {}
};

class Reader {
    private:
        std::fstream readfile;
    public:
        Reader(char *path) {
            readfile.open(path);
        }

        Reader() {}

        void setReadFile(char *path) {
            readfile.open(path);
        }

        void read(char *&buffer, int count) {
            readfile.read(buffer, count);
        }

        char *&operator>>(char *&buffer) {
            readfile.getline(buffer, 200);
            return buffer;
        }
};

class Accessor {
    private:
        std::fstream file;
    public:
        Accessor(char *path) {
            file.open(path);
        }

        void setFile(char *path) {
            if(file.is_open()) file.close();
            file.open(path);
        }

        void read(char *&buffer, int count) {
            file.read(buffer, count);
        }

        char *&operator>>(char *&buffer) {
            file.getline(buffer, sizeof(buffer));
            return buffer;
        }

        void write(char *message) {
            file.write(message, sizeof(message));
        }

        void setPos(int pos) {
            file.seekg(pos);
        }

        Accessor &operator<<(char *message) {
            write(message);
            return *this;
        }
};


#endif // _IO_