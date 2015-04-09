// Copyright 2011, Tencent Inc.
// Author: Xiaokang Liu <hsiaokangliu@tencent.com>

package org.apache.zookeeper.server;
import org.apache.log4j.Logger;
import org.apache.zookeeper.ZooDefs;
import org.apache.zookeeper.ZooDefs.OpCode;

// Access logs.
public class AccessLog {
    private static final Logger LOG = Logger.getLogger(AccessLog.class);

    public static String opType2String(int type) {
        switch (type) {
            case ZooDefs.OpCode.notification:
                return "notification";
            case ZooDefs.OpCode.create:
                return "create";
            case ZooDefs.OpCode.delete:
                return "delete";
            case ZooDefs.OpCode.exists:
                return "exists";
            case ZooDefs.OpCode.getData:
                return "getData";
            case ZooDefs.OpCode.setData:
                return "setData";
            case ZooDefs.OpCode.getACL:
                return "getACL";
            case ZooDefs.OpCode.setACL:
                return "setACL";
            case ZooDefs.OpCode.getChildren:
                return "getChildren";
            case ZooDefs.OpCode.sync:
                return "sync";
            case ZooDefs.OpCode.ping:
                return "ping";
            case ZooDefs.OpCode.getChildren2:
                return "getChildren2";
            case ZooDefs.OpCode.auth:
                return "auth";
            case ZooDefs.OpCode.setWatches:
                return "setWatches";
            case ZooDefs.OpCode.createSession:
                return "createSession";
            case ZooDefs.OpCode.closeSession:
                return "closeSession";
        }
        return "unknown";
    }

    // e.g. [xfs] from [10.6.222.126] create [/zk/xaec/xfs]: 111ms
    public static void dump(String role, String address, int op, String path, long latency) {
        String item;
        if (role != null) {
            item = "[" + role + "] from ";
        } else {
            item = "[guest] from ";
        }
        if (address != null) {
            item += "[" + address + "] ";
        } else {
            item += "[unknown] ";
        }
        item += opType2String(op);
        if (path != null) {
            item += " [" + path + "]: ";
        } else {
            item += ": ";
        }
        item += latency + "ms";
        LOG.info(item);
    }
}
