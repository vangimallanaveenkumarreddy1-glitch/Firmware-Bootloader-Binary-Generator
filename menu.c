#include"header.h"
int main()
{
    int op;
    char file[50];
    char type[50];
    Phone phone;
    Car car;
    Mcw mcw;
    strcpy(phone.name, "Android");
    phone.brit = 30;
    phone.storage = 78;
    strcpy(phone.date, "01-09-2026");
    strcpy(phone.sim, "jio");

    strcpy(car.name, "TATA");
    strcpy(car.odo, "1200");
    car.pres = 300;
    strcpy(car.date, "01-09-2026");
    strcpy(car.fuel, "60");
    strcpy(car.mode, "Auto");

    strcpy(mcw.name, "Philips");
    mcw.heat = 24;
    mcw.lock = 0;
    strcpy(mcw.date, "01-09-2026");
    strcpy(mcw.mode, "Auto");
    mcw.timer = 50;
    
    Type mchn;
    mchn.phone = phone;
    mchn.car = car;
    mchn.MW = mcw;
    firmware fw;
    int sm=0;
    char meachine[3][20]={"Smart Phone","Microwave","Car"};
    char ans;
    int exit =0,created=0;
    do{
        printf("\n=======================================================================\n");
        printf("\n                            BOOTLOADER \n");
        printf("\n=======================================================================\n\n");
        printf("\nSelect Meachine\n---------------------\n1. Smart Phone\n2. Microwave\n3. Car\n4. Exit\n\nEnter your choice : ");
        scanf("%d",&sm);
        if(sm<4)
        do{
            printf("\n\n\t%s \n-----------------------\n",meachine[sm-1]);
            printf("\n1. Show Values\n2. Convert setting to binary\n3. Load Settings\n4. Change Values\n5. Exit\n\nEter your choice : ");
            scanf("%d",&op);
            switch(op)
            {
                case 1:
                    if(sm == 1) {
                        disp_phone(&mchn.phone);
                    }
                    else if(sm == 2) {
                        disp_mic(&mchn.MW);
                    }
                    else if(sm == 3) {
                        disp_car(&mchn.car);
                    }
                    break;
                case 2:strcpy(type,meachine[sm-1]);
                    creat_bin(&mchn,type);
                    created=1;

                    break;
                case 3: if(created==0)
                {
                    printf("\n## binary file is not created.\n");
                    printf("Choose '2' to create....\n");
                    break;
                }
                        loadfirmware(&fw,type);
                        validate(&fw,type);
                        boot(&fw,type);
                    break;
                case 4:
                    if(sm == 1) 
                    {
                        change_phone_data(&mchn.phone);
                    }
                    else if(sm == 2) 
                    {
                        change_microwave_data(&mchn.MW);
                    }
                    else if(sm == 3) 
                    {
                        change_car_data(&mchn.car);
                    }
                break;
                default:printf("Invalid choice..\n");
            }
        }while(op!=5);
    else
    {
        printf("Conform to exit (Y/N) : ");
        scanf(" %c",&ans);
        if(ans=='Y' || ans=='y')
        {
            exit=1; 
            printf("\nProgram Terminated sucessfully...\n");
        }
        else{
            printf("\nExit cancelled.....\n");
        }
       
    }
    }while(sm!=4 || exit == 0);
     
}
