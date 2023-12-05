#include "bits/stdc++.h"
#define CAPACITY 2

typedef struct state State;
typedef struct node Node;
typedef struct list List;

struct state{
    int cannibalCountLeft;
    int missionaryCountLeft;
    int missionaryCountRight;
    int cannibalCountRight;
    int side;   // 1 if boat is present on right side else 0
};

struct node{
    Node * parentNode;
    Node * next;
    State * thisState;
};

struct list{
     Node * thisNode;
     List * next;
};

List * addToList( List * head, Node * thisNode){
    List * newList = new List;

    newList->thisNode = thisNode;
    newList->next = NULL;

    List * temp = head;
    if(head == NULL) head = newList;
    else{
        while(temp->next!=NULL){
            temp = temp->next;
        }
        temp->next = newList;
    }
    return head;
}

List * removeFromList(List * head){
    if(head == NULL) return NULL;
    head = head->next;
    return head;
}

State * createState(int missionaryCountLeft, int missionaryCountRight, int cannibalCountLeft, int cannibalCountRight,int side){
    State * newState = new state;
    newState->cannibalCountLeft = cannibalCountLeft;
    newState->cannibalCountRight = cannibalCountRight;
    newState->missionaryCountLeft = missionaryCountLeft;
    newState->missionaryCountRight = missionaryCountRight;
    newState->side = side;
    return newState;
}

Node * createNode(Node * parentNode,State * thisState){
    Node * newNode = new node;
    newNode->parentNode = parentNode;
    newNode->thisState = thisState;
    newNode->next = NULL;
}

Node * addSuccessorsForBoatOnLeft(Node * head, Node * currentNode,int missionaryCountOnBoat, int cannibalCountOnBoat){
    int missionaryCountLeft = currentNode->thisState->missionaryCountLeft;
    int missionaryCountRight = currentNode->thisState->missionaryCountRight;
    int cannibalCountLeft = currentNode->thisState->cannibalCountLeft;
    int cannibalCountRight = currentNode->thisState->cannibalCountRight;

    int missionaryRemOnLeft = missionaryCountLeft-missionaryCountOnBoat;
    int cannibalRemOnLeft = cannibalCountLeft-cannibalCountOnBoat;
    int cannibalAddedOnRight = cannibalCountRight + cannibalCountOnBoat;
    int missionaryAddedOnRight = missionaryCountRight + missionaryCountOnBoat;
    int right = 1;

    //check if missonary >= cannibal
    if(((missionaryRemOnLeft>=cannibalRemOnLeft) || (missionaryRemOnLeft == 0)) && ((missionaryAddedOnRight>=cannibalAddedOnRight) || (missionaryAddedOnRight == 0))){
        State * successorState = createState(missionaryRemOnLeft,missionaryAddedOnRight,cannibalRemOnLeft,cannibalAddedOnRight,right);
        Node * newNode = createNode(currentNode,successorState);
        //insert at first
        if(head == NULL){
            head = newNode;
        }else{
            Node * temp = head;
            newNode->next = temp;
            head = newNode;
        }
    }
    return head;
}

Node * addSuccessorsForBoatOnRight(Node * head, Node * currentNode,int missionaryCountOnBoat, int cannibalCountOnBoat){
    int missionaryCountLeft = currentNode->thisState->missionaryCountLeft;
    int missionaryCountRight = currentNode->thisState->missionaryCountRight;
    int cannibalCountLeft = currentNode->thisState->cannibalCountLeft;
    int cannibalCountRight = currentNode->thisState->cannibalCountRight;

    int missionaryRemOnRight = missionaryCountRight-missionaryCountOnBoat;
    int cannibalRemOnRight = cannibalCountRight-cannibalCountOnBoat;
    int cannibalAddedOnLeft = cannibalCountLeft + cannibalCountOnBoat;
    int missionaryAddedOnLeft = missionaryCountLeft + missionaryCountOnBoat;
    int left = 0;

    if(((missionaryRemOnRight>=cannibalRemOnRight) || (missionaryRemOnRight == 0)) && ((missionaryAddedOnLeft>=cannibalAddedOnLeft) || (missionaryAddedOnLeft == 0))){
        State * successorState = createState(missionaryAddedOnLeft,missionaryRemOnRight,cannibalAddedOnLeft,cannibalRemOnRight,left);
        Node * newNode = createNode(currentNode,successorState);
        //insert first
        if(head == NULL){
            head = newNode;
        }else{
            Node * temp = head;
            newNode->next = temp;
            head = newNode;
        }
    }
    return head;
}


Node * successorFunction(Node * currentNode){

    int missionaryCountLeft = currentNode->thisState->missionaryCountLeft;
    int missionaryCountRight = currentNode->thisState->missionaryCountRight;
    int cannibalCountLeft = currentNode->thisState->cannibalCountLeft;
    int cannibalCountRight = currentNode->thisState->cannibalCountRight;
    int side = currentNode->thisState->side;
    int missionaryCountOnBoat = 0;
    int cannibalCountOnBoat = 0;

    Node * head = NULL;

    //(1M,1C),(2C,0M),(2C,0M),(1M,0C),(1C,0M)
    if(side == 0){
        for(int i=1;i<=CAPACITY;i++){
            for(int j=0;j<=i;j++){
                missionaryCountOnBoat = j;
                cannibalCountOnBoat = i-j;

                if((missionaryCountOnBoat<=missionaryCountLeft) && (cannibalCountOnBoat<=cannibalCountLeft)){
                    head = addSuccessorsForBoatOnLeft(head,currentNode,missionaryCountOnBoat,cannibalCountOnBoat);
                }
            }
        }

    }else if(side == 1){

        for(int i=1;i<=CAPACITY;i++){
            for(int j=0;j<=i;j++){
                missionaryCountOnBoat = j;
                cannibalCountOnBoat = i-j;

                if((missionaryCountOnBoat<=missionaryCountRight) && (cannibalCountOnBoat<=cannibalCountRight)){
                    head = addSuccessorsForBoatOnRight(head,currentNode,missionaryCountOnBoat,cannibalCountOnBoat);
                }
            }
        }
    }

    return head;
}

//Goal Test
int isGoal(State * thisState, State * goalState){
    if((thisState->cannibalCountLeft == goalState->cannibalCountLeft) &&
       (thisState->cannibalCountRight == goalState->cannibalCountRight) &&
       (thisState->missionaryCountLeft == goalState->missionaryCountLeft) &&
       (thisState->missionaryCountRight == goalState->missionaryCountRight) &&
       (thisState->side == goalState->side))
        return 1;
    else
        return 0;
}



//Print states
void printState(State * thisState){
    int left = 0,right = 0;
    if(thisState->side==0) left =1;
    else right = 1;
    printf("{%dM, %dC, %d} \t\t {%dM, %dC, %d}]\n",thisState->missionaryCountLeft,thisState->cannibalCountLeft,left,thisState->missionaryCountRight,thisState->cannibalCountRight,right);

}

void printPath(Node * goalNode){
    if(goalNode == NULL) return;

    printPath(goalNode->parentNode);
    printState(goalNode->thisState);

}

int isSameState(State * stateA, State * stateB){
    if((stateA->cannibalCountLeft == stateB->cannibalCountLeft) &&
       (stateA->cannibalCountRight == stateB->cannibalCountRight) &&
       (stateA->missionaryCountLeft == stateB->missionaryCountLeft) &&
       (stateA->missionaryCountRight == stateB->missionaryCountRight) &&
       (stateA->side == stateB->side))
        return 1;
    else return 0;
}

int findNodeInList(List * head,Node * curNode){
    List * temp = head;
    while(temp!=NULL){
        State * stateA = temp->thisNode->thisState;
        State * stateB = curNode->thisState;
        if(isSameState(stateA,stateB) == 1) return 1;
        temp = temp->next;
    }
    return 0;
}


int main(int argc, char * argv[]){
    State * initialState = createState(3,0,3,0,0);

    State * goalState = createState(0,3,0,3,1);

    Node * startNode = createNode(NULL, initialState);
    Node * goalNode = NULL;

    List * openList = addToList(NULL,startNode);
    List * closedList = NULL;

    while(openList!=NULL){
        Node * curNode = openList->thisNode;
        Node * successorsList = successorFunction(curNode);

        while(successorsList!=NULL){
            Node * succNode = successorsList;
            successorsList = successorsList->next;
            State * succState = succNode->thisState;
            if(isGoal(succState,goalState)!=1){
                if(findNodeInList(openList,succNode) == 0 && findNodeInList(closedList,succNode)==0)
                    openList = addToList(openList,succNode);
            }else{
                goalNode = succNode;
                break;
            }
        }

        closedList = addToList(closedList,curNode);
        openList = removeFromList(openList);

        if(goalNode!=NULL) break;
    }

    printf("Solution path\n");
    printf("    Left \t\t    Right\n");
    printPath(goalNode);
}
