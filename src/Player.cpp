#include "Player.h"
#include <iostream>
#include <tuple>

namespace Blackjack {

std::tuple<int, int> addScore(int prevScore, int value, int numHighAces) {
  int score = prevScore + value;

  while (score > 21 && numHighAces > 0) {
    numHighAces--;
    score -= 10;
  }

  return std::make_tuple(score, numHighAces);
}

Action Player::turn() const {
  while (true) {
    std::cout << "Enter (1) to Hit, (2) to Stand\n";

    std::string buf;
    std::getline(std::cin, buf);

    int actionNum = std::stoi(buf);
    if (actionNum == 1) {
      return Action::HIT;
    } else if (actionNum == 2) {
      return Action::STAND;
    }
  }
}

void Player::addCard(Card card) {
  int value;
  if (card.value() == 1) {
    this->numHighAces_++;
    value = 11;
  } else {
    value = card.value();
  }

  std::tie(score_, numHighAces_) = addScore(score_, value, numHighAces_);
}

Action Dealer::turn() const {
  if (this->score() >= 17) {
    return Action::STAND;
  }

  return Action::HIT;
}

}  // namespace Blackjack
