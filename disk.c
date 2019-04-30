#include "disk.h"

disk_t disk;

int log2phys(int logaddr, physaddr_t *phaddr)
{
    // TODO: implement
    if (logaddr> MAX_LOGICAL_SECTOR || logaddr < 0){
        printf("invalid logical address");
        return WRONGLOGICALSEC;
    }
    phaddr->cyl = logaddr/(SECT_SIZE);
    phaddr->head = (logaddr%(SECT_SIZE))/NUM_OF_SECTS;
    phaddr->sect = ((logaddr%(SECT_SIZE))%NUM_OF_SECTS + 1);

    return 0;
}

int phys2log(physaddr_t *phaddr)
{
    // TODO: implement
    //(C x TH x TS) + (H x TS) + (S - 1) = LBA
    int logAddr = (phaddr->cyl * NUM_OF_HEADS * NUM_OF_SECTS) + (phaddr->head * NUM_OF_SECTS) + (phaddr->sect -1);
    return logAddr;
}

void printTransl(int logaddr)
{
    physaddr_t phaddr;

    printf("Logical sector number: %d\n", logaddr);
    if (log2phys(logaddr, &phaddr) == 0)
    {
        printf("Physical address: (%d, %d, %d)\n", phaddr.cyl, phaddr.head, phaddr.sect);

        if (phys2log(&phaddr) != logaddr)
            printf("ERROR: no match!\n");
    } else
        printf("ERROR: invalid logical address!\n");
}

int readDisk(int logical_block_num, int numOfBlocks, void **buffer)
{
    // TODO: implement
    char* strcppy = malloc(numOfBlocks* sizeof(char) * SECT_SIZE);

    return 0;
}

int writeDisk(int logicalBlockNum, int numOfSectors, void *buffer)
{
    // TODO: implement

    return 0;
}

int main(int argc, char *argv[])
{
    // TODO: extend to also test for reading and writing
    
    physaddr_t phaddr;

    char buf[8 * SECT_SIZE];

    int logaddr;

    if (argc < 2)
        while (1)
        {
            logaddr = rand() % MAX_LOGICAL_SECTOR;
            printTransl(logaddr);
            switch (rand() % 2)
            {
                case 0:
                    readDisk(logaddr, rand() % 8, (void *) &buf);
                    break;
                case 1:
                    writeDisk(logaddr, rand() % 8, buf);
                    break;
            }
            usleep(10);
        }

    switch (argv[1][0]) // "l" for logical "p" for physical
    {
        case 'l': // logical
            if (argv[2] == NULL)
                break;
            logaddr = strtol(argv[2], NULL, 10) % MAX_LOGICAL_SECTOR;
            printTransl(logaddr);
            break;

        case 'p': // physical
            if (argv[2] == NULL || argv[3] == NULL || argv[4] == NULL)
                break;
            phaddr.cyl = strtol(argv[2], NULL, 10);
            phaddr.head = strtol(argv[3], NULL, 10);
            phaddr.sect = strtol(argv[4], NULL, 10);
            logaddr = phys2log(&phaddr);
            printTransl(logaddr);
            break;
    }
}