#include<stdio.h>
#include<stdlib.h>
typedef struct linked_list{
    int coeff;
    int deg;
    struct linked_list *next;
}Polynomial;

void initialize(Polynomial **aa_head){
    *aa_head=NULL;
}

void insertion(Polynomial **aa_head,int c,int d){
    Polynomial *t,*cur,*prv;
    t=(Polynomial*)malloc(sizeof(Polynomial));
    t->coeff=c;
    t->deg=d;
    for(cur=*aa_head,prv=NULL; cur && d<=cur->deg; cur=cur->next){  
        if(cur->deg==d){
            cur->coeff=cur->coeff+c;
            return;
        }      
        prv=cur;             
    }    
    t->next=cur;
    if(prv!=NULL)
        prv->next=t;
    else
        *aa_head=t;
}

void display (Polynomial *a_head){
  for( ; a_head ; a_head = a_head->next){
    if(a_head->coeff>0)
        printf(" +"); 
    if(a_head->coeff!=0){
        if(a_head->deg==0)
            printf("%d",a_head->coeff);
        else
            printf("%dx^%d", a_head->coeff, a_head->deg);
    }       
    printf("\n");
  }
}

void add(Polynomial *a_head1, Polynomial *a_head2){
    Polynomial *added=NULL;
    initialize(&added);
    while(a_head1 && a_head2){
        if(a_head1->deg==a_head2->deg){
            insertion(&added,a_head1->coeff + a_head2->coeff,a_head1->deg);
            a_head1=a_head1->next;
            a_head2=a_head2->next;
        }
        
        else if(a_head1->deg>a_head2->deg){
            insertion(&added,a_head1->coeff,a_head1->deg);
            a_head1=a_head1->next;
        }

        else if(a_head2->deg>a_head1->deg){
            insertion(&added,a_head2->coeff,a_head2->deg);
            a_head2=a_head2->next;
        }
    }

    while(a_head1){
        insertion(&added,a_head1->coeff,a_head1->deg);
        a_head1=a_head1->next;
    }
    while(a_head2){
        insertion(&added,a_head2->coeff,a_head2->deg);
        a_head2=a_head2->next;
    }    
    display(added);   
    
}


void mul(Polynomial *a_head1, Polynomial *a_head2){
    Polynomial *mul=NULL, *t;
    t=a_head2;
    while(a_head1){
        a_head2=t;
        while(a_head2){
            insertion(&mul,(a_head1->coeff)*(a_head2->coeff), a_head1->deg+a_head2->deg);
            a_head2=a_head2->next;
        }
        
        a_head1=a_head1->next;
    }
    
    display(mul);
    

}

void main(){
    Polynomial *poly1=NULL,*poly2=NULL;
    initialize(&poly1);
    initialize(&poly2);
    int coeff1,coeff2,deg1,deg2;  //1=polynomial A, 2=polynomial B
    int ac=0,bc=0;                 //ac=counts number of terms of A, bc=counts number of terms of B

    while(1){
        int choice,innerchoice=1;          // ic=inner while loop counter
        printf("\n-----List Of Choices-----\n");
        printf("\nWhat would you like to do?\n1: Enter Polynomial A\n2: Enter Polynomial B\n3: Add A and B\n4: Multiply A and B\n5: Exit the program.\n");
        scanf("%d",&choice);
        switch(choice){

            case 1:
                ac++;
                printf("You opted to enter the Polynomial A:\n");
                while(innerchoice){
                    printf("Enter the coefficient and the degree of x of Polynomial A\n");
                    scanf("%d %d",&coeff1,&deg1);
                    insertion(&poly1,coeff1,deg1);
                    printf("Are there more terms?(1-Yes, 0-No)\n");
                    scanf("%d",&innerchoice);
                }
                printf("Polynomial A inserted succesfully\n");
                break;

            case 2:
                bc++;
                printf("You opted to enter the Polynomial B:\n");
                while(innerchoice){
                    printf("Enter the coefficient and the degree of x of Polynomial B\n");
                    scanf("%d %d",&coeff2,&deg2);
                    insertion(&poly2,coeff2,deg2);
                    printf("Are there more terms?(1-Yes, 0-No)\n");
                    scanf("%d",&innerchoice);
                }
                printf("Polynomial B inserted succesfully\n");
                break;

            case 3:
                if(ac==0 && bc==0){
                    printf("\nEnter Polynomials A and B");
                    printf("\n");
                    break;
                }
                                
                printf("Polynomial A: ");
                display(poly1);
                printf("Polynomial B: ");
                display(poly2);
                printf("Added Polynomial: ");
                add(poly1,poly2);
                
                break;

            case 4:
                if(ac==0 && bc==0){
                    printf("\nEnter Polynomials A and B");
                    printf("\n");
                    break;
                }
               
                printf("Polynomial A: ");
                display(poly1);
                printf("Polynomial B: ");
                display(poly2);
                printf("Multiplied Polynomial: ");
                mul(poly1,poly2);
                break;
            
            case 5:
                printf("\nSuccessfully Exited the Program.\n");
                printf("\n");
                exit(1);

            default:
                printf("ERROR: Wrong input\n");
                break;                 
        }         
    }
}