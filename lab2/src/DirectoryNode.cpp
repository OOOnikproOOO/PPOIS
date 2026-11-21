/**
 * @file DirectoryNode.cpp
 * @brief Implementation of DirectoryNode methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "DirectoryNode.h"
#include "ComputerException.h"
#include "DeviceNotFoundException.h"

DirectoryNode::DirectoryNode(const std::string& name) : name_(name) {}

bool DirectoryNode::operator==(const DirectoryNode& other) const {
    return name_ == other.name_ && files_ == other.files_ && subdirectories_ == other.subdirectories_;
}

bool DirectoryNode::operator!=(const DirectoryNode& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const DirectoryNode& dir) {
    os << "Directory '" << dir.name_ << "' (" << dir.files_.size() << " files, " << dir.subdirectories_.size() << " subdirs, " << dir.CalculateTotalSizeBytes() << " bytes)";
    return os;
}

void DirectoryNode::AddFile(const FileEntry& file) {
    if (file.GetName().empty()) 
        throw ComputerException("File name cannot be empty.");
    for (int i = 0; i < files_.size(); i++) {
        if (files_[i].GetName() == file.GetName()) 
            throw ComputerException("File '" + file.GetName() + "' already exists in '" + name_ + "'.");
    }
    files_.push_back(file);
}

void DirectoryNode::RemoveFile(const std::string& file_name) {
    for (int i = 0; i < files_.size(); i++) {
        if (files_[i].GetName() == file_name) {
            files_.erase(files_.begin() + i);
            return;
        }
    }
    throw DeviceNotFoundException("File '" + file_name + "' not found in directory '" + name_ + "'.");
}

void DirectoryNode::AddSubdirectory(const DirectoryNode& dir) {
    if (dir.GetName().empty()) 
        throw ComputerException("Directory name cannot be empty.");
    for (int i = 0; i < subdirectories_.size(); i++) {
        if (subdirectories_[i].GetName() == dir.GetName()) 
            throw ComputerException("Subdirectory '" + dir.GetName() + "' already exists in '" + name_ + "'.");
    }
    subdirectories_.push_back(dir);
}

void DirectoryNode::RemoveSubdirectory(const std::string& dir_name) {
    for (int i = 0; i < subdirectories_.size(); i++) {
        if (subdirectories_[i].GetName() == dir_name) {
            subdirectories_.erase(subdirectories_.begin() + i);
            return;
        }
    }
    throw DeviceNotFoundException("Subdirectory '" + dir_name + "' not found in '" + name_ + "'.");
}

int DirectoryNode::CalculateTotalSizeBytes() const {
    int total = 0;
    for (int i = 0; i < files_.size(); i++)
        total += files_[i].GetSizeBytes();
    for (int i = 0; i < subdirectories_.size(); i++)
        total += subdirectories_[i].CalculateTotalSizeBytes();
    return total;
}

int DirectoryNode::CountTotalFiles() const {
    int count = static_cast<int>(files_.size());
    for (int i = 0; i < subdirectories_.size(); i++)
        count += subdirectories_[i].CountTotalFiles();
    return count;
}

const std::string& DirectoryNode::GetName() const {
    return name_;
}

int DirectoryNode::GetFileCount() const {
    return static_cast<int>(files_.size());
}

int DirectoryNode::GetSubdirectoryCount() const {
    return static_cast<int>(subdirectories_.size());
}

FileEntry& DirectoryNode::GetFile(int index) {
    if (index < 0 || index >= files_.size()) 
        throw DeviceNotFoundException("File index out of range.");
    return files_[index];
}

const FileEntry& DirectoryNode::GetFile(int index) const {
    if (index < 0 || index >= files_.size()) 
        throw DeviceNotFoundException("File index out of range.");
    return files_[index];
}

FileEntry& DirectoryNode::GetFileByName(const std::string& file_name) {
    for (int i = 0; i < files_.size(); i++) {
        if (files_[i].GetName() == file_name) 
            return files_[i];
    }
    throw DeviceNotFoundException("File '" + file_name + "' not found in directory '" + name_ + "'.");
}

const FileEntry& DirectoryNode::GetFileByName(const std::string& file_name) const {
    for (int i = 0; i < files_.size(); i++) {
        if (files_[i].GetName() == file_name) 
            return files_[i];
    }
    throw DeviceNotFoundException("File '" + file_name + "' not found in directory '" + name_ + "'.");
}

DirectoryNode& DirectoryNode::GetSubdirectory(int index) {
    if (index < 0 || index >= subdirectories_.size()) 
        throw DeviceNotFoundException("Subdirectory index out of range.");
    return subdirectories_[index];
}

const DirectoryNode& DirectoryNode::GetSubdirectory(int index) const {
    if (index < 0 || index >= subdirectories_.size()) 
        throw DeviceNotFoundException("Subdirectory index out of range.");
    return subdirectories_[index];
}

DirectoryNode& DirectoryNode::GetSubdirectoryByName(const std::string& dir_name) {
    for (int i = 0; i < subdirectories_.size(); i++) {
        if (subdirectories_[i].GetName() == dir_name) 
            return subdirectories_[i];
    }
    throw DeviceNotFoundException("Subdirectory '" + dir_name + "' not found in directory '" + name_ + "'.");
}

const DirectoryNode& DirectoryNode::GetSubdirectoryByName(const std::string& dir_name) const {
    for (int i = 0; i < subdirectories_.size(); i++) {
        if (subdirectories_[i].GetName() == dir_name) 
            return subdirectories_[i];
    }
    throw DeviceNotFoundException("Subdirectory '" + dir_name + "' not found in directory '" + name_ + "'.");
}