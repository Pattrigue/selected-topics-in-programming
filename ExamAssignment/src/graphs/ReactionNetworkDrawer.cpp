#include "ReactionNetworkDrawer.h"

namespace StochSimLib::Graphs {
    
    std::string ReactionNetworkDrawer::truncateDecimal(double num) {
        std::ostringstream out;
        out << std::setprecision(9) << std::fixed << num;
        std::string truncated = out.str();
        truncated.erase(truncated.find_last_not_of('0') + 1, std::string::npos);
        
        if (truncated.back() == '.') {
            truncated.pop_back();
        }
        
        return truncated;
    }

    void ReactionNetworkDrawer::createNode(Agraph_t *g, const std::string &name, const std::string &fillColor,
                                           const std::string &shape) {
        auto node = agnode(g, (char *) name.c_str(), 1);
        agsafeset(node, (char *) "style", (char *) "filled", (char *) "");
        agsafeset(node, (char *) "fillcolor", (char *) fillColor.c_str(), (char *) "");
        agsafeset(node, (char *) "shape", (char *) shape.c_str(), (char *) "");
    }

    void ReactionNetworkDrawer::createEdge(Agraph_t *g, const std::string &source, const std::string &destination) {
        if (source == "env" || destination == "env") {
            return;
        }

        agedge(g, agnode(g, (char *) source.c_str(), 1), agnode(g, (char *) destination.c_str(), 1), nullptr, 1);
    }

    void ReactionNetworkDrawer::draw(const Simulation &simulation, const std::string &filename, const std::string &format) {
        GVC_t *gvc = gvContext();
        Agraph_t *g = agopen((char*)"g", Agdirected, nullptr);

        // Create species nodes
        for (const auto &[_, species]: simulation.species()) {
            if (species->name() != "env") {
                createNode(g, species->name(), "lightgreen");
            }
        }

        // Draw edges between species based on reactions
        int rateNodeCount = 0;

        for (const auto &[reactionName, reaction]: simulation.reactions()) {
            // Create rate node
            double rate = reaction->rate;
            
            std::string rateStr = truncateDecimal(rate);
            std::string rateNodeName = "rate" + std::to_string(rateNodeCount++);
            
            createNode(g, rateNodeName, "lightblue", "box");
            agset(agnode(g, (char *) rateNodeName.c_str(), 1), (char*)"label", (char*)rateStr.c_str());

            // Draw edges between every species in the reaction as well as the rate node
            for (const auto &x: reaction->reactants()) {
                createEdge(g, x->name(), rateNodeName);
            }

            for (const auto &x: reaction->products()) {
                createEdge(g, rateNodeName, x->name());
            }
        }

        // Render the graph and free resources
        gvLayout(gvc, g, "dot");
        gvRenderFilename(gvc, g, (char*)format.c_str(), (char*)(filename + "." + format).c_str());
        gvFreeLayout(gvc, g);
        agclose(g);
        gvFreeContext(gvc);
    }
    
}