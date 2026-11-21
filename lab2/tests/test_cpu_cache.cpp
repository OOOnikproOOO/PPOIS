/**
 * @file test_cpu_cache.cpp
 * @brief Unit tests for the CPUCache class.
 * @author Nikita Momot
 * @date 2026
 */

#include <gtest/gtest.h>
#include <sstream>
#include "CPUCache.h"

TEST(CPUCacheTest, DefaultConstructorAndGetters) {
    CPUCache cache(2, 512, 64);
    EXPECT_EQ(cache.GetLevel(), 2);
    EXPECT_EQ(cache.GetSizeKb(), 512);
    EXPECT_EQ(cache.GetLineSizeBytes(), 64);
    EXPECT_EQ(cache.GetHits(), 0);
    EXPECT_EQ(cache.GetMisses(), 0);
    EXPECT_FALSE(cache.IsDirty());
    EXPECT_DOUBLE_EQ(cache.GetHitRate(), 0.0);
}

TEST(CPUCacheTest, ReadHitsAndMisses) {
    CPUCache cache;
    EXPECT_FALSE(cache.Read(0x0LL));
    EXPECT_EQ(cache.GetMisses(), 1);

    EXPECT_TRUE(cache.Read(0x10LL));
    EXPECT_EQ(cache.GetHits(), 1);

    EXPECT_DOUBLE_EQ(cache.GetHitRate(), 0.5);
}

TEST(CPUCacheTest, WriteAndFlush) {
    CPUCache cache;
    EXPECT_FALSE(cache.Write(0x10LL, 0));
    EXPECT_FALSE(cache.IsDirty());

    EXPECT_TRUE(cache.Write(0x10LL, 32));
    EXPECT_TRUE(cache.IsDirty());

    cache.Flush();
    EXPECT_FALSE(cache.IsDirty());
}

TEST(CPUCacheTest, Invalidate) {
    CPUCache cache;
    cache.Write(0x10LL, 16);
    cache.Invalidate();

    EXPECT_EQ(cache.GetHits(), 0);
    EXPECT_EQ(cache.GetMisses(), 0);
    EXPECT_FALSE(cache.IsDirty());
}

TEST(CPUCacheTest, EqualityAndStream) {
    CPUCache c1(1, 32, 64);
    CPUCache c2(1, 32, 64);
    CPUCache c3(3, 16384, 128);

    EXPECT_TRUE(c1 == c2);
    EXPECT_TRUE(c1 != c3);

    std::stringstream ss;
    ss << c1;
    EXPECT_NE(ss.str().find("L1 Cache"), std::string::npos);
}