#include "Game.h"
#include <iostream>

namespace Blackjack {

std::string playerResultToString(PlayerResult result) {
  switch (result) {
    case PlayerResult::WIN:
      return "win";
    case PlayerResult::LOSE:
      return "lose";
    case PlayerResult::PUSH:
      return "push";
    default:
      return "";
  }
}

void printAction(std::string name, bool dealer, Action action) {
  if (dealer) {
    std::cout << "Dealer ";
  } else {
    std::cout << "Player " << name << " ";
  }

  switch (action) {
    case Action::HIT:
      std::cout << "hit";
      break;
    case Action::STAND:
      std::cout << "stood";
      break;
    case Action::SPLIT:
      std::cout << "split";
      break;
    case Action::DOUBLE:
      std::cout << "doubled";
      break;
  }

  std::cout << "\n";
}

Game::Game(std::random_device& rd, std::string dealerName,
           std::vector<std::unique_ptr<Player>> players)
    : deck_(rd), dealer_(dealerName), players_(std::move(players)) {
  this->deck_.shuffle();
}

void Game::askBets() {
  for (auto& player : this->players_) {
    player->placeBet();
  }
}

void Game::run() {
  this->askBets();

  // Deals two cards to dealer.
  auto card1 = this->deck_.draw();
  auto card2 = this->deck_.draw();
  this->dealer_.addCard(std::move(card1));
  this->dealer_.addCard(std::move(card2));

  for (auto& player : this->players_) {
    // Deals two cards to every player initially.
    auto card1 = this->deck_.draw();
    auto card2 = this->deck_.draw();
    player->addCard(0, std::move(card1));
    player->addCard(0, std::move(card2));

    // Handles actions for every hand the player has.
    for (size_t handIndex = 0; handIndex < player->hands(); handIndex++) {
      while (!player->isBust(handIndex)) {
        Action action;
        bool validAction;
        do {
          action = player->turn(handIndex);
          validAction = this->applyAction(*player, handIndex, action);

          if (!validAction)
            std::cout << "Invalid action\n";
          else
            printAction(player->name(), false, action);
        } while (!validAction);

        if (action == Action::STAND) {
          break;
        }
      }
    }
  }

  // Handles actions for the dealer.
  Action action;
  do {
    action = this->dealer_.turn();
    this->applyAction(this->dealer_, action);
    printAction(this->dealer_.name(), true, action);
    std::cout << "Dealer's score is: " << this->dealer_.score() << "\n";
  } while (!this->dealer_.isBust() && action != Action::STAND);

  // Displays and applies results and resets all of the scores.
  const int dealerScore = this->dealer_.score();
  for (auto& player : this->players_) {
    std::cout << player->name() << "'s scores is:\n";
    for (size_t i = 0; i < player->hands(); i++) {
      const int score = player->score(i);
      std::cout << score << ": ";

      auto result = this->scoreHand(dealerScore, score);
      std::cout << playerResultToString(result) << "\n";
      this->applyResult(*player, i, result);
    }
    std::cout << "\n";

    player->reset();
  }

  this->dealer_.reset();
}

bool Game::applyAction(Player& player, size_t handIndex, Action action) {
  switch (action) {
    case Action::DOUBLE:
      if (!player.addBet(handIndex, player.bet(handIndex))) return false;
    case Action::HIT: {
      auto card = this->deck_.draw();
      player.addCard(handIndex, std::move(card));
      return true;
    }
    case Action::SPLIT: {
      if (!player.split(handIndex)) return false;
      auto card1 = this->deck_.draw();
      auto card2 = this->deck_.draw();
      player.addCard(handIndex, std::move(card1));
      player.addCard(player.hands() - 1, std::move(card2));
      return true;
    }
    case Action::STAND:
      return true;
    default:
      return false;
  }
}

bool Game::applyAction(Dealer& dealer, Action action) {
  switch (action) {
    case Action::HIT: {
      auto card = this->deck_.draw();
      dealer.addCard(std::move(card));
      return true;
    }
    case Action::STAND:
      return true;
    default:
      return false;
  }
}

void Game::applyResult(Player& player, size_t handIndex, PlayerResult result) {
  const int bet = player.bet(handIndex);
  switch (result) {
    case PlayerResult::WIN:
      player.addMoney(bet * 2);
      break;
    case PlayerResult::PUSH:
      player.addMoney(bet);
      break;
    case PlayerResult::LOSE:
      // Do nothing.
      break;
  }
}

PlayerResult Game::scoreHand(int dealerScore, int playerScore) {
  if (playerScore > 21) {
    return PlayerResult::LOSE;
  } else if (dealerScore > 21) {
    return PlayerResult::WIN;
  } else if (playerScore == dealerScore) {
    return PlayerResult::PUSH;
  } else if (playerScore > dealerScore) {
    return PlayerResult::WIN;
  } else {
    return PlayerResult::LOSE;
  }
}

}  // namespace Blackjack
