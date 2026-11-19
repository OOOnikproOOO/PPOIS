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

    /**
     * @brief Compares two MusicFolder instances for equality.
     * @param other Folder to compare with.
     * @return true if paths and settings match.
     */
    bool operator==(const MusicFolder& other) const;

    /**
     * @brief Compares two MusicFolder instances for inequality.
     * @param other Folder to compare with.
     * @return true if paths or settings differ.
     */
    bool operator!=(const MusicFolder& other) const;

    /**
     * @brief Stream output operator for formatting MusicFolder info.
     * @param os Output stream.
     * @param folder Folder instance to display.
     * @return Reference to the output stream.
     */
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

    /**
     * @brief Gets filesystem directory path.
     * @return Reference to folder path string.
     */
    const std::string& GetFolderPath() const;

    /**
     * @brief Checks if folder scan includes subdirectories.
     * @return true if recursive.
     */
    bool IsRecursive() const;

    /**
     * @brief Gets allowed audio file extension filters.
     * @return Reference to vector of extension strings.
     */
    const std::vector<std::string>& GetAllowedExtensions() const;

    /**
     * @brief Gets list of discovered audio file paths.
     * @return Reference to vector of discovered file paths.
     */
    const std::vector<std::string>& GetDiscoveredFiles() const;

private:
    std::string folder_path_;
    bool is_recursive_;
    std::vector<std::string> file_extensions_;
    std::vector<std::string> discovered_file_paths_;
};

#endif