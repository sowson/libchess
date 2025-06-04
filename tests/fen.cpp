#include <array>
#include <libchess/position.hpp>
#include <string>
#include <tuple>
#include "catch.hpp"

TEST_CASE("Position::get_fen()") {
    const std::array<std::string, 8> fens = {{
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w K - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w Q - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w k - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b q - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b - - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b Kk - 0 1",
        "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b Qq - 0 1",
    }};

    for (const auto &fen : fens) {
        INFO(fen);
        const libchess::Position pos{fen};
        REQUIRE(pos.get_fen() == fen);
    }
}

TEST_CASE("Counters") {
    using tuple_type = std::tuple<std::string, int, int>;

    const std::array<tuple_type, 15> moves = {{
        {"e2e4", 0, 1},
        {"c7c5", 0, 2},
        {"g1f3", 1, 2},
        {"d7d6", 0, 3},
        {"d2d4", 0, 3},
        {"c5d4", 0, 4},
        {"f3d4", 0, 4},
        {"g8f6", 1, 5},
        {"b1c3", 2, 5},
        {"g7g6", 0, 6},
        {"c1e3", 1, 6},
        {"f8g7", 2, 7},
        {"f1e2", 3, 7},
        {"e8g8", 4, 8},
        {"e1g1", 5, 8},
    }};

    auto pos = libchess::Position{"startpos"};
    for (const auto &[movestr, half, full] : moves) {
        INFO(movestr);
        const auto move = pos.parse_move(movestr);
        pos.makemove(move);
        REQUIRE((unsigned long)pos.halfmoves() == (unsigned long)half);
        REQUIRE((unsigned long)pos.fullmoves() == (unsigned long)full);
    }
}

TEST_CASE("FEN - Illegal castling") {
    using pair_type = std::pair<std::string, std::string>;

    const std::array<pair_type, 5> tests = {{
        {"r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1", "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"},
        {"4k2r/8/8/8/8/8/8/4K2R w KQkq - 0 1", "4k2r/8/8/8/8/8/8/4K2R w Kk - 0 1"},
        {"r3k3/8/8/8/8/8/8/R3K3 w KQkq - 0 1", "r3k3/8/8/8/8/8/8/R3K3 w Qq - 0 1"},
        {"4k3/8/8/8/8/8/8/4K3 w KQkq - 0 1", "4k3/8/8/8/8/8/8/4K3 w - - 0 1"},
        {"1b1r2r1/p1pppkp1/5p1p/3n4/1P3P2/2p5/P7/B1N1K2N w KQ - 0 17",
         "1b1r2r1/p1pppkp1/5p1p/3n4/1P3P2/2p5/P7/B1N1K2N w - - 0 17"},
    }};

    for (const auto &[fen, corrected] : tests) {
        INFO(fen);
        auto pos = libchess::Position{fen};
        CHECK(pos.get_fen() == corrected);
    }
}
