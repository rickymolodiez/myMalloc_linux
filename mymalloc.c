#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>


void *mallocAndPrint(size_t myLength, int prot, int flags, int fileDescriptor, int myOffset, char *message);


int main(){
    char content[100];
    printf("Enter something meaningful (or not) to be stored in memory: ");
    scanf("%s", content);   
    int sizeM;
    printf("Enter the length (in kilobytes) of the desired memory partition:\n");
    scanf("%d", &sizeM);
    size_t size =  (size_t) sizeM + strlen(content);
    int prot = 0x1 | 0x2;
    int flags = -1;
    int fd = -1;
    int offset = 0;
    long len=size*1024;
    void *addr = mmap(NULL, len, prot, flags, fd, offset);
    if(addr==0){
        perror("system call mmap has failed!");
    }
    int *vmAddr = (int*)addr;
    printf("if you didn't see the error message, then that means mmap has allocated virtual memoryat %p\n", vmAddr); 

return 0;

}


