/**
 * @file ID3TagEditor.cpp
 * @brief Implementation of ID3TagEditor methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "ID3TagEditor.h"

ID3TagEditor::ID3TagEditor(int tag_version, const std::string& encoding, const std::string& default_comment) :
    tag_version_(tag_version), encoding_(encoding), comment_(default_comment), is_dirty_(false) {}

bool ID3TagEditor::operator==(const ID3TagEditor& other) const {
    return tag_version_ == other.tag_version_ &&
           encoding_ == other.encoding_ &&
           comment_ == other.comment_ &&
           is_dirty_ == other.is_dirty_;
}

bool ID3TagEditor::operator!=(const ID3TagEditor& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const ID3TagEditor& editor) {
    os << "ID3Editor[v2." << editor.tag_version_ << " (" << editor.encoding_ << ")" << (editor.is_dirty_ ? " *MODIFIED*" : " [Clean]") << "]";
    return os;
}

void ID3TagEditor::ApplyTags(AudioTrack& track, const std::string& title, const std::string& artist, const std::string& album, const std::string& genre, int year, int track_number) {
    AudioMetadata new_meta(title, artist, album, genre, year, track_number);
    track.UpdateMetadata(new_meta);
    is_dirty_ = true;
}

void ID3TagEditor::SetComment(const std::string& comment) {
    comment_ = comment;
    is_dirty_ = true;
}

void ID3TagEditor::SaveChanges() {
    is_dirty_ = false;
}

void ID3TagEditor::RevertChanges() {
    is_dirty_ = false;
}

int ID3TagEditor::GetTagVersion() const {
    return tag_version_;
}

const std::string& ID3TagEditor::GetEncoding() const {
    return encoding_;
}

const std::string& ID3TagEditor::GetComment() const {
    return comment_;
}

bool ID3TagEditor::IsDirty() const {
    return is_dirty_;
}