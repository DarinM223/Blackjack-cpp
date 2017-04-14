#include "Deck.hpp"

namespace Blackjack {

int random_range(std::random_device& rd, int min, int max) {
  std::mt19937 rng(rd());
  std::uniform_int_distribution<int> uni(min, max);

  return uni(rng);
}

Card::Card(Suite suite, int value) : suite(suite), value(value) {}

BlackjackDeck::BlackjackDeck(std::random_device& rd) : rd(rd) {
  // Generates standard 52 card deck.
  for (int value = 1; value <= 13; value++) {
    this->cards.push_back(Card(Suite::DIAMONDS, value));
    this->cards.push_back(Card(Suite::HEARTS, value));
    this->cards.push_back(Card(Suite::SPADES, value));
    this->cards.push_back(Card(Suite::CLUBS, value));
  }
}

Card BlackjackDeck::draw() {
  if (this->cards.size() <= 0) {
    throw EmptyDeckException();
  }

  // Move out last card and remove it from the vector.
  Card card = std::move(this->cards[this->cards.size() - 1]);
  this->cards.pop_back();

  return card;
}

void BlackjackDeck::shuffle() {
  for (int i = this->cards.size() - 1; i >= 1; i--) {
    int j = random_range(this->rd, 0, i);

    std::swap(this->cards[j], this->cards[i]);
  }
}

int BlackjackDeck::size() const { return this->cards.size(); }

}  // namespace Blackjack
