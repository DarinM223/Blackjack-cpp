#include "Deck.h"

namespace Blackjack {

int random_range(std::random_device& rd, int min, int max) {
  std::mt19937 rng{rd()};
  std::uniform_int_distribution<int> uni{min, max};

  return uni(rng);
}

Deck::Deck(std::random_device& rd) : rd_(rd) {
  // Generates standard 52 card deck.
  for (int value = 1; value <= 13; value++) {
    int cardValue = value > 9 ? 10 : value;
    this->cards_.push_back(Card(Suite::DIAMONDS, cardValue));
    this->cards_.push_back(Card(Suite::HEARTS, cardValue));
    this->cards_.push_back(Card(Suite::SPADES, cardValue));
    this->cards_.push_back(Card(Suite::CLUBS, cardValue));
  }
}

Card Deck::draw() {
  if (this->cards_.size() <= 0) {
    throw EmptyDeckException{};
  }

  // Move out last card and remove it from the vector.
  Card card = std::move(this->cards_[this->cards_.size() - 1]);
  this->cards_.pop_back();

  return card;
}

void Deck::shuffle() {
  for (int i = this->cards_.size() - 1; i >= 1; i--) {
    int j = random_range(this->rd_, 0, i);

    std::swap(this->cards_[j], this->cards_[i]);
  }
}

}  // namespace Blackjack
