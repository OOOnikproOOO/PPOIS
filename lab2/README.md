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
- **Графическая подсистема:** графический процессор (GPUCore), видеопамять (VRAM), видеовыходы (VideoPort), дискретная видеокарта (GraphicsCard), монитор (Display).
- **Аудиоподсистема:** цифро-аналоговый преобразователь (AudioDAC), цифровой процессор сигналов (AudioDSP), аудиоразъемы (AudioJack), звуковая карта (SoundCard), акустическая система (SpeakerSystem).
- **Материнская плата и шины расширения:** модуль регулятора напряжения (VRM), чипсет (Chipset), разъемы расширения (PCIeSlot), системная плата (Motherboard).
- **Подсистема электропитания:** шины постоянного тока (PowerRail), блок питания (PowerSupply).
- **Подсистема охлаждения и корпус:** вентиляторы охлаждения (CoolingFan), СЖО / водяное охлаждение (LiquidCooler), комплексная система охлаждения (CoolingSystem), компьютерный корпус (ComputerCase).

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
│   ├── ThermalPaste.h           # Термоинтерфейс
│   ├── GPUCore.h                # Графический процессор (GPU)
│   ├── VRAM.h                   # Видеопамять (GDDR6/GDDR6X)
│   ├── VideoPort.h              # Видеовыходы (HDMI, DisplayPort)
│   ├── GraphicsCard.h           # Дискретная видеокарта
│   ├── AudioDAC.h               # Аудио ЦАП
│   ├── AudioDSP.h               # Цифровой процессор звуковых эффектов
│   ├── AudioJack.h              # Аналоговые аудиоразъемы 3.5мм
│   ├── SoundCard.h              # Звуковая карта
│   ├── Display.h                # Монитор
│   ├── SpeakerSystem.h          # Акустическая система
│   ├── VRM.h                    # Модуль регулятора напряжения (VRM)
│   ├── Chipset.h                # Чипсет материнской платы (PCH)
│   ├── PCIeSlot.h               # Разъем PCI Express
│   ├── Motherboard.h            # Системная материнская плата
│   ├── PowerRail.h              # Линия/шина питания постоянного тока (+12V, +5V, +3.3V)
│   ├── PowerSupply.h            # Блок питания (PSU)
│   ├── CoolingFan.h             # Вентилятор охлаждения с PWM
│   ├── LiquidCooler.h           # СЖО (водяное охлаждение / AIO)
│   ├── CoolingSystem.h          # Комплексная система терморегуляции
│   └── ComputerCase.h           # Компьютерный корпус
├── src/                         # Реализация логики классов (.cpp)
├── app/                         # Консольный интерфейс пользователя (CLI)
│   └── main.cpp
├── tests/                       # Unit-тесты для каждого класса (GoogleTest)
├── CMakeLists.txt               # Сценарий сборки CMake
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

## 5. Статистика проекта

| Показатель | Реализовано на данный момент | Требование к проекту |
|---|---|---|
| Классы предметной области | 30 (+ 12 классов исключений) | $\ge 50$ |
| Поля суммарно | 150 полей | $\ge 150$ ✅ |
| Содержательные методы-поведения | 110 поведений (140 с учётом конструкторов) | $\ge 100$ ✅ |
| Ассоциации между классами | 18 ассоциаций | $\ge 30$ |
| Собственные исключения | 12 исключений | $\ge 12$ ✅ |
| Unit-тесты (GoogleTest) | 147 тестов (в 31 файле) | $\ge 90\%$ покрытие ✅ |

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

При каждом пуше в ветки `main`, `master`, `feature-lab2` (а также при Pull Request) автоматически запускается GitHub Actions workflow (`.github/workflows/lab2_ci.yml`), который выполняет:
1. Сборку проекта (CMake + Ninja).
2. Запуск всех unit-тестов (`Tests_Run`).
3. Проверку покрытия кода тестами через `gcovr` (не менее 90%).
4. Статический анализ кода линтером `cppcheck`.
5. Сборку Windows-релиза и публикацию архива `lab2-windows.zip` в разделе Releases (при пуше в основную ветку или тега `v2*`).
