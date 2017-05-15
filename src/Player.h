#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <tuple>
#include <vector>
#include "Deck.h"

namespace Blackjack {

enum class Action { HIT = 0, STAND, DOUBLE, SPLIT };

class Player {
 public:
  Player(std::string name, int money) : money_(money), name_(name) {
    this->reset();
  }

  std::string name() const { return this->name_; }
  int score(size_t handIndex) const { return this->scores_[handIndex]; }
  size_t hands() const { return this->cards_.size(); }
  const std::vector<Card>& hand(size_t index) const {
    return this->cards_.at(index);
  }
  void addCard(size_t handIndex, Card card);
  virtual Action turn(size_t handIndex) const;
  virtual bool isBust(size_t handIndex) const {
    return this->scores_[handIndex] > 21;
  }

  int money() const { return this->money_; }
  bool addMoney(int difference);

  int bet(size_t index) const { return this->bets_[index]; }
  bool addBet(size_t index, int amount);
  virtual void placeBet();

  bool split(size_t handIndex);
  void reset();
  Card removeCard(size_t handIndex, size_t cardIndex);

 private:
  std::vector<int> scores_;
  std::vector<int> numHighAces_;
  std::vector<int> bets_;
  int money_;
  std::string name_;
  std::vector<std::vector<Card>> cards_;
};

class AIPlayer : public Player {
 public:
  AIPlayer(std::string name, int money) : Player(name, money) {}
  virtual Action turn(size_t handIndex) const override;
  virtual void placeBet() override;
};

class Dealer {
 public:
  Dealer(std::string name) : score_(0), numHighAces_(0), name_(name) {}

  std::string name() const { return this->name_; }
  virtual bool isBust() const { return this->score_ > 21; }
  void addCard(Card card);
  Action turn() const;
  int score() const { return this->score_; }
  void reset();

 private:
  int score_;
  int numHighAces_;
  std::string name_;
};

}  // namespace Blackjack

#endif
