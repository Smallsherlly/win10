#include "tree_list.h"
#include <malloc.h>
//创建树节点
Node* create_node(int data)
{
	Node* node = malloc(sizeof(Node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}
//树初始化
void tree_init(Tree* tree)
{
	tree->root = NULL;
	tree->size = 0;
}
void deinit(Node* root)
{
	if(root ==NULL) return;
	deinit(root->left);
	deinit(root->right);
	free(root);
}
//树释放
void tree_deinit(Tree* tree)
{
	deinit(tree->root);
	tree->root = NULL;
}
void Newinsert(Node** root,int data)
{
	Node* node = create_node(data);
	Node** root1 = root;
	while(1)
	{
		if(*root1 == NULL)
		{
			*root1 = node;

			return;ssssss
		}
		else
		{
			if((*root1)->data > node->data)
			{
				
				root1 = &(*root1)->left;
			}
			else
			{
				
				root1 = &(*root1)->right;
				
			}
		}
	}
}
//向树中插入一个节点
static void insert(Node** root,Node* node)
{
	
	if(*root == NULL)
	{
		*root = node;
	}
	else
	{
		if((*root)->data > node->data)
		{
			insert(&(*root)->left,node);
		}
		else
		{
			insert(&(*root)->right,node);
		}
	}
}
//向树中插入一个节点
void tree_insert(Tree* tree,int data)
{
	insert(&tree->root,create_node(data));
}
Node* find(Node* root,int data);

bool delete(Node** root,int data)
{
	if(*root == NULL) return false;
	if((*root)->data == data)
	{
		Node* temp = *root;
		Node* right = (*root)->right;

		*root = (*root)->left;
		insert(root,right);
		free(temp);
		return true;

	}
	if((*root)->data > data)
	{
		delete(&(*root)->left,data);
	}
	else
	{
		delete(&(*root)->right,data);
	}

}
//从树中删除一个节点
bool tree_delete(Tree* tree,int data)
{
	return delete(&tree->root,data);
}
//修改指定的值
bool tree_modify(Tree* tree,int old,int new)
{
	if(delete(&tree->root,old));
	{
		insert(&tree->root,create_node(new));
		return true;
	}
	return false;

}

Node* find(Node* root,int data)
{
	if(root == NULL) return NULL;
	if(root->data == data) return root;
	if(root->data > data)
	{
		find(root->left,data);
	}
	else
	{
		find(root->right,data);
	}
}
//查找指定值一个节点
Node* tree_find(Tree* tree,int data)
{
	return find(tree->root,data);
}
void ergodic(Node* root)
{
	if(root == NULL) return;
	ergodic(root->left);
	printf("%d ",root->data);
	ergodic(root->right);
}
//中序遍历树
void tree_show(Tree* tree)
{
	ergodic(tree->root);
	printf("\n");
}



