/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ZK_LOG_H_
#define ZK_LOG_H_

#include "thirdparty/zookeeper-3.3.3/src/c/include/zookeeper.h"

#ifdef __cplusplus
extern "C" {
#endif

#define LOG_ERROR(x) log_message(ZOO_LOG_LEVEL_ERROR, __FILE__,__LINE__,format_log_message x)
#define LOG_WARN(x)  log_message(ZOO_LOG_LEVEL_WARN,__FILE__,__LINE__,format_log_message x)
#define LOG_INFO(x)  log_message(ZOO_LOG_LEVEL_INFO,__FILE__,__LINE__,format_log_message x)
#define LOG_DEBUG(x) log_message(ZOO_LOG_LEVEL_DEBUG, __FILE__,__LINE__,format_log_message x)

ZOOAPI void log_message(ZooLogLevel curLevel, const char* fileName, int line,
    const char* message);

ZOOAPI const char* format_log_message(const char* format,...) __attribute__((format(printf, 1, 2)));

#ifdef __cplusplus
}
#endif

#endif /*ZK_LOG_H_*/
