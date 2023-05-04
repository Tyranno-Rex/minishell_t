#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 연결 리스트 노드 구조체
struct node {
    char *name;
    char *value;
    struct node *next;
};

// 연결 리스트 노드 생성 함수
struct node *create_node(char *name, char *value) {
    struct node *new_node = (struct node*) malloc(sizeof(struct node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    new_node->name = strdup(name);
    if (new_node->name == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    new_node->value = strdup(value);
    if (new_node->value == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    new_node->next = NULL;
    return new_node;
}

// 연결 리스트에 노드 삽입 함수
void insert_node(struct node **head, struct node *new_node) {
    if (*head == NULL) {
        *head = new_node;
    } else {
        insert_node(&(*head)->next, new_node);
    }
}

// 연결 리스트 출력 함수
void print_list(struct node *head) {
    if (head == NULL) {
        return;
    }
    printf("%s=%s\n", head->name, head->value);
    print_list(head->next);
}

int main() {
    char input[] = "export hello=\"hi\" cat=\"meow!\" me=\"eunseong\"";
    char *name, *value;
    struct node *head = NULL;

    // 입력 파싱
    char *token = strtok(input, " ");
    while (token != NULL) {
        if (strstr(token, "export") != NULL) {
            // "export" 문자열 제거
            token += strlen("export");
            // 데이터 이름 추출
            name = strtok(token, "=");
            // 데이터 값 추출
            value = strtok(NULL, "\"");
            // 새로운 노드 생성
            struct node *new_node = create_node(name, value);
            // 연결 리스트에 노드 삽입
            insert_node(&head, new_node);
        }
        token = strtok(NULL, " ");
    }

    // 연결 리스트 출력
    print_list(head);

    // 메모리 해제
    struct node *current = head;
    while (current != NULL) {
        struct node *temp = current;
        current = current->next;
        free(temp->name);
        free(temp->value);
        free(temp);
    }
    head = NULL;

    return 0;
}