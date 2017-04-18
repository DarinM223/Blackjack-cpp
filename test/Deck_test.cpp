#include "Deck.h"
#include <gtest/gtest.h>
#include <random>

namespace Blackjack {

TEST(DeckTest, DeckContains52Cards) {
  std::random_device rd;
  Deck deck{rd};
  EXPECT_EQ(deck.size(), 52);
}

TEST(DeckTest, DrawingCardRemovesFromDeck) {
  std::random_device rd;
  Deck deck{rd};

  deck.draw();

  EXPECT_EQ(deck.size(), 51);
}

TEST(DeckTest, AllCardsBetween1And10) {
  std::random_device rd;
  Deck deck{rd};

  for (int i = 0; i < 52; i++) {
    auto card = deck.draw();
    EXPECT_TRUE(card.value() <= 10 && card.value() >= 1);
  }
}

TEST(DeckTest, ExceptionAfterNoCards) {
  std::random_device rd;
  Deck deck{rd};

  for (int i = 0; i < 52; i++) {
    deck.draw();
  }

  bool caughtException = false;

  try {
    deck.draw();
  } catch (EmptyDeckException e) {
    caughtException = true;
  }

  EXPECT_EQ(caughtException, true);
}

}  // namespace Blackjack
