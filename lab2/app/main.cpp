/**
 * @file main.cpp
 * @brief Interactive Command Line Interface (CLI) for the Computer simulation.
 * @author Nikita Momot
 * @date 2026
 */

#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <iomanip>
#include <memory>

#include "CPU.h"
#include "RAM.h"
#include "SSD.h"
#include "HDD.h"
#include "StorageController.h"
#include "ThermalPaste.h"
#include "GraphicsCard.h"
#include "SoundCard.h"
#include "Display.h"
#include "SpeakerSystem.h"
#include "Exceptions.h"

using namespace std;

// Table Menu Helpers

void PrintDivider(int width = 52) {
    for (int i = 0; i < width; i++) cout << "-";
    cout << "\n";
}

void PrintRow(const string& text, int width = 52) {
    cout << "| " << text;
    int spaces = width - 3 - static_cast<int>(text.length());
    if (spaces < 0) spaces = 0;
    for (int i = 0; i < spaces; i++) cout << " ";
    cout << "|\n";
}

void PrintHeader(const string& title, int width = 52) {
    PrintDivider(width);
    int total_padding = width - 2 - static_cast<int>(title.length());
    int pad_left = total_padding / 2;
    int pad_right = total_padding - pad_left;
    cout << "|";
    for (int i = 0; i < pad_left; i++) cout << " ";
    cout << title;
    for (int i = 0; i < pad_right; i++) cout << " ";
    cout << "|\n";
    PrintDivider(width);
}

string FormatDouble(double val, int precision = 1) {
    ostringstream oss;
    oss << fixed << setprecision(precision) << val;
    return oss.str();
}

// Input Helper Functions

int PromptChoice() {
    cout << "Selected: ";
    string input;
    getline(cin, input);
    if (input.empty()) {
        return -1;
    }
    stringstream ss(input);
    int val = -1;
    if (ss >> val && ss.eof()) {
        return val;
    }
    return -1;
}

string PromptString(const string& prompt, const string& default_val = "") {
    if (!default_val.empty()) {
        cout << prompt << " [" << default_val << "]: ";
    } else {
        cout << prompt << ": ";
    }

    string input;
    getline(cin, input);
    if (input.empty()) {
        return default_val;
    }
    return input;
}

int PromptInt(const string& prompt, int default_val, int min_val = -1000000, int max_val = 1000000) {
    while (true) {
        cout << prompt << " [" << default_val << "]: ";
        string input;
        getline(cin, input);
        if (input.empty()) {
            return default_val;
        }

        stringstream ss(input);
        int val = 0;
        if (ss >> val && ss.eof()) {
            if (val < min_val) {
                cout << "Warning: value must be at least " << min_val << ". Using default " << default_val << ".\n";
                return default_val;
            }
            if (val > max_val) {
                cout << "Warning: value must be at most " << max_val << ". Using default " << default_val << ".\n";
                return default_val;
            }
            return val;
        }
        cout << "Invalid number! Please enter a valid integer.\n";
    }
}

long long PromptLongLong(const string& prompt, long long default_val, long long min_val = 0, long long max_val = 1000000000000LL) {
    while (true) {
        cout << prompt << " [" << default_val << "]: ";
        string input;
        getline(cin, input);
        if (input.empty()) {
            return default_val;
        }

        stringstream ss(input);
        long long val = 0;
        if (ss >> val && ss.eof()) {
            if (val < min_val) {
                cout << "Warning: value must be at least " << min_val << ". Using default " << default_val << ".\n";
                return default_val;
            }
            if (val > max_val) {
                cout << "Warning: value must be at most " << max_val << ". Using default " << default_val << ".\n";
                return default_val;
            }
            return val;
        }
        cout << "Invalid number! Please enter a valid integer.\n";
    }
}

double PromptDouble(const string& prompt, double default_val, double min_val = -1000000.0, double max_val = 1000000.0) {
    while (true) {
        cout << prompt << " [" << default_val << "]: ";
        string input;
        getline(cin, input);
        if (input.empty()) {
            return default_val;
        }

        stringstream ss(input);
        double val = 0.0;
        if (ss >> val && ss.eof()) {
            if (val < min_val) {
                cout << "Warning: value must be at least " << min_val << ". Using default " << default_val << ".\n";
                return default_val;
            }
            if (val > max_val) {
                cout << "Warning: value must be at most " << max_val << ". Using default " << default_val << ".\n";
                return default_val;
            }
            return val;
        }
        cout << "Invalid number! Please enter a valid decimal number.\n";
    }
}

// Simulator Hardware State

struct HardwareState {
    CPU cpu;
    RAM ram;
    SSD ssd;
    HDD hdd;
    StorageController controller;
    ThermalPaste paste;
    GraphicsCard gpu;
    SoundCard sound_card;
    Display display;
    SpeakerSystem speakers;

    HardwareState() : cpu("AMD Ryzen 7 7800X3D", "AM5", 120, 98304), ram(4), ssd("Samsung 990 PRO", "NVMe PCIe 4.0", 2000, 1200.0), hdd("Seagate IronWolf Pro", 7200, 4000, 256),
          controller("PCIe NVMe Controller"), paste("Noctua NT-H2", 9.0, 50000.0, 0.04), gpu("NVIDIA GeForce RTX 4080", 320, GPUCore(0, 2200), VRAM(16384, 256, "GDDR6X")),
          sound_card("Creative Sound BlasterX AE-5", 6, AudioDAC(96000, 24, 122.0), AudioDSP("Gaming Surround", 1, 0.0)), display("LG UltraGear 27GP850", 2560, 1440, 165), speakers("Edifier R1280DB", 42, 35) {
        cpu.AddCore(CPUCore(0, 4200, true));
        cpu.AddCore(CPUCore(1, 4200, true));
        cpu.AddCore(CPUCore(2, 4200, true));
        cpu.AddCore(CPUCore(3, 4200, true));

        RAMStick stick1("KF432C16BB/16", 16384, 3200, "DDR4", RAMTiming(16, 18, 18, 36));
        RAMStick stick2("KF432C16BB/16", 16384, 3200, "DDR4", RAMTiming(16, 18, 18, 36));
        ram.InstallStick(stick1, 0);
        ram.InstallStick(stick2, 1);

        controller.AttachSSD(ssd);
        controller.AttachHDD(hdd);

        gpu.AddPort(VideoPort("DisplayPort 1.4", 3840, 240));
        gpu.AddPort(VideoPort("DisplayPort 1.4", 3840, 240));
        gpu.AddPort(VideoPort("HDMI 2.1", 3840, 144));
        gpu.GetPort(0).ConnectCable();

        sound_card.AddJack(AudioJack("Line Out 3.5mm", "Green", 32.0));
        sound_card.AddJack(AudioJack("Mic In 3.5mm", "Pink", 1000.0));
        sound_card.AddJack(AudioJack("Headphone Out", "Black", 16.0));
        sound_card.GetJack(0).PlugIn();
    }
};

// Action Menus

void ActionCpu(HardwareState& state) {
    while (true) {
        cout << "\n\n\n";
        PrintHeader("CPU & Cores");
        PrintRow("1 - Execute computational workload");
        PrintRow("2 - Overclock processor");
        PrintRow("3 - Cool down processor");
        PrintRow("4 - Add new CPU core");
        PrintRow("5 - L3 Cache access (Read/Write/Flush)");
        PrintRow("0 - Return");
        PrintDivider();
        PrintRow("Status: " + to_string(state.cpu.GetCoreCount()) + " cores | " +
                 FormatDouble(state.cpu.GetAverageTemperature()) + " C | " +
                 to_string(state.cpu.CalculateCurrentPowerDraw()) + " W");
        PrintRow("Model: " + state.cpu.GetModelName() + " (" + state.cpu.GetSocketType() + ")");
        PrintRow("L3 Cache: " + to_string(state.cpu.GetL3Cache().GetSizeKb()) + " KB | TDP: " +
                 to_string(state.cpu.GetTdpWatts()) + " W");
        PrintDivider();

        int choice = PromptChoice();
        if (choice == 0) break;

        try {
            if (choice == 1) {
                long long instr = PromptLongLong("Number of instructions to execute", 4000000LL, 1LL, 100000000000LL);
                state.cpu.ComputeWorkload(instr);
                cout << "SUCCESS: Workload finished!\n";
                cout << "New Average Temperature: " << state.cpu.GetAverageTemperature() << " C\n";
                cout << "New Power Draw: " << state.cpu.CalculateCurrentPowerDraw() << " W\n";
            } else if (choice == 2) {
                double mult = PromptDouble("Overclock multiplier (e.g. 1.15 for +15%)", 1.15, 1.01, 2.0);
                state.cpu.Overclock(mult);
                cout << "SUCCESS: CPU overclocked with multiplier " << mult << "x!\n";
            } else if (choice == 3) {
                double delta = PromptDouble("Cool down temperature delta (Celsius)", 15.0, 1.0, 100.0);
                state.cpu.CoolDown(delta);
                cout << "SUCCESS: Cores cooled down by " << delta << " C!\n";
                cout << "New Average Temperature: " << state.cpu.GetAverageTemperature() << " C\n";
            } else if (choice == 4) {
                int core_id = state.cpu.GetCoreCount();
                int clock = PromptInt("Base clock frequency (MHz)", 4200, 1000, 6000);
                string ht_str = PromptString("Enable Hyper-Threading? (yes/no)", "yes");
                bool ht = (ht_str == "yes" || ht_str == "y" || ht_str == "1");
                state.cpu.AddCore(CPUCore(core_id, clock, ht));
                cout << "SUCCESS: Core #" << core_id << " added! Total cores: "
                     << state.cpu.GetCoreCount() << "\n";
            } else if (choice == 5) {
                cout << "L3 Cache Operations:\n";
                cout << " 1 - Read memory address\n 2 - Write data\n 3 - Flush dirty lines\n 4 - Invalidate cache\n";
                int op = PromptInt("Choose operation", 1, 1, 4);
                if (op == 1) {
                    long long addr = PromptLongLong("Memory address", 4096, 0, 1000000000LL);
                    bool hit = state.cpu.GetL3Cache().Read(addr);
                    cout << (hit ? "CACHE HIT!" : "CACHE MISS! Line fetched into cache.") << "\n";
                } else if (op == 2) {
                    long long addr = PromptLongLong("Memory address", 4096, 0, 1000000000LL);
                    int bytes = PromptInt("Bytes to write", 64, 1, 4096);
                    state.cpu.GetL3Cache().Write(addr, bytes);
                    cout << "SUCCESS: Wrote " << bytes << " bytes to cache address " << addr << ".\n";
                } else if (op == 3) {
                    state.cpu.GetL3Cache().Flush();
                    cout << "SUCCESS: L3 Cache flushed to main memory.\n";
                } else if (op == 4) {
                    state.cpu.GetL3Cache().Invalidate();
                    cout << "SUCCESS: L3 Cache invalidated.\n";
                }
            } else {
                cout << "Error! Invalid selection! Please enter a valid menu number.\n";
            }
        } catch (const ComputerException& ex) {
            cout << "\n[HARDWARE EXCEPTION CAUGHT] " << ex.what() << "\n";
        } catch (const exception& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
    }
}

void ActionRam(HardwareState& state) {
    while (true) {
        cout << "\n\n\n";
        PrintHeader("RAM Subsystem");
        PrintRow("1 - Allocate memory");
        PrintRow("2 - Free memory");
        PrintRow("3 - Install RAM stick");
        PrintRow("4 - Remove RAM stick");
        PrintRow("5 - Enable XMP profile");
        PrintRow("6 - Memory integrity diagnostics");
        PrintRow("0 - Return");
        PrintDivider();
        PrintRow("Allocated: " + to_string(state.ram.GetTotalAllocatedMb()) + " / " +
                 to_string(state.ram.GetTotalCapacityMb()) + " MB (" +
                 FormatDouble(state.ram.GetTotalCapacityMb() ? (100.0 * state.ram.GetTotalAllocatedMb() / state.ram.GetTotalCapacityMb()) : 0.0) + "%)");
        PrintRow("Modules: " + to_string(state.ram.GetInstalledSticksCount()) + " / " +
                 to_string(state.ram.GetMaxSlots()) + " slots (" +
                 to_string(state.ram.GetChannelMode()) + "x mode)");
        PrintDivider();

        int choice = PromptChoice();
        if (choice == 0) break;

        try {
            if (choice == 1) {
                int mb = PromptInt("Megabytes to allocate", 4096, 1, 262144);
                state.ram.Allocate(mb);
                cout << "SUCCESS: Allocated " << mb << " MB of RAM!\n";
                cout << "Current usage: " << state.ram.GetTotalAllocatedMb() << " / "
                     << state.ram.GetTotalCapacityMb() << " MB\n";
            } else if (choice == 2) {
                int mb = PromptInt("Megabytes to free", 2048, 1, 262144);
                state.ram.Free(mb);
                cout << "SUCCESS: Freed " << mb << " MB of RAM!\n";
                cout << "Current usage: " << state.ram.GetTotalAllocatedMb() << " / "
                     << state.ram.GetTotalCapacityMb() << " MB\n";
            } else if (choice == 3) {
                int slot = PromptInt("Target slot index (0 to " + to_string(state.ram.GetMaxSlots() - 1) + ")",
                                     2, 0, state.ram.GetMaxSlots() - 1);
                string sn = PromptString("Stick serial number", "KF432C16BB/16");
                int cap = PromptInt("Capacity (MB)", 16384, 1024, 65536);
                int freq = PromptInt("Frequency (MHz)", 3200, 1600, 8000);
                string gen = PromptString("Generation (DDR4/DDR5)", "DDR4");
                int cl = PromptInt("CAS Latency (CL)", 16, 10, 40);
                int trcd = PromptInt("tRCD", 18, 10, 50);
                int trp = PromptInt("tRP", 18, 10, 50);
                int tras = PromptInt("tRAS", 36, 20, 100);

                RAMStick new_stick(sn, cap, freq, gen, RAMTiming(cl, trcd, trp, tras));
                state.ram.InstallStick(new_stick, slot);
                cout << "SUCCESS: Installed " << cap << " MB stick into slot #" << slot << "!\n";
            } else if (choice == 4) {
                int slot = PromptInt("Slot index to remove stick from", 0, 0, state.ram.GetMaxSlots() - 1);
                RAMStick removed = state.ram.RemoveStick(slot);
                cout << "SUCCESS: Removed stick " << removed.GetSerialNumber() << " from slot #" << slot << "!\n";
            } else if (choice == 5) {
                int slot = PromptInt("Slot index of the stick", 0, 0, state.ram.GetMaxSlots() - 1);
                RAMStick stick = state.ram.GetStick(slot);
                int target_freq = PromptInt("XMP Frequency (MHz)", 3600, 2000, 9000);
                int cl = PromptInt("XMP CAS Latency", 16, 10, 40);
                int trcd = PromptInt("XMP tRCD", 19, 10, 50);
                int trp = PromptInt("XMP tRP", 19, 10, 50);
                int tras = PromptInt("XMP tRAS", 39, 20, 100);

                stick.EnableXMP(target_freq, RAMTiming(cl, trcd, trp, tras));
                state.ram.InstallStick(stick, slot);
                cout << "SUCCESS: XMP enabled on slot #" << slot << "! New specs: " << stick << "\n";
            } else if (choice == 6) {
                cout << "Running memory integrity test across all installed modules...\n";
                bool all_ok = true;
                for (int i = 0; i < state.ram.GetInstalledSticksCount(); i++) {
                    try {
                        RAMStick s = state.ram.GetStick(i);
                        bool ok = s.RunDiagnostics();
                        cout << " Slot #" << i << " [" << s.GetSerialNumber() << "]: "
                             << (ok ? "PASS (Integrity 100%)" : "FAIL") << "\n";
                        if (!ok) all_ok = false;
                    } catch (...) {}
                }
                if (all_ok) cout << "OVERALL RAM HEALTH: EXCELLENT!\n";
            } else {
                cout << "Error! Invalid selection! Please enter a valid menu number.\n";
            }
        } catch (const ComputerException& ex) {
            cout << "\n[HARDWARE EXCEPTION CAUGHT] " << ex.what() << "\n";
        } catch (const exception& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
    }
}

void ActionSsd(HardwareState& state) {
    while (true) {
        cout << "\n\n\n";
        PrintHeader("SSD");
        PrintRow("1 - Write data");
        PrintRow("2 - Read data");
        PrintRow("3 - Perform NAND TRIM");
        PrintRow("4 - S.M.A.R.T. health check");
        PrintRow("0 - Return");
        PrintDivider();
        PrintRow("Used: " + FormatDouble(state.ssd.GetUsedGb()) + " / " +
                 FormatDouble(state.ssd.GetCapacityGb()) + " GB | Health: " +
                 to_string(static_cast<int>(state.ssd.GetHealthPercentage())) + "%");
        PrintRow("Model: " + state.ssd.GetModel() + " [" + state.ssd.GetInterfaceType() + "]");
        PrintDivider();

        int choice = PromptChoice();
        if (choice == 0) break;

        try {
            if (choice == 1) {
                double gb = PromptDouble("Data volume to write (GB)", 50.0, 0.1, 100000.0);
                state.ssd.WriteData(gb);
                cout << "SUCCESS: Written " << gb << " GB to SSD!\n";
                cout << "Updated Used Space: " << state.ssd.GetUsedGb() << " GB\n";
                cout << "Updated Health:     " << state.ssd.GetHealthPercentage() << "%\n";
            } else if (choice == 2) {
                double gb = PromptDouble("Data volume to read (GB)", 20.0, 0.1, 100000.0);
                state.ssd.ReadData(gb);
                cout << "SUCCESS: Read " << gb << " GB from SSD!\n";
            } else if (choice == 3) {
                state.ssd.PerformTrim();
                cout << "SUCCESS: NAND TRIM executed! Unused flash blocks safely garbage-collected.\n";
            } else if (choice == 4) {
                state.ssd.RunHealthCheck();
                double daily_write = PromptDouble("Estimated daily write workload (GB/day)", 40.0, 1.0, 5000.0);
                double months = state.ssd.EstimateRemainingLifespanMonths(daily_write);
                cout << "---------------- S.M.A.R.T. REPORT ----------------\n";
                cout << "Drive Model:               " << state.ssd.GetModel() << "\n";
                cout << "Interface:                 " << state.ssd.GetInterfaceType() << "\n";
                cout << "NAND Health:               " << state.ssd.GetHealthPercentage() << "%\n";
                cout << "TBW Endurance Remaining:  "
                     << (state.ssd.GetTbwResourceTb() - state.ssd.GetTbwWrittenTb()) << " TB\n";
                cout << "Estimated Lifespan:        " << fixed << setprecision(1) << months << " months (~"
                     << (months / 12.0) << " years)\n";
            } else {
                cout << "Error! Invalid selection! Please enter a valid menu number.\n";
            }
        } catch (const ComputerException& ex) {
            cout << "\n[HARDWARE EXCEPTION CAUGHT] " << ex.what() << "\n";
        } catch (const exception& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
    }
}

void ActionHdd(HardwareState& state) {
    while (true) {
        cout << "\n\n\n";
        PrintHeader("HDD");
        PrintRow("1 - Write data");
        PrintRow("2 - Read data");
        PrintRow("3 - Spin up spindle");
        PrintRow("4 - Park heads safely");
        PrintRow("5 - Scan for bad sectors");
        PrintRow("0 - Return");
        PrintDivider();
        PrintRow("Used: " + FormatDouble(state.hdd.GetUsedGb()) + " / " +
                 FormatDouble(state.hdd.GetCapacityGb()) + " GB | Bad: " +
                 to_string(state.hdd.GetBadSectorsCount()));
        PrintRow("Spindle: " + string(state.hdd.AreHeadsParked() ? "Parked (Standby)" :
                 to_string(state.hdd.GetRpm()) + " RPM (Active)"));
        PrintDivider();

        int choice = PromptChoice();
        if (choice == 0) break;

        try {
            if (choice == 1) {
                double gb = PromptDouble("Data volume to write (GB)", 100.0, 0.1, 100000.0);
                state.hdd.WriteData(gb);
                cout << "SUCCESS: Wrote " << gb << " GB to magnetic platters!\n";
                cout << "Updated Used Space: " << state.hdd.GetUsedGb() << " GB\n";
            } else if (choice == 2) {
                double gb = PromptDouble("Data volume to read (GB)", 50.0, 0.1, 100000.0);
                state.hdd.ReadData(gb);
                cout << "SUCCESS: Read " << gb << " GB from HDD!\n";
            } else if (choice == 3) {
                state.hdd.SpinUp();
                cout << "SUCCESS: Spindle motor accelerated to " << state.hdd.GetRpm() << " RPM. Heads unparked.\n";
            } else if (choice == 4) {
                state.hdd.ParkHeads();
                cout << "SUCCESS: Magnetic heads safely parked on ramp. Platters spun down.\n";
            } else if (choice == 5) {
                int sectors = PromptInt("Number of sectors to scan", 10000, 100, 10000000);
                cout << "Scanning magnetic surface sectors...\n";
                state.hdd.ScanForBadSectors(sectors);
                cout << "Surface scan complete. Bad sectors found: " << state.hdd.GetBadSectorsCount() << "\n";
            } else {
                cout << "Error! Invalid selection! Please enter a valid menu number.\n";
            }
        } catch (const ComputerException& ex) {
            cout << "\n[HARDWARE EXCEPTION CAUGHT] " << ex.what() << "\n";
        } catch (const exception& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
    }
}

void ActionStorageController(HardwareState& state) {
    while (true) {
        cout << "\n\n\n";
        PrintHeader("Storage Controller & RAID");
        PrintRow("1 - Configure RAID mode");
        PrintRow("2 - Perform integrity check");
        PrintRow("3 - Sync controller with drives");
        PrintRow("0 - Return");
        PrintDivider();
        PrintRow("Controller: " + state.controller.GetControllerType());
        PrintRow("RAID Mode: " + state.controller.GetRaidMode() + " | Usable: " +
                 FormatDouble(state.controller.GetTotalCapacityGb()) + " GB");
        PrintDivider();

        int choice = PromptChoice();
        if (choice == 0) break;

        try {
            if (choice == 1) {
                cout << "Available RAID modes:\n";
                cout << " - NONE  (Individual physical drives)\n";
                cout << " - RAID0 (Striping - performance and pooled capacity)\n";
                cout << " - RAID1 (Mirroring - fault tolerance)\n";
                cout << " - JBOD  (Just a Bunch Of Disks - linear span)\n";
                string mode = PromptString("Enter target RAID mode", "RAID1");
                state.controller.ConfigureRAID(mode);
                cout << "SUCCESS: RAID mode configured to " << state.controller.GetRaidMode() << "!\n";
                cout << "Usable storage array capacity: " << state.controller.GetTotalCapacityGb() << " GB\n";
            } else if (choice == 2) {
                cout << "Checking drive health, parity, and RAID consistency...\n";
                bool ok = state.controller.PerformIntegrityCheck();
                cout << "Array Integrity Status: " << (ok ? "HEALTHY (All drives optimal)" : "DEGRADED / WARNING") << "\n";
            } else if (choice == 3) {
                StorageController updated(state.controller.GetControllerType());
                updated.AttachSSD(state.ssd);
                updated.AttachHDD(state.hdd);
                updated.ConfigureRAID(state.controller.GetRaidMode());
                state.controller = updated;
                cout << "SUCCESS: Storage Controller synced with current drive states.\n";
            } else {
                cout << "Error! Invalid selection! Please enter a valid menu number.\n";
            }
        } catch (const ComputerException& ex) {
            cout << "\n[HARDWARE EXCEPTION CAUGHT] " << ex.what() << "\n";
        } catch (const exception& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
    }
}

void ActionThermalPaste(HardwareState& state) {
    while (true) {
        cout << "\n\n\n";
        PrintHeader("Thermal Paste");
        PrintRow("1 - Calculate thermal resistance");
        PrintRow("2 - Simulate thermal aging");
        PrintRow("3 - Replace thermal paste");
        PrintRow("0 - Return");
        PrintDivider();
        PrintRow("Paste: " + state.paste.GetBrandName() + " (" +
                 (state.paste.IsEffective() ? "Optimal" : "Degraded!") + ")");
        PrintRow("Conductivity: " + FormatDouble(state.paste.GetThermalConductivity()) +
                 " W/(m*K) | Eff: " + FormatDouble(state.paste.EvaluateHeatTransferEfficiency(), 3));
        PrintDivider();

        int choice = PromptChoice();
        if (choice == 0) break;

        try {
            if (choice == 1) {
                double area = PromptDouble("IHS Surface Area (cm^2, typical CPU is ~4.0)", 4.0, 0.5, 50.0);
                double res = state.paste.CalculateThermalResistance(area);
                cout << "Thermal Junction Resistance for " << area << " cm^2: "
                     << fixed << setprecision(5) << res << " (K*cm^2)/W\n";
            } else if (choice == 2) {
                double years = PromptDouble("Operating elapsed time to simulate (years)", 2.0, 0.1, 20.0);
                state.paste.DegradeOverTime(years);
                cout << "SUCCESS: Simulated " << years << " years of thermal cycling!\n";
                cout << "New Thermal Conductivity: " << state.paste.GetThermalConductivity() << " W/(m*K)\n";
                cout << "New Efficiency Score:     " << state.paste.EvaluateHeatTransferEfficiency() << "\n";
                cout << "Still Effective?          " << (state.paste.IsEffective() ? "Yes" : "NO - WARNING!") << "\n";
            } else if (choice == 3) {
                double cond = PromptDouble("New thermal conductivity [W/(m*K)]", 12.5, 1.0, 100.0);
                double thick = PromptDouble("Applied layer thickness (mm)", 0.03, 0.005, 1.0);
                state.paste.ReplacePaste(cond, thick);
                cout << "SUCCESS: Fresh thermal compound applied!\n";
                cout << "New Efficiency Score: " << state.paste.EvaluateHeatTransferEfficiency() << "\n";
            } else {
                cout << "Error! Invalid selection! Please enter a valid menu number.\n";
            }
        } catch (const ComputerException& ex) {
            cout << "\n[HARDWARE EXCEPTION CAUGHT] " << ex.what() << "\n";
        } catch (const exception& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
    }
}

void ActionGraphics(HardwareState& state) {
    while (true) {
        cout << "\n\n\n";
        PrintHeader("Graphics Card & Display");
        PrintRow("1 - Render 3D scene (Workload & VRAM)");
        PrintRow("2 - Set GPU clock frequency");
        PrintRow("3 - Cool down GPU core");
        PrintRow("4 - Configure display (Resolution/Refresh)");
        PrintRow("5 - Connect / Disconnect monitor cable");
        PrintRow("6 - Toggle display monitor power");
        PrintRow("0 - Return");
        PrintDivider();
        PrintRow("GPU: " + to_string(state.gpu.GetGPUCore().GetClockMhz()) + " MHz | " +
                 FormatDouble(state.gpu.GetGPUCore().GetTemperatureCelsius()) + " C | Load: " +
                 to_string(static_cast<int>(state.gpu.GetGPUCore().GetLoadPercentage())) + "%");
        PrintRow("VRAM: " + to_string(state.gpu.GetVRAM().GetUsedMb()) + " / " +
                 to_string(state.gpu.GetVRAM().GetCapacityMb()) + " MB | " +
                 to_string(state.gpu.CalculateCurrentPowerDraw()) + " W");
        PrintRow("Display: " + to_string(state.display.GetResolutionWidth()) + "x" +
                 to_string(state.display.GetResolutionHeight()) + "@" +
                 to_string(state.display.GetRefreshRateHz()) + "Hz [" +
                 (state.display.IsPoweredOn() ? "ON" : "OFF") + "]");
        PrintDivider();

        int choice = PromptChoice();
        if (choice == 0) break;

        try {
            if (choice == 1) {
                int frames = PromptInt("Number of frames to render", 60, 1, 1000);
                int tex_mb = PromptInt("Texture memory required (MB)", 2048, 1, 32768);
                state.gpu.RenderScene(frames, tex_mb);
                cout << "SUCCESS: 3D scene rendered successfully!\n";
                cout << "GPU Temperature: " << state.gpu.GetGPUCore().GetTemperatureCelsius() << " C\n";
                cout << "GPU Load:        " << state.gpu.GetGPUCore().GetLoadPercentage() << "%\n";
                cout << "VRAM Used:       " << state.gpu.GetVRAM().GetUsedMb() << " / "
                     << state.gpu.GetVRAM().GetCapacityMb() << " MB\n";
                cout << "Current Power:   " << state.gpu.CalculateCurrentPowerDraw() << " W\n";
            } else if (choice == 2) {
                int clock = PromptInt("Target GPU clock frequency (MHz)", 2400, 500, 4000);
                state.gpu.GetGPUCore().SetClockMhz(clock);
                cout << "SUCCESS: GPU clock frequency set to " << clock << " MHz!\n";
            } else if (choice == 3) {
                double delta = PromptDouble("Cool down temperature delta (Celsius)", 15.0, 1.0, 100.0);
                state.gpu.GetGPUCore().CoolDown(delta);
                cout << "SUCCESS: GPU core cooled down! New temperature: "
                     << state.gpu.GetGPUCore().GetTemperatureCelsius() << " C\n";
            } else if (choice == 4) {
                int width = PromptInt("Resolution width", 2560, 640, 7680);
                int height = PromptInt("Resolution height", 1440, 480, 4320);
                int hz = PromptInt("Refresh rate (Hz)", 144, 30, 540);
                state.display.SetResolution(width, height);
                state.display.SetRefreshRate(hz);
                cout << "SUCCESS: Display mode updated: " << width << "x" << height << "@" << hz << "Hz!\n";
                cout << "Total Active Pixels: " << state.display.CalculateTotalPixels() << "\n";
            } else if (choice == 5) {
                if (state.gpu.GetPortCount() > 0) {
                    bool currently = state.gpu.GetPort(0).IsConnected();
                    if (currently) {
                        state.gpu.GetPort(0).DisconnectCable();
                        cout << "SUCCESS: Display cable disconnected from " << state.gpu.GetPort(0).GetPortType() << ".\n";
                    } else {
                        state.gpu.GetPort(0).ConnectCable();
                        cout << "SUCCESS: Display cable connected to " << state.gpu.GetPort(0).GetPortType() << "!\n";
                    }
                }
            } else if (choice == 6) {
                state.display.PowerToggle();
                cout << "SUCCESS: Display monitor power toggled: "
                     << (state.display.IsPoweredOn() ? "POWER ON" : "STANDBY") << "!\n";
            } else {
                cout << "Error! Invalid selection! Please enter a valid menu number.\n";
            }
        } catch (const ComputerException& ex) {
            cout << "\n[HARDWARE EXCEPTION CAUGHT] " << ex.what() << "\n";
        } catch (const exception& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
    }
}

void ActionAudio(HardwareState& state) {
    while (true) {
        cout << "\n\n\n";
        PrintHeader("Sound Card & Speakers");
        PrintRow("1 - Play audio stream");
        PrintRow("2 - Apply DSP sound profile preset");
        PrintRow("3 - Adjust speaker volume");
        PrintRow("4 - Toggle speaker mute");
        PrintRow("5 - Configure surround sound channels");
        PrintRow("6 - Plug / Unplug audio jack");
        PrintRow("0 - Return");
        PrintDivider();
        PrintRow("DSP: '" + state.sound_card.GetDSP().GetProfileName() + "' | Channels: " +
                 to_string(state.sound_card.GetChannelCount()));
        PrintRow("DAC: " + to_string(state.sound_card.GetDAC().GetSamplingRateHz()) +
                 " Hz / " + to_string(state.sound_card.GetDAC().GetBitDepth()) + "-bit");
        PrintRow("Speakers: " + to_string(state.speakers.GetCurrentVolume()) + "% " +
                 (state.speakers.IsMuted() ? "[MUTED]" : "[ACTIVE]") + " | Jack: " +
                 (state.sound_card.GetJackCount() > 0 && state.sound_card.GetJack(0).IsPlugged() ? "Plugged" : "Open"));
        PrintDivider();

        int choice = PromptChoice();
        if (choice == 0) break;

        try {
            if (choice == 1) {
                int samples = PromptInt("Number of digital PCM samples to play", 48000, 1, 1920000);
                double vol = PromptDouble("Stream volume level (0.0 to 1.0)", 0.75, 0.0, 1.0);
                state.sound_card.PlayAudioStream(samples, vol);
                state.speakers.OutputSound(3, 75.0);
                cout << "SUCCESS: Audio playback stream processed through DAC & DSP!\n";
                cout << "Acoustic sound emitted via " << state.speakers.GetSystemName() << ".\n";
            } else if (choice == 2) {
                cout << "Available sound profiles: [Flat, Bass Boost, Gaming Surround, Voice Clarity, Studio Clean]\n";
                string profile = PromptString("Enter preset name", "Bass Boost");
                state.sound_card.GetDSP().ApplySoundProfile(profile);
                cout << "SUCCESS: Active audio DSP profile set to '" << profile << "'!\n";
            } else if (choice == 3) {
                int vol = PromptInt("Speaker master volume (0 - 100%)", 50, 0, 100);
                state.speakers.SetVolume(vol);
                cout << "SUCCESS: Speaker master volume set to " << vol << "%!\n";
            } else if (choice == 4) {
                state.speakers.ToggleMute();
                cout << "SUCCESS: Speaker mute toggled: "
                     << (state.speakers.IsMuted() ? "MUTED" : "UNMUTED") << "!\n";
            } else if (choice == 5) {
                int ch = PromptInt("Surround channel configuration (2, 6, 8)", 6, 2, 8);
                state.sound_card.ConfigureSurround(ch);
                cout << "SUCCESS: Sound card configured for " << ch << "-channel surround output!\n";
            } else if (choice == 6) {
                if (state.sound_card.GetJackCount() > 0) {
                    bool currently = state.sound_card.GetJack(0).IsPlugged();
                    if (currently) {
                        state.sound_card.GetJack(0).Unplug();
                        cout << "SUCCESS: Audio jack unplugged.\n";
                    } else {
                        state.sound_card.GetJack(0).PlugIn();
                        cout << "SUCCESS: Audio cable plugged into " << state.sound_card.GetJack(0).GetPortType() << ".\n";
                    }
                }
            } else {
                cout << "Error! Invalid selection! Please enter a valid menu number.\n";
            }
        } catch (const ComputerException& ex) {
            cout << "\n[HARDWARE EXCEPTION CAUGHT] " << ex.what() << "\n";
        } catch (const exception& ex) {
            cout << "\n[ERROR] " << ex.what() << "\n";
        }
    }
}

void ActionSystemSummary(HardwareState& state) {
    cout << "\n\n\n";
    cout << "===================================================================\n";
    cout << "                     SYSTEM HARDWARE PASSPORT                      \n";
    cout << "===================================================================\n\n";

    cout << " [1] CPU\n";
    cout << "     Model:       " << state.cpu.GetModelName() << " (" << state.cpu.GetSocketType() << ")\n";
    cout << "     Cores:       " << state.cpu.GetCoreCount() << " physical cores\n";
    cout << "     Average T:   " << fixed << setprecision(2) << state.cpu.GetAverageTemperature() << " C\n";
    cout << "     Power Draw:  " << state.cpu.CalculateCurrentPowerDraw() << " W (TDP: " << state.cpu.GetTdpWatts() << " W)\n";
    cout << "     L3 Cache:    " << state.cpu.GetL3Cache().GetSizeKb() << " KB\n\n";

    cout << " [2] RAM\n";
    cout << "     Installed:   " << state.ram.GetInstalledSticksCount() << " / " << state.ram.GetMaxSlots() << " slots\n";
    cout << "     Total Cap:   " << state.ram.GetTotalCapacityMb() << " MB ("
         << (state.ram.GetTotalCapacityMb() / 1024) << " GB)\n";
    cout << "     Allocated:   " << state.ram.GetTotalAllocatedMb() << " MB ("
         << fixed << setprecision(1) << (100.0 * state.ram.GetTotalAllocatedMb() / state.ram.GetTotalCapacityMb()) << "%)\n";
    cout << "     Channel:     " << state.ram.GetChannelMode() << "x mode\n\n";

    cout << " [3] STORAGE SUBSYSTEM\n";
    cout << "     SSD:         " << state.ssd.GetModel() << " [" << state.ssd.GetInterfaceType() << "]\n";
    cout << "                  " << state.ssd.GetUsedGb() << " GB used / " << state.ssd.GetCapacityGb() << " GB total ("
         << state.ssd.GetHealthPercentage() << "% health)\n";
    cout << "     HDD:         " << state.hdd.GetModel() << " [" << state.hdd.GetRpm() << " RPM]\n";
    cout << "                  " << state.hdd.GetUsedGb() << " GB used / " << state.hdd.GetCapacityGb() << " GB total\n";
    cout << "     Controller:  " << state.controller.GetControllerType() << " (RAID: " << state.controller.GetRaidMode() << ")\n";
    cout << "     Array Total: " << fixed << setprecision(1) << state.controller.GetTotalCapacityGb() << " GB usable\n\n";

    cout << " [4] THERMAL INTERFACE\n";
    cout << "     Paste:       " << state.paste.GetBrandName() << "\n";
    cout << "     Efficiency:  " << fixed << setprecision(3) << state.paste.EvaluateHeatTransferEfficiency()
         << " (" << (state.paste.IsEffective() ? "Optimal" : "Degraded / Repaste required") << ")\n\n";

    cout << " [5] GRAPHICS & DISPLAY\n";
    cout << "     GPU Model:   " << state.gpu.GetModelName() << " [" << state.gpu.GetGPUCore().GetClockMhz() << " MHz]\n";
    cout << "     GPU Temp:    " << state.gpu.GetGPUCore().GetTemperatureCelsius() << " C (Load: "
         << state.gpu.GetGPUCore().GetLoadPercentage() << "%)\n";
    cout << "     VRAM:        " << state.gpu.GetVRAM().GetUsedMb() << " MB used / "
         << state.gpu.GetVRAM().GetCapacityMb() << " MB " << state.gpu.GetVRAM().GetMemoryType() << "\n";
    cout << "     GPU Power:   " << state.gpu.CalculateCurrentPowerDraw() << " W\n";
    cout << "     Display:     " << state.display.GetModel() << " [" << state.display.GetResolutionWidth()
         << "x" << state.display.GetResolutionHeight() << "@" << state.display.GetRefreshRateHz() << "Hz]\n";
    cout << "     Status:      " << (state.display.IsPoweredOn() ? "Screen Active" : "Standby") << "\n\n";

    cout << " [6] AUDIO SUBSYSTEM\n";
    cout << "     Sound Card:  " << state.sound_card.GetCardModel() << " (" << state.sound_card.GetChannelCount() << " Channels)\n";
    cout << "     Audio DAC:   " << state.sound_card.GetDAC().GetSamplingRateHz() << " Hz, "
         << state.sound_card.GetDAC().GetBitDepth() << "-bit (SNR: " << state.sound_card.GetDAC().GetSnrDb() << " dB)\n";
    cout << "     Audio DSP:   Profile: '" << state.sound_card.GetDSP().GetProfileName() << "'\n";
    cout << "     Speakers:    " << state.speakers.GetSystemName() << " [" << state.speakers.GetPowerWattsRms()
         << " W RMS, Volume: " << state.speakers.GetCurrentVolume() << "%"
         << (state.speakers.IsMuted() ? " (MUTED)" : "") << "]\n";
    cout << "===================================================================\n";
}

void PrintMainMenu() {
    cout << "\n\n\n";
    PrintHeader("COMPUTER SIMULATOR CLI");
    PrintRow("1 - CPU & Cores");
    PrintRow("2 - RAM Subsystem");
    PrintRow("3 - SSD");
    PrintRow("4 - HDD");
    PrintRow("5 - Storage Controller & RAID");
    PrintRow("6 - Thermal Paste");
    PrintRow("7 - Graphics Card & Display");
    PrintRow("8 - Sound Card & Speakers");
    PrintRow("9 - System Passport");
    PrintRow("10 - Reset to Defaults");
    PrintRow("0 - Exit");
    PrintDivider();
}

int main() {
    cout << "Initializing Computer System Hardware Simulator...\n";
    HardwareState state;
    cout << "System initialized with standard configuration.\n";

    while (true) {
        PrintMainMenu();
        int choice = PromptChoice();

        if (choice == 0) {
            cout << "\nExiting Computer System Simulator. Goodbye!\n\n";
            break;
        }

        switch (choice) {
        case 1:
            ActionCpu(state);
            break;
        case 2:
            ActionRam(state);
            break;
        case 3:
            ActionSsd(state);
            break;
        case 4:
            ActionHdd(state);
            break;
        case 5:
            ActionStorageController(state);
            break;
        case 6:
            ActionThermalPaste(state);
            break;
        case 7:
            ActionGraphics(state);
            break;
        case 8:
            ActionAudio(state);
            break;
        case 9:
            ActionSystemSummary(state);
            break;
        case 10: {
            string confirm = PromptString("Reset all components to defaults? (yes/no)", "no");
            if (confirm == "yes" || confirm == "y") {
                state = HardwareState();
                cout << "SUCCESS: All components reset to factory default values.\n";
            } else {
                cout << "Reset canceled.\n";
            }
            break;
        }
        default:
            cout << "Error! Invalid selection! Please enter a valid menu number.\n";
            break;
        }
    }

    return 0;
}