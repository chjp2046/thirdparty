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

package org.apache.zookeeper.server.util;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;

import org.apache.log4j.Logger;

import org.apache.jute.InputArchive;
import org.apache.jute.OutputArchive;
import org.apache.jute.Record;
import org.apache.zookeeper.ZooDefs.OpCode;
import org.apache.zookeeper.server.DataTree;
import org.apache.zookeeper.server.ZooTrace;
import org.apache.zookeeper.txn.CreateSessionTxn;
import org.apache.zookeeper.txn.DeleteSessionTxn;
import org.apache.zookeeper.txn.CreateTxn;
import org.apache.zookeeper.txn.DeleteTxn;
import org.apache.zookeeper.txn.ErrorTxn;
import org.apache.zookeeper.txn.SetACLTxn;
import org.apache.zookeeper.txn.SetDataTxn;
import org.apache.zookeeper.txn.TxnHeader;
import org.apache.zookeeper.server.SessionInfo;

public class SerializeUtils {
    private static final Logger LOG = Logger.getLogger(SerializeUtils.class);

    public static Record deserializeTxn(InputArchive ia, TxnHeader hdr)
            throws IOException {
        hdr.deserialize(ia, "hdr");
        Record txn = null;
        switch (hdr.getType()) {
        case OpCode.createSession:
            // This isn't really an error txn; it just has the same
            // format. The error represents the timeout
            txn = new CreateSessionTxn();
            break;
        case OpCode.closeSession:
            txn = new DeleteSessionTxn();
            break;
        case OpCode.create:
            txn = new CreateTxn();
            break;
        case OpCode.delete:
            txn = new DeleteTxn();
            break;
        case OpCode.setData:
            txn = new SetDataTxn();
            break;
        case OpCode.setACL:
            txn = new SetACLTxn();
            break;
        case OpCode.error:
            txn = new ErrorTxn();
            break;
        }
        if (txn != null) {
            txn.deserialize(ia, "txn");
        }
        return txn;
    }

    /**
     * Author: rabbitliu
     * description: this method used to loadData from a given InputArchive,
     * @param dt the DataTree
     * @param ia the Inputstream of a snapshot
     * @param sessions the Map of session_id and session info
     * @param inOldFormat the way to read a snapshot, true means not read role information
     * */
    public static void deserializeSnapshot(DataTree dt,InputArchive ia,
            Map<Long, SessionInfo> sessions, boolean inOldFormat) throws IOException {
        int count = ia.readInt("count");
        while (count > 0) {
            long id = ia.readLong("id");
            int to = ia.readInt("timeout");
            String role = "guest";
            // in new way, we have the role information in snapshot.
            if (!inOldFormat) {
                try {
                    role = ia.readString("role");
                } catch(Exception e) {
                    // readString may call EOFException, IOException, NegativeArraySizeException
                    // but this method only throws IOException to upper application. we add this to
                    // catch Exception and throw IOException, then upper application can retry
                    // other snapshot format.
                    LOG.warn("exception in deserialize role. " + e);
                    throw new IOException("exception in deserialize role." + e);
                }
            }
            sessions.put(id, new SessionInfo(to, role));
            if (LOG.isTraceEnabled()) {
                ZooTrace.logTraceMessage(LOG, ZooTrace.SESSION_TRACE_MASK,
                        "loadData --- session in archive: " + id
                        + " with timeout: " + to);
            }
            count--;
        }
        dt.deserialize(ia, "tree");
    }

    public static void serializeSnapshot(DataTree dt,OutputArchive oa,
            Map<Long, SessionInfo> sessions) throws IOException {
        HashMap<Long, SessionInfo> sessSnap = new HashMap<Long, SessionInfo>(sessions);
        oa.writeInt(sessSnap.size(), "count");
        for (Entry<Long, SessionInfo> entry : sessSnap.entrySet()) {
            oa.writeLong(entry.getKey().longValue(), "id");
            oa.writeInt(entry.getValue().getTimeout(), "timeout");
            oa.writeString(entry.getValue().getRole(), "role");
        }
        dt.serialize(oa, "tree");
    }

}
