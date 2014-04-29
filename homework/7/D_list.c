
#include <stdio.h>
#include <stdlib.h>

typedef int elemType;
struct data_node {
    elemType data;
    struct data_node *next;
};

struct data_listcontainer {
    struct data_node *head;
};

void init(struct data_listcontainer *s);
void insert(struct data_listcontainer *s, int i, elemType b);
void destroy(struct data_listcontainer *s);

int main()
{
    int n, i, k;
    elemType x;
    struct data_node* p;
    struct data_node* q;

    /* һ���������ݴ洢�ռ����� */
    struct data_listcontainer s;

    /* ��ʼ�������ռ� */
    init(&s);

    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d", &x);
        insert(&s, i + 1, x);
    }

    scanf("%d", &k);

    q = s.head;
    p = q->next;
    for (i = 1; i < k; i++) {
        q = p;
        p = p->next;
    }

    q->next = p->next;
    p->next = p->next->next;
    q->next->next = p;

    p = s.head->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }

    /* ��������ռ� */
    destroy(&s);

    return 0;
}

/* ��ʼ������������һ��ͷ��� */
void init(struct data_listcontainer *s)
{
    struct data_node *node = 0;

    node = (struct data_node *)malloc(sizeof(struct data_node));
    if(node == 0) {
        printf("memory allocation error\n");
        return;
    }

    node->next = 0;
    s->head = node;
    return;
}

/* ���ҵ�i������ */
struct data_node* find(struct data_listcontainer* s, int i)
{
    struct data_node* p = s->head;
    int j = 0;

    if (i < 0)
        return NULL;

    while (j < i) {
        p = p->next;
        ++j;
    }

    return p;
}

/* ��λ��i����һ�������ݽڵ� */
void insert(struct data_listcontainer *s, int i, elemType b)
{
    struct data_node *q = NULL;
    struct data_node *p = find(s, i-1); /* �ҵ���i-1������ */

    if (p == NULL) {
        printf("No such node, insertion failed.\n");
        return;
    }

    /* Ϊb����һ���ڵ�ռ� */
    q = (struct data_node *)malloc(sizeof(struct data_node));
    if(q == 0) {
        printf("memory allocation error\n");
        return;
    }
    q->data = b;

    /* ���½ڵ���뵽��i�����ݽڵ�֮ǰ */
    q->next = p->next;
    p->next = q;

    return;
}

void destroy(struct data_listcontainer *s)
{
    /* ������� */
    struct data_node *p = s->head, *q;

    /* �ͷ�������ÿһ���ڵ� */
    while(p != 0) {
        q = p->next; /* ������һ���ڵ�ĵ�ַ */
        free(p);
        p = q;
    }

    s->head = 0;
}