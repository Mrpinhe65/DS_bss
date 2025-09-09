#include "graphlink.hpp"

int main(int argc, char *argv[]) {
  GraphLink gl;
  InitGraph(&gl);

  InsertVertex(&gl, 'A');
  InsertVertex(&gl, 'B');
  InsertVertex(&gl, 'C');
  InsertVertex(&gl, 'D');
  InsertVertex(&gl, 'E');

  InsertEdge(&gl, 'A', 'B');
  InsertEdge(&gl, 'A', 'D');
  InsertEdge(&gl, 'B', 'C');
  InsertEdge(&gl, 'B', 'E');
  InsertEdge(&gl, 'C', 'D');
  InsertEdge(&gl, 'C', 'E');

  ShowGraphLink(&gl);

  // RemoveEdge(&gl, 'B', 'C');
  // printf("RemoveVertex\n");
  // RemoveVertex(&gl, 'C');
  // printf("remove\n");
  // ShowGraphLink(&gl);
  // int post = GetFirstNeighbor(&gl, 'A');
  // int post = GetNextNeighbor(&gl, 'B', 'E');
  // int post = GetNextNeighbor(&gl, 'B', 'C');
  int post = GetNextNeighbor(&gl, 'B', 'A');
  printf("post = %d[%c]\n", post, gl.NodeTable[post].data);
  Destroy(&gl);
  return 0;
}
