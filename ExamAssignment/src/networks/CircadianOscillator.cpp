#ifndef STOCHSIMLIB_CIRCADIANOSCILLATOR_CPP
#define STOCHSIMLIB_CIRCADIANOSCILLATOR_CPP

#include "Simulation.h"
#include "Reaction.h"

namespace StochSimLib::Networks {

    /** Creates a simulation of the circadian oscillator based on the model from the PDF. */
    Simulation circadianOscillator() {
        auto alphaA = 50.0;
        auto alpha_A = 500.0;
        auto alphaR = 0.01;
        auto alpha_R = 50.0;
        auto betaA = 50.0;
        auto betaR = 5.0;
        auto gammaA = 1.0;
        auto gammaR = 1.0;
        auto gammaC = 2.0;
        auto deltaA = 1.0;
        auto deltaR = 0.2;
        auto deltaMA = 10.0;
        auto deltaMR = 0.5;
        auto thetaA = 50.0;
        auto thetaR = 100.0;

        Simulation simulation{};

        auto env = simulation.environment();

        auto DA = simulation.addSpecies("DA", 1);
        auto D_A = simulation.addSpecies("D_A", 0);
        auto DR = simulation.addSpecies("DR", 1);
        auto D_R = simulation.addSpecies("D_R", 0);
        auto MA = simulation.addSpecies("MA", 0);
        auto MR = simulation.addSpecies("MR", 0);
        auto A = simulation.addSpecies("A", 0);
        auto R = simulation.addSpecies("R", 0);
        auto C = simulation.addSpecies("C", 0);

        simulation.addReaction(A + DA >>= D_A, gammaA);
        simulation.addReaction(D_A >>= DA + A, thetaA);
        simulation.addReaction(A + DR >>= D_R, gammaR);
        simulation.addReaction(D_R >>= DR + A, thetaR);
        simulation.addReaction(D_A >>= MA + D_A, alpha_A);
        simulation.addReaction(DA >>= MA + DA, alphaA);
        simulation.addReaction(D_R >>= MR + D_R, alpha_R);
        simulation.addReaction(DR >>= MR + DR, alphaR);
        simulation.addReaction(MA >>= MA + A, betaA);
        simulation.addReaction(MR >>= MR + R, betaR);
        simulation.addReaction(A + R >>= C, gammaC);
        simulation.addReaction(C >>= R, deltaA);
        simulation.addReaction(A >>= env, deltaA);
        simulation.addReaction(R >>= env, deltaR);
        simulation.addReaction(MA >>= env, deltaMA);
        simulation.addReaction(MR >>= env, deltaMR);

        return simulation;
    }

}

#endif