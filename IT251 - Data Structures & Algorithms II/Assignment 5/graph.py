class Node:
    def __init__(self, idx, data=0):
        """
        Node class represents a vertex/node in the graph.

        Parameters:
        idx (int): ID of the node.
        data (int, optional): Data associated with the node. Defaults to 0.
        """
        self.id = idx
        self.data = data
        self.connectedTo = dict()

    def addNeighbour(self, neighbour, weight=0):
        """
        Adds the neighbour_id : weight pair into the dictionary of the current node.

        Parameters:
        neighbour (Node): The neighbour node.
        weight (int, optional): Weight of the edge connecting the current node to the neighbour node. Defaults to 0.
        """
        if neighbour.id not in self.connectedTo.keys():
            self.connectedTo[neighbour.id] = weight

    def setData(self, data):
        """
        Sets the data associated with the node.

        Parameters:
        data (int): Data to be associated with the node.
        """
        self.data = data

    def getConnections(self):
        """
        Returns the IDs of all the neighbours of the node.

        Returns:
        dict_keys: IDs of all the neighbours of the node.
        """
        return self.connectedTo.keys()

    def getID(self):
        """
        Returns the ID of the node.

        Returns:
        int: ID of the node.
        """
        return self.id

    def getData(self):
        """
        Returns the data associated with the node.

        Returns:
        int: Data associated with the node.
        """
        return self.data

    def getWeight(self, neighbour):
        """
        Returns the weight of the edge connecting the current node to the neighbour node.

        Parameters:
        neighbour (Node): The neighbour node.

        Returns:
        int: Weight of the edge connecting the current node to the neighbour node.
        """
        return self.connectedTo[neighbour.id]

    def __str__(self):
        """
        Returns a string representation of the node.

        Returns:
        str: String representation of the node.
        """
        return str(self.data) + " Connected to : " + str([x.data for x in self.connectedTo])

class Graph:

    totalV = 0  # total vertices in the graph

    def __init__(self):
        """
        allNodes: Dictionary (key:value)
                  idx: Node Object
        """
        self.allNodes = dict()

    def addNode(self, idx):
        """ 
        Adds a node to the graph.

        Parameters:
        idx (int): The ID of the node.

        Returns:
        node (Node Object): The created node.
        """
        if idx in self.allNodes:
            return None
        
        Graph.totalV += 1
        node = Node(idx=idx)
        self.allNodes[idx] = node
        return node

    def addNodeData(self, idx, data):
        """
        Sets the data of a node in the graph.

        Parameters:
        idx (int): The ID of the node.
        data (any): The data to be set.

        Returns:
        None
        """
        if idx in self.allNodes:
            node = self.allNodes[idx]
            node.setData(data)
        else:
            print("No ID to add the data.")

    def addEdge(self, src, dst, wt=0):
        """
        Adds an edge between two nodes in the graph.

        Parameters:
        src (int): The ID of the node where the edge starts from.
        dst (int): The ID of the node where the edge ends.
        wt (int, optional): The weight of the edge. Default value is 0.

        Returns:
        None
        """
        self.allNodes[src].addNeighbour(self.allNodes[dst], wt)
        self.allNodes[dst].addNeighbour(self.allNodes[src], wt)

    def isNeighbour(self, u, v):
        """
        Checks if there is an edge between two nodes in the graph.

        Parameters:
        u (int): The ID of the first node.
        v (int): The ID of the second node.

        Returns:
        True if there is an edge between the two nodes, False otherwise.
        """
        if u >= 1 and u <= 256 and v >= 1 and v <= 256 and u != v:
            if v in self.allNodes[u].getConnections():
                return True
        return False

    def printEdges(self):
        """ 
        Prints all the edges in the graph.

        Parameters:
        None

        Returns:
        None
        """
        for idx in self.allNodes:
            node = self.allNodes[idx]
            for con in node.getConnections():
                print(node.getID(), " --> ", self.allNodes[con].getID())

    def getNode(self, idx):
        """
        Gets the node with the specified ID in the graph.

        Parameters:
        idx (int): The ID of the node.

        Returns:
        The node with the specified ID, or None if it doesn't exist.
        """
        if idx in self.allNodes:
            return self.allNodes[idx]
        return None

    def getAllNodesIds(self):
        """
        Gets the IDs of all the nodes in the graph.

        Parameters:
        None

        Returns:
        A list of all the IDs of the nodes in the graph.
        """
        return self.allNodes.keys()
