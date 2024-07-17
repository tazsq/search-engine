#include <bits/stdc++.h>

using namespace std;

/// @brief -----------------just some forward declarations to avoid conflicts------------------------------

class linkedList;

class node;

struct ret_word;

linkedList* table[200]={nullptr};

vector<string> documents={"1.txt","2.txt","3.txt"};


/*
---------------------------main definitions of classes---------------------------------------------
*/

class node{
    public:
    string data;
    node* next;
    set<string> files_found;
    node(string data){
        this->data=data;
        next=NULL;
    }
};

struct ret_word{
    bool flag;
    node* ret_ptr=NULL;
};

class linkedList{
public:
    node* head;
    node* tail;
    linkedList(){
        head=NULL;
        tail=NULL;
    }


    void iathead(string data){
        
        if(head==NULL){
            head=new node(data); 
            tail=head;                       
        }
        else{
        node* temp=new node(data);
        temp->next=head;
        head=temp;
        }

    }

    void iatback(string data){
        
        if(head==NULL){
            head=new node(data); 
            tail=head;                       
        }
        else{
            node* temp=head;
            while(temp->next!=NULL){
                temp=temp->next;
            }
            
            temp->next=new node(data);
            tail=temp->next;
        }
    }

    void print_table(){
        node* temp=head;
        while(temp!=NULL){
            cout << temp->data <<"-->";
            temp=temp->next;
        }
        cout << "NULL";
    }
    
};


//<--------------------------------ALL FUNCTION DECLARATIONS HERE------------------------------------------------>

ret_word search_word(string word);

void add_totable();

void print();


/**
 * @brief ---------------------------indexer to put strings into the table-------------------------------------
 * 
 * @param s 
 * @return int 
 */

void add_totable(){
    string s;
    fstream myfile;
    for(int i = 0 ; i < documents.size() ; i++){
        myfile.open(documents[i],ios::in);
        if(!myfile){
            cout << "no such file exists \n";
        }
        else{
            while(myfile >> s){
                    
                    ret_word retword;
                    int sum=0;
                    for(int i=0;i<s.size();i++){
                        sum+=abs(toupper(s[i])-65);
                    }
                    int index=sum%200;
                    retword=search_word(s);
                    if(retword.flag==true && retword.ret_ptr->data==s){
                        table[index]->head->files_found.insert(documents[i]);     
                        continue;
                    }
                    table[index]->iathead(s); 
                    table[index]->head->files_found.insert(documents[i]);       
            }        
        }
        myfile.close();
    }
}

/**
 * @brief to print the table--------------------------------------------------------------------------------------
 * 
 */


void print(){
    for(int i=0;i<200;i++){
        cout << i <<"  --->  ";
        if(table[i]->head!=NULL){
            table[i]->print_table();
        }
        
        cout << "\n";
    }
}
//----------------------------------------retriever here!!!!!---------------------------------------------------

ret_word search_word(string word){
    ret_word retword;
    
    for(int i = 0 ; i < documents.size() ; i++){
                    int sum=0;
                    for(int i=0;i<word.size();i++){
                        sum+=abs(toupper(word[i])-65);
                    }
                    int index=sum%200;
                    if(index>199 || index<0){
                        retword.flag=false;
                        return retword;
                    }
                    node* temp=table[index]->head;
                    while(temp!=NULL){
                        if(temp->data==word){
                            retword.flag=true;
                            
                            retword.ret_ptr=temp;
                            return retword;
                        }
                    else{
                            temp=temp->next;
                        }
                    }
                    retword.flag=false;
                    return retword;     
                           
    }        
}


//-----------------------------------------the main func!!!------------------------------------------------------
int main(){
    for(int i=0;i<200;i++){
        table[i]=new linkedList();
    }
    add_totable();
    int choice;
    string user_enter;
    cout << "what do you want to do ??\n\n";
    cout << " 1 --> search a word \n\n 2 --> print table data structure \n\n 3 --> end the program \n\n ";
    
    
    choice=-1;
    while(choice!=3){
        cout << "Enter a choice\n";
        cin >> choice;

        if(choice == 1){
            
            cout << "enter a string\n";
            cin >> user_enter;
            ret_word r;
            
            r=search_word(user_enter);
            if(r.flag==true){
                cout << "found in --> \n";
                for(const auto& file:r.ret_ptr->files_found){
                    cout << file << " \n";
                }
            }
            else {
                cout << "not found in the database\n";
            }
        }
        else if(choice == 2){
            print();
        }
        else if(choice == 3){
            choice=3;
        }
    }
  
     cout << "Thank you for using me :) \n";
    return 0;
}

