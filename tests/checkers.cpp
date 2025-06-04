#include <array>
#include <cstdint>
#include <libchess/position.hpp>
#include <string>
#include "catch.hpp"

TEST_CASE("Position::checkers()") {
    using pair_type = std::pair<std::string, std::uint64_t>;

    const std::array<pair_type, 2> positions = {{
        {"startpos", 0x0},
        {"k7/3r4/3Pn3/2p1p3/1r1K3q/8/1Pn5/b5b1 w - - 0 1", 0x101482000440},
    }};

    for (const auto &[fen, checkers] : positions) {
        INFO(fen);
        const libchess::Position pos{fen};
        REQUIRE(pos.checkers() == libchess::Bitboard(checkers));
    }
}

TEST_CASE("Position::legal_moves().size()") {
    using pair_type = std::pair<std::string, std::uint64_t>;

    const std::array<pair_type, 2> positions = {{
        {"startpos", 20},
        {"1r3k1r/1pb2p1B/p2p1p2/8/2Pp4/4q3/PP2K1b1/QRN3R1 w k - 1 28", 1},
    }};

    for (const auto &[fen, checkers] : positions) {
        INFO(fen);
        const libchess::Position pos{fen};
        REQUIRE(pos.legal_moves().size() == checkers);
    }
}
