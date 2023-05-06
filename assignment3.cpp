#include <bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"header.hpp"
#include "classes.hpp"
using namespace std;
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
int main(int argc, char *argv[])
{
    // below variables keeps track of vertices, edges and faces created so far
    int vertices = 0, edges = 0, faces = 0;
    ifstream iFile(argv[1]);

    // create object faceHead of class face
    face *faceHead = new face();
    faces++;
    faceHead->faceIndex = 0;

    // created object of class halfEdge and initialize class variables
    halfEdge *currentEdge = new halfEdge();
    edges++;
    faceHead->edgeHead = currentEdge;
    currentEdge->edgeIndex = edges - 1;
    currentEdge->faceIndex = faceHead->faceIndex;

    // loop which will iterate over input in the file
    while (!iFile.eof())
    {
        // create object of class vertex and give it the coordinate obtained from the file
        vertex *newVertex = new vertex();
        vertices++;
        iFile >> newVertex->x;
        iFile >> newVertex->y;
        newVertex->vertexIndex = vertices - 1;
        // create object of class halfEdge and initialize its class variables
        halfEdge *newEdge = new halfEdge();
        edges++;
        // updating class variables
        currentEdge->nextEdge = newEdge;
        if (currentEdge->prevEdge != NULL)
            currentEdge->prevEdge->nextVertex = newVertex;
        currentEdge->prevVertex = newVertex;
        newEdge->edgeIndex = edges - 1;
        newEdge->faceIndex = currentEdge->faceIndex;
        newEdge->prevEdge = currentEdge;

        currentEdge = newEdge;
    }

    currentEdge = currentEdge->prevEdge;
    delete currentEdge->nextEdge;
    edges--;
    currentEdge->nextEdge = faceHead->edgeHead;
    currentEdge->nextVertex = faceHead->edgeHead->prevVertex;
    faceHead->edgeHead->prevEdge = currentEdge;

    FILE *f = fopen(argv[3], "wt");
    fprintf(f, "Faces:\n");
    printEdges(f, faceHead, edges);
    fprintf(f, "Halfedges:\n");
    printHalfEdges(f, faceHead);
    fprintf(f, "Faces:\n");
    printFace(f, faceHead);

    ifstream iFile2(argv[2]);
    string split;
    iFile2 >> split;
    face *tempFace, *endFace = faceHead;
    halfEdge *tempEdge;
    while (split == "Split")
    {
        face *newFace = endFace->nextFace = new face();
        faces++;
        newFace->prevFace = endFace;
        endFace = newFace;
        newFace->faceIndex = faces - 1;
        int a, b;
        iFile2 >> a >> b;

        halfEdge *startEdge, *endEdge, *newEdge = new halfEdge();
        edges++;
        tempFace = faceHead;
        while (tempFace->nextFace != NULL)
        {
            currentEdge = faceHead->edgeHead;
            tempFace->nextFace;
            do
            {
                if (currentEdge->edgeIndex == a)
                    startEdge = currentEdge;
                if (currentEdge->edgeIndex == b)
                    endEdge = currentEdge;
                currentEdge = currentEdge->nextEdge;
            } while (currentEdge != faceHead->edgeHead);
            tempFace = tempFace->nextFace;
        }
        vertex *startVertex = new vertex();
        vertices++;
        startVertex->vertexIndex = vertices - 1;
        vertex *endVertex = new vertex();
        vertices++;
        endVertex->vertexIndex = vertices - 1;
        startVertex->x = (startEdge->prevVertex->x + startEdge->nextVertex->x) / 2;
        startVertex->y = (startEdge->prevVertex->y + startEdge->nextVertex->y) / 2;

        endVertex->x = (endEdge->prevVertex->x + endEdge->nextVertex->x) / 2;
        endVertex->y = (endEdge->prevVertex->y + endEdge->nextVertex->y) / 2;

        newEdge->edgeIndex = edges - 1;
        newEdge->faceIndex = startEdge->faceIndex;
        newEdge->nextEdge = endEdge;
        newEdge->nextVertex = endVertex;
        newEdge->prevEdge = startEdge;
        newEdge->prevVertex = startVertex;

        halfEdge *nextNewEdge = new halfEdge();
        halfEdge *prevNewEdge = new halfEdge();
        twinedge(newEdge, edges, newFace);
        faceHead->edgeHead = newEdge;
        edges++;
        nextNewEdge->edgeIndex = edges - 1;
        nextNewEdge->faceIndex = newFace->faceIndex;
        nextNewEdge->nextVertex = startEdge->nextVertex;
        nextNewEdge->prevVertex = startVertex;
        nextNewEdge->prevEdge = newEdge->twinEdge;
        edges++;
        prevNewEdge->edgeIndex = edges - 1;
        prevNewEdge->faceIndex = newFace->faceIndex;
        prevNewEdge->nextVertex = endVertex;
        prevNewEdge->prevVertex = endEdge->prevVertex;
        prevNewEdge->nextEdge = newEdge->twinEdge;

        if (startEdge->nextEdge == endEdge)
        {
            nextNewEdge->nextEdge = prevNewEdge;
            prevNewEdge->prevEdge = nextNewEdge;
        }
        else
        {
            nextNewEdge->nextEdge = startEdge->nextEdge;
            startEdge->nextEdge->prevEdge = nextNewEdge;
            prevNewEdge->prevEdge = endEdge->prevEdge;
            endEdge->prevEdge->nextEdge = prevNewEdge;
            // to update the facee index of edges between nextNewEdge and prevNewEdge
            tempEdge = nextNewEdge->nextEdge;
            while (tempEdge != prevNewEdge)
            {
                tempEdge->faceIndex = nextNewEdge->faceIndex;
                tempEdge = tempEdge->nextEdge;
            }
        }

        newEdge->twinEdge->nextEdge = nextNewEdge;
        newEdge->twinEdge->prevEdge = prevNewEdge;

        startEdge->nextEdge = newEdge;
        startEdge->nextVertex = startVertex;

        endEdge->prevEdge = newEdge;
        endEdge->prevVertex = endVertex;

        if (newEdge->prevEdge->twinEdge != NULL)
            updateTwinEdge1(newEdge->prevEdge->twinEdge, newEdge->twinEdge->nextEdge);
        if (newEdge->nextEdge->twinEdge != NULL)
            updateTwinEdge2(newEdge->nextEdge->twinEdge, newEdge->twinEdge->prevEdge);

        fprintf(f, "\n//After split %d %d\n \n", a, b);
        tempFace = faceHead;
        fprintf(f, "Edges:\n");
        printEdges(f, tempFace, edges);

        tempFace = faceHead;
        fprintf(f, "Halfedges:\n");
        do
        {
            printHalfEdges(f, tempFace);
            tempFace = tempFace->nextFace;
        } while (tempFace != NULL);
        tempFace = faceHead;
        fprintf(f, "Faces:\n");
        do
        {
            printFace(f, tempFace);
            tempFace = tempFace->nextFace;
        } while (tempFace != NULL);
        if (iFile2.eof())
            break;
        iFile2 >> split;
    }
    int id = 1;
    while (!iFile2.eof())
    {
        int x, y;
        iFile2 >> x;
        iFile2 >> y;
        face *Face = pointLocation(faceHead, x, y);
        fprintf(f, "\n%d %d", id, Face->faceIndex);
        id++;
        if (iFile2.eof())
            break;
        iFile2 >> split;
    }
    fclose(f); // should be shifted below
}