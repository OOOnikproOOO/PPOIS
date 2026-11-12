/**
 * @file FileEntry.cpp
 * @brief Implementation of FileEntry methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "FileEntry.h"
#include "ComputerException.h"

FileEntry::FileEntry(const std::string& name, const std::string& content, bool is_readonly) :
    name_(name), content_(content), size_bytes_(static_cast<int>(content.size())), is_readonly_(is_readonly) {}

bool FileEntry::operator==(const FileEntry& other) const {
    return name_ == other.name_ && content_ == other.content_ &&
           size_bytes_ == other.size_bytes_ && is_readonly_ == other.is_readonly_;
}

bool FileEntry::operator!=(const FileEntry& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const FileEntry& file) {
    os << "FileEntry '" << file.name_ << "' (" << file.size_bytes_ << " bytes" << (file.is_readonly_ ? ", R/O" : "") << ")";
    return os;
}

void FileEntry::WriteContent(const std::string& new_content) {
    if (is_readonly_) 
        throw ComputerException("Cannot write to read-only file '" + name_ + "'.");
    content_ = new_content;
    size_bytes_ = static_cast<int>(content_.size());
}

void FileEntry::AppendContent(const std::string& extra) {
    if (is_readonly_) 
        throw ComputerException("Cannot append to read-only file '" + name_ + "'.");
    content_ += extra;
    size_bytes_ = static_cast<int>(content_.size());
}

std::string FileEntry::ReadContent() const {
    return content_;
}

void FileEntry::SetReadOnly(bool readonly) {
    is_readonly_ = readonly;
}

const std::string& FileEntry::GetName() const {
    return name_;
}

int FileEntry::GetSizeBytes() const {
    return size_bytes_;
}

bool FileEntry::IsReadOnly() const {
    return is_readonly_;
}