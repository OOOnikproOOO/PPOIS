/**
 * @file FileSystem.cpp
 * @brief Implementation of FileSystem methods.
 * @author Nikita Momot
 * @date 2026
 */

#include <sstream>
#include "FileSystem.h"
#include "StorageOutOfSpaceException.h"

FileSystem::FileSystem(const std::string& fs_type, int total_capacity_bytes) :
    fs_type_(fs_type), total_capacity_bytes_(total_capacity_bytes), root_directory_("/") {}

bool FileSystem::operator==(const FileSystem& other) const {
    return fs_type_ == other.fs_type_ && total_capacity_bytes_ == other.total_capacity_bytes_ &&
           root_directory_ == other.root_directory_;
}

bool FileSystem::operator!=(const FileSystem& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const FileSystem& fs) {
    os << "FileSystem [" << fs.fs_type_ << ", Used: " << fs.GetUsedSpaceBytes() << " / " << fs.total_capacity_bytes_ << " bytes, Files: " << fs.root_directory_.CountTotalFiles() << "]";
    return os;
}

void FileSystem::CreateFile(const std::string& dir_path, const std::string& file_name, const std::string& content, bool is_readonly) {
    if (content.size() > GetFreeSpaceBytes()) 
        throw StorageOutOfSpaceException("Insufficient file system space to create '" + file_name + "'.");
    DirectoryNode& target = NavigateToDirectory(dir_path);
    target.AddFile(FileEntry(file_name, content, is_readonly));
}

std::string FileSystem::ReadFile(const std::string& dir_path, const std::string& file_name) const {
    const DirectoryNode& target = NavigateToDirectory(dir_path);
    return target.GetFileByName(file_name).ReadContent();
}

void FileSystem::WriteFile(const std::string& dir_path, const std::string& file_name, const std::string& new_content) {
    DirectoryNode& target = NavigateToDirectory(dir_path);
    FileEntry& file = target.GetFileByName(file_name);
    int delta = static_cast<int>(new_content.size()) - file.GetSizeBytes();
    if (delta > GetFreeSpaceBytes()) 
        throw StorageOutOfSpaceException("Insufficient file system space to overwrite '" + file_name + "'.");
    file.WriteContent(new_content);
}

void FileSystem::DeleteFile(const std::string& dir_path, const std::string& file_name) {
    DirectoryNode& target = NavigateToDirectory(dir_path);
    target.RemoveFile(file_name);
}

void FileSystem::CreateDirectory(const std::string& parent_path, const std::string& dir_name) {
    DirectoryNode& parent = NavigateToDirectory(parent_path);
    parent.AddSubdirectory(DirectoryNode(dir_name));
}

void FileSystem::DeleteDirectory(const std::string& parent_path, const std::string& dir_name) {
    DirectoryNode& parent = NavigateToDirectory(parent_path);
    parent.RemoveSubdirectory(dir_name);
}

DirectoryNode& FileSystem::NavigateToDirectory(const std::string& dir_path) {
    std::vector<std::string> parts = SplitPath(dir_path);
    DirectoryNode* current = &root_directory_;
    for (int i = 0; i < parts.size(); i++)
        current = &current->GetSubdirectoryByName(parts[i]);
    return *current;
}

const DirectoryNode& FileSystem::NavigateToDirectory(const std::string& dir_path) const {
    std::vector<std::string> parts = SplitPath(dir_path);
    const DirectoryNode* current = &root_directory_;
    for (int i = 0; i < parts.size(); i++)
        current = &current->GetSubdirectoryByName(parts[i]);
    return *current;
}

int FileSystem::GetUsedSpaceBytes() const {
    return root_directory_.CalculateTotalSizeBytes();
}

int FileSystem::GetFreeSpaceBytes() const {
    int free_space = total_capacity_bytes_ - GetUsedSpaceBytes();
    return free_space > 0 ? free_space : 0;
}

const std::string& FileSystem::GetFsType() const {
    return fs_type_;
}

int FileSystem::GetTotalCapacityBytes() const {
    return total_capacity_bytes_;
}

DirectoryNode& FileSystem::GetRootDirectory() {
    return root_directory_;
}

const DirectoryNode& FileSystem::GetRootDirectory() const {
    return root_directory_;
}

std::vector<std::string> FileSystem::SplitPath(const std::string& path) {
    std::vector<std::string> parts;
    std::stringstream ss(path);
    std::string item;
    while (std::getline(ss, item, '/')) {
        if (!item.empty()) 
            parts.push_back(item);
    }
    return parts;
}