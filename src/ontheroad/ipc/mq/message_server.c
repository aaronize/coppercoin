#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

// 用于创建一个唯一的key
#define MSG_FILE "/tmp/test.msg"

// 消息结构体
typedef struct msg_form {
    long    mtype;
    char    mtext[256];
} msg_form;

int main()
{
    int         msqid;
    key_t       key;
    msg_form    msg;

    // ftok生成一个唯一key
    if ((key = ftok(MSG_FILE, 'z')) < 0)
    {
        perror("ftok error");
        exit(1);
    }

    printf("Message Queue - Server key is: %d.\n", key);

    // 创建消息队列
    if ((msqid = msgget(key, IPC_CREAT|0777)) < 0)
    {
        perror("msgget error");
        exit(1);
    }

    printf("the msqid: %d\n", msqid);
    printf("the pid: %d\n", getpid());

    // 循环读取消息
    for (;;)
    {
        msgrcv(msqid, &msg, 256, 888, 0);  // 返回类型为888的第一个消息
        printf("Server - receive msg.mtext: %s.\n", msg.mtext);
        printf("Server - receive msg.mtype: %s.\n", msg.mtype);

        msg.mtype = 999;  // 客户端接收的消息 
        sprintf(msg.mtext, "hello, this is server[%d]", getpid());
        msgsnd(msqid, &msg, sizeof(msg.mtext), 0);
    }

    return 0;
}
