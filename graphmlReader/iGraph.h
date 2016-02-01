#pragma once
#include "stdafx.h"

#ifdef THROW_EXCEPTION
#define THROW throw
#else
#define THROW //
#endif

class INode
{
public:
	INode();
	virtual ~INode();

	INode(const char *id, void *data);

	virtual void SetData(void *data)
	{
		this->m_data = data;
	}
	virtual void* GetData()
	{
		return m_data;
	}
	const char* GetId()
	{
		return m_id;
	}

	void AddVertex(INode *nodeDst);

	bool IsAdjacent(const char *id);

	std::list<INode*>& GetAdjList()
	{
		return ConnectedNodes;
	}

#ifdef _DEBUG
	void PrintConnectedNode();
#endif

private:
	const char *m_id;
	void* m_data;

	// list of connected nodes
	// direction is from this to each connected nodes
	std::list<INode*> ConnectedNodes;
};

typedef std::unordered_map<const char*, INode*> GraphListMap;

class IGraph
{
public:
	IGraph();
	~IGraph();

	void AddVertex(const char *idSrc, const char *idDst);
	void AddGraphNode(const char *id, void *data);

	INode* GetGraphNode(const char *id);

	int GetNodeCount()
	{
		return m_nodesList.size();
	}

#ifdef _DEBUG
	void printGraph();
#endif
public:
	// this is where nodes take place
	GraphListMap m_nodesList;
};