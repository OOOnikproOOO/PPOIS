/**
 * @file GraphicsCard.cpp
 * @brief Implementation of GraphicsCard methods.
 * @author Nikita Momot
 * @date 2026
 */

#include "GraphicsCard.h"
#include "Exceptions.h"

GraphicsCard::GraphicsCard(const std::string& model_name, int base_power_watts, const GPUCore& core, const VRAM& vram) :
    model_name_(model_name), power_draw_watts_(base_power_watts), gpu_core_(core), vram_(vram), video_ports_() {}

bool GraphicsCard::operator==(const GraphicsCard& other) const {
    return (model_name_ == other.model_name_ &&
            power_draw_watts_ == other.power_draw_watts_ &&
            gpu_core_ == other.gpu_core_ &&
            vram_ == other.vram_ &&
            video_ports_ == other.video_ports_);
}

bool GraphicsCard::operator!=(const GraphicsCard& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const GraphicsCard& gpu) {
    os << "GraphicsCard: " << gpu.model_name_ << " [" << gpu.gpu_core_.GetClockMhz() << " MHz, " << gpu.vram_.GetCapacityMb() << " MB VRAM, Ports: " << gpu.video_ports_.size() << ", Power: " << gpu.CalculateCurrentPowerDraw() << " W]";
    return os;
}

void GraphicsCard::AddPort(const VideoPort& port) {
    video_ports_.push_back(port);
}

void GraphicsCard::RenderScene(int frame_count, int texture_memory_mb) {
    if (frame_count <= 0)
        return;
    
    vram_.Allocate(texture_memory_mb);
    try {
        gpu_core_.RenderFrames(frame_count);
    } catch (...) {
        vram_.Free(texture_memory_mb);
        throw;
    }
}

int GraphicsCard::CalculateCurrentPowerDraw() const {
    double load_ratio = gpu_core_.GetLoadPercentage() / 100.0;
    int calculated = static_cast<int>(power_draw_watts_ * (0.15 + 0.85 * load_ratio));
    return std::max(15, calculated);
}

std::string GraphicsCard::GetModelName() const {
    return model_name_;
}

GPUCore& GraphicsCard::GetGPUCore() {
    return gpu_core_;
}

const GPUCore& GraphicsCard::GetGPUCore() const {
    return gpu_core_;
}

VRAM& GraphicsCard::GetVRAM() {
    return vram_;
}

const VRAM& GraphicsCard::GetVRAM() const {
    return vram_;
}

int GraphicsCard::GetPortCount() const {
    return static_cast<int>(video_ports_.size());
}

VideoPort& GraphicsCard::GetPort(int index) {
    if (index < 0 || index >= static_cast<int>(video_ports_.size()))
        throw DeviceNotFoundException("Video port index out of bounds on graphics card.");
    
    return video_ports_[index];
}