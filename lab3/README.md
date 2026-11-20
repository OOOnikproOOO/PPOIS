# Лабораторная работа №3 — Крупный ООП-проект

**Студент:** Момот Никита Дмитриевич  
**Группа:** 521702  
**Предметная область:** Приложение музыкального проигрывателя (Music Player Application)

---

## 1. Описание предметной области

Проект моделирует архитектуру современного кроссплатформенного музыкального проигрывателя:
- **Аудиоформаты, кодеки и декодеры:** структуры сэмплов (`AudioSample`), циклический аудиобуфер (`AudioBuffer`), спецификации кодеков (`AudioCodec`), декодеры форматов (`MP3Decoder`, `FLACDecoder`, `WAVDecoder`), потоковые источники (`AudioStream`).
- **Музыкальный контент и медиатека:** метаданные (`AudioMetadata`), аудиодорожки (`AudioTrack`), альбомы (`Album`), исполнители (`Artist`), пользовательские плейлисты (`Playlist`), умные плейлисты (`SmartPlaylist`), папки локального сканирования (`MusicFolder`), центральная медиатека (`MusicLibrary`).
- **Звуковая обработка и эффекты:** полосы частот (`EqualizerBand`), параметрический эквалайзер (`GraphicEqualizer`), регулятор громкости (`VolumeControl`), движок плавного перехода (`CrossfadeEngine`), эффекты реверберации (`ReverbEffect`), усиления баса (`BassBoostEffect`), коррекции тональности (`PitchShifter`), общая стойка эффектов (`AudioEffectsRack`).
- **Управление воспроизведением и очередь:** очередь воспроизведения (`PlaybackQueue`), алгоритм перемешивания (`ShuffleEngine`), контроллер повтора (`RepeatController`), системный движок вывода (`AudioEngine`), история прослушиваний (`PlaybackHistory`), закладки времени (`Bookmark`), контроллер позиции (`PlaybackPosition`).
- **Тексты песен, теги и визуализация:** строки синхронизированного текста (`LyricLine`), окно отображения караоке (`LyricsViewer`), анализатор спектра (`SpectrumAnalyzer`), визуализатор звуковых волн (`AudioVisualizer`), обложки альбомов (`AlbumArt`), редактор тегов (`ID3TagEditor`), акустический отпечаток (`AudioFingerprint`).
- **Стриминг, устройства и пользователи:** интернет-радиостанции (`OnlineRadioStation`), кэширующий загрузчик (`StreamDownloader`), аудиоустройства (`AudioOutputDevice`), диспетчер устройств (`DeviceManager`), профиль пользователя (`UserProfile`), тарифная подписка (`SubscriptionPlan`), таймер сна (`SleepTimer`), статистика прослушиваний (`PlaybackStatistics`).
- **Подкасты, расширения и интеграция:** эпизоды подкастов (`PodcastEpisode`), шоу подкастов (`PodcastShow`), запись звука (`AudioRecorder`), менеджер расширений (`PluginManager`), музыкальный проигрыватель (`MusicPlayer`).

---

## 2. Структура проекта

```text
lab3/
├── include/                   # Объявление классов (.h)
│   ├── MusicPlayerException.h				# Базовое исключение домена
│   ├── TrackNotFoundException.h			# Исключение: трек не найден
│   ├── PlaylistNotFoundException.h			# Исключение: плейлист не найден
│   ├── CorruptedAudioFileException.h		# Исключение: повреждённый аудиофайл
│   ├── UnsupportedAudioFormatException.h	# Исключение: неподдерживаемый формат
│   ├── DeviceAudioOutputException.h		# Исключение: сбой устройства вывода
│   ├── PlaybackBufferUnderflowException.h	# Исключение: опустошение аудиобуфера
│   ├── InvalidEqualizerBandException.h		# Исключение: некорректная полоса эквалайзера
│   ├── PlaylistFullException.h				# Исключение: переполнение плейлиста
│   ├── UnauthorizedPlaybackException.h		# Исключение: отказ в доступе / нет подписки
│   ├── StreamingNetworkException.h			# Исключение: сетевая ошибка стриминга
│   ├── LicenseExpiredException.h			# Исключение: истечение лицензии
│   ├── AudioMetadata.h          # Метаданные трека
│   ├── AudioSample.h            # Стереосэмпл звука
│   ├── AudioBuffer.h            # Циклический аудиобуфер
│   ├── AudioCodec.h             # Спецификация аудиокодека
│   ├── MP3Decoder.h             # Декодер MP3 фреймов
│   ├── FLACDecoder.h            # Декодер FLAC блоков
│   ├── WAVDecoder.h             # Декодер PCM WAV RIFF
│   ├── AudioStream.h            # Потоковый аудиоисточник
│   ├── AudioTrack.h             # Трек (аудиодорожка)
│   ├── Album.h                  # Музыкальный альбом
│   ├── Artist.h                 # Исполнитель
│   ├── Playlist.h               # Пользовательский плейлист
│   ├── SmartPlaylist.h          # Умный фильтрующий плейлист
│   ├── MusicFolder.h            # Папка сканирования файлов
│   ├── MusicLibrary.h           # Центральная медиатека
│   ├── EqualizerBand.h          # Полоса эквалайзера
│   ├── GraphicEqualizer.h       # 10-полосный эквалайзер
│   ├── VolumeControl.h          # Регулятор громкости
│   ├── CrossfadeEngine.h        # Плавный переход между треками
│   ├── ReverbEffect.h           # Эффект реверберации
│   ├── BassBoostEffect.h        # Эффект усиления баса
│   ├── PitchShifter.h           # Регулятор тональности звука
│   ├── AudioEffectsRack.h       # Стойка аудиоэффектов
│   ├── PlaybackQueue.h          # Очередь воспроизведения
│   ├── ShuffleEngine.h          # Алгоритм перемешивания
│   ├── RepeatController.h       # Контроллер режимов повтора
│   ├── AudioEngine.h            # Движок рендеринга звука
│   ├── PlaybackHistory.h        # История прослушиваний
│   ├── Bookmark.h               # Временная закладка
│   ├── PlaybackPosition.h       # Текущая позиция воспроизведения
│   ├── LyricLine.h              # Строка синхронизированного текста
│   ├── LyricsViewer.h           # Компонент отображения текста и караоке
│   ├── SpectrumAnalyzer.h       # Анализатор частотного спектра
│   ├── AudioVisualizer.h        # Визуализатор звуковых волн
│   ├── AlbumArt.h               # Обложка альбома (.jpeg, .png)
│   ├── ID3TagEditor.h           # Редактор ID3-тегов треков
│   ├── AudioFingerprint.h       # Акустический отпечаток трека
│   ├── OnlineRadioStation.h     # Интернет-радиостанция
│   ├── StreamDownloader.h       # Загрузчик и кэшировщик потоков
│   ├── AudioOutputDevice.h      # Физическое или виртуальное аудиоустройство
│   ├── DeviceManager.h          # Менеджер устройств вывода
│   ├── UserProfile.h            # Профиль пользователя
│   ├── SubscriptionPlan.h       # Тарифный план и подписка
│   ├── SleepTimer.h             # Таймер автоматического выключения
│   ├── PlaybackStatistics.h     # Статистика и аналитика прослушиваний
│   ├── PodcastEpisode.h         # Эпизод подкаста
│   ├── PodcastShow.h            # Каталог подкаст-шоу
│   ├── AudioRecorder.h          # Компонент захвата и записи звука
│   ├── PluginManager.h          # Менеджер подключаемых расширений
│   └── MusicPlayer.h            # Музыкальный проигрыватель
├── src/                     # Реализация классов (.cpp)
│   ├── Album.cpp
│   ├── AlbumArt.cpp
│   ├── Artist.cpp
│   ├── AudioBuffer.cpp
│   ├── AudioCodec.cpp
│   ├── AudioEffectsRack.cpp
│   ├── AudioEngine.cpp
│   ├── AudioFingerprint.cpp
│   ├── AudioMetadata.cpp
│   ├── AudioOutputDevice.cpp
│   ├── AudioRecorder.cpp
│   ├── AudioSample.cpp
│   ├── AudioStream.cpp
│   ├── AudioTrack.cpp
│   ├── AudioVisualizer.cpp
│   ├── BassBoostEffect.cpp
│   ├── Bookmark.cpp
│   ├── CorruptedAudioFileException.cpp
│   ├── CrossfadeEngine.cpp
│   ├── DeviceAudioOutputException.cpp
│   ├── DeviceManager.cpp
│   ├── EqualizerBand.cpp
│   ├── FLACDecoder.cpp
│   ├── GraphicEqualizer.cpp
│   ├── ID3TagEditor.cpp
│   ├── InvalidEqualizerBandException.cpp
│   ├── LicenseExpiredException.cpp
│   ├── LyricLine.cpp
│   ├── LyricsViewer.cpp
│   ├── MP3Decoder.cpp
│   ├── MusicFolder.cpp
│   ├── MusicLibrary.cpp
│   ├── MusicPlayer.cpp
│   ├── MusicPlayerException.cpp
│   ├── OnlineRadioStation.cpp
│   ├── PitchShifter.cpp
│   ├── PlaybackBufferUnderflowException.cpp
│   ├── PlaybackHistory.cpp
│   ├── PlaybackPosition.cpp
│   ├── PlaybackQueue.cpp
│   ├── PlaybackStatistics.cpp
│   ├── Playlist.cpp
│   ├── PlaylistFullException.cpp
│   ├── PlaylistNotFoundException.cpp
│   ├── PluginManager.cpp
│   ├── PodcastEpisode.cpp
│   ├── PodcastShow.cpp
│   ├── RepeatController.cpp
│   ├── ReverbEffect.cpp
│   ├── ShuffleEngine.cpp
│   ├── SleepTimer.cpp
│   ├── SmartPlaylist.cpp
│   ├── SpectrumAnalyzer.cpp
│   ├── StreamDownloader.cpp
│   ├── StreamingNetworkException.cpp
│   ├── SubscriptionPlan.cpp
│   ├── TrackNotFoundException.cpp
│   ├── UnauthorizedPlaybackException.cpp
│   ├── UnsupportedAudioFormatException.cpp
│   ├── UserProfile.cpp
│   ├── VolumeControl.cpp
│   └── WAVDecoder.cpp
├── app/                     # Консольный интерфейс пользователя (CLI)
│   └── main.cpp
├── tests/                   # Unit-тесты (GoogleTest)
│   ├── test_album.cpp
│   ├── test_album_art.cpp
│   ├── test_artist.cpp
│   ├── test_audio_buffer.cpp
│   ├── test_audio_codec.cpp
│   ├── test_audio_effects_rack.cpp
│   ├── test_audio_engine.cpp
│   ├── test_audio_fingerprint.cpp
│   ├── test_audio_metadata.cpp
│   ├── test_audio_output_device.cpp
│   ├── test_audio_recorder.cpp
│   ├── test_audio_sample.cpp
│   ├── test_audio_stream.cpp
│   ├── test_audio_track.cpp
│   ├── test_audio_visualizer.cpp
│   ├── test_bass_boost_effect.cpp
│   ├── test_bookmark.cpp
│   ├── test_crossfade_engine.cpp
│   ├── test_device_manager.cpp
│   ├── test_equalizer_band.cpp
│   ├── test_exceptions.cpp
│   ├── test_flac_decoder.cpp
│   ├── test_graphic_equalizer.cpp
│   ├── test_id3_tag_editor.cpp
│   ├── test_lyric_line.cpp
│   ├── test_lyrics_viewer.cpp
│   ├── test_mp3_decoder.cpp
│   ├── test_music_folder.cpp
│   ├── test_music_library.cpp
│   ├── test_music_player.cpp
│   ├── test_online_radio_station.cpp
│   ├── test_pitch_shifter.cpp
│   ├── test_playback_history.cpp
│   ├── test_playback_position.cpp
│   ├── test_playback_queue.cpp
│   ├── test_playback_statistics.cpp
│   ├── test_playlist.cpp
│   ├── test_plugin_manager.cpp
│   ├── test_podcast_episode.cpp
│   ├── test_podcast_show.cpp
│   ├── test_repeat_controller.cpp
│   ├── test_reverb_effect.cpp
│   ├── test_shuffle_engine.cpp
│   ├── test_sleep_timer.cpp
│   ├── test_smart_playlist.cpp
│   ├── test_spectrum_analyzer.cpp
│   ├── test_stream_downloader.cpp
│   ├── test_subscription_plan.cpp
│   ├── test_user_profile.cpp
│   ├── test_volume_control.cpp
│   └── test_wav_decoder.cpp
├── CMakeLists.txt           # Сборка проекта через CMake
├── Doxyfile                 # Конфигурация документации Doxygen
└── README.md                # Документация проекта
```

---

## 3. Таблица классов

| № | Класс | Поля | Методы | Ассоциации (связанные классы) |
|---|---|---|---|---|
| — | Exceptions | 1 | 12 | MusicPlayerException, TrackNotFoundException, PlaylistNotFoundException и др. |
| 1 | AudioMetadata | 6 | 7 | — |
| 2 | AudioSample | 4 | 5 | — |
| 3 | AudioBuffer | 6 | 5 | AudioSample |
| 4 | AudioCodec | 5 | 6 | — |
| 5 | MP3Decoder | 4 | 5 | — |
| 6 | FLACDecoder | 4 | 5 | — |
| 7 | WAVDecoder | 4 | 5 | — |
| 8 | AudioStream | 5 | 6 | AudioBuffer |
| 9 | AudioTrack | 6 | 6 | AudioMetadata, AudioCodec |
| 10 | Album | 4 | 6 | AudioTrack |
| 11 | Artist | 4 | 6 | Album |
| 12 | Playlist | 4 | 7 | AudioTrack |
| 13 | SmartPlaylist | 4 | 7 | Playlist, AudioTrack |
| 14 | MusicFolder | 4 | 6 | — |
| 15 | MusicLibrary | 5 | 7 | AudioTrack, Album, Artist, Playlist |
| 16 | EqualizerBand | 4 | 5 | — |
| 17 | GraphicEqualizer | 4 | 7 | EqualizerBand |
| 18 | VolumeControl | 4 | 6 | — |
| 19 | CrossfadeEngine | 3 | 5 | AudioSample |
| 20 | ReverbEffect | 4 | 5 | AudioSample |
| 21 | BassBoostEffect | 3 | 4 | AudioSample |
| 22 | PitchShifter | 4 | 5 | AudioSample |
| 23 | AudioEffectsRack | 5 | 7 | GraphicEqualizer, ReverbEffect, BassBoostEffect, PitchShifter |
| 24 | PlaybackQueue | 4 | 7 | AudioTrack |
| 25 | ShuffleEngine | 3 | 6 | — |
| 26 | RepeatController | 3 | 6 | — |
| 27 | AudioEngine | 4 | 6 | AudioBuffer, AudioSample |
| 28 | PlaybackHistory | 3 | 6 | AudioTrack |
| 29 | Bookmark | 4 | 4 | — |
| 30 | PlaybackPosition | 4 | 6 | — |
| 31 | LyricLine | 3 | 7 | — |
| 32 | LyricsViewer | 3 | 9 | LyricLine |
| 33 | SpectrumAnalyzer | 4 | 9 | AudioBuffer |
| 34 | AudioVisualizer | 4 | 9 | AudioSample |
| 35 | AlbumArt | 4 | 8 | — |
| 36 | ID3TagEditor | 4 | 8 | AudioTrack |
| 37 | AudioFingerprint | 4 | 8 | AudioBuffer |
| 38 | OnlineRadioStation | 5 | 9 | — |
| 39 | StreamDownloader | 5 | 9 | — |
| 40 | AudioOutputDevice | 5 | 9 | — |
| 41 | DeviceManager | 3 | 9 | AudioOutputDevice |
| 42 | UserProfile | 4 | 9 | — |
| 43 | SubscriptionPlan | 4 | 6 | — |
| 44 | SleepTimer | 5 | 8 | — |
| 45 | PlaybackStatistics | 4 | 8 | — |
| 46 | PodcastEpisode | 5 | 8 | — |
| 47 | PodcastShow | 4 | 8 | PodcastEpisode |
| 48 | AudioRecorder | 4 | 8 | AudioBuffer |
| 49 | PluginManager | 3 | 8 | — |
| 50 | MusicPlayer | 15 | 25 | MusicLibrary, PlaybackQueue, AudioEngine, AudioEffectsRack, VolumeControl, PlaybackPosition, RepeatController, ShuffleEngine, PlaybackHistory, DeviceManager, UserProfile, SubscriptionPlan, SleepTimer |

---

## 4. Исключения (12)

- MusicPlayerException
- TrackNotFoundException
- PlaylistNotFoundException
- CorruptedAudioFileException
- UnsupportedAudioFormatException
- DeviceAudioOutputException
- PlaybackBufferUnderflowException
- InvalidEqualizerBandException
- PlaylistFullException
- UnauthorizedPlaybackException
- StreamingNetworkException
- LicenseExpiredException

---

## 5. Итоговая статистика проекта

| Показатель | Значение |
|---|---|
| Поля | 217 |
| Поведения | 342 |
| Ассоциации | 38 |
| Исключения | 12 |

---

## 6. Сборка и запуск

Проект собирается с использованием **CMake** ($\ge 3.14$) и компилятора с поддержкой C++17. Библиотека GoogleTest загружается автоматически.

### Сборка через CMake

```bash
cmake -S lab3 -B lab3/build
cmake --build lab3/build --config Debug
```

### Запуск консольного интерфейса (CLI)

```bash
# Windows
.\lab3\build\Debug\Lab3_Run.exe

# Linux
./lab3/build/Lab3_Run
```

### Запуск unit-тестов (GoogleTest)

**Способ 1: Прямой запуск**

```bash
# Windows
.\lab3\build\Debug\Tests_Run.exe

# Linux
./lab3/build/Tests_Run
```

**Способ 2: Через CTest**

```bash
cd lab3/build
ctest --output-on-failure
```

---

## 7. Документация

Для генерации HTML-документации нужно перейти в папку `lab3` и выполнить:

```bash
doxygen Doxyfile
```

Затем открыть файл `docs/html/index.html` в браузере.

---

## 8. CI/CD Pipeline

При каждом пуше, а также при Pull Request автоматически запускается GitHub Actions workflow (`.github/workflows/lab3_ci.yml`), который выполняет:
1. Сборку проекта (CMake).
2. Запуск всех Unit-тестов (`Tests_Run`).
3. Статический анализ кода линтером `cppcheck`.
4. Публикацию исполняемого артефакта в Releases (при пуше тега версии).