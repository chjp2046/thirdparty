// Copyright 2012, Tencent Inc.
// Author: Bin Liu <rabbitliu@tencent.com>

package org.apache.zookeeper;

import org.apache.log4j.Logger;
import org.apache.zookeeper.server.DataTree;
import org.apache.zookeeper.server.DataNode;

/**
 * this class manage the quotas related to a given role,
 * we store the quotas imformation under /zookeeper/role,
 * now quota means how many sessions a role can create.
 */

public class RoleRelatedQuotas
{
    private static final Logger LOG = Logger.getLogger(RoleRelatedQuotas.class);

    public static final String quotaZookeeper = "/zookeeper/role";
    public static final String limitNode = "quota_limits";
    public static final String statNode = "quota_stats";

    public static String limitPath(String role)
    {
        return quotaZookeeper + "/" + role + "/" + limitNode;
    }

    public static String statPath(String role)
    {
        return quotaZookeeper + "/" + role + "/" + statNode;
    }

    // get the quota limit of a given role.
    public static int getLimit(String role, DataTree dt) throws Exception {
        int limitQuota = -1;
        if (dt == null) {
            return limitQuota;
        }
        DataNode limitDataNode = dt.getNode(limitPath(role));
        if (limitDataNode == null) {
            return limitQuota;
        }
        String nodeData;
        synchronized (limitDataNode) {
            try {
                nodeData = new String(limitDataNode.getData());
            } catch (NullPointerException e) {
                return limitQuota;
            }
        }
        try {
            limitQuota = Integer.parseInt(nodeData);
        } catch(NumberFormatException e) {
            LOG.error("role: " + role + ", limit node has wrong fomat number.");
        }
        return limitQuota;
    }

    // get the quota used by a given role.
    public static int getStat(String role, DataTree dt) throws Exception {
        int statQuota = -1;
        if (dt == null) {
            return statQuota;
        }
        DataNode statDataNode = dt.getNode(statPath(role));
        if (statDataNode == null) {
            return statQuota;
        }
        String nodeData;
        synchronized (statDataNode) {
            try {
                nodeData = new String(statDataNode.getData());
            } catch(NullPointerException e) {
                return statQuota;
            }
        }
        try {
            statQuota = Integer.parseInt(nodeData);
        } catch(NumberFormatException e) {
            LOG.error("role: " + role + ", stat node has wrong fomat number.");
        }
        return statQuota;
   }
}
