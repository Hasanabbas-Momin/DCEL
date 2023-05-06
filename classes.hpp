#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.hpp"
using namespace std;
class halfEdge;
class face;

class vertex
{
public:
    int vertexIndex;
    int x;
    int y;
};

class halfEdge
{
public:
    int edgeIndex;
    halfEdge *nextEdge;
    halfEdge *prevEdge;
    vertex *nextVertex;
    vertex *prevVertex;
    int faceIndex;
    halfEdge *twinEdge;
};

class face
{
public:
    face *prevFace;
    halfEdge *edgeHead;
    int faceIndex;
    face *nextFace;
};