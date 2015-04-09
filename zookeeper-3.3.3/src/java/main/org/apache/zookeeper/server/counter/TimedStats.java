// Copyright 2011, Tencent Inc.
// Author: Xiaokang Liu <hsiaokangliu@tencent.com>
// brief: request stat in one second/minute/hour and total.

package org.apache.zookeeper.server.counter;

class StatsResult {
    public long secondCount;
    public long minuteCount;
    public long hourCount;
    public long totalCount;
    public StatsResult() {
        secondCount = 0;
        minuteCount = 0;
        hourCount = 0;
        totalCount = 0;
    }
}

public class TimedStats {
    protected final static int kTimeWindowSize = 3600;
    protected long startTime;
    protected long lastTime;

    // statistical variable name.
    public String name;
    // total count since statistics begins.
    private long totalCount;
    // counting items which maintain the count of each second in the past hour.
    private long countItems[] = new long[kTimeWindowSize];

    private Object lock = new Object();

    public TimedStats(String statName) {
        startTime = -1;
        lastTime = -1;
        name = statName;
        totalCount = 0;
        for (int i = 0; i < kTimeWindowSize; ++i) {
            countItems[i] = 0;
        }
    }

    public StatsResult stats(long timestamp) {
        StatsResult result = new StatsResult();
        synchronized(lock) {
            result.secondCount = getCountsInLock(timestamp, 1);
            result.minuteCount = getCountsInLock(timestamp, 60);
            result.hourCount = getCountsInLock(timestamp, 3600);
            result.totalCount = totalCount;
        }
        return result;
    }

    public long getTotalCount() {
        synchronized(lock) {
            return totalCount;
        }
    }

    public long getSecondCount(long timestamp) {
        synchronized(lock) {
            return getCurrentSecondCountInLock(timestamp);
        }
    }

    public long getMaxCountOfPastSeconds(long timestamp, long timespan) {
        synchronized(lock) {
            long begin = timestamp - timespan;
            long end = timestamp - 1;
            if (begin < startTime) {
                begin = startTime;
            }
            if (begin < lastTime - kTimeWindowSize) {
                begin = lastTime - kTimeWindowSize;
            }
            if (end > lastTime) {
                end = lastTime;
            }
            long max = 0;
            for (long i = begin; i <= end; ++i) {
                if (countItems[(int) (i % kTimeWindowSize)] > max) {
                    max = countItems[(int) (i % kTimeWindowSize)];
                }
            }
            return max;
        }
    }

    public void addCount(long timestamp) {
        synchronized(lock) {
            addCountInLock(timestamp);
        }
    }

    public boolean addCountIfSecondCountLT(int maxCount, long timestamp) {
        synchronized(lock) {
            if (getCurrentSecondCountInLock(timestamp) < maxCount) {
                addCountInLock(timestamp);
                return true;
            }
            return false;
        }
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        long timestamp =  System.currentTimeMillis() / 1000;
        StatsResult result = stats(timestamp);
        sb.append(name + "\t" + result.secondCount + "\t" + result.minuteCount + "\t"
                + result.hourCount + "\t" + result.totalCount + "\n");
        return sb.toString();
    }

    private long getCurrentSecondCountInLock(long timestamp) {
        if (timestamp != lastTime) {
            return 0;
        }
        return countItems[(int) (lastTime % kTimeWindowSize)];
    }

    private long getCountsInLock(long timestamp, long length) {
        long begin = timestamp - length;
        long end = timestamp - 1;
        if (begin < startTime) {
            begin = startTime;
        }
        if (begin < lastTime - kTimeWindowSize) {
            begin = lastTime - kTimeWindowSize;
        }
        if (end > lastTime) {
            end = lastTime;
        }
        long count = 0;
        for (long i = begin; i <= end; ++i) {
            count += countItems[(int) (i % kTimeWindowSize)];
        }
        return count;
    }

    private void addCountInLock(long timestamp) {
        if (startTime < 0) {
            // first value
            startTime = timestamp;
            lastTime = timestamp;
            totalCount = 1;
            countItems[(int) (lastTime % kTimeWindowSize)] = 1;
            return;
        }
        totalCount++;
        if (timestamp > lastTime) {
            if (timestamp - lastTime >= kTimeWindowSize) {
                for (int i = 0; i < kTimeWindowSize; i++) {
                    countItems[i] = 0;
                }
            } else {
                while (++lastTime != timestamp) {
                    countItems[(int) (lastTime % kTimeWindowSize)] = 0;
                }
            }
            lastTime = timestamp;
            countItems[(int) (lastTime % kTimeWindowSize)] = 1;
        } else {
            // timestamp == lastTime
            countItems[(int) (lastTime % kTimeWindowSize)]++;
        }
    }
}

