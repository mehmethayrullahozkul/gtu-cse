#include "shell.h"

namespace OS
{
    Shell::Shell(const string &config_file) : _config(new JSON())
    {
        std::ifstream cfg(config_file);
        if (!cfg.is_open())
        {
            cout << "could not find config file, creating default config file..." << endl;
            _size = 0;
            _currentPath = {"os", "/"};
            _config->add("name", "GTU OS");
            _config->add("provided by", "Mehmet Hayrullah Ozkul");
            _config->add("size", to_string(this->_size));
            _config->add("currentPath", path_to_string(this->_currentPath));
            _config->add("os", new JSON());
            _config->add("id", strHash("os/"), {"os"});
            _config->add("name", "os", {"os"});
            _config->add("path", "/os/", {"os"});
            _config->add("type", "directory", {"os"});
            _config->add("last_modified", "2020-01-01 00:00:00", {"os"});
            _config->add("size", "0", {"os"});
            _config->add("/", new JSON(), {"os"});
            _config->save(DEFAULT_CONFIG_FILE);
        }
        else
        {
            cout << "config file found, loading..." << endl;
            _config->read(DEFAULT_CONFIG_FILE);
            _size = stoi(config().get("size").value());
            _currentPath = path_parser(config().get("currentPath").value());
        }
    }

    Shell::~Shell()
    {
        delete _config;
        for (auto it = _filesToDelete.begin(); it != _filesToDelete.end(); it++)
        {
            delete *it;
        }
    }

    void Shell::run()
    {
        update();
        string input = "";
        string command = "";
        vector<string> tokens = {};
        int size = 0;
        bool onExit = false;
        while (!onExit)
        {
            try
            {
                update();
                tokens.clear();
                prompt();
                getline(cin, input);
                tokens = command_parser(input);
                size = tokens.size();

                if (size <= 0)
                    continue;

                command = tokens[0];

                if (command == "ls")
                {
                    this->ls(tokens);
                }
                else if (command == "cd")
                {
                    this->cd(tokens);
                }
                else if (command == "link")
                {
                    this->link(tokens);
                }
                else if (command == "mkdir")
                {
                    this->mkdir(tokens);
                }
                else if (command == "clear")
                {
                    system("clear");
                }
                else if (command == "cp")
                {
                    this->cp(tokens);
                }
                else if (command == "rmdir")
                {
                    this->rmdir(tokens);
                }
                else if (command == "rm")
                {
                    this->rm(tokens);
                }
                else if (command == "cat")
                {
                    this->cat(tokens);
                }
                else if (command == "exit")
                {
                    onExit = true;
                }
                else if (command == "update")
                {
                    this->update();
                }
                else
                {
                    cout << "command not found" << endl;
                }
            }
            catch (const Exception &e)
            {
                cout << "exception: " << e << endl;
            }
        }
    }

    /*
     *  Shell::ls
     *  - params: args
     *  - return: none
     *
     *  print current directory .
     *  if depth is at least 2, print the outer directory ..
     *
     *  get the current directory
     *  get child json data from current directory
     *  print all files and directories in current directory
     *
     */
    void Shell::ls(const vector<string> &args)
    {
        if (args.size() > 2)
            throw Exception("ls: too many arguments", ExceptionType::Shell);

        /* no flags, casual ls */
        if (args.size() == 1)
        {
            /* print current directory . */
            cout << "D\t\t.\t\t" << config().get("last_modified", path_pop()).value() << endl;

            /* if depth is at least 2, print the outer directory .. */
            if (path().size() > 2)
                cout << "D\t\t..\t\t" << config().get("last_modified", path_pop(3)).value() << endl;

            /* get current directory */
            JSON *cdirectory = config().get("/", path_pop()).child();

            /* get child json data from current directory */
            JSON *cdirectorychild;

            /* print all files and directories in current directory */
            for (int i = 0; i < cdirectory->size(); i++)
            {
                cdirectorychild = cdirectory->operator[](i).child();
                if (cdirectorychild->get("type").value() == "dir")
                {
                    cout << "D\t\t" << cdirectorychild->get("name").value() << "\t\t" << cdirectorychild->get("last_modified").value() << endl;
                }
                else if (cdirectorychild->get("type").value() == "regular")
                {
                    cout << "F\t\t" << cdirectorychild->get("name").value() << "\t\t" << cdirectorychild->get("last_modified").value() << "\t\t" << cdirectorychild->get("size").value() << " Bytes" << endl;
                }
                else if (cdirectorychild->get("type").value() == "link")
                {
                    cout << "L\t\t" << cdirectorychild->get("name").value() << "\t\t" << cdirectorychild->get("last_modified").value() << "\t\t" << cdirectorychild->get("size").value() << " Bytes" << endl;
                }
            }
        }
        /* recursive flag */
        else if (args[1] == "-R" || args[1] == "-r")
        {
            cout << ".: " << endl;
            JSON *cdirectory = config().get("/", path_pop()).child();
            JSON *cdirectorychild;

            /* print all files and directories in current directory */
            for (int i = 0; i < cdirectory->size(); i++)
            {
                cdirectorychild = cdirectory->operator[](i).child();
                cout << cdirectorychild->get("name").value() << endl;
            }
            cout << endl;
            DirectoryFile dir(path_to_string(path_pop()));
            for (auto it = dir.begin(); it != dir.end(); it++)
            {
                if ((*it).type() == FileType::DIRECTORY)
                {
                    (*it).print();
                }
            }
        }
    }

    bool Shell::isDirectory(const string &path)
    {
        const string dirhashpath = DEFAULT_OS_PATH + strHash(path) + File::defaultConfigExtension;
        return DirectoryFile::exists(path);
    }

    bool Shell::isFile(const string &path)
    {
        const string filehashpath = DEFAULT_OS_PATH + strHash(path) + File::defaultConfigExtension;
        return RegularFile::exists(filehashpath);
    }

    void Shell::cd(const vector<string> &args)
    {
        if (args.size() <= 1)
            throw Exception("cd: missing operand", ExceptionType::Shell);

        if (args[1] == ".")
            return;

        if (args[1] == "..")
        {
            if (path().size() > 2)
            {
                path().pop_back();
                path().pop_back();
            }
            return;
        }

        list<string> pathlist = path_parser(args[1]);
        list<string> temp_path = path();

        if (pathlist.front() == "/")
        {
            temp_path.clear();
            temp_path.push_back("os");
            pathlist.pop_front();
        }

        if (pathlist.back() != "/")
        {
            pathlist.push_back("/");
        }

        for (int i = 0; i < pathlist.size(); i++)
        {
            Node *nextdir = config().findKeyInPath(pathlist.front(), temp_path);
            if (nextdir == nullptr)
            {
                throw Exception("cd: no such file or directory", ExceptionType::Shell);
            }
            else
            {
                if (nextdir->child()->get("type").value() == "dir")
                {
                    temp_path.push_back(pathlist.front());
                    temp_path.push_back("/");
                    pathlist.pop_front();
                    pathlist.pop_front();
                }
                else
                {
                    throw Exception("cd: not a directory", ExceptionType::Shell);
                }
            }
        }
        this->path() = temp_path;
    }

    void Shell::cat(const vector<string> &args)
    {
        if (args.size() <= 1)
            throw Exception("cat: missing operand", ExceptionType::Shell);

        const string filepath = path_to_string(path()) + args[1];
        if (RegularFile::try_open(filepath))
        {
            RegularFile file(filepath);
            file.print();
        }
        else
        {
            throw Exception("cat: no such file or directory", ExceptionType::Shell);
        }
    }

    void Shell::mkdir(const vector<string> &args)
    {

        if (args.size() <= 1)
            throw Exception("mkdir: missing operand", ExceptionType::Shell);

        /* directory name and path variables according to hash */
        const string dirname = strHash(path_to_string(path()) + args[1]);
        const string dirpath = DEFAULT_OS_PATH + dirname + File::defaultConfigExtension;

        /* if directory already exists, throw exception */
        if (DirectoryFile::exists(dirpath))
            throw Exception("mkdir: cannot create directory '" + args[1] + "': directory exists - to remove dir use -rmdir", ExceptionType::Shell);

        /* create new directory */
        DirectoryFile newdir;
        DirectoryFile parentdir(path_to_string(path_pop()));

        //_filesToDelete.push_back(newdir);
        //_filesToDelete.push_back(parentdir);

        newdir.id(dirname);
        newdir.name(args[1]);
        newdir.parent(path_to_string(path()));
        newdir.path(path_to_string(path()) + args[1] + "/");
        newdir.lastModified(currentTime());
        newdir.size(0);
        newdir.type(FileType::DIRECTORY);
        newdir.good(true);
        newdir.save();
        parentdir.addFile(&newdir);
        config().update("last_modified", currentTime(), path_pop());
        Node *config_node = config().findKeyInPath(path().back(), path_pop());
        JSON *config_json = new JSON();
        config_json->add("id", newdir.id());
        config_json->add("name", newdir.name());
        config_json->add("path", newdir.path());
        config_json->add("type", "dir");
        config_json->add("last_modified", newdir.lastModified());
        config_json->add("size", to_string(newdir.size()));
        config_json->add("/", new JSON());
        _size += newdir.size();
        config().get("size").value(to_string(_size));
        config_node->child()->add(newdir.name(), config_json);
        config().save(DEFAULT_CONFIG_FILE);
        parentdir.updateTime();
        parentdir.update();
    }

    void Shell::rm(const vector<string> &args)
    {
        if (args.size() <= 1)
            throw Exception("rm: missing operand", ExceptionType::Shell);

        const string filename = args[1];

        const string filepath = path_to_string(path()) + filename;

        if (RegularFile::try_open(filepath))
        {
            RegularFile file(filepath);

            if (file.type() == FileType::DIRECTORY)
                throw Exception("rm: cannot remove '" + filename + "': Is a directory", ExceptionType::Shell);

            const string fileid = file.id();
            DirectoryFile parentdir(path_to_string(path_pop()));
            parentdir.removeFile(fileid);
            config().remove(fileid, path());
        }
        update();
    }

    vector<string> Shell::command_parser(const string &input)
    {
        vector<string> tokens;
        string token = "";
        for (size_t i = 0; i < input.length(); i++)
        {
            if (input[i] == ' ')
            {
                if (token != "")
                {
                    tokens.push_back(token);
                    token = "";
                }
            }
            else
            {
                token += input[i];
            }
        }
        if (token != "")
        {
            tokens.push_back(token);
        }
        return tokens;
    }

    void Shell::link(const vector<string> &args)
    {
        cout << "dint implemented link" << endl;
    }

    void Shell::rmdir(const vector<string> &args)
    {
        if (args.size() <= 1)
            throw Exception("rmdir: missing operand", ExceptionType::Shell);

        const string dirname = args[1];
        const string dirhashpath = DEFAULT_OS_PATH + strHash(path_to_string(path()) + dirname) + File::defaultConfigExtension;
        const string dirpath = path_to_string(path()) + dirname;

        if (!DirectoryFile::exists(dirhashpath))
            throw Exception("rmdir: failed to remove '" + dirname + "': No such file or directory", ExceptionType::Shell);

        DirectoryFile dir(dirpath);
        DirectoryFile parentdir(path_to_string(path_pop()));
        config().remove(dir.name(), path());
        parentdir.removeFile(dir.id());
        update();
    }

    list<string> Shell::path_parser(const string &path)
    {
        list<string> tokens;
        string token = "";
        for (size_t i = 0; i < path.length(); i++)
        {
            if (path[i] == '/')
            {
                if (token != "")
                {
                    tokens.push_back(token);
                    token = "";
                    tokens.push_back("/");
                }
            }
            else
            {
                token += path[i];
            }
        }
        if (token != "")
        {
            tokens.push_back(token);
        }
        return tokens;
    }

    string Shell::path_to_string(const list<string> &path)
    {
        if (path.size() == 0)
            return "";
        string str = "";
        for (auto it = path.begin(); it != path.end(); it++)
        {
            str += *it;
        }
        return str;
    }

    list<string> Shell::path_pop(int n)
    {
        list<string> path = _currentPath;
        for (int i = 0; i < n; i++)
        {
            path.pop_back();
        }
        return path;
    }

    void Shell::cp(const vector<string> &args)
    {
        if (args.size() <= 2)
            throw Exception("cp: missing operand", ExceptionType::Shell);

        const string source = args[1];
        const string destination_name = args[2];

        list<string> source_path = path_parser(source);

        if (source[0] == '/')
        {
            cp_from_system(source, destination_name);
        }
        else
        {
            cp_from_local(source, destination_name);
        }
    }

    void Shell::cp_from_system(const string &src, const string &dst)
    {
        std::ifstream src_file(src, std::ios::binary);
        if (!src_file.is_open())
            throw Exception("cp: cannot read '" + src + "': no such file or directory", ExceptionType::Shell);

        list<string> src_path = path_parser(src);
        const string src_name = src_path.back();

        if (src_name == "/")
            throw Exception("cp: cannot copy directory from system", ExceptionType::Shell);

        const string filename = (dst == ".") ? src_name : dst;

        if (isDirectory(path_to_string(path()) + filename))
        {
            throw Exception("cp: cannot copy, file name already exists in current dir", ExceptionType::Shell);
        }
        else if (isFile(path_to_string(path()) + filename))
        {
            throw Exception("cp: cannot copy, file name already exists in current dir", ExceptionType::Shell);
        }

        const string destinationFilePath = path_to_string(path()) + filename;
        const string destinationFileID = strHash(destinationFilePath);
        const string contentFileExtension = (RegularFile::get_extension(filename) == "") ? File::defaultConfigExtension : RegularFile::get_extension(filename);
        const string contentFileName = strHash(destinationFileID) + RegularFile::get_extension(filename);
        const string contentFilePath = DEFAULT_OS_PATH + contentFileName;

        std::ofstream content_file(contentFilePath, std::ios::binary);

        if (!content_file.is_open())
            throw Exception("cp: cannot create file", ExceptionType::Shell);

        // Copy the contents of the source file to the destination file
        content_file << src_file.rdbuf();

        // Close the files
        src_file.close();
        content_file.close();

        RegularFile file;
        file.id(strHash(destinationFilePath));
        file.name(filename);
        file.path(destinationFilePath);
        file.parent(path_to_string(path()));
        file.lastModified(currentTime());
        file.linkedFile(contentFileName);
        file.extension(contentFileExtension);
        file.size(RegularFile::get_size(contentFilePath));
        file.type(FileType::REGULAR);
        file.good(true);
        file.save();
        DirectoryFile parentdir(path_to_string(path_pop()));
        parentdir.addFile(&file);
        Node *config_node = config().findKeyInPath(path().back(), path_pop());
        JSON *config_json = new JSON();
        config_json->add("id", file.id());
        config_json->add("name", file.name());
        config_json->add("path", file.path());
        config_json->add("type", "regular");
        config_json->add("last_modified", file.lastModified());
        config_json->add("size", to_string(file.size()));
        config_node->child()->add(file.id(), config_json);
        _size += file.size();
        config().get("size").value(to_string(_size));
        config().save(DEFAULT_CONFIG_FILE);
        parentdir.update();
        return;
    }

    void Shell::cp_from_local(const string &src, const string &dst)
    {
        list<string> src_path_list = path_parser(src);
        const string src_name = src_path_list.back();

        const string src_path = (src_path_list.front() == "os") ? path_to_string(src_path_list) : path_to_string(path()) + src;

        RegularFile src_content_file(src_path);
        const string source_content_file = src_content_file.linkedFile();

        std::ifstream src_file(DEFAULT_OS_PATH + source_content_file, std::ios::binary);
        if (!src_file.is_open())
            throw Exception("cp: cannot read '" + src + "': no such file or directory", ExceptionType::Shell);

        if (isDirectory(src_path))
            throw Exception("cp: cannot copy directories", ExceptionType::Shell);

        const string filename = (dst == ".") ? src_name : dst;

        if (isFile(path_to_string(path()) + filename))
            throw Exception("cp: cannot copy, file name already exists in current dir", ExceptionType::Shell);

        if (isDirectory(path_to_string(path()) + filename))
            throw Exception("cp: cannot copy, file name already exists in current dir", ExceptionType::Shell);

        const string destinationFilePath = path_to_string(path()) + filename;
        const string destinationFileID = strHash(destinationFilePath);
        const string contentFileExtension = (RegularFile::get_extension(filename) == "") ? File::defaultConfigExtension : RegularFile::get_extension(filename);
        const string contentFileName = strHash(destinationFileID) + RegularFile::get_extension(filename);
        const string contentFilePath = DEFAULT_OS_PATH + contentFileName;

        std::ofstream content_file(contentFilePath, std::ios::binary);

        if (!content_file.is_open())
            throw Exception("cp: cannot create file", ExceptionType::Shell);

        // Copy the contents of the source file to the destination file
        content_file << src_file.rdbuf();

        // Close the files
        src_file.close();
        content_file.close();

        RegularFile file;
        file.id(strHash(destinationFilePath));
        file.name(filename);
        file.path(destinationFilePath);
        file.parent(path_to_string(path()));
        file.lastModified(currentTime());
        file.linkedFile(contentFileName);
        file.extension(contentFileExtension);
        file.size(RegularFile::get_size(contentFilePath));
        file.type(FileType::REGULAR);
        file.good(true);
        file.save();
        DirectoryFile parentdir(path_to_string(path_pop()));
        parentdir.addFile(&file);
        Node *config_node = config().findKeyInPath(path().back(), path_pop());
        JSON *config_json = new JSON();
        config_json->add("id", file.id());
        config_json->add("name", file.name());
        config_json->add("path", file.path());
        config_json->add("type", "regular");
        config_json->add("last_modified", file.lastModified());
        config_json->add("size", to_string(file.size()));
        config_node->child()->add(file.id(), config_json);
        _size += file.size();
        config().get("size").value(to_string(_size));
        config().save(DEFAULT_CONFIG_FILE);
        parentdir.update();
        return;
    }

    void Shell::print(const list<string> &path)
    {
        cout << "path: ";
        for (auto it = path.begin(); it != path.end(); ++it)
            cout << " \"" << *it << "\"";
        cout << endl;
    }

    void Shell::update()
    {
        int total_size = 0;
        int file_size = 0;
        string last_modified = "";
        JSON *data_tree = config().get("os").child()->operator[]("/").child();

        for (int i = 0; i < data_tree->size(); i++)
        {
            if (data_tree->operator[](i).child()->get("type").value() == "dir")
            {

                file_size = updateLocal(data_tree->operator[](i).child(), {"/"});
                last_modified = data_tree->operator[](i).child()->get("last_modified").value();
                total_size += file_size;
                data_tree->operator[](i).child()->get("size").value(to_string(file_size));
                data_tree->operator[](i).child()->get("last_modified").value(last_modified);
            }
            else
            {

                RegularFile file;
                file.readbyid(data_tree->operator[](i).child()->get("id").value());
                file.updateSize();
                file.save();
                file_size = file.size();
                last_modified = file.lastModified();
                data_tree->operator[](i).child()->get("size").value(to_string(file_size));
                data_tree->operator[](i).child()->get("last_modified").value(last_modified);
                total_size += file_size;
            }
        }
        config().get("os").child()->get("size").value(to_string(total_size));
        config().get("size").value(to_string(total_size));
        config().save(DEFAULT_CONFIG_FILE);
    }

    int Shell::updateLocal(JSON *json, const list<string> &path)
    {
        int total_size = 0;
        int file_size = 0;
        JSON *data_tree = json->get("/").child();
        for (int i = 0; i < data_tree->size(); i++)
        {
            if (data_tree->operator[](i).child()->get("type").value() == "dir")
            {
                file_size = updateLocal(data_tree->operator[](i).child(), {"/"});
                total_size += file_size;
                data_tree->operator[](i).child()->get("size").value(to_string(file_size));
            }
            else
            {
                RegularFile file;
                file.readbyid(data_tree->operator[](i).child()->get("id").value());
                file.updateSize();
                file.save();
                file_size = file.size();
                data_tree->operator[](i).child()->get("size").value(to_string(file_size));
                total_size += file_size;
            }
        }
        return total_size;
    }

    void Shell::prompt()
    {
        cout << "gtu-shell:" << path_to_string(_currentPath) << "$ ";
    }
} // namespace OS