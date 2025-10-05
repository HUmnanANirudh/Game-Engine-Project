#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include "games/tictactoe/TicTacToe.hpp"
#include "engine/Minimax.hpp"

using engine::Player;
using games::tictactoe::TicTacToe;

static bool readMovePair(int& row, int& col) {
	std::string line;
	if (!std::getline(std::cin, line)) return false;
	std::istringstream iss(line);
	int r, c;
	if (!(iss >> r >> c)) return false;
	row = r; col = c;
	return true;
}

int main() {
	TicTacToe state;
	std::cout << "Play as X or O? (X goes first): ";
	char who; std::cin >> who; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	Player human = (who == 'O' || who == 'o') ? Player::O : Player::X;
	Player ai = (human == Player::X) ? Player::O : Player::X;

	while (!state.isTerminal()) {
		std::cout << "\nBoard:\n" << state.toString() << "\n\n";
		if (state.currentPlayer() == human) {
			auto legal = state.generateMoves();
			std::cout << "Legal moves: ";
			for (size_t i = 0; i < legal.size(); ++i) {
				std::cout << "(" << legal[i].row << "," << legal[i].col << ")";
				if (i + 1 < legal.size()) std::cout << ", ";
			}
			if (legal.empty()) std::cout << "<none>";
			std::cout << "\nYour move (row col, 0-based): ";
			int r, c;
			if (!readMovePair(r, c)) { std::cout << "Invalid input. Try again.\n"; continue; }
			TicTacToe::Move m{r,c};
			if (!state.isLegal(m)) { std::cout << "Illegal. Try again.\n"; continue; }
			state = state.applyMove(m);
		} else {
			std::cout << "AI thinking...\n";
			auto best = engine::findBestMove(state, /*depth*/9, ai);
			state = state.applyMove(best);
		}
	}

	std::cout << "\nFinal board:\n" << state.toString() << "\n";
	int scoreForHuman = state.evaluate(human);
	if (scoreForHuman > 0) std::cout << "You win!\n";
	else if (scoreForHuman < 0) std::cout << "AI wins!\n";
	else std::cout << "Draw.\n";
	return 0;
}
