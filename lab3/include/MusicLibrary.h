/**
 * @file MusicLibrary.h
 * @brief Declaration of the MusicLibrary class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <iostream>
#include <string>
#include <vector>
#include "AudioTrack.h"
#include "Album.h"
#include "Artist.h"
#include "Playlist.h"

/**
 * @brief Central repository managing tracks, albums, artists, and playlists.
 */
class MusicLibrary {
public:
    /**
     * @brief Constructs a MusicLibrary.
     * @param library_name Name of media library database.
     */
    explicit MusicLibrary(const std::string& library_name = "Main Music Library");

    /**
     * @brief Compares two MusicLibrary instances for equality.
     * @param other Library to compare with.
     * @return true if properties and collections match.
     */
    bool operator==(const MusicLibrary& other) const;

    /**
     * @brief Compares two MusicLibrary instances for inequality.
     * @param other Library to compare with.
     * @return true if properties or collections differ.
     */
    bool operator!=(const MusicLibrary& other) const;

    /**
     * @brief Stream output operator for formatting MusicLibrary info.
     * @param os Output stream.
     * @param lib Library instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const MusicLibrary& lib);

    /**
     * @brief Adds a track to the library collection.
     * @param track AudioTrack to insert.
     */
    void AddTrack(const AudioTrack& track);

    /**
     * @brief Searches for a track by exact title.
     * @param title Track title.
     * @return Const reference to found AudioTrack.
     * @throws TrackNotFoundException if not found.
     */
    const AudioTrack& FindTrackByTitle(const std::string& title) const;

    /**
     * @brief Adds a playlist to the user library.
     * @param playlist Playlist to store.
     */
    void AddPlaylist(const Playlist& playlist);

    /**
     * @brief Searches for a playlist by name.
     * @param name Playlist name.
     * @return Const reference to found Playlist.
     * @throws PlaylistNotFoundException if not found.
     */
    const Playlist& FindPlaylistByName(const std::string& name) const;

    /**
     * @brief Calculates cumulative listening duration in seconds across all stored tracks.
     * @return Total seconds.
     */
    double GetTotalListeningTimeSec() const;

    /**
     * @brief Gets media library database name.
     * @return Reference to library name string.
     */
    const std::string& GetLibraryName() const;

    /**
     * @brief Gets collection of all audio tracks in library.
     * @return Reference to vector of AudioTrack.
     */
    const std::vector<AudioTrack>& GetTracks() const;

    /**
     * @brief Gets collection of all albums in library.
     * @return Reference to vector of Album.
     */
    const std::vector<Album>& GetAlbums() const;

    /**
     * @brief Gets collection of all artists in library.
     * @return Reference to vector of Artist.
     */
    const std::vector<Artist>& GetArtists() const;

    /**
     * @brief Gets collection of user playlists in library.
     * @return Reference to vector of Playlist.
     */
    const std::vector<Playlist>& GetPlaylists() const;

private:
    std::string library_name_;
    std::vector<AudioTrack> tracks_;
    std::vector<Album> albums_;
    std::vector<Artist> artists_;
    std::vector<Playlist> playlists_;
};

#endif