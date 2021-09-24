#ifndef FILE_MANAGER_H_
#define FILE_MANAGER_H_
#include <fstream>
#include <vector>
#include <dirent.h>

class FileManager
{
public:
    FileManager();
    ~FileManager();

    void Config();
    const bool CheckDirectory(const std::string& string);
    std::vector<std::string> SearchDirectory(const std::string& directoryPath, const std::string& fileType);

    //Music Tool Specific (more so anyways)
    const std::string& GetMusicDirectory() const;
    void SetMusicDirectory(const std::string& musicDirectoryPath);
    const std::string& GetBPMDirectory() const;
    void SetBPMDirectory(const std::string& BPMDirectoryPath);
    std::vector<std::string> GetAllMusic();
    const float GetBPM(const std::string& musicTitle) const;
    void SetBPM(const std::string& musicTitle, const float BPM);



// private:
//     void ReadDirectory(DIR *dp);
// public:
//     const bool SetFile(const std::string& string);
// private:
//     const bool CheckFiles(const std::string& string);
// public:
//     const bool AddFile(const std::string& string);
//     const bool SubFile(const std::string& string);
//     void DisplayAllFiles() const;
//     const std::string& GetFile() const;
//     const std::string& GetDirectory() const;

//     const bool AddElement(const std::string& string);
//     const bool SubElement(const std::string& string);
//     const std::string& GetRandElement() const;
//     void DisplayAllElements() const;

private:
    // std::vector<std::string> files_;
    // std::string activeFile_;
    // std::string activeDirectory_;
    std::string BPMDirectory_{"./"};
    std::string musicDirectory_{"./"};
};

#endif