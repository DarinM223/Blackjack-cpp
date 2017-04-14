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
  Card(Suite suite, int value);

  Suite getSuite() const { return this->suite; }
  int getValue() const { return this->value; }

 private:
  Suite suite;
  int value;
};

class Deck {
 public:
  virtual Card draw() = 0;
  virtual void shuffle() = 0;
  virtual int size() const = 0;
};

class BlackjackDeck : public Deck {
 public:
  BlackjackDeck(std::random_device& rd);
  virtual Card draw() override;
  virtual void shuffle() override;
  virtual int size() const override;

 private:
  std::vector<Card> cards;
  std::random_device& rd;
};

}  // namespace Blackjack

#endif
