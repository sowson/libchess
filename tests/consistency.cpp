#include <array>
#include <libchess/position.hpp>
#include <string>
#include "catch.hpp"

void valid(libchess::Position &pos, const int depth) noexcept {
    REQUIRE(pos.valid());

    if (depth == 0) {
        return;
    }

    if (!pos.in_check()) {
        const auto halfmoves = pos.halfmoves();
        const auto fullmoves = pos.fullmoves();
        const auto hash = pos.hash();
        const auto turn = pos.turn();

        pos.makenull();

#ifdef NO_HASH
        REQUIRE(hash == 0);
#else
        REQUIRE(hash != pos.calculate_hash());
        REQUIRE(pos.hash() == pos.calculate_hash());
#endif

        valid(pos, depth - 1);
        pos.undonull();

        REQUIRE(halfmoves == pos.halfmoves());
        REQUIRE(fullmoves == pos.fullmoves());
        REQUIRE(hash == pos.hash());
        REQUIRE(turn == pos.turn());
    }

    const auto moves = pos.legal_moves();
    for (const auto &move : moves) {
        const auto halfmoves = pos.halfmoves();
        const auto fullmoves = pos.fullmoves();
        const auto hash = pos.hash();
        const auto turn = pos.turn();

        pos.makemove(move);

#ifdef NO_HASH
        REQUIRE(hash == 0);
#else
        REQUIRE(hash != pos.calculate_hash());
        REQUIRE(pos.hash() == pos.calculate_hash());
#endif

        valid(pos, depth - 1);
        pos.undomove();

        REQUIRE(halfmoves == pos.halfmoves());
        REQUIRE(fullmoves == pos.fullmoves());
        REQUIRE(hash == pos.hash());
        REQUIRE(turn == pos.turn());
    }
}

TEST_CASE("Consistency") {
    const std::array<std::string, 8> fens = {{
        "startpos",
        "2rq1rk1/pp1bppbp/2np1np1/8/3NP3/1BN1BP2/PPPQ2PP/2KR3R b - - 8 11",
        "2rqr1k1/pp1bppbp/3p1np1/4n3/3NP2P/1BN1BP2/PPPQ2P1/1K1R3R b - - 0 13",
        "rnbqkbnr/ppp1pppp/8/8/3pP3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 3",
        "4k3/8/4r3/3pP3/8/8/8/4K3 w - d6 0 2",
        "4k3/8/8/K2pP2r/8/8/8/8 w - d6 0 1",
        "4k3/8/7r/K2pP3/8/8/8/8 w - d6 0 1",
        "5k2/8/8/1K1Pp1r1/8/8/8/8 w - e6 0 2",
    }};

    for (const auto &fen : fens) {
        INFO(fen);
        libchess::Position pos{fen};
        valid(pos, 3);
    }
}

TEST_CASE("Consistency Corner Cases") {
    const std::array<std::string, 4> fens = {{
        "1r3k1r/1pb2p1B/p2p1p2/8/2Pp4/4q3/PP2K1b1/QRN3R1 w k - 1 28",
        "r3k1nr/2pp1ppp/4p3/8/4b2P/1P1P2P1/4P2R/1N1K2N1 b kq - 0 17",
        "7r/8/3pk2p/6P1/6r1/1K6/5b1P/5b2 b - - 2 34",
        "r1bqkbnr/pppp1ppp/2n1p3/8/3P4/PP6/2P1PPPP/RNBQKBNR b KQkq d3 0 3"
    }};

    for (const auto &fen : fens) {
        INFO(fen);
        libchess::Position pos{fen};
        valid(pos, 3);
    }
}
