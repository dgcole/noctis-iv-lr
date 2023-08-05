#ifndef ONSHIPSCREEN_H
#define ONSHIPSCREEN_H

#include <cstddef>
#include <cstdint>
#include <array>
#include <string>

class OnShipScreen
{
public:
    static constexpr size_t WIDTH  = 21;
    static constexpr size_t HEIGHT =  7;
    static constexpr size_t SCREEN_SIZE = WIDTH * HEIGHT;

    std::array<char, SCREEN_SIZE> screen;
    size_t cursor = 0;

    bool text_wrapping = false;

    OnShipScreen();

    /* Cursor Positioning */

    void set_cursor(size_t exact_position);
    void set_cursor(size_t x, size_t y);

    void move_cursor(int8_t direction, size_t n);

    void cursor_newline();



    /* Text Write Operations */

    // Exact placement of character
    void put_char(char c);
    void put_char(size_t x, size_t y, char c);

    // Exact placement of text
    void put_line(size_t line_number, std::string_view &text);
    void put_line(size_t line_number, std::string &text);
    void put_line(size_t line_number, char * text);

    // Write text at current cursor position
    void set_text_wrapping(bool do_wrapping);
    void write(const std::string_view &text);
    void write(const std::string &text);
    void write(const char * text);


    /* Text Read Operations */
    const std::string_view get_char(size_t position);
    const std::string_view get_line(size_t line_number);
    const std::string_view get_slice(size_t start, size_t end);
    const std::string_view get_full_text();
};

#endif ONSHIPSCREEN_H