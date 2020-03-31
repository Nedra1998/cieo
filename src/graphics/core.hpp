#ifndef GRAPHICS_CORE_HPP_
#define GRAPHICS_CORE_HPP_

#include <string>

#include <glm/glm.hpp>

namespace graphics {
/**
 * @brief Opens a new window
 *
 * This opens a new window, and must be called before all other graphics calls,
 * and it can only be called once.
 *
 * @param name The name of the window to create.
 * @param w The width of the window
 * @param h The height of the window
 *
 * @return `true` if the window was successfully created, `false` otherwise.
 */
bool open(const std::string &name, const std::size_t &w = 500,
          const std::size_t &h = 500);
/**
 * @brief Closes the window
 *
 * Thus should be called at the end of the program, but is not neccessary
 *
 * @return Always returns `true`.
 */
bool close();

/**
 * @brief Sets the background color
 *
 * @param color The `rgb` value of the color.
 */
void clear_rgb(const glm::vec3 &color);
/**
 * @brief Sets the view matrix
 *
 * @param pos Position of the observer
 * @param look The point that the observer is looking at.
 * @param up The direction to consier up.
 */
void set_view(const glm::vec3 &pos, const glm::vec3 &look, const glm::vec3 &up);
/**
 * @brief Sets the projection matrix
 *
 * @param fov Field of view in degrees.
 */
void set_fov(const float &fov);
/**
 * @brief Sets the light parameters for the shading
 *
 * @param pos The position of the light in `xyz` coordinates.
 * @param color The color of the light in `rgb` components.
 */
void set_light(const glm::vec3 &pos, const glm::vec3 &color);

/**
 * @brief Checks if the window is currently open
 *
 * @return `true` if the window is open, `false` otherwise.
 */
bool is_open();
/**
 * @brief Sets the window to close when possible
 */
void should_close();
/**
 * @brief Updates the window content. This should be called exactly once per
 * frame.
 *
 * @return Always returns `true`
 */
bool update();

/**
 * @brief Determins is key or mouse button is currently pressed
 *
 * @param int Key/Mouse button to check
 *
 * @return `true` if the key or button is being pressed.
 */
bool is_pressed(unsigned int);
} // namespace graphics

#endif // GRAPHICS_CORE_HPP_
