#include"header.h"
void disp_phone(Phone *p)
{
    printf("\n---------- Phone Data ----------\n\n");
    printf("Device Name : %s\n", p->name);
    printf("Sim Card : %s\n", p->sim);
    printf("Brightness level : %d\n", p->brit);
    printf("Storage : %d\n", p->storage);
    printf("Date : %s\n", p->date);
    return;
}
void disp_mic(Mcw *m) 
{
    printf("\n--------- MicroWave Data ---------\n");
    printf("Logo : %s\n", m->name);
    printf("Temperature : %d\n", m->heat);
    printf("Child Lock : %s\n", m->lock == 1 ? "Yes" : "No");
    printf("Mode : %s\n", m->mode);
    printf("Date : %s\n", m->date);
    printf("Timer : %d\n", m->timer);
    return;
}

void disp_car(Car *c) 
{
    printf("\n---------- Car Data ---------------\n");
    printf("Brand : %s\n", c->name);
    printf("Odometer : %s\n", c->odo);
    printf("Tyre pressure : %d\n", c->pres);
    printf("Date : %s\n", c->date);
    printf("Fuel level : %s\n", c->fuel);
    printf("Mode : %s\n", c->mode);
    return;
}

void loadfirmware(firmware*fw,char* type)
 {
    
    printf("\nFirmware loading.......\n");
    sleep(3);
    FILE*fp=fopen("firmware.bin","rb");
    if(fp==NULL)
    {
        printf("File not found..\n");
        return;
    }
    int size=fread(fw->data,1,sizeof(fw->data)-1,fp);
    fclose(fp);
    if(strcmp(type, "Smart Phone") == 0) {
        Phone* p = (Phone*)fw->data;
        p->name[29] = '\0';
        p->sim[29] = '\0';
        p->date[9] = '\0';
        printf("  Cleaned phone data strings\n");
    } 
    else if(strcmp(type, "Microwave") == 0) {
        Mcw* m = (Mcw*)fw->data;
        m->name[29] = '\0';
        m->mode[29] = '\0';
        m->date[9] = '\0';
        printf("  Cleaned microwave data strings\n");
    } 
    else if(strcmp(type, "Car") == 0) {
        Car* c = (Car*)fw->data;
        c->name[29] = '\0';
        c->odo[9] = '\0';
        c->date[9] = '\0';
        c->fuel[29] = '\0';
        c->mode[29] = '\0';
        printf("  Cleaned car data strings\n");
    }
    
    fw->data[size]='\0';
    strcpy(fw->file,type);
    fw->size=size;
    fw->valid=1;
    printf("\n## Firmware lodded sucessfully..\n");
    return;
}
void validate(firmware* fw, char* type)
{
    printf("\n# Validating firmware...........\n");
    sleep(2);
    
    // Check if firmware is loaded
    if(fw->size == 0) {
        printf("ERROR: No firmware loaded! Please load firmware first.\n");
        fw->valid = 0;
        return;
    }
    
    // Check file type matches
    if(strcmp(fw->file, type) != 0) {
        printf("ERROR: Firmware type mismatch!\n");
        printf("Expected: %s, Found: %s\n", type, fw->file);
        fw->valid = 0;
        return;
    }
    
    // Check for minimum size
    int min_size = 0;
    if(strcmp(type, "Smart Phone") == 0) {
        min_size = sizeof(Phone);
    } else if(strcmp(type, "Microwave") == 0) {
        min_size = sizeof(Mcw);
    } else if(strcmp(type, "Car") == 0) {
        min_size = sizeof(Car);
    }
    
    if(fw->size < min_size) {
        printf("ERROR: Firmware size too small!\n");
        printf("Expected: %d bytes, Found: %d bytes\n", min_size, fw->size);
        fw->valid = 0;
        return;
    }
    // Check for valid data patterns
    int valid_chars = 0;
    for(int i = 0; i < fw->size && i < 200; i++) {
        if((fw->data[i] >= 0x20 && fw->data[i] <= 0x7E) || fw->data[i] == 0x00) {
            valid_chars++;
        }
    }
    
    // Calculate validation score
    float score = (float)valid_chars / fw->size * 100;
    
    if(score < 50) {
        printf("ERROR: Firmware validation failed - too much corrupt data\n");
        printf("Validation score: %.1f%%\n", score);
        fw->valid = 0;
        return;
    }
    fw->valid = 1;
    
    printf("\n## Firmware validated successfully!\n");
    printf("   Device Type: %s\n", type);
    printf("   File Size: %d bytes\n", fw->size);
    printf("   Validation Score: %.1f %%\n", score);    
    return;
}
void boot(firmware* fw, char* type)
{
    printf("\n# Booting...........\n");
    sleep(2);
    
    if(fw->valid == 0) {
        printf("ERROR: Firmware not validated!\n");
        printf("Please validate firmware first.\n");
        return;
    }
    
    printf("\n=====================================================================\n");
    printf("                             BOOTING FIRMWARE\n");
    printf("=======================================================================\n");
    printf("  Device Type: %s\n", type);
    printf("  Firmware Size: %d bytes\n", fw->size);
    printf("  Boot Status: INITIALIZING...\n\n");
    
    sleep(1);
    
    // Display structured data based on device type
    if(strcmp(type, "Smart Phone") == 0) {
        Phone* p = (Phone*)fw->data;
        printf("SMART PHONE FIRMWARE DETAILS\n-------------------------------\n");
        printf("Device Name      : %s\n", p->name);
        printf("SIM Card         : %s\n", p->sim);
        printf("Brightness Level : %d %%\n", p->brit);
        printf("Storage          : %d GB\n", p->storage);
        printf("Date             : %s\n", p->date);
        printf("----------------------------------------\n");
        printf("\nPhone initialized successfully!!!!!!!!\n");
    } 
    else if(strcmp(type, "Microwave") == 0) {
        Mcw* m = (Mcw*)fw->data;
        printf(" MICROWAVE FIRMWARE DETAILS\n");
        printf("----------------------------------------\n");
        printf("Brand            : %s\n", m->name);
        printf("Temperature      : %d°C\n", m->heat);
        printf("Child Lock       : %s\n", m->lock ? "ENABLED" : "DISABLED");
        printf("Mode             : %s\n", m->mode);
        printf("Date             : %s\n", m->date);
        printf("Timer            : %d seconds\n", m->timer);
        printf("----------------------------------------\n");
        printf("# Microwave initialized successfully!!!!!\n");
    } 
    else if(strcmp(type, "Car") == 0) {
        Car* c = (Car*)fw->data;
        printf("CAR FIRMWARE DETAILS\n");
        printf("----------------------------------------\n");
        printf("Brand             : %s\n", c->name);
        printf("Odometer          : %s KM\n", c->odo);
        printf("Tyre Pressure     : %d PSI\n", c->pres);
        printf("Date              : %s\n", c->date);
        printf("Fuel Level        : %s %%\n", c->fuel);
        printf("Driving Mode      : %s\n", c->mode);
        printf("----------------------------------------\n");
        printf("# Car initialized successfully!!!!!!\n");
    }
    
    printf("\n==========================================================\n");
    printf("                         BOOT COMPLETE\n");
    printf("===========================================================\n\n");
    
    return;
}
void change_phone_data(Phone *p)
{
    int choice;
    char input[50];
    
    printf("\n=== Change Smart Phone Settings ===\n\n");
    printf("1. Change Device Name (current: %s)\n", p->name);
    printf("2. Change SIM Card (current: %s)\n", p->sim);
    printf("3. Change Brightness (current: %d)\n", p->brit);
    printf("4. Change Storage (current: %d)\n", p->storage);
    printf("5. Change Date (current: %s)\n", p->date);
    printf("6. Back to Main Menu\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            printf("Enter new device name: ");
            scanf(" %[^\n]", input);
            strncpy(p->name, input, 29);
            p->name[29] = '\0';
            printf("Device name updated to: %s\n", p->name);
            break;
            
        case 2:
            printf("Enter new SIM card: ");
            scanf(" %[^\n]", input);
            strncpy(p->sim, input, 29);
            p->sim[29] = '\0';
            printf("SIM card updated to: %s\n", p->sim);
            break;
            
        case 3:
            printf("Enter new brightness level (0-100): ");
            scanf("%d", &p->brit);
            if(p->brit < 0) p->brit = 0;
            if(p->brit > 100) p->brit = 100;
            printf("Brightness updated to: %d\n", p->brit);
            break;
            
        case 4:
            printf("Enter new storage (GB): ");
            scanf("%d", &p->storage);
            if(p->storage < 0) p->storage = 0;
            printf("Storage updated to: %d GB\n", p->storage);
            break;
            
        case 5:
            printf("Enter new date (DD-MM-YYYY): ");
            scanf(" %[^\n]", input);
            strncpy(p->date, input, 9);
            p->date[9] = '\0';
            printf("Date updated to: %s\n", p->date);
            break;
            
        case 6:
            return;
            break;
            
        default:
            printf("Invalid choice!\n");
    }
    return;
}

void change_microwave_data(Mcw *m)
{
    int choice;
    char input[50];
    
    printf("\n=========== Change Microwave Settings ===============\n");
    printf("1. Change Brand (current: %s)\n", m->name);
    printf("2. Change Temperature (current: %d)\n", m->heat);
    printf("3. Toggle Child Lock (current: %s)\n", m->lock ? "Enabled" : "Disabled");
    printf("4. Change Mode (current: %s)\n", m->mode);
    printf("5. Change Date (current: %s)\n", m->date);
    printf("6. Change Timer (current: %d)\n", m->timer);
    printf("7. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch(choice) 
    {
        case 1:
            printf("Enter new brand name: ");
            scanf(" %[^\n]", input);
            strncpy(m->name, input, 29);
            m->name[29] = '\0';
            printf("Brand updated to: %s\n", m->name);
            break;
            
        case 2:
            printf("Enter new temperature (0-100°C): ");
            scanf("%d", &m->heat);
            if(m->heat < 0) m->heat = 0;
            if(m->heat > 100) m->heat = 100;
            printf("Temperature updated to: %d°C\n", m->heat);
            break;
            
        case 3:
            m->lock = !m->lock;
            printf("Child Lock %s\n", m->lock ? "Enabled" : "Disabled");
            break;
            
        case 4:
            printf("Enter new mode (Auto/Manual): ");
            scanf(" %[^\n]", input);
            strncpy(m->mode, input, 29);
            m->mode[29] = '\0';
            printf("Mode updated to: %s\n", m->mode);
            break;
            
        case 5:
            printf("Enter new date (DD-MM-YYYY): ");
            scanf(" %[^\n]", input);
            strncpy(m->date, input, 9);
            m->date[9] = '\0';
            printf("Date updated to: %s\n", m->date);
            break;
            
        case 6:
            printf("Enter new timer (seconds): ");
            scanf("%d", &m->timer);
            if(m->timer < 0) m->timer = 0;
            printf("Timer updated to: %d seconds\n", m->timer);
            break;
            
        case 7:
            return;
            break;
            
        default:
            printf("Invalid choice!\n");
    }
    return;
}

void change_car_data(Car *c)
{
    int choice;
    char input[50];
    
    printf("\n====================== Change Car Settings =========================\n");
    printf("1. Change Brand (current: %s)\n", c->name);
    printf("2. Change Odometer (current: %s)\n", c->odo);
    printf("3. Change Tyre Pressure (current: %d)\n", c->pres);
    printf("4. Change Date (current: %s)\n", c->date);
    printf("5. Change Fuel Level (current: %s)\n", c->fuel);
    printf("6. Change Driving Mode (current: %s)\n", c->mode);
    printf("7. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            printf("Enter new brand name: ");
            scanf(" %[^\n]", input);
            strncpy(c->name, input, 29);
            c->name[29] = '\0';
            printf("Brand updated to: %s\n", c->name);
            break;
            
        case 2:
            printf("Enter new odometer reading (KM): ");
            scanf(" %[^\n]", input);
            strncpy(c->odo, input, 9);
            c->odo[9] = '\0';
            printf("Odometer updated to: %s KM\n", c->odo);
            break;
            
        case 3:
            printf("Enter new tyre pressure (PSI): ");
            scanf("%d", &c->pres);
            if(c->pres < 0) c->pres = 0;
            if(c->pres > 500) c->pres = 500;
            printf("Tyre pressure updated to: %d PSI\n", c->pres);
            break;
            
        case 4:
            printf("Enter new date (DD-MM-YYYY): ");
            scanf(" %[^\n]", input);
            strncpy(c->date, input, 9);
            c->date[9] = '\0';
            printf("Date updated to: %s\n", c->date);
            break;
            
        case 5:
            printf("Enter new fuel level (%%): ");
            scanf(" %[^\n]", input);
            strncpy(c->fuel, input, 29);
            c->fuel[29] = '\0';
            printf("Fuel level updated to: %s%%\n", c->fuel);
            break;
            
        case 6:
            printf("Enter new driving mode (Auto/Sport/Eco): ");
            scanf(" %[^\n]", input);
            strncpy(c->mode, input, 29);
            c->mode[29] = '\0';
            printf("Driving mode updated to: %s\n", c->mode);
            break;
            
        case 7:
            return;
            break;
            
        default:
            printf("Invalid choice!\n");
    }
    return;
}