#include "sharedArray.h"

int main() {

  sa_init();
  
  shared_array a = sa_create("shm://test", 10, SA_FLOAT);

  shared_array b = sa_attach("shm://test");

  sa_list();

  //sa_delete("shm://test");

  sa_setFloat(a,10,12.45);

  float value = sa_getFloat(a,10);
  
  printf("%f\n",value);
  
  sa_list();
}
