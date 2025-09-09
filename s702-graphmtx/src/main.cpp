#include "graphmtx.hpp"

int main(int argc, char *argv[]) {
  GraphMtx gm;
  InitGraph(&gm);
  InsertVertex(&gm, 'A');
  InsertVertex(&gm, 'B');
  InsertVertex(&gm, 'C');
  InsertVertex(&gm, 'D');
  InsertVertex(&gm, 'E');

  InsertEdge(&gm, 'A', 'B');
  InsertEdge(&gm, 'A', 'D');
  InsertEdge(&gm, 'B', 'C');
  InsertEdge(&gm, 'B', 'E');
  InsertEdge(&gm, 'C', 'E');
  InsertEdge(&gm, 'C', 'D');
  ShowGraph(&gm);

  // RemoveEdge(&gm, 'B', 'C');
  // ShowGraph(&gm);

  // RemoveVerTices(&gm, 'C');
  // ShowGraph(&gm);

  int pos = GetFirstNeighbor(&gm, 'A');
  printf("\nFirst Neigbor pos = %d\n", pos);

  ShowGraph(&gm);
  pos = GetNextNeighbor(&gm, 'C', 'D');
  printf("'C','D',Next Neigbor pos = %d\n", pos);

  DestroyGraph(&gm);
  return 0;
}
