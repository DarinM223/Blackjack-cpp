#include "Player.h"
#include <gtest/gtest.h>
#include "Deck.h"

namespace Blackjack {

TEST(PlayerTest, ScoreWithAces) {
  Player player("Bob");
  player.addCard(Card(Suite::HEARTS, 1));
  player.addCard(Card(Suite::DIAMONDS, 1));

  EXPECT_EQ(player.score(), 12);
}

TEST(PlayerTest, DealerActions) {
  Dealer dealer("Bob");

  dealer.addCard(Card(Suite::HEARTS, 5));
  EXPECT_EQ(dealer.turn(), Action::HIT);

  dealer.addCard(Card(Suite::DIAMONDS, 1));
  EXPECT_EQ(dealer.turn(), Action::HIT);

  dealer.addCard(Card(Suite::SPADES, 1));
  EXPECT_EQ(dealer.turn(), Action::STAND);
}

}  // namespace Blackjack
