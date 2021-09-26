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

    void Config(); //read config
    const bool CheckDirectory(const std::string& string); //check directory to see if it exists
    std::vector<std::string> SearchDirectory(const std::string& directoryPath, const std::string& fileType); //check directory for files that contain "fileType"

    //Music Tool Specific (more so anyways)
    const std::string& GetMusicDirectory() const;
    void SetMusicDirectory(const std::string& musicDirectoryPath);
    const std::string& GetBPMDirectory() const;
    void SetBPMDirectory(const std::string& BPMDirectoryPath);
    std::vector<std::string> GetAllMusic(); //finds all music (.ogg, .wav, .flac) within the musicDirectory_ and stores the file names in a vector
    const int GetBPM(const std::string& musicTitle) const; //get BPM for selected musicTitle from the BPM save file
    void SetBPM(const std::string& musicTitle, const int BPM); //save the BPM for selected musicTitle in the BPM save file

private:
    std::string BPMDirectory_{"./"}; //directory where the BPM save file is located
    std::string musicDirectory_{"./"}; //directory where the music is located
};

#endif