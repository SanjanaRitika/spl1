#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

void clrscr()
{
    system("@cls||clear");
}


typedef struct date
{
	int day;
	int month;
	int year;
}date;


typedef struct item
{
	int prodno;
	char prodname[30];
	int qty;
	float price;
	date mfg;
	date exp;
	char type[100];
}item;


void menu();
void add();
int  check_product_no(int prodno, int count);
void check_date(int day,int month,int year);


void view();
void view_option();
void sort_alphabetically();
void sort_product_by_no();
void search_product_no();

void delete_menu();
void delete_product_no();
void delete_name();
void delete_date();

int search(item ptr[],int pno,int count);
int searchname(item ptr[],char *pname,int count);
int dateloc(item product[],int day,int month,int year, int count);

int binarySearch(item ptr[], int pno, int count);
int binarySearchName(item ptr[], char *pname, int count);
void merge(item arr[], int left, int middle, int right, int num_based);
void mergeSort(item arr[], int left, int right, int num_based);

void modifyprice();
void modifylist();
void modifyqty();


int main()
{
	printf("\t\t SANJANA'S INVENTORY MANAGEMENT SYSTEM\n\n");
	menu();
}


void menu()
{
	
	int choice;
	printf("\n");
	printf("\nAvailable options: \n\n");
	printf("1.Add Product\n");
	printf("2.Delete Product\n");
	printf("3.Modify Product\n");
	printf("4.View Products\n");
	printf("5.Search Product\n");
	printf("6.Exit");
	printf("\n\nEnter number to proceed: \n");
	scanf("%d",&choice);	
	
	switch(choice)
	{
		case 1: add();
		break;
		case 2: delete_menu();
		break;
		case 3: modifylist();
		break;
		case 4:	view_option();
		break;
		case 5:	search_product_no();
		break;
		case 6: exit(0);
		break;
		default:
		printf("Choice is invalid!!!");
		menu();	
	}
}


void view_option()
{
	clrscr();
	
	int option;
	FILE *counter=fopen("counter.dat","r");
	int count;
	fscanf(counter,"%d",&count);
	printf("\n\t\tTotal number of available items in inventory: %d\n",count);
	printf("\n\t\tSelect option to sort items and view: %d\n",count);
	printf("\n1. Product number");
	printf("\n2. Alphabetical Order");
	printf("\n3. Last added");		
	printf("\n\nEnter number to proceed: ");		
	scanf("%d",&option);
	
	switch(option)
	{
		case 1: sort_product_by_no();
		break;
		case 2: sort_alphabetically();
		break;
		case 3: view();
		break;
		default: menu();
	}
}


void add()
{
	item product;
	char ch;
	FILE *fp=fopen("records.bin","ab");
	
	FILE *counterr=fopen("counter.dat","r");
	int count;
	fscanf(counterr,"%d",&count);
	
	
	/*
	printf("%d",count);

	//printf("Enter Product no: ");
	//scanf("%d",&product.prodno);
	*/
	
	/*
	while (fread(&product,sizeof (item),1,fp))
	{
		count++;
	}
	*/
	
	product.prodno=1000+count;
	product.prodno=check_product_no(product.prodno,count);
	
	printf("Enter name of product: ");
	scanf("%s",product.prodname);
	printf("Enter quantity of product: ");
	scanf("%d",&product.qty);
	printf("Enter price of product: ");
	scanf("%f",&product.price);
	printf("Enter manufacturing date of product: (dd/mm/yyyy) \n");
	scanf("%d/%d/%d",&product.mfg.day,&product.mfg.month,&product.mfg.year);
	check_date(product.mfg.day,product.mfg.month,product.mfg.year);
	printf("Enter expiration date of product: (dd/mm/yyyy) \n");
	scanf("%d/%d/%d",&product.exp.day,&product.exp.month,&product.exp.year);
	check_date(product.exp.day,product.exp.month,product.exp.year);
	printf("Enter the type of product : (veg/fruit/gen) \n");
	scanf("%s",product.type);
	
		
	fclose(counterr);
	count++;
	
	FILE *counterw=fopen("counter.dat","wb");
	fprintf(counterw,"%d",count);
	fclose(counterw);

	
	fwrite(&product, sizeof(item), 1, fp);
	fclose(fp);
	
	
	printf("\n\nDo you want to add more products? [Y/N]\n");
	getchar();
	scanf("%c",&ch);
	if(ch=='Y'||ch=='y')
	{
		add();
	}
	else 
	{
		printf("\n\nWould you like to go back to the menu? [Y/N]\n");
		getchar();
		scanf("%c",&ch);
		
		if(ch=='Y'||ch=='y')
		{
			menu();
		}
		
		else 
		{
			exit(0);
		}
		
	}
	
}

// checks the uniqueness of the product number by reading the existing items from the file and comparing them with the provided product number.
// If a match is found, the function increases the product number by 100 to ensure uniqueness
int check_product_no(int prodno, int count)
{
	item product[100]; 
	FILE *fp=fopen("records.bin","rb");
	fread(&product, sizeof(product), 1, fp);

	for(int i=0;i<count;i++)
	{
		if(prodno==product[i].prodno)
		{
			return prodno+100;
		}
	
	}
	
	return prodno;
	
	/*
	if(flag==0)
	{
		char ch;
		printf("\n\tSorry, the product number you inserted already exist");
		printf("\n\nWould you like to try again with another product number? [Y/N]\n");
		getchar();
		scanf("%c",&ch);
		if(ch=='Y'||ch=='y')
		{
			add();
		}
		else 
		{
			menu();
		}
	}
	*/
	
}

//view item by last added
void view()
{
	item product[100]; 
	FILE *fp=fopen("records.bin","rb");
	FILE *counter=fopen("counter.dat","r");
	
	int count=0;
	
	fscanf(counter,"%d",&count);
	fread(&product, sizeof(product), 1, fp);
	fclose(fp);
	
	/*
	while (fread(&product,sizeof (item),1,fp))
	{
		count++;
	}
	*/
	
	printf("\n ************************************************************************************************************");
	printf("\n *   Product no   *   Product Name   *   Stock   *    Price   *    Mfg date   *    Exp date    *     Type   *" );
	printf("\n ************************************************************************************************************");
	
	for(int i=0;i<count;i++)
	{
		printf("\n|   %10d   |   ",product[i].prodno);
		printf("%12s   |   ",product[i].prodname);
		printf("%5d   |   ",product[i].qty);
		printf("%.2f    |   ",product[i].price);
		printf("%2d/%2d/%2d  |   ",product[i].mfg.day,product[i].mfg.month,product[i].mfg.year);
		printf("%2d/%2d/%2d   |   ",product[i].exp.day,product[i].exp.month,product[i].exp.year);
		printf("%5s     |",product[i].type);
	}
	
	printf("\n ***********************************************************************************************************");
	
	char ch;
	printf("\n\nWould you like to go back to the menu? [Y/N]\n");
	getchar();
	scanf("%c",&ch);
	
	if(ch=='Y'||ch=='y')
	{
		menu();
	}
	
	else 
	{
		exit(0);
	}
	
}




void merge(item arr[], int left, int middle, int right, int num_based) {

    int i, j, k;
    int n1 = middle - left + 1;
    int n2 = right - middle;
    
    item L[n1], R[n2];
    
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];
    
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {


        if ((num_based == 1) ? (L[i].prodno <= R[j].prodno):(strcmp(L[i].prodname,R[j].prodname) <=0)) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(item arr[], int left, int right, int num_based) {

    if (left < right) {
        int middle = left + (right - left) / 2;
        
        mergeSort(arr, left, middle, num_based);
        mergeSort(arr, middle + 1, right, num_based);
        merge(arr, left, middle, right, num_based);

    }

}



void sort_product_by_no()
{
	item product[100]; 
	FILE *fp=fopen("records.bin","rb");
	FILE *counter=fopen("counter.dat","r");
	
	int count;
	fscanf(counter,"%d",&count);
	
	fread(&product, sizeof(product), 1, fp);
	
	mergeSort(product, 0, count - 1, 1);

	
	printf("\n*************************************************************************************************************");
	printf("\n*   Product no   *   Product Name   *   Stock   *    Price   *    Mfg date   *    Exp date    *     Type    *" );
	printf("\n*************************************************************************************************************");
	
	for(int i=0;i<count;i++)
	{
		printf("\n|   %10d   |   ",product[i].prodno);
		printf("%12s   |   ",product[i].prodname);
		printf("%5d   |   ",product[i].qty);
		printf("%.2f    |   ",product[i].price);
		printf("%2d/%2d/%2d  |   ",product[i].mfg.day,product[i].mfg.month,product[i].mfg.year);
		printf("%2d/%2d/%2d   |   ",product[i].exp.day,product[i].exp.month,product[i].exp.year);
		printf("%5s     |",product[i].type);
	}
	
	printf("\n*************************************************************************************************************");		
	
	char ch;
	fclose(fp);
	printf("\n\nWould you like to go back to the menu? [Y/N]\n");
	getchar();
	scanf("%c",&ch);
	
	if(ch=='Y'||ch=='y')
	{
		clrscr();
		menu();
	}
	
	else 
	{
		exit(0);
	}
	
}


void check_date(int day,int month,int year)
{
	if( (day>30 && month == (  2 || 4 || 6 || 9 ||  11 )))
	{
		printf("\nChoice is invalid \n Please enter correct details\n");
		add();
	}
	
	if( (day>31 && month == (  1 || 2 || 3 || 5 || 7 ||  8 ||  10 ||  12 )))
	{
		printf("\nChoice is invalid \n Please enter correct details\n");
		add();
	}
	
	if( (day>29 && month == 2))
	{
		printf("\nChoice is invalid \n Please enter correct details\n");
		add();
	}
	
	if (year<0 || year>2500)
	{
		printf("\nChoice is invalid \n Please enter correct details\n");
		add();
	}
	
	if (month<1 || month>12)
	{
		printf("\nChoice is invalid \n Please enter correct details\n");
		add();
	}

}


void sort_alphabetically()
{

	item product[100]; 
	
	FILE *fp=fopen("records.bin","rb");
	FILE *counter=fopen("counter.dat","r");
	
	int count;
	fscanf(counter,"%d",&count);
	
	fread(&product, sizeof(product), 1, fp);

	mergeSort(product, 0, count - 1, 0);

	printf("\n ************************************************************************************************************");
	printf("\n *   Product no   *   Product Name   *   Stock   *    Price   *    Mfg date   *    Exp date    *     Type   *");
	printf("\n ************************************************************************************************************");
	
	for(int i=0;i<count;i++)
	{
		printf("\n|   %10d   |   ",product[i].prodno);
		printf("%12s   |   ",product[i].prodname);
		printf("%5d   |   ",product[i].qty);
		printf("%.2f    |   ",product[i].price);
		printf("%2d/%2d/%2d  |   ",product[i].mfg.day,product[i].mfg.month,product[i].mfg.year);
		printf("%2d/%2d/%2d   |   ",product[i].exp.day,product[i].exp.month,product[i].exp.year);
		printf("%5s     |",product[i].type);
	}
	printf("\n*************************************************************************************************************");
	
	fclose(fp);
	
	char ch;
	printf("\n\nWould you like to go back to the menu? [Y/N]\n");
	getchar();
	scanf("%c",&ch);
	
	if(ch=='Y'||ch=='y')
	{
		clrscr();
		menu();
	}
	
	else 
	{
		exit(0);
	}
	
}


void delete_menu()
{
	clrscr();
	
	int choice;
	
	printf("\nEnter method to delete product: ");
	printf("\n\t1. Product Number");
	printf("\n\t2. Product Name");
	printf("\n\t3. Remove Expired Goods");
	
	printf("\n\nEnter choice to proceed: ");
	scanf("%d",&choice);
	
	switch(choice)
	{
		case 1: delete_product_no();
		break;
		case 2: delete_name();
		break;
		case 3: delete_date();
		break;
		default: 
		printf("\nChoice is invalid");
	}
	
}


void delete_product_no()
{
	item product[100]; 
	int location;
	
	FILE *fp=fopen("records.bin","rb");
	FILE *counter=fopen("counter.dat","r");
	
	int count;
	fscanf(counter,"%d",&count);
	
	fread(&product, sizeof(product), 1, fp);
	
	printf("\nEnter Product number to delete: ");
	int prodno;
	scanf("%d",&prodno);

	mergeSort(product, 0, count - 1, 1);
	location = binarySearch(product,prodno,count);
	
	int i;
	printf("%d",location);

	if(location!=-1)
	{
		for(i=location;i<count-1;i++)
		{
			product[i]=product[i+1];
		}
		count--;
		printf("Record has been succesfully deleted\n");	

		fclose(counter);
		
		FILE *counterw=fopen("counter.dat","w");
		fprintf(counterw,"%d",count);
		fclose(counterw);
		
		printf("\n ************************************************************************************************************");
		printf("\n *   Product no   *   Product Name   *   Stock   *    Price   *    Mfg date   *    Exp date    *     Type    *" );
		printf("\n ************************************************************************************************************");
		
		for(int i=0;i<count;i++)
		{
			printf("\n|   %10d   |   ",product[i].prodno);
			printf("%12s   |   ",product[i].prodname);
			printf("%5d   |   ",product[i].qty);
			printf("%.2f    |   ",product[i].price);
			printf("%2d/%2d/%2d  |   ",product[i].mfg.day,product[i].mfg.month,product[i].mfg.year);
			printf("%2d/%2d/%2d   |   ",product[i].exp.day,product[i].exp.month,product[i].exp.year);
			printf("%5s     |",product[i].type);
		}
		
		printf("\n ************************************************************************************************************");		
		
		/*FILE *fp2=fopen("records2.bin","wb");
		fwrite(&product, sizeof(item), 1, fp2);
		remove("record.bin");
		rename("record1.bin","record.bin");
		fclose(fp2);
		*/
		
		FILE *fp2=fopen("records1.bin","wb");
		fwrite(&product, sizeof(item), count, fp2);
		remove("records.bin");
		rename("records1.bin","records.bin");
		fclose(fp2);
		
		getchar();
		char ch;
		printf("\nDo you want to delete more records? [Y/N] ");
		scanf("%c",&ch);
		
		if(ch=='y'|| ch=='Y')
		{
			delete_product_no();
		}
		
		else
		{
			menu();
		}
		
	}
	
	if(location==-1)
		{
			printf("\n\nWe are sorry the item your looking for is not found\n\n");
			char ch;
			printf("\n\nWould you like to go back to the menu? [Y/N]\n");
			getchar();
			scanf("%c",&ch);
			
			if(ch=='Y'||ch=='y')
			{
				clrscr();
				menu();
			}
			else 
			{
				exit(0);
			}	
		}
}

int binarySearch(item ptr[], int pno, int count) {

	int left = 0 ;  
	int right = count - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
		
        if (ptr[mid].prodno == pno)
            return mid;
        if (ptr[mid].prodno < pno)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int binarySearchName(item ptr[], char *pname, int count) {

	int left = 0 ;  
	int right = count - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
		
        if (strcmp(ptr[mid].prodname,pname)==0)
            return mid;
        if (strcmp(ptr[mid].prodname,pname)<0)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}


int search(item ptr[],int pno,int count) 
{
	int i;
	for(i=0;i<count;i++)
	{
		if(pno==ptr[i].prodno)
		{
			return i;
			
		}
		
	}
	return -1;
	
}

	
	
void delete_name()
{
	item product[100]; 
	int location;
	
	FILE *fp=fopen("records.bin","rb");
	FILE *counter=fopen("counter.dat","r");
	
	int count;
	char pname[100];
	
	fscanf(counter,"%d", &count);
	fclose(counter);
	
	fread(&product, sizeof(product), 1, fp);
	
	printf("\nEnter name of item to be deleted: ");
	scanf("%s",pname);

	mergeSort(product, 0, count - 1, 0);
	location= binarySearchName(product,pname,count); //searchname(product,pname,count);
	int i;
	if(location!=-1)
	{
	
		for(i=location;i<count-1;i++)
		{
			product[i]=product[i+1];
		
		}
		count--;	
	
		printf("Record has been succesfully deleted\n");
		printf("\n ************************************************************************************************************");
		printf("\n *   Product no   *   Product Name   *   Stock   *    Price   *    Mfg date   *    Exp date    *     Type   *" );
		printf("\n ************************************************************************************************************");
		
		for(int i=0;i<count;i++)
		{
			printf("\n|   %10d   |   ",product[i].prodno);
			printf("%12s   |   ",product[i].prodname);
			printf("%5d   |   ",product[i].qty);
			printf("%.2f    |   ",product[i].price);
			printf("%2d/%2d/%2d  |   ",product[i].mfg.day,product[i].mfg.month,product[i].mfg.year);
			printf("%2d/%2d/%2d   |   ",product[i].exp.day,product[i].exp.month,product[i].exp.year);
			printf("%5s     |",product[i].type);
		}
		
		printf("\n ************************************************************************************************************");		
		
		/*FILE *fp2=fopen("records2.bin","wb");
		fwrite(&product, sizeof(item), 1, fp2);
		remove("record.bin");
		rename("record1.bin","record.bin");
		fclose(fp2);
		*/
		
		FILE *fp2=fopen("records1.bin","wb");
		fwrite(&product, sizeof(item), count, fp2);
		remove("records.bin");
		rename("records1.bin","records.bin");
		fclose(fp2);
			
		FILE *counterw=fopen("counter.dat","w");
		fprintf(counterw,"%d",count);
		fclose(counterw);
		
		getchar();
		char ch;
		printf("\nDo you want to delete more records? [Y/N] ");
		scanf("%c",&ch);
		
		if(ch=='y'|| ch=='Y')
		{
			delete_product_no();
		}
		
		else
		{
			
			menu();
		}
		
	}
	
	if(location==-1)
		{
			printf("\n\nWe are sorry the item your looking for is not found\n\n");
			char ch;
			printf("\n\nWould you like to go back to the menu? [Y/N]\n");
			getchar();
			scanf("%c",&ch);
		
			if(ch=='Y'||ch=='y')
			{
				clrscr();
				menu();
			}
		
			else 
			{
				exit(0);
			}
		
		}

} 

	
int searchname(item ptr[],char *pname,int count)
{
	int i;
	for(i=0;i<count;i++)
	{
		if(strcmp(pname,ptr[i].prodname)==0)
		{
			return i;
			
		}

	}
	return -1;
	
}


void delete_date()
{
	item product[100]; 
	int location=0;

	FILE *fp=fopen("records.bin","rb");
	FILE *counter=fopen("counter.dat","r");

	int count;
	fscanf(counter,"%d",&count);
	fread(&product, sizeof(product), 1, fp);
	fclose(counter);
	
	date d;
	printf("Enter current date(dd/mm/yyyy)\n");
	scanf("%d/%d/%d",&d.day,&d.month,&d.year);
	
	if( (d.day>30 && d.month == (  2 || 4 || 6 || 9 ||  11 )))
	{
		printf("\nDate is invalid! \nPlease enter correct details\n");
		scanf("%d/%d/%d",&d.day,&d.month,&d.year);
	}

	if( (d.day>31 && d.month == (  1 || 2 || 3 || 5 || 7 ||  8 ||  10 ||  12 )))
	{
		printf("\nDate is invalid! \nPlease enter correct details\n");
		scanf("%d/%d/%d",&d.day,&d.month,&d.year);
	}

	if( (d.day>29 && d.month == 2))
	{
		printf("\nDate is invalid! \nPlease enter correct details\n");
		scanf("%d/%d/%d",&d.day,&d.month,&d.year);
	}

	if (d.year<0 || d.year>2500)
	{
		printf("\nDate is invalid! \nPlease enter correct details\n");
		scanf("%d/%d/%d",&d.day,&d.month,&d.year);
	}

	if (d.month<1 || d.month>12)
	{
		printf("\nDate is invalid! \nPlease enter correct details\n");
		scanf("%d/%d/%d",&d.day,&d.month,&d.year);
	}
	

	printf("\nDeleted item list\n");

	while(1)
	{
		location=dateloc(product,d.day,d.month,d.year,count);
		if(location!=-1)
		{
			for(int i=location;i<count;i++)
			{
				printf("Product Number: %d   |    Product name: %s\n",product[i].prodno,product[i].prodname);
				product[i]=product[i+1];
				count--;
				
			}
			
			FILE *counterw=fopen("counter.dat","w");
			fprintf(counterw,"%d",count);
			fclose(counterw);
			
			FILE *fp=fopen("records.bin","wb");
			fwrite(&product, sizeof(item), 1, fp);
			fclose(fp);
		
		}
		
		if(location==-1)
		{
			printf("\nThere are no more expired items in the inventory\n\n");
			char ch;
			printf("\n\nWould you like to go back to the menu? [Y/N]\n");
			getchar();
			scanf("%c",&ch);
		
			if(ch=='Y'||ch=='y')
			{
				clrscr();
				menu();
			}
		
			else 
			{
				exit(0);
			}
		
		}
	
	}

}	
	


int dateloc(item product[],int day,int month,int year, int count)
{
	int i;

	for(i=0;i<count;i++)
	{
		if(year>product[i].exp.year)
		{
			return i;
		}
		
		else if(year==product[i].exp.year && month>product[i].exp.month)
		{
			return i;
		}
		
		else if(year==product[i].exp.year && month==product[i].exp.month && day>product[i].exp.day)
		{
			return i;
		}
		
	}

	return -1;

}


void modifylist()
{
	printf("\nOptions\n");
	printf("\n\t1. Update Price");
	printf("\n\t2. Update Quantity");
	printf("\n\nEnter choice\n");
	int choice; 
	scanf("%d",&choice);

	switch (choice)
	{
		case 1: modifyprice();
		break; 

		case 2: modifyqty();
		break;

		default: printf("\nChoice is invalid!!");
		modifylist();
				
	}
	
}


void modifyprice()
{
	item product[100];
	int pno; 
	int location;

	FILE *fp=fopen("records.bin","rb");
	fread(&product, sizeof(product),1,fp);
	
	FILE *counter=fopen("counter.dat","r");
	int count;
	fscanf(counter,"%d",&count);
	fclose(counter);
	
	printf("\nEnter product number of item to be modified: ");
	scanf("%d",&pno); 

	int price; 
	printf("\nEnter new price: ");
	scanf("%d",&price); 
	
    mergeSort(product, 0, count - 1, 1);
	location = binarySearch(product,pno,count);
	
    if (location != -1)
    {
		product[location].price=price;
    	printf("\n\nPrice updated\n");

		FILE *fp2=fopen("records1.bin","wb");
		fwrite(&product, sizeof(item), count, fp2);
		remove("records.bin");
		rename("records1.bin","records.bin");
		fclose(fp2);
		
		char ch;
		printf("\n\nDo you want to modify more records? [Y/N]\n ");
		getchar();
		scanf("%c",&ch);
		
		if(ch=='y'|| ch=='Y')
		{
			modifyprice();
		}
		
		else
		{
			char ch;
			printf("\nWould you like to go back to menu? [Y/N]\n ");
			getchar();
			scanf("%c",&ch);	
		
			if(ch=='y'|| ch=='Y')
			{
				menu();
			}
		
			else
			{
				exit(0);
			}
		
		}

		
    }
    
    else
    {
		printf("\n\nEntered item not found!\n");
		char ch;
		printf("\nDo you want to try again? [Y/N] ");
		scanf("%c",&ch);
		
		if(ch=='y'|| ch=='Y')
		{
			modifyprice();
		}
		
		else
		{
			menu();
		}
		
	}
		
		
}

//binary search
void search_product_no()
{
	item product[100]; 
	int location;
	
	FILE *fp=fopen("records.bin","rb");
	FILE *counter=fopen("counter.dat","r");
	
	int count;
	fscanf(counter,"%d",&count);
	
	fread(&product, sizeof(product), 1, fp);
	
	printf("\nEnter Product number of item to search: ");
	int prodno;
	scanf("%d",&prodno);

	mergeSort(product, 0, count - 1, 1);
	location = binarySearch(product,prodno,count);
	

	if(location==-1)
		{
			printf("We are sorry the item your looking for is not found\n\n");
			char ch;
			printf("\n\nWould you like to go back to the menu? [Y/N]\n");
			getchar();
			scanf("%c",&ch);
			
			if(ch=='Y'||ch=='y')
			{
				clrscr();
				menu();
			}
			else 
			{
				exit(0);
			}	
		}
	else{
		
		printf("\n ************************************************************************************************************");
		printf("\n *   Product no   *   Product Name   *   Stock   *    Price   *    Mfg date   *    Exp date    *     Type   *" );
		printf("\n ************************************************************************************************************");
			
		printf("\n|   %10d   |   ",product[location].prodno);
		printf("%12s   |   ",product[location].prodname);
		printf("%5d   |   ",product[location].qty);
		printf("%.2f    |   ",product[location].price);
		printf("%2d/%2d/%2d  |   ",product[location].mfg.day,product[location].mfg.month,product[location].mfg.year);
		printf("%2d/%2d/%2d   |   ",product[location].exp.day,product[location].exp.month,product[location].exp.year);
		printf("%5s     |",product[location].type);
			
			
		printf("\n ************************************************************************************************************");

		char ch;
		fclose(fp);
		printf("\n\nWould you like to go back to the menu? [Y/N]\n");
		getchar();
		scanf("%c",&ch);
		
		if(ch=='Y'||ch=='y')
		{
			clrscr();
			menu();
		}

		
		else 
		{
			exit(0);
		}
	}
}
    

void modifyqty()
{
	item product[100];
	int pno; 
	int location;

	FILE *fp=fopen("records.bin","rb");
	fread(&product, sizeof(product),1,fp);
	
	FILE *counter=fopen("counter.dat","r");
	int count;
	fscanf(counter,"%d",&count);
	fclose(counter);
	
	printf("\nEnter product number of item to be modified\n");
	scanf("%d",&pno); 
	int qty; 
	printf("\nEnter new Quantity\n");
	scanf("%d",&qty); 
	
	mergeSort(product, 0, count - 1, 1);
	location = binarySearch(product,pno,count);

    if (location != -1)
    {
		product[location].qty=qty;
    	printf("\n\nPrice updated\n");
		FILE *fp2=fopen("records1.bin","wb");
		fwrite(&product, sizeof(item), count, fp2);
		remove("records.bin");
		rename("records1.bin","records.bin");
		fclose(fp2);
		
		char ch;
		printf("\nDo you want to modify more records? [Y/N] \n");
		getchar();
		scanf("%c",&ch);
		if(ch=='y'|| ch=='Y')
		{
			modifyprice();
		}
		
		else
		{
			char ch;
			printf("\nWould you like to go back to menu? [Y/N] \n");
			getchar();
			scanf("%c",&ch);	
		
			if(ch=='y'|| ch=='Y')
			{
				menu();
			}
		
			else
			{
				exit(0);
			}
		
		}

		
    }
    
    else
    {
		printf("\n\nEntered item not found!\n");
		char ch;
		printf("\nDo you want to try again? [Y/N] \n");
		scanf("%c",&ch);
		
		if(ch=='y'|| ch=='Y')
		{
			modifyprice();
		}
		
		else
		{
			char ch;
			printf("\nWould you like to go back to menu? [Y/N] \n");
			scanf("%c",&ch);	
		
			if(ch=='y'|| ch=='Y')
			{
				menu();
			}
		
			else
			{
				exit(0);
			}
			
		}
	
	}
				
}
