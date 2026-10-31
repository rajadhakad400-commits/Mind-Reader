// Mind Reader (C++): predicts a number 1..99 from yes/no answers over 9 screens.
// Same design as the Verilog version: 9-bit codes in a ROM, an accumulator
// register, and a 3-state FSM (IDLE -> ASK -> DONE).
//
// Build:  g++ -std=c++17 -O2 -o mind_reader mind_reader.cpp
// Play:   ./mind_reader
// Test:   ./mind_reader --test      (plays all 99 numbers automatically)

#include <array>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <string>

constexpr int BITS = 9;     // number of screens = width of the accumulator
constexpr int MAX_N = 99;   // numbers 1..99

// Code ROM: CODE_ROM[n-1] is the 9-bit code of number n (all codes unique).
constexpr std::array<uint16_t, MAX_N> CODE_ROM = {{
    0b000000000, 0b000000001, 0b000000010, 0b000000100, 0b000001000, 0b000010000,
    0b000100000, 0b001000000, 0b010000000, 0b100000000, 0b000000011, 0b000000101,
    0b000001001, 0b000010001, 0b000100001, 0b001000001, 0b010000001, 0b100000001,
    0b000000110, 0b000001010, 0b000010010, 0b000100010, 0b001000010, 0b010000010,
    0b100000010, 0b000001100, 0b000010100, 0b000100100, 0b001000100, 0b010000100,
    0b100000100, 0b000011000, 0b000101000, 0b001001000, 0b010001000, 0b100001000,
    0b000110000, 0b001010000, 0b010010000, 0b100010000, 0b001100000, 0b010100000,
    0b100100000, 0b011000000, 0b101000000, 0b110000000, 0b010101000, 0b001000101,
    0b100010010, 0b010010001, 0b101100000, 0b000001110, 0b011100000, 0b100011000,
    0b000000111, 0b001000011, 0b010100100, 0b101010000, 0b010001010, 0b100101000,
    0b000010101, 0b010000011, 0b001100100, 0b100001010, 0b001010001, 0b110001000,
    0b000110100, 0b000010011, 0b111000000, 0b000101100, 0b011001000, 0b000100110,
    0b100010001, 0b011000001, 0b100001100, 0b000110010, 0b110010000, 0b000100101,
    0b001001010, 0b001001100, 0b010100001, 0b101000010, 0b000110001, 0b010001100,
    0b100000011, 0b001110000, 0b100000110, 0b010011000, 0b010001001, 0b100100010,
    0b001010100, 0b000001101, 0b010100010, 0b001011000, 0b100110000, 0b010000101,
    0b001000110, 0b110000001, 0b000101010,
}};

class MindReader {
public:
    enum class State { IDLE, ASK, DONE };

    void start() { acc_ = 0; screen_ = 0; state_ = State::ASK; }

    // One clock step: the user answers the current screen.
    void answer(bool yes) {
        if (state_ != State::ASK) return;
        if (yes) acc_ |= static_cast<uint16_t>(1u << screen_);   // set bit k
        if (screen_ == BITS - 1) state_ = State::DONE;
        else ++screen_;
    }

    // Does the current screen show number n?  (bit `screen_` of its code)
    bool shows(int n) const {
        return state_ == State::ASK && ((CODE_ROM[n - 1] >> screen_) & 1u);
    }

    // ROM lookup: accumulator -> number (0 if no match).
    int found() const {
        if (state_ != State::DONE) return 0;
        for (int n = 1; n <= MAX_N; ++n)
            if (CODE_ROM[n - 1] == acc_) return n;
        return 0;
    }

    bool done()  const { return state_ == State::DONE; }
    bool error() const { return done() && found() == 0; }
    int  screen() const { return screen_; }
    uint16_t acc() const { return acc_; }

private:
    State    state_  = State::IDLE;
    uint16_t acc_    = 0;
    int      screen_ = 0;
};

static bool askYesNo(const std::string& prompt) {
    for (;;) {
        std::cout << prompt << " (y/n): " << std::flush;
        std::string s;
        if (!(std::cin >> s)) std::exit(0);          // input closed
        if (s == "y" || s == "Y") return true;
        if (s == "n" || s == "N") return false;
        std::cout << "Please type y or n.\n";
    }
}

static void play() {
    do {
        MindReader mr;
        std::cout << "\n=== MIND READER (9 screens) ===\n"
                  << "Think of a number from 1 to " << MAX_N
                  << ". Answer y or n for each screen.\n";
        mr.start();
        while (!mr.done()) {
            std::cout << "\nScreen " << mr.screen() + 1 << " of " << BITS << ":\n";
            int count = 0;
            for (int n = 1; n <= MAX_N; ++n)
                if (mr.shows(n)) {
                    std::cout << n << ' ';
                    if (++count % 10 == 0) std::cout << '\n';
                }
            std::cout << '\n';
            mr.answer(askYesNo("Is your number here?"));
        }
        std::cout << "\nAccumulator = " << std::bitset<BITS>(mr.acc()) << '\n';
        if (mr.error())
            std::cout << "Your answers match no number from 1 to " << MAX_N
                      << ". Check your answers!\n";
        else
            std::cout << "*** Your number is " << mr.found() << " ***\n";
    } while (askYesNo("\nPlay again?"));
    std::cout << "Bye!\n";
}

static int selfTest() {
    int errors = 0;
    for (int secret = 1; secret <= MAX_N; ++secret) {
        MindReader mr;
        mr.start();
        int count[BITS] = {0};
        while (!mr.done()) {
            for (int n = 1; n <= MAX_N; ++n) count[mr.screen()] += mr.shows(n);
            mr.answer(mr.shows(secret));      // honest user
        }
        if (mr.error() || mr.found() != secret) {
            ++errors;
            std::cout << "FAIL: secret=" << secret << " predicted=" << mr.found() << '\n';
        }
    }
    std::cout << "Numbers per screen:";
    {
        MindReader mr;
        for (int k = 0; k < BITS; ++k) {
            int c = 0;
            for (int n = 1; n <= MAX_N; ++n) c += (CODE_ROM[n - 1] >> k) & 1u;
            std::cout << ' ' << c;
        }
    }
    std::cout << '\n';
    if (errors == 0) std::cout << "ALL 99 NUMBERS PREDICTED CORRECTLY\n";
    else             std::cout << errors << " FAILURES\n";
    return errors ? 1 : 0;
}

int main(int argc, char** argv) {
    if (argc > 1 && std::string(argv[1]) == "--test") return selfTest();
    play();
    return 0;
}
