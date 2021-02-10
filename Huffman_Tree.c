#include<stdio.h>													
#include<string.h>
#include<stdlib.h>
#define MAX 1000   													
struct node{
	int freq;														
	char harf[MAX];
	struct node *next, *right, *left;
};

void linkedListOfTheFrequencies(char wordFromUser[]);               
void printLevelOrder(struct node* top); 							
void printCurrentLevel(struct node* top, int level); 				
struct node createOrder(struct node **headLocate, struct node *novelNode);


// INSERTION SORT OF LINKED LIST
struct node insertionSort(struct node **headLocate)
{ 	
    struct node* sortedList=NULL; 						
    struct node* current= *headLocate; 
    while(current!=NULL)
	{ 
        struct node *next=current->next;  
        createOrder(&sortedList,current); 
        current=next; 
    }  
    *headLocate=sortedList;
    return **headLocate;
}

struct node createOrder(struct node** headLocate, struct node* novelNode)
{
    struct node* now; 
    if(*headLocate==NULL ||(*headLocate)->freq>=novelNode->freq)
	{ 	
        novelNode->next=*headLocate; 
        *headLocate=novelNode; 
    } 
    else
	{ 
        now=*headLocate; 
        while(now->next!=NULL && now->next->freq< novelNode->freq)
		{ 
           now=now->next; 
        } 
        novelNode->next=now->next; 
        now->next=novelNode; 
    } 
    return **headLocate;
}  

void createAndPrintTree(struct node *head)
{		
	struct node *root;						
	struct node* up;					
	struct node* indis=head;
	struct node* after=indis->next;
	if(after==NULL)
	{							
		root=(struct node*)malloc(sizeof(struct node));
		root->freq=head->freq;
		root->left=NULL;
		root->right=NULL;
		root=head;
		strcpy(root->harf,head->harf);
	}
	else
	{
		while(after!=NULL)
		{
			struct node* middle=(struct node*)malloc(sizeof(struct node));
			middle->freq=(indis->freq+after->freq);
			middle->left=indis;
			middle->right=after;
			char letter[]="";
			strcpy(middle->harf,letter);	
			createOrder(&head,middle);
			indis=after->next;
			after=indis->next;
			if(after==NULL)
				root=indis;
		}
	}
	printLevelOrder(root);
}

void console()
{
	 char wordFromUser[MAX];
	 printf("Enter your word/sentence:");		
 	 getchar();
	 gets(wordFromUser);							
	 linkedListOfTheFrequencies(wordFromUser);		
}

void linkedListOfTheFrequencies(char wordFromUser[])
{
		struct node *head=NULL;		
		struct node *indis=NULL;
		int i;
		int counter[27];			
		for(i=0;i<27;i++)
		{			
			counter[i]=0;
		}
		for(i=0;i<strlen(wordFromUser);i++)
		{ 
			if(wordFromUser[i]>='a' && wordFromUser[i]<='z')	
				counter[wordFromUser[i]-'a']++;	 					
			else if(wordFromUser[i]==' ')      
				counter[26]++;
			else
			{
				printf("Error: Your input must include only (a-z) or space");	
				exit(0);
			}
		}
		for(i=0;i<27;i++)
		{				
			if(counter[i]!=0)
			{
				if(head==NULL)
				{					
					if(i==26)
					{			
						indis=(struct node*)malloc(sizeof(struct node));
						indis->freq=counter[i];	
						char letter[MAX]="*";   
						strcpy(indis->harf,letter);							
						indis->left=NULL;		
						indis->right=NULL;
						indis->next=NULL;	
						head=indis;
					}
					else
					{					
						indis=(struct node*)malloc(sizeof(struct node));
						indis->freq=counter[i]; 
						char letter[MAX]={i+'a'};	
						strcpy(indis->harf,letter);
						indis->left=NULL;
						indis->right=NULL;
						indis->next=NULL;
						head=indis;
					}
				}
				else
				{					
					if(i==26)
					{				
						indis=(struct node*)malloc(sizeof(struct node));
						indis->freq=counter[i];
						char letter[MAX]="*";  	
						strcpy(indis->harf,letter);	
						indis->left=NULL;
						indis->right=NULL;
						indis->next=head;	
						head=indis;			
					}
					else
					{			
						indis=(struct node*)malloc(sizeof(struct node));
						indis->freq=counter[i];
						char letter[MAX]={i+'a'};
						strcpy(indis->harf,letter);	
						indis->left=NULL;				
						indis->right=NULL;
						indis->next=head;
						head=indis;
					}
				}
			}
		}
	insertionSort(&head);								
	createAndPrintTree(head);							
}
void file()
{	
	FILE *file;								
	char wordFromUser[MAX];							
	if ((file=fopen("text.txt","r"))==NULL)
	{
				printf("FILE ERROR!\n");
				exit(1);
	}
	else{
		while(fgets(wordFromUser,sizeof(wordFromUser),file)!=NULL){
			linkedListOfTheFrequencies(wordFromUser);		
		}
		fclose(file);
	}
}

int heightOfTree(struct node *root)
{			
	if(root==NULL)
	{
		return 0;
	}
	else
	{
		int leftHeight, rightHeight;			
		leftHeight=heightOfTree(root->left);
		rightHeight=heightOfTree(root->right);	
		if(leftHeight>rightHeight)
		{				
			return leftHeight+1;				
		}
		else return rightHeight+1;
	}
}

void printLevelOrder(struct node* top)
{ 		
    int height;							
    int a; 
    height=heightOfTree(top);				
    a=0;
    while(a<=height)
	{ 							
        printCurrentLevel(top,a); 				
        printf("\n");							
		a=a+1; 
    } 
} 

void printCurrentLevel(struct node* top, int level)
{
    if(top==NULL)
	{									
    	printf("   ");
        return;
	}	
    if(level==1)
	{
        printf("(%s)%d ",top->harf,top->freq);
	}
    else if(level>1)
	{ 
        printCurrentLevel(top->left,level-1);
		printCurrentLevel(top->right,level-1);
    } 
} 

int main()
{		
	int choice; 						
	int flag;									
	flag=0;		
	while(flag==0)
	{										
		printf("Press 1 for standart input, Press 2 for reading from file: ");
		scanf("%d",&choice);
		if(choice==1||2)
		{
			flag=1;
		}
	}
	if(choice==1)											
		console(); // STD INPUT
	else 
		file();    // FILE
	return 0;
}
