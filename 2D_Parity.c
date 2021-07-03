#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

////////////////////////////////Sender's Finctions start//////////////////////////////
//Sender's Task
void Sender();

//Calculates length of the message
int msg_length(long long int n); 	

//Fills the value of msg in array					
void array_el_input(int *array,long long int binary_msg, int msg_len_original);

//Finds the padding to the msg		
int padding(int msg_len,int part_size);				

//Generats Parity bits 		
void parity_genterater(int parity[], int *arr, int msg_len, int part_size);

//Message to Receiver
void Msg_To_Receiver(int *array , int parity[], int part_size, int msg_len);
/////////////////////////////////Sender's Function Ends///////////////////////////////


/////////////////////////////////Receiver Functions Starts///////////////////////////
//Receivers Task
void Receiver();

//Check for Parity's validity
void Error_Detection(int *array, int msg_len, int part_size);
/////////////////////////////////Receiver Functions Ends////////////////////////////


void main(){
	int n;
	
	printf("*********************Hello Chum !!! Welcome to 2D (EVEN) Parity Checking*********************\n\n");
	printf("1.)				Press 1 to be part of Sender's end\n");
	printf("2.)				Press 2 to be part of Receiver's end'\n");
	
	printf("Enter your option: ");
	scanf("%d",&n);
	
	switch(n){
		case 1:
			Sender();
			break;
		case 2:
			Receiver();
			break;
		default:
			printf("..........................Please enter valid option..........................");
			break;
	}
}

void Receiver(){
	long long int msg_from_sender;
	int *array;
	int part_size;
	int msg_len;
	int i;
	
	//user input code
	printf("Sender's message: ");
	scanf("%lld", &msg_from_sender);
	
	//user input of part size
	printf("Part Size: ");
	scanf("%d", &part_size);
	
	printf("Message from Sender = %lld\nPart Size = %d\n",msg_from_sender, part_size);
	msg_len = msg_length(msg_from_sender);
	
	printf("Message Length = %d\n",msg_len);
	
	array = (int *)calloc(msg_len, sizeof(int));
	
	array_el_input(array,msg_from_sender,msg_len);
	
	printf("Message in array = ");
	for(i = 0; i < msg_len; i++){
		printf("%d",array[i]);
	}
	printf("\n");
	Error_Detection(array, msg_len-(part_size+1), part_size);
}

void Error_Detection(int *array, int msg_len, int part_size){
	int parity[part_size];	//declaring array for storing parity
	int i, j , error = 0; 
	parity_genterater(parity, array, msg_len, part_size);
	printf("Parity = ");
	for(i = 0; i <= part_size; i++){
		printf("%d",parity[i]);
	}
	
	for(i = 0, j = msg_len ; i <= part_size, j < msg_len+part_size; i++, j++){
		if(error == 1){
			printf("\n\n!!!!!!!!!!!!!!!!!!!!!!ERROR!!!!!!!!!!!!!!!!!!!!!!");
			break;
		}
		else{
			if(array[j] == parity[i]){
				continue;
			}
			else{
				error = 1;
			}
		}
	}
	if(error == 0){
		printf("\n\nXD------------You have been delivered Correct message------------XD");
	}
}

void Sender(){
	int binary_msg; 			//binary msg from user
	int part_size; 				//part size of the msg
	int msg_len_original;		//Original msg length
	int padded_bits; 			//Required padding
	int msg_len; 				//padded message if padding available 
	int *array; 				//dynamic array for storing msg 
	int i; 						//loop counter
	
	
	//Binary msg input
	printf("Enter Binary msg: ");
	scanf("%d",&binary_msg);
	
	//Part size input
	printf("Enter Part Size: ");
	scanf("%d",&part_size);
	
	//Calling msg_length function to get original msg lenght
	msg_len_original = msg_length(binary_msg);
	printf("Original msg len = %d\n",msg_len_original);
	
	//padding if any
	padded_bits = padding(msg_len_original,part_size);
	printf("Padded bit = %d\n",padded_bits);
	
	
	//padded msg_len
	msg_len = msg_len_original + padded_bits;
	printf("Padded msg len = %d\n",msg_len);
	
	//making dynamic array using calloc
	array = (int*)calloc(msg_len, sizeof(int));
	
	//getting inputs in array
	printf("Msg = ");
	array_el_input(array, binary_msg, msg_len_original);
	for(i = 0 ; i < msg_len; i++){
		printf("%d",array[i]);
	}
	
	int parity[part_size];	//declaring array for storing parity
	
	//Calling parity generater function
	parity_genterater(parity, array, msg_len, part_size);
	
	printf("\nParity = ");
	
	for(i = 0 ; i <= part_size; i++){
		printf("%d",parity[i]);
	}
	
	Msg_To_Receiver(array, parity, part_size, msg_len);
}

void Msg_To_Receiver(int *array , int parity[], int part_size , int msg_len){
	int i;
 
	printf("\n\n\nMsg to Reciever = ");
	for(i = 0; i < msg_len ; i++){
		printf("%d",array[i]);
	}
	for(i = 0; i <= part_size ; i++){
		printf("%d",parity[i]);
	}
}

int msg_length(long long int n){
	long long int temp = n;
	int count = 0;
	int rem;
	while(temp != 0){
		temp /= 10;
		count++;
	}	
	return count;
}

int padding(int msg_len_original,int part_size){
	int rem;
	if(msg_len_original >= part_size){
		rem = msg_len_original % part_size;
		if (rem == 0)
			return 0;
		else
			return (part_size - rem);
	}
	else{
		return part_size;
	}
}

void array_el_input(int *array,long long int binary_msg, int msg_len_original){
	int i;
	for(i = msg_len_original-1; i >= 0; i--){
		array[i] = binary_msg % 10;
		binary_msg /= 10;
 	}
}

void parity_genterater(int parity[], int *arr, int msg_len, int part_size){
	int i,j;
	int one_counter;
		
	for(i = 0 ; i < part_size ; i++){
		one_counter = 0;
		for(j = 0 ; j < (msg_len / part_size) ; j++){
			if(arr[i + j*part_size] == 1){
				one_counter++;
			}
		}
		if(one_counter % 2 == 1){
			parity[i] = 1;
		}
		else{
			parity[i] = 0;
		}
	}
	one_counter = 0;
	for(i = 0 ; i < part_size  ; i++){
		if(parity[i] == 1)
			one_counter++;
	}
	if(one_counter % 2 == 1)
		parity[part_size] = 1;
	else
		parity[part_size] = 0;
}
