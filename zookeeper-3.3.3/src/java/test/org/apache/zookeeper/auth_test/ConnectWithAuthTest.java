// Copyright 2012, Tencent Inc.
// Author: Bin Liu <rabbitliu@tencent.com>

/**
 * This is the example of how to connect to a zk server use java client.
 */

public class ConnectWithAuthTest {
    public static void main(String[] argv) {
        // Authentication example
        ZkJavaClientTest client = new ZkJavaClientTest();
        if (!client.Connect("tjnl.zk.oa.com:2181", 3000, "zk_test", "rabbitliu")) {
            System.out.println("connect error.");
            return;
        }
        String data = client.getData("/zk/tjnl/xcube/rabbit_test");
        if (data != null) {
            System.out.println("data: " + data);
        }
        client.close();

        // Connect to old server.
        if (!client.Connect("xaec.zk.oa.com:2181", 3000)) {
            System.out.println("connect error.");
            return;
        }
        data = client.getData("/zk/xaec/xcube/rabbit_test");
        if (data != null) {
            System.out.println("data: " + data);
        }
        client.close();

        // Connect to old server with role and id.
        if (!client.Connect("xaec.zk.oa.com:2181", 3000, "zk_test", "rabbitliu")) {
            System.out.println("connect error.");
            return;
        }
        data = client.getData("/zk/xaec/xcube/rabbit_test");
        if (data != null) {
            System.out.println("data: " + data);
        }
        client.close();
    }
}
