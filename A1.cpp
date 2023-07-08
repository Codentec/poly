#include <iostream>
#include <string>
#include <cmath>
using namespace std;

////////////////////////////////////////////////////////////////////////

/*other data type*/
typedef struct term
{
    int coeff;
    int degree;
    term * next;
} term;

typedef struct polyn
{
    term* t;
    polyn* next;
} polyn;

////////////////////////////////////////////////////////////////////////

/*fuction prototype & definitions*/
void select(int x,polyn** h);
polyn* selectp(polyn** h);
void sortedInsert(term** head, term* newNode);
term* insertSort(term** head);
void printList(polyn** head);
void printTerms(polyn* p);
void createpolyn(polyn **head);
term* addremoveterm(polyn* p, int d, int c);
void addremoveterm(polyn* p, int d);
void addremoveterm(polyn* p, int i, int j,  double q);
double evaluate(polyn* p, double x);
polyn* derivative(polyn* p);
double zeroNewton(polyn* p, double x, double q );

////////////////////////////////////////////////////////////////////////

int main()
{
    polyn* h = NULL;
    int x = 0;
    while(x != 9)
    {
        fflush(stdin);
        fflush(stdout);
        cout << "Please choose the one of the following action:\n";
        cout << "1. Create Polynomial\n";
        cout << "2. Add or Remove terms\n";
        cout << "3. Evaluate\n";
        cout << "4. Adding 2 Polynomials\n";
        cout << "5. Derivative\n";
        cout << "6. Calculate zero\n";
        cout << "7. Print List of polynomials\n";
        cout << "8. Remove all terms with very low coefficients\n";
        cout << "9. exit\n\n";
        fflush(stdin);
        fflush(stdout);
        cin >> x;
        

        switch(x)
        {
        case 1:
            createpolyn(&h);
            break;
        case 2:
            int y;
            cout << "1. Add\n";
            cout << "2. Remove\n";
            fflush(stdin);
            fflush(stdout);
            cin >> y;
            switch(y)
            {
                case 1:
                    select(1,&h);
                    break;
                
                case 2:
                    select(2,&h);
                    break;
                default:
                    break;
            }
            break;
            
        case 3:
            select(3,&h);
            break;
        case 4:
            select(5,&h);
            break;

        case 5:
            select(6,&h);
            break;
        case 7:
            cout << endl;
            printList(&h);
            break;

        case 8:
            select(4, &h);
            break;
        case 9:
            break;
        }

        
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////

/*funtion definition*/
//the below function is used for some of the the functions
void addTerm(polyn p, int d, int c)
{
    p.t = new term();
    term* ptr = p.t;
    term* n = (term* )malloc(sizeof(term));
    n->coeff = c;
    n->degree = d;
    n->next = ptr;
    p.t = n;
    p.t = insertSort(&(p.t));
    fflush(stdin);
    fflush(stdout); 
}


void createpolyn(polyn** head)
{
    polyn* n = (polyn*)malloc(sizeof(polyn));
    polyn* ptr = *head;
    n->t = new term();
    if(ptr == NULL) //list is empty
    {
        *head = n;
    }
    else //else add at the end
    {
        while(ptr -> next != NULL)
        {
            ptr = ptr -> next;
        }
        ptr -> next = n;
    }
    n->next = NULL;

    char ch = 'y';
    while(1)
    {
        int d,c;
        cout << "Enter coefficient and degree: ";
        cin >> c >> d;
        n->t = addremoveterm(n, d, c);
        n->t = insertSort(&(n->t));
        getchar();
        cout << "Want to add another term?Y/n: ";
        cin >> ch;
        if(ch != 'y' && ch != 'Y')
        {
            break;
        }
    }
    cout << "Polnomial successfully created! :)\n";
    fflush(stdin);
    fflush(stdout);
}


////////////////////////////////////////////////////////////////////////
void printTerms(polyn* p)
{
    term* ptr = (p)->t;
    while(ptr->next != NULL)
    {
        cout << ptr->coeff << "x^" << ptr->degree <<" + " ;
        ptr = ptr->next;  
    }
    cout << ptr->coeff << "x^" << ptr->degree;
}

void printList(polyn** head)
{
    if(*head == NULL)
    {
        cout << "Empty\n\n";
        return;
    }
    int i = 0;
    polyn* ptr = new polyn();
    ptr = *head;
    while(ptr != NULL)
    {
        cout << ++i <<". ";
        printTerms(ptr);
        ptr = ptr->next;
        cout << "\n";
    }
    fflush(stdin);fflush(stdout);
}

////////////////////////////////////////////////////////////////////////

//for adding term
term* addremoveterm(polyn* p, int d, int c)
{
    term* ptr = p->t;
    term* n = (term* )malloc(sizeof(term));
    n->coeff = c;
    n->degree = d;
    n->next = NULL;

    //checking if the term with the following degree is present or not
    while(ptr != NULL)
    {
        if(ptr->degree == d)
        {
            cout << "Term with degree "<< d <<" is already present!";
            getchar();
            fflush(stdin);
        }
        ptr = ptr->next;
    }
    ptr = p->t;
    n->next = ptr;
    p->t = n;
    p->t = insertSort(&(p->t));
    return ptr;
}

//for removing term
void addremoveterm(polyn* p, int d)
{
    fflush(stdin);
    int flag = 0;
    term* prev = NULL;
    term* ptr = p -> t;
    while(ptr != NULL)
    {
        if(ptr->degree == d)
        {
            flag++;
        }
        ptr = ptr->next;
    }
    ptr = p->t;
    if(flag){
        while(ptr->degree != d)
        {
            prev = ptr;
            ptr = ptr->next;
        }
        //if node is at the beginning
        if(ptr == p->t)
        {
            p->t = (p->t)->next;
            free(ptr); return;
        }

        //if node is in the middle
        if(ptr != p->t and ptr->next != NULL)
        {
            prev->next = ptr->next;
            free(ptr); return;
        }

        //if node is at the end
        if(ptr->next == NULL)
        {
            prev->next = NULL;
            free(ptr);return;
        }
        
    }
    else
    {
        cout << "Term with degree "<< d << " is not present\n";
    }
    fflush(stdin);fflush(stdout);
}

//for removing terms with very low coeffcients polynomial
/*void addremoveterm(polyn *p, int i, int j, double q)
{
    term* ptr = p->t;
    if(ptr != NULL)
    {
        for(; ptr != NULL; ptr = ptr->next)
        {
            if(ptr->coeff - q <= 0)
            {
                addremoveterm(p,ptr->degree);
            }
        }
    }
}*/

double evaluate(polyn* p, double x)
{
    double ans = 0;
    polyn* ptr = p;
    term* t1 = ptr->t;
    while(t1 != NULL)
    {
        ans = ans + t1->coeff*pow(x,t1->degree);
        t1 = t1->next;
    }
    return ans;
}

polyn operator +(const polyn p1,const polyn p2)
{
    polyn new_polyn;
    term* ti = p1.t;
    term* tj = p2.t;
    while(ti != NULL && tj != NULL)
    {
        if(ti->degree < tj->degree)
        {
            addTerm(new_polyn,ti->degree,ti->coeff);
            ti = ti->next;
        }
        else if(ti->degree > tj->degree)
        {
            addTerm(new_polyn, tj->degree, tj->coeff);
            tj = tj->next;
        }
        else
        {
            addTerm(new_polyn, ti->degree, ti->coeff + tj->coeff);
            ti = ti->next;
            tj = tj->next;
        }
    }
    if(ti == NULL)
    {
        while(tj != NULL)
        {
            addTerm(new_polyn,tj->degree,tj->coeff);
            tj = tj->next;
        }
    }
    if(tj == NULL)
    {
        while(ti != NULL)
        {
            addTerm(new_polyn, ti->degree, ti->coeff);
            ti = ti->next;
        }
    }
    return new_polyn;
}


polyn* derivative(polyn* p)
{
    polyn* d_p = (polyn*)malloc(sizeof(polyn));
    term* ptr = p->t;
    while(ptr != NULL)
    {
        int d = ptr->degree;
        int c = ptr-> coeff;
        addTerm(*d_p,d,c);
    }
    return d_p;
}
/*
double zeroNewton(polyn* p, double x, double q = 1e-9)
{
    polyn* d_p = (polyn*)malloc(sizeof(polyn));
    //d_p = derivative(p);
    cout << "Enter initial guess: ";
    cin >> x;
    int prev_x;
    while(1)
    {
        prev_x = x;
        x = x - evaluate(p,x)/evaluate(d_p,x);
        if(ab(x - prev_x) <= q)
        {
            break;
        }
    }
    return x;
}*/

//following function is used for sorting the linked list
void sortedInsert(term** head, term* newNode)
{
    term dummy;
    term* current = &dummy;
    dummy.next = *head;
 
    while (current->next != NULL && current->next->degree < newNode->degree) {
        current = current->next;
    }
 
    newNode->next = current->next;
    current->next = newNode;
    *head = dummy.next;
}
 
// Given a list, change it to be in sorted order (using `sortedInsert()`).
term* insertSort(term** head)
{
    term* result = NULL;     // build the answer here
    term* current = *head;   // iterate over the original list
    term* next;
 
    while (current != NULL)
    {
        // tricky: note the next pointer before we change it
        next = current->next;
 
        sortedInsert(&result, current);
        current = next;
    }
 
    *head = result;
    return *head;
}

polyn* selectp(polyn** h)
{
    polyn* ptr = *h;
    cout << "Select Polynomial:\n\n";
    printList(h);
                
    if(ptr != NULL){
        fflush(stdin);
        fflush(stdout);
        int num; cin >> num;
        num = num -1;
        while(num-- && ptr->next != NULL)
        {
            ptr = ptr->next;
        }
    }
    return ptr;   
}
void select(int x, polyn** h)
{
    polyn* ptr = selectp(h);
    if(x == 1)
    {
        cout << "Enter coefficient and degree: ";
        int c,d;
        fflush(stdin);
        fflush(stdout);
        cin >> c >> d;
        addremoveterm(ptr, d,c);
        
    }
    else if(x ==2)
    {
        int d1;
        cout << "Enter degree: ";
        fflush(stdin);
        fflush(stdout);
        cin >> d1;
        addremoveterm(ptr, d1);
            
    }

    else if(x == 3)
    {
        double x;
        cout << "\nEnter the value at which you want to evaluate: ";
        cin >> x;
        cout << "The value of polynomial is : "<< evaluate(ptr, x);
        
    }
    else if(x == 4)
    {
        //addremoveterm(ptr, 0 ,0 , 1e-9);
    }
    else if(x == 5)
    {
        fflush(stdin);
        fflush(stdout);
        polyn* ptr2 = selectp(h);
        polyn *p3 = new polyn();
        *p3 = *ptr + *ptr2;
        printTerms(p3);
    }
    else if(x == 6)
    {
        polyn* p = NULL;
        p = derivative(p);
        //printTerms(p);
    }
}