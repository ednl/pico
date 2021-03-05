#include <stdio.h>   // getline
#include <stdlib.h>  // malloc, free
#include <string.h>  // memset
#include <time.h>
#include <stdint.h>
#include "pico/stdlib.h"  // stdio_init, sleep_ms
#include "day24-input.h"  // char puzzle[][]

// Puzzle input file name not used
// static const char *inp = "input24.txt";
static const int turns = 100;

// Parsed input
static signed char *tile;
static int lines = 0;

// Hexagonal grid, max size to be determined
static unsigned char *grid = NULL;
static int origx = 0, origy = 0, width = 0, height = 0, gridsize = 0;

// Start or stop a timer
static double timer(void)
{
    static bool start = true;
    // static struct timespec t0;
    // struct timespec t1;
    static uint64_t t0;
    uint64_t t;

    if (start) {
        start = false;
        // clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
        t0 = time_us_64();
        return 0;
    } else {
        // clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
        t = time_us_64();
        start = true;
        // return 1.0 * t1.tv_sec + 1e-9 * t1.tv_nsec - (1.0 * t0.tv_sec + 1e-9 * t0.tv_nsec);
        return (t - t0) * 1e-6;
    }
}

static int countlines(void)
{
    return (int)(sizeof puzzle / sizeof *puzzle);
}

static void parseline(const char * const s, int * const dx, int * const dy)
{
    const char *c = s;
    int x = 0, y = 0;

    while (*c) {
        if (*c == 'e') {
            ++x;                  // E
        } else if (*c == 'w') {
            --x;                  // W
        } else if (*c == 'n') {
            --y;                  // NW
            if (*(++c) == 'e') {
                ++x;              // NE
            }
        } else if (*c == 's') {
            ++y;                  // SE
            if (*(++c) == 'w') {
                --x;              // SW
            }
        }
        ++c;
    }
    *dx = x;
    *dy = y;
}

static void getdims(void)
{
    int i, x, y, minx = 0, maxx = 0, miny = 0, maxy = 0;

    for (i = 0; i < sizeof puzzle / sizeof *puzzle; ++i) {
        parseline(puzzle[i], &x, &y);
        tile[i * 2    ] = (signed char)x;
        tile[i * 2 + 1] = (signed char)y;
        if (x < minx) {
            minx = x;
        } else if (x > maxx) {
            maxx = x;
        }
        if (y < miny) {
            miny = y;
        } else if (y > maxy) {
            maxy = y;
        }
    }
    // Include border of zeros
    origx = turns - minx + 1;
    origy = turns - miny + 1;
    width = turns * 2 + maxx - minx + 3;
    height = turns * 2 + maxy - miny + 3;
    gridsize = width * height;
}

static inline int ix(int x, int y)
{
    return width * y + x;
}

static int blacktiles(void)
{
    int i, n = 0;

    for (i = 0; i < gridsize; ++i) {
        n += grid[i];
    }
    return n;
}

static void part1(void)
{
    for (int i = 0; i < lines * 2; i += 2) {
        grid[ix(origx + tile[i], origy + tile[i + 1])] ^= 1;
    }
}

static void part2(void)
{
    int x, y, i, j, n;
    unsigned char t, *grid2, *a, *b, *tmp;

    grid2 = malloc((size_t)gridsize * sizeof *grid);
    memset(grid2, 0, gridsize);
    a = grid;
    b = grid2;
    for (i = turns; i >= 1; --i) {
        // Use turn counter as reach limiter
        for (y = i; y < height - i; ++y) {
            for (x = i; x < width - i; ++x) {
                j = ix(x, y);
                t = a[j];
                n  = a[ix(x + 1, y    )];  // E
                n += a[ix(x - 1, y    )];  // W
                n += a[ix(x + 1, y - 1)];  // NE
                n += a[ix(x    , y - 1)];  // NW
                n += a[ix(x    , y + 1)];  // SE
                n += a[ix(x - 1, y + 1)];  // SW
                if (t == 0 && n == 2) {
                    b[j] = 1;
                } else if (t == 1 && (n == 0 || n > 2)) {
                    b[j] = 0;
                } else {
                    b[j] = t;
                }
            }
        }
        tmp = a;
        a = b;
        b = tmp;
    }
    free(grid2);
}

void main(void)
{
    // Pico init
    stdio_init_all();

    while (true) {
        sleep_ms(4000);  // sleep at start to give terminal connection some time
        timer();

        lines = countlines();
        tile = malloc((size_t)(lines * 2) * sizeof *tile);
        getdims();
        grid = malloc((size_t)gridsize * sizeof *grid);
        memset(grid, 0, gridsize);

        part1();
        printf("Part 1: %d\n", blacktiles());
        free(tile);

        part2();
        printf("Part 2: %d\n", blacktiles());
        free(grid);

        printf("Time: %.5f s\n\n", timer());
    }
}
