#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

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

    // 发送类型为888的消息
    msg.mtype = 888;
    sprintf(msg.mtext, "hello, this is client[%d]", getpid());
    msgsnd(msqid, &msg, sizeof(msg.mtext), 0);

    // 读取类型为999的消息
    msgrcv(msqid, &msg, 256, 999, 0);
    printf("Client - receive msg.mtext: %s\n", msg.mtext);
    printf("Client - receive msg.mtype: %s\n", msg.mtype);

    return 0;
}