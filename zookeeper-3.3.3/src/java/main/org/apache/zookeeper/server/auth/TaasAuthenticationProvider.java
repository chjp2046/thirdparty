// Copyright 2012, Tencent Inc.
// Author: Bin Liu <rabbitliu@tencent.com>

/**
 * this class authenticate the role of a client connection use taas api,
 * check the role's quota, and help check acl when do some node operation.
 */

package org.apache.zookeeper.server.auth;

import org.apache.log4j.Logger;
import org.apache.zookeeper.KeeperException;
import org.apache.zookeeper.RoleRelatedQuotas;
import org.apache.zookeeper.data.Id;
import org.apache.zookeeper.server.DataTree;
import org.apache.zookeeper.server.NIOServerCnxn;
import org.apache.zookeeper.server.ServerCnxn;

import com.soso.taassw.*;

public class TaasAuthenticationProvider implements AuthenticationProvider
{
    private static final Logger LOG =
        Logger.getLogger(TaasAuthenticationProvider.class);

    private static CredentialVerifier taasVerifier = null;

    static {
        System.loadLibrary("taassw_java");
        // Java system property: zookeeper.enableTaasTestEnv
        // Add "-Dzookeeper.enableTaasTestEnv=yes" in zk server start script to
        // enable taas test env
        if (System.getProperty("zookeeper.enableTaasTestEnv", "no").equals("yes")) {
            WrapClient.TaasForTest();
            LOG.info("Use taas test environment.");
        }
        // create local taas verifier.
        taasVerifier = ServerUtility.CreateLocalCredtialVerifier("zk_server", "zk_server");
    }

    public String getScheme()
    {
        return "taas";
    }

    // return true means have quota.
    private boolean hasQuota(NIOServerCnxn cnxn, String role)
    {
        // zk_admin always have quota.
        if (role.equals("zk_admin")) {
            return true;
        }

        try {
            DataTree dt = cnxn.getCnxnFactory().getZkServer().getZKDatabase().getDataTree();
            int maxQuota = RoleRelatedQuotas.getLimit(role, dt);
            // -1 means this limit node does not exist, or the data in
            // this node is not a number.
            if (maxQuota <= 0) {
                return false;
            }
            // -1 means this stat node does not exist, or the data in
            // this node is not a number.
            int roleStatCount = RoleRelatedQuotas.getStat(role, dt);
            if (roleStatCount < 0) {
                return false;
            }
            // quota exceed limit.
            if (roleStatCount >= maxQuota) {
                return false;
            }
            return true;
        } catch(Exception e) {
            LOG.error("occur exceptions:", e);
        }
        return false;
    }

    @SuppressWarnings("serial")
    static class TaasVerfierException extends Exception
    {
        TaasVerfierException(String msg) {
            super(msg);
        }
    }

    public KeeperException.Code
        handleAuthentication(ServerCnxn cnxn, byte[] credential)
    {
        // if no credential received, defaultly set role to "guest"
        String role = "guest";
        String identity = "guest";
        String clientIp = cnxn.getRemoteAddress().getAddress().getHostAddress();
        try {
            if (credential != null && credential.length != 0) {
                LOG.debug("user credential len: " + credential.length + ", credential value: "
                        + new String(credential));
                if (taasVerifier == null) {
                    taasVerifier =
                        ServerUtility.CreateLocalCredtialVerifier("zk_server", "zk_server");
                    if (taasVerifier == null) {
                        // can Not verify role, treat it as guest now.
                        throw new TaasAuthenticationProvider.
                            TaasVerfierException("create taas verifier failure");
                    }
                }
                DummyVerifyCompleteCallback callback = new DummyVerifyCompleteCallback();
                SWIGTYPE_p_ClosureT_void_std__string_const_p_std__string_const_p_int_t
                    done = callback.GetCallBack();
                taasVerifier.Verify(credential, clientIp, done);
                callback.WaitUtilCallback();
                if (TaasCredentialVerifier.VerifyResult.kSuccess.swigValue()
                        != callback.ErrCode()) {
                    LOG.warn("[" + clientIp + "] taas verfify error, return code: "
                            + callback.ErrCode());
                    return KeeperException.Code.AUTHFAILED;
                }
                role = callback.UserRole();
                identity = callback.UserId();
                LOG.debug("client log in, role: " + role + ", identity: " + identity);
            }
        } catch (Exception e) {
            LOG.error("[" + clientIp + "] occur an exception when taas verifying: ", e);
            role = "guest";
            identity = "guest";
        }
        cnxn.setRole(role);
        // authentication success, check quota.
        if (!cnxn.getReopenOldSession() && !hasQuota((NIOServerCnxn)cnxn, role)) {
            return KeeperException.Code.NOQUOTA;
        }
        // all successful.
        // only allow one role in AuthInfo.
        cnxn.getAuthInfo().clear();
        if (role.equals("zk_admin")) {
            // first super means super scheme, zk will not check ACL in this scheme
            // second 'zkadmin' is the roleName of super role.
            cnxn.getAuthInfo().add(new Id("super", "zk_admin:"));
        } else {
            cnxn.getAuthInfo().add(new Id(getScheme(), role + ":"));
        }
        return KeeperException.Code.OK;
    }

    // if you want to use auth scheme, this method will return true, or it return false.
    public boolean isAuthenticated()
    {
        return true;
    }

    // if this return false it will raise ZINVALIDACL exception.
    // id like role:identity.
    public boolean isValid(String id)
    {
        String parts[] = id.split(":");
        return parts.length == 2;
    }

    // compaire the author information and the acl information in a node.
    public boolean matches(String id, String aclExpr)
    {
        // isValid already called, so do Not need handle error of id and aclExpr.
        String id_role = id.split(":")[0];
        String aclExpr_role = aclExpr.split(":")[0];
        return id_role.equals(aclExpr_role);
    }
}
