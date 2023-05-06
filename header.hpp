#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;
class halfEdge;
class face;
class vertex;

void printEdges(FILE *f, face *faceHead, int edges);
void printHalfEdges(FILE *f, face *faceHead);
void printFace(FILE *f, face *faceHead);
void twinedge(halfEdge *edge, int edges, face *newFace);
void updateTwinEdge1(halfEdge *edge, halfEdge *splittedEdge);
void updateTwinEdge2(halfEdge *edge, halfEdge *splittedEdge);
bool parity(vertex *prevVertex, vertex *nextVertex, int x0, int y0, int x, int y);
face *pointLocation(face *faceHead, int x, int y);