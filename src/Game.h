#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include <unordered_map>
#include <vector>
#include "Deck.h"
#include "Player.h"

namespace Blackjack {

enum class PlayerResult { WIN = 0, LOSE, PUSH };

std::string playerResultToString(PlayerResult result);

class Game {
 public:
  Game(std::random_device& rd, std::string dealerName,
       std::vector<std::unique_ptr<Player>> players);
  virtual void askBets();
  virtual void run();
  virtual bool applyAction(Player& player, size_t handIndex, Action action);
  virtual bool applyAction(Dealer& dealer, Action action);
  virtual void applyResult(Player& player, size_t handIndex,
                           PlayerResult result);
  virtual PlayerResult scoreHand(int dealerScore, int playerScore);

 private:
  Deck deck_;
  Dealer dealer_;
  std::vector<std::unique_ptr<Player>> players_;
};

}  // namespace Blackjack

#endif
