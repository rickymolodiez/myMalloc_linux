#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define SYS_mmap 197

void *mallocAndPrint(size_t myLength, int prot, int flags, int fileDescriptor, int myOffset, char *message);
// https://developer.apple.com/library/archive/documentation/System/Conceptual/ManPages_iPhoneOS/man2/mmap.2.html
//197	AUE_MMAP	ALL	{ user_addr_t mmap(caddr_ut addr, size_ut len, int prot, int flags, int fd, off_t pos) NO_SYSCALL_STUB; }
//from xnu repo
/*args for 197 :
ALL = architectures supported.
*/
//compilemsg
// gcc -Wno-deprecated-declarations mymalloc.c -o malloc
//

int main(){
    char content[100];
    printf("Enter something meaningful (or not) to be stored in memory: ");
    scanf("%s", content);

    printf("Enter the length (in bytes) of the desired memory partition:\n");
    size_t size =  24 + strlen(content);
    int prot = 0x1 | 0x2;
    int flags = -1;
    int fd = -1;
    int offset = 0;
    mallocAndPrint(size, prot, flags, fd, offset, content);



}


void *mallocAndPrint(size_t myLength, int prot, int flags, int fileDescriptor, int myOffset, char *message){

void *ptr =  (void *) syscall(197,NULL, myLength,prot, flags, fileDescriptor, myOffset); //used syscal 197 to allocate enough memory for string inputted by user
char hMessage[] = "Hello from Memory!\n";
char *tptr = (char *)ptr;
int hLen = strlen(hMessage);
int mLen = strlen(message);
for (int i = 0; i < hLen; i++) {
    tptr[i] = hMessage[i];
}
for (int i = 0; i < mLen; i++) {
    tptr[hLen + i] = message[i];
}
tptr[hLen + mLen] = '\0';


printf("%s", tptr);
}



