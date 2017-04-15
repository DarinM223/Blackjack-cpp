#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Deck.h"

namespace Blackjack {

enum class Action { HIT = 0, STAND, DOUBLE, SPLIT };

class Player {
 public:
  Player(std::string name) : score_(0), numHighAces_(0), name_(name) {}

  std::string name() const { return this->name_; }
  int score() const { return this->score_; }
  virtual Action turn() const;
  virtual void addCard(Card card);

 protected:
  int score_;
  int numHighAces_;
  std::string name_;
  std::vector<Card> hand_;
};

class Dealer : public Player {
 public:
  Dealer(std::string name) : Player(name) {}
  virtual Action turn() const override;
};

}  // namespace Blackjack

#endif
