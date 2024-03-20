#pragma once

#include "go.h"
#include <string>

namespace minizero::env::atarigo {

const std::string kAtariGoName = "atarigo";
const int kAtariGoNumPlayer = 2;
const int kAtariGoBoardSize = 7;

typedef go::GoAction AtariGoAction;

class AtariGoEnv : public go::GoEnv {
public:
    AtariGoEnv() : go::GoEnv()
    {
        assert(kAtariGoBoardSize == minizero::config::env_board_size);
        is_eat_stone = false;
    }

    // bool isLegalAction(const AtariGoAction& action) const override
    // {
    //     if (actions_.size() == 1) { return isPassAction(action); }
    //     if (actions_.size() < 3) { return !isPassAction(action) && go::GoEnv::isLegalAction(action); }
    //     return go::GoEnv::isLegalAction(action);
    // }

    bool isTerminal() const override
    {
        // all black's benson or any white's benson
        // if (benson_bitboard_.get(Player::kPlayer1).count() == board_size_ * board_size_ || benson_bitboard_.get(Player::kPlayer2).count() > 0)
        //     return true;
        if (is_eat_stone) return true;
        return go::GoEnv::isTerminal();
    }

    float getEvalScore(bool is_resign = false) const override
    {
        if (is_eat_stone && turn_ == Player::kPlayer1)
            return -1.0f; // white win
        else if (is_eat_stone && turn_ == Player::kPlayer2)
            return 1.0f; // black win
        else
            return 0.0f;
        // if (stone_bitboard_.get(Player::kPlayer2).count() == 0 || benson_bitboard_.get(Player::kPlayer1).count() == board_size_ * board_size_)
        //     return 1.0f; // player1 wins
        // else
        //     return -1.0f; // player2 wins
    }

    inline std::string name() const override { return kAtariGoName + "_" + std::to_string(board_size_) + "x" + std::to_string(board_size_); }
    inline int getNumPlayer() const override { return kAtariGoNumPlayer; }
};

class AtariGoEnvLoader : public go::GoEnvLoader {
public:
    inline std::string name() const override { return kAtariGoName + "_" + std::to_string(getBoardSize()) + "x" + std::to_string(getBoardSize()); }
};

} // namespace minizero::env::atarigo
