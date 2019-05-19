#include <stdio.h>
#include <string.h>

// 只定义结构体，使用struct Books cbook的方式实例化
 struct Books
{
    char title[50];
    char author[50];
    char subject[100];
    int book_id;
};

// 定义结构体并实例化，
struct Pen
{
    char brand[50];
    float price;
    int length;
} hero_pen;

// 创建结构体并定义别名，可直接使用别名实例化Company company;
typedef struct Companys
{
    char name[50];
    char location[50];
    char type[50];
} Company;



int main(void)
{
    struct Books cbook;

    strcpy(cbook.title, "Learn C");
    strcpy(cbook.author, "aaron");
    strcpy(cbook.subject, "basic");
    cbook.book_id = 1012;

    printf("图书标题：%s\n", cbook.title);
    printf("作者：%s\n", cbook.author);
    printf("图书类目：%s\n", cbook.subject);
    printf("图书编号：%d\n", cbook.book_id);

    // 实例化同时直接赋值
    struct Books gobook = {"Learn golang", "aaron", "basic", 1022};
    printf("标题：%s\n 作者： %s\n 类目：%s\n 编号：%d\n", gobook.title, gobook.author, gobook.subject, gobook.book_id);

    // 
    // hero_pen = {10.0, 20}; // 不能这样赋值了
    // hero_pen.brand = "英雄";
    strcpy(hero_pen.brand, "英雄");
    hero_pen.price = 10.0;
    hero_pen.length = 20;
    printf("钢笔品牌：%s\n价格：%f\n长度：%d(cm)\n", hero_pen.brand, hero_pen.price, hero_pen.length);

    Company company = {"C4X", "SH,CN", "TECH"};
    printf("Company Name:%s\nLocation:%s\nType:%s\n", company.name, company.location, company.type);

    return 0;
}
