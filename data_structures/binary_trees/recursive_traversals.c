/* Includes the functions for Recursive Traversals
   of a Binary Tree. It is assumed that nodes and
   tree have been created as per create_node.c
 */

#include <stdio.h>

void inOrderTraversal(struct node *node)
{
    if (node == NULL)  // if tree is empty
        return;

    inOrderTraversal(node->leftNode);
    printf("\t%d\t", node->data);
    inOrderTraversal(node->rightNode);
}

void preOrderTraversal(struct node *node)
{
    if (node == NULL)  // if tree is empty
        return;

    printf("\t%d\t", node->data);
    preOrderTraversal(node->leftNode);
    preOrderTraversal(node->rightNode);
}

void postOrderTraversal(struct node *node)
{
    if (node == NULL)  // if tree is empty
        return;

    postOrderTraversal(node->leftNode);
    postOrderTraversal(node->rightNode);
    printf("\t%d\t", node->data);
}

void printLevelOrder(struct node *node) {
       enque(node);
       while (!isEmpty()) {
           struct node* tempNode = deque();
           printf("\t%d\t", tempNode->data);

           /*add left child to the queue */
           if (tempNode->left != NULL) {
               enque(tempNode->left);
           }

           /*add right right child to the queue */
           if (tempNode->right != NULL) {
               enque(tempNode->right);
           }
       }
   }


int main(void)
{
    /* traversals can be done by simply invoking the
       function with a pointer to the root node.
    */

    return 0;
}
