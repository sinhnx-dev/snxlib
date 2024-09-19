#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <snxlib.h>

// snxlib more functions
void clearKeyboardBuffer()
{
    // clear keyboard buffer on UNIX
    fseek(stdin, 0, SEEK_END);
    // clear keyboard buffer on Windows
    fflush(stdin);
}
void getString(char *str, int length)
{
    clearKeyboardBuffer();
    // input string
    fgets(str, length, stdin);
    str[strlen(str) - 1] = '\0';
    clearKeyboardBuffer();
}
int menu(const char *title, int menuItemCount, char *menuItem[])
{
    int i = 0, choice;
    printf("==============================\n");
    printf(" %s\n", title);
    printf("==============================\n");
    for (; i < menuItemCount; i++)
    {
        printf(" %d. %s \n", i + 1, menuItem[i]);
    }
    printf("==============================\n");
    do
    {
        printf("Your choice: ");
        clearKeyboardBuffer();
        scanf("%d", &choice);
    } while (choice <= 0 || choice > menuItemCount);
    return choice;
}
void waitEnterPress(char *msg)
{
    printf("%s\n", msg);
    clearKeyboardBuffer();
    getchar();
}

// Stack ADT
Stack *initStack(unsigned int sizeOfElement)
{
    if (sizeOfElement <= 0)
    {
        return NULL;
    }
    Stack *s;
    s = (Stack *)malloc(sizeof(Stack));
    s->sizeOfElement = sizeOfElement;
    s->top = NULL;
    return s;
}
int sPush(Stack *s, void *newElement)
{
    if (s == NULL || newElement == NULL)
    {
        return 0;
    }
    sNode *newNode;
    newNode = (sNode *)malloc(sizeof(sNode));
    newNode->data = malloc(s->sizeOfElement);
    memcpy(newNode->data, newElement, s->sizeOfElement);
    newNode->next = s->top;
    s->top = newNode;
    return 1;
}
int sIsEmpty(Stack *s)
{
    return s == NULL || s->top == NULL;
}
void *sPop(Stack *s)
{
    if (sIsEmpty(s))
    {
        return NULL;
    }
    void *topValue;
    topValue = s->top->data;
    sNode *topNode;
    topNode = s->top;
    s->top = s->top->next;
    free(topNode);
    return topValue;
}
void *sPeek(Stack *s)
{
    if (sIsEmpty(s))
    {
        return NULL;
    }
    return s->top->data;
}

// Queue ADT
Queue *initQueue(unsigned int sizeOfElement)
{
    if (sizeOfElement <= 0)
    {
        return NULL;
    }
    Queue *q;
    q = (Queue *)malloc(sizeof(Queue));
    q->sizeOfElement = sizeOfElement;
    q->front = NULL;
    q->rear = NULL;
    return q;
}
int qIsEmpty(Queue *q)
{
    return q->front == NULL;
}
int qEnqueue(Queue *q, void *newElement)
{
    qNode *newNode;
    newNode = (qNode *)malloc(sizeof(qNode));
    newNode->data = malloc(q->sizeOfElement);
    memcpy(newNode->data, newElement, q->sizeOfElement);
    newNode->next = q->rear;
    q->rear = newNode;
    if (qIsEmpty(q))
    {
        q->front = newNode;
    }
    return 1;
}
void *qDequeue(Queue *q)
{
    if (qIsEmpty(q))
    {
        return NULL;
    }
    void *frontElement;
    frontElement = q->front->data;
    qNode *front;
    front = q->front;
    if (q->front == q->rear)
    {
        q->front = NULL;
        q->rear = NULL;
    }
    else
    {
        qNode *it;
        for (it = q->rear; it->next != q->front; it = it->next)
            ;
        q->front = it;
    }
    free(front);
    return frontElement;
}

// ArrayList ADT
ArrayList *alInit(unsigned sizeOfElement, unsigned int maxElements)
{
    if (sizeOfElement <= 0)
    {
        return NULL;
    }
    ArrayList *al;
    al = (ArrayList *)malloc(sizeof(ArrayList));
    if (maxElements <= 0)
    {
        al->maxElements = 16;
    }
    else
    {
        al->maxElements = maxElements;
    }
    al->sizeOfElement = sizeOfElement;
    al->count = 0;
    al->data = malloc(sizeOfElement * al->maxElements);
    return al;
}
int alInsert(ArrayList *al, void *newElement)
{
    if (al->count == al->maxElements)
    {
        al->maxElements = al->maxElements + al->maxElements / 2;
        al->data = realloc(al->data, sizeof(al->sizeOfElement) * al->maxElements);
    }
    // al->data[al->count] = *newElement;
    memcpy(al->data + al->count * al->sizeOfElement, newElement, al->sizeOfElement);
    al->count++;
    return 1;
}

int alInsertAt(ArrayList *al, void *newElement, unsigned position)
{
    if (position < 0 || position > al->count)
    {
        return 0;
    }
    if (al->count == al->maxElements)
    {
        al->maxElements = al->maxElements + al->maxElements / 2;
        al->data = realloc(al->data, sizeof(al->sizeOfElement) * al->maxElements);
    }
    for (int i = al->count; i > position; i--)
    {
        // al->data[i] = al->data[i-1];
        memcpy(al->data + i * al->sizeOfElement, al->data + (i - 1) * al->sizeOfElement, al->sizeOfElement);
    }
    // al->data[position] = *newElement;
    memcpy(al->data + position * al->sizeOfElement, newElement, al->sizeOfElement);
    al->count++;
    return 1;
}
void *alGetAt(ArrayList *al, unsigned position)
{
    if (position >= al->count)
    {
        return NULL;
    }
    return al->data + position * al->sizeOfElement;
}
int alRemoveAt(ArrayList *al, unsigned position)
{
    int count = al->count;
    if (position < 0 || position >= count)
    {
        return 0;
    }
    for (int i = position; i < count - 1; i++)
    {
        memcpy(al->data + i * al->sizeOfElement, al->data + (i + 1) * al->sizeOfElement, al->sizeOfElement);
    }
    al->count--;
    return 1;
}
int alIsEmpty(ArrayList *al)
{
    return al->count == 0;
}
void alShowInfo(ArrayList *al)
{
    printf("ArrayList->count = %d\n", al->count);
    printf("ArrayList->maxElements = %d\n", al->maxElements);
    printf("ArrayList->sizeOfElement = %d\n", al->sizeOfElement);
}
void alDestroy(ArrayList *al)
{
    free(al->data);
    free(al);
}
int alSaveToFile(ArrayList *al, const char *path)
{
    if (al == NULL || al->data == NULL || al->count == 0)
    {
        return 0;
    }
    FILE *f;
    f = fopen(path, "wb");
    if (f == NULL)
    {
        return 0;
    }
    fwrite(&(al->count), sizeof(unsigned int), 1, f);
    fwrite(&(al->maxElements), sizeof(unsigned int), 1, f);
    fwrite(&(al->sizeOfElement), sizeof(unsigned int), 1, f);
    fwrite(al->data, al->sizeOfElement, al->count, f);
    fclose(f);
    return 1;
}
ArrayList *alLoadFromFile(const char *path)
{
    FILE *f;
    f = fopen(path, "rb");
    if (f == NULL)
    {
        return NULL;
    }
    ArrayList *al;
    al = (ArrayList *)malloc(sizeof(ArrayList));
    fread(&(al->count), sizeof(unsigned int), 1, f);
    fread(&(al->maxElements), sizeof(unsigned int), 1, f);
    fread(&(al->sizeOfElement), sizeof(unsigned int), 1, f);
    al->data = malloc(al->sizeOfElement * al->maxElements);
    fread(al->data, al->sizeOfElement, al->count, f);
    fclose(f);
    return al;
}

// LinkedList ADT
LinkedList *llInit(unsigned sizeOfElement)
{
    if (sizeOfElement <= 0)
    {
        return NULL;
    }
    LinkedList *ll;
    ll = (LinkedList *)malloc(sizeof(LinkedList));
    ll->sizeOfElement = sizeOfElement;
    ll->head = NULL;
    ll->it = NULL;
    return ll;
}
int llInsert(LinkedList *ll, void *newElement)
{
    if (ll == NULL || ll->sizeOfElement <= 0 || newElement == NULL)
    {
        return 0;
    }
    llNode *newNode;
    newNode = (llNode *)malloc(sizeof(llNode));
    newNode->data = malloc(ll->sizeOfElement);
    memcpy(newNode->data, newElement, ll->sizeOfElement);
    newNode->next = ll->head;
    ll->head = newNode;
    return 1;
}
int llInsertAt(LinkedList *ll, void *newElement, unsigned position)
{
    if (position == 0)
    {
        return llInsert(ll, newElement);
    }
    if (ll == NULL || ll->sizeOfElement <= 0 || position < 0)
    {
        return 0;
    }
    llNode *cur, *pre;
    cur = ll->head;
    int i = 0;
    while (cur != NULL && i < position)
    {
        pre = cur;
        cur = cur->next;
        i++;
    }
    if (cur == NULL && i < position)
    {
        return 0;
    }
    llNode *newNode;
    newNode = (llNode *)malloc(sizeof(llNode));
    newNode->data = malloc(ll->sizeOfElement);
    memcpy(newNode->data, newElement, ll->sizeOfElement);
    pre->next = newNode;
    newNode->next = cur;
    return 1;
}
int llIsEmpty(LinkedList *ll)
{
    if (ll == NULL || ll->sizeOfElement <= 0 || ll->head == NULL)
    {
        return 1;
    }
    return 0;
}
void *llGetAt(LinkedList *ll, unsigned int position)
{
    if (position < 0)
    {
        return NULL;
    }
    llNode *cur;
    int i;
    for (cur = ll->head, i = 0; i < position && cur != NULL; cur = cur->next, i++)
        ;
    if (cur == NULL)
    {
        return NULL;
    }
    return cur->data;
}
int llRemove(LinkedList *ll)
{
    if (llIsEmpty(ll))
    {
        return 0;
    }
    llNode *delFirst;
    delFirst = ll->head;
    ll->head = ll->head->next;
    free(delFirst);
    return 1;
}
int llRemoveAt(LinkedList *ll, unsigned int position)
{
    if (position == 0)
    {
        return llRemove(ll);
    }
    if (llIsEmpty(ll) || position < 0)
    {
        return 0;
    }
    llNode *cur, *pre;
    cur = ll->head;
    int i = 0;
    while (cur != NULL && i < position)
    {
        pre = cur;
        cur = cur->next;
        i++;
    }
    if (cur == NULL)
    {
        return 0;
    }
    pre->next = cur->next;
    free(cur);
    return 1;
}
int llInitIterator(LinkedList *ll)
{
    if (ll->head == NULL)
    {
        return 0;
    }
    ll->it = ll->head;
    return 1;
}
int llHasNext(LinkedList *ll)
{
    if (ll->head == NULL || ll->sizeOfElement <= 0 || ll->it == NULL)
    {
        return 0;
    }
    return 1;
}
void *llNext(LinkedList *ll)
{
    void *pCur;
    pCur = ll->it->data;
    ll->it = ll->it->next;
    return pCur;
}
void llDestroy(LinkedList *ll)
{
    llNode *curNode, *delNode;
    curNode = ll->head;
    while (curNode != NULL)
    {
        delNode = curNode;
        curNode = curNode->next;
        free(delNode);
    }
    free(ll);
}
int llSaveToFile(LinkedList *ll, const char *path)
{
    if (path == NULL || ll == NULL || llIsEmpty(ll))
    {
        return 0;
    }
    FILE *f = fopen(path, "wb");
    if (f == NULL)
    {
        return 0;
    }
    fwrite(&(ll->sizeOfElement), sizeof(unsigned int), 1, f);
    llNode *cur;
    cur = ll->head;
    while (cur != NULL)
    {
        fwrite(cur->data, ll->sizeOfElement, 1, f);
        cur = cur->next;
    }
    fclose(f);
    return 1;
}
LinkedList *llLoadFromFile(const char *path)
{
    if (path == NULL)
    {
        return NULL;
    }
    FILE *f = fopen(path, "rb");
    if (f == NULL)
    {
        return NULL;
    }
    LinkedList *ll;
    ll = (LinkedList *)malloc(sizeof(LinkedList));
    fread(&(ll->sizeOfElement), sizeof(unsigned int), 1, f);
    if (ll->sizeOfElement <= 0)
    {
        return NULL;
    }
    ll->head = NULL;
    llNode *cur, *pre;
    void *temp;
    int i = 0;
    while (!feof(f))
    {
        temp = malloc(ll->sizeOfElement);
        if (fread(temp, ll->sizeOfElement, 1, f) > 0)
        {
            llInsertAt(ll, temp, i++);
        }
    }
    fclose(f);
    return ll;
}

// Binary Search Tree ADT
BinarySearchTree *bstInitRoot(void *root, unsigned int sizeOfElement, nodeCompare *nodecmp)
{
    if (sizeOfElement <= 0 || nodecmp == NULL)
        return NULL;
    BinarySearchTree *bst = (BinarySearchTree *)malloc(sizeof(BinarySearchTree));
    bst->sizeOfElement = sizeOfElement;
    bst->nodecmp = nodecmp;
    bst->root = root;
    return bst;
}
BinarySearchTree *bstInit(unsigned int sizeOfElement, nodeCompare *nodecmp)
{
    if (sizeOfElement <= 0 || nodecmp == NULL)
        return NULL;
    return bstInitRoot(NULL, sizeOfElement, nodecmp);
}
void btDestroyRoot(btNode *root)
{
    if (root != NULL)
    {
        free(root->data);
        btDestroyRoot(root->left);
        btDestroyRoot(root->right);
        free(root);
    }
}
void bstDestroy(BinarySearchTree *bst)
{
    btDestroyRoot(bst->root);
    free(bst);
}
int bstInsertNode(BinarySearchTree *bst, btNode *newNode)
{
    if (newNode == NULL)
        return 0;
    if (bst->root == NULL)
        bst->root = newNode;
    else
    {
        btNode *cur, *parent;
        cur = bst->root;
        parent = NULL;
        while (1)
        {
            parent = cur;
            // go to left of the tree
            if (bst->nodecmp(newNode->data, parent->data) < 0)
            {
                cur = cur->left;
                // insert to the left
                if (cur == NULL)
                {
                    parent->left = newNode;
                    break;
                }
            }
            else
            {
                cur = cur->right;
                // insert to the right
                if (cur == NULL)
                {
                    parent->right = newNode;
                    break;
                }
            }
        }
    }
    return 1;
}
int bstInsert(BinarySearchTree *bst, void *newElement)
{
    if (newElement == NULL)
        return 0;
    btNode *newNode = (btNode *)malloc(sizeof(btNode));
    newNode->data = malloc(bst->sizeOfElement);
    memcpy(newNode->data, newElement, bst->sizeOfElement);
    newNode->left = NULL;
    newNode->right = NULL;
    return bstInsertNode(bst, newNode);
}
void bstTraversal(btNode *root, traversalFunc *tf)
{
    if (root == NULL)
        return;
    bstTraversal(root->left, tf);
    tf(root->data);
    bstTraversal(root->right, tf);
}
void bstTraversalDesc(btNode *root, traversalFunc *tf)
{
    if (root == NULL)
        return;
    bstTraversalDesc(root->right, tf);
    tf(root->data);
    bstTraversalDesc(root->left, tf);
}
void bstTraversalCondition(btNode *root, nodeCompare *nodeCmp, const void *key, traversalFunc tf)
{
    if (root == NULL)
        return;
    if (!nodeCmp(root->data, key))
        tf(root->data);
    bstTraversalCondition(root->left, nodeCmp, key, tf);
    bstTraversalCondition(root->right, nodeCmp, key, tf);
}
btNode *bstMinNode(btNode *root)
{
    if (root == NULL || root->left == NULL)
        return root;
    else
        return bstMinNode(root->left);
}
btNode *bstRemoveNode(btNode *root, void *deleteElement, nodeCompare *nodecmp, unsigned int sizeOfElement)
{
    if (root == NULL)
        return root;
    if (nodecmp(deleteElement, root->data) < 0)
        root->left = bstRemoveNode(root->left, deleteElement, nodecmp, sizeOfElement);
    else if (nodecmp(deleteElement, root->data) > 0)
        root->right = bstRemoveNode(root->right, deleteElement, nodecmp, sizeOfElement);
    else
    {
        if (root->left == NULL)
        {
            btNode *temp = root->right;
            free(root->data);
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            btNode *temp = root->left;
            free(root->data);
            free(root);
            return temp;
        }
        else
        {
            btNode *temp = bstMinNode(root->right);
            memcpy(root->data, temp->data, sizeOfElement);
            root->right = bstRemoveNode(root->right, root->right->data, nodecmp, sizeOfElement);
        }
    }
    return root;
}
int bstRemove(BinarySearchTree *bst, void *delValue)
{
    if (delValue == NULL)
        return 0;
    bst->root = bstRemoveNode(bst->root, delValue, bst->nodecmp, bst->sizeOfElement);
    return 1;
}
btNode *bstSearch(BinarySearchTree *bst, void *key)
{
    btNode *cur = bst->root;
    while (cur != NULL && bst->nodecmp(cur->data, key) != 0)
    {
        if (bst->nodecmp(cur->data, key) > 0)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return cur;
}
btNode *bstSearchCondition(btNode *root, nodeCompare searchCriteria, void *key)
{
    if (root == NULL || searchCriteria == NULL || key == NULL)
        return NULL;
    if (!searchCriteria(root->data, key))
        return root;
    btNode *left = bstSearchCondition(root->left, searchCriteria, key);
    if (left != NULL)
        return left;
    return bstSearchCondition(root->right, searchCriteria, key);
}

// Book struct
Book getBook()
{
  Book book;
  printf("Input Book isbn: ");
  getString(book.isbn, 14);
  printf("Input Book title: ");
  getString(book.title, 50);
  printf("Input Book author: ");
  getString(book.author, 50);
  printf("Input Book price: ");
  scanf("%f", &book.price);
  return book;
}
void printBook(Book book)
{
  printf("| %-14s | %-26s | %-20s | %6.2f |\n",
         book.isbn, book.title, book.author, book.price);
}
void printLine()
{
  printf("+-%-14s-+-%-26s-+-%-20s-+-%-6s-+\n", "--------------",
         "--------------------------", "--------------------", "------");
}
void printTitle()
{
  printLine();
  printf("| %-14s | %-26s | %-20s | %-6s |\n", "ISBN", "Title",
         "Author", "Price");
  printLine();
}