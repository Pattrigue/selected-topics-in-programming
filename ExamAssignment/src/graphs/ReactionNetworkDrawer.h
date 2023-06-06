#ifndef STOCHSIMLIB_REACTIONNETWORKDRAWER_H
#define STOCHSIMLIB_REACTIONNETWORKDRAWER_H

#include <sstream>
#include <iomanip>
#include <string>

#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

#include "Simulation.h"

namespace StochSimLib::Graphs {

    class ReactionNetworkDrawer {
        /** Truncates a double to 9 decimal places and removes trailing zeros.
         * Also removes the decimal point if it's the last character. */
        static std::string truncateDecimal(double num);

        /** Creates a node in the graph with the given name, fill color, and shape. */
        static void createNode(Agraph_t *g, const std::string &name, const std::string &fillColor,
                               const std::string &shape = "ellipse");

        /** Creates an edge in the graph with the given source and destination.
         * Ignores the edge if either the source or destination is the environment. */
        static void createEdge(Agraph_t *g, const std::string &source, const std::string &destination);

    public:
        /** Fulfills part of requirement 2: 
        * "Pretty print the reaction network in a network graph". */
        static void draw(const StochSimLib::Simulation &simulation, const std::string &filename = "graph", const std::string &format = "png");
    };
    
} 

#endif 
