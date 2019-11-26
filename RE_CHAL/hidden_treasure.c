#include<stdio.h>
#include <stdlib.h>
#include <windows.h>

int size_Signature=4;  //4byte
int size_FileHeader=20;//20byte

char *Read_All_byte_from_file(char *name_file){
	FILE *fileptr;
	char *buffer;
	long filelen;

	fileptr = fopen(name_file, "rb");  // Open the file in binary mode
	fseek(fileptr, 0, SEEK_END);          // Jump to the end of the file
	filelen = ftell(fileptr);             // Get the current byte offset in the file
	rewind(fileptr);                      // Jump back to the beginning of the file

	buffer = (char *)malloc((filelen+1)*sizeof(char)); // Enough memory for file + \0
	fread(buffer, filelen, 1, fileptr); // Read in the entire file
	fclose(fileptr); // Close the file
	return buffer;
}

int main(){
	int len_store=8*31;
	char name_file[]="inside-the-mind-of-a-hacker-memory.bmp";
	char *lpBaseAddress=Read_All_byte_from_file(name_file);
	DWORD DWORD_10 = *(DWORD *)(lpBaseAddress + 10);
	DWORD DWORD_18 = *(DWORD *)(lpBaseAddress + 18);
    DWORD DWORD_22 = *(DWORD *)(lpBaseAddress + 22);
    int Gia_Tri_DWORD10 = (int)&lpBaseAddress[DWORD_10];
	int i=0;
	int j=0;
	int z=0;
	int sosanh_head=0;
	int store_element=sosanh_head;
	do{
	if ( sosanh_head >= DWORD_22 )
                    break;
     int sosanh_last = 0;
	 if(store_element < len_store){
	 	char flag=0;
		 do{
            if ( sosanh_last >= DWORD_18 )
                break;
            if(store_element % 8 == 0) {
            	printf("%c", flag);
            	flag=0;
			}

            char goi=*(BYTE *)(Gia_Tri_DWORD10 + 3*(i + sosanh_last));
            //printf("%d  ", goi);

            flag=(goi<<(store_element % 8 ) )+ flag;

            store_element++;
            sosanh_last++;
            i = j;
            }
        while ( store_element < len_store );
         sosanh_head = z;
	 }
	 ++sosanh_head;
     i+= 3 * DWORD_18;
     z = sosanh_head;
     j = i;
	}
while ( store_element < len_store );
	return 0;
}
