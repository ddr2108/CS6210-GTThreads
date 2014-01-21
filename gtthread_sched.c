typedef struct{
    ucontext_t node;
    contextNode* next;
} contextNode;

typedef struct{
    contextNode* head = NULL;
    contextNode* tail = NULL;
} context;

context information;
contextNode* current;    //Current one to change

void addContext(ucontext_t newContext){
    //Create new node
    contextNode* newNode = malloc(sizeof(contextNode));
    newNode->node = newContext;
    newNode->next = NULL;
    
    //Add node to linked list
    if (information.head==NULL){
        information.head = newContext;
        information.tail = newContext;
    }else{
        information.tail->next = newNode;
    }
}

void removeContext(){
    //Pointers to nodes
    contextNode* lead = information.head;
    contextNode* trail = NULL;

    //Search while not NULL
    while(lead!=NULL){
        //If reached the correct node
        if (lead==current){
            if (trail!=NULL){
                trail->next = lead->next;
            }else{      //its the head
                information.head = lead.next;
                //If only item in linked list
                if (information.tail==current){
                    information.tail = lead.next;
                }
            }
            //Free memory
            free(lead)
            break;
        }
        //Move values
        trail = lead;
        lead = lead->next;
    }
}

//Set alarm, switch context based on next in linked list
void changeContext(int sig)
{
    struct itimerval it;       //Structure to hold time info
    struct sigaction act, oact;         //Structure for signal handler
    
    //Swap context
    swapcontext(&currentNode->node, &currentNode->next->node);
    current = current->next
    
    //Set signal handler
    act.sa_handler = changeContext;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGPROF, &act, &oact); 
                           
    // Start itimer
    it.it_interval.tv_sec = RRPeriod;
    it.it_interval.tv_usec = 0;
    it.it_value.tv_sec = RRPeriod;
    it.it_value.tv_usec = 0;
    setitimer(ITIMER_VIRTUAL, &it, NULL);
}

//http://nitish712.blogspot.com/2012/10/thread-library-using-context-switching.html
