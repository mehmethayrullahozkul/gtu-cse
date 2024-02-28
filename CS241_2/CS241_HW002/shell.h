#ifndef SHELL_H
#define SHELL_H

#include "json.h"
#include "os.h"
#include "directory-file.h"
#include "regular-file.h"

namespace OS
{
    const std::string DEFAULT_CONFIG_FILE = DEFAULT_OS_PATH + "os-config.json";

    class Shell
    {
    private:
        JSON *_config;
        int _size;
        std::list<std::string> _currentPath;
        std::list<File *> _filesToDelete;

    public:
        Shell(const string &config_file = DEFAULT_CONFIG_FILE);
        ~Shell();

        void run();
        void ls(const std::vector<string> &args = {});
        void cd(const std::vector<string> &args = {});
        void mkdir(const std::vector<string> &args = {});
        void rmdir(const std::vector<string> &args = {});
        void link(const std::vector<string> &args = {});
        void rm(const std::vector<string> &args = {});
        void cat(const std::vector<string> &args = {});
        void cp(const std::vector<string> &args = {});
        void update();
        void exit();

        // Helpers
        void cp_from_system(const std::string &src, const std::string &dst);
        void cp_from_local(const std::string &src, const std::string &dst);
        int updateLocal(JSON *json, const std::list<std::string> &path);
        void print(const std::list<std::string> &path);
        bool isDirectory(const string &path);
        bool isFile(const string &path);
        inline void prompt();
        inline JSON &config() { return *_config; }
        std::list<string> &path() { return _currentPath; }
        std::vector<std::string> command_parser(const string &input);
        std::list<string> path_parser(const string &path);
        std::list<string> path_pop(int n = 1);
        std::string path_to_string(const list<string> &path);
    };

}

#endif // SHELL_H