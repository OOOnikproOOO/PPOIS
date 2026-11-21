/**
 * @file Computer.h
 * @brief Declaration of the Computer class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>
#include <string>
#include "CPU.h"
#include "RAM.h"
#include "Motherboard.h"
#include "GraphicsCard.h"
#include "PowerSupply.h"
#include "OperatingSystem.h"
#include "NetworkAdapter.h"
#include "SystemDiagnostics.h"

/**
 * @brief Class modeling an integrated Personal Computer uniting motherboard, CPU, RAM, GPU, PSU, OS, network and diagnostics.
 */
class Computer {
public:
    /**
     * @brief Constructs a Computer with interconnected hardware and software subsystems.
     * @param pc_name Personal computer system identifier name.
     * @param motherboard Motherboard subsystem.
     * @param cpu Central processing unit.
     * @param ram Memory subsystem.
     * @param gpu Graphics subsystem.
     * @param psu Power delivery subsystem.
     * @param os Operating system.
     * @param network Network adapter.
     * @param diagnostics Diagnostics monitor.
     */
    explicit Computer(const std::string& pc_name = "Master PC", const Motherboard& motherboard = Motherboard(), const CPU& cpu = CPU(), const RAM& ram = RAM(), const GraphicsCard& gpu = GraphicsCard(),
                      const PowerSupply& psu = PowerSupply(), const OperatingSystem& os = OperatingSystem(), const NetworkAdapter& network = NetworkAdapter(), const SystemDiagnostics& diagnostics = SystemDiagnostics());

    /**
     * @brief Equality operator comparing computer configurations and states.
     * @param other Another Computer instance.
     * @return true if computers match.
     */
    bool operator==(const Computer& other) const;

    /**
     * @brief Inequality operator.
     * @param other Another Computer instance.
     * @return true if computers differ.
     */
    bool operator!=(const Computer& other) const;

    /**
     * @brief Stream output operator for formatting computer state.
     * @param os Output stream.
     * @param pc Computer instance.
     * @return Reference to output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Computer& pc);

    /**
     * @brief Powers on the computer, performs hardware verification and boots operating system.
     */
    void PowerOn();

    /**
     * @brief Shuts down operating system and cuts main DC power delivery.
     */
    void PowerOff();

    /**
     * @brief Executes comprehensive hardware diagnostics across thermal and electrical sensors.
     * @return true if all subsystems report nominal status.
     */
    bool RunDiagnostics();

    /**
     * @brief Assigns IP network configuration and connects network interface.
     * @param ip New IPv4 address string.
     */
    void ConnectNetwork(const std::string& ip);

    /**
     * @brief Gets computer system name.
     * @return Computer name string.
     */
    const std::string& GetPcName() const;

    /**
     * @brief Checks whether the computer is powered on.
     * @return true if running.
     */
    bool IsPoweredOn() const;

    /**
     * @brief Gets reference to the integrated Motherboard.
     * @return Reference to Motherboard.
     */
    Motherboard& GetMotherboard();
    const Motherboard& GetMotherboard() const;

    /**
     * @brief Gets reference to the Central Processing Unit.
     * @return Reference to CPU.
     */
    CPU& GetCPU();
    const CPU& GetCPU() const;

    /**
     * @brief Gets reference to the RAM subsystem.
     * @return Reference to RAM.
     */
    RAM& GetRAM();
    const RAM& GetRAM() const;

    /**
     * @brief Gets reference to the discrete Graphics Card.
     * @return Reference to GraphicsCard.
     */
    GraphicsCard& GetGPU();
    const GraphicsCard& GetGPU() const;

    /**
     * @brief Gets reference to the Power Supply.
     * @return Reference to PowerSupply.
     */
    PowerSupply& GetPSU();
    const PowerSupply& GetPSU() const;

    /**
     * @brief Gets reference to the Operating System.
     * @return Reference to OperatingSystem.
     */
    OperatingSystem& GetOS();
    const OperatingSystem& GetOS() const;

    /**
     * @brief Gets reference to the Network Adapter.
     * @return Reference to NetworkAdapter.
     */
    NetworkAdapter& GetNetwork();
    const NetworkAdapter& GetNetwork() const;

    /**
     * @brief Gets reference to the System Diagnostics monitor.
     * @return Reference to SystemDiagnostics.
     */
    SystemDiagnostics& GetDiagnostics();
    const SystemDiagnostics& GetDiagnostics() const;

private:
    std::string pc_name_;
    bool is_powered_on_;
    Motherboard motherboard_;
    CPU cpu_;
    RAM ram_;
    GraphicsCard gpu_;
    PowerSupply psu_;
    OperatingSystem os_;
    NetworkAdapter network_;
    SystemDiagnostics diagnostics_;
};

#endif