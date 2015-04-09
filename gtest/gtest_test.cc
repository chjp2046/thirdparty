// Copyright (c) 2012, Tencent Inc.
// All rights reserved.
//
// Author: CHEN Feng <phongchen@tencent.com>
// Created: 03/02/12
// Description:

#include "thirdparty/gtest/gtest.h"
#include <string>

TEST(GTest, Test)
{
    EXPECT_EQ(1, 1);
    std::string s = "hello";
    EXPECT_EQ("hello", s) << s;
}
