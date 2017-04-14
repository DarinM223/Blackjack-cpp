#ifndef BLACKJACK_H
#define BLACKJACK_H

#include <vector>

namespace Blackjack {

enum class Suite { HEARTS = 0, DIAMONDS, SPADES, CLUBS };

class Card {
 public:
  const Suite suite;
  const int value;

  Card(Suite suite, int value);
};

class Deck {
 public:
  virtual Card draw() = 0;
  virtual void shuffle() = 0;
};

class BlackjackDeck : public Deck {
 public:
  virtual Card draw() override;
  virtual void shuffle() override;

 private:
  std::vector<Card> cards;
};

}  // namespace Blackjack

#endif
