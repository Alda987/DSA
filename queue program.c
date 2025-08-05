#include<stdio.h>
#define SIZE 100

int queue[SIZE];
int front = -1;
int rear = -1;

int isFull() {
	return rear == SIZE - 1;
}

int isEmpty() {
	return front ==  -1 || front > rear;
}

void enqueue(int item) {
	if(isFull()) {
		printf("The queue is full, element cannot be enqueued (Overflow) \n");
		return;
	}
	
	if(front == -1) {
		front = 0;
	}
	
	rear++;
	queue[rear] = item;
	printf("Enqueued element: %d \n", item);
}

int dequeue() {
	if(isEmpty()) {
		printf("The queue is empty, element cannot be dequeued (Underflow) \n");
		return -1;
	}
	
	int item = queue[front];
	front++;
	
	if (front > rear) {
        front = rear = -1;
    }
	
	return item;
}

void displayQueue() {
	if(isEmpty()) {
		printf("The queue is empty \n");
		return;
	}
	
	printf("The queue elements \n");
	
	for(int i = front; i <= rear; i++) {
		printf("%d \t", queue[i]);
	}
	
	printf("\n");
}

int main() {
	int choice, element;
	
	while(1) {
		printf("\nChoose an operation:\n");
		printf("1. Enqueue\n");
		printf("2. Dequeue\n");
		printf("3. Display Queue\n");
		printf("4. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		
		if(choice == 1) {
			printf("Enter the element to enqueue: ");
			scanf("%d", &element);
			enqueue(element);
		}
		
		else if(choice == 2) {
			element = dequeue();
			if(element != -1) {
				printf("Dequeued element: %d", element);
			}
		}
		
		else if(choice == 3) {
			printf("Display queue elements \n");
			displayQueue();
		}
		
		else if(choice == 4) {
			printf("Exiting program \n");
			break;
		}
		
		else {
			printf("Invalid choice, Enter valid choice!");
		}
	}
	
	return 0;
}