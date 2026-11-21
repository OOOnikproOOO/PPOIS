# Лабораторная работа №2 — Крупный ООП-проект

**Студент:** Момот Никита Дмитриевич  
**Группа:** 521702  
**Предметная область:** Компьютер

---

## 1. Описание предметной области

Проект моделирует архитектуру современного персонального компьютера и его подсистем:
- **Вычислительные компоненты:** процессор (CPU), физические ядра (CPUCore), многоуровневая кэш-память (CPUCache), термоинтерфейс (ThermalPaste).
- **Подсистема оперативной памяти:** планки памяти (RAMStick), тайминги (RAMTiming), многоканальная подсистема (RAM).
- **Подсистема постоянной памяти и хранилища:** твердотельные накопители (SSD), магнитные диски (HDD), RAID-контроллер (StorageController).
- **Графическая подсистема:** графический процессор (GPUCore), видеопамять (VRAM), видеовыходы (VideoPort), дискретная видеокарта (GraphicsCard), монитор (Display).
- **Аудиоподсистема:** цифро-аналоговый преобразователь (AudioDAC), цифровой процессор сигналов (AudioDSP), аудиоразъемы (AudioJack), звуковая карта (SoundCard), акустическая система (SpeakerSystem).
- **Материнская плата и шины расширения:** стабилизатор напряжения (VRM), чипсет (Chipset), разъемы расширения (PCIeSlot), системная плата (Motherboard).
- **Подсистема электропитания:** шины постоянного тока (PowerRail), блок питания (PowerSupply).
- **Подсистема охлаждения и корпус:** вентиляторы охлаждения (CoolingFan), водяное охлаждение (LiquidCooler), комплексная система охлаждения (CoolingSystem), компьютерный корпус (ComputerCase).
- **Системное ПО, загрузка и время:** конфигурация прошивки (BIOSSettings), загрузчик ОС (Bootloader), системные часы и аптайм (SystemClock).
- **Операционная система и файловая система:** файлы (FileEntry), каталоги (DirectoryNode), файловая система (FileSystem), процессы (OSProcess), планировщик задач (ProcessScheduler), драйверы устройств (DeviceDriver), операционная система (OperatingSystem).
- **Сетевая подсистема и безопасность:** сетевые пакеты (NetworkPacket), сетевой адаптер (NetworkAdapter), межсетевой экран (SecurityFirewall).
- **Периферийные устройства ввода и порты:** клавиатура (Keyboard), мышь (Mouse), порты внешней шины (USBPort).
- **Управление доступом, мониторинг и бенчмарки:** учетная запись пользователя (UserAccount), аппаратная диагностика (SystemDiagnostics), синтетический бенчмарк (SystemBenchmark).
- **Интегрированная рабочая станция:** комплексная сборка компьютера (Computer), связывающая все подсистемы в единый функциональный организм.

---

## 2. Структура проекта

```text
lab2/
├── include/                     # Заголовочные файлы классов (.h)
│   ├── ComputerException.h            # Базовое исключение предметной области
│   ├── DeviceNotFoundException.h      # Исключение: устройство/элемент не найдены
│   ├── IncompatibleSocketException.h  # Исключение: несовместимость сокета CPU
│   ├── IncompatibleMemoryException.h  # Исключение: несовместимость памяти RAM
│   ├── ThermalThrottlingException.h   # Исключение: троттлинг от перегрева
│   ├── OverheatingException.h         # Исключение: критический перегрев
│   ├── PowerSupplyOverloadException.h # Исключение: перегрузка блока питания
│   ├── VoltageInstabilityException.h  # Исключение: нестабильность напряжения
│   ├── StorageOutOfSpaceException.h   # Исключение: нехватка места на носителе
│   ├── StorageBadSectorException.h    # Исключение: сбойный сектор накопителя
│   ├── MemoryAllocationException.h    # Исключение: ошибка выделения памяти
│   ├── POSTFailureException.h         # Исключение: сбой самотестирования POST
│   ├── CPUCache.h               # Кэш-память процессора
│   ├── CPUCore.h                # Физическое ядро процессора
│   ├── CPU.h                    # Центральный процессор
│   ├── RAMTiming.h              # Тайминги оперативной памяти
│   ├── RAMStick.h               # Планка оперативной памяти
│   ├── RAM.h                    # Подсистема оперативной памяти
│   ├── SSD.h                    # Твердотельный накопитель
│   ├── HDD.h                    # Жесткий диск
│   ├── StorageController.h      # Дисковый RAID-контроллер
│   ├── ThermalPaste.h           # Термоинтерфейс
│   ├── GPUCore.h                # Графический процессор
│   ├── VRAM.h                   # Видеопамять
│   ├── VideoPort.h              # Видеовыходы
│   ├── GraphicsCard.h           # Дискретная видеокарта
│   ├── AudioDAC.h               # Аудио ЦАП
│   ├── AudioDSP.h               # Цифровой процессор звуковых эффектов
│   ├── AudioJack.h              # Аналоговые аудиоразъемы
│   ├── SoundCard.h              # Звуковая карта
│   ├── Display.h                # Монитор
│   ├── SpeakerSystem.h          # Акустическая система
│   ├── VRM.h                    # Стабилизатор напряжения
│   ├── Chipset.h                # Чипсет материнской платы
│   ├── PCIeSlot.h               # Разъем PCI Express
│   ├── Motherboard.h            # Системная материнская плата
│   ├── PowerRail.h              # Линия/шина питания постоянного тока
│   ├── PowerSupply.h            # Блок питания
│   ├── CoolingFan.h             # Вентилятор охлаждения с PWM
│   ├── LiquidCooler.h           # Водяное охлаждение
│   ├── CoolingSystem.h          # Комплексная система терморегуляции
│   ├── ComputerCase.h           # Компьютерный корпус
│   ├── BIOSSettings.h           # Настройки прошивки BIOS/UEFI
│   ├── Bootloader.h             # Системный загрузчик ОС
│   ├── SystemClock.h            # Часы реального времени и счетчик аптайма
│   ├── FileEntry.h              # Файл с текстовыми данными и правами доступа
│   ├── DirectoryNode.h          # Каталог иерархии файловой системы
│   ├── FileSystem.h             # Файловая система
│   ├── OSProcess.h              # Процесс операционной системы
│   ├── ProcessScheduler.h       # Планировщик задач и процессов ОС
│   ├── DeviceDriver.h           # Драйвер аппаратного устройства
│   ├── OperatingSystem.h        # Операционная система
│   ├── NetworkPacket.h          # Сетевой IP-пакет данных
│   ├── NetworkAdapter.h         # Сетевой адаптер
│   ├── Keyboard.h               # Клавиатура
│   ├── Mouse.h                  # Мышь
│   ├── USBPort.h                # Порт внешней шины USB
│   ├── SecurityFirewall.h       # Межсетевой экран
│   ├── UserAccount.h            # Учетная запись пользователя
│   ├── SystemBenchmark.h        # Комплексный тест производительности
│   ├── SystemDiagnostics.h      # Аппаратный монитор температур и питания (диагностика)
│   └── Computer.h               # Итоговая интеграция всей сборки компьютера
├── src/                   # Реализация логики классов (.cpp)
│   ├── ComputerException.cpp
│   ├── DeviceNotFoundException.cpp
│   ├── IncompatibleSocketException.cpp
│   ├── IncompatibleMemoryException.cpp
│   ├── ThermalThrottlingException.cpp
│   ├── OverheatingException.cpp
│   ├── PowerSupplyOverloadException.cpp
│   ├── VoltageInstabilityException.cpp
│   ├── StorageOutOfSpaceException.cpp
│   ├── StorageBadSectorException.cpp
│   ├── MemoryAllocationException.cpp
│   ├── POSTFailureException.cpp
│   ├── CPUCache.cpp
│   ├── CPUCore.cpp
│   ├── CPU.cpp
│   ├── RAMTiming.cpp
│   ├── RAMStick.cpp
│   ├── RAM.cpp
│   ├── SSD.cpp
│   ├── HDD.cpp
│   ├── StorageController.cpp
│   ├── ThermalPaste.cpp
│   ├── GPUCore.cpp
│   ├── VRAM.cpp
│   ├── VideoPort.cpp
│   ├── GraphicsCard.cpp
│   ├── AudioDAC.cpp
│   ├── AudioDSP.cpp
│   ├── AudioJack.cpp
│   ├── SoundCard.cpp
│   ├── Display.cpp
│   ├── SpeakerSystem.cpp
│   ├── VRM.cpp
│   ├── Chipset.cpp
│   ├── PCIeSlot.cpp
│   ├── Motherboard.cpp
│   ├── PowerRail.cpp
│   ├── PowerSupply.cpp
│   ├── CoolingFan.cpp
│   ├── LiquidCooler.cpp
│   ├── CoolingSystem.cpp
│   ├── ComputerCase.cpp
│   ├── BIOSSettings.cpp
│   ├── Bootloader.cpp
│   ├── SystemClock.cpp
│   ├── FileEntry.cpp
│   ├── DirectoryNode.cpp
│   ├── FileSystem.cpp
│   ├── OSProcess.cpp
│   ├── ProcessScheduler.cpp
│   ├── DeviceDriver.cpp
│   ├── OperatingSystem.cpp
│   ├── NetworkPacket.cpp
│   ├── NetworkAdapter.cpp
│   ├── Keyboard.cpp
│   ├── Mouse.cpp
│   ├── USBPort.cpp
│   ├── SecurityFirewall.cpp
│   ├── UserAccount.cpp
│   ├── SystemBenchmark.cpp
│   ├── SystemDiagnostics.cpp
│   └── Computer.cpp
├── app/                         # Консольный интерфейс пользователя (CLI)
│   └── main.cpp
├── tests/                       # Unit-тесты для каждого класса (GoogleTest)
│   ├── test_audio_dac.cpp
│   ├── test_audio_dsp.cpp
│   ├── test_audio_jack.cpp
│   ├── test_bios_settings.cpp
│   ├── test_bootloader.cpp
│   ├── test_chipset.cpp
│   ├── test_computer.cpp
│   ├── test_computer_case.cpp
│   ├── test_cooling_fan.cpp
│   ├── test_cooling_system.cpp
│   ├── test_cpu.cpp
│   ├── test_cpu_cache.cpp
│   ├── test_cpu_core.cpp
│   ├── test_device_driver.cpp
│   ├── test_directory_node.cpp
│   ├── test_display.cpp
│   ├── test_exceptions.cpp
│   ├── test_file_entry.cpp
│   ├── test_file_system.cpp
│   ├── test_gpu_core.cpp
│   ├── test_graphics_card.cpp
│   ├── test_hdd.cpp
│   ├── test_keyboard.cpp
│   ├── test_liquid_cooler.cpp
│   ├── test_motherboard.cpp
│   ├── test_mouse.cpp
│   ├── test_network_adapter.cpp
│   ├── test_network_packet.cpp
│   ├── test_operating_system.cpp
│   ├── test_os_process.cpp
│   ├── test_pcie_slot.cpp
│   ├── test_power_rail.cpp
│   ├── test_power_supply.cpp
│   ├── test_process_scheduler.cpp
│   ├── test_ram.cpp
│   ├── test_ram_stick.cpp
│   ├── test_ram_timing.cpp
│   ├── test_security_firewall.cpp
│   ├── test_sound_card.cpp
│   ├── test_speaker_system.cpp
│   ├── test_ssd.cpp
│   ├── test_storage_controller.cpp
│   ├── test_system_benchmark.cpp
│   ├── test_system_clock.cpp
│   ├── test_system_diagnostics.cpp
│   ├── test_thermal_paste.cpp
│   ├── test_usb_port.cpp
│   ├── test_user_account.cpp
│   ├── test_video_port.cpp
│   ├── test_vram.cpp
│   └── test_vrm.cpp
├── CMakeLists.txt               # Файл конфигурации сборки CMake
├── Doxyfile                     # Конфигурация Doxygen
└── README.md                    # Документация проекта
```

---

## 3. Таблица классов

| № | Класс | Поля | Методы | Ассоциации (связанные классы) |
|---|---|---|---|---|
| — | Exceptions | 1 | 12 | ComputerException, ThermalThrottlingException, MemoryAllocationException и др. |
| 1 | CPUCache | 6 | 6 | — |
| 2 | CPUCore | 6 | 6 | — |
| 3 | CPU | 6 | 7 | CPUCore, CPUCache |
| 4 | RAMTiming | 5 | 5 | — |
| 5 | RAMStick | 7 | 6 | RAMTiming |
| 6 | RAM | 5 | 6 | RAMStick |
| 7 | SSD | 7 | 6 | — |
| 8 | HDD | 7 | 6 | — |
| 9 | StorageController | 5 | 5 | SSD, HDD |
| 10 | ThermalPaste | 6 | 6 | — |
| 11 | GPUCore | 4 | 5 | — |
| 12 | VRAM | 4 | 5 | — |
| 13 | VideoPort | 4 | 4 | — |
| 14 | GraphicsCard | 5 | 6 | GPUCore, VRAM, VideoPort |
| 15 | AudioDAC | 4 | 5 | — |
| 16 | AudioDSP | 4 | 5 | — |
| 17 | AudioJack | 4 | 4 | — |
| 18 | SoundCard | 5 | 6 | AudioDAC, AudioDSP, AudioJack |
| 19 | Display | 5 | 6 | — |
| 20 | SpeakerSystem | 4 | 5 | — |
| 21 | VRM | 4 | 5 | — |
| 22 | Chipset | 4 | 4 | — |
| 23 | PCIeSlot | 5 | 4 | — |
| 24 | Motherboard | 6 | 6 | VRM, Chipset, PCIeSlot |
| 25 | PowerRail | 4 | 4 | — |
| 26 | PowerSupply | 5 | 6 | PowerRail |
| 27 | CoolingFan | 5 | 4 | — |
| 28 | LiquidCooler | 5 | 4 | — |
| 29 | CoolingSystem | 4 | 4 | LiquidCooler, CoolingFan |
| 30 | ComputerCase | 5 | 5 | — |
| 31 | BIOSSettings | 4 | 6 | — |
| 32 | Bootloader | 4 | 4 | BIOSSettings |
| 33 | SystemClock | 3 | 5 | — |
| 34 | FileEntry | 4 | 5 | — |
| 35 | DirectoryNode | 3 | 7 | FileEntry |
| 36 | FileSystem | 3 | 9 | DirectoryNode |
| 37 | OSProcess | 4 | 5 | — |
| 38 | ProcessScheduler | 3 | 5 | OSProcess |
| 39 | DeviceDriver | 4 | 4 | — |
| 40 | OperatingSystem | 7 | 5 | Bootloader, FileSystem, ProcessScheduler, SystemClock, DeviceDriver |
| 41 | NetworkPacket | 5 | 5 | — |
| 42 | NetworkAdapter | 6 | 6 | NetworkPacket |
| 43 | Keyboard | 4 | 5 | — |
| 44 | Mouse | 5 | 5 | — |
| 45 | USBPort | 4 | 4 | — |
| 46 | SecurityFirewall | 4 | 5 | NetworkPacket |
| 47 | UserAccount | 5 | 5 | — |
| 48 | SystemBenchmark | 4 | 5 | — |
| 49 | SystemDiagnostics | 4 | 5 | — |
| 50 | Computer | 10 | 5 | Motherboard, CPU, RAM, GraphicsCard, PowerSupply, OperatingSystem, NetworkAdapter, SystemDiagnostics |

---

## 4. Исключения (12)

- ComputerException
- DeviceNotFoundException
- IncompatibleSocketException
- IncompatibleMemoryException
- ThermalThrottlingException
- OverheatingException
- PowerSupplyOverloadException
- VoltageInstabilityException
- StorageOutOfSpaceException
- StorageBadSectorException
- MemoryAllocationException
- POSTFailureException

---

## 5. Итоговая статистика проекта

| Показатель | Значение |
|---|---|
| Поля | 239 |
| Поведения | 193 |
| Ассоциации | 37 |
| Исключения | 12 |

---

## 6. Сборка и запуск

Проект собирается с использованием **CMake** ($\ge 3.14$) и компилятора с поддержкой C++17. Библиотека GoogleTest загружается автоматически.

### Сборка через CMake

```bash
cmake -S lab2 -B lab2/build
cmake --build lab2/build --config Debug
```

### Запуск консольного меню (CLI)

```bash
# Windows
.\lab2\build\Debug\Lab2_Run.exe

# Linux
./lab2/build/Lab2_Run
```

### Запуск unit-тестов (GoogleTest)

**Способ 1: Прямой запуск**

```bash
# Windows
.\lab2\build\Debug\Tests_Run.exe

# Linux
./lab2/build/Tests_Run
```

**Способ 2: Через CTest**

```bash
cd lab2/build
ctest --output-on-failure
```

---

## 7. Документация

Для генерации HTML-документации нужно перейти в папку `lab2` и выполнить:

```bash
doxygen Doxyfile
```

Затем открыть файл `docs/html/index.html` в браузере.

---

## 8. CI/CD Pipeline

При каждом пуше, а также при Pull Request автоматически запускается GitHub Actions workflow (`.github/workflows/lab2_ci.yml`), который выполняет:
1. Сборку проекта (CMake).
2. Запуск всех Unit-тестов (`Tests_Run`).
3. Статический анализ кода линтером `cppcheck`.
4. Публикацию исполняемого артефакта в Releases (при пуше тега версии).