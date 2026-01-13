#include <unistd.h> // Needed for sleep function
#include <stdlib.h> // Needed for malloc function
#include <stdio.h> // Needed for printf

int main(int argc, char** argv) {
  void* ptr = malloc(1024); // 힙에서 1KB 할당하기
  printf("Address: %p\n", ptr);
  fflush(stdout); // 강제로 출력하기
  // Infinite loop
  while (1) {
    sleep(1); // Sleep 1 second
  };
  return 0;
}