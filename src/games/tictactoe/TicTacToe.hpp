#pragma once

#include <array>
#include <vector>
#include <string>
#include "engine/GameConcept.hpp"

namespace games { namespace tictactoe {
	struct TicTacToe {
		struct Move { int row{0}; int col{0}; };

		using Board = std::array<char, 9>; // 'X', 'O', ' '

		TicTacToe();
		explicit TicTacToe(const Board& b, engine::Player toMove);

		engine::Player currentPlayer() const;
		bool isTerminal() const;
		int evaluate(engine::Player perspective) const;
		std::vector<Move> generateMoves() const;
		TicTacToe applyMove(const Move& m) const;
		bool isLegal(const Move& m) const;

		std::string toString() const;

		Board board;
		engine::Player toMove;
	};
}}
