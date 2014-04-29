
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
void sort(struct data_listcontainer *s);

int main()
{
    struct data_listcontainer s;
    struct data_node *p;
    int n, i, b;

    scanf("%d", &n);

    init(&s);

    for (i = 0; i < n; i++) {
        scanf("%d", &b);
        insert(&s, i+1, b);
    }

    sort(&s);

    for (p = s.head->next; p != NULL; p = p->next)
        printf("%d ", p->data);

    printf("\n");

    destroy(&s);

    return 0;
}

struct data_node* find_min_node(struct data_node* head)
{
    struct data_node *min_node = head;
    struct data_node *p;

    for (p = head; p != NULL; p = p->next)
        if (p->data < min_node->data)
            min_node = p;

    return min_node;
}

void sort(struct data_listcontainer *s)
{
    struct data_node *p, *min_node;
    int temp;

    for (p = s->head->next; p != NULL; p = p->next) {
        min_node = find_min_node(p);
        temp = min_node->data;
        min_node->data = p->data;
        p->data = temp;
    }
}

/* ��ʼ������������һ��ͷ��� */
void init(struct data_listcontainer *s)
{
    struct data_node *node = NULL;

    node = (struct data_node *)malloc(sizeof(struct data_node));
    if(node == NULL) {
        printf("memory allocation error\n");
        return;
    }

    node->next = NULL;
    s->head = node;
}

/* ���ҵ�i������ */
struct data_node* find_helper(struct data_node *p, int i)
{
    if (i == 0 || p == NULL)
        return p;
    else
        return find_helper(p->next, i-1);

}

struct data_node* find(struct data_listcontainer* s, int i)
{
    return find_helper(s->head, i);
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
    if(q == NULL) {
        printf("memory allocation error\n");
        return;
    }
    q->data = b;

    /* ���½ڵ���뵽��i�����ݽڵ�֮ǰ */
    q->next = p->next;
    p->next = q;
}

void destroy(struct data_listcontainer *s)
{
    /* ������� */
    struct data_node *p = s->head, *q;

    /* �ͷ�������ÿһ���ڵ� */
    while(p != NULL) {
        q = p->next; /* ������һ���ڵ�ĵ�ַ */
        free(p);
        p = q;
    }

    s->head = NULL;
}