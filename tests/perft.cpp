#include <array>
#include <cstdint>
#include <libchess/position.hpp>
#include <string>
#include <vector>
#include "catch.hpp"

using pair_type = std::pair<std::string, std::vector<std::uint64_t>>;

TEST_CASE("Position::perft()") {
    const std::array<pair_type, 8> positions = {{
        {"startpos", {1, 20, 400, 8902}},
        {"8/4k3/8/8/8/8/4K3/8 w - - 0 1", {1, 8}},
        {"7k/8/8/8/8/4B3/8/7K w - - 0 1", {1, 14}},
        {"7k/8/8/8/8/4N3/8/7K w - - 0 1", {1, 11}},
        {"4k3/4r3/8/8/8/3p4/4P3/4K3 w - - 0 1", {1, 6}},
        {"4k3/4r3/8/8/8/8/3p4/4K3 w - - 0 2", {1, 4}},
        {"4k3/8/8/8/8/8/1r4K1/5b2 w - - 0 2", {1, 5}},
        {"4k3/2b3q1/3P1P2/4K3/3P1P2/2b3q1/8/8 w - - 0 1", {1, 6}},
    }};

    for (const auto &[fen, nodes] : positions) {
        INFO(fen);
        libchess::Position pos{fen};
        for (std::size_t i = 0; i < nodes.size(); ++i) {
            REQUIRE(pos.perft(i) == nodes[i]);
        }
    }
}

TEST_CASE("En passant -- Diagonal pin") {
    const std::array<pair_type, 12> positions = {{
        {"4k3/b7/8/2Pp4/8/8/8/6K1 w - d6 0 2", {1, 5}},
        {"4k3/7b/8/4pP2/8/8/8/1K6 w - e6 0 2", {1, 5}},
        {"6k1/8/8/8/2pP4/8/B7/3K4 b - d3 0 2", {1, 5}},
        {"1k6/8/8/8/4Pp2/8/7B/4K3 b - e3 0 2", {1, 5}},
        {"4k3/b7/8/1pP5/8/8/8/6K1 w - b6 0 2", {1, 6}},
        {"4k3/7b/8/5Pp1/8/8/8/1K6 w - g6 0 2", {1, 6}},
        {"6k1/8/8/8/1Pp5/8/B7/4K3 b - b3 0 2", {1, 6}},
        {"1k6/8/8/8/5pP1/8/7B/4K3 b - g3 0 2", {1, 6}},
        {"4k3/K7/8/1pP5/8/8/8/6b1 w - b6 0 2", {1, 6}},
        {"4k3/7K/8/5Pp1/8/8/8/1b6 w - g6 0 2", {1, 6}},
        {"6B1/8/8/8/1Pp5/8/k7/4K3 b - b3 0 2", {1, 6}},
        {"1B6/8/8/8/5pP1/8/7k/4K3 b - g3 0 2", {1, 6}},
    }};

    for (const auto &[fen, nodes] : positions) {
        INFO(fen);
        libchess::Position pos{fen};
        for (std::size_t i = 0; i < nodes.size(); ++i) {
            REQUIRE(pos.perft(i) == nodes[i]);
        }
    }
}

TEST_CASE("En passant -- Horizontal pin") {
    const std::array<pair_type, 4> positions = {{
        {"4k3/8/8/K2pP2r/8/8/8/8 w - d6 0 1", {1, 6}},
        {"4k3/8/8/r2pP2K/8/8/8/8 w - d6 0 1", {1, 6}},
        {"8/8/8/8/1k1Pp2R/8/8/4K3 b - d3 0 1", {1, 8}},
        {"8/8/8/8/1R1Pp2k/8/8/4K3 b - d3 0 1", {1, 6}},
    }};

    for (const auto &[fen, nodes] : positions) {
        INFO(fen);
        libchess::Position pos{fen};
        for (std::size_t i = 0; i < nodes.size(); ++i) {
            REQUIRE(pos.perft(i) == nodes[i]);
        }
    }
}

TEST_CASE("En passant -- Vertical pin") {
    const std::array<pair_type, 2> positions = {{
        {"k7/8/4r3/3pP3/8/8/8/4K3 w - d6 0 1", {1, 5}},
        {"k3K3/8/8/3pP3/8/8/8/4r3 w - d6 0 1", {1, 6}},
    }};

    for (const auto &[fen, nodes] : positions) {
        INFO(fen);
        libchess::Position pos{fen};
        for (std::size_t i = 0; i < nodes.size(); ++i) {
            REQUIRE(pos.perft(i) == nodes[i]);
        }
    }
}

TEST_CASE("En passant -- Legal") {
    const std::array<pair_type, 4> positions = {{
        {"8/8/8/8/1k1PpN1R/8/8/4K3 b - d3 0 1", {1, 9, 193, 1322}},
        {"8/8/8/8/1k1Ppn1R/8/8/4K3 b - d3 0 1", {1, 17, 220, 3001}},
        {"4k3/8/8/2PpP3/8/8/8/4K3 w - d6 0 1", {1, 9, 47, 376}},
        {"4k3/8/8/8/2pPp3/8/8/4K3 b - d3 0 1", {1, 9, 47, 376}},
    }};

    for (const auto &[fen, nodes] : positions) {
        INFO(fen);
        libchess::Position pos{fen};
        for (std::size_t i = 0; i < nodes.size(); ++i) {
            REQUIRE(pos.perft(i) == nodes[i]);
        }
    }
}

TEST_CASE("En passant -- Capture checker") {
    const std::array<pair_type, 2> positions = {{
        {"4k3/8/8/4pP2/3K4/8/8/8 w - e6 0 2", {1, 9}},
        {"8/8/8/4k3/5Pp1/8/8/3K4 b - f3 0 1", {1, 9}},
    }};

    for (const auto &[fen, nodes] : positions) {
        INFO(fen);
        libchess::Position pos{fen};
        for (std::size_t i = 0; i < nodes.size(); ++i) {
            REQUIRE(pos.perft(i) == nodes[i]);
        }
    }
}

TEST_CASE("En passant -- Horizontally block check") {
    const std::array<pair_type, 1> positions = {{
        {"4k3/8/K6r/3pP3/8/8/8/8 w - d6 0 1", {1, 6}},
    }};

    for (const auto &[fen, nodes] : positions) {
        INFO(fen);
        libchess::Position pos{fen};
        for (std::size_t i = 0; i < nodes.size(); ++i) {
            REQUIRE(pos.perft(i) == nodes[i]);
        }
    }
}

TEST_CASE("Perft - Many moves") {
    INFO("Perft position with the most known moves");
    const auto pos = libchess::Position("R6R/3Q4/1Q4Q1/4Q3/2Q4Q/Q4Q2/pp1Q4/kBNN1KB1 w - - 0 1");
    const auto moves = pos.legal_moves();
    REQUIRE(moves.size() == 218);
    REQUIRE(moves.size() <= moves.capacity());
}

TEST_CASE("Perft - Shallow") {
    const std::array<pair_type, 28> tests = {{
        {"startpos", {20, 400, 8902, 197281}},
        {"4k3/b7/8/2Pp4/8/8/8/6K1 w - d6 0 2", {5}},
        {"4k3/7b/8/4pP2/8/8/8/1K6 w - e6 0 2", {5}},
        {"6k1/8/8/8/2pP4/8/B7/3K4 b - d3 0 2", {5}},
        {"1k6/8/8/8/4Pp2/8/7B/4K3 b - e3 0 2", {5}},
        {"4k3/b7/8/1pP5/8/8/8/6K1 w - b6 0 2", {6}},
        {"4k3/7b/8/5Pp1/8/8/8/1K6 w - g6 0 2", {6}},
        {"6k1/8/8/8/1Pp5/8/B7/4K3 b - b3 0 2", {6}},
        {"1k6/8/8/8/5pP1/8/7B/4K3 b - g3 0 2", {6}},
        {"4k3/K7/8/1pP5/8/8/8/6b1 w - b6 0 2", {6}},
        {"4k3/7K/8/5Pp1/8/8/8/1b6 w - g6 0 2", {6}},
        {"6B1/8/8/8/1Pp5/8/k7/4K3 b - b3 0 2", {6}},
        {"1B6/8/8/8/5pP1/8/7k/4K3 b - g3 0 2", {6}},
        {"4k3/8/8/K2pP2r/8/8/8/8 w - d6 0 1", {6}},
        {"4k3/8/8/r2pP2K/8/8/8/8 w - d6 0 1", {6}},
        {"8/8/8/8/1k1Pp2R/8/8/4K3 b - d3 0 1", {8}},
        {"8/8/8/8/1R1Pp2k/8/8/4K3 b - d3 0 1", {6}},
        {"k7/8/4r3/3pP3/8/8/8/4K3 w - d6 0 1", {5}},
        {"k3K3/8/8/3pP3/8/8/8/4r3 w - d6 0 1", {6}},
        {"8/8/8/8/1k1PpN1R/8/8/4K3 b - d3 0 1", {9, 193, 1322}},
        {"8/8/8/8/1k1Ppn1R/8/8/4K3 b - d3 0 1", {17, 220, 3001}},
        {"4k3/8/8/2PpP3/8/8/8/4K3 w - d6 0 1", {9, 47, 376}},
        {"4k3/8/8/8/2pPp3/8/8/4K3 b - d3 0 1", {9, 47, 376}},
        {"4k3/8/8/4pP2/3K4/8/8/8 w - e6 0 2", {9}},
        {"8/8/8/4k3/5Pp1/8/8/3K4 b - f3 0 1", {9}},
        {"4k3/8/K6r/3pP3/8/8/8/8 w - d6 0 1", {6}},
        {"rnb2rk1/1ppp1ppp/p7/4p1N1/1PB1Q3/3P4/PP3PPP/RN2K2R b KQ - 0 10", {15}},
        {"rnbkrbqn/p1pp1ppp/4p3/1p6/8/BPN3P1/P1PPPP1P/R2KRBQN w EAea - 2 9", {28, 667, 18886 }}
    }};

    for (const auto &[fen, nodes] : tests) {
        INFO(fen);
        auto pos = libchess::Position(fen);
        for (std::size_t i = 0; i < nodes.size(); ++i) {
            INFO("DEPTH: ");
            INFO(i);
            REQUIRE(pos.perft(i + 1) == nodes.at(i));
        }
    }
}

TEST_CASE("Perft - Custom") {
    const std::array<pair_type, 1> tests = {{
         {"rnbkrbqn/p1pp1ppp/4p3/1p6/8/BPN3P1/P1PPPP1P/R2KRBQN w EAea - 2 9", { 28, 667, 18886,	471824,	13845222, 358941665 }}
 }};

    for (const auto &[fen, nodes] : tests) {
        INFO(fen);
        auto pos = libchess::Position(fen);
        for (std::size_t i = 0; i < nodes.size(); ++i) {
            INFO("DEPTH: ");
            INFO(i);
            REQUIRE(pos.perft(i + 1) == nodes.at(i));
        }
    }
}
