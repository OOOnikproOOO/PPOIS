/**
 * @file MusicFolder.cpp
 * @brief Implementation of MusicFolder methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "MusicFolder.h"
#include <algorithm>

MusicFolder::MusicFolder(const std::string& folder_path, bool is_recursive) :
    folder_path_(folder_path), is_recursive_(is_recursive), file_extensions_({".mp3", ".flac", ".wav"}), discovered_file_paths_() {}

bool MusicFolder::operator==(const MusicFolder& other) const {
    return folder_path_ == other.folder_path_ &&
           is_recursive_ == other.is_recursive_ &&
           file_extensions_ == other.file_extensions_ &&
           discovered_file_paths_ == other.discovered_file_paths_;
}

bool MusicFolder::operator!=(const MusicFolder& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const MusicFolder& folder) {
    os << "MusicFolder[" << folder.folder_path_ << " (" << folder.discovered_file_paths_.size() << " files discovered)]";
    return os;
}

void MusicFolder::AddAllowedExtension(const std::string& extension) {
    if (std::find(file_extensions_.begin(), file_extensions_.end(), extension) == file_extensions_.end())
        file_extensions_.push_back(extension);
}

size_t MusicFolder::ScanFolder(const std::vector<std::string>& sample_filenames) {
    size_t count = 0;
    for (const auto& filename : sample_filenames) {
        for (const auto& ext : file_extensions_) {
            if (filename.size() >= ext.size() &&
                filename.compare(filename.size() - ext.size(), ext.size(), ext) == 0) {
                discovered_file_paths_.push_back(folder_path_ + "/" + filename);
                count++;
                break;
            }
        }
    }
    return count;
}

bool MusicFolder::ContainsFile(const std::string& file_path) const {
    return std::find(discovered_file_paths_.begin(), discovered_file_paths_.end(), file_path) != discovered_file_paths_.end();
}

void MusicFolder::ClearScannedFiles() {
    discovered_file_paths_.clear();
}

const std::string& MusicFolder::GetFolderPath() const {
    return folder_path_;
}

bool MusicFolder::IsRecursive() const {
    return is_recursive_;
}

const std::vector<std::string>& MusicFolder::GetAllowedExtensions() const {
    return file_extensions_;
}

const std::vector<std::string>& MusicFolder::GetDiscoveredFiles() const {
    return discovered_file_paths_;
}