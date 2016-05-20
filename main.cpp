#include <iostream>

using namespace std;

struct Node;
struct List;

List*  list();
Node* node(int v);

List*  push(List* s, Node* n);
List*  inject(List* s, Node* n);
List* insertAfter(List* s, Node* curr, Node* n);
List* insertBefore(List* s, Node* curr, Node* n);
List*  del(List* s, int v);
void  printNode(Node* n);
void  printLR(List* s);
void  printRL(List* s);
List* sieve(int n);

bool czyJest(List* s, Node* n);
bool czyJestCurr(List* s, Node* n);

void TEST(List* s, Node* n1,Node* n2,Node* n3,Node* n4,Node* n5);

struct Node
{
    int value;
    struct Node *next;
};


struct List
{
    int liczbaObjektow = 0;
    struct Node *first, *last;
};



int main()
{
    List* lista = list();
    Node* my_node1,*my_node2,*my_node3,*my_node4,*my_node5;

    my_node1 = node(1);
    my_node2 = node(2);
    my_node3 = node(3);
    my_node4 = node(4);
    my_node5 = node(5);

    TEST(lista,my_node1,my_node2,my_node3,my_node4,my_node5);
    
    delete lista;
    delete my_node1;
    delete my_node2;
    delete my_node3;
    delete my_node4;
    delete my_node5;

    return 0;
}



List*  list(){
    return new List();
}
Node* node(int v){
    return new Node{v, NULL};
}
List*  push(List* s, Node* n){
        if(s->first == NULL){
            s->first = n;
            s->first->next = NULL;
            s->last = n;
            s->liczbaObjektow++;
            return s;
        }

        Node * tmpFirst = s->first;

        if(!czyJest(s,n)){
           s->first = n;
           s->first->next = tmpFirst;
           s->liczbaObjektow++;
        }


        return s;
}

List*  inject(List* s, Node* n){
       if(!czyJest(s,n)){

       if(s->last == NULL){
            s->last = n;
            if(s->first == NULL){
                s->first = n;
                s->liczbaObjektow++;
                return s;
            }

                Node * tmp = s->first;
                while(tmp->next != NULL){
                    tmp = tmp->next;
                }
            tmp->next = n;
            s->liczbaObjektow++;
            return s;
        }

        Node * tmpLast = s->last;

        if(!czyJest(s,n)){
           s->last = n;
           tmpLast->next = n;
           s->liczbaObjektow++;
        }
       }


        return s;
}
//dodaje do listy s węzęł n (jeśli nie było jego wartości wcześniej na liście) na pozycję bezpośrednio po
//węzle curr (licząc od lewej do prawej strony) i zwraca zmodyfikowaną s
List* insertAfter(List* s, Node* curr, Node* n){

    if(czyJestCurr(s,curr)){ // curr jest na liste?


    Node * linkKurr = curr->next;
    if(!czyJest(s,n)){

        if(curr->next == NULL)
            s->last = n;


        curr->next = n;
        n->next = linkKurr;
        s->liczbaObjektow++;
    }

    }else{cout << "Nie ma takiego elementu na liscie! | insertAfter" << endl;}
    return s;
}
//dodaje do listy s węzęł n (jeśli nie było jego wartości wcześniej na liście) na pozycję bezpośrednio przed
//węzłem curr (licząc od lewej do prawej strony) i zwraca zmodyfikowaną s
List* insertBefore(List* s, Node* curr, Node* n){

    if(czyJestCurr(s,curr)){ // curr jest na liste?

    if(!czyJest(s,n)){

        if(curr == s->first)
            s->first = n;


        Node * tmp = s->first;

        n->next = curr;
        if(n != tmp){ // dla wtawiania miendzy
           while(tmp->next != curr){
                //cout << "!";
                 tmp = tmp->next;
           }
           tmp->next = n;
        }

        s->liczbaObjektow++;
    }

    }else{cout << "Nie ma takiego elementu na liscie! | insertBefore" << endl;}
    return s;

}
//usuwa z listy s węzeł o wartości v i zwraca zmodyfikowaną s
List*  del(List* s, int v){
    if(s->first == s->last){
        cout << "Ostatni element!" << endl;
        cout << "Usunenty >> "; printNode(s->first);
        cout << "Lista pusta!" << endl;
        s->first = NULL;
        s->last = NULL;
        s->liczbaObjektow--;
        return s;
    }
        Node * tmp = s->first;
        Node * before = tmp;

        if(tmp->value == v){ // del pierszego
            cout << "Usunenty >> "; printNode(tmp);
                s->first = tmp->next;
                s->liczbaObjektow--;
                return s;
        };


        while(tmp != NULL){
            if(v == tmp->value){
                 cout << "Usunenty >> "; printNode(tmp);
                if(tmp->next == NULL){

                    before->next = NULL;
                    s->last = before;
                    s->liczbaObjektow--;
                     return s;
                }


                before->next = tmp->next;
                s->liczbaObjektow--;
                return s;
            }
            before = tmp;
            tmp = tmp->next;
        }
        cout << "Nie ma (" << v << ") w liscie!" << endl;

        return s;
}
//wypisuje informacje o węzle n
void  printNode(Node* n){
    cout << "Value -> " << n->value << " Next -> ";
    if(n->next == NULL){ cout << "NULL" << endl;}else{ cout << n->next << endl;}
}
//wypisuje informacje o wszystkich węzłach z listy s, w kolejności od lewej do prawej
void  printLR(List* s){
    if(s->first == NULL && s->last == NULL){
        cout << "Nie ma elementow! " << endl;
        return;
    }
        Node * tmp = s->first;
        while(tmp != NULL){
            printNode(tmp);
            tmp = tmp->next;
        }

}
//wypisuje informacje o wszystkich węzłach z listy s, w kolejności od prawej do lewej.
void  printRL(List* s){
    if(s->first == NULL && s->last == NULL){
        cout << "Nie ma elementow!" << endl;
        return;
    }
    Node * tmp = s->first;
    Node* mas[s->liczbaObjektow];

        int i = s->liczbaObjektow;

        while(tmp != NULL){
            mas[--i] = tmp;
            tmp = tmp->next;
        }

        for(int j = 0; j < s->liczbaObjektow; j++ ){
            printNode(mas[j]);
        }

}
//zwracającą listę węzłów zawierających wszystkie liczby pierwsze
//z przedziału [2,n] metodą sita Eratostenesa. Należy skorzystać wyłącznie z operacji na liście.
List* sieve(int n){
    int size = n-1;
    List * sito = list();
    Node * wezli[size];
    int j = 2;
    for(int i = 0 ; i < size ; i++){
        wezli[i] = node(j++);
        inject(sito,wezli[i]);
    }
    delete [] wezli;

    Node * tmp = sito->first;
    Node * tmpIn = sito->first;
      int curL = sito->first->value;
        while(curL*curL <= n){

            tmpIn = tmp;

       while(tmpIn != NULL){
        if(tmpIn->value % curL == 0 && curL != tmpIn->value){
            del(sito,tmpIn->value);
        }
        tmpIn = tmpIn->next;
       }


        tmp = tmp->next;
         curL = tmp->value;
    }

    return sito;
}

bool czyJest(List* s, Node* n){
        bool jest = false;
        Node * tmpFirst = s->first;
        while(tmpFirst != NULL){
                if(tmpFirst->value == n->value){
                    cout << " Taka wartosc juz jest na liscie! " ;
                    printNode(n);

                    jest = true;
                    break;
                }
            tmpFirst = tmpFirst->next;
        }

        return jest;
}


bool czyJestCurr(List* s, Node* n){
        bool jest = false;
        Node * tmpFirst = s->first;
        while(tmpFirst != NULL){
                if(tmpFirst->value == n->value){
                    jest = true;
                    break;
                }
            tmpFirst = tmpFirst->next;
        }

        return jest;
}

void TEST(List* s, Node* n1,Node* n2,Node* n3,Node* n4,Node* n5){

    insertAfter(s,n1,n2); // Nie mozna dodac nie ma elementa
    insertBefore(s,n2,n1); // -||-
    cout << "----------------Tylko PUSH-------------------------" << endl;
    push(s,n1); //zaczynamy od push
    push(s,n1); // nie mozna dodawac ten sam wezel
    push(s,n2);
    push(s,n3);
    push(s,n4);
    push(s,n5);

    printLR(s); // print z LR
    cout << s->first->value << " - first" << endl; // pokazuje ze lista wie gdzie first i last przy push
    cout << s->last->value  << " - last" << endl;
    printRL(s); // print z RL
    cout << "---------------- DEL 1-3 -------------------------" << endl;

    del(s,1);
    del(s,2); //del 1-3
    del(s,3);

    printLR(s); // print z LR
    cout << s->first->value << " - first" << endl; // pokazuje ze lista wie gdzie first i last przy push
    cout << s->last->value << " - last"  << endl;
    printRL(s); // print z RL
    cout << "---------------insert after / before po first i last--------------------------" << endl;


   insertAfter(s,n4,n1); // po pierwszym
   insertAfter(s,n4,n1); // zle
   insertAfter(s,n4,n4); // zle
   del(s,5); // del n5
   insertBefore(s,n4,n5); // przed ostatnim

   insertBefore(s,n4,n2); // przed pierwszym
   insertBefore(s,n2,n3); // przed pierszym

    printLR(s); // print z LR
    cout << s->first->value << " - first" << endl; // pokazuje ze lista wie gdzie first i last przy push
    cout << s->last->value << " - last" << endl;
    printRL(s); // print z RL
    cout << "----------------- insert before i after | miedzy wezlami ------------------------" << endl;

   del(s,3);
   del(s,5);

   insertBefore(s,n2,n3); // miedzy
   insertAfter(s,n2,n5); // miedzy

    printLR(s); // print z LR
    cout << s->first->value << " - first" << endl; // pokazuje ze lista wie gdzie first i last przy push
    cout << s->last->value << " - last" << endl;
    printRL(s); // print z RL
    cout << "----------------DEL calej listy-------------------------" << endl;

    del(s,1);
    del(s,2); // usuwamy calu liste
    del(s,3);
    del(s,4);
    del(s,5);

    printLR(s); // print z LR
    cout << s->first << " - first" << endl; // pokazuje ze lista wie gdzie first i last przy push
    cout << s->last << " - last" << endl;
    printRL(s); // print z RL
    cout << "---------------- Tylko inject -------------------------" << endl;

    inject(s,n1);
    inject(s,n2); // dodajemy z konca
    inject(s,n3);
    inject(s,n4);
    inject(s,n5);

    printLR(s); // print z LR
    cout << s->first->value << " - first" << endl; // pokazuje ze lista wie gdzie first i last przy push
    cout << s->last->value << " - last" << endl;
    printRL(s); // print z RL
    cout << "------------------ Mieszane -----------------------" << endl;

    del(s,1);
    del(s,2); // usuwamy calu liste
    del(s,3);
    del(s,4);
    del(s,5);

    push(s,n1); // mieszana!
    insertAfter(s,n1,n2);
    insertBefore(s,n1,n3);
    inject(s,n5);
    push(s,n4);

    printLR(s); // print z LR
    cout << s->first->value << " - first" << endl; // pokazuje ze lista wie gdzie first i last przy push
    cout << s->last->value << " - last" << endl;
    printRL(s); // print z RL
    cout << "---------------- SITO -------------------------" << endl;

    List * sito = sieve(30);

    cout << "\nWynik! : " << endl;
    printLR(sito); // print z LR
    cout << sito->first->value << " - first" << endl; // pokazuje ze lista wie gdzie first i last przy push
    cout << sito->last->value << " - last" << endl;
    cout << "--------------- END TEST --------------------------" << endl;
    delete sito;
    cout << "\nDziekuje za uwage :) " << endl;
}


