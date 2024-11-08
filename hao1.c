#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100

// 定义客户结构体
typedef struct {
	int number;         // 取号序号
	char business[50];  // 业务类型
} Customer;

// 定义循环队列结构
typedef struct {
	Customer data[MAX_QUEUE_SIZE];  // 队列数组
	int front;                      // 队头指针
	int rear;                       // 队尾指针
	int currentNumber;              // 当前叫号
} CircularQueue;

// 初始化队列
void initQueue(CircularQueue *q) {
	q->front = 0;
	q->rear = 0;
	q->currentNumber = 0;
}

// 判断队列是否为空
int isEmpty(CircularQueue *q) {
	return q->front == q->rear;
}

// 判断队列是否已满
int isFull(CircularQueue *q) {
	return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// 入队操作
int enqueue(CircularQueue *q, char *business) {
	if (isFull(q)) {
		printf("队列已满，请稍后再试！\n");
		return 0;
	}
	
	// 创建新客户
	Customer newCustomer;
	newCustomer.number = ++(q->currentNumber);
	strcpy(newCustomer.business, business);
	
	// 将客户信息加入队列
	q->data[q->rear] = newCustomer;
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	
	return newCustomer.number;
}

// 出队操作
Customer dequeue(CircularQueue *q) {
	Customer customer = {0, ""};
	if (isEmpty(q)) {
		printf("队列为空！\n");
		return customer;
	}
	
	customer = q->data[q->front];
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return customer;
}

// 显示当前队列状态
void displayQueue(CircularQueue *q) {
	if (isEmpty(q)) {
		printf("当前没有等待的客户。\n");
		return;
	}
	
	printf("\n当前等待队列：\n");
	printf("序号\t业务类型\n");
	int i = q->front;
	while (i != q->rear) {
		printf("%d\t%s\n", q->data[i].number, q->data[i].business);
		i = (i + 1) % MAX_QUEUE_SIZE;
	}
	printf("\n");
}

int main() {
	CircularQueue queue;
	initQueue(&queue);
	int choice;
	char business[50];
	
	while (1) {
		printf("\n=== 银行叫号系统 ===\n");
		printf("1. 客户取号\n");
		printf("2. 下一位客户\n");
		printf("3. 显示等待队列\n");
		printf("4. 退出系统\n");
		printf("请选择操作(1-4): ");
		scanf("%d", &choice);
		
		switch (choice) {
		case 1:
			printf("请输入业务类型(存款/取款/咨询): ");
			scanf("%s", business);
			int number = enqueue(&queue, business);
			if (number > 0) {
				printf("取号成功！您的号码是：%d\n", number);
			}
			break;
			
		case 2:
			{
				Customer customer = dequeue(&queue);
				if (customer.number > 0) {
					printf("请 %d 号客户办理 %s 业务\n", 
						customer.number, customer.business);
				}
			}
			break;
			
		case 3:
			displayQueue(&queue);
			break;
			
		case 4:
			printf("感谢使用，再见！\n");
			return 0;
			
		default:
			printf("无效的选择，请重试！\n");
		}
	}
	
	return 0;
}
