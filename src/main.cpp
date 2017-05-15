#include <iostream>
#include <memory>
#include "Game.h"

using namespace Blackjack;

int main() {
  std::random_device rd;
  std::unique_ptr<Player> mainPlayer = std::make_unique<Player>("Main", 100),
                          bot1 = std::make_unique<AIPlayer>("Bot1", 100),
                          bot2 = std::make_unique<AIPlayer>("Bot2", 100),
                          bot3 = std::make_unique<AIPlayer>("Bot3", 100);

  std::vector<std::unique_ptr<Player>> players;
  players.emplace_back(std::move(mainPlayer));
  players.emplace_back(std::move(bot1));
  players.emplace_back(std::move(bot2));
  players.emplace_back(std::move(bot3));

  Game game{rd, "Dealer", std::move(players)};
  while (true) {
    game.run();
  }

  return 0;
}
