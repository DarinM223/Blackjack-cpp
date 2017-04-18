#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include <unordered_map>
#include <vector>
#include "Deck.h"
#include "Player.h"

namespace Blackjack {

class Game {
 public:
  Game(std::random_device& rd, std::string dealerName,
       std::vector<std::string> playerNames, int initMoney);
  virtual void askBets();
  virtual void run();
  virtual bool applyAction(Player& player, size_t handIndex, Action action);
  virtual bool applyAction(Dealer& dealer, Action action);

 private:
  Deck deck_;
  Dealer dealer_;
  std::vector<Player> players_;
};

}  // namespace Blackjack

#endif
