/**
 * @file MusicFolder.h
 * @brief Declaration of the MusicFolder class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef MUSICFOLDER_H
#define MUSICFOLDER_H

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Manages local storage directory monitoring and audio file discovery.
 */
class MusicFolder {
public:
    /**
     * @brief Constructs a MusicFolder.
     * @param folder_path Filesystem directory path.
     * @param is_recursive Whether subdirectories are traversed.
     */
    MusicFolder(const std::string& folder_path = "C:/Users/Music", bool is_recursive = true);

    bool operator==(const MusicFolder& other) const;
    bool operator!=(const MusicFolder& other) const;
    friend std::ostream& operator<<(std::ostream& os, const MusicFolder& folder);

    /**
     * @brief Adds a recognized file format extension to the scan filter.
     * @param extension Extension string (e.g. ".mp3", ".flac", ".wav").
     */
    void AddAllowedExtension(const std::string& extension);

    /**
     * @brief Simulates scanning directory and discovering audio files.
     * @param sample_filenames List of candidate filenames found in folder.
     * @return Number of files matched against allowed extensions.
     */
    size_t ScanFolder(const std::vector<std::string>& sample_filenames);

    /**
     * @brief Checks if a specific file path is present in discovered files.
     * @param file_path Path to check.
     * @return true if discovered.
     */
    bool ContainsFile(const std::string& file_path) const;

    /**
     * @brief Clears discovered file registry.
     */
    void ClearScannedFiles();

    const std::string& GetFolderPath() const;
    bool IsRecursive() const;
    const std::vector<std::string>& GetAllowedExtensions() const;
    const std::vector<std::string>& GetDiscoveredFiles() const;

private:
    std::string folder_path_;
    bool is_recursive_;
    std::vector<std::string> file_extensions_;
    std::vector<std::string> discovered_file_paths_;
};

#endif