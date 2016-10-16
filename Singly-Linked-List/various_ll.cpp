/*
createList()
printList()
deleteList()
lengthOfList()
findKthNode()
findKthLastNode
nodeIndex()
swapNodes(Node *head,int i,int j)
swapNodes(Node *head, Node *first,Node *second)
evenOdd()
appendLastN()
removeDuplicates()
reverseLL()
reverseLL_rec()
kReverse()
mergeLLRecursively
   */
#include<iostream>
using namespace std;

struct Node {
	int data;
	Node *next;
};

Node * createList(){
	cout << "Enter Numbers Till -1: ";
	Node *head = 0;
	Node *prevNode = 0;
	int value;
	cin >> value;
	while(value != -1){
		Node *temp = new Node;
		temp->data = value;
		temp->next = NULL;
		if(!head)
			head = temp;
		else
			prevNode->next = temp;
		prevNode = temp;
	cin >> value;
	}
return head;
}

int nodeIndex(Node *head, Node *node){
	int index;
	if(head && node)
		index = 1;
	else
		index = 0;
	while(head && node && head!=node){
		index += 1;
		head = head->next;
	}
return index;
}

int lengthOfList(Node *head){
	int len = 0;
	
	while(head){
		len += 1;
		head = head->next;
	}
return len;
}

Node * findKthNode(Node *head,int posn){
	int len = lengthOfList(head);
	if(posn > len || posn<=0){
		//cout << "Chu Hai Kya Be? \n";
		return NULL;
	}

	while(head && --posn){
		head = head->next;
	}
return head;
}

Node * findKthLastNode(Node *head,int back){
	int len = lengthOfList(head);
	if(back > len || back <= 0)
		return NULL;

	len -= back;
	len++;

	while(head && --back)
		head = head->next;
return head;
}

void printList(Node *head){
	while(head){
		cout << head->data << " --> ";
		head = head->next;
	}
	cout << "NULL" << endl;
return;
}

Node * swapNodes(Node *head,int i,int j){
	int len = lengthOfList(head);
	if(i>len || j>len || i<=0 || j<=0){
		//cout << "WTF?\n";
		return head;
	}
	if(i==j)
		return head;

	if(i>j){
		int temp = i;
		i = j;
		j = temp;
	}
	Node *first = findKthNode(head,i);
	Node *second = findKthNode(head,j);

	if(first->next == second){ //Consecutive Nodes
		if(first == head){
			Node *temp = head;
			head->next = second->next;
			head = second;
			head->next = temp;
		}
		else{
			Node *firstPrev = findKthNode(head,i-1);
			Node *firstNext = findKthNode(head,i+1);
			Node *secondPrev = findKthNode(head,j-1);
			Node *secondNext = findKthNode(head,j+1);
			
			firstPrev->next = second;
			first->next = secondNext;
			second->next = first;
		}
	}
	else{
		if(first == head){
			Node *temp = head;
			Node *secondPrev = findKthNode(head,j-1);
			Node *secondNext = findKthNode(head,j+1);
			
			second->next = head->next;
			head = second;
			secondPrev->next = first;
			first->next = secondNext;
		}
		else{
			Node *firstPrev = findKthNode(head,i-1);
			Node *firstNext = findKthNode(head,i+1);
			Node *secondPrev = findKthNode(head,j-1);
			Node *secondNext = findKthNode(head,j+1);
			
			firstPrev->next = second;
			second->next = firstNext;
			secondPrev->next = first;
			first->next = secondNext;
		}
	}
return head;
}

Node *swapNodes(Node *head,Node *first, Node *second){
	int i = nodeIndex(head,first);
	int j = nodeIndex(head,second);
	int len = lengthOfList(head);
	if(i>len || j>len || i<=0 || j<=0){ //No Need
		//cout << "WTF?\n";
		return head;
	}
	if(i==j)
		return head;

	if(i>j){
		Node *temp = first;
		first = second;
		second = temp;
	}

	if(first->next == second){ //Consecutive Nodes
		if(first == head){
			Node *temp = head;
			head->next = second->next;
			head = second;
			head->next = temp;
		}
		else{
			Node *firstPrev = findKthNode(head,i-1);
			Node *firstNext = findKthNode(head,i+1);
			Node *secondPrev = findKthNode(head,j-1);
			Node *secondNext = findKthNode(head,j+1);
			
			firstPrev->next = second;
			first->next = secondNext;
			second->next = first;
		}
	}
	else{
		if(first == head){
			Node *temp = head;
			Node *secondPrev = findKthNode(head,j-1);
			Node *secondNext = findKthNode(head,j+1);
			
			second->next = head->next;
			head = second;
			secondPrev->next = first;
			first->next = secondNext;
		}
		else{
			Node *firstPrev = findKthNode(head,i-1);
			Node *firstNext = findKthNode(head,i+1);
			Node *secondPrev = findKthNode(head,j-1);
			Node *secondNext = findKthNode(head,j+1);
			
			firstPrev->next = second;
			second->next = firstNext;
			secondPrev->next = first;
			first->next = secondNext;
		}
	}
return head;
}

Node * evenOdd(Node *head){
	Node *temp = head;

	while(temp){
		int value = temp->data;
		if(value % 2 == 0){
			Node *mover = temp->next;
			while(mover){
				if(mover->data % 2 != 0){
					if(temp == head){
						head = swapNodes(head,nodeIndex(head,temp),nodeIndex(head,mover));
					}else{
						temp = swapNodes(head,nodeIndex(head,temp),nodeIndex(head,mover));
					}
					break;
				}
				mover = mover->next;
			}
		}
		temp = temp->next;
	}
return head;
}

Node *appendLastN (Node *head){
	int len = lengthOfList(head);
	int n;
	cout << "Enter Last n Nodes To Appned: ";
	cin >> n;
	if(len-n==0 || n>len)
		return head;

	Node *firstHalf = findKthNode(head,len-n);
	Node *newHead = firstHalf->next;
	
	Node *lastNode = newHead;
	while(lastNode->next){
		lastNode = lastNode->next;
	}
	lastNode->next = head;
	firstHalf->next = 0;

return newHead;
}

void removeDuplicates(Node *head){
	
	Node *temp = head;

	while(temp){
		Node *mover = temp->next;
		Node *prevNode = temp;
		while(mover){
			if(temp->data == mover->data){
				prevNode->next = mover->next;
				delete(mover);
			}
			prevNode = mover;
			mover = mover->next;
		}
		temp = temp->next;
	}
}

Node *reverseLL(Node *head){
	Node *temp = 0;
	while(head){
		Node *next = head->next;
		head->next = temp;
		temp = head;
		head = next;
	}
return temp;
}

Node * reverseLL_rec(Node * &head,Node *temp){
	if(!temp){
		return NULL;
	}
	Node *temp1 = reverseLL_rec(head,temp->next);
	if(!temp1){
		head = temp;
		return temp;
	}
	temp1->next = temp;
	return temp;
}

void kReverse(Node * &head){
	int k;
	cout << "Enter k: ";
	cin >> k;
	int len = lengthOfList(head);
	if(k > len || k<=0)
		return;
	
	int pos = 1;
	Node *prevNode = 0;
	while(pos <= len-k+1){
		Node *tempHead = findKthNode(head,pos);
		Node *tempTail = findKthNode(head,pos+k-1);
		Node *restList = tempTail->next;
		tempTail->next = 0;
		Node *newTempHead = reverseLL(tempHead);
		if(!prevNode)
			head = newTempHead;
		else
			prevNode->next = newTempHead;
		
		tempHead->next = restList;
		prevNode = tempHead;
	/* 
	   Above 2 lines same as: 

	   Node *newTempTail = newTempHead;
		
		while(newTempTail->next){
			newTempTail = newTempTail->next;
		}
		newTempTail->next = restList;
		prevNode = newTempTail;
	*/
		pos += k;
	}
return;
}

Node *mergeLLRecursively(Node *head1,Node *head2){
	
	if(!head1){
		return head2;
	}
	if(!head2){
		return head1;
	}
	if(head1->data < head2->data){
		head1->next = mergeLLRecursively(head1->next,head2);
		return head1;
	}
	else{
		head2->next = mergeLLRecursively(head1,head2->next);
		return head2;
	}
}

Node *midpoint_ll(Node *head){
	//Returns N/2 + 1 In Case Of Even
	Node *temp = head;
	while(head && head->next){
		temp = temp->next;
		head = head->next->next;
	}
return temp;
}

void deleteList(Node * head){
	while(head){
		Node *addrOfNextNode = head->next;
		delete(head);
		head = addrOfNextNode;
	}
return;
}

int main(){
	Node *head = createList();
	printList(head);

	head = swapNodes(head,1,6);
	printList(head);
	head = swapNodes(head,1,2);
	printList(head);
	head = swapNodes(head,4,2);
	printList(head);
	head = swapNodes(head,2,3);
	printList(head);
	head = swapNodes(head,4,6);
	printList(head);
	head = evenOdd(head);
	printList(head);

	head = appendLastN(head);
	printList(head);

	removeDuplicates(head);
	printList(head);
	
	head = reverseLL(head);
	printList(head);

	Node *temp = reverseLL_rec(head,head);
	temp->next = 0;
	printList(head);
	
	kReverse(head);
	printList(head);
	
	//head1 = mergeLLRecursively(head1,head2)

	cout << "MidPoint = " << midpoint_ll(head)->data << endl;

	deleteList(head);
return 0;
}


Node *selectionSort(Node *head){
	Node *looper = head;
	while(looper){
		Node *mover = looper->next;
		int min = looper->data;
		while(mover){
			if(mover->data < min)
				min = mover->data;
			mover = mover->next;
		}
	}
}
