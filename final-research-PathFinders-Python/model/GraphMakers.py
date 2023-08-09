import model.Graph as Graph
import model.Node as Node
import model_rows.GraphRC as GraphRC
import model_rows.NodeRC as NodeRC
import csv



def read_file(filename):
    try:
        with open(filename, 'rb') as f:
            content = f.read().decode('utf-8')
        return content
    except FileNotFoundError:
        print("Error opening file")
        return None


def graph_from_string(vertices, distances):
    graph = Graph.Graph()

    vertices_lines = vertices.split('\n')
    for vertex in vertices_lines:
        ascii_values = 0
        if vertex:
            for char in vertex:
                ascii_values += ord(char)
            graph.add_node(Node.Node(vertex, ascii_values, ascii_values))

    distances_lines = distances.split('\n')
    for line in distances_lines:
        if line:
            source, destination, weight = line.split()
            weight = int(weight)
            source_node = graph.get_node_via_name(source)
            destination_node = graph.get_node_via_name(destination)
            graph.set_edge_weighted(source_node, destination_node, weight)

    return graph


def graph_from_file(filename):
    content = read_file(filename)
    if content:
        vertices, distances = content.split('\n\n')
        return graph_from_string(vertices, distances)
    else:
        return None


def graph_from_csv(filename, total_rows):
    try:
        with open(filename, 'r') as f:
            reader = csv.DictReader(f)
            graph = GraphRC.GraphRC()

            # create all the nodes first
            for row in reader:
                cell = row['  cell  '].strip('"')

                maze_row = cell[1]
                maze_column = cell[4]
                node = NodeRC.NodeRC(cell, int(maze_row), int(maze_column))
                graph.add_node(node)

            f.seek(0)
            next(reader)
            for row in reader:
                cell = row['  cell  '].strip('"')
                east = int(row['E'])
                west = int(row['W'])
                north = int(row['N'])
                south = int(row['S'])

                source_node = graph.get_node_via_name(cell)
                source_row = int(source_node.get_row())
                source_column = int(source_node.get_column())
                # create all the edges now
                if north == 1:
                    dest_row = source_row - 1
                    dest_column = source_column
                    destination_node = graph.get_node_via_row_column(dest_row, dest_column)
                    graph.set_edge_unweighted(source_node, destination_node)
                if south == 1:
                    dest_row = source_row + 1
                    dest_column = source_column
                    destination_node = graph.get_node_via_row_column(dest_row, dest_column)
                    graph.set_edge_unweighted(source_node, destination_node)
                if east == 1:
                    dest_row = source_row
                    dest_column = source_column + 1
                    destination_node = graph.get_node_via_row_column(dest_row, dest_column)
                    graph.set_edge_unweighted(source_node, destination_node)
                if west == 1:
                    dest_row = source_row
                    dest_column = source_column  - 1
                    destination_node = graph.get_node_via_row_column(dest_row, dest_column)
                    graph.set_edge_unweighted(source_node, destination_node)



    except FileNotFoundError:
        print("Error opening file")
        return None