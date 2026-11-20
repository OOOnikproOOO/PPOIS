/**
 * @file main.cpp
 * @brief Interactive CLI - Music Player Application.
 * @author Nikita Momot
 * @date 2026
 */

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>

#include "MusicPlayer.h"
#include "AudioVisualizer.h"
#include "SpectrumAnalyzer.h"
#include "LyricsViewer.h"
#include "Bookmark.h"
#include "PodcastShow.h"
#include "PlaybackStatistics.h"
#include "PluginManager.h"
#include "MusicPlayerException.h"

// Table Menu Helpers

static constexpr int kMenuWidth = 60;

static void PrintDivider(int width = kMenuWidth) {
    for (int i = 0; i < width; i++)
        std::cout << "-";

    std::cout << "\n";
}

static void PrintRow(const std::string& text, int width = kMenuWidth) {
    int max_len = width - 4;
    std::string safe_text = (static_cast<int>(text.length()) > max_len) ? text.substr(0, max_len) : text;
    std::cout << "| " << safe_text;
    int spaces = width - 3 - static_cast<int>(safe_text.length());
    if (spaces < 0)
        spaces = 0;

    for (int i = 0; i < spaces; i++)
        std::cout << " ";

    std::cout << "|\n";
}

static void PrintHeader(const std::string& title, int width = kMenuWidth) {
    PrintDivider(width);
    int total_padding = width - 2 - static_cast<int>(title.length());
    int pad_left = total_padding / 2;
    int pad_right = total_padding - pad_left;
    std::cout << "|";
    for (int i = 0; i < pad_left; i++)
        std::cout << " ";

    std::cout << title;
    for (int i = 0; i < pad_right; i++)
        std::cout << " ";

    std::cout << "|\n";
    PrintDivider(width);
}

static void PrintMainMenu() {
    PrintHeader("Music Player Application");
    PrintRow(" 1 - Load Demo Music Library");
    PrintRow(" 2 - Add Track by File Path");
    PrintRow(" 3 - Play / Resume Audio");
    PrintRow(" 4 - Pause Playback");
    PrintRow(" 5 - Stop Playback");
    PrintRow(" 6 - Next Track");
    PrintRow(" 7 - Previous Track");
    PrintRow(" 8 - Seek Playback Timeline");
    PrintRow(" 9 - Volume Control and Mute");
    PrintRow("10 - Audio Effects Rack (DSP)");
    PrintRow("11 - View Playback Queue");
    PrintRow("12 - Synchronized Lyrics (Karaoke)");
    PrintRow("13 - Time Bookmarks");
    PrintRow("14 - Audio Output Devices");
    PrintRow("15 - User Profile & Subscription");
    PrintRow("16 - Podcast Shows & Episodes");
    PrintRow("17 - Playback History & Statistics");
    PrintRow("18 - Extensions and Add-ons Manager");
    PrintRow(" 0 - Exit Application");
    PrintDivider();
}

int main() {
    MusicPlayer player("Cosmic Player Pro");
    AudioVisualizer visualizer("VU_Meter", 60);
    SpectrumAnalyzer spectrum(12, 0.05, true);
    std::vector<Bookmark> bookmarks;
    PodcastShow podcast("IT Deep Dive", "OOOnikproOOO", "Technology");
    PlaybackStatistics stats;
    PluginManager plugin_mgr(2, true);

    std::map<std::string, LyricsViewer> karaoke_storage;

    LyricsViewer queen_lyrics(true, 16);
    queen_lyrics.AddLine(LyricLine(0.8, "Is this the real life? Is this just fantasy?"));
    queen_lyrics.AddLine(LyricLine(8.5, "Caught in a landslide, no escape from reality..."));
    queen_lyrics.AddLine(LyricLine(16.0, "Open your eyes, look up to the skies and see...", true));
    queen_lyrics.AddLine(LyricLine(24.0, "I'm just a poor boy, I need no sympathy..."));
    queen_lyrics.AddLine(LyricLine(32.0, "Because I'm easy come, easy go, little high, little low..."));
    karaoke_storage["Bohemian Rhapsody"] = queen_lyrics;

    LyricsViewer daft_lyrics(true, 16);
    daft_lyrics.AddLine(LyricLine(4.0, "Like the legend of the phoenix, all ends with beginnings..."));
    daft_lyrics.AddLine(LyricLine(12.0, "What keeps the planet spinning, the force from the beginning..."));
    daft_lyrics.AddLine(LyricLine(21.0, "We've come too far to give up who we are...", true));
    daft_lyrics.AddLine(LyricLine(29.5, "We're up all night 'til the sun, we're up all night to get some...", true));
    daft_lyrics.AddLine(LyricLine(37.0, "We're up all night for good fun, we're up all night to get lucky!", true));
    karaoke_storage["Get Lucky"] = daft_lyrics;

    LyricsViewer beethoven_lyrics(true, 16);
    beethoven_lyrics.AddLine(LyricLine(0.5, "(Allegro con brio) Fate knocking at the door: Da-da-da-dum!"));
    beethoven_lyrics.AddLine(LyricLine(6.0, "Powerful orchestral repetition in C minor motif..."));
    beethoven_lyrics.AddLine(LyricLine(15.0, "Horn call introduces the lyrical second theme in E-flat major...", true));
    beethoven_lyrics.AddLine(LyricLine(24.0, "Dramatic orchestral crescendo building towards triumphant development!"));
    karaoke_storage["Symphony No. 5"] = beethoven_lyrics;

    player.GetDeviceManager().RegisterDevice(AudioOutputDevice("Speakers (Realtek Audio)", "DEV_SPK_01", 2, true, true));
    player.GetDeviceManager().RegisterDevice(AudioOutputDevice("Headphones (Wireless Bluetooth)", "DEV_HP_02", 2, true, false));

    podcast.AddEpisode(PodcastEpisode("Architecture of OOP Audio Players", 1, 1800.0, "2026.11.20", false));

    int choice = -1;
    while (choice != 0) {
        PrintMainMenu();
        std::cout << "Selected: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::string dummy;
            std::cin >> dummy;
            continue;
        }

        try {
            switch (choice) {
                case 1: {
                    AudioTrack t1("music/queen_bohemian.mp3", 354.0, AudioMetadata("Bohemian Rhapsody", "Queen", "A Night at the Opera", "Rock", 1975, 11), AudioCodec("MP3", 320, 44100, 2, false));
                    AudioTrack t2("music/daft_punk_get_lucky.flac", 248.0, AudioMetadata("Get Lucky", "Daft Punk", "Random Access Memories", "Electronic", 2013, 8), AudioCodec("FLAC", 960, 48000, 2, true));
                    AudioTrack t3("music/beethoven_symphony5.wav", 432.0, AudioMetadata("Symphony No. 5", "Ludwig van Beethoven", "Classical Masterpieces", "Classical", 1808, 1), AudioCodec("WAV", 1411, 44100, 2, true));

                    player.LoadAndQueueTrack(t1);
                    player.LoadAndQueueTrack(t2);
                    player.LoadAndQueueTrack(t3);

                    std::cout << "\n  SUCCESS: Added 3 demo tracks into library and playback queue!\n\n";
                    break;
                }
                case 2: {
                    std::cout << "\n  Enter path to audio file (e.g. music/song.mp3 or C:/Music/test.mp3): ";
                    std::string path;
                    std::cin >> path;

                    std::cout << "  Enter track title: ";
                    std::string title;
                    std::cin.ignore();
                    std::getline(std::cin, title);

                    std::cout << "  Enter artist name: ";
                    std::string artist;
                    std::getline(std::cin, artist);

                    std::cout << "  Enter approximate duration in seconds (e.g. 210): ";
                    double duration = 200.0;
                    std::cin >> duration;

                    std::string codec_name = "MP3";
                    if (path.length() >= 5 && path.substr(path.length() - 5) == ".flac")
                        codec_name = "FLAC";
                    else if (path.length() >= 4 && path.substr(path.length() - 4) == ".wav")
                        codec_name = "WAV";

                    AudioTrack custom_track(path, duration, AudioMetadata(title, artist, "User Imports", "General", 2026, 1), AudioCodec(codec_name, 320, 44100, 2));
                    player.LoadAndQueueTrack(custom_track);
                    karaoke_storage[title] = LyricsViewer(true, 16);
                    std::cout << "  SUCCESS: Track '" << title << "' added to library and queue!\n\n";
                    break;
                }
                case 3: {
                    if (player.GetQueue().GetQueueSize() == 0) {
                        std::cout << "\n  Queue is empty! Please load tracks first (option 1 or 2).\n\n";
                        break;
                    }

                    bool started = player.Play();
                    if (started) {
                        const AudioTrack& cur = player.GetQueue().GetCurrentTrack();

                        std::cout << "\n  Now Playing: " << cur.GetMetadata().FormatDisplayString() << "\n";
                        std::cout << "  File: " << cur.GetFilePath() << " (" << cur.GetCodec().GetCodecName() << ", " << cur.GetCodec().GetBitrateKbps() << " kbps)\n";

                        AudioSample sample(0.65 * player.GetVolume().GetEffectiveVolume() / 100.0, 0.70 * player.GetVolume().GetEffectiveVolume() / 100.0, 16);
                        visualizer.UpdateLevels(sample);
                        player.GetEngine().GetBuffer().WriteSample(sample);
                        spectrum.ProcessBuffer(player.GetEngine().GetBuffer());

                        std::cout << "  Stereo Signal Level:  " << visualizer.RenderStereoVuMeter() << "\n";
                        std::cout << "  Spectral Audio Power: " << spectrum.CalculateTotalEnergy() << " W\n";
                        std::cout << "  Timeline Position:    " << player.GetPosition().FormatTimeElapsed() << "\n";

                        auto it = karaoke_storage.find(cur.GetMetadata().GetTitle());
                        if (it != karaoke_storage.end()) {
                            const LyricLine* line = it->second.GetCurrentLine(player.GetPosition().GetCurrentSec());
                            if (line)
                                std::cout << "  Lyrics:               " << line->FormatTimestampedLine() << "\n";
                        }

                        stats.RecordSession(cur.GetDurationSec(), cur.GetMetadata().GetGenre(), false);
                        std::cout << "\n";
                    }
                    break;
                }
                case 4: {
                    player.Pause();
                    std::cout << "\n  Playback paused.\n\n";
                    break;
                }
                case 5: {
                    player.Stop();
                    std::cout << "\n  Playback stopped. Position reset to start.\n\n";
                    break;
                }
                case 6: {
                    if (player.Next()) {
                        const AudioTrack& cur = player.GetQueue().GetCurrentTrack();
                        stats.RecordSession(45.0, cur.GetMetadata().GetGenre(), true);
                        std::cout << "\n  Skipped to next track: " << cur.GetMetadata().FormatDisplayString() << "\n\n";
                    } else {
                        std::cout << "\n  Reached end of playback queue.\n\n";
                    }
                    break;
                }
                case 7: {
                    if (player.Previous()) {
                        const AudioTrack& cur = player.GetQueue().GetCurrentTrack();
                        stats.RecordSession(30.0, cur.GetMetadata().GetGenre(), true);
                        std::cout << "\n  Stepped to previous track: " << cur.GetMetadata().FormatDisplayString() << "\n\n";
                    } else {
                        std::cout << "\n  Already at the beginning of queue.\n\n";
                    }
                    break;
                }
                case 8: {
                    std::cout << "\n  Enter target timeline position in seconds: ";
                    double sec = 0.0;
                    std::cin >> sec;
                    player.Seek(sec);
                    if (player.GetQueue().GetQueueSize() > 0) {
                        const AudioTrack& cur = player.GetQueue().GetCurrentTrack();
                        stats.RecordSession(sec, cur.GetMetadata().GetGenre(), false);
                    }
                    std::cout << "  Seek completed. Position: " << player.GetPosition().FormatTimeElapsed() << "\n\n";
                    break;
                }
                case 9: {
                    std::cout << "\n  --- VOLUME CONTROL ---\n";
                    std::cout << "  Current Volume: " << player.GetVolume().GetVolumeLevel() << "%\n";
                    std::cout << "  1. Set Volume Level (0-100%)\n";
                    std::cout << "  2. Toggle Mute State\n";
                    std::cout << "  Selection: ";
                    int vopt = 0;
                    std::cin >> vopt;
                    if (vopt == 1) {
                        std::cout << "  Enter volume percentage (0-100): ";
                        int lvl = 70;
                        std::cin >> lvl;
                        player.GetVolume().SetVolume(lvl);
                        std::cout << "  Volume updated: " << player.GetVolume().GetVolumeLevel()
                                  << "% (Gain: " << player.GetVolume().CalculateGainDecibels() << " dB)\n\n";
                    } else if (vopt == 2) {
                        player.GetVolume().ToggleMute();
                        std::cout << "  Mute state: " << (player.GetVolume().IsMuted() ? "MUTED" : "UNMUTED") << "\n\n";
                    }
                    break;
                }
                case 10: {
                    std::cout << "\n  --- AUDIO EFFECTS RACK (DSP) ---\n";
                    std::cout << "  1. Equalizer Presets (Rock / Pop / Jazz / Flat)\n";
                    std::cout << "  2. Bass Boost (Current: +" << player.GetEffectsRack().GetBassBoost().GetBoostDb() << " dB)\n";
                    std::cout << "  3. Reverb Effect (Status: " << (player.GetEffectsRack().GetReverb().IsActive() ? "ON" : "OFF") << ")\n";
                    std::cout << "  4. Pitch Shift (Offset: " << player.GetEffectsRack().GetPitch().GetSemitonesOffset() << " semitones)\n";
                    std::cout << "  5. Toggle Master Bypass\n";
                    std::cout << "  Selection: ";
                    int eff_opt = 0;
                    std::cin >> eff_opt;
                    if (eff_opt == 1) {
                        std::cout << "  Enter preset name (Rock, Pop, Jazz, Flat): ";
                        std::string pr;
                        std::cin >> pr;
                        player.GetEffectsRack().GetEqualizer().ApplyPreset(pr);
                        std::cout << "  Equalizer preset applied: " << player.GetEffectsRack().GetEqualizer().GetPresetName() << "\n\n";
                    } else if (eff_opt == 2) {
                        std::cout << "  Enter bass boost in dB (0..18): ";
                        double bdb = 6.0;
                        std::cin >> bdb;
                        player.GetEffectsRack().GetBassBoost().SetBoost(bdb);
                        player.GetEffectsRack().GetBassBoost().ToggleEffect(bdb > 0.0);
                        std::cout << "  Bass boost configured: +" << player.GetEffectsRack().GetBassBoost().GetBoostDb() << " dB\n\n";
                    } else if (eff_opt == 3) {
                        bool cur = player.GetEffectsRack().GetReverb().IsActive();
                        player.GetEffectsRack().GetReverb().ToggleEffect(!cur);
                        std::cout << "  Reverb effect: " << (!cur ? "ENABLED" : "BYPASSED") << "\n\n";
                    } else if (eff_opt == 4) {
                        std::cout << "  Enter semitone pitch offset (-12..+12): ";
                        int semi = 0;
                        std::cin >> semi;
                        player.GetEffectsRack().GetPitch().SetPitchOffset(semi);
                        player.GetEffectsRack().GetPitch().ResetPitch();
                        std::cout << "  Pitch offset set to " << semi << " semitones.\n\n";
                    } else if (eff_opt == 5) {
                        bool b = player.GetEffectsRack().IsBypass();
                        player.GetEffectsRack().SetBypassAll(!b);
                        std::cout << "  Master DSP Bypass: " << (!b ? "ENABLED" : "DISABLED") << "\n\n";
                    }
                    break;
                }
                case 11: {
                    std::cout << "\n  --- CURRENT PLAYBACK QUEUE ---\n";
                    const auto& tracks = player.GetQueue().GetTracks();
                    int cur_idx = player.GetQueue().GetCurrentIndex();
                    for (size_t i = 0; i < tracks.size(); i++) {
                        std::cout << "  [" << (static_cast<int>(i) == cur_idx ? ">>" : "  ") << "] "
                                  << (i + 1) << ". " << tracks[i].GetMetadata().FormatDisplayString()
                                  << " (" << tracks[i].FormatDurationString() << ")\n";
                    }
                    std::cout << "\n";
                    break;
                }
                case 12: {
                    std::cout << "\n  --- SYNCHRONIZED SONG LYRICS (KARAOKE) ---\n";
                    if (player.GetQueue().GetQueueSize() > 0) {
                        const AudioTrack& cur = player.GetQueue().GetCurrentTrack();
                        std::cout << "  Track: " << cur.GetMetadata().FormatDisplayString() << "\n";
                        auto it = karaoke_storage.find(cur.GetMetadata().GetTitle());
                        if (it != karaoke_storage.end() && it->second.GetLinesCount() > 0) {
                            for (const auto& line : it->second.GetLines())
                                std::cout << "  " << line.FormatTimestampedLine() << "\n";
                        } else {
                            std::cout << "  No synchronized lyrics found for this track.\n";
                        }
                    } else {
                        std::cout << "  No tracks in playback queue.\n";
                    }
                    std::cout << "\n";
                    break;
                }
                case 13: {
                    std::cout << "\n  --- TIME BOOKMARKS ---\n";
                    std::cout << "  1. Save Bookmark at Current Position\n";
                    std::cout << "  2. List All Bookmarks\n";
                    std::cout << "  Selection: ";
                    int bopt = 0;
                    std::cin >> bopt;
                    if (bopt == 1) {
                        std::cout << "  Enter note for bookmark: ";
                        std::string note;
                        std::cin.ignore();
                        std::getline(std::cin, note);
                        std::string track_name = player.GetQueue().GetQueueSize() > 0 ? player.GetQueue().GetCurrentTrack().GetMetadata().GetTitle() : "Live Stream";
                        bookmarks.push_back(Bookmark(track_name, player.GetPosition().GetCurrentSec(), note, "2026.11.20"));
                        std::cout << "  Bookmark saved: " << bookmarks.back().FormatBookmarkString() << "\n\n";
                    } else if (bopt == 2) {
                        std::cout << "  Total Bookmarks: " << bookmarks.size() << "\n";
                        for (const auto& bm : bookmarks)
                            std::cout << "  * " << bm.FormatBookmarkString() << "\n";

                        std::cout << "\n";
                    }
                    break;
                }
                case 14: {
                    std::cout << "\n  --- AUDIO OUTPUT DEVICES ---\n";
                    for (const auto& dev : player.GetDeviceManager().GetDevices())
                        std::cout << "  " << dev.FormatDeviceInfo() << "\n";

                    std::cout << "  Enter Device ID to switch to (e.g. DEV_HP_02): ";
                    std::string dev_id;
                    std::cin >> dev_id;
                    player.GetDeviceManager().SelectActiveDevice(dev_id);
                    std::cout << "  Audio routed to: " << player.GetDeviceManager().GetActiveDevice().GetDeviceName() << "\n\n";
                    break;
                }
                case 15: {
                    std::cout << "\n  --- USER PROFILE & SUBSCRIPTION ---\n";
                    std::cout << "  " << player.GetUser().FormatProfileCard() << "\n";
                    std::cout << "  " << player.GetSubscription() << "\n\n";
                    break;
                }
                case 16: {
                    std::cout << "\n  --- PODCAST CATALOG ---\n";
                    std::cout << "  " << podcast << "\n";
                    for (const auto& ep : podcast.GetEpisodes())
                        std::cout << "  " << ep.FormatEpisodeSummary() << "\n";

                    std::cout << "\n";
                    break;
                }
                case 17: {
                    std::cout << "\n  --- PLAYBACK HISTORY & STATISTICS ---\n";
                    std::cout << "  Total Listening Minutes: " << std::fixed << std::setprecision(1) << (stats.GetTotalListenTimeSec() / 60.0) << "\n";
                    std::cout << "  Playback Sessions Count: " << stats.GetSessionsCount() << "\n";
                    std::cout << "  Skipped Tracks Count:    " << stats.GetSkipsCount() << "\n";
                    std::cout << "  Skip Rate:               " << std::fixed << std::setprecision(1) << stats.CalculateSkipRatePercentage() << "%\n";
                    std::cout << "  Average Session Length:  " << std::fixed << std::setprecision(1) << stats.GetAverageSessionMinutes() << " min\n";
                    std::cout << "  Favorite Genre:          " << stats.GetFavoriteGenre() << "\n";
                    std::cout << "  Recent Tracks in History:\n";
                    for (const auto& item : player.GetHistory().GetRecords())
                        std::cout << "  - " << item << "\n";

                    std::cout << "\n";
                    break;
                }
                case 18: {
                    std::cout << "\n  --- EXTENSIONS AND ADD-ONS MANAGER ---\n";
                    std::cout << "  " << plugin_mgr << "\n";
                    std::cout << "  1. Install Extension\n";
                    std::cout << "  2. Uninstall Extension\n";
                    std::cout << "  Selection: ";
                    int popt = 0;
                    std::cin >> popt;
                    if (popt == 1) {
                        std::cout << "  Enter extension name (e.g. HighRes_Audio_Booster): ";
                        std::string pname;
                        std::cin >> pname;
                        plugin_mgr.InstallExtension(pname);
                        std::cout << "  Extension '" << pname << "' successfully installed!\n\n";
                    } else if (popt == 2) {
                        std::cout << "  Enter extension name to remove: ";
                        std::string pname;
                        std::cin >> pname;
                        plugin_mgr.UninstallExtension(pname);
                        std::cout << "  Extension removed.\n\n";
                    }
                    break;
                }
                case 0: {
                    std::cout << "\n  Exiting Music Player Application. Goodbye!\n";
                    player.PowerOff();
                    break;
                }
                default: {
                    std::cout << "  Invalid menu option. Please try again.\n\n";
                    break;
                }
            }
        } catch (const MusicPlayerException& ex) {
            std::cout << "\n  [PLAYER ERROR]: " << ex.what() << "\n\n";
        }
    }

    return 0;
}