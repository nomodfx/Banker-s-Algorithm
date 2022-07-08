#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Declare dynamic arrays and global variables*/
int *resource = NULL;
int *available = NULL;
int *max_claim = NULL;
int *allocated = NULL;
int *need = NULL;
int num_process;
int num_resources;

void output_resources() {
    
    //resources, units
    printf ("\n\tUnits\tAvailable:");
    
    for (int i = 0; i < num_resources; i++){ 
        printf("\nr%d",i);
        printf ("\t%d\t%d", resource[i], available[i]);
    }
}

void output_matrix(){
    
    // print the max_claim, allocated, need
    printf ("\n\n\tMaximum\t\t\tCurrent\t\t\tPotential\n");
    printf("\tr0\tr1\tr2\tr0\tr1\tr2\tr0\tr1\tr2\n");
  
    for (int i = 0; i < num_process; i++) {
        printf ("p%d", i);
        for (int j = 0; j < num_resources; j++){
            printf ("\t%d", max_claim[i*num_resources+j]);
        }
        for (int j = 0; j < num_resources; j++){
            printf("\t%d", allocated[i*num_resources+j]);
        }
        for (int j = 0; j < num_resources; j++){
            printf("\t%d", need[i*num_resources+j]);
        }
        printf ("\n");
    }
	
    return;
}

void option_1() {

    printf ("Enter number of processes: ");
    scanf ("%d", &num_process);
    
    printf ("Enter number of resources: ");
    scanf ("%d", &num_resources);
    
    /* allocate memory for vectors and arrays: resource, available, max_claim, allocated, need */	
	resource = (int *)malloc(num_resources * sizeof(int));
	available = (int *)malloc(num_resources * sizeof(int));
	
	max_claim = (int *)malloc(num_process * num_resources * sizeof(int)); 
	allocated = (int *)malloc(num_process * num_resources * sizeof(int)); 
	need = (int *)malloc(num_process * num_resources * sizeof(int)); 
	
    printf ("Enter number of units for resources (r0 to r%d): ", (num_resources - 1));
    for (int i = 0; i < num_resources; i++) {
        scanf ("%d", &resource[i]);
        available[i] = resource[i];

    }
    
    for (int i = 0; i < num_process; i++) {
        printf ("Enter max units process p%d will request for each resource (r0 to r%d): ", i, (num_resources - 1));
        for (int j = 0; j < num_resources; j++){
            scanf ("%d", &max_claim[i*num_resources+j]);
        }
    }
    
    for (int i = 0; i < num_process; i++) {
        printf ("Enter number of units each resource (r0 to r%d) allocated to process p%d: ", (num_resources - 1), i);
        for (int j = 0; j < num_resources; j++) {
            scanf ("%d", &allocated[i*num_resources+j]);
            available[j] -= allocated[i*num_resources+j];
            need[i*num_resources+j] = max_claim[i*num_resources+j] - allocated[i*num_resources+j];
        }
    }
	
    output_resources();
    output_matrix();
    return;
}

void option_2() {
	
    int at_least_one_sequenced = 1;
    //if resources are either processed or not processed
    bool processed[num_process];
    for (int i = 0; i < num_process; i++) {
        processed[num_process] = false;
    }

    for (int k = 0; k < num_process; k++) {
        for (int i = 0; i < num_process; i++) {
            //resources already processed
            if (!processed[i]) {
                printf ("Checking: < ");
                
                for (int j = 0; j < num_resources; j++) { 
                    printf ("%d ", need[i*num_resources+j]);
                }
                printf ("> <= < ");
                
                for (int j = 0; j < num_resources; j++) {
                    printf ("%d ", available[i*num_resources+j]);
                }
                
                printf ("> ");
                
                //if resource can be assigned to process
                bool process = true;
                
                for (int j = 0; j < num_resources; j++) {
                    if (need[i*num_resources+j] > available[j]) {
                        process = false;
                    }
                }

                //completed assigned resources               
                if (process) {
                
                    for (int j = 0; j < num_resources; j++) {
                        available[j] += allocated[i*num_resources+j];
                    }
                    //processed successfully sequenced
                    processed[i] = true;
                    printf (":p%d safely sequenced", i);
                }
                //processed failed sequencing
                else {
                    printf(":p%d could not be sequenced", i);
                }
                printf ("\n");
            }
        }
    }
    if(at_least_one_sequenced==0) {
        printf("Deadlock reached!\n");
    }
	
    return;
}

void free_resource() {
	///* check if vectors/array are not NULL--if so, free each vector/array */	);
	if(resource != NULL){
	    
		free(resource);
		free(available);
		free(allocated);
	
	    
	}
	
	return;
}

int main() {

	/* Declare local variables */
	
	/* Until the user quits, print the menu, prompt for the menu choice, call the appropriate procedure */
	int choice = 0;

	while (choice != 3) {
		
	    printf("\nBanker's Algorithm\n");
	    printf("--------------------------------\n");
	    printf("1) Enter parameters\n");
	    printf("2) Determine safe sequence\n");
	    printf("3) Quit program\n");

	    printf("\nEnter choice: ");
	    scanf("%d", &choice);
	
	    switch(choice){
	        case 1: 
	            option_1(); 
	            break;
		    case 2: 
			    option_2(); 
			    break;
		    case 3: 
			    printf("Quitting program...");
			    break;
		    default: 
		        printf("Invalid choice\n"); 
				break;
	    }
    }
    
	return 1;
}