/**
 * @file Computer.cpp
 * @brief Implementation of Computer methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "Computer.h"
#include "POSTFailureException.h"
#include "DeviceNotFoundException.h"

Computer::Computer(const std::string& pc_name, const Motherboard& motherboard, const CPU& cpu, const RAM& ram, const GraphicsCard& gpu, const PowerSupply& psu, const OperatingSystem& os, const NetworkAdapter& network, const SystemDiagnostics& diagnostics) :
    pc_name_(pc_name), is_powered_on_(false), motherboard_(motherboard), cpu_(cpu), ram_(ram), gpu_(gpu), psu_(psu), os_(os), network_(network), diagnostics_(diagnostics) {}

bool Computer::operator==(const Computer& other) const {
    return pc_name_ == other.pc_name_ && is_powered_on_ == other.is_powered_on_ &&
           motherboard_ == other.motherboard_ && cpu_ == other.cpu_ &&
           ram_ == other.ram_ && gpu_ == other.gpu_ &&
           psu_ == other.psu_ && os_ == other.os_ &&
           network_ == other.network_ && diagnostics_ == other.diagnostics_;
}

bool Computer::operator!=(const Computer& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Computer& pc) {
    os << "Computer '" << pc.pc_name_ << "' [" << (pc.is_powered_on_ ? "POWERED ON" : "SHUTDOWN") << ", " << pc.cpu_.GetModelName() << ", " << (pc.ram_.GetTotalCapacityMb() / 1024) << " GB RAM, " << pc.gpu_.GetModelName() << ", " << pc.os_.GetOsName() << "]";
    return os;
}

void Computer::PowerOn() {
    if (ram_.GetInstalledSticksCount() == 0) 
        throw POSTFailureException("Computer POST failure: No RAM modules installed.");
    psu_.PowerOn();
    motherboard_.PerformPOST();
    os_.Boot();
    is_powered_on_ = true;
}

void Computer::PowerOff() {
    if (os_.IsBooted()) 
        os_.Shutdown();
    psu_.PowerOff();
    is_powered_on_ = false;
}

bool Computer::RunDiagnostics() {
    double cpu_t = cpu_.GetAverageTemperature();
    double gpu_t = gpu_.GetTemperatureCelsius();
    double vrm_t = motherboard_.GetVRMTemperature();
    diagnostics_.DiagnoseTemperatures(cpu_t, gpu_t, vrm_t);
    int power = psu_.CalculateTotalPowerDrawWatts();
    diagnostics_.DiagnosePower(power, psu_.GetRatedWattage());
    return diagnostics_.IsNominal();
}

void Computer::ConnectNetwork(const std::string& ip) {
    network_.Connect();
    network_.SendPacket(NetworkPacket(ip, "8.8.8.8", 53, 32, "UDP"));
}

const std::string& Computer::GetPcName() const {
    return pc_name_;
}

bool Computer::IsPoweredOn() const {
    return is_powered_on_;
}

Motherboard& Computer::GetMotherboard() {
    return motherboard_;
}

const Motherboard& Computer::GetMotherboard() const {
    return motherboard_;
}

CPU& Computer::GetCPU() {
    return cpu_;
}

const CPU& Computer::GetCPU() const {
    return cpu_;
}

RAM& Computer::GetRAM() {
    return ram_;
}

const RAM& Computer::GetRAM() const {
    return ram_;
}

GraphicsCard& Computer::GetGPU() {
    return gpu_;
}

const GraphicsCard& Computer::GetGPU() const {
    return gpu_;
}

PowerSupply& Computer::GetPSU() {
    return psu_;
}

const PowerSupply& Computer::GetPSU() const {
    return psu_;
}

OperatingSystem& Computer::GetOS() {
    return os_;
}

const OperatingSystem& Computer::GetOS() const {
    return os_;
}

NetworkAdapter& Computer::GetNetwork() {
    return network_;
}

const NetworkAdapter& Computer::GetNetwork() const {
    return network_;
}

SystemDiagnostics& Computer::GetDiagnostics() {
    return diagnostics_;
}

const SystemDiagnostics& Computer::GetDiagnostics() const {
    return diagnostics_;
}