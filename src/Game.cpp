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

      if (player.addBet(0, betAmount)) {
        break;
      } else {
        std::cout << "You entered an invalid bet\n";
      }
    }
  }
}

void Game::run() {
  this->askBets();
  for (Player& player : this->players_) {
    for (size_t handIndex = 0; handIndex < player.hands(); handIndex++) {
      while (!player.isBust(handIndex)) {
        auto action = player.turn(handIndex);
        this->applyAction(player, handIndex, action);

        if (action == Action::STAND) {
          break;
        }
      }
    }
  }

  while (!this->dealer_.isBust()) {
    auto action = this->dealer_.turn();
    this->applyAction(this->dealer_, action);

    if (action == Action::STAND) {
      break;
    }
  }

  // TODO(DarinM223): handle final scores.
}

bool Game::applyAction(Player& player, size_t handIndex, Action action) {
  switch (action) {
    case Action::DOUBLE:
      if (!player.addBet(handIndex, player.bet(handIndex))) return false;
    case Action::HIT: {
      auto card = this->deck_.draw();
      player.addCard(handIndex, card);
      return true;
    }
    case Action::SPLIT: {
      if (!player.split(handIndex)) return false;
      auto card1 = this->deck_.draw();
      auto card2 = this->deck_.draw();
      player.addCard(handIndex, card1);
      player.addCard(player.hands() - 1, card2);
      return true;
    }
    case Action::STAND:
      return true;
    default:
      return false;
  }
}

bool Game::applyAction(Dealer& dealer, Action action) {
  switch (action) {
    case Action::HIT: {
      auto card = this->deck_.draw();
      dealer.addCard(card);
      return true;
    }
    case Action::STAND:
      return true;
    default:
      return false;
  }
}

}  // namespace Blackjack
