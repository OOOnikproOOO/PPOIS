# Лабораторная работа №3 — Крупный ООП-проект

**Студент:** Момот Никита Дмитриевич  
**Группа:** 521702  
**Предметная область:** Приложение музыкального проигрывателя (Music Player Application)

---

## 1. Описание предметной области

Проект моделирует архитектуру современного кроссплатформенного музыкального проигрывателя:
- **Аудиоформаты, кодеки и декодеры:** структуры сэмплов (AudioSample), циклический буфер (AudioBuffer), спецификации кодеков (AudioCodec), декодеры форматов (MP3Decoder, FLACDecoder, WAVDecoder), потоковые источники (AudioStream).
- **Музыкальный контент и медиатека:** метаданные (AudioMetadata), аудиодорожки (AudioTrack), альбомы (Album), исполнители (Artist), пользовательские плейлисты (Playlist), умные плейлисты (SmartPlaylist), папки локального сканирования (MusicFolder), центральная медиатека (MusicLibrary).
- **Звуковая обработка и эффекты:** полосы частот (EqualizerBand), параметрический эквалайзер (GraphicEqualizer), регулятор громкости (VolumeControl), движок плавного перехода (CrossfadeEngine), эффекты реверберации (ReverbEffect), усиления баса (BassBoostEffect), коррекции тональности (PitchShifter), общая стойка эффектов (AudioEffectsRack).
- **Управление воспроизведением и очередь:** очередь воспроизведения (PlaybackQueue), алгоритм перемешивания (ShuffleEngine), контроллер повтора (RepeatController), системный движок вывода (AudioEngine), история прослушиваний (PlaybackHistory), закладки времени (Bookmark), контроллер позиции (PlaybackPosition).
- **Тексты песен, теги и визуализация:** строки синхронизированного текста (LyricLine), окно отображения караоке (LyricsViewer), анализатор спектра (SpectrumAnalyzer), визуализатор звуковых волн (AudioVisualizer), обложки альбомов (AlbumArt), редактор тегов (ID3TagEditor), акустический отпечаток (AudioFingerprint).
- **Стриминг, устройства и пользователи:** интернет-радиостанции (OnlineRadioStation), кэширующий загрузчик (StreamDownloader), аудиоустройства (AudioOutputDevice), диспетчер устройств (DeviceManager), профиль пользователя (UserProfile), тарифная подписка (SubscriptionPlan), таймер сна (SleepTimer), статистика прослушиваний (PlaybackStatistics).
- **Подкасты, расширения и интеграция:** эпизоды подкастов (PodcastEpisode), шоу подкастов (PodcastShow), запись звука (AudioRecorder), менеджер расширений (PluginManager), комплексный музыкальный проигрыватель (MusicPlayer).

---

## 2. Структура проекта

```text
lab3/
├── include/                     # Заголовочные файлы классов (.h)
│   ├── MusicPlayerException.h         # Базовое исключение домена
│   ├── TrackNotFoundException.h       # Исключение: трек не найден
│   ├── PlaylistNotFoundException.h    # Исключение: плейлист не найден
│   ├── CorruptedAudioFileException.h  # Исключение: повреждённый аудиофайл
│   ├── UnsupportedAudioFormatException.h # Исключение: неподдерживаемый формат
│   ├── DeviceAudioOutputException.h   # Исключение: сбой устройства вывода
│   ├── PlaybackBufferUnderflowException.h # Исключение: опустошение аудиобуфера
│   ├── InvalidEqualizerBandException.h# Исключение: некорректная полоса эквалайзера
│   ├── PlaylistFullException.h        # Исключение: переполнение плейлиста
│   ├── UnauthorizedPlaybackException.h# Исключение: отказ в доступе / нет подписки
│   ├── StreamingNetworkException.h    # Исключение: сетевая ошибка стриминга
│   ├── LicenseExpiredException.h      # Исключение: истечение лицензии DRM
│   ├── AudioMetadata.h          # Метаданные трека
│   ├── AudioSample.h            # Стереосэмпл звука
│   ├── AudioBuffer.h            # Циклический аудиобуфер
│   ├── AudioCodec.h             # Спецификация аудиокодека
│   ├── MP3Decoder.h             # Декодер MP3 фреймов
│   ├── FLACDecoder.h            # Декодер FLAC блоков
│   ├── WAVDecoder.h             # Декодер PCM WAV RIFF
│   ├── AudioStream.h            # Потоковый аудиоисточник
│   ├── AudioTrack.h             # Аудиодорожка / трек
│   ├── Album.h                  # Музыкальный альбом
│   ├── Artist.h                 # Исполнитель
│   ├── Playlist.h               # Пользовательский плейлист
│   ├── SmartPlaylist.h          # Умный фильтрующий плейлист
│   ├── MusicFolder.h            # Папка сканирования файлов
│   └── MusicLibrary.h           # Центральная медиатека
├── src/                         # Реализация методов (.cpp)
├── app/                         # Консольный интерфейс пользователя (CLI)
│   └── main.cpp
├── tests/                       # Unit-тесты GoogleTest
├── CMakeLists.txt               # Сборка проекта через CMake
├── Doxyfile                     # Конфигурация документации Doxygen
└── README.md                    # Документация проекта
```

---

## 3. Таблица классов (Этап 1: реализованные классы 1–15)

| № | Класс | Поля | Методы | Ассоциации (связанные классы) |
|---|---|---|---|---|
| — | Exceptions | 1 | 12 | MusicPlayerException, TrackNotFoundException, PlaylistNotFoundException и др. |
| 1 | AudioMetadata | 6 | 7 | — |
| 2 | AudioSample | 4 | 5 | — |
| 3 | AudioBuffer | 5 | 5 | AudioSample |
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

## 5. Статистика текущего этапа (Этап 1 из 3)

| Показатель | Значение (Этап 1) | Целевое значение |
|---|---|---|
| Классы предметной области | 15 | $\ge 50$ |
| Поля классов | 68 | $\ge 150$ |
| Уникальные поведения | 68 | $\ge 100$ |
| Ассоциации | 10 | $\ge 30$ |
| Классы исключений | 12 | $\ge 12$ |
| Unit-тесты | 61 (100% пройдены) | $>90\%$ покрытие |

---

## 6. Сборка и запуск

```bash
# Конфигурация и сборка
cmake -S lab3 -B lab3/build
cmake --build lab3/build --config Debug

# Запуск тестов
.\lab3\build\Debug\Tests_Run.exe

# Запуск программы
.\lab3\build\Debug\Lab3_Run.exe
```