// Copyright 2011, Tencent Inc.
// Author: Bin Liu <rabbitliu@tencent.com>

/**
 * This is the example of how to connect a zk server use java client.
 */

import java.io.IOException;

import org.apache.zookeeper.KeeperException;
import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher;
import org.apache.zookeeper.ZooKeeper;
import org.apache.zookeeper.Watcher.Event.KeeperState;

public class ZkJavaClientTest implements Watcher {
    Object mutex = null;
    ZooKeeper zk = null;

    static {
        System.loadLibrary("taassw_java");
    }

    public ZkJavaClientTest() {
        mutex = new Object();
    }

    public boolean Connect(String zkHost, int timeout, String role, String identity ) {
        synchronized (mutex) {
            if (zk == null) {
                try {
                    zk = new ZooKeeper(zkHost, timeout, this, role, identity);
                    mutex.wait();
                    System.out.println("Create zk handle successful: " + zk);
                    return true;
                } catch (IOException e) {
                    e.printStackTrace();
                    zk = null;
                } catch (Exception e) {
                    e.printStackTrace();
                    zk = null;
                }
                return false;
            }
            return true;
        }
    }

    public boolean Connect(String zkHost, int timeout) {
        return Connect(zkHost, timeout, null, null);
    }

    public void process(WatchedEvent event) {
        // connected
        System.out.println("state = " + event.getState() + ", event = " + event.getType());
        if (event.getState() == KeeperState.SyncConnected) {
            synchronized (mutex) {
                mutex.notify();
            }
        }
    }

    public String getData(String path) {
        assert zk != null;
        byte[] data = null;
        try {
            data = zk.getData(path, false, null);
        } catch (KeeperException e) {
            System.out.println("Failed to getData, reason: " + e.getMessage());
            return null;
        } catch (InterruptedException e) {
            e.printStackTrace();
            return null;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
        return new String(data);
    }

    public void close() {
        try {
            if (zk != null) {
                zk.close();
                zk = null;
            }
        } catch (Exception e) {}
    }
}
