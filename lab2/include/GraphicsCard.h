/**
 * @file GraphicsCard.h
 * @brief Declaration of the GraphicsCard class.
 * @author Nikita Momot
 * @date 2026
 */

#ifndef GRAPHICSCARD_H
#define GRAPHICSCARD_H

#include <iostream>
#include <string>
#include <vector>
#include "GPUCore.h"
#include "VRAM.h"
#include "VideoPort.h"

/**
 * @brief Class modeling a discrete graphics adapter uniting GPUCore, VRAM and VideoPorts.
 */
class GraphicsCard {
public:
    /**
     * @brief Constructs a graphics card with specified model, core and VRAM.
     * @param model_name Commercial product name.
     * @param base_power_watts Base power consumption in Watts.
     * @param core Graphics processing unit core die.
     * @param vram Video graphics memory subsystem.
     */
    explicit GraphicsCard(const std::string& model_name = "NVIDIA GeForce RTX 4080", int base_power_watts = 320, const GPUCore& core = GPUCore(0, 2200), const VRAM& vram = VRAM(16384, 256, "GDDR6X"));

    /**
     * @brief Equality operator comparing graphics card models and configurations.
     * @param other GraphicsCard to compare with.
     * @return true if properties match.
     */
    bool operator==(const GraphicsCard& other) const;

    /**
     * @brief Inequality operator.
     * @param other GraphicsCard to compare with.
     * @return true if properties differ.
     */
    bool operator!=(const GraphicsCard& other) const;

    /**
     * @brief Stream output operator for formatting graphics card status.
     * @param os Output stream.
     * @param gpu GraphicsCard instance to display.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const GraphicsCard& gpu);

    /**
     * @brief Adds a display output connector to the graphics card rear panel.
     * @param port VideoPort instance to add.
     */
    void AddPort(const VideoPort& port);

    /**
     * @brief Renders a 3D graphic scene, allocating VRAM and executing GPU core cycles.
     * @param frame_count Number of graphical frames to compute.
     * @param texture_memory_mb VRAM buffer size required for textures.
     */
    void RenderScene(int frame_count, int texture_memory_mb);

    /**
     * @brief Calculates current dynamic power draw in Watts based on load and clock.
     * @return Power consumption in Watts.
     */
    int CalculateCurrentPowerDraw() const;

    /**
     * @brief Gets graphics card commercial model name.
     * @return Model name string.
     */
    std::string GetModelName() const;

    /**
     * @brief Gets reference to the graphics core unit.
     * @return Reference to GPUCore.
     */
    GPUCore& GetGPUCore();
    const GPUCore& GetGPUCore() const;

    /**
     * @brief Gets reference to the VRAM subsystem.
     * @return Reference to VRAM.
     */
    VRAM& GetVRAM();
    const VRAM& GetVRAM() const;

    /**
     * @brief Gets count of installed display output ports.
     * @return Port count.
     */
    int GetPortCount() const;

    /**
     * @brief Gets reference to video port at specified index.
     * @param index Port slot index.
     * @return Reference to VideoPort.
     */
    VideoPort& GetPort(int index);

private:
    std::string model_name_;
    int power_draw_watts_;
    GPUCore gpu_core_;
    VRAM vram_;
    std::vector<VideoPort> video_ports_;
};

#endif