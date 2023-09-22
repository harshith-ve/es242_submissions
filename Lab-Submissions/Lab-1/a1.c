//Team members: Harshith, Ganesh, Bharat
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_array(int a[],int n){
    for (int i=0; i<n;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
}
void print_array_1(int *a, int n, void *data)
{
    print_array(a, n);
}

void swap(int *a,int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
}
void bubble_sort(int arr[],int n1,int n2){
    for(int i=n1;i<n2+1;i++){
        for (int j=n1;j<n2;j++){
            if (arr[j]<arr[j+1]){
                swap(&arr[j],&arr[j+1]);
            }
        }
    }   
}

int check_sorted(int arr[],int n){
    int flag=1;
    for (int i=0; i<n-1;i++){
        if (arr[i]>arr[i+1]){
            flag=0;
        }
    }
    return flag;
}

/*
 * Generate k-selections of a[0..n-1] in lexicographic order and call process_selection to process them.
 *
 * The array b[] will have enough space to hold k elements.
 * For a selection i1, ..., ik, you should set b[0] = a[i1], ..., b[k-1] = a[ik].
 * Selections should be generated in lexicographic order.
 * a[0..k-1] is the smallest selection and a[n-k..n-1] is the largest.
 */
void generate_selections(int a[], int n, int k, int b[], void *data, void (*process_selection)(int *b, int k, void *data))
{
    int c[n];
    for (int i=0;i<n;i++){
        c[i]=i;
    }
    int d[k];
    for (int i=0;i<k;i++){
        d[i]=c[i];
    }
    for (int j=0;j<k;j++){
        b[j]=a[d[j]];
    }
    process_selection(b,k,data);
    int ptr1=k-1;
    int ptr2=k-2;
    int k1=k-1;
    while (d[0]!=c[n-k]){
        if (d[ptr1]==c[n-1]){
            int temp=2;
            while (d[ptr2]==c[n-temp]){
                ptr2--;
                temp++;
            }
            for (int i=0;i<n;i++){
                if (d[ptr2]==c[i]){
                    k1=i+1;
                    break;
                }
            }
            d[ptr2]=c[k1];
            for (int i=ptr2+1;i<k;i++){
                k1++;
                d[i]=c[k1];
            }
            ptr2=k-2;
            for (int j=0;j<k;j++){
                b[j]=a[d[j]];
            }
            process_selection(b,k,data);
        }
        else{
            int i1=k1+1;
            for (int i=i1;i<n;i++){
                d[ptr1]=c[i];
                for (int j=0;j<k;j++){
                    b[j]=a[d[j]];
            }
                process_selection(b,k,data);
            }
        }
    }
}

/*
 * See Exercise 2 (a), page 94 in Jeff Erickson's textbook.
 * The exercise only asks you to count the possible splits.
 * In this assignment, you have to generate all possible splits into buf[]
 * and call process_split() to process them.
 * The dictionary parameter is an array of words, sorted in dictionary order.
 * nwords is the number of words in this dictionary.
 */
int isWord(char word[],int start,int end, const char *dictionary[], int nwords) {
    int flag = 0;
    for (int i = 0; i < nwords; i++) {
        if (end-start+1 == strlen(dictionary[i])) {
            flag = 0;
            for (int j = 0; j < strlen(dictionary[i]); j++) {
                if (word[j+start] != dictionary[i][j]) {
                    flag = 1;
                }
            }
            if (flag == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void split(char word[], const char *dictionary[], int nwords, char buf[], int start,int end,int num_space,void *data, void (*process_split)(char buf[], void *data)) {
    if (strlen(buf)==strlen(word)+num_space){
        process_split(buf,data);
    }
    for (int i=start;i<end+1;i++){
        if (isWord(word,start,i,dictionary,nwords)){
            int i1=strlen(buf);
            for (int j=start;j<i+1;j++){
                buf[j-start+i1]=word[j];
            }
            buf[i+1-start+i1]=' ';
            buf[i+1-start+i1+1]='\0';
            split(word,dictionary,nwords,buf,i+1,end,num_space+1,data,process_split);
            for (int j=start;j<i+2;j++){
                buf[j-start+i1]='\0';
            }
        }
    }
}

void printstr(char buf[], void *data) {
    printf("%s\n", buf);
}

void generate_splits(const char *source, const char *dictionary[], int nwords, char buf[], void *data, void (*process_split)(char buf[], void *data))
{
    int word_len = strlen(source);
    char c[word_len];
    strcpy(c,source);
    split(c, dictionary, nwords, buf,0,word_len-1,0,data,process_split);

}

/*
 * Transform a[] so that it becomes the previous permutation of the elements in it.
 * If a[] is the first permutation, leave it unchanged.
 */
void previous_permutation(int a[], int n)
{
    //assuming all ements are distinct
    if (check_sorted(a,n)==0){
        int temp1=0;
        int d1 = __INT_MAX__;
        int temp2=n-1;
        for(int i=n-1;i>=0;i--){
            if (a[i-1]>a[i]){
                temp1=i-1;
                break;
            }
        }
        for (int i=n-1;i>temp1;i--){
            if ((a[i]<a[temp1]) && ((a[temp1]-a[i])<d1)){
                temp2=i;
                d1=a[temp1]-a[i];
            }
        }
        swap(&a[temp1],&a[temp2]);
        bubble_sort(a,temp1+1,n-1);
    }

}

/* Write your tests here. Use the previous assignment for reference. */

typedef struct {
    int index;
    int err;
} state_t;

static void test_selections_2165(int b[], int k, void *data)
{
    state_t *s = (state_t *)data;
    s->err = 0;
    switch (s->index) {
    case 0:
        if ((b[0] != 2) || (b[1] != 1)) {
            s->err = 1;
        }
        break;
    case 1:
        if ((b[0] != 2) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 2:
        if ((b[0] != 2) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 3:
        if ((b[0] != 1) || (b[1] != 6)) {
            s->err = 1;
        }
        break;
    case 4:
        if ((b[0] != 1) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    case 5:
        if ((b[0] != 6) || (b[1] != 5)) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
    ++(s->index);
}

BEGIN_TEST(generate_selections) {
    int a[] = { 2, 1, 6, 5 };
    int b[2];
    state_t s2165 = { .index = 0, .err = 1 };
    generate_selections(a, 4, 2, b, &s2165, test_selections_2165);
    ASSERT(!s2165.err, "Failed on 2 1 6 5.");
} END_TEST

void test_splits_art(char buf[], void *data)
{
    state_t *s = (state_t*)data;
    s->err = 0;
    switch (s->index) {
    case 0:
        if (!strcmp(buf, "art is toil")) {
            s->err = 1;
        }
        break;
    case 1:
        if (!strcmp(buf, "artist oil")) {
            s->err = 1;
        }
        break;
    default:
        s->err = 1;
    }
}

BEGIN_TEST(generate_splits) {
    const char *a = "artistoil";
    const char *dict[] = {
        "art",
        "artist",
        "is",
        "oil",
        "toil"
    };
    int nwords = 5;
    state_t s = { .index = 0, .err = 1 };
    char buf[256];
    generate_splits(a, dict, nwords, buf, &s, test_splits_art);
    ASSERT(!s.err, "Failed on 'artistoil'.");
} END_TEST

BEGIN_TEST(previous_permutation) {
    int a[] = { 1, 5, 6, 2, 3, 4 };
    previous_permutation(a, 6);
    ASSERT_ARRAY_VALUES_EQ(a, 6, "Failed on 1 5 6 2 3 4.", 1, 5, 4, 6, 3, 2);
} END_TEST

int main()
{
    run_tests((test_t[]) {
            TEST(generate_selections),
            TEST(generate_splits),
            TEST(previous_permutation),
            0
        });
    const char *a = "artistoil";
    const char *dict[] = {
        "art",
        "artist",
        "is",
        "oil",
        "toil"
    };
    int nwords = 5;
    char buf[256];
    generate_splits(a, dict, nwords, buf, NULL, printstr);
    int arr1[]={1,2,3,5,4};
    previous_permutation(arr1,5);
    // here the arr1 is changed after the execution of prev_perm now arr1 is {1,2,3,4,5}
    print_array(arr1,5);
    int b1[3];
    generate_selections(arr1,5,3,b1,NULL,print_array_1);
    return 0;
}
