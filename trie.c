#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26

typedef struct nd
{
	struct nd* children[ALPHABET_SIZE];
	struct nd* parent;
	int cnt;
	int cnt_of_ending_here;
}node;

typedef struct tr
{
	node* root;
	int number_of_words;
}trie;

trie* initialize_trie()
{
	trie* t = (trie*)malloc(sizeof(trie));
	t->root = NULL;
	t->number_of_words = 0;
	return t;
}
node* initialize_node()
{
	node* _node = (node*)malloc(sizeof(node));
	_node->cnt=0;
	_node->cnt_of_ending_here=0;
	return _node;
}

void add(trie* t,char* word)
{
	int n = strlen(word);
	if(t->root == NULL)t->root=initialize_node();
	node* now = t->root;
	for(int i = 0; i < n; i++)
	{
		char z = *(word+i);
		int pos = z-'a';
		if(now->children[pos]==NULL)now->children[pos]=initialize_node();
		now->cnt++;
		now=now->children[pos];
	}
	now->cnt++;
	now->cnt_of_ending_here++;
}
bool check(trie* t,char* word)
{
	int n = strlen(word);
	if(t->root == NULL)return false;
	node* now = t->root;
	for(int i = 0; i < n; i++)
	{
		char z = *(word+i);
		int pos = z-'a';
		if(now->children[pos]==NULL)return false;
		now=now->children[pos];
	}
	if(now==NULL)return false;
	if(now->cnt_of_ending_here > 0)return true;
	return false;
}
void rem(trie* t,char* word)
{
	if(!check(t,word))return;
	int n = strlen(word);
	if(t->root == NULL)return;
	node* now = t->root;
	for(int i = 0; i < n; i++)
	{
		char z = *(word+i);
		int pos = z-'a';
		if(now->children[pos]==NULL)return;
		now->cnt--;
		now=now->children[pos];
	}
	now->cnt--;
	now->cnt_of_ending_here--;
}

int main()
{
	trie* t = initialize_trie();
	add(t,"abbba");
	add(t,"accccz");
	printf("%d\n",check(t,"ab"));
	printf("%d\n",check(t,"abbb"));
	printf("%d\n",check(t,"abbba"));
	add(t,"abbb");
	rem(t,"abbba");
	printf("%d\n",check(t,"abbb"));
	return 0;
}