#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

int max(int a,int b)
{
	if(a>b)return a;
	return b;
}

typedef struct nd
{
	struct nd* left;
	struct nd* right;
	struct nd* parent;
	int cnt;
	int x;
}node;

typedef struct pq
{
	node* head;
}priority_queue;

priority_queue* initialize_priority_queue()
{
	priority_queue* pq = (priority_queue*)malloc(sizeof(priority_queue));
	pq->head = NULL;
	return pq;
}

void fix_up(node* now)
{
	if(now==NULL)return;
	if(now->parent == NULL)return;
	if(now->parent->x >= now->x)return;
	int temp = now->x;
	now->x = now->parent->x;
	now->parent->x = temp;
	fix_up(now->parent);
}
node* fix_down(node* now)
{
	if(now->left == NULL && now->right == NULL)return now;
	int down_max = INT_MIN;
	if(now->left != NULL)down_max=max(down_max,now->left->x);
	if(now->right != NULL)down_max=max(down_max,now->right->x);
	if(down_max < now->x)return now;
	if(now->left->x == down_max)
	{
		now->left->x = now->x;
		now->x = down_max;
		now=now->left;
	}
	else
	{
		now->right->x = now->x;
		now->x = down_max;
		now=now->right;
	}
	fix_down(now);
}

void add(priority_queue** _pq,int x)
{
	priority_queue* pq = *_pq;
	node* now = pq->head;
	node* prev = pq->head;
	bool left = false;
	while(now!=NULL)
	{
		prev = now;
		now->cnt++;
		if(now->left == NULL || now->right != NULL && now->left->cnt < now->right->cnt)now=now->left,left=true;
		else now=now->right,left=false;
	}
	node* new_element = (node*)malloc(sizeof(node));
	new_element->parent = NULL;
	new_element->left = NULL;
	new_element->right = NULL;
	new_element->x = x;
	if(prev==NULL){pq->head = new_element;return;}
	new_element->parent = prev;
	if(left)prev->left=new_element;
	else prev->right=new_element;
	fix_up(new_element);

}
int find_max(priority_queue* pq)
{
	if(pq->head == NULL){printf("Priority queue is empty!\n");return -1;}
	return pq->head->x;
}

void decrease_cnt(node* now)
{
	if(now==NULL)return;
	now->cnt -= 1;
	decrease_cnt(now->parent);
}

void remove_max(priority_queue** _pq)
{
	priority_queue* pq = *_pq;
	if(pq->head == NULL){printf("Priority queue is empty!\n");return ;}
	node* now = pq->head;
	now->x = INT_MIN;
	now = fix_down(now);
	decrease_cnt(now);
	if(now->parent->left == now)now->parent->left = NULL;
	if(now->parent->right == now)now->parent->right = NULL;
	free(now);
}

int main()
{
	srand(time(NULL));
	priority_queue* pq = initialize_priority_queue();
	add(&pq,5);
	printf("%d\n",find_max(pq));
	add(&pq,3);
	printf("%d\n",find_max(pq));
	add(&pq,7);
	printf("%d\n",find_max(pq));
	add(&pq,12);
	printf("%d\n",find_max(pq));
	add(&pq,1);
	printf("%d\n",find_max(pq));
	add(&pq,99);
	printf("%d\n",find_max(pq));
	add(&pq,87);
	printf("%d\n",find_max(pq));
	add(&pq,15);
	printf("%d\n",find_max(pq));
	add(&pq,123);
	printf("%d\n",find_max(pq));
	remove_max(&pq);
	printf("%d\n",find_max(pq));
	remove_max(&pq);
	printf("%d\n",find_max(pq));
	remove_max(&pq);
	printf("%d\n",find_max(pq));
	int n = (int)1e6;
	for(int i = 0; i < n; i++)
	{
		add(&pq,rand()%(n*100));
	}
	printf("%d\n",find_max(pq));
	printf("%d\n",pq->head->cnt);
	return 0;
}