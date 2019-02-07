#include <iostream>
#include "string.h"
#include "memory.h"

using namespace std;

/* ---------------------------------------------------------------------- */

Memory::Memory(MPM *mpm) : Pointers(mpm) {}

/* ----------------------------------------------------------------------
   safe malloc
------------------------------------------------------------------------- */

void *Memory::smalloc(bigint nbytes, string name)
{
  if (nbytes == 0) return NULL;

#if defined(MPM_MEMALIGN)
  void *ptr;
  int retval = posix_memalign(&ptr, MPM_MEMALIGN, nbytes);
  if (retval) ptr = NULL;
#else
  void *ptr = malloc(nbytes);
#endif
  if (ptr == NULL) {
    char str[128];
    cout << "Failed to allocate " << nbytes << " bytes for array " << name << endl;
    exit(1);
  }
  return ptr;
}

/* ----------------------------------------------------------------------
   safe realloc
------------------------------------------------------------------------- */

void *Memory::srealloc(void *ptr, bigint nbytes, string name)
{
  if (nbytes == 0) {
    destroy(ptr);
    return NULL;
  }

  ptr = realloc(ptr,nbytes);
  if (ptr == NULL) {
    char str[128];
    cout << "Failed to allocate " << nbytes << " bytes for array " << name << endl;
    exit(1);
  }
  return ptr;
}

/* ----------------------------------------------------------------------
   safe free
------------------------------------------------------------------------- */

void Memory::sfree(void *ptr)
{
  if (ptr == NULL) return;
  free(ptr);
}

/* ----------------------------------------------------------------------
   erroneous usage of templated create/grow functions
------------------------------------------------------------------------- */

void Memory::fail(string name)
{
  char str[128];
  cout << "Cannot create/grow a vector/array of pointers for " << name << endl;
  exit(1);
}