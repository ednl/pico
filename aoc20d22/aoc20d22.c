#include <stdio.h>        // printf
#include <string.h>       // memcpy
#include "pico/stdlib.h"  // stdio_init, sleep_ms

// Test
// const unsigned char player1[] = {9, 2, 6, 3, 1};
// const unsigned char player2[] = {5, 8, 4, 7, 10};

// Puzzle
static const unsigned char player1[] = {28, 50, 9, 11, 4, 45, 19, 26, 42, 43, 31, 46, 21, 40, 33, 20, 7, 6, 17, 44, 5, 39, 35, 27, 10};
static const unsigned char player2[] = {18, 16, 29, 41, 14, 12, 30, 37, 36, 24, 48, 38, 47, 34, 15, 8, 49, 23, 1, 3, 32, 25, 22, 13, 2};

// Yes, compiler, these *are* constant
//static const size_t P1_SIZE = sizeof player1 / sizeof *player1;
//static const size_t P2_SIZE = sizeof player2 / sizeof *player2;
//static const size_t MAXSIZE = P1_SIZE + P2_SIZE;

// OK gcc7 Pico compiler, these are the constants you want
#define P1_SIZE 25
#define P2_SIZE 25
#define MAXSIZE 50

// A deck is a stack of cards + index to the first card + size of the stack
typedef struct {
    unsigned char card[MAXSIZE];
    size_t head;
    size_t size;
} DECK, *PDECK;

// Score of a deck (also a fairly good state identifier)
// calculate from bottom: 1 * value1 + 2 * value2 + 3 * value3 + ... + size * valueSize
static unsigned int score(PDECK pd)
{
    unsigned int id = 0;
    size_t head = pd->head;
    size_t size = pd->size;

    while (size) {
        id += size-- * pd->card[head++];
        if (head == MAXSIZE) {
            head = 0;
        }
    }
    return id;
}

int main(void)
{
    uint64_t t0, t;
    size_t i, winner;
    unsigned int rounds, part1;
    unsigned char draw[2];
    DECK game[2];  // a game is 2 decks

    // Pico init
    stdio_init_all();

    while (1) {
        // Get clock ticks at start
        t0 = time_us_64();

        // Init game
        memcpy(game[0].card, player1, P1_SIZE);
        game[0].head = 0;
        game[0].size = P1_SIZE;
        memcpy(game[1].card, player2, P2_SIZE);
        game[1].head = 0;
        game[1].size = P2_SIZE;

        // Play game
        rounds = 0;
        while (game[0].size && game[1].size) {

            // Draw 1 card from top of each deck
            for (i = 0; i < 2; ++i) {
                draw[i] = game[i].card[game[i].head++];
                if (game[i].head == MAXSIZE) {
                    game[i].head = 0;
                }
                game[i].size--;
            }

            // Determine round winner from card values
            // true = 1 = player 1 wins, false = 0 = player 0 wins
            winner = draw[1] > draw[0];

            // Move 2 cards to bottom of winner's deck, highest first
            for (i = 0; i < 2; ++i) {
                game[winner].card[(game[winner].head + game[winner].size++) % MAXSIZE] = draw[(winner + i) % 2];
            }

            ++rounds;
        }

        // Determine game winner from deck size
        // true = 1 = player 1 wins, false = 0 = player 0 wins
        winner = game[0].size == 0;

        // Calculate result for part 1, get elapsed time
        // Print result and time if min or max
        part1 = score(&game[winner]);
        t = time_us_64() - t0;
        printf("%zu %u %u %lu\n", winner, rounds, part1, t);
        sleep_ms(1000);
    }
    return 0;
}
