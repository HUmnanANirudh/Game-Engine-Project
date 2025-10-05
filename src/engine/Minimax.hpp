#pragma once

#include <algorithm>
#include <vector>
#include <limits>
#include "engine/GameConcept.hpp"

namespace engine {
	template <typename Game>
	int minimax(const Game& state, int depth, int alpha, int beta, Player maximizingFor) {
		const bool isMaximizing = (state.currentPlayer() == maximizingFor);

		if (depth == 0 || state.isTerminal()) {
			return state.evaluate(maximizingFor);
		}

		const auto moves = state.generateMoves();
		if (moves.empty()) {
			return state.evaluate(maximizingFor);
		}

		if (isMaximizing) {
			int best = std::numeric_limits<int>::min();
			for (const auto& move : moves) {
				Game child = state.applyMove(move);
				int score = minimax(child, depth - 1, alpha, beta, maximizingFor);
				best = std::max(best, score);
				alpha = std::max(alpha, best);
				if (beta <= alpha) break; // alpha-beta prune
			}
			return best;
		} else {
			int best = std::numeric_limits<int>::max();
			for (const auto& move : moves) {
				Game child = state.applyMove(move);
				int score = minimax(child, depth - 1, alpha, beta, maximizingFor);
				best = std::min(best, score);
				beta = std::min(beta, best);
				if (beta <= alpha) break; // alpha-beta prune
			}
			return best;
		}
	}

	template <typename Game>
	typename Game::Move findBestMove(const Game& state, int depth, Player maximizingFor) {
		const bool isMaximizing = (state.currentPlayer() == maximizingFor);
		const auto moves = state.generateMoves();
		// Fallback in case no move exists; caller should ensure non-terminal
		if (moves.empty()) return typename Game::Move{};

		int bestScore = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
		typename Game::Move bestMove = moves.front();
		int alpha = std::numeric_limits<int>::min();
		int beta = std::numeric_limits<int>::max();

		for (const auto& move : moves) {
			Game child = state.applyMove(move);
			int score = minimax(child, depth - 1, alpha, beta, maximizingFor);
			if (isMaximizing) {
				if (score > bestScore) { bestScore = score; bestMove = move; }
				alpha = std::max(alpha, bestScore);
			} else {
				if (score < bestScore) { bestScore = score; bestMove = move; }
				beta = std::min(beta, bestScore);
			}
			if (beta <= alpha) break;
		}
		return bestMove;
	}
}
