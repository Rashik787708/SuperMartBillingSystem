#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

struct Product{
    int id;
    char name[100];
    float price;
    int quantity;
};
struct Product p[100];
int i=0;
void loadProducts(){
    FILE *fp;
    fp = fopen("products.txt","r");
    if(fp == NULL)
        return;
    while(fscanf(fp,"%d %s %f %d",&p[i].id,p[i].name,&p[i].price,&p[i].quantity) == 4){
        i++;
    }
    fclose(fp);
}
void saveProducts(){
    FILE *fp;
    fp = fopen("products.txt","w");
    if(fp == NULL)
    {
        printf("\nUnable to Open File!\n");
        return;
    }

    for(int j=0;j<i;j++)
    {
        fprintf(fp,"%d %s %.2f %d\n",
                p[j].id,
                p[j].name,
                p[j].price,
                p[j].quantity);
    }

    fclose(fp);
}
bool validId(int ind){
    for(int j=0;j<i;j++){
        if(ind!=j && p[ind].id==p[j].id){
            return true;
        }
    }
    return false;
}

int enterId(){
    int id;
    printf("Enter Product ID : ");
    scanf("%d",&id);

    for(int j=0;j<i;j++){
        if(id==p[j].id){
            return j;
        }
    }

    printf("\n!!! Product ID Not Found !!!\n");
    return -1;
}

void display(int j){
    printf("\n-----------------------------\n");
    printf("Product Name    : %s\n",p[j].name);
    printf("Product ID      : %d\n",p[j].id);
    printf("Product Price   : %.2f\n",p[j].price);
    printf("Available Stock : %d\n",p[j].quantity);
}

bool admin(){
    char uname[100],pass[100];

    for(int k=0;k<3;k++){

        printf("\nEnter Username : ");
        scanf("%s",uname);

        printf("Enter Password : ");
        scanf("%s",pass);

        if(strcmp(uname,"Admin")==0 &&
           strcmp(pass,"jjcet@123")==0){
            return true;
        }

        printf("\nIncorrect Username or Password!\n");
    }

    printf("\nSYSTEM LOCKED!\n");
    return false;
}

void addProduct(){

    printf("Enter Product Name : ");
    scanf("%s",p[i].name);

    printf("Enter Product ID : ");
    scanf("%d",&p[i].id);

    if(validId(i)){
        printf("\nDuplicate Product ID!\n");
        return;
    }

    printf("Enter Product Price : ");
    scanf("%f",&p[i].price);

    printf("Enter Quantity : ");
    scanf("%d",&p[i].quantity);

    i++;

    saveProducts(); 

    printf("\nProduct Added Successfully!\n");
}

void view(){

    if(i==0){
        printf("\nNo Products Available!\n");
        return;
    }

    for(int j=0;j<i;j++){
        display(j);
    }
}

void search(){

    int index=enterId();

    if(index!=-1){
        printf("Product Found!\n");
        display(index);
        
    }
}

int findIndex(int id){

    for(int j=0;j<i;j++){
        if(p[j].id==id){
            return j;
        }
    }

    return -1;
}
void updateProduct(){

    int id,index;

    printf("Enter Product ID to Update : ");
    scanf("%d",&id);

    index=findIndex(id);

    if(index==-1){
        printf("\nProduct Not Found!\n");
        return;
    }

    printf("Enter New Product Name : ");
    scanf("%s",p[index].name);

    printf("Enter New Price : ");
    scanf("%f",&p[index].price);

    printf("Enter New Quantity : ");
    scanf("%d",&p[index].quantity);

    saveProducts();     

    printf("\nProduct Updated Successfully!\n");
}

void deleteProduct(){

    int id,index;

    printf("Enter Product ID to Delete : ");
    scanf("%d",&id);

    index=findIndex(id);

    if(index==-1){
        printf("\nProduct Not Found!\n");
        return;
    }

    for(int j=index;j<i-1;j++){
        p[j]=p[j+1];
    }

    i--;

    saveProducts();  

    printf("\nProduct Deleted Successfully!\n");
}

void printBill(){

    int id,qty,index;
    float total=0,bill;

    printf("\n========== BILL ==========\n");

    while(1){

        printf("\nEnter Product ID (0 to Finish) : ");
        scanf("%d",&id);

        if(id==0)
            break;

        index=findIndex(id);

        if(index==-1){
            printf("Invalid Product ID!\n");
            continue;
        }

        printf("Enter Quantity : ");
        scanf("%d",&qty);

        if(qty>p[index].quantity){
            printf("Only %d item(s) available!\n",p[index].quantity);
            continue;
        }

        bill=p[index].price*qty;
        total+=bill;

        p[index].quantity-=qty;

        printf("%-15s x %d = %.2f\n",
               p[index].name,
               qty,
               bill);
    }

    saveProducts();      

    printf("\n--------------------------\n");
    printf("Total Amount : %.2f\n",total);
    printf("==========================\n");
}

int main(){

    int choice;

    loadProducts();     

    if(!admin()){
        return 0;
    }

    while(1){

        printf("\n=================================\n");
        printf("      POS BILLING SYSTEM\n");
        printf("=================================\n");
        printf("1. Add Product\n");
        printf("2. View Products\n");
        printf("3. Search Product\n");
        printf("4. Update Product\n");
        printf("5. Delete Product\n");
        printf("6. Print Bill\n");
        printf("7. Exit\n");
        printf("=================================\n");
        printf("Enter Your Choice : ");
        scanf("%d",&choice);

        switch(choice){

            case 1:
                addProduct();
                break;

            case 2:
                view();
                break;

            case 3:
                search();
                break;

            case 4:
                updateProduct();
                break;

            case 5:
                deleteProduct();
                break;

            case 6:
                printBill();
                break;

            case 7:
                printf("\nThank You for Using POS Billing System.\n");
                return 0;

            default:
                printf("\nInvalid Choice! Please Try Again.\n");
        }
    }

    return 0;
}
