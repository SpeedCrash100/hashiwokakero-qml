#include <gtest/gtest.h>

#include "boardbuilder.hpp"

TEST(HashiwokakeroLibGeneration, AllIslandHaveBridgeReqInRange)
{
    BoardBuilder builder;
    builder.setWidth(7);
    builder.setHeight(7);
    auto board = builder.build(20);

    auto islands = board->islands();

    for (auto island : islands)
    {
        ASSERT_GT(island.bridgeRequired, 0);
        ASSERT_LE(island.bridgeRequired, 4 * MAX_BRIDGE_SIZE);
    }
}
