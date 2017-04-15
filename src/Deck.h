#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <exception>
#include <random>
#include <vector>

namespace Blackjack {

struct EmptyDeckException : public std::exception {
  const char* what() const throw() { return "Deck is empty"; }
};

enum class Suite { HEARTS = 0, DIAMONDS, SPADES, CLUBS };

class Card {
 public:
  Card(Suite suite, int value) : suite_(suite), value_(value) {}

  Suite suite() const { return this->suite_; }
  int value() const { return this->value_; }

 private:
  Suite suite_;
  int value_;
};

class Deck {
 public:
  Deck(std::random_device& rd);
  Card draw();
  void shuffle();
  int size() const { return this->cards_.size(); }

 private:
  std::vector<Card> cards_;
  std::random_device& rd_;
};

}  // namespace Blackjack

#endif
