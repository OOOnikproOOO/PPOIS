/**
 * @file FileSystem.h
 * @brief Declaration of the FileSystem class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include "DirectoryNode.h"

/**
 * @brief Represents a hierarchical file system partition with file and directory management.
 */
class FileSystem {
public:
    /**
     * @brief Constructs a FileSystem partition.
     * @param fs_type File system format (e.g., "ext4", "NTFS").
     * @param total_capacity_bytes Maximum partition capacity in bytes.
     */
    explicit FileSystem(const std::string& fs_type = "ext4", int total_capacity_bytes = 65536);

    /**
     * @brief Equality operator comparing file system type, capacity, and directory tree.
     * @param other Another FileSystem instance.
     * @return true if file systems match.
     */
    bool operator==(const FileSystem& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another FileSystem instance.
     * @return true if file systems differ.
     */
    bool operator!=(const FileSystem& other) const;

    /**
     * @brief Stream output operator for formatting file system summary.
     * @param os Output stream.
     * @param fs FileSystem instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const FileSystem& fs);

    /**
     * @brief Creates a new file with optional text content in the specified directory.
     * @param dir_path Directory path (e.g., "/" or "/docs").
     * @param file_name Name of the file to create.
     * @param content Initial text data.
     * @param is_readonly Whether the file is read-only.
     */
    void CreateFile(const std::string& dir_path, const std::string& file_name, const std::string& content = "", bool is_readonly = false);

    /**
     * @brief Reads and returns text content from a file in the specified directory.
     * @param dir_path Directory path.
     * @param file_name Target file name.
     * @return File content string.
     */
    std::string ReadFile(const std::string& dir_path, const std::string& file_name) const;

    /**
     * @brief Overwrites text content of an existing file and checks capacity limits.
     * @param dir_path Directory path.
     * @param file_name Target file name.
     * @param new_content New text content.
     */
    void WriteFile(const std::string& dir_path, const std::string& file_name, const std::string& new_content);

    /**
     * @brief Deletes a file from the specified directory.
     * @param dir_path Directory path.
     * @param file_name Target file name.
     */
    void DeleteFile(const std::string& dir_path, const std::string& file_name);

    /**
     * @brief Creates a new subdirectory under the specified parent path.
     * @param parent_path Parent directory path.
     * @param dir_name New directory name.
     */
    void CreateDirectory(const std::string& parent_path, const std::string& dir_name);

    /**
     * @brief Deletes a subdirectory from the specified parent path.
     * @param parent_path Parent directory path.
     * @param dir_name Subdirectory name to delete.
     */
    void DeleteDirectory(const std::string& parent_path, const std::string& dir_name);

    /**
     * @brief Navigates to and returns a reference to a directory by path.
     * @param dir_path Target directory path.
     * @return Reference to DirectoryNode.
     */
    DirectoryNode& NavigateToDirectory(const std::string& dir_path);
    const DirectoryNode& NavigateToDirectory(const std::string& dir_path) const;

    /**
     * @brief Gets total used space across all files in bytes.
     * @return Used space in bytes.
     */
    int GetUsedSpaceBytes() const;

    /**
     * @brief Gets remaining free space on the partition in bytes.
     * @return Free space in bytes.
     */
    int GetFreeSpaceBytes() const;

    /**
     * @brief Gets file system format type string.
     * @return Format string (e.g., "ext4").
     */
    const std::string& GetFsType() const;

    /**
     * @brief Gets total partition capacity in bytes.
     * @return Total capacity in bytes.
     */
    int GetTotalCapacityBytes() const;

    /**
     * @brief Gets reference to the root directory node.
     * @return Reference to root DirectoryNode.
     */
    DirectoryNode& GetRootDirectory();
    const DirectoryNode& GetRootDirectory() const;

private:
    static std::vector<std::string> SplitPath(const std::string& path);

    std::string fs_type_;
    int total_capacity_bytes_;
    DirectoryNode root_directory_;
};

#endif