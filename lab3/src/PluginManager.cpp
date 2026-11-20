/**
 * @file PluginManager.cpp
 * @brief Implementation of PluginManager methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "PluginManager.h"
#include <algorithm>

PluginManager::PluginManager(int api_version, bool allow_unsigned) : api_version_(api_version < 1 ? 1 : api_version), allow_unsigned_(allow_unsigned) {}

bool PluginManager::operator==(const PluginManager& other) const {
    return api_version_ == other.api_version_ &&
           allow_unsigned_ == other.allow_unsigned_ &&
           extensions_ == other.extensions_;
}

bool PluginManager::operator!=(const PluginManager& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PluginManager& pm) {
    os << "PluginManager[API v" << pm.api_version_ << ", " << pm.extensions_.size() << " extensions, Unsigned: " << (pm.allow_unsigned_ ? "ALLOWED" : "BLOCKED") << "]";
    return os;
}

bool PluginManager::InstallExtension(const std::string& extension_name) {
    if (extension_name.empty())
        return false;

    if (HasExtension(extension_name))
        return false;

    extensions_.push_back(extension_name);
    return true;
}

bool PluginManager::UninstallExtension(const std::string& extension_name) {
    auto it = std::find(extensions_.begin(), extensions_.end(), extension_name);
    if (it == extensions_.end())
        return false;

    extensions_.erase(it);
    return true;
}

bool PluginManager::HasExtension(const std::string& extension_name) const {
    return std::find(extensions_.begin(), extensions_.end(), extension_name) != extensions_.end();
}

void PluginManager::ClearExtensions() {
    extensions_.clear();
}

int PluginManager::GetApiVersion() const {
    return api_version_;
}

bool PluginManager::IsAllowUnsigned() const {
    return allow_unsigned_;
}

size_t PluginManager::GetExtensionsCount() const {
    return extensions_.size();
}

const std::vector<std::string>& PluginManager::GetExtensions() const {
    return extensions_;
}