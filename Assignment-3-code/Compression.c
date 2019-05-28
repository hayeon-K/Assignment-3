#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


#define MAX_CODE 22
#define MAX_TRANSACTIONS 100

struct date{
    int day;
    int month;
    int year;
};
typedef struct date date_t;

struct transaction{
    int student_id;
    char item_name[8];
    date_t transaction_date;
    int quantity; 
};
typedef struct transaction transaction_t;

/* Node of the huffman tree */
struct node{
    int frequency;
    char data;
    struct node *left,*right;
};
typedef struct node node_t;

struct code{
    char data; 
    char* huffman;
};
typedef struct code code_t;

struct heap{
    unsigned size; 
    unsigned capacity;
    node_t** array;
};
typedef struct heap heap_t;

node_t* new_node(char data, int freq){
    node_t* temp = (node_t*) malloc (sizeof(node_t)); 
    temp->left = temp-> right = NULL;
    temp->data = data;
    temp->frequency = freq;
    return temp;
}

heap_t* create_heap(unsigned capacity){
    heap_t* min_heap = (heap_t*) malloc(sizeof(heap_t)); 

    min_heap->size = 0;
    min_heap->capacity = capacity; 
    min_heap->array = (node_t**) malloc(min_heap->capacity * sizeof(node_t*)); 

    return min_heap; 
}

void swap_heap_node(node_t** a, node_t** b){
    node_t* temp = *a;
    *a = *b;
    *b = temp;
}

void make_heap(heap_t* heaps, int idx) { 
    int smallest = idx; 
    int left = 2 * idx + 1; 
    int right = 2 * idx + 2; 
  
    if (left < heaps->size && heaps->array[left]-> 
frequency < heaps->array[smallest]->frequency) 
        smallest = left; 
  
    if (right < heaps->size && heaps->array[right]-> 
frequency < heaps->array[smallest]->frequency) 
        smallest = right; 
  
    if (smallest != idx) { 
        swap_heap_node(&heaps->array[smallest], 
                        &heaps->array[idx]); 
        make_heap(heaps, smallest); 
    } 
} 

int is_size_one(heap_t* heaps){
    return heaps->size == 1;
}

node_t* extract(heap_t* heaps){
    node_t* temp = heaps->array[0]; 
    heaps->array[0] 
        = heaps->array[heaps->size - 1]; 
  
    --heaps->size; 
    make_heap(heaps, 0); 
  
    return temp; 
}

void insert_heap(heap_t* heap, node_t* node){
    ++heap->size; 
    int i = heap->size - 1; 
  
    while (i && node->frequency < heap->array[(i - 1) / 2]->frequency) { 
  
        heap->array[i] = heap->array[(i - 1) / 2]; 
        i = (i - 1) / 2; 
    } 
  
    heap->array[i] = node; 
}

void build_heap(heap_t* heap){
    int n = heap->size - 1; 
    int i; 
  
    for (i = (n - 1) / 2; i >= 0; --i) 
        make_heap(heap, i); 
}

int is_leaf(node_t* root) { 
    return !(root->left) && !(root->right); 
} 

heap_t* create_build_heap(char data[], int freq[], int size){
    heap_t* heaps = create_heap(size); 
    int i; 
    for (i = 0; i < size; ++i) 
        heaps->array[i] = new_node(data[i], freq[i]); 
    heaps->size = size; 
    build_heap(heaps); 
    return heaps; 
}

node_t* build_huffman_tree(char data[], int freq[], int size){
    node_t *left, *right, *top; 
    heap_t* heaps = create_build_heap(data, freq, size); 
    while(!is_size_one(heaps)){
        left = extract(heaps);
        right = extract(heaps);
        top = new_node('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right; 
        insert_heap(heaps, top);
    }
    return extract(heaps);
}

void print_num(code_t *codes, int * index, char data, int arr[], int n){
    code_t code;
    code.data = data; 
    code.huffman = (char*) malloc(n * sizeof(char*)); 
    int i, j = 0; 
    for (i = 0; i < n; ++i) 
        j += sprintf(&code.huffman[j], "%d", arr[i]); 
    codes[*index] = code; 
    *index += 1;
}


void print_code(code_t *code, int * index, node_t* root, int arr[], int top){
    if(root->left){
        arr[top] = 0;
        print_code(code, index, root->left, arr, top + 1);
    }
    if(root->right){
        arr[top]= 1;
        print_code(code, index, root->right, arr, top + 1);
    }
    if(is_leaf(root)){
         print_num(code, index, root->data, arr, top);
    }
}


void huffman(code_t *codes){
    char transactions[MAX_CODE] = {'\n', ' ', 'S', 'h', 'r', 'o', 't', '-', 'L', 'M',
        'i', 's', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int transaction_frequencies [MAX_CODE] = {100, 50, 25, 12, 12, 12, 8, 8, 6, 6, 4, 4,
        3, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    int size = sizeof(transactions) / sizeof(transactions[0]);
    node_t* root = build_huffman_tree(transactions, transaction_frequencies, size);
    int index = 0;
    int arr[100], top = 0;
    print_code(codes, &index, root, arr, top);
}

void to_string(char * string, transaction_t transaction){
    int i = 0;
    i += sprintf(&string[i], "%d", transaction.student_id); 
    strcat(string, " ");
    strcat(string, transaction.item_name);
    strcat(string, " ");
    i = strlen(string);
    i += sprintf(&string[i], "%d", transaction.transaction_date.year); 
    strcat(string, " ");
    i = strlen(string);
    i += sprintf(&string[i], "%d", transaction.transaction_date.month); 
    strcat(string, " ");
    i = strlen(string);
    i += sprintf(&string[i], "%d", transaction.transaction_date.day); 
    strcat(string, " ");
    i = strlen(string);
    i += sprintf(&string[i], "%d\n", transaction.quantity); 
}

void to_huffman(const code_t * code, char * huffmaned, char* transaction){
    int i, index = 0;
    for(i = 0; i < strlen(transaction); i++){
        for(index = 0; index < MAX_CODE; index++){
            if(transaction[i] == code[index].data){
                strcat(huffmaned, code[index].huffman);
            }
        }
    }
}

void dehuffman(char * huffman, char * test){
    char transactions[MAX_CODE] = {'\n',' ', 'S', 'h', 'r', 'o', 't', '-', 'L', 'M',
        'i', 's', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int transaction_frequencies [MAX_CODE] = {100, 50, 25, 12, 12, 12, 8, 8, 6, 6, 4, 4,
        3, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    int size = sizeof(transactions) / sizeof(transactions[0]);
    node_t* root = build_huffman_tree(transactions, transaction_frequencies, size);
    node_t* curr = root; 
    int i, j = 0;
    for(i = 0; i < strlen(huffman); i++){
        if(huffman[i] == '0') curr = curr->left;
        else curr = curr->right;
        if(curr->left == NULL && curr->right == NULL){
             j += sprintf(&test[j], "%c", curr->data); 
             curr = root;
        }
    }
}

void create_compression(code_t * codes, transaction_t * transactions, int size){
    FILE *fp;

     /* Opening a file in r mode */
    fp = fopen("compressed_huffman", "w");

    /* If fp is NULL, print error message and finish */ 
      if(fp == NULL){
        printf("Write error\n");
    } 

    /* int variable for for loop */
    int i, j;


    /* loop the number of flights and write to file in certain format, 
        changing line with each flight  */
    for(i = 0; i < size; i++){
        char test[200];
        char huffmaned[200] = {'\0'};    
        to_string(test, transactions[i]);
        to_huffman(codes, huffmaned, test);
        for(j = 0; j < strlen(huffmaned); j++){
            fputc(huffmaned[j], fp);
        }
    }

    /* close file */
    fclose(fp);
}

void decompress_to_file(){
    FILE *rfp;
    char huffmaned[1000] = {'\0'};    
     /* Opening a file in r mode */
    rfp = fopen("compressed_huffman", "r");

    /* If fp is NULL, print error message and finish */ 
    if(rfp == NULL){
        printf("Students not loaded. Is database in right folder? \n");
    } 
    char ch;
    while(1){
        fscanf(rfp, "%s", huffmaned);
        ch = fgetc(rfp);
        if(ch == EOF) break;
    }
    FILE *fp;

     /* Opening a file in r mode */
    fp = fopen("decompressed.bin", "wb");

    /* If fp is NULL, print error message and finish */ 
      if(fp == NULL){
        printf("Write error\n");
    } 


    /* loop the number of flights and write to file in certain format, 
        changing line with each flight  */
    while(1){
        char test2[1000] = {'\0'};
        dehuffman(huffmaned, test2);
        fwrite(test2, sizeof(char), sizeof(test2), fp); 
        ch = fgetc(fp);
        if(ch == EOF) break;
    }

    /* close file */
    fclose(fp);
}

void read_database(){
    FILE * fp;
    long lsize;
    char * buffer;

    size_t result; 
 

    fp = fopen("decompressed.bin", "rb");
    /* If fp is NULL, print error message and finish */ 
    if(fp == NULL){
        printf("Read error\n");
    } 
    fseek(fp, 0, SEEK_END);
    lsize = ftell(fp);
    rewind(fp);
    

    buffer = (char*) malloc(sizeof(char)*lsize);
    if(buffer == NULL) {printf("Memory error");}

    result = fread(buffer, 1, lsize, fp);
    if(result != lsize) {printf("Reading Error");}
    int size = 0;
    
    size = strlen(buffer) / sizeof(transaction_t);
    printf("%d\n", size);
    int i = 0;
    transaction_t * transactions;
    transactions = (transaction_t*) malloc(sizeof(transaction_t)*size);
    for(i = 0; i < size; i++){
        sscanf(buffer, "%d %s %d %d %d %d", &transactions[i].student_id, transactions[i].item_name,
                 &transactions[i].transaction_date.year, &transactions[i].transaction_date.month,
                 &transactions[i].transaction_date.day, &transactions[i].quantity);

    }


    for(i = 0; i < size; i++){
        printf("%d %s %d %d %d %d\n", transactions[i].student_id, transactions[i].item_name,
                 transactions[i].transaction_date.year, transactions[i].transaction_date.month,
                 transactions[i].transaction_date.day, transactions[i].quantity);

     }
    fclose(fp);
    free(buffer);

}

