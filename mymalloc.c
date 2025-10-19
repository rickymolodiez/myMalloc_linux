#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <string.h>

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
    int sizeM;
    printf("Enter the length (in bytes) of the desired memory partition:\n");
    scanf("%d", &sizeM);
    size_t size =  (size_t) sizeM + strlen(content);
    int prot = 0x1 | 0x2;
    int flags = -1;
    int fd = -1;
    int offset = 0;
    mallocAndPrint(size, prot, flags, fd, offset, content);

return 0;

}


void *mallocAndPrint(size_t myLength, int prot, int flags, int fileDescriptor, int myOffset, char *message){

long result = syscall(197,NULL, myLength ,prot, flags, fileDescriptor, myOffset); //used syscal 197 to allocate enough memory for string inputted by user
void *ptr = (void *) result;
if (ptr == (void *)-1) {
        perror("syscall mmap failed");
        return NULL;
    }
const char hMessage[20] = "Hello from Memory!\n";


return 0;

}



