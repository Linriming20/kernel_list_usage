#include <stdio.h>

#include "list.h"


typedef struct _class{
	char *name;
	struct list_head _list_head;
}class_t;


typedef struct _student{
	char *name;
	int age;
	int height;
	struct list_head _list_node;
}student_t;


int main(int argc, char *argv[])
{
	//printf("hello, world!\n");

	/* list head */
	class_t cls1 = {
		.name = "cls1",
	};
	INIT_LIST_HEAD(&cls1._list_head);

	/* _list_node 1 */
	student_t zhangsan = {
		.name = "zhangsan",
		.age = 17,
		.height = 170,
	};
	list_add_tail(&zhangsan._list_node, &cls1._list_head);

	/* _list_node 2 */
	student_t lisi = {.name = "lisi"};
	lisi.age = 18;
	lisi.height = 180;
	list_add_tail(&lisi._list_node, &cls1._list_head);

	/* _list_node 3 */
	student_t wangwu = {};
	wangwu.name = "wangwu";
	wangwu.age = 19;
	wangwu.height = 190;
	list_add_tail(&wangwu._list_node, &cls1._list_head);

	/* _list_node 4 */
	student_t chenliu;
	chenliu.name = "chenliu";
	chenliu.age = 20;
	chenliu.height = 200;
	list_add_tail(&chenliu._list_node, &cls1._list_head);

	/* 遍历一遍 */
	printf("==========================================\n");
	printf(">>> first traverse start!\n");
	while(1)
	{
		/* 判断链表是否为空 */
		//if(list_empty(cls1._list_head.next)) // 这样判断也可以
		if(list_empty(&cls1._list_head))
		{
			printf("<<< first traverse end!\n");
			break;
		}

		/* 取出链表节点所对应的宿主 */
		student_t *stu = list_entry(cls1._list_head.next, student_t, _list_node);
		printf("[name: %8s]  [age: %d]  [height: %d]\n", stu->name, stu->age, stu->height);

		/* 删除该链表节点 */
		list_del(&stu->_list_node);
	}

	printf("==========================================\n");

	/* 重新添加节点（乱序） */
	list_add(&zhangsan._list_node, &cls1._list_head);     /* 成为链表头下一个节点，可搭配`list_entry`先进后出实现"栈" */
	list_add(&lisi._list_node, &cls1._list_head);
	list_add_tail(&chenliu._list_node, &cls1._list_head); /* 成为链表头上一个节点，可搭配`list_entry`先进先出实现"队列" */
	list_add_tail(&wangwu._list_node, &cls1._list_head);

	if(!list_empty(&cls1._list_head))
	{
		student_t *stu = NULL;
		student_t *tmp = NULL;

		/* 链表不为空，再遍历一遍 */
		printf(">>> second traverse start!\n");
		list_for_each_entry_safe(stu, tmp, &cls1._list_head, _list_node) /* 已经自动取出链表节点所对应的宿主 */
		{
			printf("[name: %8s]  [age: %d]  [height: %d]\n", stu->name, stu->age, stu->height);

			/* 删除此链表节点 */
			list_del(&stu->_list_node);
		}
		printf("<<< second traverse end!\n");
	}
	printf("==========================================\n");

	if(list_empty(&cls1._list_head))
		printf("list is empty!\n");
	else
		printf("list is not empty!\n");

	printf("==========================================\n");

	return 0;
}

/*
==========================================
>>> first traverse start!
[name: zhangsan]  [age: 17]  [height: 170]
[name:     lisi]  [age: 18]  [height: 180]
[name:   wangwu]  [age: 19]  [height: 190]
[name:  chenliu]  [age: 20]  [height: 200]
<<< first traverse end!
==========================================
>>> second traverse start!
[name:     lisi]  [age: 18]  [height: 180]
[name: zhangsan]  [age: 17]  [height: 170]
[name:  chenliu]  [age: 20]  [height: 200]
[name:   wangwu]  [age: 19]  [height: 190]
<<< second traverse end!
==========================================
list is empty!
==========================================
*/