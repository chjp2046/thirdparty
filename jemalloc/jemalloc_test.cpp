// Copyright (c) 2012, Tencent Inc.
// All rights reserved.
//
// Author: CHEN Feng <phongchen@tencent.com>
// Created: 2012-05-02
// Description:

#include "thirdparty/jemalloc/jemalloc.h"
#include "thirdparty/jemalloc/jemalloc_defs.h"
#include "thirdparty/gtest/gtest.h"

TEST(Jemalloc, Test)
{
    void* p = malloc(100);
    EXPECT_TRUE(p != NULL);
    free(p);
}
