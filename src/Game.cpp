#include "Game.h"
#include <iostream>

namespace Blackjack {

Game::Game(std::random_device& rd, std::string dealerName,
           std::vector<std::string> playerNames, int initMoney)
    : deck_(rd), dealer_(dealerName) {
  for (const std::string& name : playerNames) {
    this->players_.push_back(Player{name, initMoney});
  }

  this->deck_.shuffle();
}

void Game::askBets() {
  for (Player& player : this->players_) {
    while (true) {
      std::cout << "Enter the bet for " << player.name() << "\n";

      std::string buf;
      std::getline(std::cin, buf);
      int betAmount = std::stoi(buf);
      if (betAmount > 0 && player.addMoney(-betAmount)) {
        this->bets_[player.name()] = betAmount;
        break;
      } else {
        std::cout << "You entered an invalid bet\n";
      }
    }
  }
}

void Game::run() {
  // TODO(DarinM223): run game
}

void Game::applyAction(Player& player, size_t handIndex, Action action) {
  switch (action) {
    case Action::DOUBLE:
      player.addBet(handIndex, player.bet(handIndex));
    case Action::HIT: {
      auto card = this->deck_.draw();
      player.addCard(handIndex, card);
      break;
    }
    case Action::SPLIT: {
      if (player.split(handIndex)) {
        auto card1 = this->deck_.draw();
        auto card2 = this->deck_.draw();
        player.addCard(handIndex, card1);
        player.addCard(player.hands() - 1, card2);
      }
      break;
    }
    case Action::STAND:
      break;
  }
}

}  // namespace Blackjack
