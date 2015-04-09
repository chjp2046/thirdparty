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

#ifndef DLL_EXPORT
#  define USE_STATIC_LIB
#endif

#include "zookeeper_log.h"
#include <unistd.h>
#include <stdarg.h>
#include <time.h>
#include "thirdparty/glog/logging.h"

#define TIME_NOW_BUF_SIZE 1024
#define FORMAT_LOG_BUF_SIZE 4096

#ifdef THREADED
#include <pthread.h>

static pthread_key_t time_now_buffer;
static pthread_key_t format_log_msg_buffer;

void freeBuffer(void* p){
    if(p) free(p);
}

__attribute__((constructor)) void prepareTSDKeys() {
    pthread_key_create (&time_now_buffer, freeBuffer);
    pthread_key_create (&format_log_msg_buffer, freeBuffer);
}

char* getTSData(pthread_key_t key,int size){
    char* p = static_cast<char*>(pthread_getspecific(key));
    if(p==0){
        int res;
        p = static_cast<char*>(calloc(1,size));
        res=pthread_setspecific(key,p);
        if(res!=0){
            fprintf(stderr,"Failed to set TSD key: %d",res);
        }
    }
    return p;
}

char* get_time_buffer(){
    return getTSData(time_now_buffer,TIME_NOW_BUF_SIZE);
}

char* get_format_log_buffer(){  
    return getTSData(format_log_msg_buffer,FORMAT_LOG_BUF_SIZE);
}
#else
char* get_time_buffer(){
    static char buf[TIME_NOW_BUF_SIZE];
    return buf;    
}

char* get_format_log_buffer(){
    static char buf[FORMAT_LOG_BUF_SIZE];
    return buf;
}

#endif

void zoo_set_log_stream(FILE* stream)
{
}

static const char* time_now(){
    struct timeval tv;
    struct tm lt;
    time_t now = 0;
    size_t len = 0;
    char* now_str=get_time_buffer();
    
    if(!now_str)
        return "time_now(): Failed to allocate memory buffer";
    
    gettimeofday(&tv,0);

    now = tv.tv_sec;
    localtime_r(&now, &lt);

    // clone the format used by log4j ISO8601DateFormat
    // specifically: "yyyy-MM-dd HH:mm:ss,SSS"

    len = strftime(now_str, TIME_NOW_BUF_SIZE,
                          "%F %H:%M:%S",
                          &lt);

    len += snprintf(now_str + len,
                    TIME_NOW_BUF_SIZE - len,
                    ",%03d",
                    (int)(tv.tv_usec/1000));

    return now_str;
}

void log_message(ZooLogLevel curLevel, const char* fileName, int line,
    const char* message)
{
    int glog_level = 0;
    switch (curLevel) {
    case ZOO_LOG_LEVEL_ERROR:
        glog_level = google::ERROR;
        break;
    case ZOO_LOG_LEVEL_WARN:
        glog_level = google::WARNING;
        break;
    case ZOO_LOG_LEVEL_INFO:
        glog_level = google::INFO;
        break;
    case ZOO_LOG_LEVEL_DEBUG:
        glog_level = google::INFO;
        break;
    }

    if (curLevel != ZOO_LOG_LEVEL_DEBUG || VLOG_IS_ON(5)) {
        google::LogMessage log_message(fileName, line, glog_level);
        log_message.stream() << message;
    }
}

const char* format_log_message(const char* format,...)
{
    va_list va;
    char* buf=get_format_log_buffer();
    if(!buf)
        return "format_log_message: Unable to allocate memory buffer";
    
    va_start(va,format);
    vsnprintf(buf, FORMAT_LOG_BUF_SIZE-1,format,va);
    va_end(va); 
    return buf;
}

void zoo_set_debug_level(ZooLogLevel level)
{
}

