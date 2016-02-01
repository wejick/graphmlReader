// graphmlReader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "pugixml.hpp"

#include "iGraph.h"

int main(int argc, char *argv[])
{
	{
		IGraph graf1;

		graf1.AddGraphNode("Graf1", NULL);
		graf1.AddGraphNode("Graf2", NULL);
		graf1.AddGraphNode("Graf3", NULL);

		graf1.AddVertex("Graf1", "Graf2");
		graf1.AddVertex("Graf2", "Graf3");
		graf1.AddVertex("Graf1", "Graf3");
		graf1.AddVertex("Graf1", "Graf3");

		if (graf1.GetGraphNode("Graf1")->IsAdjacent("Graf3"))
		{
			printf("Adjacent \n");
		}

#ifdef _DEBUG
		graf1.printGraph();
#endif
	}
	return 0;
}