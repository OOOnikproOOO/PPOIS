/**
 * @file PluginManager.h
 * @brief Declaration of the PluginManager class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief Manages third-party audio extensions, DSP add-ons and visualizer plugins.
 */
class PluginManager {
public:
    /**
     * @brief Constructs a PluginManager.
     * @param api_version Core host API compatibility version.
     * @param allow_unsigned Security policy for external extensions.
     */
    explicit PluginManager(int api_version = 1, bool allow_unsigned = false);

    /**
     * @brief Compares two PluginManager instances for equality.
     * @param other Manager to compare with.
     * @return true if plugins and settings match.
     */
    bool operator==(const PluginManager& other) const;

    /**
     * @brief Compares two PluginManager instances for inequality.
     * @param other Manager to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const PluginManager& other) const;

    /**
     * @brief Stream output operator for formatting PluginManager info.
     * @param os Output stream.
     * @param pm PluginManager instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const PluginManager& pm);

    /**
     * @brief Registers and activates a new extension.
     * @param extension_name Extension package identifier.
     * @return true if successfully installed.
     */
    bool InstallExtension(const std::string& extension_name);

    /**
     * @brief Uninstalls an extension by name.
     * @param extension_name Extension name.
     * @return true if removed.
     */
    bool UninstallExtension(const std::string& extension_name);

    /**
     * @brief Checks if a specific extension is currently installed and active.
     * @param extension_name Extension name.
     * @return true if active.
     */
    bool HasExtension(const std::string& extension_name) const;

    /**
     * @brief Unloads all active extensions.
     */
    void ClearExtensions();

    /**
     * @brief Gets host API version.
     * @return API version integer.
     */
    int GetApiVersion() const;

    /**
     * @brief Checks if unsigned extensions are permitted.
     * @return true if unsigned allowed.
     */
    bool IsAllowUnsigned() const;

    /**
     * @brief Gets count of installed extensions.
     * @return Number of extensions.
     */
    size_t GetExtensionsCount() const;

    /**
     * @brief Gets constant reference to installed extension identifiers.
     * @return Reference to vector of extension name strings.
     */
    const std::vector<std::string>& GetExtensions() const;

private:
    int api_version_;
    bool allow_unsigned_;
    std::vector<std::string> extensions_;
};

#endif