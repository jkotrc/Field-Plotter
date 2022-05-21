#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "util/vectors.h"
#include <mutex>
#include <vector>

namespace fp {
    struct SimulationConfig {
        double dt;
        double dx;
        //potentially integrators here?
    };

    /*
    ** Parameters for field line computation:
    ** dt ::
    ** visible_dt ::
    ** subdivisions :: how many pieces of each spherical angle to start the lines at
    */
    struct FieldLinesConfig {
        double dt;
        double visible_dt;
        double subdivisions;
    };

    /*
    ** A class taking as input the charges and exposing a buffer for field lines and vectors
    */
    template <int dim>
    class Simulation {
        public:
            Simulation(SimulationConfig const& simconfig);
            ~Simulation(); //especially important here
            void addCharge(Vec<dim> const& point, double charge);
            void removeCharge(int index);
            Vec<dim> getCharge(int index) const;
            bool startSim(); //return true if successfull and false if another sim is running
            bool loadNext(std::vector<Vec<dim>>& output); //returns true when a line has finished. Subsequent calls return other lines
        private:
            int load_index;
            std::lock_guard<std::mutex> m_guard;
            bool sim_running;
    };
}

#endif // SIMULATION_H_
