*This project has been created as part of the 42 curriculum by zabishev.*

# ft_printf

## Description

`ft_printf` is a re-implementation of the C standard library function `printf()`.
The goal of the project is to learn how variadic functions work in C
(`va_list`, `va_start`, `va_arg`, `va_end`) and to build a small, reusable
static library, `libftprintf.a`.

The function has the same prototype as the original:

```c
int	ft_printf(const char *format, ...);
```

It writes to the standard output and returns the number of characters printed,
or `-1` if `format` is `NULL`.

### Supported conversions

| Conversion | Prints |
|---|---|
| `%c` | a single character |
| `%s` | a string (`(null)` if the pointer is `NULL`) |
| `%p` | a pointer address in lowercase hexadecimal, prefixed with `0x` (`(nil)` if `NULL`) |
| `%d` | a signed decimal integer |
| `%i` | a signed decimal integer (same as `%d`) |
| `%u` | an unsigned decimal integer |
| `%x` | an unsigned hexadecimal integer, lowercase |
| `%X` | an unsigned hexadecimal integer, uppercase |
| `%%` | a literal percent sign |

As required by the subject, there is no buffer management: each character is
written immediately with `write(2)`.

## Instructions

### Build

```bash
make        # builds libftprintf.a at the root of the repository
make clean  # removes object files
make fclean # removes object files and libftprintf.a
make re     # fclean + all
```

The library is built with `cc -Wall -Wextra -Werror` and archived with `ar rcs`.

### Use

Include the header and link the library:

```c
#include "ft_printf.h"

int	main(void)
{
	int	n;

	n = 42;
	ft_printf("%s is %d years old, hex: %x, ptr: %p\n", "Bob", n, 255, &n);
	return (0);
}
```

```bash
cc main.c libftprintf.a -o demo
./demo
```

## Algorithm and data structure

### Main loop

`ft_printf` walks through `format` one character at a time with an index `i`:

1. If the character is not `%`, it is printed as is.
2. If it is `%` and the next character is `'\0'` (format ends with `%`),
   the loop stops. This prevents the index from jumping past the
   terminating `'\0'` and reading invalid memory.
3. Otherwise the character after `%` is passed to `ft_dispatcher`, and `i`
   moves forward by 2 (over `%` and the conversion letter).

Every printing function returns the number of characters it wrote, and these values are summed in `count`, which is what `ft_printf` returns.

### Dispatcher

`ft_dispatcher(char c, va_list *ap)` receives only the conversion letter and a **pointer** to the argument list. It picks the matching printing function with an `if / else if` chain and calls `va_arg` with the type the caller actually passed (`int` for `%c`, `%d`, `%i`; `unsigned int` for `%u`, `%x`, `%X`;
`char *` for `%s`; `void *` for `%p`).

The `va_list` is passed by pointer so that every call to `va_arg` advances the same list in `ft_printf`. On some platforms, such as arm64 macOS, `va_list` passed by value is a copy, and the next conversion would read the same argument again.

Splitting the work into `ft_printf` (loop) and `ft_dispatcher` (choice)
also keeps each function under the Norm's 25-line limit.

### Number printing

- **`ft_putnbr(int)`** handles `%d` and `%i`. The value is copied into a `long` before changing its sign, so `INT_MIN` (`-2147483648`) does not overflow. Digits are extracted with `% 10` and `/ 10`, stored in a small stack array (they come out in reverse order), and then printed from the end.
- **`ft_putnbr_base(size_t, char *base)`** handles `%u`, `%x`, `%X` and `%p`.
  The base is the length of the `base` string, and each digit is printed as `base[n % base_len]`. One function covers all four conversions, because only the `base` string changes: `"0123456789"`, `"0123456789abcdef"` or `"0123456789ABCDEF"`.
- **`ft_putptr(void *, char *base)`** prints `0x` and then the address, cast to `unsigned long` so the full 64-bit value is kept.

### Why these choices

- A **stack array** (`char str[20]`) instead of `malloc`: the maximum number of digits is known in advance (20 for a 64-bit unsigned value in base 10), so there is nothing to free and no allocation that can fail.
- A **loop with a buffer** instead of recursion for digits: no risk of deep call stacks, and the digit count is directly available as the return value.
- **One generic base function** instead of separate functions for decimal and hexadecimal: less code to maintain and test.

### Files

| File | Content |
|---|---|
| `ft_printf.h` | includes and prototypes |
| `ft_printf.c` | `ft_printf`, `ft_dispatcher`, `ft_print_char` |
| `ft_functions.c` | `ft_putnbr`, `ft_putnbr_base`, `ft_putstr`, `ft_putptr`, `ft_strlen` |
| `Makefile` | builds `libftprintf.a` |

## Resources

- `man 3 printf` — reference behaviour of every conversion
- `man 3 stdarg` — `va_start`, `va_arg`, `va_end`, `va_copy`
- `man 2 write`
- [cppreference: Variadic functions](https://en.cppreference.com/w/c/variadic)
- [cppreference: printf](https://en.cppreference.com/w/c/io/fprintf)
- [ASCII table](https://www.asciitable.com/)

### Use of AI

Claude (Anthropic) was used as a **tutor** during this project. All code was
written by me. The AI was used to:

- explain concepts I didn't understand yet: variadic arguments and `va_arg`.
- show mistakes that was made by me without giving the solution.
