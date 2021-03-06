#ifndef __GAME_HPP__
#define __GAME_HPP__

#include "logger.hpp"
#include "controller.hpp"
#include "renderer.hpp"
#include "brick.hpp"

// unlike renderer, the game can be played on any rendering device that supports pixel rendering
// it is not limited to 8 pixels in width, it can be any number, but needs to be specified in the static data section
template <class Controller>
class game
{
public:
    game(Controller &controller, renderer &renderer) : _controller(controller),
                                                             _renderer(renderer),
                                                             _create_new_brick(true),
                                                             _current_interval(_init_fall_interval),
                                                             _points(0),
                                                             _level(0),
                                                             _lines_deleted(0),
                                                             _boost(false)
    {
        memset(_board, false, sizeof(_board));
    }

    void start()
    {
        SERIAL_PRINTLN("Starting the game");
        _renderer.clear();

        //greeting_screen();

        _lines_deleted = 0;
        _points = 0;
        _level = 0;
        _create_new_brick = true;
        _current_interval = _init_fall_interval;
        unsigned long last_fall_update = millis();

        while (create_brick())
        {
            read_user_input();
            if (process_user_input())
                render();

            unsigned long delta = millis() - last_fall_update;
            if (_boost ? delta > _boost_speed : delta > _current_interval)
            {
                last_fall_update = millis();
                fall();
                render();
            }
        }
        end_screen();
        show_score();
    }

    // const size_t _points_rules[brick::_height] = {40U, 100U, 300U, 1200U};

    // number of points depends on how many lines you delete at the same time
    static const size_t _points_rules[brick::_height]; // = {40U, 100U, 300U, 1200U};
    static constexpr size_t _level_change_diff = 10U;
    static constexpr size_t _init_fall_interval = 250U;
    static constexpr size_t _min_fall_interval = 50U;
    static constexpr size_t _speed_delta = 20U;
    static constexpr size_t _boost_speed = _min_fall_interval;

private:
    Controller &_controller;
    renderer &_renderer;
    // again -> static cuz dynamic allocation is not the greatest idea
    bool _board[renderer::_height * renderer::_width];
    bool _create_new_brick;

    size_t _current_interval;

    brick _brick;

    size_t _points;
    size_t _level;
    size_t _lines_deleted;

    bool _boost;

private:
    bool create_brick()
    {
        if (_create_new_brick)
        {
            random_brick();
            _create_new_brick = false;
            // if brick cant be in this place, it menas that the hame is over
            if (!move_brick(0, 0))
                return false;
        }
        return true;
    }

    void fall()
    {
        // fall ONE STEP down
        if (!move_brick(0, -1))
        {
            copy_brick_to_board();
            delete_full_rows();
            _boost = false;
        }
    }

    bool process_user_input()
    {
        int x_dir = 0;
        if (_controller.left())
            x_dir += 1;
        if (_controller.right())
            x_dir -= 1;
        if (_controller.down())
            _boost = true;
        if (_controller.up())
            _boost = false;

        bool something_changed = false;

        if (x_dir != 0)
            something_changed |= move_brick(x_dir, 0);
        if (_controller.button())
            something_changed |= rotate_brick();

        _controller.reset();
        return something_changed;
    }

    void read_user_input()
    {
        _controller.read_input();
    }

    void render()
    {
        for (size_t y = 0; y < renderer::_height; y++)
            for (size_t x = 0; x < renderer::_width; x++)
                if (_board[x + y * _renderer._width])
                    _renderer.render(x, y);

        for (uint8_t y = 0; y < brick::_height; y++)
            for (uint8_t x = 0; x < brick::_width; x++)
                if (_brick.pixel_at(x, y))
                    _renderer.render(_brick.x() + static_cast<int>(x), _brick.y() + static_cast<int>(y));

        _renderer.show();
    }

    void random_brick()
    {
        SERIAL_PRINTLN("Creating random brick");
        const int x = random(renderer::_width - brick::_width);
        const int y = renderer::_height - brick::_height;
        int random_number = random(brick::_models_count);
        _brick = brick(x, y, brick::_models[random_number]);
    }

    bool move_brick(int x_offset, int y_offeset)
    {
        for (uint8_t y = 0; y < brick::_height; y++)
            for (uint8_t x = 0; x < brick::_width; x++)
                if (_brick.pixel_at(x, y))
                {
                    const int new_x = _brick.x() + x + x_offset;
                    const int new_y = _brick.y() + y + y_offeset;

                    if (new_x < 0 || static_cast<size_t>(new_x) >= renderer::_width)
                        return false;
                    if (new_y < 0 || static_cast<size_t>(new_y) >= renderer::_height)
                        return false;
                    if (_board[new_x + new_y * renderer::_width])
                        return false;
                }
        _brick.move(x_offset, y_offeset);
        return true;
    }

    bool rotate_brick()
    {
        _brick.rotate_right();

        for (uint8_t y = 0; y < _brick._height; y++)
            for (int8_t x = 0; x < _brick._width; x++)
                if (_brick.pixel_at(x, y))
                {
                    // for debugging purposes
                    // if point is out of map or it collides with seomthing from board
                    // -> rotate back and return false
                    const int x_cor = _brick.x() + static_cast<int>(x);
                    const int y_cor = _brick.y() + static_cast<int>(y);
                    const int board_index = x_cor + y_cor * renderer::_width;
                    if (x_cor < 0 || static_cast<size_t>(x_cor) >= renderer::_width || y_cor < 0 || static_cast<size_t>(y_cor) > renderer::_height || _board[board_index])
                    {
                        _brick.rotate_left();
                        return false;
                    }
                }

        return true;
    }

    void copy_brick_to_board()
    {
        for (int y = 0; y < brick::_height; y++)
            for (int x = 0; x < brick::_width; x++)
                if (_brick.pixel_at(x, y))
                {
                    int x_cor = _brick.x() + x;
                    int y_cor = _brick.y() + y;
                    _board[x_cor + y_cor * renderer::_width] = true;
                }
        // after this copying we need a new brick
        _create_new_brick = true;
    }

    // TODO => MAKE LESS COPIES AND MAKE IT FASTER
    void delete_full_rows()
    {
        size_t lines_deleted = 0;
        for (size_t y = 0; y < renderer::_height; y++)
        {
            bool fullLine = true;
            for (size_t x = 0; x < renderer::_width && fullLine; x++)
            {
                if (!_board[x + y * renderer::_width])
                    fullLine = false;
            }
            if (fullLine)
            {
                for (size_t i = y * renderer::_width; i < (renderer::_height - 1) * renderer::_width; i++)
                    _board[i] = _board[i + renderer::_width];

                for (size_t i = (renderer::_height - 1) * renderer::_height; i < renderer::_height * renderer::_width; i++)
                    _board[i] = false;
                --y;
                lines_deleted++;
            }
        }
        if (lines_deleted)
        {
            _points += _points_rules[lines_deleted - 1U] * (_level + 1U);
            _lines_deleted += lines_deleted;
            if (_lines_deleted >= (_level + 1U) * _level_change_diff)
            {
                _level++;
                if (_current_interval > _min_fall_interval)
                    _current_interval -= _speed_delta;
            }

            SERIAL_PRINT("Lines deleted: ")
            SERIAL_PRINTLN_INT(lines_deleted)
            SERIAL_PRINT("Level: ")
            SERIAL_PRINTLN_INT(_level)
            SERIAL_PRINT("Lines deleted so far: ")
            SERIAL_PRINTLN_INT(_lines_deleted)
            SERIAL_PRINT("Points: ")
            SERIAL_PRINTLN_INT(_points)
        }
    }

    void greeting_screen()
    {
        _renderer.render("Hello");
    }

    void end_screen()
    {
        _renderer.render("game over");
    }

    void show_score()
    {
        char buffer[100];
        sprintf(buffer, "score %d", _points);
        _renderer.render(buffer);
    }
};

template<class Controller>
const size_t game<Controller>::_points_rules[brick::_height] = {40U, 100U, 300U, 1200U};

#endif // __GAME_HPP__