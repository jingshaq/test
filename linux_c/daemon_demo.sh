#!/bin/sh
#
# daemon_demo         This shell script takes care of starting and stopping daemon_demo.
#
# chkconfig: 35 65 35
# description: daemon_demo is web servce I/O server, which is used to access files on remote hosts.
 
# Source function library.
. /etc/rc.d/init.d/functions
 
# Source networking configuration.
. /etc/sysconfig/network
 
# Check that networking is up.
[ ${NETWORKING} = "no" ] && exit 0
 
RETVAL=0
prog="daemon_demo"
WSIOARGS="-h $HOSTNAME -p 80 -t STANDALONE -k -c -d"
start() {
        # Start daemons.
        echo -n $"Starting $prog: "
        daemon /usr/local/bin/daemon_demo ${WSIOARGS}
        RETVAL=$?
        echo
        [ $RETVAL -eq 0 ] && touch /var/lock/subsys/daemon_demo
        return $RETVAL
}
stop() {
        # Stop daemons.
        echo -n $"Shutting down $prog: "
        killproc daemon_demo
        RETVAL=$?
        echo
        [ $RETVAL -eq 0 ] && rm -f /var/lock/subsys/daemon_demo
        return $RETVAL
}
 
# See how we were called.
case "$1" in
  start)
        start
        ;;
  stop)
        stop
        ;;
  restart|reload)
        stop
        start
        RETVAL=$?
        ;;
  status)
        status daemon_demo
        RETVAL=$?
        ;;
  *)
        echo $"Usage: $0 {start|stop|restart|status}"
        exit 1
esac
 
exit $RETVAL
