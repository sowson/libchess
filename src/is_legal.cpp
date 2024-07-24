#include <algorithm>
#include <ranges>
#include "libchess/position.hpp"

namespace libchess {

[[nodiscard]] bool Position::is_legal(const Move &m) const noexcept {
    const auto moves = legal_moves();
    return std::any_of(moves.begin(), moves.end(), [m](const auto &move) {
        return move == m;
    });
}

}  // namespace libchess
