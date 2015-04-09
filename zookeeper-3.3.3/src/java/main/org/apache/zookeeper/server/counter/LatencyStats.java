// Copyright 2011, Tencent Inc.
// Author: Xiaokang Liu <hsiaokangliu@tencent.com>

package org.apache.zookeeper.server.counter;

import java.util.ArrayList;

class LatencyResult {
    public long minLatency = 0;
    public long maxLatency = 0;
    public long totalLatency = 0;
    public long sampleCount = 0;

    public void clear() {
        minLatency = 0;
        maxLatency = 0;
        totalLatency = 0;
        sampleCount = 0;
    }
}

public class LatencyStats {
    protected final static int kTimeWindowSize = 3600;
    protected long startTime;
    protected long lastTime;

    // statistical variable name.
    public String name;
    // overall latency since statistics begins.
    public LatencyResult overallLatency = new LatencyResult();
    // counting items which maintain the count of each second in the past hour.
    public LatencyResult latencyItems[] = new LatencyResult[kTimeWindowSize];

    private Object lock = new Object();

    public LatencyStats(String statName) {
        name = statName;
        startTime = -1;
        lastTime = -1;
        for (int i = 0; i < kTimeWindowSize; ++i) {
            latencyItems[i] = new LatencyResult();
        }
    }

    public ArrayList<LatencyResult> stats() {
        long timestamp =  System.currentTimeMillis() / 1000;
        ArrayList<LatencyResult> arrayList = new ArrayList<LatencyResult>();
        synchronized(lock) {
            LatencyResult result = getLatency(timestamp, 1);
            arrayList.add(result);
            result = getLatency(timestamp, 60);
            arrayList.add(result);
            result = getLatency(timestamp, 3600);
            arrayList.add(result);
            arrayList.add(overallLatency);
        }
        return arrayList;
    }

    public void addLatency(long latency, long timestampInMillis) {
        long timestamp = timestampInMillis / 1000;
        synchronized(lock) {
            if (startTime < 0) {
                // first value
                startTime = timestamp;
                lastTime = timestamp;
                overallLatency.sampleCount = 1;
                overallLatency.minLatency = latency;
                overallLatency.maxLatency = latency;
                overallLatency.totalLatency = latency;
                latencyItems[(int) (lastTime % kTimeWindowSize)].sampleCount = 1;
                latencyItems[(int) (lastTime % kTimeWindowSize)].minLatency = latency;
                latencyItems[(int) (lastTime % kTimeWindowSize)].maxLatency = latency;
                latencyItems[(int) (lastTime % kTimeWindowSize)].totalLatency = latency;
                return;
            }
            overallLatency.sampleCount++;
            overallLatency.totalLatency += latency;
            if (latency < overallLatency.minLatency) {
                overallLatency.minLatency = latency;
            }
            if (latency > overallLatency.maxLatency) {
                overallLatency.maxLatency = latency;
            }
            if (timestamp > lastTime) {
                if (timestamp - lastTime >= kTimeWindowSize) {
                    for (int i = 0; i < kTimeWindowSize; i++) {
                        latencyItems[i].clear();
                    }
                } else {
                    while (++lastTime != timestamp) {
                        latencyItems[(int) (lastTime % kTimeWindowSize)].clear();
                    }
                }
                lastTime = timestamp;
                latencyItems[(int) (lastTime % kTimeWindowSize)].sampleCount = 1;
                latencyItems[(int) (lastTime % kTimeWindowSize)].minLatency = latency;
                latencyItems[(int) (lastTime % kTimeWindowSize)].maxLatency = latency;
                latencyItems[(int) (lastTime % kTimeWindowSize)].totalLatency = latency;
            } else {
                // timestamp == lastTime
                latencyItems[(int) (lastTime % kTimeWindowSize)].sampleCount++;
                latencyItems[(int) (lastTime % kTimeWindowSize)].totalLatency += latency;
                if (latency < latencyItems[(int) (lastTime % kTimeWindowSize)].minLatency) {
                    latencyItems[(int) (lastTime % kTimeWindowSize)].minLatency = latency;
                }
                if (latency > latencyItems[(int) (lastTime % kTimeWindowSize)].maxLatency) {
                    latencyItems[(int) (lastTime % kTimeWindowSize)].maxLatency = latency;
                }
            }
        }
    }

    private LatencyResult getLatency(long timestamp, long length) {
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
        LatencyResult result = new LatencyResult();
        result.minLatency = Long.MAX_VALUE;
        result.maxLatency = 0;
        for (long i = begin; i <= end; ++i) {
            long val = latencyItems[(int) (i % kTimeWindowSize)].minLatency;
            if (val < result.minLatency) {
                result.minLatency = val;
            }
            val = latencyItems[(int) (i % kTimeWindowSize)].maxLatency;
            if (val > result.maxLatency) {
                result.maxLatency = val;
            }
            result.totalLatency +=
                latencyItems[(int) (i % kTimeWindowSize)].totalLatency;
            result.sampleCount +=
                latencyItems[(int) (i % kTimeWindowSize)].sampleCount;
        }
        if (result.minLatency == Long.MAX_VALUE) {
            result.minLatency = 0;
        }
        return result;
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        ArrayList<LatencyResult> arrayList = stats();
        LatencyResult secondResult = arrayList.get(0);
        LatencyResult minuteResult = arrayList.get(1);
        LatencyResult hourResult = arrayList.get(2);
        sb.append("second\t\t" + secondResult.minLatency + "\t" + secondResult.maxLatency + "\t" +
                (secondResult.sampleCount > 0 ? secondResult.totalLatency / secondResult.sampleCount : 0) +
                "\n");
        sb.append("minute\t\t" + minuteResult.minLatency + "\t" + minuteResult.maxLatency + "\t" +
                (minuteResult.sampleCount > 0 ? minuteResult.totalLatency / minuteResult.sampleCount : 0) +
                "\n");
        sb.append("hour\t\t" + hourResult.minLatency + "\t" + hourResult.maxLatency + "\t" +
                (hourResult.sampleCount > 0 ? hourResult.totalLatency / hourResult.sampleCount : 0) +
                "\n");
        sb.append("total\t\t" + overallLatency.minLatency + "\t" + overallLatency.maxLatency + "\t" +
                (overallLatency.sampleCount > 0 ? overallLatency.totalLatency / overallLatency.sampleCount : 0) +
                "\n");
        return sb.toString();
    }
}

