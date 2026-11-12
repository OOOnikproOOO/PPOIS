/**
 * @file DirectoryNode.h
 * @brief Declaration of the DirectoryNode class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef DIRECTORYNODE_H
#define DIRECTORYNODE_H

#include <iostream>
#include <string>
#include <vector>
#include "FileEntry.h"

/**
 * @brief Represents a directory node in a hierarchical file system tree.
 */
class DirectoryNode {
public:
    /**
     * @brief Constructs a DirectoryNode instance.
     * @param name Directory name.
     */
    explicit DirectoryNode(const std::string& name = "/");

    /**
     * @brief Equality operator comparing directory names, files and subdirectories.
     * @param other Another DirectoryNode instance.
     * @return true if directories match.
     */
    bool operator==(const DirectoryNode& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another DirectoryNode instance.
     * @return true if directories differ.
     */
    bool operator!=(const DirectoryNode& other) const;

    /**
     * @brief Stream output operator for formatting directory summary.
     * @param os Output stream.
     * @param dir DirectoryNode instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const DirectoryNode& dir);

    /**
     * @brief Adds a new file to this directory.
     * @param file FileEntry object to add.
     */
    void AddFile(const FileEntry& file);

    /**
     * @brief Removes a file by name from this directory.
     * @param file_name Target file name.
     */
    void RemoveFile(const std::string& file_name);

    /**
     * @brief Adds a nested subdirectory to this directory.
     * @param dir DirectoryNode object to add.
     */
    void AddSubdirectory(const DirectoryNode& dir);

    /**
     * @brief Removes a nested subdirectory by name.
     * @param dir_name Target subdirectory name.
     */
    void RemoveSubdirectory(const std::string& dir_name);

    /**
     * @brief Recursively calculates total size of all files in this directory tree in bytes.
     * @return Total size in bytes.
     */
    int CalculateTotalSizeBytes() const;

    /**
     * @brief Recursively counts total number of files in this directory tree.
     * @return File count.
     */
    int CountTotalFiles() const;

    /**
     * @brief Gets directory name.
     * @return Directory name string.
     */
    const std::string& GetName() const;

    /**
     * @brief Gets count of direct files inside this directory.
     * @return Number of files.
     */
    int GetFileCount() const;

    /**
     * @brief Gets count of direct subdirectories inside this directory.
     * @return Number of subdirectories.
     */
    int GetSubdirectoryCount() const;

    /**
     * @brief Gets reference to a file by index.
     * @param index File index.
     * @return Reference to FileEntry.
     */
    FileEntry& GetFile(int index);
    const FileEntry& GetFile(int index) const;

    /**
     * @brief Gets reference to a file by name.
     * @param file_name Target file name.
     * @return Reference to FileEntry.
     */
    FileEntry& GetFileByName(const std::string& file_name);
    const FileEntry& GetFileByName(const std::string& file_name) const;

    /**
     * @brief Gets reference to a subdirectory by index.
     * @param index Subdirectory index.
     * @return Reference to DirectoryNode.
     */
    DirectoryNode& GetSubdirectory(int index);
    const DirectoryNode& GetSubdirectory(int index) const;

    /**
     * @brief Gets reference to a subdirectory by name.
     * @param dir_name Target subdirectory name.
     * @return Reference to DirectoryNode.
     */
    DirectoryNode& GetSubdirectoryByName(const std::string& dir_name);
    const DirectoryNode& GetSubdirectoryByName(const std::string& dir_name) const;

private:
    std::string name_;
    std::vector<FileEntry> files_;
    std::vector<DirectoryNode> subdirectories_;
};

#endif