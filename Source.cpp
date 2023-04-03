#include <stdio.h>
#include <stdlib.h>

#define size 30

int get_word_start(int i, char* string) {
	while (string) {
		if ((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z')) {
			return i;
		}
		if (string[i] == '\0') {
			return -1;
		}
		i++;
	}
	return -1;
}

int get_word_end(int i, char* string) {
	while (string) {
		if ((string[i] < 'a' || string[i] > 'z') && (string[i] < 'A' || string[i] > 'Z')) {
			return i - 1;
		}
		i++;
	}
	return -1;
}
struct list {
	char* word;
	struct list* next;
};

struct list* init(int start, int end, char* string) {
	struct list* tmp;
	char* t;
	int max = end - start + 2;
	int j = max;
	tmp = (struct list*)malloc(sizeof(struct list));
	if (tmp) {
		t = (char*)malloc(sizeof(char) * max);
		if (t) {
			tmp->word = t;
		}
		for (int i = start; i <= end; i++) {
			tmp->word[max - j] = string[i];
			j--;
		}
		tmp->word[max - 1] = '\0';
		tmp->next = NULL;
	}
	return tmp;
};

struct list* add_note(struct list* ptr, int start, int end, char* string) {
	struct list* tmp;
	char* t;
	int max = end - start + 2;
	int j = max;
	tmp = (struct list*)malloc(sizeof(struct list));
	if (tmp) {
		t = (char*)malloc(sizeof(char) * max);
		if (t) {
			tmp->word = t;
		}
		ptr->next = tmp;
		for (int i = start; i <= end; i++) {
			tmp->word[max - j] = string[i];
			j--;
		}
		tmp->word[max - 1] = '\0';
		tmp->next = NULL;
	}
	return tmp;
}

void print_list(struct list* p) {
	int i = 0;
	while (p != NULL) {
		while (p->word[i] != '\0') {
			putc(p->word[i], stdout);
			i++;
		}
		putc(' ', stdout);
		p = p->next;
		i = 0;
	}
	putc('\n', stdout);
}


struct list* minimal_alphabet(struct list* p1, struct list* p2) {
	int i = 0;
	struct list* p = NULL;
	while (p1->word[i] != '\0' && p2->word[i] != '\0') {
		if (p1->word[i] < p2->word[i]) {
			return p1;
		}
		else if (p1->word[i] > p2->word[i]) {
			return p2;
		}
		else {
			i++;
		}
	}
	if (p1->word[i] == '\0') {
		return p1;
	}
	else {
		return p2;
	}
}


struct list* merge(struct list* head1, struct list* head2) {
	struct list* p1 = head1;
	struct list* p2 = head2;
	struct list* p = head2;
	struct list* head = NULL;

	head = minimal_alphabet(head1, head2);
	p = head;
	if (p == head1) {
		p1 = p1->next;
	}
	else {
		p2 = p2->next;
	}

	while (p1 != NULL && p2 != NULL) {
		p->next = minimal_alphabet(p1, p2);
		p = p->next;
		if (p == p1) {
			p1 = p1->next;
		}
		else {
			p2 = p2->next;
		}
	}
	if (p1 == NULL) {
		p->next = p2;
	}
	else {
		p->next = p1;
	}
	return head;
}

int main() {

	int x = 0, start = 0, end = 0, i = 0;
	struct list* head = NULL;
	struct list* head1 = NULL;
	struct list* head2 = NULL;
	struct list* p = head1;
	char* string1 = NULL;
	char* string2 = NULL;
	char* tmp = NULL;
	char  c;
	int len = size;

	printf("Input string 1: ");

	string1 = (char*)malloc(sizeof(char) * size);

	while ((c = getc(stdin)) != '\n') {
		if (string1) {
			string1[i++] = c;
			if (i == len) {
				len += size;
				tmp = (char*)realloc(string1, sizeof(char) * len);
				if (tmp != NULL) {
					string1 = tmp;
				}
			}
		}
	}
	if (string1) {
		string1[i] = '\0';
	}

	while (1) {
		start = get_word_start(start, string1);
		if (start == -1) {
			break;
		}
		end = get_word_end(start, string1);
		if (!head1) {
			head1 = init(start, end, string1);
			p = head1;
			start = end + 1;
			continue;
		}
		p = add_note(p, start, end, string1);
		start = end + 1;
	}

	i = 0;
	len = size;
	tmp = NULL;

	printf("Input string 2: ");
	string2 = (char*)malloc(sizeof(char) * size);


	while ((c = getc(stdin)) != '\n') {
		if (string2) {
			string2[i++] = c;
			if (i == len) {
				len += size;
				tmp = (char*)realloc(string2, sizeof(char) * len);
				if (tmp != NULL) {
					string2 = tmp;
				}
			}
		}
	}
	if (string2) {
		string2[i] = '\0';
	}

	start = end = 0;

	while (1) {
		start = get_word_start(start, string2);
		if (start == -1) {
			break;
		}
		end = get_word_end(start, string2);
		if (!head2) {
			head2 = init(start, end, string2);
			p = head2;
			start = end + 1;
			continue;
		}
		p = add_note(p, start, end, string2);
		start = end + 1;
	}

	printf("List 1: ");
	print_list(head1);
	printf("List 2: ");
	print_list(head2);

	head = merge(head1, head2);

	printf("Merge list: ");
	print_list(head);

	p = head;
	struct list* t;

	while (p != NULL) {
		t = p;
		p = p->next;
		free(t->word);
		free(t);
	}

	return 0;
}
