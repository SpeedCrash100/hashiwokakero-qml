#include <gtest/gtest.h>

#include "boardbuilder.hpp"

TEST(HashiwokakeroLibGeneration, IslandCount) {
  std::vector<int> test_steps = {0, 1, 2, 8, 50, 1000};
  std::vector<int> test_size = {8, 8, 8, 8, 50, 1000};

  for (int i = 0; i < test_steps.size(); i++) {
    auto field_size = test_size[i];
    auto steps = test_steps[i];

    BoardBuilder builder;
    builder.setWidth(field_size);
    builder.setHeight(field_size);
    auto board = builder.build(steps);

    auto islands = board->islands();

    ASSERT_EQ(islands.size(), steps + 1);
  }
}

TEST(HashiwokakeroLibGeneration, AllIslandHaveBridgeReqInRange) {
  BoardBuilder builder;
  builder.setWidth(7);
  builder.setHeight(7);
  auto board = builder.build(8);

  auto islands = board->islands();

  for (auto island : islands) {
    ASSERT_GT(island.bridgeRequired, 0);
    ASSERT_LE(island.bridgeRequired, 4 * MAX_BRIDGE_SIZE);
  }
}

TEST(HashiwokakeroLibGeneration, TooManySteps) {
  BoardBuilder builder;
  builder.setWidth(10);
  builder.setHeight(10);

  EXPECT_THROW(builder.build(100), std::runtime_error);
}
