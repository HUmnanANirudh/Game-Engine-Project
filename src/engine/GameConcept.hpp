#pragma once

#include <vector>
#include <limits>

namespace engine {
	enum class Player { X, O };

	// Minimal interface a Game must provide to use the Minimax engine.
	//
	// struct Game {
	// 	using Move = ...;
	// 	Player currentPlayer() const;
	// 	bool isTerminal() const;
	// 	int evaluate(Player perspective) const; // + good for perspective, - bad
	// 	std::vector<Move> generateMoves() const;
	// 	Game applyMove(const Move& m) const; // returns new state
	// };
}
