// Copyright 2012, Tencent Inc.
// Author: rabbitliu <rabbitliu@tencent.com>

package org.apache.zookeeper.server.counter;
import org.apache.log4j.Logger;
import java.util.HashMap;

// The counter for role-based operation and output like the following:
// ==========================================================================================
// Role             Con         R           W           Clo         PCon PR   PW   PClo AcCon
// ==========================================================================================
// xcube            1           1           0           1           1    1    0    1    0
// xfs_server       2           2           0           2           1    1    0    1    0
// twse_rel_merge   4           0           0           0           1    0    0    0    1

public class RoleOpCounter {
    private static final Logger LOG = Logger.getLogger(RoleOpCounter.class);

    static private class CounterInfo {
        public TimedStats createSessionStats = new TimedStats("CreateSession");
        public TimedStats closeSessionStats = new TimedStats("CloseSession");
        public TimedStats readStats = new TimedStats("Read");
        public TimedStats writeStats = new TimedStats("Write");
    } // end of class CounterInfo

    private final int sampleTime = 5 * 60;

    private static final int CREATESESSION = 11;
    private static final int READ = 12;
    private static final int WRITE = 13;
    private static final int CLOSESESSION = 14;
    private HashMap<String, CounterInfo> roleReportMap = new HashMap<String, CounterInfo>();

    public RoleOpCounter() {
    }

    public void addCreateSession(long timestamp, String role) {
        addCount(timestamp, role, CREATESESSION);
    }

    public void addRead(long timestamp, String role) {
        addCount(timestamp, role, READ);
    }

    public void addWrite(long timestamp, String role) {
        addCount(timestamp, role, WRITE);
    }

    public void addCloseSession(long timestamp, String role) {
        addCount(timestamp, role, CLOSESESSION);
    }

    private void addCount(long timestamp, String role, int type) {
        CounterInfo info = null;
        synchronized(this.roleReportMap) {
            info = roleReportMap.get(role);
            if (info == null) {
                info = new CounterInfo();
                roleReportMap.put(role, info);
            }
        }
        switch(type) {
        case CREATESESSION: {
            info.createSessionStats.addCount(timestamp);
            break;
        }
        case READ: {
            info.readStats.addCount(timestamp);
            break;
        }
        case WRITE: {
            info.writeStats.addCount(timestamp);
            break;
        }
        case CLOSESESSION: {
            info.closeSessionStats.addCount(timestamp);
            break;
        }
        default: {
            LOG.warn("Unknow operation type: " + type);
        }
        }
    }

    public String dump(HashMap<String, Integer> activeConnectionMap) {
        StringBuilder sb = new StringBuilder();
        sb.append("=========================================================================" +
                "===================================\n");
        sb.append(String.format("%-26.26s%-14s%-14s%-14s%-14s%-5s%-5s%-5s%-5s%-4s\n", "Role",
                    "Con", "R", "W", "Clo", "PCon", "PR", "PW", "PClo", "AcCon"));
        sb.append("=========================================================================" +
                "===================================\n");
        long timestamp = System.currentTimeMillis() / 1000;
        synchronized(roleReportMap) {
            for (String role : roleReportMap.keySet()) {
                CounterInfo info = roleReportMap.get(role);
                Integer activeConnectionNum = activeConnectionMap.get(role);
                if (activeConnectionNum == null) {
                    activeConnectionNum = 0;
                }
                sb.append(String.format("%-25.25s ", role));
                sb.append(String.format("%-14s%-14s%-14s%-14s%-5s%-5s%-5s%-5s%-4s\n",
                          info.createSessionStats.getTotalCount(),
                          info.readStats.getTotalCount(),
                          info.writeStats.getTotalCount(),
                          info.closeSessionStats.getTotalCount(),
                          info.createSessionStats.getMaxCountOfPastSeconds(timestamp, sampleTime),
                          info.readStats.getMaxCountOfPastSeconds(timestamp, sampleTime),
                          info.writeStats.getMaxCountOfPastSeconds(timestamp, sampleTime),
                          info.closeSessionStats.getMaxCountOfPastSeconds(timestamp, sampleTime),
                          activeConnectionNum));
            }
        }
        return sb.toString();
    }
}
