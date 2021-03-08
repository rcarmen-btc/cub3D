#ifndef KEYCODES_H
# define KEYCODES_H
# include <stdint.h>

# ifdef __MACH__
# define MLX_KEYS_OS            1
# else
# define MLX_KEYS_OS            0
# endif

# define MLX_MOUSE_PRESSED      0
# define MLX_MOUSE_X_COORD      1
# define MLX_MOUSE_Y_COORD      2

# define MLX_MOUSE_CLICK_LEFT   1
# define MLX_MOUSE_CLICK_MIDDLE 2
# define MLX_MOUSE_CLICK_RIGHT  3
# define MLX_MOUSE_SCROLL_UP    4
# define MLX_MOUSE_SCROLL_DOWN  5
# define MLX_MOUSE_SCROLL_RIGHT 6
# define MLX_MOUSE_SCROLL_LEFT  7
# define MLX_MOUSE_SIDE_ONE     8
# define MLX_MOUSE_SIDE_TWO     9

# define MLX_KEY_A              (MLX_KEYS_OS ? 0 : (uint8_t)'a')
# define MLX_KEY_S              (MLX_KEYS_OS ? 1 : (uint8_t)'s')
# define MLX_KEY_D              (MLX_KEYS_OS ? 2 : (uint8_t)'d')
# define MLX_KEY_F              (MLX_KEYS_OS ? 3 : (uint8_t)'f')
# define MLX_KEY_H              (MLX_KEYS_OS ? 4 : (uint8_t)'h')
# define MLX_KEY_G              (MLX_KEYS_OS ? 5 : (uint8_t)'g')
# define MLX_KEY_Z              (MLX_KEYS_OS ? 6 : (uint8_t)'z')
# define MLX_KEY_X              (MLX_KEYS_OS ? 7 : (uint8_t)'x')
# define MLX_KEY_C              (MLX_KEYS_OS ? 8 : (uint8_t)'c')
# define MLX_KEY_V              (MLX_KEYS_OS ? 9 : (uint8_t)'v')
# define MLX_KEY_B              (MLX_KEYS_OS ? 11 : (uint8_t)'b')
# define MLX_KEY_Q              (MLX_KEYS_OS ? 12 : (uint8_t)'q')
# define MLX_KEY_W              (MLX_KEYS_OS ? 13 : (uint8_t)'w')
# define MLX_KEY_E              (MLX_KEYS_OS ? 14 : (uint8_t)'e')
# define MLX_KEY_R              (MLX_KEYS_OS ? 15 : (uint8_t)'r')
# define MLX_KEY_Y              (MLX_KEYS_OS ? 16 : (uint8_t)'y')
# define MLX_KEY_T              (MLX_KEYS_OS ? 17 : (uint8_t)'t')
# define MLX_KEY_O              (MLX_KEYS_OS ? 31 : (uint8_t)'o')
# define MLX_KEY_U              (MLX_KEYS_OS ? 32 : (uint8_t)'u')
# define MLX_KEY_I              (MLX_KEYS_OS ? 34 : (uint8_t)'i')
# define MLX_KEY_P              (MLX_KEYS_OS ? 35 : (uint8_t)'p')
# define MLX_KEY_L              (MLX_KEYS_OS ? 37 : (uint8_t)'l')
# define MLX_KEY_J              (MLX_KEYS_OS ? 38 : (uint8_t)'j')
# define MLX_KEY_K              (MLX_KEYS_OS ? 40 : (uint8_t)'k')
# define MLX_KEY_N              (MLX_KEYS_OS ? 45 : (uint8_t)'n')
# define MLX_KEY_M              (MLX_KEYS_OS ? 46 : (uint8_t)'m')


# define MLX_KEY_ONE            (MLX_KEYS_OS ? 18 : (uint8_t)'1')
# define MLX_KEY_TWO            (MLX_KEYS_OS ? 19 : (uint8_t)'2')
# define MLX_KEY_THREE          (MLX_KEYS_OS ? 20 : (uint8_t)'3')
# define MLX_KEY_FOUR           (MLX_KEYS_OS ? 21 : (uint8_t)'4')
# define MLX_KEY_SIX            (MLX_KEYS_OS ? 22 : (uint8_t)'6')
# define MLX_KEY_FIVE           (MLX_KEYS_OS ? 23 : (uint8_t)'5')
# define MLX_KEY_NINE           (MLX_KEYS_OS ? 25 : (uint8_t)'9')
# define MLX_KEY_SEVEN          (MLX_KEYS_OS ? 26 : (uint8_t)'7')
# define MLX_KEY_EIGHT          (MLX_KEYS_OS ? 28 : (uint8_t)'8')
# define MLX_KEY_ZERO           (MLX_KEYS_OS ? 29 : (uint8_t)'0')
# define MLX_KEY_BRACE_L        (MLX_KEYS_OS ? 33 : (uint8_t)'[')
# define MLX_KEY_BRACE_R        (MLX_KEYS_OS ? 30 : (uint8_t)']')
# define MLX_KEY_SEMI           (MLX_KEYS_OS ? 41 : (uint8_t)',')
# define MLX_KEY_PLUS           (MLX_KEYS_OS ? 69 : (uint8_t)'+')
# define MLX_KEY_MINUS          (MLX_KEYS_OS ? 78 : (uint8_t)'-')

# define MLX_KEY_LEFT           (MLX_KEYS_OS ? 123 : 65361)
# define MLX_KEY_RIGHT          (MLX_KEYS_OS ? 124 : 65363)
# define MLX_KEY_DOWN           (MLX_KEYS_OS ? 125 : 65364)
# define MLX_KEY_UP             (MLX_KEYS_OS ? 126 : 65362)

# define MLX_KEY_CTRL_L         (MLX_KEYS_OS ? 11111 : 65507)
# define MLX_KEY_CTRL_R         (MLX_KEYS_OS ? 11111 : 65508)

# define MLX_KEY_ALT_L          (MLX_KEYS_OS ? 11111 : 65513)
# define MLX_KEY_ALT_R          (MLX_KEYS_OS ? 11111 : 65514)

# define MLX_KEY_SHIFT_L        (MLX_KEYS_OS ? 11111 : 65505)
# define MLX_KEY_SHIFT_R        (MLX_KEYS_OS ? 11111 : 65506)

# define MLX_KEY_CAPSLOCK       (MLX_KEYS_OS ? 11111 : 65509)

# define MLX_KEY_BACKSPACE      (MLX_KEYS_OS ? 11111 : 65288)
# define MLX_KEY_DELETE         (MLX_KEYS_OS ? 11111 : 65535)
# define MLX_KEY_ESCAPE         (MLX_KEYS_OS ? 11111 : 65307)

# define MLX_KEY_TAB            (MLX_KEYS_OS ? 48 : 65289)
# define MLX_KEY_SPACE          (MLX_KEYS_OS ? 11111 : 32)
# define MLX_KEY_ENTER          (MLX_KEYS_OS ? 11111 : 65293)
#endif