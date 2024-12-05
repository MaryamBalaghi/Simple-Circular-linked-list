#include <iostream>
using namespace std;
class node
{
    friend class circularlist;
    private:
    int data;
    node *next;
};
class circularlist
{
    node* last;
    public:
    circularlist();
    ~circularlist();
    void enter_to_beginning();
    void enter_to_ending();
    void disply();
    void enter_to_sorted_list(); // this function ensert the newnode to a sorted list.
    void delete_from_beginning();
    void delete_from_end();
    void delete_specific_node(); 
};
circularlist::circularlist()
{
    last=nullptr;
}
circularlist::~circularlist()
{
    if(last==nullptr)
    {
        return;  //list is empty.
    }
    node*curptr=last->next;
    node*temp;
    do
    {
        temp=curptr;
        curptr=curptr->next;
        delete temp;
    } while (curptr!=last->next);
    last=nullptr;
}
void circularlist::enter_to_beginning()
{
    node* newnode=new node;
    cout<<"Please enter the number: ";
    cin>>newnode->data;
    if(last==nullptr) // insert a newnode to a empty list.
    {
        last=newnode;
        newnode->next=newnode;
        return;
    }
    newnode->next=last->next;
    last->next=newnode;
}
void circularlist ::disply()
{
    if(last==nullptr)
    {
        cout<<"This list is empty";
        return;
    }
    node* curptr=last->next;
    do
    {
        cout<<curptr->data<<" ";
        curptr=curptr->next;
    } while (curptr!=last->next); 
    cout << endl;
}
void circularlist::enter_to_ending()
{
    node* newnode=new node;
    cout<<"Please enter the number: ";
    cin>>newnode->data;
    if(last==nullptr)         // if the list is empty. 
    {
        newnode->next=newnode;
        last=newnode;
        
    }
    else{ //The else block clearly shows that the two cases are mutually exclusive: the list is either empty or non-empty.
    newnode->next=last->next;
    last->next=newnode;
    last=newnode;
    }
}
void circularlist::enter_to_sorted_list()
{
    node* nodenew = new node;
    cout << "Enter the number: ";
    cin >> nodenew->data;

    if (last == nullptr) {
        // Case 1: If the list is empty
        nodenew->next = nodenew;  // Points to itself
        last = nodenew;           // Last points to the new node
        return;
    }

    node* curptr = last->next;  // Start at the head (first node)
    node* precur = last;        // Precursor to curptr (last node)
    
    // Case 2: Insert at the beginning (before the first node)
    if (nodenew->data <= curptr->data) {
        nodenew->next = curptr;
        last->next = nodenew;
        return;
    }

    // Case 3: Insert at the end (after the last node)
    if (nodenew->data >= last->data) {
        nodenew->next = last->next;  // Point it to the first node
        last->next = nodenew;        // Last node points to the new node
        last = nodenew;              // Update last to the new node
        return;
    }

    // Case 4: Insert in between nodes
    do {
        // If the new node should go between precur and curptr
        if (nodenew->data <= curptr->data && nodenew->data > precur->data) {
            nodenew->next = curptr;
            precur->next = nodenew;
            return;
        }
        precur = curptr;      // Move to the next node
        curptr = curptr->next;
    } while (curptr != last->next);  // Loop until we complete the circular traversal
}
void circularlist::delete_from_beginning()
{
    if(last==nullptr)  //This list is empty.
    {
        cout<<"This list is empty.";
        return;
    }
    node* temp;
    if(last==last->next) //This list has only one node;
    {
        temp=last;
        delete temp;
        last=nullptr;
    }
    else  //This list has more than one element.
    {
        temp=last->next;
        last->next=temp->next;
        delete temp;
    } 
    cout<<"Node deleted from the beginning. "<<endl;
}
void circularlist::delete_from_end()
{
    if(last==nullptr) // case1 the list is empty.
    {
        cout<<"This list is empty."<<endl;
        return;
    }
    node* temp=last->next;
    if(last==last->next)    //case2 the list has only one element.
    {
        delete temp;
        last=nullptr;
    }
    else            //case3 the list has atleast tow node;
    {
        node*pretemp=temp;
        while (pretemp->next!=last)  //for finding the second last node;
        {
            pretemp=pretemp->next;
        }
        pretemp->next=last->next;
        delete last;
        last=pretemp;
        
    }
    cout<<"Note deleted from the end;"<<endl;
}
void circularlist::delete_specific_node()
{
    if(last==nullptr) //case 1 : list in empty.
    {
        cout<<"This list is empty."<<endl;
        return;
    }
    int key; // this is node that must be deleted.
    cout<<"Enter the node for delete: ";
    cin>>key;
    node* cur=last->next;
    node* precur=last;
    do
    {
        if(cur->data==key)            //find the specific node .
        {
            if(cur==last&&cur==last->next)       // case 2 if key is only node of list.
            {
                delete cur;
                last=nullptr;
                cout << "Node deleted. The list is now empty." << endl;
                return;
            }
            else if(cur==last->next)     //case 3 if list at leat has tow element and key is first.
            {
                last->next=cur->next;
                delete cur;
                cout<<"First node deleted";
                return;
            }
            else                // Case 4: The node is either in the middle or is the last node.
            {
                precur->next=cur->next; 
                if(cur==last)          //if it is the last node, update last. 
                {
                    last=precur;
                }
                delete cur;
                cout<<"Node deleted."<<endl;
                return;
            }
        }
        precur=cur;
        cur=cur->next;
    } while (cur!=last->next);
    cout<<"Node with value: "<<key<<" not found."<<endl;  //case 4 key not found in the list.
}
int main()
{
    circularlist a;
    int c,n;
    bool Continue=true;
    char m;
    cout<<"++++++guide+++++++"<<endl;
    cout << "++++++ Guide +++++++" << endl;
    cout << "1 - Insert a node at the beginning." << endl;
    cout << "2 - Insert a node at the end." << endl;
    cout << "3 - Create a sorted list (list must be empty or already sorted)." << endl;
    cout << "4 - Delete a specific node." << endl;
    cout << "5 - Delete from the beginning." << endl;
    cout << "6 - Delete from the end." << endl;
    cout << "7 - Display all nodes." << endl;
    while (Continue)
    {
        cout<<"\nPlease enter your choice: ";
        cin>>c;
        switch (c)
        {
        case 1:
            a.enter_to_beginning();
            break;
        case 2:
            a.enter_to_ending();
            break;
        case 3:
            cout<<"Please enter the number of elements to add: ";
            cin>>n;
            while (n>0)
            {
                a.enter_to_sorted_list();
                n--;
            }
            break;
        case 4:
            a.delete_specific_node();
            break;
        case 5:
            a.delete_from_beginning();
            break;
        case 6:
            a.delete_from_end();
            break;
        case 7:
         cout << "Current list contents: ";
            a.disply();
            break;
        default:
            cout<<"Invalid choise."<<endl;
            break;
        }
        cout<<"Do you continue?(Y/N)";
        cin>>m;
        if(m=='n' or m=='N')
        {
            Continue=false;
        }
    }
     cout << "Program terminated. Thank you! \3" << endl;
    return 0;
}
