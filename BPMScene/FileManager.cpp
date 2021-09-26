#include "FileManager.h"
#include <iostream>

FileManager::FileManager()
{
    Config();
}

FileManager::~FileManager()
{}

void FileManager::Config()
{
    std::fstream inputStream("config"); //open confige
    std::string dummy; //string to store lines
    while (std::getline(inputStream, dummy))
    {//while there are still lines to read
        if (dummy[0] == '#' || dummy == "") continue; //don't read lines that start with '#', nor blank lines
        if (dummy == "Music Directory:") 
        {//fist step
            std::getline(inputStream, dummy); //grab the next line
            if (CheckDirectory(dummy)) SetMusicDirectory(dummy); //use the directory in the config if there are no problems
            else SetMusicDirectory("./"); //if the directory in the config fails, use "./"
        }
        else if (dummy == "BPM Save File Directory:") 
        {//second step
            std::getline(inputStream, dummy); //grab the next line
            if (CheckDirectory(dummy)) SetBPMDirectory(dummy); //use the directory in the config if there are no problems
            else SetBPMDirectory("./"); //if the directory in the config fails, use "./"
        }
    }
    inputStream.close(); //close config
}

const bool FileManager::CheckDirectory(const std::string& string)
{
    DIR *dp; //directory
    if ((dp = opendir(string.c_str())) == NULL) return false; //if the directory doesn't exist, return false
    return true; //return success
}

std::vector<std::string> FileManager::SearchDirectory(const std::string& directoryPath, const std::string& fileType)
{
    std::vector<std::string> fileNames; //vector to store file names

    DIR *dp; //directory
    if ((dp = opendir(directoryPath.c_str())) == NULL)
    {//if the directory fails to open
        fileNames.push_back("Failed to open directory");
        return fileNames;
    }

    struct dirent *dirp; 
    while ((dirp = readdir(dp)) != NULL) 
    {//while there are files to read
        std::string fname = dirp->d_name; //store name of the files
        if(fname.find(fileType) != std::string::npos) fileNames.push_back(fname); //if the file is the right type, store the file name
    }

    return fileNames; //return vector of file names
}



const std::string& FileManager::GetMusicDirectory() const
{
    return musicDirectory_;
}

void FileManager::SetMusicDirectory(const std::string& musicDirectoryPath)
{
    musicDirectory_ = musicDirectoryPath;
}

const std::string& FileManager::GetBPMDirectory() const
{
    return BPMDirectory_;
}

void FileManager::SetBPMDirectory(const std::string& BPMDirectoryPath)
{
    BPMDirectory_ = BPMDirectoryPath;
}

std::vector<std::string> FileManager::GetAllMusic()
{
    std::vector<std::string> musicTitles; //vector to store music titles

    DIR *dp; //directory
    if ((dp = opendir(musicDirectory_.c_str())) == NULL)
    {//formality, program should have defaulted to "./" if the provided directory failed
        musicTitles.push_back("Failed to open directory");
        return musicTitles;
    }

    struct dirent *dirp; 
    while ((dirp = readdir(dp)) != NULL) 
    {//while there are files to read
        std::string fname = dirp->d_name; //store name of the files
        if (fname.find(".ogg") != std::string::npos ||
            fname.find(".wav") != std::string::npos ||
            fname.find(".flac") != std::string::npos) musicTitles.push_back(fname); //if the file is the right type, store the file name
    }

    return musicTitles; //return vector of music titles
}

const int FileManager::GetBPM(const std::string& musicTitle) const
{
    std::fstream inputStream(GetBPMDirectory() + "BPM"); //open BPM save file
    std::string dummy; //string to store lines from the active file
    int BPM = 0; //int to store BPM
    while (std::getline(inputStream, dummy))
    {//while reading lines
        if (dummy == musicTitle)
        {//if the title is found
            inputStream >> BPM; //store the BPM
            inputStream.close(); //close the active file
            return BPM; //return the BPM
        }
    }
    inputStream.close(); //close the active file
    return 0; //if the function fails to find the title, return a BPM of 0
}


void FileManager::SetBPM(const std::string& musicTitle, const int BPM)
{
    std::fstream inputStream(GetBPMDirectory() + "BPM"); //open BPM save file
    std::string dummy; //string to store lines
    std::vector<std::string> elements_; //vector of strings to hold the contents of the file
    while (std::getline(inputStream, dummy))
    {//while reading lines
        if (dummy != musicTitle) elements_.push_back(dummy); //copy the files data, minus the element marked for deletion
        else std::getline(inputStream, dummy); //makes sure that the old BPM doesn't get copied over
    }
    inputStream.close(); //close the active file

    std::ofstream outputStream_("temp.txt"); //create a temp file to place the active files data, minus the marked element
    for (auto element : elements_) outputStream_ << element << std::endl; //actualy input data
    outputStream_ << musicTitle << std::endl; //save the music title and
    outputStream_ << BPM << std::endl; //save the BPM for the title
    outputStream_.close(); //close the temp file
    remove((GetBPMDirectory() + "BPM").c_str()); //delete the now old BPM save file and
    rename("temp.txt", (GetBPMDirectory() + "BPM").c_str()); //replace it with the temp file
}