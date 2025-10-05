#include "games/tictactoe/TicTacToe.hpp"

#include <cassert>

namespace games { namespace tictactoe {
	static inline int idx(int r, int c) { return r * 3 + c; }

	TicTacToe::TicTacToe() : board{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }, toMove(engine::Player::X) {}

	TicTacToe::TicTacToe(const Board& b, engine::Player tm) : board(b), toMove(tm) {}

	engine::Player TicTacToe::currentPlayer() const { return toMove; }

	static int lineWinner(const TicTacToe::Board& b) {
		static const int lines[8][3] = {
			{0,1,2},{3,4,5},{6,7,8}, // rows
			{0,3,6},{1,4,7},{2,5,8}, // cols
			{0,4,8},{2,4,6}          // diags
		};
		for (const auto& ln : lines) {
			char a = b[ln[0]], c = b[ln[1]], d = b[ln[2]];
			if (a != ' ' && a == c && c == d) {
				return a == 'X' ? +1 : -1;
			}
		}
		return 0;
	}

	bool TicTacToe::isTerminal() const {
		if (lineWinner(board) != 0) return true;
		for (char cell : board) if (cell == ' ') return false;
		return true; // draw
	}

	int TicTacToe::evaluate(engine::Player perspective) const {
		int w = lineWinner(board);
		if (w != 0) {
			int score = (w > 0) ? 100 : -100; // X win = +100, O win = -100
			if (perspective == engine::Player::X) return score;
			return -score;
		}
    // If the board is full and no line winner, it's a draw: score 0 for everyone
    bool anyEmpty = false;
    for (char cell : board) {
        if (cell == ' ') { anyEmpty = true; break; }
    }
    if (!anyEmpty) {
        return 0;
    }
		// Non-terminal heuristic: small preference for center and corners if available
		int heuristic = 0;
		if (board[4] == 'X') heuristic += 3; else if (board[4] == 'O') heuristic -= 3;
		for (int i : {0,2,6,8}) {
			if (board[i] == 'X') heuristic += 2; else if (board[i] == 'O') heuristic -= 2;
		}
		return (perspective == engine::Player::X) ? heuristic : -heuristic;
	}

	std::vector<TicTacToe::Move> TicTacToe::generateMoves() const {
		std::vector<Move> moves;
		moves.reserve(9);
		if (isTerminal()) return moves;
		for (int r = 0; r < 3; ++r) {
			for (int c = 0; c < 3; ++c) {
				if (board[idx(r,c)] == ' ') moves.push_back({r,c});
			}
		}
		return moves;
	}

	bool TicTacToe::isLegal(const Move& m) const {
		if (m.row < 0 || m.row >= 3 || m.col < 0 || m.col >= 3) return false;
		if (isTerminal()) return false;
		return board[idx(m.row, m.col)] == ' ';
	}

	TicTacToe TicTacToe::applyMove(const Move& m) const {
		assert(isLegal(m));
		TicTacToe next = *this;
		char mark = (toMove == engine::Player::X) ? 'X' : 'O';
		next.board[idx(m.row, m.col)] = mark;
		next.toMove = (toMove == engine::Player::X) ? engine::Player::O : engine::Player::X;
		return next;
	}

	std::string TicTacToe::toString() const {
		std::string s;
		s.reserve(3*3 + 6);
		for (int r = 0; r < 3; ++r) {
			for (int c = 0; c < 3; ++c) {
				char ch = board[idx(r,c)];
				s.push_back(ch == ' ' ? '.' : ch);
			}
			if (r != 2) s.append("\n");
		}
		return s;
	}
}}
