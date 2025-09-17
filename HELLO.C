#include <stdio.h>//needed to run the code
#include <string.h> //for strings
#include <ctype.h> //for ispunct
struct word_info
{
	char word[50];
	int len;
	int n;
	int position[100];
};
struct word_info w1[100];
char text [2000];
int count_uni = 0;// unique words

//Making things globale


void remove_anomalies()
{
	int j = 0; // using for skipping the punct
	int i; // for some unknown reason the program im using dont allow int in for so yeah
	printf("enter you're text plz : ");
	fgets(text , sizeof(text) , stdin);
	text[strcspn(text , "\n")] = '\0';// remove new line
	strlwr(text);
	for(i = 0 ; text[i] != '\0' ; i++)
	{
		if(!ispunct(text[i]))
		{
			text[j++] = text[i]; // skips puncts
		}
		
	}
	text[j] = '\0';
	// now punct and upper words are gone for good
	
	
	char *split = strtok(text , " ");
	int pos = 0;
	while(split != NULL)
	{
		int found = 0;
		for(i =0 ; i < count_uni ; i++ )
		{
			if(strcmp(split , w1[i].word) == 0)
			{
				found = 1;
				w1[i].n++;
				w1[i].position[w1[i].n-1] = pos;
			}
		}
		if(!found)
		{
			strcpy(w1[count_uni].word , split);
			w1[count_uni].n = 1;
			w1[count_uni].len = strlen(w1[count_uni].word);
			w1[count_uni].position[0] = pos ;
			count_uni++;
		}
		split = strtok(NULL," ");
		pos++;
	}
	
}
void view()
{
	
	int j = 0;
	for(int i = 0 ; i < count_uni ; i++)
	{
		printf("%s : %d ocurence , %d lenght \t", w1[i].word , w1[i].n , w1[i].len);
		printf("positions [");
		for(j = 0 ; j < w1[i].n ; j++)
		{
			printf("%d" , w1[i].position[j]);
            printf(",");
		}
		printf("]\n");
	}
}
void search_ex()
{
    int j = 0;
    char search [100];
    printf("put the word you want to search for :");
    fgets(search , sizeof(search) , stdin);
    search[strcspn(search , "\n")] = '\0';
    strlwr(search);
    for(int i = 0 ; search[i] != '\0' ; i++)
    {
        if(!ispunct(search[i]))
        search[j++] = search[i];
    }
    search[j] = '\0';
    int check = 0 ;
    for (int i = 0; i < count_uni ; i++)
    {
        if(strcmp(w1[i].word , search) == 0)
        {
            
            int j = 0;
	        
		        printf("%s : %d ocurence , %d lenght \t", w1[i].word , w1[i].n , w1[i].len);
		        printf("positions [");
		        for(j = 0 ; j < w1[i].n ; j++)
		        {
			        printf("%d" , w1[i].position[j]);
                    printf(",");
		        }
		        printf("]\n");
	           
               check = 1;
               break;
        }
    }
    if(!check){
        printf(" was not found\n");
    }
    
}
void search_part()
{
    int j = 0;
    char search [100];
    printf("put the part of the word you want to search for :");
    fgets(search , sizeof(search) , stdin);
    search[strcspn(search , "\n")] = '\0';
    strlwr(search);
    for(int i = 0 ; search[i] != '\0' ; i++)
    {
        if(!ispunct(search[i]))
        search[j++] = search[i];
    }
    search[j] = '\0';
    int check = 0;
    for(int i = 0 ; i < count_uni ; i++)
    {
        char *result = strstr(w1[i].word , search);
        if(result != NULL)
        {    
            int j = 0;
	        
		        printf("%s : %d ocurence , %d lenght \t", w1[i].word , w1[i].n , w1[i].len);
		        printf("positions [");
		        for(j = 0 ; j < w1[i].n ; j++)
		        {
			        printf("%d" , w1[i].position[j]);
                    printf(",");
		        }
		        printf("]\n");
	           
               check = 1;
               break;
        }
    }
    if (check == 0)
    {
       printf("wild guess this is the second time right :\n\n");
    }
    
}
void alph_sort()
{
	for(int i = 0; i < count_uni ; i++)
	{
		for(int j = i + 1 ; j < count_uni ; j++)
		{
			if(strcmp(w1[i].word , w1[j].word) > 0)
			{
				struct word_info temp = w1[i];
				w1[i] = w1[j];
				w1[j] = temp;
			}
		}
	}
	view();
}
void len_sort()
{
	for(int i = 0; i < count_uni ; i++)
	{
		for(int j = i + 1 ; j < count_uni ; j++)
		{
			if(w1[i].len < w1[j].len)
			{
				struct word_info temp = w1[i];
				w1[i] = w1[j];
				w1[j] = temp;
			}
		}
	}
	view();
}
void occ_sort()
{
	for(int i = 0; i < count_uni ; i++)
	{
		for(int j = i + 1 ; j < count_uni ; j++)
		{
			if(w1[i].n < w1[j].n)
			{
				struct word_info temp = w1[i];
				w1[i] = w1[j];
				w1[j] = temp;
			}
		}
	}
	view();
}
void Global_view()
{
	int total = 0 ;
	int lentot = 0 ;
	float len_m ;
	for(int i = 0 ; i < count_uni ; i++)
	{
		total += w1[i].n;
	}
	float lx_dv = (float) count_uni / total;
	for(int i = 0 ; i <count_uni ;i++ )
	{
		lentot += w1[i].len;
	}
	len_m = (float)lentot / total;
	int a = 0 , b = 0 , c = 0 ;
	for(int i = 0 ; i < count_uni ; i++)
	{
		if(w1[i].len < w1[a].len) a = i;
		if(w1[i].len > w1[b].len) b = i;
		if(w1[i].n > w1[c].n) c = i;
	}
	printf("total words are %d , there are %d unique words , the dv_le is %.2f and the len_moy is %.2f\n",lentot ,count_uni ,lx_dv ,len_m );
	printf("the biggest lenght is %d \n the smallest is \n and the most frequente is \n");
}
void palin()
{
	
	for(int i = 0 ; i < count_uni ; i++)
	{
		int isp = 1;
		int size = strlen(w1[i].word);
		for(int j = 0 ; j < size/2 ; j++)
		{
			if(w1[i].word[j] != w1[i].word[size - j - 1])
			isp = 0 ;
		}
		if(isp)
		{
			printf("%s is palindrum\n" , w1[i].word);
		}
		else
			printf("%s is not palindrum\n" , w1[i].word);
	}
}
void anna()
{

}
void stars()
{
	for(int i = 0 ; i < count_uni ; i++)
	{
		printf("%s :", w1[i].word);
		for(int j = 0 ; j < w1[i].n ; j++)
		{
			printf("*");
		}
		printf("\n");
	}
}
int main ()
{
	int choice = 0 ;
	do{	
		printf("choose a number from the following : \n");
		printf("choice 1 : Enter Text to Analyse\n");
		printf("choice 2 : Show The Analysation\n");
		printf("choice 3 : search for word\n");
		printf("choice 4 : sort\n");
		printf("choice 5 : Global status\n");
		printf("choice 6 : Pqlindrqmes\n");
		printf("choice 7 : annagrams\n");
		printf("choice 8 : stars\n");
		printf("choice 0 : Exit\n");
		scanf("%d" , &choice);
         while ((getchar()) != '\n');
		switch(choice)
		{
			case 1:
				remove_anomalies();
				break;
			case 2:
				view();
				break;
			case 3:
				printf("pick a search way\n");
				int choice2;
				printf("1 - search for word \n 2 - search for part\n choice :");
				scanf("%d" , &choice2);
				while ((getchar()) != '\n');
				switch (choice2)
				{
					case 1:
						search_ex();
						break;
					case 2:
						search_part();
						break;
			
					default:
						printf("error");
						break;
				}
				break;
			case 4:
				int choice3;
				printf("1 - sort alphabticly \n 2 - sort by len\n sort by oc\n choce :");
				scanf("%d" , &choice3);
				while ((getchar()) != '\n');
				switch(choice3)
				{
					case 1:
						alph_sort();
						break;
					case 2:
						len_sort();
						break;
					case 3:
						occ_sort();
						break;
					default : printf("invalid input");
				}
				break;
			case 5 :
                Global_view();
				break;
			case 6 :
				palin();
				break;
			case 7 :
				anna();
				break;
			case 8 :
				stars();
				break;	
			case 0 :
				printf("\n\nGood Bye");
				break;	
				
			default	: printf("invalid input try again.\n\n");		
		}
	}while(choice != 0);
	return 0;
	
}
