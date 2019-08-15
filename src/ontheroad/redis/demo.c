/*
redis C客户端 hiredis
git@github.com:redis/hiredis.git

usage：
git clone git@github.com:redis/hiredis.git
cd hiredis 
make
make install

build:
gcc demo.c -o demo -L/usr/local/lib -lhiredis
 */
#include <stdio.h>
#include <hiredis/hiredis.h>

int main(void)
{
    redisContext *conn = redisConnect("127.0.0.1", 6379);
    if (conn != NULL && conn->err)
    {
        printf("connection error:%s\n", conn->errstr);
        return 1;
    }

    redisReply *reply;
    reply = redisCommand(conn, "SET %s %s", "say", "Bonjour!");
    freeReplyObject(reply);

    reply = redisCommand(conn, "GET %s", "say");
    printf("%s\n", reply->str);
    freeReplyObject(reply);

    redisFree(conn);

    return 0;
}
