#include "Player.h"
#include <gtest/gtest.h>
#include "Deck.h"

namespace Blackjack {

TEST(PlayerTest, ScoreWithAces) {
  Player player{"Bob", 100};
  player.addCard(0, Card{Suite::HEARTS, 1});
  player.addCard(0, Card{Suite::DIAMONDS, 1});

  EXPECT_EQ(player.score(0), 12);
}

TEST(PlayerTest, Money) {
  Player playerA{"Bob", 100};
  EXPECT_EQ(playerA.addMoney(-10), true);
  EXPECT_EQ(playerA.money(), 90);

  Player playerB{"Bob", 100};
  EXPECT_EQ(playerB.addMoney(-100), true);
  EXPECT_EQ(playerB.money(), 0);

  Player playerC{"Bob", 100};
  EXPECT_EQ(playerC.addMoney(-110), false);
  EXPECT_EQ(playerC.money(), 100);

  Player playerD{"Bob", 100};
  EXPECT_EQ(playerD.addMoney(110), true);
  EXPECT_EQ(playerD.money(), 210);
}

TEST(PlayerTest, Bets) {
  Player player{"Bob", 100};
  EXPECT_EQ(player.bet(0), 0);

  EXPECT_EQ(player.addBet(0, 10), true);
  EXPECT_EQ(player.bet(0), 10);
  EXPECT_EQ(player.money(), 90);

  EXPECT_EQ(player.addBet(0, 91), false);
  EXPECT_EQ(player.addBet(0, -1), false);
  EXPECT_EQ(player.bet(0), 10);
  EXPECT_EQ(player.money(), 90);

  EXPECT_EQ(player.addBet(0, 90), true);
  EXPECT_EQ(player.bet(0), 100);
  EXPECT_EQ(player.money(), 0);
}

TEST(PlayerTest, SplitSuccess) {
  Player player{"Bob", 200};
  player.addCard(0, Card{Suite::HEARTS, 1});
  player.addCard(0, Card{Suite::DIAMONDS, 1});

  player.addBet(0, 100);
  EXPECT_EQ(player.split(0), true);

  EXPECT_EQ(player.hands(), static_cast<size_t>(2));

  EXPECT_EQ(player.score(0), 11);
  EXPECT_EQ(player.score(1), 11);

  EXPECT_EQ(player.bet(0), 100);
  EXPECT_EQ(player.bet(1), 100);
  EXPECT_EQ(player.money(), 0);
}

TEST(PlayerTest, SplitFail) {
  Player player{"Bob", 100};
  player.addCard(0, Card{Suite::HEARTS, 1});
  player.addCard(0, Card{Suite::DIAMONDS, 1});

  player.addBet(0, 60);
  EXPECT_EQ(player.split(0), false);

  EXPECT_EQ(player.hands(), static_cast<size_t>(1));
  EXPECT_EQ(player.score(0), 12);
  EXPECT_EQ(player.money(), 40);
}

TEST(PlayerTest, PlayerReset) {
  Player player{"Bob", 100};
  player.addCard(0, Card{Suite::HEARTS, 1});
  player.addCard(0, Card{Suite::DIAMONDS, 1});
  player.addBet(0, 10);
  player.split(0);

  player.reset();

  EXPECT_EQ(player.hands(), static_cast<size_t>(1));
  EXPECT_EQ(player.score(0), 0);
  EXPECT_EQ(player.bet(0), 0);
  EXPECT_EQ(player.money(), 80);
}

TEST(PlayerTest, DealerReset) {
  Dealer dealer{"Bob"};
  dealer.addCard(Card{Suite::HEARTS, 1});
  dealer.addCard(Card{Suite::DIAMONDS, 1});

  dealer.reset();

  EXPECT_EQ(dealer.score(), 0);
}

TEST(DealerTest, ScoreWithAces) {
  Dealer dealer{"Bob"};
  dealer.addCard(Card{Suite::HEARTS, 1});
  dealer.addCard(Card{Suite::DIAMONDS, 1});

  EXPECT_EQ(dealer.score(), 12);
}

TEST(PlayerTest, DealerActions) {
  Dealer dealer{"Bob"};

  dealer.addCard(Card{Suite::HEARTS, 5});
  EXPECT_EQ(dealer.turn(), Action::HIT);

  dealer.addCard(Card{Suite::DIAMONDS, 1});
  EXPECT_EQ(dealer.turn(), Action::HIT);

  dealer.addCard(Card{Suite::SPADES, 1});
  EXPECT_EQ(dealer.turn(), Action::STAND);
}

}  // namespace Blackjack
