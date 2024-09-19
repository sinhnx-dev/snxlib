// snxlib more functions
void clearKeyboardBuffer();
void getString(char *str, int length);
int menu(const char *title, int menuItemCount, char *menuItem[]);
void waitEnterPress(char* msg);

// Stack ADT
typedef struct snode
{
  void *data;
  struct snode *next;
} sNode;
typedef struct stack{
  unsigned int sizeOfElement;
  sNode *top;
} Stack;
Stack* initStack(unsigned int sizeOfElement);
int sPush(Stack *s, void *newElement);
int sIsEmpty(Stack *s);
void* sPop(Stack *s);
void* sPeek(Stack *s);

// Queue ADT
typedef struct qnode
{
  void *data;
  struct qnode *next;
} qNode;
typedef struct
{
  unsigned int sizeOfElement;
  qNode *front;
  qNode *rear;
} Queue;

Queue *initQueue(unsigned int sizeOfElement);
int qIsEmpty(Queue *q);
int qEnqueue(Queue *q, void *newElement);
void *qDequeue(Queue *q);

// ArrayList ADT
typedef struct
{
  void *data;
  unsigned int count;
  unsigned int maxElements;
  unsigned int sizeOfElement;
} ArrayList;
ArrayList *alInit(unsigned sizeOfElement, unsigned int maxElements);
int alInsert(ArrayList *al, void *newElement);
int alInsertAt(ArrayList *al, void *newElement, unsigned position);
void *alGetAt(ArrayList *al, unsigned position);
int alRemoveAt(ArrayList *al, unsigned position);
int alIsEmpty(ArrayList *al);
void alShowInfo(ArrayList *al);
void alDestroy(ArrayList *al);
int alSaveToFile(ArrayList *al, const char* path);
ArrayList* alLoadFromFile(const char* path);

// LinkedList ADT
typedef struct node
{
  void *data;
  struct node *next;
} llNode;
typedef struct
{
  unsigned int sizeOfElement;
  llNode *head;
  llNode *it;
} LinkedList;
LinkedList *llInit(unsigned sizeOfElement);
int llInsert(LinkedList *ll, void *newElement);
int llInsertAt(LinkedList *ll, void *newElement, unsigned position);
int llIsEmpty(LinkedList *ll);
void* llGetAt(LinkedList *ll, unsigned int position);
int llRemove(LinkedList *ll);
int llRemoveAt(LinkedList *ll, unsigned int position);
int llInitIterator(LinkedList *ll);
int llHasNext(LinkedList *ll);
void *llNext(LinkedList *ll);
void llDestroy(LinkedList *ll);
int llSaveToFile(LinkedList *ll, const char *path);
LinkedList *llLoadFromFile(const char *path);

// Binary Search Tree ADT
typedef struct btreeNode
{
  void *data;
  struct btreeNode *left;
  struct btreeNode *right;
} btNode;
typedef int nodeCompare(const void *v1, const void *v2);
typedef void traversalFunc(const void *element);
typedef struct
{
  unsigned int sizeOfElement;
  nodeCompare *nodecmp;
  btNode *root;
} BinarySearchTree;
BinarySearchTree *bstInitRoot(void *root, unsigned int sizeOfElement, nodeCompare *nodecmp);
BinarySearchTree *bstInit(unsigned int sizeOfElement, nodeCompare *nodecmp);
void btDestroyRoot(btNode *root);
void bstDestroy(BinarySearchTree *bst);
int bstInsertNode(BinarySearchTree *bst, btNode *newNode);
int bstInsert(BinarySearchTree *bst, void *newElement);
void bstTraversal(btNode *root, traversalFunc *tf);
void bstTraversalDesc(btNode *root, traversalFunc *tf);
void bstTraversalCondition(btNode *root, nodeCompare *nodeCmp, const void *key, traversalFunc tf);
btNode *bstMinNode(btNode *root);
btNode *bstRemoveNode(btNode *root, void *deleteElement, nodeCompare *nodecmp, unsigned int sizeOfElement);
int bstRemove(BinarySearchTree *bst, void *delValue);
btNode *bstSearch(BinarySearchTree *bst, void *key);
btNode *bstSearchCondition(btNode *root, nodeCompare searchCriteria, void *key);

// Book struct
typedef struct
{
  char isbn[15];
  char title[51];
  char author[51];
  float price;
} Book;
Book getBook();
void printBook(Book book);
void printLine();
void printTitle();