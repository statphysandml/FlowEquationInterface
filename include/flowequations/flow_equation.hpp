#ifndef FLOWEQUATIONS_FLOW_EQUATION_HPP
#define FLOWEQUATIONS_FLOW_EQUATION_HPP

#include <vector>
#include <string>
#include <memory>

#include <nlohmann/json.hpp>

#include <devdat/header.hpp>
#include <devdat/devdat.hpp>


using json = nlohmann::json;


namespace flowequations {
    class FlowEquationsWrapper : public std::enable_shared_from_this<FlowEquationsWrapper>
    {
    public:
        virtual void operator() (devdat::DimensionIteratorC &derivatives, const devdat::DevDatC &variables, const int dim_index) = 0;
        
        virtual size_t get_dim() = 0;

        virtual json get_json() const;

        static std::string name();
    };

    struct FlowEquation
    {
        virtual void operator() (devdat::DimensionIteratorC &derivatives, const devdat::DevDatC &variables) = 0;
    };

    template<typename FlowEquations, typename... Args>
    std::shared_ptr<FlowEquationsWrapper> generate_flow_equations(Args... args)
    {
        return std::make_shared<FlowEquations>(args...);
    }

    devdat::DevDatC compute_flow(const devdat::DevDatC &coordinates, FlowEquationsWrapper * flow_equations);

    void compute_flow(const devdat::DevDatC &coordinates, devdat::DevDatC &vertex_velocities, FlowEquationsWrapper * flow_equations);
}

#endif //FLOWEQUATIONS_FLOW_EQUATION_HPP
