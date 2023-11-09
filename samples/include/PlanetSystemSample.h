#pragma once

#include "Sample.h"

#include "SDL.h"

#include <array>

/**
 * @struct CelestialBody is a struct that represent a celestial body with a reference to a body in the world,
 * a radius and a color to represent the object graphically with a circle.
 */
struct CelestialBody
{
    PhysicsEngine::BodyRef BodyRef;
    // In Pixels
    float Radius;
    SDL_Color Color;
};

class PlanetSystemSample final : public Sample
{
private:
    std::vector<CelestialBody> _planets{};
    CelestialBody _sun{};

    bool _mustCreatePlanet = false;

    /**
     * @brief createPlanet is a method that creates a CelestialBody representing a planet 
     * (see CelestialBody struct).
     * @param pos The position of the planet.
     * @param radius The radius of the planet.
     * @param color The color of the planet.
     * @return The CelestialBody object representing the planet.
     */
    [[nodiscard]] CelestialBody createPlanet(Math::Vec2F pos, float radius, SDL_Color color) noexcept;

    /**
     * @brief calculatePlanetMovements is a method that calculate the gravitational force between
     * the sun and each planet.
     */
    void calculatePlanetMovements() noexcept;

public:
    /**
     * @brief The gravitational constant for the physical world of the planet system.
     */
    static constexpr float G = 0.0667f;

    /**
     * @brief The number of planet at the start of the sample.
     */
    static constexpr std::size_t StartPlanetNbr = 200;

    PlanetSystemSample() noexcept = default;

    // Inherited via Sample
    std::string Name() const noexcept override { return "Planet System"; }
    std::string Description() const noexcept override;
    std::string InputText() const noexcept override;

    /**
     * @brief Init is a method that initializes the planet system sample (aka instantiates the sun and all the planets).
     * @note The planet bodies are instantiated with an orbital velocity in order to create the orbital movement around
     * the sun.
     */
    void onInit() noexcept override;

    /**
     * @brief HandleInputs is a method that performs the different action of the sample
     * according to the inputs.
     * @param event The SDL event that contains the input data.
     */
    void onHandleInputs(SDL_Event event, bool isMouseOnAnImGuiWindow) noexcept override;

    /**
     * @brief onUpdate is a method that updates the sample. 
     * More specifically, it creates planets if the left mouse button is pressed and calculates
     * the gravitational force to apply to each planet.
     */
    void onUpdate() noexcept override;

    void onRender() noexcept override;

    /**
     * @brief onDeinit is a method that deinitializes the sample (aka clear all the celestial bodies).
     */
    void onDeinit() noexcept override;
};