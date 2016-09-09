#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*this program gets the two binary numbers and puts these numbers to linked lists.Multiplies them and adds
 another linked list and shows decimal value of binary numbers*/

/*create a structure with a value and a pointer*/
struct node{
    int data;
    struct node *next;
};

typedef struct node node;

/*these pointers for pop operation*/
node *c = NULL;
node *p;

void turnLL(node**, long long);
void push(node**, int);
node *add(node *, node*);
void reverse(node**);
void printList(node *);
int length(node *);
void pop();
void carry(node*);
int toDecimal(node*);
int binaryOrNot(long long);


int main(){
    /*these pointers for showing entered binary numbers*/
    node *hdr,*hdr2;
    
    hdr = NULL;
    hdr2 = NULL;
    
    long long firstNumber = 0 ,secondNumber = 0;
    
    /*this while loop run until "a" value is not one. "a" value is checked from "binaryOrNot" function.If entered number
     is not binary than "a" value is 0 so while loop run again.*/
    int a = 0;
    while(a != 1){
        printf("Please enter first binary number: \n");
        scanf("%lld",&firstNumber);
        a = binaryOrNot(firstNumber);
    }
    
    /*turn the binary number a linked list*/
    turnLL(&hdr,firstNumber);
    
    /*print the linked list and show the decimal value of binary number*/
    printList(hdr);
    int decimal1 = toDecimal(hdr);
    printf(" decimal of binary number is = %d\n",decimal1);
    printf("\n");
    
    /*do again while loop for second entered binary number for checking binary or not*/
    int b = 0;
    while(b != 1){
        printf("Please enter second binary number: \n");
        scanf("%lld",&secondNumber);
        b = binaryOrNot(secondNumber);
    }
    
    /*turn the second number a linked list and show the decimal value*/
    turnLL(&hdr2,secondNumber);
    printList(hdr2);
    int decimal2 = toDecimal(hdr2);
    printf(" decimal of binary number is = %d\n",decimal2);
    printf("\n");
    
    /*take the reverse second number for multiplication to linked lists*/
    reverse(&hdr2);
    
    /*if first or second number is 0 terminate the program*/
    if(firstNumber == 0 || secondNumber == 0){
        printf("Binary multiplication is 0");
        return 0;
    }
    
    int count = 0;
    int len = 0;
    
    /*do while loop until second number's pointer is null*/
    while(hdr2 != NULL){
        /*do that only one time because if second number's last digit is zero*/
        if(count == 0){
            if(hdr2->data == 0){
                len = length(hdr);
                
                int x;
                /*if zero than create a linked list with zeros amount of first number digits*/
                for(x = 0; x < len;x++){
                    push(&c,0);
                }
                /*add extra a zero for adding linked list*/
                push(&c,0);
                
                hdr2 = hdr2->next;
            }
        }
        /*if second number's digit is 1 then take first number and add with c which is first time is null */
        if(hdr2->data == 1){
            c = add(hdr,c);
            /*add a zero to linked list's head for adding linked lists*/
            push(&c,0);
            
        }else{
            /*if second number's digit is not 1 then add a zero linked list's head*/
            push(&c,0);
        }
        hdr2 = hdr2->next;
        /*increase the count for run only one time*/
        count ++;
    }
    /*reverse the number for carry because carry function checks the number from tail to head*/
    reverse(&c);
    /*call the carry function*/
    carry(c);
    /*take again reverse for correct number*/
    reverse(&c);
    
    /*from multiplication there can be an extra zero at the beginning of the list so pop that zero*/
    if(c->data == 0){
        pop();
    }
    
    /*print the multiplication and decimal value of binary number*/
    printf("Multiplication of binary numbers is = ");
    printList(c);
    int decimal3 = toDecimal(c);
    printf("\nDecimal of binary number is= %d",decimal3);
    
    return 0;
    
}
/*this function checks the number binary or not.If any digit is greater than 1 this number is not a binary number so
 if not binary return the status 0 and ask again for entering a number*/
int binaryOrNot(long long number){
    
    int status = 1;
    
    while(1){
        if(number == 0){
            break;
        }else{
            int digit = number % 10;
            if(digit > 1){
                status = 0;
                break;
            }
            number = number / 10;
        }
    }
    return status;
}

/*this function for creating a linked list*/
void turnLL(node ** header,long long value)
{
    while(value != 0){
        node* ptr = malloc(sizeof(node));
        ptr->data = value%10;
        ptr->next = *header;
        *header = ptr;
        value/=10;
    }
}

/*push the nedeed value head of list*/
void push(node** head_ref, int new_data)
{
    node* new_node = malloc(sizeof(node));
    new_node->data  = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

/*add to linked list*/
node * add(node* ptr , node * iki){
    node *q = NULL;
    /*do while loop pointers's are not null*/
    while(ptr != NULL && iki != NULL){
        push(&q, ptr->data+iki->data);
        ptr = ptr->next;
        iki = iki->next;
    }
    
    /*if first number's amount is greater than second, add the first number's other digits to list*/
    if(ptr != NULL && iki == NULL){
        while(ptr != NULL){
            push(&q, ptr->data);
            ptr = ptr->next;
        }
    }
    
    /*if second number's amount is greater than first, add the second number's other digits to list*/
    if(iki != NULL && ptr == NULL){
        while(iki != NULL ){
            push(&q, iki->data);
            iki = iki->next;
        }
    }
    /*because of push function take the reverse of number*/
    reverse(&q);
    return q;
}

/*reverse the binary numbers*/
void reverse(node ** head_ref)
{
    node * prev = NULL;
    node * current = *head_ref;
    node * next;
    while(current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

/*print the binary numbers*/
void printList(node *node)
{
    while (node != NULL)
    {
        printf("%d", node->data);
        node = node->next;
    }
}
/*take the amount of nodes*/
int length(node * head){
    
    int num;
    
    while(head != NULL){
        num += 1;
        head = head->next;
    }
    
    return num;
}

/*if numbers are not 1 or 0 apply the carry function from tail to head*/
void carry(node *p){
    
    while(p->next != NULL){
        if(p->data != 0 || p->data != 1){
            
            /*take digit to "a" value */
            int a = p->data;
            int count;
            
            /*if a's mode is 0 then calculate how much this number contains two*/
            if(a % 2 == 0){// 2,4,6,8...
                count = 0;
                while(a != 0){
                    a = a - 2;
                    count++;
                }
                /*because of a is an even number data should be 0*/
                p->data = 0;
                
                /*add the count with next data*/
                p->next->data = p->next->data + count;
                
            }
            /*if a' mode is 1 which is odd number. calculate how much this number contains two*/
            if(a % 2 == 1){//3,5,7,9..
                a = a-1;
                count = 0;
                
                while(a != 0){
                    a = a - 2;
                    count++;
                }
                /*because of a is an odd number data should be 1 */
                p->data = 1;
                
                /*add the count with next data*/
                p->next->data = p->next->data + count;
            }
        }
        p = p->next ;
    }
}
/*take the first digit from linked list*/
void pop()
{
    p = c;
    
    if (p == NULL)
    {
        printf("\n Error : Trying to pop from empty stack");
        return;
    }
    else
        p = p->next;
    
    free(c);
    c = p;
    
}
/*calculate the decimal of binary number*/
int toDecimal(node* ptr){
    
    int count = length(ptr);
    double sum = 0;
    
    while(ptr != NULL){
        sum = sum + ptr->data * pow(2,(count-1));
        ptr = ptr->next;
        count = (count - 1);
    }
    return (int)sum;
}

