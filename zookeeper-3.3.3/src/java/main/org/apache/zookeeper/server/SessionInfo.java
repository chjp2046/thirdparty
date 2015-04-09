/**
 * this class manage the role and timeout associate with a session id
 */

package org.apache.zookeeper.server;

public class SessionInfo {
    private int timeout;
    private String role;

    public SessionInfo(int timeout, String role) {
        this.timeout = timeout;
        this.role = role;
    }

    public int getTimeout() {
        return this.timeout;
    }
    public String getRole() {
        return this.role;
    }
}


