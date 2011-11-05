#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <math.h>
#include <stdint.h> //for uint64_t
#define rdtsc(x) __asm__ volatile ("rdtsc" : "=A" (x))
#define MAX 3000
uint64_t a, b, c,a_multibittree,b_multibittree,a_multibit_lookup,b_multibit_lookup;
int counter=0;
int counter_lookup_multibit=0;
int lookuptimearray[MAX];
int lookuptimearray_multibit[MAX];






/**************************************Tree structure declaration**********************************************************************/


typedef struct tree_node {
	char *hop;
	struct tree_node *left;
	struct tree_node *right;
}tree_node;


struct tree_node *root, *temp, *temp_lookup;


/**************************************Multibittree structure declaration**********************************************************************/
typedef struct multibittree_node{

	char *hop_multibittree;
	struct multibittree_node *left;
	struct multibittree_node *left1;
	struct multibittree_node *right;
	struct multibittree_node *right1;
}multibittree_node;

struct multibittree_node *root_multibittree, *temp_multibittree, *temp_lookup_multibittree;

/****************************************Convert Binary Function*************************************************************************/
char * convertbinary(unsigned long y) {
	char *a;
	a = (char *) malloc(33);
	int i;
	for (i = 31; i >= 0; i--) {
		a[i] = y % 2;
		y = y / 2;
	}
	return a;

}

/****************************************Compare Times Function****************************************************************************/

int
    compare_times (const void *a, const void *b)
    {
      const int *da = (const int *) a;
      const int *db = (const int *) b;

      return (*da > *db) - (*da < *db);
    }
   
   
/*******************************************Create tree function*******************************************************************/
int count_binary_prefix=0;
void create_tree(char *st, int cdr, char *hp) //input the (store-ip converted to binary) and prefix length converted to int form-cdr and include the next hop address
{
     if{
                      
                      
	int i;
	temp = root;
	struct tree_node *node;
	for (i = 0; i < cdr; i++) {
		if (st[i] == 0) {
			if (temp->left == NULL) {
				node = (tree_node *) malloc(sizeof(struct tree_node));
				node->hop= (char *) malloc(16);
				temp->left = node;
				node->left = NULL;
				node->right = NULL;
				temp = temp->left;
				
			} else {
				temp = temp->left;
				temp->hop = hp;
			}
		} else {
			if(st[i]== 1){
			if ((temp->right) == NULL) {
				node = (tree_node *) malloc(sizeof(struct tree_node));
				node->hop= (char *) malloc(16);
				temp->right= node;
				
				node->left = NULL;
				node->right = NULL;
				//node->hop= NULL;
				temp= temp->right;
			} 
			
				else {
				temp = temp->right;
				temp->hop = hp;
				
			}
		}
		}
	}
	count_binary_prefix++;
	temp->hop = hp;
}

/**************************************************Size of binary tree**************************************************************/

float findBinTreeSize(tree_node *T) {

	if (!T)
		return 0;
	else
		return (1 + findBinTreeSize(T->left) + findBinTreeSize(T->right));
		
}

/*************************************************Lookup_tree function***************************************************************************/

char * lookup_tree(char *ip) {
	
	int i;
	char *last_hop;
	//printf("%s", st);
	temp_lookup = root;
	//printf("cccc");
	for (i = 0; i < 32; i++) {
		if (ip[i] == 0){
			if((temp_lookup->left) != NULL) {
			temp_lookup = temp_lookup->left;
			if ((temp_lookup->hop) != NULL) {
				last_hop = temp_lookup->hop;
			}
			}
		} else if (ip[i] == 1){
			if((temp_lookup->right) != NULL) {
			temp_lookup = temp_lookup->right;
			if ((temp_lookup->hop) != NULL) {
				last_hop = temp_lookup->hop;
			}
				
			}

		}
	}
	
	return (last_hop);
}
   /********************************************************Delete function***************************************************************/
  /* delete_treebinary(char *pr, int cd)
  	{
  	
  	temp=root;
  	
  	for(i=0;i<32;i++)
  	{
  	if(pr[i]==0)
  	{
  	if((temp->left)!= NULL) {
  		
  		
			temp = temp->left;
			if ((temp->hop) != NULL) {
				temp->hop=NULL;
			}
			}
		} else if (ip[i] == 1){
			if((temp_lookup->right) != NULL) {
			temp_lookup = temp_lookup->right;
			if ((temp->hop) != NULL) {
				temp->hop= NULL;
			}
				
			}

		}
	}
	
	return (last_hop);
}
   
   
   
   
   
   
   
   
    
/********************************************Create Multibittree Function2**************************************************************/
int count_multibit_prefix;
void create_multibittree(char *st, int cdr, char *hp) //input the (store-ip converted to binary) and prefix length converted to int form-cdr and include the next hop address
{
	int i;
	temp_multibittree = root_multibittree;
	for (i = 0; i < cdr; i++) {
		if (st[i]== 0){
			if(st[i+1]==0){
			
				if (temp_multibittree->left == NULL) {
				
					temp_multibittree->left = (multibittree_node *) malloc(sizeof(struct multibittree_node));
					temp_multibittree = temp_multibittree->left;
					temp_multibittree->left = NULL;
					temp_multibittree->left1 = NULL;
					temp_multibittree->right = NULL;
					temp_multibittree->right1 = NULL;
					temp_multibittree->hop_multibittree = NULL;
				
				
				
				}else {
				temp_multibittree = temp_multibittree->left;
			}/*temp_multibittree->left == NULL*/
						
			}else if(st[i+1==1]){
				if (temp_multibittree->left1 == NULL) {
				temp_multibittree->left1= (multibittree_node *) malloc(sizeof(struct multibittree_node));
				temp_multibittree = temp_multibittree->left1;
				temp_multibittree->left1=NULL;
				temp_multibittree->left = NULL;
				temp_multibittree->right = NULL;
				temp_multibittree->right1 = NULL;
				temp_multibittree->hop_multibittree = NULL;
				
			} else {
				temp_multibittree = temp_multibittree->left1;
			}
			
			}//st[i+1]==1
		
		
		
		
		}else if(st[i]==1){
		
			if(st[i+1]==0){
			
					if (temp_multibittree->right == NULL) {
						temp_multibittree->right = (multibittree_node *) malloc(sizeof(struct multibittree_node));
						temp_multibittree = temp_multibittree->right;
						temp_multibittree->left = NULL;
						temp_multibittree->left1 = NULL;
						temp_multibittree->right = NULL;
						temp_multibittree->right1 = NULL;
						temp_multibittree->hop_multibittree = NULL;
				
					} else {
						temp_multibittree = temp_multibittree->right;
					}
			
			
			}else if(st[i+1]==1){
			
			
			if (temp_multibittree->right1 == NULL) {
						temp_multibittree->right1 = (multibittree_node *) malloc(sizeof(struct multibittree_node));
						temp_multibittree = temp_multibittree->right1;
						temp_multibittree->right1 = NULL;
						temp_multibittree->left = NULL;
						temp_multibittree->left1 = NULL;
						temp_multibittree->right = NULL;
						temp_multibittree->hop_multibittree = NULL;
				
					} else {
						temp_multibittree = temp_multibittree->right1;
					}
			
			
			} //st[i+1]==0
			
		
		
		
		
		}//st[i]==0
}//for	
	count_multibit_prefix++;
	temp_multibittree->hop_multibittree = hp;
}	


/**************************************************Size of Multibit Tree**************************************************************/

float findMultiTreeSize(multibittree_node *T) {

	if (!T)
		return 0;
	else
		return (1 + findMultiTreeSize(T->left) + findMultiTreeSize(T->right)+findMultiTreeSize(T->right1)+findMultiTreeSize(T->left1));
		
}



/*************************************************Lookup_tree function for Multibit***************************************************************/

char * lookup_tree_multibit(char *ip) {
	int i;
	char *last_hop_multibittree;
	//printf("%s", st);
	temp_lookup_multibittree = root_multibittree;
	//printf("cccc");
	for (i = 0; i < 32; i++) {
		if (ip[i] == 0){
			if (ip[i+1]==0){
				if((temp_lookup_multibittree->left) != NULL) {
						temp_lookup_multibittree = temp_lookup_multibittree->left;
							if ((temp_lookup_multibittree->hop_multibittree) != NULL) {
								last_hop_multibittree = temp_lookup_multibittree->hop_multibittree;
									}
						}
				
			
			}else if(ip[i+1]==1){
				
				
				if((temp_lookup_multibittree->left1) != NULL){
				
					temp_lookup_multibittree = temp_lookup_multibittree->left1;
					if ((temp_lookup_multibittree->hop_multibittree) != NULL){
					
							last_hop_multibittree = temp_lookup_multibittree->hop_multibittree;
			
						}
				
				}
			
			}
			}else if (ip[i]=1){
			
				if (ip[i+1]==0){
				
					if((temp_lookup_multibittree->right) != NULL){
					
						temp_lookup_multibittree = temp_lookup_multibittree->right;
						if ((temp_lookup_multibittree->hop_multibittree) != NULL){
						
							last_hop_multibittree = temp_lookup_multibittree->hop_multibittree;
						
						}
					
					}
				
				
				}else if (ip[i+1]==1){
				
					if((temp_lookup_multibittree->right1) != NULL){
					
						temp_lookup_multibittree = temp_lookup_multibittree->right1;
						if ((temp_lookup_multibittree->hop_multibittree) != NULL){
						
							last_hop_multibittree = temp_lookup_multibittree->hop_multibittree;	
						
						}
					
					}
					
				
				}
		}		
			
	}
	return (last_hop_multibittree);
}

/*************************************************Update function for Multibit Tree***************************************************************/






/*********************************************Main Function***************************************************************************************/

int count_badlenght_binary=0;
int count_badlenght_multibit=0;
int main()
 {
	look
	char *message;
	message=(char *) malloc(11);
	
	
	char *xyz_bin;
	xyz_bin=(char *) malloc(15);
	
	int cdrupdate_binaryint;
	int i;
	FILE *ipfile,*lookupfile,*multibitipfile,*lookup_multibittree,*updatefile_binary;
	char strline[128];char strline_lookup[128];char strline_multibit[128];char strline_lookup_multibit[128];char strlineupdate_binary[128];
	char *prfix;
	char *prfix_multibit;
	char *prfixupdate;
	prfixupdate=(char *) malloc(13);
	prfix= (char *) malloc(33);
	prfix_multibit= (char *) malloc(33);
	char *cdrnum;char *cdrnum_multibit;
	char *cdrupdate_binary;
	cdrupdate_binary=(char *) malloc(2);
	cdrnum= (char *) malloc(2);
	cdrnum_multibit= (char *) malloc(2);
	
	char *nxthop;
	char *nxthop_multibit;
	 nxthop = (char *) malloc(16);
	 nxthop_multibit = (char *) malloc(16);
	unsigned long prfixbinary;unsigned long lookupbinary;unsigned long multibitbinary;unsigned long lookupmultibitbinary;

	char *store;char *store_lookup;char *store_multibit;char *store_lookup_multibit;
	store = (char *) malloc(33);
	store_lookup = (char *) malloc(33);
	store_multibit = (char *) malloc(33);
	store_lookup_multibit = (char *) malloc(33);
	
	int cdr;
	int cdr_multibit;

	root = (tree_node *) malloc(sizeof(struct tree_node));
	root->hop = (char *) malloc(16);

	root_multibittree = (multibittree_node *) malloc(sizeof(struct multibittree_node));
	root_multibittree->hop_multibittree = (char *) malloc(16) ;


	ipfile = fopen("load", "r");
	if (ipfile == NULL) {
		printf("Error in opening iploadfile\n");
	} else {
		printf("ipload File is opened\n");
	}

	lookupfile = fopen("lookup", "r");
		if (lookupfile == NULL) {
		printf("Error in opening lookupfile\n");
		} else {
			printf("Lookup File is opened\n");
			}
			
	lookup_multibittree = fopen("lookupmlt", "r");
		if (lookup_multibittree == NULL) {
		printf("Error in opening lookupfile for multibit tree\n");
		} else {
			printf("Lookup File is opened for multibit tree\n");
			}
			
	updatefile_binary = fopen("update", "r");
	if (updatefile_binary == NULL) {
		printf("Error in opening updatefile for binary tree\n");
	} else {
		printf("update File for binary tree is opened\n");
	}

/**************************************************Prefix load to binary tree*******************************************************/	
	int lineCounter = 0;
	while(fgets(strline, sizeof (strline), ipfile)!=NULL){
	prfix = strtok(strline, "/"); //strtok takes only string as input, does not take FILE
	cdrnum = strtok(NULL, "/ "); // Using delimiters to select the required tokens from the strline
	nxthop = strtok(NULL, " ");
	cdr = atoi(cdrnum);
	lineCounter++;
	prfixbinary = ntohl(inet_addr(prfix));
	
	store= convertbinary(prfixbinary);
	
if (cdr>31 || cdr<1){

count_badlenght_binary++;

}else create_tree(store, cdr, nxthop);
	

//	printf(" , tree size: %f\n", findBinTreeSize(root));
}

printf("/*********************************OUTPUTS FOR BINARY TREE*****************************************/\n");
printf("\n");
printf("/*******---------------------Memorey and Time values for creating  binary tree----------------******/\n");
		printf("\ntreesize: %f, lines read: %d", findBinTreeSize(root), lineCounter);
		printf("\nMemory Required for prefix tree: %.2f Byte\n", (float) findBinTreeSize(root) * sizeof(tree_node));
		printf("Number of Prefixes in binary tree: %d\n",(count_binary_prefix-count_badlenght_binary));
		printf("Number of Prefixes in badlenght prefix number: %d\n",count_badlenght_binary);
printf("/*******---------------------Memory and Time values for creating  binary tree----------------******/\n");
printf("\n");
	
fclose ( ipfile );
/*******************************************Lookup_tree outputs***********************************************/

printf("/*******------------------------Max,Min,Median, and Mean time values for Binary Tree------------------******/\n");	
			while (fgets(strline_lookup, sizeof strline_lookup, lookupfile) != NULL) {
				lookupbinary = ntohl(inet_addr(strline_lookup));
				store_lookup = convertbinary(lookupbinary);
				rdtsc(a);
				lookup_tree(store_lookup);
				rdtsc(b);
				lookuptimearray[counter]=b-a;
				counter++;

			}


		int ilhan;
		int sumtime=0;
		float middle;
		int intmiddle;
		qsort(lookuptimearray, counter,sizeof(int),compare_times);
		printf("Counter for the ips in the file: %d\n", counter);
		printf("Minimum Lookup Time for lookup in binary tree: %d\n", lookuptimearray[0]);
		printf("Maximum Lookup Time for lookup in binary tree: %d\n", lookuptimearray[counter-1]);
		for(ilhan=0;ilhan<counter;ilhan++)
			sumtime+=lookuptimearray[ilhan];
		printf("Mean Time for lookup in binary tree: %f\n", (float)sumtime/counter);
			if(counter%2==0)
		printf("Median for lookup in binary tree: %f\n", (float)(lookuptimearray[(counter/2)-1]+lookuptimearray[(counter/2)])/2);
		else{
			middle=(float)(counter/2);
			intmiddle=ceil(middle);
			printf("Median for lookup in binary tree: %f\n", (float)lookuptimearray[intmiddle]);
}
printf("/*******----------------------- Max,Min,Median, and Mean time values for Multibit Tree---------------------******/\n");

/**************************************************Prefix load to Multibit tree*******************************************************/

multibitipfile = fopen("load", "r");
	if (multibitipfile == NULL) {
		printf("Error in opening iploadfile\n");
	} else {
		printf("ipload File is opened for Multibit Tree\n");
	}
int lineCountermulti = 0;
while(fgets(strline_multibit, sizeof (strline_multibit), multibitipfile)!=NULL){

	prfix_multibit = strtok(strline_multibit, "/"); //strtok takes only string as input, does not take FILE
	cdrnum_multibit = strtok(NULL, "/ "); // Using delimiters to select the required tokens from the strline
	nxthop_multibit = strtok(NULL, " ");
	cdr_multibit = atoi(cdrnum_multibit);
	//printf("reading line %d, pref: %s, cdrnum: %d, nxthop: %s ", lineCountermulti++, prfix_multibit, cdr_multibit, nxthop_multibit);
	multibitbinary = ntohl(inet_addr(prfix_multibit));
	store_multibit=convertbinary(multibitbinary);
	
	
	if (cdr_multibit>31 || cdr_multibit<1){

	count_badlenght_multibit++;

	}else{
		rdtsc(a_multibittree);
		create_multibittree(store_multibit,cdr_multibit,nxthop_multibit);
		rdtsc(b_multibittree);
	
	} 
	
}


/*************************************************outputs for multibittree*************************************************************/
printf("/*********************************OUTPUTS FOR MULTIBIT TREE*****************************************/\n");
printf("\n");
printf("/*******---------------------Memorey and Time values for creating  multibittree----------------******/\n");
printf ("Time for creating multibit tree : %ld\n",b-a);

printf("Memory Required for prefix tree: %.2f Byte\n", (float) findMultiTreeSize(root_multibittree) * sizeof(multibittree_node));
printf("Number of Prefixes in Multibit tree: %d\n",(count_multibit_prefix-count_badlenght_multibit));
printf("Number of Prefixes in badprefix number: %d\n",count_badlenght_multibit);
printf("/*******---------------------Memorey and Time values for creating  multibittree------------------******/\n");
printf("\n");

/******************************************************Creating Lookup for multibit tree***************************************************************/
while (fgets(strline_lookup_multibit, sizeof strline_lookup_multibit, lookup_multibittree) != NULL) {
				
				lookupmultibitbinary = ntohl(inet_addr(strline_lookup_multibit));
				store_lookup_multibit = convertbinary(lookupmultibitbinary);
				rdtsc(a_multibit_lookup);
				lookup_tree_multibit(store_lookup_multibit);
				rdtsc(b_multibit_lookup);
				//printf("ip:%s hop:%s\n",strline_lookup_multibit,lookup_tree_multibit(store_lookup_multibit));
				//printf("\n");
				lookuptimearray_multibit[counter_lookup_multibit]=b_multibit_lookup-a_multibit_lookup;
				counter_lookup_multibit++;
				//break;

			}
printf("/*******------------------------Max,Min,Median, and Mean time values for Multibit Tree------------------******/\n");	
		int ilhan_multi;
		int sumtime_multi=0;
		float middle_multi;
		int intmiddle_multi;
		
		qsort(lookuptimearray_multibit, counter_lookup_multibit,sizeof(int),compare_times);
		printf("Counter for the ips in the file: %d\n", counter_lookup_multibit);
		printf("Minimum Lookup Time for multibit tree: %d\n", lookuptimearray_multibit[0]);
		printf("Maximum Lookup Time for multibit tree: %d\n", lookuptimearray_multibit[counter_lookup_multibit-1]);
		for(ilhan_multi=0;ilhan_multi<counter_lookup_multibit;ilhan_multi++)
			sumtime_multi+=lookuptimearray_multibit[ilhan_multi];
		printf("Mean Time for multibit tree: %f\n", (float)sumtime_multi/counter_lookup_multibit);
		
		if(counter_lookup_multibit%2==0)
printf("Median for multibit tree: %f\n",((float)(lookuptimearray_multibit[(counter_lookup_multibit/2)-1]+lookuptimearray_multibit[(counter_lookup_multibit/2)]))/2);
		else{
			middle_multi=(float)(counter_lookup_multibit/2);
			intmiddle_multi=ceil(middle_multi);
			printf("Median for multibit tree: %f\n", (float)lookuptimearray_multibit[intmiddle_multi]);
}
printf("/*******----------------------- Max,Min,Median, and Mean time values for Multibit Tree---------------------******/\n");
		
		


/****************************************************************************************************************************************/

/*******************************************Update binary tree***************************************************************************/
/*char *store_upbin;
store_upbin=(char *) malloc(33);
unsigned long binaryupdate;
int iii;

while (fgets(strlineupdate_binary, sizeof strlineupdate_binary,updatefile_binary) != NULL) {
        //selecting the first string line
        message = strtok(strlineupdate_binary," "); //strtok takes only string as input, does not take FILE
       
       // binaryupdate = ntohl(inet_addr(prfixupdate));
        //printf("\nbinaryupdate:  %lu",binaryupdate);
        //break;
        //store_upbin=convertbinary(binaryupdate);
        //printf("\nstore_upbin:  %s",store_upbin[31]);
        //for (iii=0;iii<32;iii++)
        //printf("\nstore_upbin:  %s",store_upbin[iii]);
        
        
     	if (strcmp(message,"ANNOUNCED:")==0){
     		 prfixupdate= strtok(NULL,"/");
        	cdrupdate_binary=strtok(NULL," ");
        	xyz_bin=strtok(NULL," ");
        		binaryupdate = ntohl(inet_addr(prfixupdate));
        		store_upbin=convertbinary(binaryupdate);
        	cdrupdate_binaryint = atoi(cdrupdate_binary);
        	create_tree(store_upbin, cdrupdate_binaryint, xyz_bin);
        	
        	}
        	
        	/*else
        	{
        	prfixupdate= strtok(NULL,"/");
        	cdrupdate_binary=strtok(NULL," ");
        	cdrupdate_binaryint = atoi(cdrupdate_binary);
        	delete_treebinary(prfixupdate, cdrupdate_binaryint);
        	}*/
        	
      //  }		
        	
        	
        	
//             }


/****************************************************************************************************************************************/

    


return 1;


}










