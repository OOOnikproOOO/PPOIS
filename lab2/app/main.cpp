/**
 * @file main.cpp
 * @brief Interactive Command Line Interface (CLI) for the Computer System simulation.
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
#include "Exceptions.h"

using namespace std;

// ============================================================================
// Table Menu UI Helpers (Framed with '|')
// ============================================================================

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

// ============================================================================
// Input Helper Functions
// ============================================================================

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

// ============================================================================
// Global Simulator Hardware State
// ============================================================================

struct HardwareState {
    CPU cpu;
    RAM ram;
    SSD ssd;
    HDD hdd;
    StorageController controller;
    ThermalPaste paste;

    HardwareState()
        : cpu("AMD Ryzen 7 7800X3D", "AM5", 120, 98304),
          ram(4),
          ssd("Samsung 990 PRO", "NVMe PCIe 4.0", 2000, 1200.0),
          hdd("Seagate IronWolf Pro", 7200, 4000, 256),
          controller("PCIe NVMe Controller"),
          paste("Noctua NT-H2", 9.0, 50000.0, 0.04) {
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
    }
};

// ============================================================================
// Subsystem Action Menus
// ============================================================================

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
        PrintHeader("SSD Drive");
        PrintRow("1 - Write data");
        PrintRow("2 - Read data");
        PrintRow("3 - Perform NAND TRIM");
        PrintRow("4 - S.M.A.R.T. health check");
        PrintRow("0 - Return");
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
        PrintHeader("HDD Drive");
        PrintRow("1 - Write data");
        PrintRow("2 - Read data");
        PrintRow("3 - Spin up spindle");
        PrintRow("4 - Park heads safely");
        PrintRow("5 - Scan for bad sectors");
        PrintRow("0 - Return");
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
         << " (" << (state.paste.IsEffective() ? "Optimal" : "Degraded / Repaste required") << ")\n";
    cout << "===================================================================\n";
}

// ============================================================================
// Main Menu
// ============================================================================

void PrintMainMenu() {
    cout << "\n\n\n";
    PrintHeader("COMPUTER SYSTEM SIMULATOR CLI");
    PrintRow("1 - CPU & Cores");
    PrintRow("2 - RAM Subsystem");
    PrintRow("3 - SSD Drive");
    PrintRow("4 - HDD Drive");
    PrintRow("5 - Storage Controller & RAID");
    PrintRow("6 - Thermal Paste");
    PrintRow("7 - System Passport");
    PrintRow("8 - Reset to Defaults");
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
            ActionSystemSummary(state);
            break;
        case 8: {
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
