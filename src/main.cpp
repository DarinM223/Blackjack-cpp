#include <iostream>
#include <memory>
#include "Game.h"

using namespace Blackjack;

int main() {
  std::random_device rd;
  Game game{rd, "Dealer", {"A", "B", "C", "D"}, 100};
  while (true) {
    game.run();
  }

  return 0;
}
