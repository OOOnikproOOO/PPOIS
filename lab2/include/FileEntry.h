/**
 * @file FileEntry.h
 * @brief Declaration of the FileEntry class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef FILEENTRY_H
#define FILEENTRY_H

#include <iostream>
#include <string>

/**
 * @brief Represents an individual file with text payload, size metadata and read-only attribute.
 */
class FileEntry {
public:
    /**
     * @brief Constructs a FileEntry instance.
     * @param name File name (e.g., "notes.txt").
     * @param content Initial text data stored in the file.
     * @param is_readonly Whether the file is protected from modifications.
     */
    explicit FileEntry(const std::string& name = "untitled.txt", const std::string& content = "", bool is_readonly = false);

    /**
     * @brief Equality operator comparing two file entries.
     * @param other Another FileEntry instance.
     * @return true if name, content, size, and permissions match.
     */
    bool operator==(const FileEntry& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another FileEntry instance.
     * @return true if file entries differ.
     */
    bool operator!=(const FileEntry& other) const;

    /**
     * @brief Stream output operator for formatting file metadata.
     * @param os Output stream.
     * @param file FileEntry instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const FileEntry& file);

    /**
     * @brief Overwrites the file text content and updates byte size.
     * @param new_content New text content.
     */
    void WriteContent(const std::string& new_content);

    /**
     * @brief Appends text data to the end of the file.
     * @param extra Text data to append.
     */
    void AppendContent(const std::string& extra);

    /**
     * @brief Reads and returns the full stored text content.
     * @return File content string.
     */
    std::string ReadContent() const;

    /**
     * @brief Updates the file read-only protection flag.
     * @param readonly Target read-only state.
     */
    void SetReadOnly(bool readonly);

    /**
     * @brief Gets the file name.
     * @return File name string.
     */
    const std::string& GetName() const;

    /**
     * @brief Gets the file size in bytes.
     * @return File size in bytes.
     */
    int GetSizeBytes() const;

    /**
     * @brief Checks whether the file is read-only.
     * @return true if read-only.
     */
    bool IsReadOnly() const;

private:
    std::string name_;
    std::string content_;
    int size_bytes_;
    bool is_readonly_;
};

#endif