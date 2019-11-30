#include "heap.h"
typedef struct _mm_sdram_struct 
{
	struct _mm_sdram_struct *next;			// Point to next management entry of linking list
	uint32_t *end;							// Point to the last word(4 bytes) of allocated memory
} MM_SDRAM_STRUCT, *P_MM_SDRAM_STRUCT;

#define USER_HEAP_SIZE		20480		// 20K

static uint32_t fst_heap_memory[USER_HEAP_SIZE/sizeof(uint32_t)]; 

static MM_SDRAM_STRUCT *VT_mm_sdram_head;
static uint32_t VT_free_sdram_start;
static uint32_t VT_free_sdram_end;


void enable_mm(void)
{
	mm_init((uint32_t)fst_heap_memory, sizeof(fst_heap_memory));
}

void disable_mm(void)
{

}

void reset_mm(void)
{
	disable_mm();
	enable_mm();
}

void check_mm(void)
{
	if (VT_mm_sdram_head->next->next) {

	}
}

void mm_init(uint32_t free_memory_start, uint32_t size)
{
	// Initate management structure for variable size free SDRAM

	VT_free_sdram_start = (free_memory_start + 3) & (~0x3);		// Align to 4-bytes boundary
	VT_free_sdram_end = free_memory_start + size;
	VT_free_sdram_end = VT_free_sdram_end & (~0x3);				// Align to 4-bytes boundary

	if ( (VT_free_sdram_end - VT_free_sdram_start) <= sizeof(MM_SDRAM_STRUCT))
	{
//		ASSERT(0, 0);
		return;
	}
	if (VT_mm_sdram_head != NULL)
	{
//		ASSERT(VT_mm_sdram_head->next->next == NULL, 0);
	}
	
    VT_mm_sdram_head = (MM_SDRAM_STRUCT *) VT_free_sdram_start;
    VT_mm_sdram_head->end = (uint32_t *) &VT_mm_sdram_head->end;
    VT_mm_sdram_head->next = (MM_SDRAM_STRUCT *) VT_free_sdram_end - 1;
    VT_mm_sdram_head->next->next = NULL;
	return;
}


void * malloc_align(uint32_t size, uint32_t align)
{
    MM_SDRAM_STRUCT *pmm;
    uint32_t new_head_addr;
    uint32_t new_data_addr;

	if (!size) {
    	return (NULL);
    }
    pmm = VT_mm_sdram_head;
    size = (size+3) >> 2;
	if (align & (align-1)) {				// align value must be power of 2, eg: 2, 4, 8, 16, 32...
		align = 1;
	}

  #if _OPERATING_SYSTEM != _OS_NONE
    OSSchedLock();
  #endif
    while (pmm->next) {
    	new_data_addr = (((uint32_t) (pmm->end+1))+sizeof(MM_SDRAM_STRUCT)+(align-1)) & ~(align-1);
        if (new_data_addr >= (uint32_t) pmm->next) {
        	pmm=pmm->next;
        } else if (((uint32_t *) pmm->next - (uint32_t *) new_data_addr) > size) {
        	new_head_addr = new_data_addr - sizeof(MM_SDRAM_STRUCT);
            ((MM_SDRAM_STRUCT *) new_head_addr)->next = pmm->next;
            ((MM_SDRAM_STRUCT *) new_head_addr)->end = (uint32_t *) (new_data_addr + (size<<2)) - 1;
            pmm->next = (MM_SDRAM_STRUCT *) new_head_addr;
		  #if _OPERATING_SYSTEM != _OS_NONE
            OSSchedUnlock();
          #endif
            return ((void *) new_data_addr);
        } else {
            pmm=pmm->next;
        }
    }
  #if _OPERATING_SYSTEM != _OS_NONE
    OSSchedUnlock();
  #endif
    return (NULL);
}

void * kv_malloc(uint32_t size)
{
	MM_SDRAM_STRUCT *pmm = VT_mm_sdram_head;

	if (!size) {
    	return (NULL);
    }

    size = (size+3) >> 2;

  #if _OPERATING_SYSTEM != _OS_NONE
    OSSchedLock();
  #endif
    while (pmm->next) {
        if (((uint32_t *) pmm->next - (uint32_t *) pmm->end) > size+2) {
            ((MM_SDRAM_STRUCT *) (pmm->end+1))->next = pmm->next;
            pmm->next = (MM_SDRAM_STRUCT *) (pmm->end+1);
            pmm->next->end = (uint32_t *) &pmm->next->end + size;
		  #if _OPERATING_SYSTEM != _OS_NONE
            OSSchedUnlock();
          #endif
            return ((uint32_t *) &pmm->next->end + 1);
        }

        pmm=pmm->next;
    }
  #if _OPERATING_SYSTEM != _OS_NONE
    OSSchedUnlock();
  #endif
    return (NULL);
}

void kv_free(void *ptr)
{
    MM_SDRAM_STRUCT *pmm = VT_mm_sdram_head;
    
    if ((uint32_t) ptr < VT_free_sdram_start)
	{
//		ASSERT(0, 0);
	}
    if ((uint32_t) ptr > VT_free_sdram_end)   
    {
//    	ASSERT(0, 0);
    	return;
    }

  #if _OPERATING_SYSTEM != _OS_NONE
    OSSchedLock();
  #endif
    while (pmm->next) {
        if ((uint32_t *) pmm->next+2 == ptr) {
            // Merge previous free memory with this one
            pmm->next = pmm->next->next;
          #if _OPERATING_SYSTEM != _OS_NONE
            OSSchedUnlock();
          #endif
            return;
        }
        pmm = pmm->next;
    }
    // Something must be wrong...
  #if _OPERATING_SYSTEM != _OS_NONE
    OSSchedUnlock();
  #endif
//	ASSERT(0, 0);
  return;
}


