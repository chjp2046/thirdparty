// Copyright (c) 2012, Tencent Inc.
// All rights reserved.
//
// Author: CHEN Feng <phongchen@tencent.com>
// Created: 2012-06-01

#include "thirdparty/gflags/gflags.h"
#include "thirdparty/gtest/gtest.h"

DEFINE_int32(xfs_master_port, 9527, "some bool value");
DEFINE_int32_alias(master_port, xfs_master_port);

DECLARE_int32(xfs_master_port);
DECLARE_int32(master_port);

TEST(Flags, Alias)
{
    ASSERT_EQ(9527, FLAGS_xfs_master_port);
    ASSERT_EQ(9527, FLAGS_master_port);
    ASSERT_EQ(&FLAGS_xfs_master_port, &FLAGS_master_port);
}
