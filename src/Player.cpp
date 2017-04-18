#include "Player.h"
#include <iostream>
#include <tuple>

namespace Blackjack {

std::tuple<int, int> addCard(const Card& card, int prevScore, int numHighAces) {
  int value;
  if (card.value() == 1) {
    numHighAces++;
    value = 11;
  } else {
    value = card.value();
  }

  int score = prevScore + value;

  while (score > 21 && numHighAces > 0) {
    numHighAces--;
    score -= 10;
  }

  return std::make_tuple(score, numHighAces);
}

Action Player::turn(size_t handIndex) const {
  bool done = false;
  while (!done) {
    std::cout << "Player " << this->name_ << "'s money: " << this->money_
              << "\n";
    std::cout << "Player " << this->name_ << " current score for hand "
              << handIndex + 1 << ": " << this->scores_[handIndex] << "\n";
    std::cout << "Enter (1) to Hit, (2) to Stand, "
              << "(3) to Double, (4) to Split\n";

    std::string buf;
    std::getline(std::cin, buf);

    int actionNum;
    try {
      actionNum = std::stoi(buf);
    } catch (std::exception e) {
      std::cout << "Invalid number entered\n";
      continue;
    }
    switch (actionNum) {
      case 1:
        return Action::HIT;
      case 2:
        return Action::STAND;
      case 3:
        return Action::DOUBLE;
      case 4:
        return Action::SPLIT;
      default:
        std::cout << "Invalid number entered\n";
        break;
    }
  }

  return Action::STAND;
}

void Player::addCard(size_t handIndex, Card card) {
  std::tie(scores_[handIndex], numHighAces_[handIndex]) =
      Blackjack::addCard(card, scores_[handIndex], numHighAces_[handIndex]);
  this->cards_[handIndex].push_back(card);
}

bool Player::addMoney(int difference) {
  int newAmount = this->money_ + difference;
  if (newAmount < 0) {
    return false;
  }

  this->money_ = newAmount;
  return true;
}

bool Player::addBet(size_t index, int amount) {
  if (amount < 0 || !this->addMoney(-amount)) {
    return false;
  }

  this->bets_[index] += amount;
  return true;
}

bool Player::split(size_t handIndex) {
  auto hand = this->cards_[handIndex];

  if (hand.size() == 2 && hand[0].value() == hand[1].value()) {
    auto bet = this->bets_[handIndex];
    if (!this->addMoney(-bet)) {
      return false;
    }

    auto card = this->removeCard(handIndex, hand.size() - 1);

    this->scores_.push_back(0);
    this->numHighAces_.push_back(0);
    this->bets_.push_back(bet);
    this->cards_.push_back({});

    this->addCard(this->hands() - 1, card);
    return true;
  }
  return false;
}

void Player::reset() {
  this->scores_.clear();
  this->numHighAces_.clear();
  this->cards_.clear();
  this->bets_.clear();

  this->scores_.push_back(0);
  this->numHighAces_.push_back(0);
  this->bets_.push_back(0);
  this->cards_.push_back({});
}

Card Player::removeCard(size_t handIndex, size_t cardIndex) {
  auto hand = this->cards_[handIndex];
  auto card = std::move(hand[cardIndex]);
  hand.erase(hand.begin() + cardIndex);

  // Recalculate the score by adding all the cards again.
  int numHighAces = 0;
  int score = 0;
  for (const Card& card : hand) {
    std::tie(score, numHighAces) = Blackjack::addCard(card, score, numHighAces);
  }

  this->scores_[handIndex] = score;
  this->numHighAces_[handIndex] = numHighAces;
  return card;
}

void Dealer::addCard(Card card) {
  std::tie(score_, numHighAces_) =
      Blackjack::addCard(card, score_, numHighAces_);
}

Action Dealer::turn() const {
  if (this->score() >= 17) {
    return Action::STAND;
  }

  return Action::HIT;
}

}  // namespace Blackjack
