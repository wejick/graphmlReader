#include "stdafx.h"
#include "iGraph.h"

INode::INode()
{
	m_data = NULL;
}

INode::~INode()
{
	SAFE_DEL(m_data);
}

INode::INode(const char *id, void *data)
{
	this->m_id = id;
	this->m_data = data;
}

void INode::AddVertex(INode *nodeDst)
{
	// find for duplicated destination
	std::list<INode*>::iterator itINode;
	for (itINode = ConnectedNodes.begin(); itINode != ConnectedNodes.end(); itINode++)
	{
		const char * foundId = (*itINode)->m_id;
		if (strcmp(foundId, nodeDst->m_id) == 0)
		{
			// found duplicated destination
#ifdef _DEBUG
			printf("Duplicated destination Found %s\n", foundId);
#endif //_DEBUG
			THROW std::logic_error("Duplicated destination found");
			return;
		}
	}
	ConnectedNodes.push_back(nodeDst);
}

bool INode::IsAdjacent(const char *id)
{
	std::list<INode*>::iterator itINode;
	for (itINode = ConnectedNodes.begin(); itINode != ConnectedNodes.end(); itINode++)
	{
		const char * foundId = (*itINode)->m_id;
		if (strcmp(foundId, id) == 0)
		{
			return true;
		}
	}
	return false;
}

#ifdef _DEBUG
void INode::PrintConnectedNode()
{
	std::list<INode*>::iterator itConnectedNode;
	for (itConnectedNode = ConnectedNodes.begin(); itConnectedNode != ConnectedNodes.end(); itConnectedNode++)
	{
		printf("=> %s ", (*itConnectedNode)->GetId());
	}
	printf("\n");
}
#endif //_DEBUG

IGraph::IGraph()
{
}

IGraph::~IGraph()
{
	GraphListMap::iterator itNodeList;
	for (itNodeList = m_nodesList.begin(); itNodeList != m_nodesList.end(); itNodeList++)
	{
		SAFE_DEL((*itNodeList).second);
	}
}

void IGraph::AddVertex(const char *idSrc, const char* idDst)
{
	if (m_nodesList[idSrc])
	{
		m_nodesList[idSrc]->AddVertex(m_nodesList[idDst]);
	}
}

void IGraph::AddGraphNode(const char *id, void *data)
{
	if (!m_nodesList[id])
	{
		INode *newNode = new INode(id, data);
		m_nodesList[id] = newNode;
	}
	else
	{
#ifdef _DEBUG
		printf("Duplicated Node Found %s \n", id);
#endif //_DEBUG
		THROW std::logic_error("Duplicated Node Found");
	}
}

INode* IGraph::GetGraphNode(const char *id)
{
	return m_nodesList[id];
}

#ifdef _DEBUG
void IGraph::printGraph()
{
	GraphListMap::iterator itNodeList;
	for (itNodeList = m_nodesList.begin(); itNodeList != m_nodesList.end(); itNodeList++)
	{
		printf("Graph Name : %s ", (*itNodeList).first);
		(*itNodeList).second->PrintConnectedNode();
	}
}
#endif //_DEBUG