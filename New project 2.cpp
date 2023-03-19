//
// Created by Ritika on 1/27/2023.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void clear_screen()
{
    system("@cls||clear");
}

typedef struct date_t
{
    int day;
    int month;
    int year;
} date_t;

typedef struct item_t
{
    int id;
    char name[30];
    int quantity;
    float cost;
    date_t mfg;
    date_t exp;
    char category[100];
} item_t;

void main_menu();
void add_item();
int check_id(int id, int count);
void check_date(int day,int month,int year);

void view_items();
void view_options();
void sort_alphabetically();
void sort_id();

void delete_menu();
void delete_by_id();
void delete_by_name();
void delete_by_date();

int search_by_id(item_t items[],int id,int count);
int search_by_name(item_t items[],char *name,int count);
int search_by_date(item_t items[],int day,int month,int year, int count);

void modify_cost();
void modify_options();
void modify_qty();

int main()
{
    printf("\t\tWelcome to Sanjana's INVENTORY MANAGEMENT SYSTEM\n\n");
    main_menu();
}

void main_menu()
{
    int choice;
    printf("\n");
    printf("\nEnter option\n\n");
    printf("1.Add Product\n");
    printf("2.Delete Product\n");
    printf("3.Modify Product\n");
    printf("4.View products\n");
    printf("5.Exit");
    printf("\n\nEnter Choice\n");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1: add_item();
            break;
        case 2: delete_menu();
            break;
        case 3: modify_options();
            break;
        case 4: view_options();
            break;
        case 5: exit(0);
            break;
        default:
            printf("Invalid Choice!!!");
            main_menu();

    }

}






void view_options()
{
    clrscr();

    int user_choice;
    ILE *file_pointer=fopen("counter.dat","r");
    int item_count;
    fscanf(file_pointer,"%d",&item_count);
    printf("\n\t\tTotal number of items in inventory: %d\n",item_count);

    printf("\n1. View items by product number");
    printf("\n2. View items alphabetically ");
    printf("\n3. View items by last added");
    printf("\n\nEnter option: ");
    scanf("%d",&user_choice);

    switch(user_choice)
    {
      case 1: sort_by_product_number();
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
	FILE *fp=fopen("records.bin","ab4");
	
	FILE *counterr=fopen("counter.dat","r");
	int count;
	fscanf(counterr,"%d",&count);
	
	

	product.prodno=1000+count;
	product.prodno=checkprodno(product.prodno,count);
	
	printf("Enter Product Name: ");
	scanf("%s",product.prodname);
	printf("Enter Quantity: ");
	scanf("%d",&product.qty);
	printf("Enter Price: ");
	scanf("%f",&product.price);
	printf("Enter manufacturing date of item: (dd/mm/yyyy) \n");
	scanf("%d/%d/%d",&product.mfg.day,&product.mfg.month,&product.mfg.year);
	checkdate(product.mfg.day,product.mfg.month,product.mfg.year);
	printf("Enter expiration date of item: (dd/mm/yyyy) \n");
	scanf("%d/%d/%d",&product.exp.day,&product.exp.month,&product.exp.year);
	checkdate(product.exp.day,product.exp.month,product.exp.year);
	printf("Enter type of item: (veg/fruit/gen) \n");
	scanf("%s",product.type);
	
		
	fclose(counterr);
	count++;
	
	FILE *counterw=fopen("counter.dat","w");
	fprintf(counterw,"%d",count);
	fclose(counterw);

	
	fwrite(&product, sizeof(item), 1, fp);
	fclose(fp);
	
	
	printf("\n\nDo you want to add more items? [Y/N]\n");
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

