# Лабораторная работа №2 — Крупный ООП-проект

**Студент:** Момот Никита Дмитриевич  
**Группа:** 521702  
**Предметная область:** Компьютер

---

## 1. Описание предметной области

Проект моделирует архитектуру современного персонального компьютера и его подсистем:
- **Вычислительные компоненты:** процессор (CPU), физические ядра (CPUCore), многоуровневая кэш-память (CPUCache), термоинтерфейс (ThermalPaste).
- **Подсистема оперативной памяти:** модули памяти (RAMStick), тайминги (RAMTiming), многоканальная подсистема (RAM).
- **Подсистема постоянной памяти и хранилища:** твердотельные накопители (SSD), магнитные диски (HDD), RAID-контроллер (StorageController).
- **Последующие модули:** графическая подсистема (GPU, VRAM, VideoPort), аудиоподсистема (SoundCard, DAC, DSP), материнская плата, подсистема питания и охлаждения, сетевые интерфейсы, периферия, BIOS/UEFI, POST-тестирование и сборщик ПК.

---

## 2. Структура проекта

```text
lab2/
├── include/                     # Заголовочные файлы классов (.h)
│   ├── Exceptions.h             # 12 собственных классов исключений
│   ├── CPUCache.h               # Кэш-память процессора (L1, L2, L3)
│   ├── CPUCore.h                # Физическое ядро процессора
│   ├── CPU.h                    # Центральный процессор
│   ├── RAMTiming.h              # Тайминги оперативной памяти
│   ├── RAMStick.h               # Модуль оперативной памяти (DIMM)
│   ├── RAM.h                    # Подсистема оперативной памяти
│   ├── SSD.h                    # Твердотельный накопитель
│   ├── HDD.h                    # Жесткий диск
│   ├── StorageController.h      # Дисковый RAID-контроллер
│   └── ThermalPaste.h           # Термоинтерфейс
├── src/                         # Реализация логики классов (.cpp)
│   ├── CPUCache.cpp
│   ├── CPUCore.cpp
│   ├── CPU.cpp
│   ├── RAMTiming.cpp
│   ├── RAMStick.cpp
│   ├── RAM.cpp
│   ├── SSD.cpp
│   ├── HDD.cpp
│   ├── StorageController.cpp
│   └── ThermalPaste.cpp
├── app/                         # Консольный интерфейс пользователя (CLI)
│   └── main.cpp
├── tests/                       # Unit-тесты для каждого класса (GoogleTest)
│   ├── test_exceptions.cpp
│   ├── test_cpu_cache.cpp
│   ├── test_cpu_core.cpp
│   ├── test_cpu.cpp
│   ├── test_ram_timing.cpp
│   ├── test_ram_stick.cpp
│   ├── test_ram.cpp
│   ├── test_ssd.cpp
│   ├── test_hdd.cpp
│   ├── test_storage_controller.cpp
│   └── test_thermal_paste.cpp
├── CMakeLists.txt               # Сценарий сборки CMake
├── Doxyfile                     # Конфигурация Doxygen
└── README.md                    # Документация проекта
```

---

## 3. Таблица классов (Модуль 1: Первые 10 классов)

| Класс | Поля | Методы | Ассоциации (связанные классы) |
|---|---|---|---|
| Exceptions | 1 | 12 | ComputerException, ThermalThrottlingException, MemoryAllocationException и др. |
| CPUCache | 6 | 6 | — |
| CPUCore | 6 | 6 | — |
| CPU | 6 | 6 | CPUCore, CPUCache |
| RAMTiming | 5 | 5 | — |
| RAMStick | 7 | 6 | RAMTiming |
| RAM | 4 | 5 | RAMStick |
| SSD | 7 | 6 | — |
| HDD | 7 | 6 | — |
| StorageController | 5 | 5 | SSD, HDD |
| ThermalPaste | 6 | 6 | — |

---

## 4. Собственные классы исключений (12)

1. `ComputerException` — базовое исключение предметной области.
2. `DeviceNotFoundException` — обращение к отсутствующему или неподключенному устройству.
3. `IncompatibleSocketException` — несовместимость сокета процессора и материнской платы.
4. `IncompatibleMemoryException` — несовместимость типа/поколения оперативной памяти.
5. `ThermalThrottlingException` — критический перегрев, вызывающий сброс рабочих частот.
6. `OverheatingException` — аварийный перегрев, превышающий TJMax.
7. `PowerSupplyOverloadException` — превышение допустимой мощности блока питания.
8. `VoltageInstabilityException` — отклонение напряжения на шинах питания от стандарта ATX.
9. `StorageOutOfSpaceException` — попытка записи при отсутствии свободного места на накопителе.
10. `StorageBadSectorException` — обнаружение поврежденного сектора или ячейки памяти.
11. `MemoryAllocationException` — ошибка аллокации требуемого объема RAM.
12. `POSTFailureException` — сбой процедуры самотестирования при запуске компьютера.

---

## 5. Статистика первого модуля (10 классов)

| Показатель | Значение в Модуле 1 | Требование ко всей лабе |
|---|---|---|
| Классы предметной области | 10 (+ 12 классов исключений) | $\ge 50$ |
| Поля суммарно | 59 полей | $\ge 150$ |
| Содержательные методы-поведения | 57 поведений | $\ge 100$ |
| Ассоциации между классами | 6 ассоциаций | $\ge 30$ |
| Собственные исключения | 12 исключений | $\ge 12$ ✅ |
| Модульные тесты | 54 теста (в 11 файлах) | $\ge 90\%$ покрытие ✅ |

---

## 6. Сборка и запуск

### Сборка через CMake (без IDE)

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

```bash
# Windows
.\lab2\build\Debug\Tests_Run.exe

# Linux
./lab2/build/Tests_Run
```
