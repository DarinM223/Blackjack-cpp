#include <iostream>
#include <memory>
#include "Deck.h"

using namespace Blackjack;

int main() {
  std::random_device rd;
  Deck deck{rd};
  deck.shuffle();

  std::cout << "Number of cards in deck: " << deck.size() << "\n";

  while (true) {
    try {
      auto card = deck.draw();
      std::cout << "Card value: " << card.value()
                << " suite: " << (int)card.suite() << "\n";
    } catch (EmptyDeckException e) {
      std::cout << "Ran out of cards\n";
      break;
    }
  }

  return 0;
}
