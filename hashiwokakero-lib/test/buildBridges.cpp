#include <gtest/gtest.h>

#include <algorithm>

#include "vectorboard.hpp"

class BuildBridgesTest : public ::testing::Test
{
protected:
    VectorBoard board;

    void SetUp() override
    {
        // Solution
        // 3 - - - 2 - 2
        // :   3 - - 1 |
        // :   :       |
        // 6 = 6 - - - 3
        // :   |       |
        // :   |       |
        // 4 = 4 - 3 = 3
        board.m_matrix = {
            //     0  1  2  3  4  5  6
            /*0*/ {3, 0, 0, 0, 2, 0, 2},
            /*1*/ {0, 0, 3, 0, 0, 1, 0},
            /*2*/ {0, 0, 0, 0, 0, 0, 0},
            /*3*/ {6, 0, 6, 0, 0, 0, 3},
            /*4*/ {0, 0, 0, 0, 0, 0, 0},
            /*5*/ {0, 0, 0, 0, 0, 0, 0},
            /*6*/ {4, 0, 4, 0, 3, 0, 3},
        };

        board.m_height = 7;
        board.m_width = 7;

        board.m_islands = {
            {BoardPosition(0, 0), 3},
            {BoardPosition(0, 4), 2},
            {BoardPosition(0, 6), 2},
            {BoardPosition(1, 2), 3},
            {BoardPosition(1, 5), 1},
            {BoardPosition(3, 0), 6},
            {BoardPosition(3, 2), 6},
            {BoardPosition(3, 6), 3},
            {BoardPosition(6, 0), 4},
            {BoardPosition(6, 2), 4},
            {BoardPosition(6, 4), 3},
            {BoardPosition(6, 6), 3},

        };

        board.m_bridges = {};
    }
};

TEST_F(BuildBridgesTest, RequirementUpdateCheck)
{
    ASSERT_EQ(board.bridges().size(), 0);

    ASSERT_TRUE(board.tryBuildBridge({BoardPosition(1, 2)}, {BoardPosition{1, 5}}));
    ASSERT_EQ(board.m_matrix[1][5], 0);
    ASSERT_EQ(board.m_matrix[1][2], 2);
    ASSERT_EQ(board.bridges().size(), 1);

    auto islands = board.islands();

    auto it = std::find(islands.begin(), islands.end(), Island(BoardPosition(1, 2)));
    ASSERT_NE(it, islands.end());
    ASSERT_EQ(it->bridgesRemaining, 2);

    it = std::find(islands.begin(), islands.end(), Island(BoardPosition(1, 5)));
    ASSERT_NE(it, islands.end());
    ASSERT_EQ(it->bridgesRemaining, 0);
}

TEST_F(BuildBridgesTest, BridgeUpgrade)
{
    ASSERT_EQ(board.bridges().size(), 0);

    ASSERT_TRUE(board.tryBuildBridge({BoardPosition(3, 0)}, {BoardPosition{3, 2}}));
    ASSERT_TRUE(board.tryBuildBridge({BoardPosition(3, 0)}, {BoardPosition{3, 2}}));
    ASSERT_EQ(board.m_matrix[3][0], 4);
    ASSERT_EQ(board.m_matrix[3][2], 4);
    ASSERT_EQ(board.bridges().size(), 1);

    auto islands = board.islands();

    auto it = std::find(islands.begin(), islands.end(), Island(BoardPosition(3, 0)));
    ASSERT_NE(it, islands.end());
    ASSERT_EQ(it->bridgesRemaining, 4);

    it = std::find(islands.begin(), islands.end(), Island(BoardPosition(3, 2)));
    ASSERT_NE(it, islands.end());
    ASSERT_EQ(it->bridgesRemaining, 4);
}

TEST_F(BuildBridgesTest, BridgeDelete)
{
    ASSERT_EQ(board.bridges().size(), 0);

    // Place 2sized bridge
    ASSERT_TRUE(board.tryBuildBridge({BoardPosition(3, 0)}, {BoardPosition{3, 2}}));
    ASSERT_TRUE(board.tryBuildBridge({BoardPosition(3, 0)}, {BoardPosition{3, 2}}));
    ASSERT_EQ(board.m_matrix[3][0], 4);
    ASSERT_EQ(board.m_matrix[3][2], 4);
    ASSERT_EQ(board.bridges().size(), 1);

    // Delete
    ASSERT_TRUE(board.tryBuildBridge({BoardPosition(3, 0)}, {BoardPosition{3, 2}}));
    ASSERT_EQ(board.m_matrix[3][0], 6);
    ASSERT_EQ(board.m_matrix[3][2], 6);
    ASSERT_EQ(board.bridges().size(), 0);

    auto islands = board.islands();

    auto it = std::find(islands.begin(), islands.end(), Island(BoardPosition(3, 0)));
    ASSERT_NE(it, islands.end());
    ASSERT_EQ(it->bridgesRemaining, 6);

    it = std::find(islands.begin(), islands.end(), Island(BoardPosition(3, 2)));
    ASSERT_NE(it, islands.end());
    ASSERT_EQ(it->bridgesRemaining, 6);
}

TEST_F(BuildBridgesTest, BridgeCollide)
{
    ASSERT_EQ(board.bridges().size(), 0);

    ASSERT_TRUE(board.tryBuildBridge({BoardPosition(1, 2)}, {BoardPosition{1, 5}}));
    ASSERT_FALSE(board.tryBuildBridge({BoardPosition(0, 4)}, {BoardPosition{6, 4}}));
    ASSERT_EQ(board.bridges().size(), 1);
}
