#include <iostream>
#include <memory>
#include "Deck.hpp"

using namespace Blackjack;

int main() {
  std::random_device rd;
  std::unique_ptr<Deck> deck = std::make_unique<BlackjackDeck>(rd);
  deck->shuffle();

  std::cout << "Number of cards in deck: " << deck->size() << std::endl;

  while (true) {
    try {
      auto card = deck->draw();
      std::cout << "Card value: " << card.getValue()
                << " suite: " << (int)card.getSuite() << std::endl;
    } catch (EmptyDeckException e) {
      std::cout << "Ran out of cards" << std::endl;
      break;
    }
  }

  return 0;
}
