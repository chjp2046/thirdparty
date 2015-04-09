if readlink -f "$0" > /dev/null 2>&1
then
  TESTSRC=`readlink -f "$0"`
else
  TESTSRC="$0"
fi
TESTDIR=`dirname "$TESTSRC"`

ZK_HOME="$TESTDIR"/../../../../../../../

CLASSPATH=$ZK_HOME/build/zookeeper-3.3.3.jar:$CLASSPATH

for i in $ZK_HOME/lib/*.jar
do
    CLASSPATH="$i:$CLASSPATH"
done

CLASSPATH="$ZK_HOME/build/classes:$ZK_HOME/src/java/lib/*.jar:$CLASSPATH"

javac -cp $ZK_HOME/build/zookeeper-3.3.3.jar *.java

java "-Djava.library.path=$ZK_HOME/lib" -cp  $CLASSPATH ConnectWithAuthTest
