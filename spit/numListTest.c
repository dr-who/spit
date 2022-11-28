
#include "numList.h"
#include <assert.h>
#include <stdio.h>

void test1(numListType *nl) {
  nlInit(nl, 1);
  assert(nlN(nl) == 0);
  assert(nlMean(nl) == 0);
  assert(nlMedian(nl) == 0);
  
  nlAdd(nl, 1);
  assert(nlN(nl) == 1);
  assert(nlMean(nl) == 1);
  assert(nlMedian(nl) == 1);
  
  nlAdd(nl, 3);
  assert(nlN(nl) == 1);
  assert(nlMean(nl) == 3);
  assert(nlMedian(nl) == 3);

  nlFree(nl);

  nlInit(nl, 10);
  assert(nlN(nl) == 0);
  assert(nlMean(nl) == 0);
  assert(nlMedian(nl) == 0);

  nlAdd(nl, 1);
  nlAdd(nl, 2);
  nlAdd(nl, 5);
  assert(nlN(nl) == 3);
  assert(nlMean(nl) == (1+2+5)/3.0);
  assert(nlMedian(nl) == 2);

  nlClear(nl);
  assert(nlN(nl) == 0);
  assert(nlMean(nl) == 0);
  assert(nlMedian(nl) == 0);

    nlAdd(nl, 1);
  nlAdd(nl, 2);
  nlAdd(nl, 5);
  assert(nlN(nl) == 3);
  assert(nlMean(nl) == (1+2+5)/3.0);
  assert(nlMedian(nl) == 2);
  nlFree(nl);

  assert(nlN(nl) == 0);
  assert(nlMean(nl) == 0);
  assert(nlMedian(nl) == 0);

}

void test2(numListType *nl) {
  nlInit(nl, 4);
  nlAdd(nl, 4);
  nlAdd(nl, 3);
  nlAdd(nl, 1);
  nlAdd(nl, 2);
  assert(nlN(nl) == 4);
  assert(nlMean(nl) == (1+2+3+4)/4.0);
  assert(nlMin(nl) == 1);
  assert(nlMax(nl) == 4);
  assert(isnan(nlMode(nl, 360, 1)));


  nlAdd(nl, 4);
  assert(nlN(nl) == 4);
  assert(nlMean(nl) == (4+3+2+1)/4.0);
  assert(nlMin(nl) == 1);
  assert(nlMax(nl) == 4);
  assert(isnan(nlMode(nl, 360, 1)));

  nlAdd(nl, 4);
  assert(nlN(nl) == 4);
  assert(nlMean(nl) == (4+4+1+2)/4.0);
  assert(nlMin(nl) == 1);
  assert(nlMax(nl) == 4);
  assert(4==nlMode(nl, 360, 1));

  nlAdd(nl, 4);
  assert(nlN(nl) == 4);
  assert(nlMean(nl) == (4+4+4+2)/4.0);
  assert(nlMin(nl) == 2);
  assert(nlMax(nl) == 4);
  assert(4==nlMode(nl, 360, 1));

}

void test3(numListType *nl) {
  nlInit(nl, 5);
  assert(nlN(nl) == 0);
  nlAdd(nl, 1);
  nlAdd(nl, 3);
  nlAdd(nl, 2);
  nlAdd(nl, 4);
  nlAdd(nl, 5);
  assert(nlSortedPos(nl, 0) == 1);
  assert(nlSortedPos(nl, -1) == 5);
  assert(nlSortedPos(nl, 0.5) == 3);
  assert(nlSortedPos(nl, 1) == 2);
  assert(nlSortedPos(nl, 4) == 5);
  assert(nlSortedPos(nl, 0.25) == 2); 
  assert(nlSortedPos(nl, 0.5) == 3); 
  assert(nlSortedPos(nl, 0.75) == 4); 
}


void test4even(numListType *nl) {
  nlInit(nl, 10);
  assert(nlMin(nl) == 0);
  assert(nlMedian(nl) == 0);

  nlAdd(nl, -1);
  assert(nlMedian(nl) == -1);
  nlAdd(nl, 3);
  assert(nlMedian(nl) == 1);
  nlAdd(nl, 4);
  assert(nlMedian(nl) == 3);
  assert(nlMin(nl) == -1);
  assert(nlMax(nl) == 4);
}

int main() {
  numListType nl;

  test1(&nl);
  test2(&nl);
  test3(&nl);
  test4even(&nl);

  return 0;
}

  