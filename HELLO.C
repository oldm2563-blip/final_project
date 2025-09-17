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
	printf("==================================================\n\n");
	printf("\nenter you're text plz : \n");
	printf("==================================================\n\n");
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
		printf("==================================================\n\n");
		printf("%s : %d ocurence , %d lenght \t", w1[i].word , w1[i].n , w1[i].len);
		printf("positions [");
		for(j = 0 ; j < w1[i].n ; j++)
		{
			printf("%d" , w1[i].position[j]);
            printf(",");
		}
		printf("]\n\n");
		printf("==================================================\n\n");
	}
}
void search_ex()
{
    int j = 0;
    char search [100];
	printf("==================================================\n\n");
    printf("put the word you want to search for :\n");
	printf("==================================================\n\n");
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
	           printf("==================================================\n\n");
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
	printf("==================================================\n\n");
    printf("put the part of the word you want to search for :");
	printf("==================================================\n\n");
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
	        printf("=================================================\n\n");
		        printf("%s : %d ocurence , %d lenght \t", w1[i].word , w1[i].n , w1[i].len);
		        printf("positions [");
		        for(j = 0 ; j < w1[i].n ; j++)
		        {
			        printf("%d" , w1[i].position[j]);
                    printf(",");
		        }
		        printf("]\n");
	           printf("==================================================\n\n");
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
	printf("the biggest lenght is %d \n", w1[b].len);
	printf("the smalliest lenght is %d \n", w1[a].len);
	printf("the max frequency is %d \n", w1[c].n);
}
void palin()
{
	printf("==================================================\n\n");
	
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
	printf("==================================================\n\n");
}
void argonize(char word[] , char sort [])
{
	int lon = strlen(word);
	for(int i = 0 ; i < lon ; i++)
	{
		sort[i] = word[i];
	}
	sort[lon] = '\0';
	for(int i = 0 ; i < lon - 1; i++)
	{
		for(int j = 0 ; j < lon - 1 ; j++)
		{
			if(sort[j] > sort[j + 1])
			{
				char temp = sort[j];
				sort[j] = sort [j + 1];
				sort[j + 1] = temp;
			}
		}
	}
}
void anna() 
{
	int i, j;
    char sort1[50], sorted2[50];
    int used[100] = {0};
	printf("==================================================\n\n");
    for (i = 0; i < count_uni; i++) {
        if (used[i]) continue;

        argonize(w1[i].word, sort1);
        printf("\nAnagram group: %s", w1[i].word);
        used[i] = 1;

        for (j = i + 1; j < count_uni; j++) {
            if (used[j]) continue;
            argonize(w1[j].word, sorted2);

            if (strcmp(sort1, sorted2) == 0) {
                printf(", %s", w1[j].word);
                used[j] = 1;
            }
        }
        printf("\n");
		printf("==================================================\n\n");
    }
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
		printf("=================MENU===================\n\n");
		printf("choose a number from the following : \n\n\n");
		printf("choice 1 : Enter Text to Analyse\n");
		printf("choice 2 : Show The Analysation\n");
		printf("choice 3 : search for word\n");
		printf("choice 4 : sort\n");
		printf("choice 5 : Global status\n");
		printf("choice 6 : Pqlindrqmes\n");
		printf("choice 7 : annagrams\n");
		printf("choice 8 : stars\n");
		printf("choice 0 : Exit\n");
		printf("=======================================\n\n");
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
				printf("==================================================\n\n");
				printf("pick a search way\n");
				int choice2;
				printf("1 - search for word \n 2 - search for part\n choice :");
				printf("==================================================\n\n");
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
					printf("==================================================\n\n");
						printf("error");
						printf("==================================================\n\n");
						break;
				}
				break;
			case 4:
				int choice3;
				printf("==================================================\n\n");
				printf("1 - sort alphabticly \n 2 - sort by len\n  3 - sort by oc\n choce :");
				scanf("%d" , &choice3);
				printf("==================================================\n\n");
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
						printf("==================================================\n\n");
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
printf("==================================================\n\n");
	}while(choice != 0);
	return 0;
	
}
